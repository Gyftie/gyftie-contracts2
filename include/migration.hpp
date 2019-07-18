#ifndef MIGRATION_H
#define MIGRATION_H

#include <iterator>
#include <eosio/eosio.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/asset.hpp>

#include "common.hpp"
#include "gyftie.hpp"
#include "profile.hpp"

using std::string;
using std::vector;
using std::iterator;
using namespace eosio;

class Migration {

    public:
        struct [[ eosio::table, eosio::contract("gyftietoken") ]] tprofile
        {
            name        account;
            string      idhash;
            string      id_expiration;
            asset       gft_balance;
            asset       staked_balance;
            asset       unstaking_balance;
            uint64_t    primary_key() const { return account.value; }
        };
        typedef eosio::multi_index<"tprofiles"_n, tprofile> tprofile_table;

        ProfileClass    profileClass;
        GyftieClass     gyftieClass;
        name            contract;
        tprofile_table  tprofile_t;

        Migration (const name& contract)
            : profileClass (contract),
                gyftieClass (contract),
                contract (contract),
                tprofile_t (contract, contract.value) {} 

        void removetprofs (const name account) 
        {
            // eosio::check (  has_auth (get_self()) || 
            //         has_auth ("gftma.x"_n),    
            //     "Permission denied");
                
            // tprofile_table tp_t (get_self(), get_self().value);
            // auto tp_itr = tp_t.find (account.value);
            // eosio::check (tp_itr != tp_t.end(), "Account not found");

            // int counter = 0;
            // while (tp_itr != tp_t.end() && counter <= 25) {
            //     tp_itr = tp_t.erase (tp_itr);
            //     counter++;
            // }

            // if (tp_itr != tp_t.end()) {
            //     eosio::transaction out{};
            //     out.actions.emplace_back(permission_level{get_self(), "owner"_n}, 
            //                             get_self(), "removetprofs"_n, 
            //                             std::make_tuple(tp_itr->account));
            //     out.delay_sec = 1;
            //     out.send(get_next_sender_id(), get_self());    
            // }
        }

        void backupprofs (const name& profile) {
            uint32_t prof_count = 0;

            auto p_itr = profileClass.profile_t.find (profile.value);
            check (p_itr != profileClass.profile_t.end(), "Profile record for account not found: " + profile.to_string());

            while (p_itr != profileClass.profile_t.end() && prof_count < 10) {
                copy_to_temp (p_itr->account);
                prof_count++;
                p_itr = profileClass.profile_t.erase (p_itr);
            }

            if (p_itr != profileClass.profile_t.end()) {
                eosio::transaction out{};
                out.actions.emplace_back(permission_level{contract, "owner"_n}, 
                                        contract, "backupprofs"_n, 
                                        std::make_tuple(p_itr->account));
                out.delay_sec = 1;
                out.send(gyftieClass.get_next_sender_id(), contract);    
            }
        }

        void restoreprofs (const name& profile) {
            uint32_t prof_count = 0;

            auto tp_itr = tprofile_t.find (profile.value);
            check (tp_itr != tprofile_t.end(), "Temp Profile record for account not found: " + profile.to_string());

            while (tp_itr != tprofile_t.end() && prof_count < 10) {
                copy_from_temp (tp_itr->account);
                prof_count++;
                tp_itr = tprofile_t.erase (tp_itr);
            }

            if (tp_itr != tprofile_t.end()) {
                eosio::transaction out{};
                out.actions.emplace_back(permission_level{contract, "owner"_n}, 
                                        contract, "restoreprofs"_n, 
                                        std::make_tuple(tp_itr->account));
                out.delay_sec = 1;
                out.send(gyftieClass.get_next_sender_id(), contract);    
            }
        }

        void copy_to_temp (const name& profile) {

            auto p_itr = profileClass.profile_t.find (profile.value);
            check (p_itr != profileClass.profile_t.end(), "Profile record for account not found: " + profile.to_string());

            tprofile_t.emplace (contract, [&](auto tp) {
                tp.account = p_itr->account;
                tp.idhash = p_itr->idhash;
                tp.id_expiration = p_itr->id_expiration;
                tp.gft_balance = p_itr->gft_balance;
                tp.staked_balance = p_itr->staked_balance;
                tp.unstaking_balance = p_itr->unstaking_balance;
            });
        }

        void copy_from_temp (const name& profile) {
            auto tp_itr = tprofile_t.find (profile.value);
            check (tp_itr != tprofile_t.end(), "Temp profile record from account not found: " + profile.to_string());

            profileClass.profile_t.emplace (contract, [&](auto p) {
                p.account           = tp_itr->account;
                p.idhash            = tp_itr->idhash;
                p.id_expiration     = tp_itr->id_expiration;
                p.gft_balance       = tp_itr->gft_balance;
                p.staked_balance    = tp_itr->staked_balance;
                p.unstaking_balance = tp_itr->unstaking_balance;
            });
        }
};

#endif