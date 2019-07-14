#ifndef PROPOSAL_H
#define PROPOSAL_H

#include <eosio/eosio.hpp>

#include "permit.hpp"
#include "profile.hpp"

using std::vector;
using std::string;

class ProposalClass {

    public:
        
        struct [[ eosio::table, eosio::contract("gyftietoken") ]] Proposal
        {
            uint64_t        proposal_id;
            uint32_t        created_date;
            name            proposer;
            string          notes;
            vector<name>    voters_for;
            uint32_t        votes_for;
            vector<name>    voters_against;
            uint32_t        votes_against;
            uint32_t        expiration_date;

            // DEPLOY
            // uint64_t        rank = 0;
            uint64_t        primary_key() const { return proposal_id; }
            // DEPLOY
            // uint64_t        by_created()  const { return created_date; }
            // uint64_t        by_expiration() const { return expiration_date; }
        };

        typedef eosio::multi_index<"proposals"_n, Proposal> proposal_table;

        // DEPLOY

        // typedef eosio::multi_index<"proposals:"_n, Proposal,
        //     indexed_by<"bycreated"_n,
        //         const_mem_fun<Proposal, uint64_t, &Proposal::bycreated>>
        //     indexed_by<"byexpire"_n,
        //         const_mem_fun<Proposal, uint64_t, &Proposal::byexpire>>
        // > proposal_table;


        name            contract;
        proposal_table  proposal_t;
        ProfileClass    profileClass;

            
        ProposalClass (const name& contract) : 
            proposal_t (contract, contract.value), 
            profileClass (contract),
            contract (contract) {}

        iterator<std::bidirectional_iterator_tag, const Proposal> create (const name& proposer, const string& notes) {
            require_auth (proposer);

            Permit::permit (contract, proposer, name{0}, Permit::PROPOSE);

            return proposal_t.emplace (proposer, [&](auto &p) {
                p.proposal_id       = proposal_t.available_primary_key();
                p.created_date      = current_block_time().to_time_point().sec_since_epoch();
                p.proposer          = proposer;
                p.notes             = notes;
                p.votes_for         = 1;
                p.voters_for.push_back(proposer);
                p.votes_against     = 0;

                // DEPLOY 
                // p.rank              = profileClass.profile_t.get(proposer.value).rank;
                p.expiration_date   = current_block_time().to_time_point().sec_since_epoch() + (60 * 60 * 24 * 30);  // 30 days
            });
        }

        // auto load (const uint64_t& proposal_id) {
        //     auto p_itr = proposal_t.find (proposal_id);
        //     eosio::check (p_itr != proposal_t.end(), "Proposal is not found.");
        //     return *p_itr;
        // }

        iterator<std::bidirectional_iterator_tag, const Proposal> remove (const uint64_t& proposal_id) {

            auto p_itr = proposal_t.find (proposal_id);
            eosio::check (p_itr != proposal_t.end(), "Proposal ID is not found: " + std::to_string(proposal_id));

            Permit::permit (contract, p_itr->proposer, name{0}, Permit::REMOVE_PROPOSAL);

            return proposal_t.erase (p_itr);
        }

        void check_vote (const Proposal p, const name& voter) {
            auto voter_for_itr = std::find (p.voters_for.begin(), p.voters_for.end(), voter);
            eosio::check (voter_for_itr == p.voters_for.end(), "User has already voted (for).");

            auto voter_against_itr = std::find (p.voters_against.begin(), p.voters_against.end(), voter);
            eosio::check (voter_against_itr == p.voters_against.end(), "User has already voted (against).");

            eosio::check (current_block_time().to_time_point().sec_since_epoch() <= p.expiration_date, "Proposal has expired.");
        }

        iterator<std::bidirectional_iterator_tag, const Proposal> vote_for (const name& voter, const uint64_t& proposal_id) {
            Permit::permit (contract, voter, name{0}, Permit::AUTH_ACTIVITY);
            
            auto p_itr = proposal_t.find (proposal_id);
            check (p_itr != proposal_t.end(), "Proposal ID does not exist: " + std::to_string(proposal_id));
            check_vote (*p_itr, voter);

            proposal_t.modify (p_itr, contract, [&](auto &p) {
                p.votes_for++;
                p.voters_for.push_back (voter);
            });
            return p_itr;
        }

        iterator<std::bidirectional_iterator_tag, const Proposal> vote_against (const name& voter, const uint64_t& proposal_id) {
            Permit::permit (contract, voter, name{0}, Permit::AUTH_ACTIVITY);

            auto p_itr = proposal_t.find (proposal_id);
            check (p_itr != proposal_t.end(), "Proposal ID does not exist: " + std::to_string(proposal_id));
            check_vote (*p_itr, voter);
            
            proposal_t.modify (p_itr, contract, [&](auto &p) {
                p.votes_for++;
                p.voters_for.push_back (voter);
            });

            return p_itr;
        }
                

        // ACTION gyftietoken::unvoteprop(const name voter, const uint64_t proposal_id) 
        // {
        //     eosio::check (! is_paused(), "Contract is paused." );

        //     require_auth (voter);
        //     eosio::check (is_tokenholder (voter), "Voter is not a GFT token holder.");
            
        //     proposal_table p_t (get_self(), get_self().value);
        //     auto p_itr = p_t.find (proposal_id);
        //     eosio::check (current_block_time().to_time_point().sec_since_epoch() <= p_itr->expiration_date, "Proposal has expired.");

        //     bool voter_found = false;

        //     auto voter_for_itr = std::find (p_itr->voters_for.begin(), p_itr->voters_for.end(), voter);
        //     if (voter_for_itr != p_itr->voters_for.end()) {
        //         p_t.modify (p_itr, get_self(), [&](auto &p) {
        //             p.voters_for.erase (voter_for_itr);
        //         });
        //         voter_found = true;
        //     }

        //     auto voter_against_itr = std::find (p_itr->voters_against.begin(), p_itr->voters_against.end(), voter);
        //     if (voter_against_itr != p_itr->voters_against.end()) {
        //         p_t.modify (p_itr, get_self(), [&](auto &p) {
        //             p.voters_against.erase (voter_against_itr);
        //         });
        //         voter_found = true;
        //     }

        //     eosio::check (voter_found, "Voter has not voted for or against this proposal.");
        // }

        // uint64_t get_proposal_votes_from_rank (const proposal& prop, const uint64_t* rank)
        // {
        //     uint64_t vote_count =0;
        //     vector<name> votes = prop.voters_for;
        //     for (auto voter : votes) {
        //         if (_profileClass.profile_t.get(voter.value).rank == rank) {
        //             vote_count++;
        //         }
        //     }

        //     return vote_count;
        // }
    
        // std::set<int> get_proposal_voting_ranks (const uint64_t proposal_id)
        //     {
        //         proposal_table p_t (get_self(), get_self().value);
        //         auto p_itr = p_t.find (proposal_id);
        //         eosio::check (p_itr != p_t.end(), "Proposal to promote is not found.");

        //         //profile_table profile_t (get_self(), get_self().value);

        //         vector<name> votes = p_itr->voters_for;
        //         std::set<int> rank_set;
        //         for (auto voter : votes) {
        //             if (profileClass.profile_t.get(voter.value).rank > 0) {
        //                 rank_set.insert (profileClass.profile_t.get(voter.value).rank);
        //             }
        //         }
        //         return rank_set;
        //     }


        // ACTION gyftietoken::promoteprop (const uint64_t proposal_id) 
        // {
        //     // proposal_table p_t (get_self(), get_self().value);
        //     // auto p_itr = p_t.find (proposal_id);
        //     // eosio::check (p_itr != p_t.end(), "Proposal ID to promote is not found.");
        //     // eosio::check (p_itr->rank != 1, "Proposal rank is at highest level; cannot be promoted.");
        //     // eosio::check (p_itr->voters_for.size() > 0, "There are no votes to promote this proposal.");

        //     // std::set<int> potential_ranks = get_proposal_voting_ranks (proposal_id);
        //     // eosio::check(potential_ranks.size() > 0, "There are no votes from ranked users; cannot be promoted." );

        //     // int votes_from_rank, best_eligible_rank=0;

        //     // auto potential_rank = potential_ranks.rbegin();
        //     // while (potential_rank != potential_ranks.rend() && best_eligible_rank != 1) {
            
        //     //     votes_from_rank = get_proposal_votes_from_rank(*p_itr, *potential_rank);
        //     //     print (" -- Votes from rank: ", votes_from_rank, "\n");

        //     //     if (best_eligible_rank == 0) {
        //     //         best_eligible_rank = std::max(  *potential_rank - votes_from_rank, 1);
        //     //     } else {
        //     //         best_eligible_rank = std::max(  std::min (  best_eligible_rank, 
        //     //                                         *potential_rank - votes_from_rank), 1);
        //     //     }
                
        //     //     print (" -- Best eligible rank: ", best_eligible_rank, "\n ");
        //     //     potential_rank++;
        //     // }

        //     // print ("\nCurrent rank: ", p_itr->rank, "\n");

        //     // if (p_itr->rank == 0 || best_eligible_rank < p_itr->rank) {
        //     //     print ("\n\n *** Promoting proposal: ", best_eligible_rank, "\n\n");
        //     //     p_t.modify (p_itr, get_self(), [&](auto &p) {
        //     //         p.rank = best_eligible_rank;
        //     //     });
        //     // } else { 
        //     //     eosio::check (false, "Proposal does not have the votes to be promoted.");
        //     // }
        // }


};

#endif