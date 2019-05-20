#pragma once

#include "profile.hpp"
#include "gyftie.hpp"
#include "gyft.hpp"
#include "common.hpp"

using namespace eosio;

class UtilityClass {

    public:

        // ACTION gyftietoken::fixstake (const name account)
        // {
        //     eosio::check (  has_auth (get_self()) || 
        //                 has_auth ("gftma.x"_n),    
        //             "Permission denied");

        //     profile_table p_t (get_self(), get_self().value);
        //     auto p_itr = p_t.find (account.value);
        //     eosio::check (p_itr != p_t.end(), "Account not found.");

        //     p_t.modify (p_itr, get_self(), [&](auto &p){
        //         p.gft_balance += p.staked_balance;
        //         p.staked_balance = p.gft_balance * 0;
        //     });
        // }

        // ACTION gyftietoken::fixstakes (const name account)
        // {

        //     require_auth ("gftma.x"_n);

        //     profile_table p_t(get_self(), get_self().value);
        //     auto p_itr = p_t.find(account.value);
        //     eosio::check (p_itr != p_t.end(), "Account not found.");

        //     while (p_itr != p_t.end()) {
        //         if (p_itr->staked_balance.amount < 0) {
        //             eosio::transaction out{};
        //             out.actions.emplace_back(permission_level{get_self(), "owner"_n}, 
        //                 get_self(), "fixstake"_n, 
        //                 std::make_tuple(p_itr->account));
        //             out.delay_sec = 0;
        //             out.send(get_next_sender_id(), get_self());    
        //         }
        //         p_itr++;
        //     }
        // }



        // ACTION gyftietoken::copygyfts1 ()
        // {
        //     require_auth ("gftma.x"_n);
        //     gyft_table g_t (get_self(), get_self().value);
        //     auto g_itr = g_t.begin();

        //     tgyft_table tg_t (get_self(), get_self().value);
            
        //     while (g_itr != g_t.end()) {
        //         tg_t.emplace (get_self(), [&] (auto& tg) {
        //             tg.gyft_id = g_itr->gyft_id;
        //             tg.gyfter = g_itr->gyfter;
        //             tg.gyftee = g_itr->gyftee;
        //             tg.gyfter_issue = g_itr->gyfter_issue;
        //             tg.gyftee_issue = g_itr->gyftee_issue;
        //             tg.relationship = g_itr->relationship;
        //             tg.notes = g_itr->notes;
        //             tg.gyft_date = g_itr->gyft_date;
        //             tg.likes = g_itr->likes;            
        //         });
        //        g_itr++;
        //     }

        //     g_itr = g_t.begin();
        //     while (g_itr != g_t.end()) {
        //         g_itr = g_t.erase(g_itr);
        //     }
        // }

        // ACTION gyftietoken::deloriggyfts ()
        // {
        //     require_auth ("gftma.x"_n);
        //     gyft_table g_t (get_self(), get_self().value);

        //     auto g_itr = g_t.begin();
        //     while (g_itr != g_t.end()) {
        //         g_itr = g_t.erase(g_itr);
        //     }
        // }

        // ACTION gyftietoken::upperm () 
        // {
        //     permission_level ar = permission_level{"amandarachel"_n, "active"_n};
        //     permission_level df3 = permission_level{"danielflora3"_n, "active"_n};
        //     //permission_level df2 = permission_level{"danielflora2"_n, "active"_n};
        //     permission_level zj = permission_level{"gftma.x"_n, "active"_n};
            
        //     permission_level_weight ar_weight = permission_level_weight {ar, 1};
        //     permission_level_weight df3_weight = permission_level_weight {df3, 1};
        //     //permission_level_weight df2_weight = permission_level_weight {df2, 1};
        //     permission_level_weight zj_weight = permission_level_weight {zj, 1};
            
        //     vector<permission_level_weight> accounts;
            
        //     accounts.push_back (ar_weight);
        //    // accounts.push_back (df2_weight);
        //     accounts.push_back (df3_weight);
        //     accounts.push_back (zj_weight);
            
        //     authority auth = authority{2, {}, accounts, {}};

        //     auto update_auth_payload = std::make_tuple(get_self(), "active"_n, "owner"_n, auth);

        //     action(
        //         permission_level{get_self(), "owner"_n},
        //         "eosio"_n,
        //         "updateauth"_n,
        //         update_auth_payload)
        //     .send();
        // }

        // ACTION gyftietoken::copyback (const name account)
        // {
        //     eosio::check (  has_auth (get_self()) || 
        //             has_auth ("gftma.x"_n),    
        //         "Permission denied");
        //     // config_table config (get_self(), get_self().value);
        //     // Config c = config.get();

        //     profile_table p_t (get_self(), get_self().value);
        //     tprofile_table tp_t (get_self(), get_self().value); 
        //     auto tp_itr = tp_t.find (account.value);
        //     eosio::check (tp_itr != tp_t.end(), "Account not found");

        //     int counter = 0;
        //     while (tp_itr != tp_t.end() && counter <= 10) {

        //         p_t.emplace (get_self(), [&](auto &p) {
        //             p.account = tp_itr->account;
        //             p.gft_balance = tp_itr->gft_balance;
        //             p.staked_balance = tp_itr->staked_balance;
        //             p.id_expiration = tp_itr->id_expiration;
        //             p.idhash = tp_itr->idhash;
        //             // DEPLOY
        //             p.unstaking_balance = asset {0, symbol{symbol_code(GYFTIE_SYM_STR.c_str()), GYFTIE_PRECISION}};
        //         });
        //         counter++;
        //         tp_itr++;
        //     }

        //     if (tp_itr != tp_t.end()) {
        //         eosio::transaction out{};
        //         out.actions.emplace_back(permission_level{get_self(), "owner"_n}, 
        //                                 get_self(), "copyback"_n, 
        //                                 std::make_tuple(tp_itr->account));
        //         out.delay_sec = 0;
        //         out.send(get_next_sender_id(), get_self());    
        //     }
        // }


        // ACTION gyftietoken::copyprofs (const name account)
        // {
        //     eosio::check (  has_auth (get_self()) || 
        //             has_auth ("gftma.x"_n),    
        //         "Permission denied");

        //     profile_table p_t (get_self(), get_self().value);
        //     auto p_itr = p_t.find (account.value);
        //     eosio::check (p_itr != p_t.end(), "Account not found");

        //     tprofile_table tp_t (get_self(), get_self().value); 

        //     int counter = 0;
        //     while (p_itr != p_t.end() && counter <= 10) {

        //         tp_t.emplace (get_self(), [&](auto &t) {
        //             t.account = p_itr->account;
        //             t.gft_balance = p_itr->gft_balance;
        //             t.staked_balance = p_itr->staked_balance;
        //             t.id_expiration = p_itr->id_expiration;
        //             t.idhash = p_itr->idhash;
        //         });
        //         counter++;
        //         p_itr++;
        //     }

        //     if (p_itr != p_t.end()) {
        //         eosio::transaction out{};
        //         out.actions.emplace_back(permission_level{get_self(), "owner"_n}, 
        //                                 get_self(), "copyprofs"_n, 
        //                                 std::make_tuple(p_itr->account));
        //         out.delay_sec = 1;
        //         out.send(get_next_sender_id(), get_self());    
        //     }

            // tprofile_table tp_t (get_self(), get_self().value); 
            // tp_t.emplace (get_self(), [&](auto &t) {
            //     t.account = c.gftorderbook;
            //     t.gft_balance = a_itr->balance;
            //     t.idhash = "GFT Order Book Account";
            // });

            // a_t = accounts (get_self(), c.gyftie_foundation.value);
            // a_itr = a_t.find (gft_symbol.code().raw());

            // tp_t.emplace (get_self(), [&](auto &t) {
            //     t.account = c.gyftie_foundation;
            //     t.gft_balance = a_itr->balance;
            //     t.idhash = "Gyftie Limited Account";
            // });

            // auto p_itr = p_t.begin();
            // while (p_itr != p_t.end()) {
            //     if (p_itr->account == c.gftorderbook || p_itr->account == c.gyftie_foundation) {

            //     } else {
            //         a_t = accounts (get_self(), p_itr->account.value);
            //         a_itr = a_t.find (gft_symbol.code().raw());

            //         tp_t.emplace (get_self(), [&](auto& t) {
            //             t.account = p_itr->account;
            //             t.rating_sum = p_itr->rating_sum;
            //             t.rating_count = p_itr->rating_count;
            //             t.idhash = p_itr->idhash;
            //             t.id_expiration = p_itr->id_expiration;
            //             t.gft_balance = a_itr->balance;
            //         });
            //     }
                
            //     p_itr++;
            // }
        // }

        // ACTION gyftietoken::sigupdate ()
        // {
        //     require_auth (get_self());
            
        //     // symbol sym = symbol{symbol_code(GYFTIE_SYM_STR.c_str()), GYFTIE_PRECISION};
        //     // asset josh {76902248, sym };
        //     // asset vicky {75364208, sym};
        //     // asset scott {73856928, sym};

        //     // unstake ("joshjohnpott"_n, josh);
        //     // unstake ("vickiepotter"_n, vicky);
        //     // unstake ("scottlazerso"_n, scott);

        //     xfer_account ("joshjohnpott"_n, "joshuapotter"_n);
        //     xfer_account ("vickiepotter"_n, "vicdonpotter"_n);
        //     xfer_account ("scottlazerso"_n, "slazersonfam"_n);

        // }


        // ACTION gyftietoken::ungyft(const name account)
        // {
        //     require_auth (get_self());

        //     gyft_table g_t (get_self(), get_self().value);
        //     // auto gyftee_index = g_t.get_index<"bygyftee"_n>();
        //     // auto gyftee_itr = gyftee_index.find (account.value);
        //     // eosio::check (gyftee_itr != gyftee_index.end(), "Gyft event not found for account.");

        //     // auto gyfter_index = g_t.get_index<"bygyfter"_n>();
        //     // auto gyfter_itr = gyfter_index.find (account.value);
        //     // eosio::check (gyfter_itr == gyfter_index.end(), "Account issued a gyft; must ungyft downstream accounts first.");

        //     auto g_itr = g_t.begin();
        //     while (g_itr != g_t.end()) {
        //         eosio::check (g_itr->gyfter != account, "Account issued a gyft; must ungyft downstream accounts first.");
        //         g_itr++;
        //     }

        //     bool found = false;
        //     g_itr = g_t.begin();
        //     while (g_itr != g_t.end() and !found) {
        //         if (g_itr->gyftee == account) {
        //             found = true;
        //         } else {
        //             g_itr++;
        //         }
        //     }

        //     // burn tokens for gyfter, gyftee, and gyftiegyftie
        //     burn (account, g_itr->gyftee_issue);
        //     burn (g_itr->gyfter, g_itr->gyfter_issue);

        //     config_table config (get_self(), get_self().value);
        //     auto c = config.get();
        //     burn (c.gyftie_foundation, g_itr->gyftee_issue + g_itr->gyfter_issue);

        //     profile_table p_t (get_self(), get_self().value);
        //     auto p_itr = p_t.find (account.value);
        //     eosio::check (p_itr != p_t.end(), "Account profile is not found.");
        //     p_t.erase (p_itr);

        //     accounts a_t(get_self(), account.value);
        //     auto a_itr = a_t.find(g_itr->gyftee_issue.symbol.code().raw());
        //     eosio::check (a_itr != a_t.end(), "Gyftee not found in accounts table under GFT symbol.");
        //     a_t.erase (a_itr);

        //     g_t.erase (g_itr);
        // }

            // void remove_profile (const name account)
        // {
        //     profile_table p_t (get_self(), get_self().value);
        //     auto p_itr = p_t.find (account.value);
        //     eosio::check (p_itr != p_t.end(), "Profile to remove cannot be found.");
        //     eosio::check (p_itr->gft_balance.amount <= 0, "Profile has a positive GFT balance. Cannot remove.");
        //     eosio::check (p_itr->staked_balance.amount <= 0, "Profile has a positive staked GFT balance. Cannot remove.");

        //     p_t.erase (p_itr);

        //     symbol sym = symbol{symbol_code(GYFTIE_SYM_STR.c_str()), GYFTIE_PRECISION};

        //     accounts a_t (get_self(), account.value);
        //     auto a_itr = a_t.find(sym.code().raw());
        //     if (a_itr != a_t.end()) {
        //         eosio::check (a_itr->balance.amount <= 0, "Accounts table does not have a zero balance for account. Cannot remove.");
        //         a_t.erase (a_itr);
        //     }
        // }

           // void xfer_account (const name old_account, const name new_account)
        // {
        //     profile_table p_t (get_self(), get_self().value);
        //     auto old_profile_itr = p_t.find (old_account.value);
        //     eosio::check (old_profile_itr != p_t.end(), "Profile to remove cannot be found.");
        //     eosio::check (old_profile_itr->staked_balance.amount <= 0, "Profile has staked GFT. Cannot transfer.");
            
        //     auto new_profile_itr = p_t.find (new_account.value);
        //     eosio::check (new_profile_itr != p_t.end(), "Profile of new account cannot be found.");
            
        //     config_table config(get_self(), get_self().value);
        //     auto c = config.get();

        //     symbol sym = symbol{symbol_code(GYFTIE_SYM_STR.c_str()), GYFTIE_PRECISION};
        //     balance_table b_t(c.gftorderbook, old_account.value);
        //     auto b_itr = b_t.find(sym.code().raw());
        //     if (b_itr != b_t.end() && b_itr->token_contract == get_self())
        //     {
        //         eosio::check (true, "Profile to remove has open orders or a committed balance. Delete orders and/or withdraw funds.");
        //     }

        //     string s { "Transfer from account via Gyftie signatories"};
        //     transfer (old_account, new_account, old_profile_itr->gft_balance, s);

        //     p_t.erase (old_profile_itr);
        // }

}