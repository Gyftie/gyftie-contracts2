#pragma once

#include "common.hpp"
#include "gyft.hpp"

using std::vector;
using namespace eosio;
using namespace common;

class LockClass  {

    public:

        TABLE lock 
        {
            name            account;
            vector<string>  lock_notes;
            uint64_t        primary_key() const { return account.value; }
        };

        typedef eosio::multi_index<"locks"_n, lock> lock_table;

        name _contract;
        lock_table lock_t;
        GyftClass _gyftClass;

        LockClass (const name& contract) : lock_t (contract, contract.value), _gyftClass (contract) {
            _contract = contract;
        }

        auto lock (const name& account_to_lock, const string& note) {

            eosio::check (lock_t.find (account_to_lock.value) == lock_t.end(), "Account is already locked.");

            return lock_t.emplace (_contract, [&](auto &l) {
                l.account = account_to_lock;
                l.lock_notes.push_back (note);
            });
        }

        auto unlock (const name& account_to_unlock, const string& note) {

            auto l_itr = lock_t.find (account_to_unlock.value);
            eosio::check (l_itr != lock_t.end(), "Account is not locked.");

            return lock_t.erase (l_itr);
        }

        auto addlocknote (const name& locked_account, const string& note) {

            auto l_itr = lock_t.find (locked_account.value);
            eosio::check (l_itr != lock_t.end(), "Account is not locked.");

            return lock_t.modify (l_itr, _contract, [&](auto &l) {
                l.lock_notes.push_back(note);
            });
        }
};
