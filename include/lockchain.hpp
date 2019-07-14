#ifndef LOCKCHAIN_H
#define LOCKCHAIN_H

#include "common.hpp"
#include "gyft.hpp"
#include "permit.hpp"
#include "gyftie.hpp"
#include "lock.hpp"

using std::vector;
using namespace eosio;
using namespace common;

class LockChain  {

    public:

    static void unlockchain (const name& contract, const name account_to_unlock, const string note)
    {
        // Permit::permit (contract, account_to_unlock, name{0}, Permit::ANY_SIGNATORY);

        GyftieClass gyftieClass = GyftieClass (contract);

        LockClass lockClass = LockClass (contract);
        lockClass.unlock (account_to_unlock, note);

        GyftClass gyftClass = GyftClass (contract);
        auto gyfter_index = gyftClass.gyft_t.get_index<"bygyfter"_n>();
        auto gyfter_itr = gyfter_index.find (account_to_unlock.value);
        if (gyfter_itr == gyfter_index.end()) {
            return;
        }

        while (gyfter_itr->gyfter == account_to_unlock && gyfter_itr != gyfter_index.end()) {
            eosio::transaction out{};
            out.actions.emplace_back(permission_level{contract, "owner"_n}, 
                                    contract, "unlockchain"_n, 
                                    std::make_tuple(gyfter_itr->gyftee, note));
            out.delay_sec = 1;
            out.send(gyftieClass.get_next_sender_id(), contract);    

            gyfter_itr++;
        }
    }

    static void lockchain (const name& contract, const name account_to_lock, const string note)
    {
        // Permit::permit (contract, account_to_unlock, name{0}, Permit::ANY_SIGNATORY);

        GyftieClass gyftieClass = GyftieClass (contract);

        LockClass lockClass = LockClass (contract);
        lockClass.lock (account_to_lock, note);

        GyftClass gyftClass = GyftClass (contract);
        auto gyfter_index = gyftClass.gyft_t.get_index<"bygyfter"_n>();
        auto gyfter_itr = gyfter_index.find (account_to_lock.value);
        if (gyfter_itr == gyfter_index.end()) {
            return;
        }

        while (gyfter_itr->gyfter == account_to_lock && gyfter_itr != gyfter_index.end()) {
            eosio::transaction out{};
            out.actions.emplace_back(permission_level{contract, "owner"_n}, 
                                    contract, "lockchain"_n, 
                                    std::make_tuple(gyfter_itr->gyftee, note));
            out.delay_sec = 1;
            out.send(gyftieClass.get_next_sender_id(), contract);    

            gyfter_itr++;
        }
    }

};

#endif