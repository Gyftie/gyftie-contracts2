#ifndef LOCK_H
#define LOCK_H

#include "common.hpp"
#include "gyft.hpp"

using std::vector;
using namespace eosio;
using namespace common;

class LockClass  {

    public:

        struct [[ eosio::table, eosio::contract("gyftietoken") ]] Lock 
        {
            name            account;
            vector<string>  lock_notes;
            uint64_t        primary_key() const { return account.value; }
        };

        typedef eosio::multi_index<"locks"_n, Lock> lock_table;

        name        contract;
        lock_table  lock_t;
        GyftClass   gyftClass;

        LockClass (const name& contract) 
            : lock_t (contract, contract.value), 
            gyftClass (contract),
            contract (contract){}

        iterator<std::bidirectional_iterator_tag, const Lock> lock (const name& account_to_lock, const string& note) {

            check (lock_t.find (account_to_lock.value) == lock_t.end(), "Account is already locked.");

            return lock_t.emplace (contract, [&](auto &l) {
                l.account = account_to_lock;
                l.lock_notes.push_back (note);
            });
        }

        iterator<std::bidirectional_iterator_tag, const Lock> unlock (const name& account_to_unlock, const string& note) {

            auto l_itr = lock_t.find (account_to_unlock.value);
            check (l_itr != lock_t.end(), "Account is not locked.");

            return lock_t.erase (l_itr);
        }

        iterator<std::bidirectional_iterator_tag, const Lock> add_lock_note (const name& locked_account, const string& note) {

            auto l_itr = lock_t.find (locked_account.value);
            check (l_itr != lock_t.end(), "Account is not locked.");

            lock_t.modify (l_itr, contract, [&](auto &l) {
                l.lock_notes.push_back(note);
            });

            return l_itr;
        }
};

#endif