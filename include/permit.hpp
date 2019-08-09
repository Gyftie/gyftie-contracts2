#ifndef PERMIT_H
#define PERMIT_H

#include "lock.hpp"
#include "gyft.hpp"
#include "profile.hpp"
#include "gyftie.hpp"
#include "badge.hpp"
#include "common.hpp"
#include "challenge.hpp"

using namespace eosio;
using namespace common;


class Permit {

    public: 
    static const int    ANY                         =   0;
    static const int    GYFT                        =   1;
    static const int    VOTE                        =   2;
    static const int    CHALLENGE                   =   3;
    static const int    VALIDATE                    =   4;
    static const int    PROPOSE                     =   5;
    static const int    TRANSFER                    =   6;
    static const int    REMOVE_PROPOSAL             =   7;
    static const int    ANY_SIGNATORY               =   8;
    static const int    AUTH_ACTIVITY               =   9;
    static const int    LOCK_ACTIVITY               =   10;
    static const int    ORACLE_ACTIVITY             =   11;
    static const int    SELFORSIGNATORY_ACTIVITY    =   12;
    static const int    SELLGFT_ACTIVITY            =   13;

    struct [[ eosio::table, eosio::contract("gyftietoken") ]] signatory
    {
        name        account;
        uint64_t    primary_key() const { return account.value; }
    };
    typedef eosio::multi_index<"signatories"_n, signatory> signatory_table;

    static auto add_signatory (const name& contract, const name& new_signatory) {
        require_auth (contract);
        signatory_table s_t (contract, contract.value);
        auto s_itr = s_t.find (new_signatory.value);
        eosio::check (s_itr == s_t.end(), "Account is already a signatory.");

        return s_t.emplace (contract, [&](auto &s) {
            s.account = new_signatory;
        });
    }

    static auto remove_signatory (const name& contract, const name& new_signatory) {
        require_auth (contract);
        signatory_table s_t (contract, contract.value);
        auto s_itr = s_t.find (new_signatory.value);
        eosio::check (s_itr != s_t.end(), "Signatory not found.");

        return s_t.erase (s_itr);
    }

    //static name _contract;
    //static signatory_table signatory_t;

    class Activity {

        public:

        static void permit (const name& contract, const name& account, const name& receiver) {

            eosio::check (is_account (account), "Account is not an valid EOS account.");
            eosio::check (is_account (receiver), "Receiver is not a valid EOS account.");

            ProfileClass profileClass (contract);
            
            eosio::check (!profileClass.existsInV1 (account), "Account " + account.to_string() + " must upgrade profile.");
            eosio::check (profileClass.existsInV2 (account), "Account " + account.to_string() + " does not have a profile.");

            if (receiver.value != 0) {
                eosio::check (!profileClass.existsInV1 (receiver), "Receiver account " + receiver.to_string() + " must upgrade profile.");
                eosio::check (profileClass.existsInV2 (receiver), "Receiver account " + receiver.to_string() + " does not have a profile.");
            }

            LockClass lockClass (contract);
            eosio::check (lockClass.lock_t.find(account.value) == lockClass.lock_t.end(), "Account is locked from performing activity.");

            GyftieClass gyftieClass (contract);
            eosio::check (gyftieClass.get_state().paused == UNPAUSED, "Contract is paused.");
            
            // Verify that the account is not being challenged
            ChallengeClass challengeClass (contract);
            auto c_itr = challengeClass.challenge_t.find (account.value);
            check (c_itr == challengeClass.challenge_t.end(), "Account " + account.to_string() + " has an active challenge.");
            c_itr = challengeClass.challenge_t.find (receiver.value);
            check (c_itr == challengeClass.challenge_t.end(), "Receiver " + receiver.to_string() + " has an active challenge.");
        }
    };

    class ChallengeActivity : Activity {

        public:

        static void permit (const name& contract, const name& account, const name& receiver) {
            Activity::permit (contract, account, receiver);      
            check (account != receiver, "Account cannot challenge itself.");
            require_auth (account);
        }
    };

    class OracleActivity : Activity {

        public: 

        static void permit (const name& contract, const name& gyftieAccount, const name& anyAccount) {
            Activity::permit (contract, gyftieAccount, gyftieAccount);

            check (is_account(anyAccount), "Account is not a valid EOS account: " + anyAccount.to_string());

            GyftieClass gyftieClass (contract);
            check (gyftieClass.get_state().gyftieoracle.value > 0, "Gyftie oracle is not set.");

            require_auth (gyftieClass.get_state().gyftieoracle);
        }
    };

    class AuthActivity : Activity {

        public: 

        static void permit (const name& contract, const name& account) {
            Activity::permit (contract, account, account);
            require_auth (account);
        }
    };

    class SellGFTActivity : Activity {
        public:

        static void permit (const name& contract, const name& account) { //}, const asset& sell_amount) {
            AuthActivity::permit (contract, account);

            BadgeClass badgeClass (contract);
            check (badgeClass.is_badgeholder("verified"_n, account), "Account " + account.to_string() + " must be verified (with badge) to sell GFT.");
        }
    };

    class SelfOrSignatoryActivity {
        public:

        static void permit (const name& contract, const name& gyftieAccount) {
            if (has_auth (gyftieAccount) || has_auth (gyftieAccount)) {
                return;
            }

            bool signed_by_signatory = false;
            signatory_table signatory_t (contract, contract.value);
            auto s_itr = signatory_t.begin();

            while (!signed_by_signatory && s_itr != signatory_t.end()) {
                signed_by_signatory = has_auth (s_itr->account);
                s_itr++;
            }

            eosio::check (signed_by_signatory, "Transaction requires the approval of the Gyftie account or a signatory.");
        }
    };

    class SignatoryActivity {

        public: 

        static void permit (const name& contract) {
           
            if (has_auth (contract)) {
                return;
            }

            bool signed_by_signatory = false;
            signatory_table signatory_t (contract, contract.value);
            auto s_itr = signatory_t.begin();

            while (!signed_by_signatory && s_itr != signatory_t.end()) {
                signed_by_signatory = has_auth (s_itr->account);
                s_itr++;
            }

            eosio::check (signed_by_signatory, "Transaction requires the approval of a signatory.");
        }
    };

    class LockActivity : SignatoryActivity {
        public:
        static void permit (const name& contract, const name& account) {
            SignatoryActivity::permit (contract);

            eosio::check (is_account (account), "Account is not a valid EOS account.");

            ProfileClass profileClass (contract);
            eosio::check (profileClass.exists (account), "Account does not have a Gyftie profile.");
        }
    };


    class ValidateActivity : Activity {

        public: 
        static void permit (const name& contract, const name& account, const name& receiver) {
            Activity::permit (contract, account, receiver);
            GyftClass gyftClass (contract);
            auto gyfter_index = gyftClass.gyft_t.get_index<"bygyfter"_n>();
            auto gyfter_itr = gyfter_index.find(account.value);

            while (gyfter_itr != gyfter_index.end() && gyfter_itr->gyfter == account) {
                eosio::check (gyfter_itr->gyftee != receiver, "Validator cannot validate an account they gyfted.");
                gyfter_itr++;
            }

            auto gyftee_index = gyftClass.gyft_t.get_index<"bygyftee"_n>();
            auto gyftee_itr = gyftee_index.find(account.value);

            while (gyftee_itr != gyftee_index.end() && gyftee_itr->gyftee == account) {
                eosio::check (gyftee_itr->gyfter != receiver, "Validator cannot validate their gyfter.");
                gyftee_itr++;
            }
        }
    };
    
    static void permit  (const name& contract, const name& account, const name& receiver, const int& permission) {
        switch (permission) {
            case ANY:
                Activity::permit (contract, account, receiver);
                break;
            case CHALLENGE:
                ChallengeActivity::permit (contract, account, receiver);
                break;
            case VALIDATE:
                ValidateActivity::permit (contract, account, receiver);
                break;
            case PROPOSE:
                Activity::permit (contract, account, receiver);
                break;
            case TRANSFER:
                Activity::permit (contract, account, receiver);
                break;
            case GYFT:
                Activity::permit (contract, account, receiver);
                break;
            case REMOVE_PROPOSAL:
                AuthActivity::permit (contract, account);
                break;
            case ANY_SIGNATORY: 
                SignatoryActivity::permit (contract);
                break;
            case AUTH_ACTIVITY: 
                AuthActivity::permit (contract, account);
                break;
            case LOCK_ACTIVITY:
                LockActivity::permit (contract, account);
                break;
            case ORACLE_ACTIVITY:
                OracleActivity::permit (contract, account, receiver);
                break;
            case SELFORSIGNATORY_ACTIVITY:
                SelfOrSignatoryActivity::permit (contract, account);
                break;
            case SELLGFT_ACTIVITY:
                SellGFTActivity::permit (contract, account);
                break;
        }
    }
};


#endif