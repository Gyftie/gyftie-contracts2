#ifndef GYFTIE_H
#define GYFTIE_H

#include <string>

#include "common.hpp"
#include "profile.hpp"

using std::vector;
using std::string;

using namespace common;
using namespace eosio;

class GyftieClass {

   public:

      struct [[ eosio::table, eosio::contract("gyftietoken") ]] AppState 
      {
         name        gftorderbook;
         name        gyftiegyftie;
         name        gyftieoracle;
         uint8_t     paused;
         uint32_t    account_count = 0;
         uint32_t    throttle = 0;
         uint64_t    last_sender_id;
      };

      typedef singleton<"appstates"_n, AppState> appstate_table;
      typedef eosio::multi_index<"appstates"_n, AppState> appstate_table_placeholder;

      name           contract;
      appstate_table appstate_t;

      GyftieClass (const name& contract) 
               : appstate_t (contract, contract.value),
               contract (contract) {}

      void set_config (const name& gftorderbook, const name& gyftiegyftie, const name& gyftieoracle) {
         require_auth (contract);

         AppState state = appstate_t.get_or_create (contract, AppState());
         state.gftorderbook = gftorderbook;
         state.gyftiegyftie = gyftiegyftie;
         state.gyftieoracle = gyftieoracle;
         
         ProfileClass pc = ProfileClass (contract);
         if (!pc.exists (gftorderbook)) {
            pc.create (gftorderbook, "GFT Order Book Account", "NO EXPIRATION");
         }

         if (!pc.exists (gyftiegyftie)) {
            pc.create (gyftiegyftie, "Gyftie Limited Account", "NO EXPIRATION");
         }

         appstate_t.set (state, contract);
      }

      void set_account_count (const uint32_t account_count)  
      {
         require_auth (contract);

         AppState state = appstate_t.get_or_create (contract, AppState());
         state.account_count = account_count;
         appstate_t.set(state, contract);
      }

      void change_throttle (const uint32_t& throttle) {

         AppState state = appstate_t.get_or_create (contract, AppState());
         state.throttle = throttle;
         appstate_t.set(state, contract);
      }

      void setusercnt (const uint32_t& count) {

         AppState state = appstate_t.get_or_create (contract, AppState());
         state.account_count = count;
         appstate_t.set(state, contract);
      }

      AppState get_state () {
         return appstate_t.get_or_create (contract, AppState());  
      }

      void pause () {
         require_auth (contract);
         AppState state = appstate_t.get_or_create (contract, AppState());
         state.paused = PAUSED;
         return appstate_t.set(state, contract);
      }

      void unpause () {
         require_auth (contract);
         AppState state = appstate_t.get_or_create (contract, AppState());
         state.paused = UNPAUSED;
         return appstate_t.set(state, contract);
      }

      uint64_t get_next_sender_id()
      {
         AppState state = appstate_t.get_or_create (contract, AppState());

         uint64_t return_senderid = state.last_sender_id;
         return_senderid++;
         state.last_sender_id = return_senderid;
         appstate_t.set (state, contract);
         return return_senderid;
      }

      uint64_t increment_account_count() {
         AppState state = appstate_t.get_or_create (contract, AppState());
         state.account_count++;
         appstate_t.set (state, contract);
         return state.account_count;
      }

      uint64_t decrement_account_count() {
         AppState state = appstate_t.get_or_create (contract, AppState());
         state.account_count--;
         appstate_t.set (state, contract);
         return state.account_count;
      }
};

#endif