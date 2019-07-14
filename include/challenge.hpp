#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <iterator>
#include <eosio/eosio.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/asset.hpp>

#include "common.hpp"

using std::string;
using std::vector;
using std::iterator;
using namespace eosio;

class BadgeClass
{

  private:
    name contract;

  public:
    struct [[ eosio::table, eosio::contract("gyftietoken") ]] Challenge 
    {
        name            challenged_account;
        name            challenger_account;
        vector<string>  challenge_notes;
        asset           challenge_stake;
        uint32_t        challenged_time;
        uint64_t        primary_key () const { return challenged_account.value; }
        uint64_t        by_challenger() const { return challenger_account.value; }
    };
    typedef eosio::multi_index<"challenges"_n, challenge,
        indexed_by<"bychallenger"_n,
            const_mem_fun<challenge, uint64_t, &challenge::by_challenger>>
    > challenge_table;

    challenge_table     challenge_t;

    ChallengeClass (const name& contract) : 
        challenge_t    (contract, contract.value),
        contract        (contract) {}
    
    void dchallenge (const name& challenged_account) 
    {
        // require_auth (get_self());
        // challenge_table c_t (get_self(), get_self().value);
        // auto c_itr = c_t.find (challenged_account.value);
        // eosio::check (c_itr != c_t.end(), "Active challenge for account does not exist.");

        // c_t.erase (c_itr);
    }

    void nchallenge (const name& challenger_account, const name& challenged_account, const string& note)
    {
        // Permit::permit (get_self(), challenger_account, challenged_account, Permit::CHALLENGE);

        // asset challenge_stake = adjust_asset (getgftbalance (challenged_account), (float) 0.10000000);
        // stake (challenger_account, challenge_stake);

        // challenge_table c_t (get_self(), get_self().value);
        // auto c_itr = c_t.find(challenged_account.value);
        // eosio::check (c_itr == c_t.end(), "Account has already been challenged.");

        // c_t.emplace (get_self(), [&](auto &c) {
        //     c.challenged_account = challenged_account;
        //     c.challenger_account = challenger_account;
        //     c.challenged_time = current_block_time().to_time_point().sec_since_epoch();
        //     c.challenge_notes.push_back (note);
        //     c.challenge_stake = challenge_stake;
        // });
    }

};

#endif