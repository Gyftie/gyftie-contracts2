#ifndef LOCK_H
#define LOCK_H

#include "common.hpp"
#include "gyft.hpp"

using std::vector;
using namespace eosio;
using namespace common;

class LockClass  {

    public:

        TABLE Lock 
        {
            name            account;
            vector<string>  lock_notes;
            uint64_t        primary_key() const { return account.value; }
        };

        typedef eosio::multi_index<"locks"_n, Lock> lock_table;

        name        contract;
        lock_table  lock_t;
        GyftClass   gyftClass;

        LockClass (const name& contract);

        iterator<std::bidirectional_iterator_tag, const Lock> lock (const name& account_to_lock, const string& note);
        iterator<std::bidirectional_iterator_tag, const Lock> unlock (const name& account_to_unlock, const string& note);
        iterator<std::bidirectional_iterator_tag, const Lock> add_lock_note (const name& locked_account, const string& note);
};

#endif