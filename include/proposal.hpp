#ifndef PROPOSAL_H
#define PROPOSAL_H

#include <eosio/eosio.hpp>

#include "permit.hpp"
#include "profile.hpp"

using std::vector;
using std::string;

class ProposalClass {

    public:
        
    //    struct [[ eosio::table, eosio::contract("gyftietoken") ]] Proposal
    //     {
    //         uint64_t            proposal_id;
    //         string              proposal_name           ;
    //         name                proposer;
    //         uint64_t            rank                    = 0;
    //         string              notes;
    //         vector<name>        voters_for;
    //         uint32_t            votes_for;
    //         vector<name>        voters_against;
    //         uint32_t            votes_against;
    //         std::vector<char>   packed_transaction;

    //         time_point          expiration_date       ;
    //         time_point          created_date          = current_block_time().to_time_point();
    //         time_point          updated_date          = current_block_time().to_time_point();

    //         // DEPLOY
    //         // uint64_t        rank = 0;
    //         uint64_t        primary_key () const { return proposal_id; }
    //         uint64_t        by_proposer () const { return proposer.value; }
    //         uint64_t        by_rank () const { return rank; }
    //         uint64_t        by_created () const { return created_date.sec_since_epoch(); }
    //         uint64_t        by_updated () const { return created_date.sec_since_epoch(); }
    //         uint64_t        by_expiration () const { return expiration_date.sec_since_epoch(); }

    //     };

    //     typedef eosio::multi_index<"proposals"_n, Proposal> proposal_table;



        struct [[ eosio::table, eosio::contract("gyftietoken") ]] Proposal
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

            // DEPLOY
            // uint64_t        rank = 0;
            uint64_t        primary_key() const { return proposal_id; }
            // DEPLOY
            // uint64_t        by_created()  const { return created_date; }
            // uint64_t        by_expiration() const { return expiration_date; }
        };

        typedef eosio::multi_index<"oldprops"_n, OldProposal> old_proposal_table;

        // DEPLOY

        // typedef eosio::multi_index<"proposals:"_n, Proposal,
        //     indexed_by<"bycreated"_n,
        //         const_mem_fun<Proposal, uint64_t, &Proposal::bycreated>>
        //     indexed_by<"byexpire"_n,
        //         const_mem_fun<Proposal, uint64_t, &Proposal::byexpire>>
        // > proposal_table;

        name                contract;
        proposal_table      proposal_t;
        old_proposal_table  old_proposal_t;
        ProfileClass        profileClass;

        void archive () {
            auto p_itr = proposal_t.begin();
            while (p_itr != proposal_t.end()) {
                old_proposal_t.emplace (contract, [&](auto &p) {
                    p.proposal_id       = p_itr->proposal_id;
                    p.created_date      = p_itr->created_date;
                    p.proposer          = p_itr->proposer;
                    p.new_token_gen     = p_itr->new_token_gen;
                    p.notes             = p_itr->notes;
                    p.voters_for        = p_itr->voters_for;
                    p.votes_for         = p_itr->votes_for;
                    p.voters_against    = p_itr->voters_against;
                    p.votes_against     = p_itr->votes_against;
                    p.expiration_date   = p_itr->expiration_date;
                });
                p_itr++;
            }
        }

        void clearprops () {
            auto p_itr = proposal_t.begin();
            while (p_itr != proposal_t.end()) {
                p_itr = proposal_t.erase(p_itr);
            }
        }
            
        ProposalClass (const name& contract) : 
            proposal_t (contract, contract.value), 
            old_proposal_t (contract, contract.value),
            profileClass (contract),
            contract (contract) {}

        iterator<std::bidirectional_iterator_tag, const Proposal> create (const name& proposer, const string& notes) {
            require_auth (proposer);

            Permit::permit (contract, proposer, name{0}, common::PROPOSE);

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

            Permit::permit (contract, p_itr->proposer, name{0}, common::REMOVE_PROPOSAL);

            return proposal_t.erase (p_itr);
        }

        void propose_trx (ignore<name> proposer,
                            ignore<string> proposal_name,
                            ignore<string> notes,
                            ignore<transaction> trx) {

            // name _proposer;
            // string _proposal_name;
            // string _notes;
            // transaction_header _trx_header;

            // _ds >> _proposer >> _proposal_name >> _notes;

            // const char* trx_pos = _ds.pos();
            // size_t size    = _ds.remaining();
            // _ds >> _trx_header;

            // require_auth( _proposer );
            // check( _trx_header.expiration >= eosio::time_point_sec(current_time_point()), "transaction expired" );

            // std::vector<char> pkd_trans;
            // pkd_trans.resize(size);
            // memcpy((char*)pkd_trans.data(), trx_pos, size);
            // proposal_t.emplace( _proposer, [&]( auto& prop ) {
            //     prop.proposal_id        = proposal_t.available_primary_key();
            //     prop.notes              = _notes;
            //     prop.proposal_name      = _proposal_name;
            //     // prop.packed_transaction = pkd_trans;
            // });
        }

        void exec( name proposer, uint64_t proposal_id, name executer ) {
            require_auth( executer );

            // Criteria for passing a proposal here
            // Passing criteria:
            // Open for at least 24 hours
            // Over 50% of voters approve
            // Over 50% of Tier 0 Signatories
            
            // auto& prop = proposal_t.get( proposal_id, "proposal not found" );
            // transaction_header trx_header;
            // datastream<const char*> ds( prop.packed_transaction.data(), prop.packed_transaction.size() );
            // ds >> trx_header;
            // check( trx_header.expiration >= eosio::time_point_sec(current_time_point()), "transaction expired" );

            // print (" Executing transaction for proposal  : ", prop.proposal_name, "\n");
            // send_deferred( (uint128_t(proposer.value) << 64) | proposal_name.value, executer,
            //                 prop.packed_transaction.data(), prop.packed_transaction.size() );

            // proptable.erase(prop);

        }

        void check_vote (const Proposal p, const name& voter) {
            auto voter_for_itr = std::find (p.voters_for.begin(), p.voters_for.end(), voter);
            eosio::check (voter_for_itr == p.voters_for.end(), "User has already voted (for).");

            auto voter_against_itr = std::find (p.voters_against.begin(), p.voters_against.end(), voter);
            eosio::check (voter_against_itr == p.voters_against.end(), "User has already voted (against).");

            eosio::check (current_block_time().to_time_point().sec_since_epoch() <= p.expiration_date, "Proposal has expired.");
        }

        iterator<std::bidirectional_iterator_tag, const Proposal> vote_for (const name& voter, const uint64_t& proposal_id) {
            Permit::permit (contract, voter, name{0}, common::AUTH_ACTIVITY);
            
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
            Permit::permit (contract, voter, name{0}, common::AUTH_ACTIVITY);

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