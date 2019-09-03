#ifndef COMMENT_H
#define COMMENT_H

#include <eosio/eosio.hpp>

#include "permit.hpp"

using namespace eosio;
using std::string;

class CommentClass {

    public:

        struct [[eosio::table, eosio::contract("gyftietoken")]] Comment 
        {
            uint64_t        comment_id;
            name            comment_type;
            uint64_t        proposal_id;    // optional - foreign key
            name            profile;        // optional - foreign key
            name            commenter;
            uint64_t        parent_comment_id;
            string          comment_text;

            time_point_sec  created_date        = time_point_sec(current_time_point());
            time_point_sec  updated_date        = time_point_sec(current_time_point());

            uint64_t        primary_key () const { return comment_id; }
            uint64_t        by_comment_type () const { return comment_type.value; }
            uint64_t        by_commenter () const { return commenter.value; }
            uint64_t        by_parent () const { return parent_comment_id; }
            uint64_t        by_proposal () const { return proposal_id; }
            uint64_t        by_profile () const { return profile.value; }
            uint64_t        by_created () const { return created_date.sec_since_epoch(); }
            uint64_t        by_updated () const { return updated_date.sec_since_epoch(); }
        };

        typedef eosio::multi_index<"comments"_n, Comment,
            indexed_by<"bycommtype"_n, const_mem_fun<Comment, uint64_t, &Comment::by_comment_type>>,
            indexed_by<"bycommenter"_n, const_mem_fun<Comment, uint64_t, &Comment::by_commenter>>,
            indexed_by<"byparent"_n, const_mem_fun<Comment, uint64_t, &Comment::by_parent>>,
            indexed_by<"byproposal"_n, const_mem_fun<Comment, uint64_t, &Comment::by_proposal>>,
            indexed_by<"byprofile"_n, const_mem_fun<Comment, uint64_t, &Comment::by_profile>>,
            indexed_by<"bycreated"_n, const_mem_fun<Comment, uint64_t, &Comment::by_created>>,
            indexed_by<"byupdated"_n, const_mem_fun<Comment, uint64_t, &Comment::by_updated>>
        > comment_table;

        name            contract;

        CommentClass (const name& contract) :
            contract (contract) {}

        void add_comment (const name& commenter, 
                            const name& comment_type, 
                            const uint64_t& proposal_id,    // -1 for no proposal
                            const name& profile,            // "noprofile"_n for no profile
                            const uint64_t& parent_id, 
                            const string& comment_text) {
            
            Permit::permit (contract, commenter, name{0}, common::AUTH_ACTIVITY);

            comment_table c_t (contract, contract.value);
            c_t.emplace (contract, [&](auto& c) {
                c.comment_id        = c_t.available_primary_key();
                c.comment_type      = comment_type;
                c.proposal_id       = proposal_id;
                c.profile           = profile;
                c.commenter         = commenter;
                c.parent_comment_id = parent_id;
                c.comment_text      = comment_text;
            });
        }

        void remove_comment (const uint64_t& comment_id) {
            comment_table c_t (contract, contract.value);
            auto c_itr = c_t.find (comment_id);
            check (c_itr != c_t.end(), "Comment ID not found: " + std::to_string(comment_id));
            
            Permit::permit (contract, c_itr->commenter, name{0}, common::AUTH_ACTIVITY);

            c_t.modify (c_itr, contract, [&](auto &c) {
                c.comment_text  =   "This comment has been deleted";
                c.updated_date  = time_point_sec(current_time_point());
            });
        }

        void edit_comment (const uint64_t& comment_id, const string& comment_text) {
            comment_table c_t (contract, contract.value);
            auto c_itr = c_t.find (comment_id);
            check (c_itr != c_t.end(), "Comment ID not found: " + std::to_string(comment_id));
            
            Permit::permit (contract, c_itr->commenter, name{0}, common::AUTH_ACTIVITY);

            c_t.modify (c_itr, contract, [&](auto &c) {
                c.comment_text  =   comment_text;
                c.updated_date  = time_point_sec(current_time_point());
            });
        }
};

#endif