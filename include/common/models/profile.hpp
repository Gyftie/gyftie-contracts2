#pragma once
#include <string>

#include "../common.hpp"

using std::vector;
using std::string;

using namespace common;

class ProfileClass {

    public: 

        TABLE Profile
        {
            name        account;
            uint32_t    rating_sum;
            uint16_t    rating_count;
            string      idhash;
            string      id_expiration;
            asset       gft_balance;
            asset       staked_balance;
            asset       unstaking_balance; 

            // DEPLOY
            vector<name>    promotion_votes;
            uint64_t    rank=0;
            uint64_t    by_rank() const { return rank; }

            uint64_t    voter_count;
            uint64_t    scaled_sum_rating;
            uint64_t    primary_key() const { return account.value; }
        };

        typedef eosio::multi_index<"profiles"_n, Profile,
            indexed_by<"byrank"_n,
                const_mem_fun<Profile, uint64_t, &Profile::by_rank>>
        > profile_table;
   
        name _contract;
        profile_table p_t;

        ProfileClass (const name& contract) : p_t (contract, contract.value) {
            _contract = contract;
        }

        auto load (const name& account) {
            auto p_itr = p_t.find (account.value);
            eosio::check (p_itr != p_t.end(), "Account profile is not found.");

            return *p_itr;
        }

        auto create (const name& account, const string& idhash, const string& id_expiration) {
            eosio::check (p_t.find (account.value) == p_t.end(), "Account already has a Gyftie profile.");

            return p_t.emplace (_contract, [&](auto &p) {
                p.account = account;
                p.rating_count = 0;
                p.rating_sum = 0;
                p.idhash = idhash;
                p.id_expiration = id_expiration;
                p.gft_balance = asset {0, S_GFT};
                p.unstaking_balance = asset {0, S_GFT};
                p.staked_balance = asset {0, S_GFT};
            });         
        }

        bool exists (const name& account) {
            return p_t.find (account.value) != p_t.end();
        }
};