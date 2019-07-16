#ifndef MIGRATION_H
#define MIGRATION_H

#include <iterator>
#include <eosio/eosio.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/asset.hpp>

#include "common.hpp"
#include "gyftie.hpp"
#include "profile.hpp"

using std::string;
using std::vector;
using std::iterator;
using namespace eosio;

class Migration {

    public:
        struct [[ eosio::table, eosio::contract("gyftietoken") ]] tprofile
        {
            name        account;
            string      idhash;
            string      id_expiration;
            asset       gft_balance;
            asset       staked_balance;
            asset       unstaking_balance;
            uint64_t    primary_key() const { return account.value; }
        };
        typedef eosio::multi_index<"tprofiles"_n, tprofile> tprofile_table;

        struct [[ eosio::table, eosio::contract("gyftietoken") ]] Promo 
        {
            uint64_t promo_count = 0;
        };

        typedef singleton<"promos"_n, Promo> promo_table;
        typedef eosio::multi_index<"promos"_n, Promo> promo_table_placeholder;

        struct [[ eosio::table, eosio::contract("gyftietoken") ]] Config
        {
            name token_gen;
            name gftorderbook;
            name gyftie_foundation;
            uint8_t paused;
        };

        typedef singleton<"configs"_n, Config> config_table;
        typedef eosio::multi_index<"configs"_n, Config> config_table_placeholder;

        struct [[ eosio::table, eosio::contract("gyftietoken") ]] Counter
        {
            uint32_t account_count = 0;
        };

        typedef singleton<"counters"_n, Counter> counter_table;
        typedef eosio::multi_index<"counters"_n, Counter> counter_table_placeholder;

        struct [[ eosio::table, eosio::contract("gyftietoken") ]] State 
        {
            uint32_t    user_count = 0;
            uint32_t    prior_step_user_count;   

            uint64_t    pol_scaled_user_count_decay;
            uint64_t    pol_scaled_step_increase;

            uint64_t    scaled_user_count_factor=100000000;
        };

        typedef singleton<"states"_n, State> state_table;
        typedef eosio::multi_index<"states"_n, State> state_table_placeholder;

        struct [[ eosio::table, eosio::contract("gyftietoken") ]] Throttle 
        {
            uint32_t throttle = 0;
        };

        typedef singleton<"throttles"_n, Throttle> throttle_table;
        typedef eosio::multi_index<"throttles"_n, Throttle> throttle_table_placeholder;

        struct [[ eosio::table, eosio::contract("gyftietoken") ]] SenderID
        {
            uint64_t    last_sender_id;
        };
        typedef singleton<"senderids"_n, SenderID> senderid_table;
        typedef eosio::multi_index<"senderids"_n, SenderID> senderid_table_placeholder;


        ProfileClass    profileClass;
        GyftieClass     gyftieClass;
        name            contract;
        tprofile_table  tprofile_t;
        promo_table     promo_t;
        config_table    config_t;
        counter_table   counter_t;
        state_table     state_t;
        throttle_table  throttle_t;
        senderid_table  senderid_t;

        Migration (const name& contract)
            : profileClass (contract),
                gyftieClass (contract),
                contract (contract),
                promo_t (contract, contract.value),
                config_t (contract, contract.value),
                counter_t (contract, contract.value),
                state_t (contract, contract.value),
                throttle_t (contract, contract.value),
                senderid_t (contract, contract.value),
                tprofile_t (contract, contract.value) {} 

        void remove_old_tables () {
            promo_t.remove ();
            config_t.remove();
            counter_t.remove();
            state_t.remove();
            throttle_t.remove();
            senderid_t.remove();
        }

        void backupprofs (const name& profile) {
            uint32_t prof_count = 0;

            auto p_itr = profileClass.profile_t.find (profile.value);
            check (p_itr != profileClass.profile_t.end(), "Profile record for account not found: " + profile.to_string());

            while (p_itr != profileClass.profile_t.end() && prof_count < 10) {
                copy_to_temp (p_itr->account);
                prof_count++;
                p_itr = profileClass.profile_t.erase (p_itr);
            }

            if (p_itr != profileClass.profile_t.end()) {
                eosio::transaction out{};
                out.actions.emplace_back(permission_level{contract, "owner"_n}, 
                                        contract, "backupprofs"_n, 
                                        std::make_tuple(p_itr->account));
                out.delay_sec = 1;
                out.send(gyftieClass.get_next_sender_id(), contract);    
            }
        }

        void restoreprofs (const name& profile) {
            uint32_t prof_count = 0;

            auto tp_itr = tprofile_t.find (profile.value);
            check (tp_itr != tprofile_t.end(), "Temp Profile record for account not found: " + profile.to_string());

            while (tp_itr != tprofile_t.end() && prof_count < 10) {
                copy_from_temp (tp_itr->account);
                prof_count++;
                tp_itr = tprofile_t.erase (tp_itr);
            }

            if (tp_itr != tprofile_t.end()) {
                eosio::transaction out{};
                out.actions.emplace_back(permission_level{contract, "owner"_n}, 
                                        contract, "restoreprofs"_n, 
                                        std::make_tuple(tp_itr->account));
                out.delay_sec = 1;
                out.send(gyftieClass.get_next_sender_id(), contract);    
            }
        }

        void copy_to_temp (const name& profile) {

            auto p_itr = profileClass.profile_t.find (profile.value);
            check (p_itr != profileClass.profile_t.end(), "Profile record for account not found: " + profile.to_string());

            tprofile_t.emplace (contract, [&](auto tp) {
                tp.account = p_itr->account;
                tp.idhash = p_itr->idhash;
                tp.id_expiration = p_itr->id_expiration;
                tp.gft_balance = p_itr->gft_balance;
                tp.staked_balance = p_itr->staked_balance;
                tp.unstaking_balance = p_itr->unstaking_balance;
            });
        }

        void copy_from_temp (const name& profile) {
            auto tp_itr = tprofile_t.find (profile.value);
            check (tp_itr != tprofile_t.end(), "Temp profile record from account not found: " + profile.to_string());

            profileClass.profile_t.emplace (contract, [&](auto p) {
                p.account           = tp_itr->account;
                p.idhash            = tp_itr->idhash;
                p.id_expiration     = tp_itr->id_expiration;
                p.gft_balance       = tp_itr->gft_balance;
                p.staked_balance    = tp_itr->staked_balance;
                p.unstaking_balance = tp_itr->unstaking_balance;
            });
        }
};

#endif