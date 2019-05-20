#pragma once
#include <string>

#include "common.hpp"

using std::vector;
using std::string;

using namespace common;

class ProfileClass {

    public: 

        struct [[eosio::table, eosio::contract("gyftietoken")]] Profile
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
        profile_table profile_t;

        

        auto load (const name& account) {
            auto p_itr = profile_t.find (account.value);
            eosio::check (p_itr != profile_t.end(), "Account profile is not found.");

            return *p_itr;
        }

        auto create (const name& account, const string& idhash, const string& id_expiration) {
            eosio::check (profile_t.find (account.value) == profile_t.end(), "Account already has a Gyftie profile.");

            return profile_t.emplace (_contract, [&](auto &p) {
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
            return profile_t.find (account.value) != profile_t.end();
        }

        auto unstake (const name& account, const asset& quantity) {
            Profile profile = load (account);
            eosio::check (profile.unstaking_balance >= quantity, "Unstaking balance is less than quantity unstaking.");

            return profile_t.modify (profile, _contract, [&](auto &p) {
                p.gft_balance += quantity;
                p.unstaking_balance -= quantity;
            });
        }

        auto stake (const name& account, const asset& quantity) {
            Profile profile = load (account);
            eosio::check (profile.gft_balance >= quantity, "Liquid balance is less than quantity unstaking.");

            return profile_t.modify (profile, _contract, [&](auto &p) {
                p.gft_balance -= quantity;
                p.staked_balance += quantity;
            });
        }

        auto setrank (const name& account, const uint64_t& rank) 
        {
            require_auth (_contract);

            auto p_itr = profile_t.find (account.value);
            eosio::check (p_itr != profile_t.end(), "Account to rank does not have a Gyftie profile.");
            
            profile_t.modify (p_itr, _contract, [&](auto &p) {
                p.rank = rank;
            });
        }



        // ACTION gyftietoken::promoteuser (const name account)
        // {
        //     profile_table profile_t (get_self(), get_self().value);
        //     auto p_itr = profile_t.find (account.value);
        //     eosio::check (p_itr != profile_t.end(), "Profile to promote is not found.");
        //     eosio::check (p_itr->rank != 1, "User rank is at highest level; cannot be promoted.");
        //     eosio::check (p_itr->promotion_votes.size() > 0, "There are no votes to promote this user.");

        //     print (" Promoting user: ", account, "\n");
        //     print (" Current rank: ", p_itr->rank, "\n");
        //     // bool promoted = false;
            
        //     std::set<int> potential_ranks = get_voting_ranks (account);
        //     int rank_profile_count, votes_from_rank, best_eligible_rank=0;

        //     auto potential_rank = potential_ranks.rbegin();
        //     while (potential_rank != potential_ranks.rend()) {

        //         rank_profile_count = get_rank_profile_count (*potential_rank);
        //         print ("  Rank Profile Count: ", *potential_rank, ".......", rank_profile_count, "\n");

        //         votes_from_rank = get_votes_from_rank(account, *potential_rank);
        //         print ("  Votes from Rank: ", *potential_rank, ".......", votes_from_rank, "\n");

        //         if (best_eligible_rank == 0) {
        //             best_eligible_rank = *potential_rank + rank_profile_count - votes_from_rank;
        //         } else {
        //             best_eligible_rank = std::min (  best_eligible_rank, 
        //                                         *potential_rank + rank_profile_count - votes_from_rank);
        //         }

        //         print ("---- Best eligible rank ", std::to_string(best_eligible_rank), "\n");
        //         potential_rank++;
        //     }

        //     if (p_itr->rank == 0 || best_eligible_rank < p_itr->rank) {
        //         print ("\n\n *** Promoting user: ", best_eligible_rank, "\n\n");
        //         profile_t.modify (p_itr, get_self(), [&](auto &p) {
        //             p.rank = best_eligible_rank;
        //         });
        //     } else { 
        //         eosio::check (false, "User does not have the votes to be promoted.");
        //     }
        // }

};