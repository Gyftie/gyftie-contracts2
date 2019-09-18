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
            uint64_t                proposal_id;
            string                  proposal_name           ;
            name                    proposer;
            uint64_t                rank                    = 0;
            string                  notes;
            vector<name>            voters_for;
            uint32_t                votes_for;
            vector<name>            voters_against;
            uint32_t                votes_against;
            std::vector<char>       packed_transaction;

            time_point_sec          expiration_date         ;
            time_point_sec          created_date            = time_point_sec(current_time_point());
            time_point_sec          updated_date            = time_point_sec(current_time_point());

            uint64_t            primary_key () const { return proposal_id; }
            uint64_t            by_proposer () const { return proposer.value; }
            uint64_t            by_rank () const { return rank; }
            uint64_t            by_created () const { return created_date.sec_since_epoch(); }
            uint64_t            by_updated () const { return updated_date.sec_since_epoch(); }
            uint64_t            by_expiration () const { return expiration_date.sec_since_epoch(); }
        };

        typedef eosio::multi_index<"proposals"_n, Proposal,
            indexed_by<"byrank"_n,
                const_mem_fun<Proposal, uint64_t, &Proposal::by_rank>>,
            indexed_by<"byproposer"_n,
                const_mem_fun<Proposal, uint64_t, &Proposal::by_proposer>>,
            indexed_by<"bycreated"_n,
                const_mem_fun<Proposal, uint64_t, &Proposal::by_created>>,
            indexed_by<"byupdated"_n,
                const_mem_fun<Proposal, uint64_t, &Proposal::by_updated>>,
            indexed_by<"byexpire"_n,
                const_mem_fun<Proposal, uint64_t, &Proposal::by_expiration>>
        > proposal_table;

        struct [[ eosio::table, eosio::contract("gyftietoken") ]] OldProposal
        {
            uint64_t        proposal_id;
            uint32_t        created_date;
            name            proposer;
            name            new_token_gen;
            string          notes;
            vector<name>    voters_for;
            uint32_t        votes_for;
            vector<name>    voters_against;
            uint32_t        votes_against;
            uint32_t        expiration_date;

            uint64_t        primary_key() const { return proposal_id; }
        };

        typedef eosio::multi_index<"oldprops"_n, OldProposal> old_proposal_table;

        name                contract;
        proposal_table      proposal_t;
        ProfileClass        profileClass;
           
        ProposalClass (const name& contract) : 
            proposal_t (contract, contract.value), 
            profileClass (contract),
            contract (contract) {}

        void create (const name& proposer, const string& proposal_name, const string& notes) 
        {
            Permit::permit (contract, proposer, name{0}, common::PROPOSE);

            proposal_t.emplace (proposer, [&](auto &p) {
                p.proposal_id       = proposal_t.available_primary_key();
                p.proposer          = proposer;
                p.proposal_name     = proposal_name;
                p.notes             = notes;
                p.votes_for         = 1;
                p.voters_for.push_back(proposer);
                p.votes_against     = 0;
                // p.expiration_date   = time_point_sec(current_time_point().sec_since_epoch() + (60 * 60 * 24 * 30));  // 30 days
            });
        }

        void remove (const uint64_t& proposal_id) 
        {
            auto p_itr = proposal_t.find (proposal_id);
            eosio::check (p_itr != proposal_t.end(), "Proposal ID is not found: " + std::to_string(proposal_id));

            Permit::permit (contract, p_itr->proposer, name{0}, common::REMOVE_PROPOSAL);

            proposal_t.erase (p_itr);
        }

        void propose_trx (  const name& proposer,
                            const string& proposal_name, 
                            const string& notes, 
                            const std::vector<char> pkd_trx) 
        {            
            Permit::permit (contract, proposer, name{0}, common::AUTH_ACTIVITY);

            proposal_t.emplace( proposer, [&]( auto& prop ) {
                prop.proposal_id        = proposal_t.available_primary_key();
                prop.proposer           = proposer;
                prop.notes              = notes;
                prop.proposal_name      = proposal_name;
                prop.packed_transaction = pkd_trx;
            });
        }

        void exec( const uint64_t& proposal_id, const name& executer ) {
            Permit::permit (contract, executer, name{0}, common::AUTH_ACTIVITY);

            auto& prop = proposal_t.get( proposal_id, "proposal not found" );

            // Open for at least 24 hours
            // check (current_time_point().sec_since_epoch() > prop.created_date.sec_since_epoch() + (60 * 60 * 24), 
            //     "Proposal must be open for 24 hours before it can be executed");

            // Over 80% of voters approve
            check (prop.votes_against * 4 <= prop.votes_for, "Proposal must have 80% positive votes to pass. Votes for: " +
                std::to_string(prop.votes_for) + "; Votes against: " + std::to_string(prop.votes_against));

            // Over 60% of Tier 0 Signatories
            uint64_t rank_zero_votes_for = 0;
            uint64_t rank_zero_votes_against = 0;
            vector<name> voters_for = prop.voters_for;
            for (auto voter : voters_for) {
                if (profileClass.profile2_t.get(voter.value).rank == 0) {
                    rank_zero_votes_for++;
                }
            }

            uint64_t rank_zero_count = profileClass.get_rank_profile_count (0);
            print (" Rank zero count: ", std::to_string(rank_zero_count), "\n");
            float rank_zero_voter_margin = (float) rank_zero_votes_for / (float) (rank_zero_count);

            check (rank_zero_voter_margin >= 0.6000000000000, "Rank zero voter margin must be greater than 60% to pass. Rank zero votes for: " +
                std::to_string(rank_zero_votes_for) + "; Rank zero voters: " + std::to_string(rank_zero_count));
            
            transaction_header trx_header;
            datastream<const char*> ds( prop.packed_transaction.data(), prop.packed_transaction.size() );
            ds >> trx_header;
            check( trx_header.expiration >= eosio::time_point_sec(current_time_point()), "transaction expired" );

            print (" Executing transaction for proposal  : ", prop.proposal_name, "\n");
            send_deferred( current_block_time().to_time_point().sec_since_epoch() + prop.proposal_id, executer,
                            prop.packed_transaction.data(), prop.packed_transaction.size() );

            proposal_t.erase(prop);
        }

        void check_vote (const Proposal p, const name& voter) 
        {
            auto voter_for_itr = std::find (p.voters_for.begin(), p.voters_for.end(), voter);
            eosio::check (voter_for_itr == p.voters_for.end(), "User has already voted (for).");

            auto voter_against_itr = std::find (p.voters_against.begin(), p.voters_against.end(), voter);
            eosio::check (voter_against_itr == p.voters_against.end(), "User has already voted (against).");

            // eosio::check (time_point_sec(current_time_point()) <= p.expiration_date, "Proposal has expired.");
        }

        void vote_for (const name& voter, const uint64_t& proposal_id) 
        {
            Permit::permit (contract, voter, name{0}, common::AUTH_ACTIVITY);
            
            auto p_itr = proposal_t.find (proposal_id);
            check (p_itr != proposal_t.end(), "Proposal ID does not exist: " + std::to_string(proposal_id));
            check_vote (*p_itr, voter);

            proposal_t.modify (p_itr, contract, [&](auto &p) {
                p.votes_for++;
                p.voters_for.push_back (voter);
            });
        }

        void vote_against (const name& voter, const uint64_t& proposal_id) 
        {
            Permit::permit (contract, voter, name{0}, common::AUTH_ACTIVITY);

            auto p_itr = proposal_t.find (proposal_id);
            check (p_itr != proposal_t.end(), "Proposal ID does not exist: " + std::to_string(proposal_id));
            check_vote (*p_itr, voter);
            
            proposal_t.modify (p_itr, contract, [&](auto &p) {
                p.votes_against++;
                p.voters_against.push_back (voter);
            });
        }                

        void unvote_proposal (const name voter, const uint64_t proposal_id) 
        {
            Permit::permit (contract, voter, name{0}, common::AUTH_ACTIVITY);
           
            auto p_itr = proposal_t.find (proposal_id);
            check (p_itr != proposal_t.end(), "Proposal ID does not exist: " + std::to_string(proposal_id));

            bool voter_found = false;

            auto voter_for_itr = std::find (p_itr->voters_for.begin(), p_itr->voters_for.end(), voter);
            if (voter_for_itr != p_itr->voters_for.end()) {
                proposal_t.modify (p_itr, contract, [&](auto &p) {
                    p.voters_for.erase (voter_for_itr);
                    p.votes_for--;
                });
                voter_found = true;
            }

            auto voter_against_itr = std::find (p_itr->voters_against.begin(), p_itr->voters_against.end(), voter);
            if (voter_against_itr != p_itr->voters_against.end()) {
                proposal_t.modify (p_itr, contract, [&](auto &p) {
                    p.voters_against.erase (voter_against_itr);
                    p.votes_against--;
                });
                voter_found = true;
            }

            eosio::check (voter_found, "Voter has not voted for or against this proposal. Voter: " + 
                voter.to_string() + "; Proposal ID: " + std::to_string(proposal_id));
        }

        uint64_t get_proposal_votes_from_rank (const Proposal& prop, const uint64_t& rank)
        {
            uint64_t vote_count =0;
            vector<name> votes = prop.voters_for;
            for (auto voter : votes) {
                if (profileClass.profile2_t.get(voter.value).rank == rank) {
                    vote_count++;
                }
            }

            return vote_count;
        }
    
        std::set<int> get_proposal_voting_ranks (const uint64_t proposal_id)
        {
            auto p_itr = proposal_t.find (proposal_id);
            check (p_itr != proposal_t.end(), "Proposal to promote is not found: " + std::to_string(proposal_id));

            vector<name> votes = p_itr->voters_for;
            std::set<int> rank_set;
            for (auto voter : votes) {
                if (profileClass.profile2_t.get(voter.value).rank > 0) {
                    rank_set.insert (profileClass.profile2_t.get(voter.value).rank);
                }
            }
            return rank_set;
        }

        void promoteprop (const uint64_t proposal_id) 
        {
            auto p_itr = proposal_t.find (proposal_id);
            check (p_itr != proposal_t.end(), "Proposal ID to promote is not found.");
            check (p_itr->rank != 1, "Proposal rank is at highest level; cannot be promoted.");
            check (p_itr->voters_for.size() > 0, "There are no votes to promote this proposal.");

            std::set<int> potential_ranks = get_proposal_voting_ranks (proposal_id);
            check(potential_ranks.size() > 0, "There are no votes from ranked users; cannot be promoted." );

            int votes_from_rank, best_eligible_rank=0;

            auto potential_rank = potential_ranks.rbegin();
            while (potential_rank != potential_ranks.rend() && best_eligible_rank != 1) {
            
                votes_from_rank = get_proposal_votes_from_rank(*p_itr, *potential_rank);
                print (" -- Votes from rank: ", votes_from_rank, "\n");

                if (best_eligible_rank == 0) {
                    best_eligible_rank = std::max(  *potential_rank - votes_from_rank, 1);
                } else {
                    best_eligible_rank = std::max(  std::min (  best_eligible_rank, 
                                                    *potential_rank - votes_from_rank), 1);
                }
                
                print (" -- Best eligible rank: ", best_eligible_rank, "\n ");
                potential_rank++;
            }

            print ("\nCurrent rank: ", p_itr->rank, "\n");

            if (p_itr->rank == 0 || best_eligible_rank < p_itr->rank) {
                print ("\n\n *** Promoting proposal: ", best_eligible_rank, "\n\n");
                proposal_t.modify (p_itr, contract, [&](auto &p) {
                    p.rank = best_eligible_rank;
                });
            } else { 
                eosio::check (false, "Proposal does not have the votes to be promoted.");
            }
        }
};

#endif