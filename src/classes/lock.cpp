#include "../../include/lock.hpp"

LockClass::LockClass (const name& contract) 
    : lock_t (contract, contract.value), 
    gyftClass (contract),
    contract (contract){}

iterator<std::bidirectional_iterator_tag, const LockClass::Lock> LockClass::lock (const name& account_to_lock, const string& note) {

    eosio::check (lock_t.find (account_to_lock.value) == lock_t.end(), "Account is already locked.");

    return lock_t.emplace (contract, [&](auto &l) {
        l.account = account_to_lock;
        l.lock_notes.push_back (note);
    });
}

iterator<std::bidirectional_iterator_tag, const LockClass::Lock> LockClass::unlock (const name& account_to_unlock, const string& note) {

    auto l_itr = lock_t.find (account_to_unlock.value);
    eosio::check (l_itr != lock_t.end(), "Account is not locked.");

    return lock_t.erase (l_itr);
}

iterator<std::bidirectional_iterator_tag, const LockClass::Lock> LockClass::add_lock_note (const name& locked_account, const string& note) {

    auto l_itr = lock_t.find (locked_account.value);
    eosio::check (l_itr != lock_t.end(), "Account is not locked.");

    lock_t.modify (l_itr, contract, [&](auto &l) {
        l.lock_notes.push_back(note);
    });

    return l_itr;
}
