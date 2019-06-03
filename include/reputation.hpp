#ifndef REPUTATION_H
#define REPUTATION_H

#include <string>

#include "profile.hpp"

using std::vector;
using std::string;

using namespace common;

class ReputationClass {

    public:

        name            contract;
        ProfileClass    profileClass;

        ReputationClass (const name& contract);

        uint64_t get_rank_profile_count (const uint64_t& rank);
        uint64_t get_votes_from_rank (const name& contract, const uint64_t& rank);     
        uint64_t get_next_strongest_rank (const uint64_t& rank);  
        std::set<int> get_voting_ranks (const name& account);

};

#endif

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

       // ACTION gyftietoken::addrating (const name rater, const name ratee, const uint8_t rating)
        // {
        //     permit_account(rater);
        //     availrating_table a_t (get_self(), rater.value);
        //     auto a_itr = a_t.find (ratee.value);
        //     eosio::check (a_itr != a_t.end(), "Account is not available for rating.");
        //     eosio::check (has_auth (rater), "Only eligible rater can add a rating.");
        //     eosio::check (a_itr->rate_deadline >= current_block_time().to_time_point().sec_since_epoch(), "Deadline to rate account has passed.");

        //     profile_table p_t (get_self(), get_self().value);
        //     auto p_itr = p_t.find (ratee.value);
        //     eosio::check (p_itr != p_t.end(), "Account to rate is not found.");
            
        //     p_t.modify (p_itr, get_self(), [&](auto &p) {
        //         p.rating_count++;
        //         p.rating_sum += rating;
        //     });
            
        //     a_t.erase (a_itr);
        // }


// ACTION gyftietoken::voteforuser (const name voter, const name profile, const uint8_t vote)
// {
//     require_auth (voter);
//     eosio::check (is_tokenholder (voter), "Voter is not a GFT token holder.");

//     profile_table p_t (get_self(), get_self().value);
//     auto voter_profile_itr = p_t.find (voter.value);
//     eosio::check (voter_profile_itr != p_t.end(), "Account voting is not found.");

//     auto votee_profile_itr = p_t.find (profile.value);
//     eosio::check (votee_profile_itr != p_t.end(), "Account to vote for is not found.");

//     voter_table v_t (get_self(), voter.value);
//     auto v_itr = v_t.find (profile.value);
//     eosio::check (v_itr == v_t.end(), "Voter has already voted for this user per voter table.");

//     votee_table votee_t (get_self(), profile.value);
//     auto votee_itr = votee_t.find (voter.value);
//     eosio::check (votee_itr == votee_t.end(), "Voter has already voted for this user per votee table.");

//     uint64_t voting_power = (voter_profile_itr->scaled_sum_rating / voter_profile_itr->voter_count * vote);
//     p_t.modify (votee_profile_itr, get_self(), [&](auto &p) {
//         p.voter_count++;
//         p.scaled_sum_rating += voting_power;
//     });

//     v_t.modify (v_itr, get_self(), [&](auto &v) {
//         v.votee = profile;
//         v.vote_power = voting_power;
//     });

//     votee_t.modify (votee_itr, get_self(), [&](auto &v) {
//         v.voter = voter;
//         v.vote_power = voting_power;
//     });
// }


