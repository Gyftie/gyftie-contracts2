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

      TABLE AppState 
      {
         name        gftorderbook;
         name        gyftiegyftie;
         uint8_t     paused;
         uint32_t    account_count = 0;
         uint32_t    prior_step_user_count;   

         uint64_t    pol_scaled_user_count_decay;
         uint64_t    pol_scaled_step_increase;

         uint64_t    scaled_user_count_factor=100000000;
         uint32_t    throttle = 0;
         uint64_t    last_sender_id;
      };

      typedef singleton<"appstates"_n, AppState> appstate_table;
      typedef eosio::multi_index<"appstates"_n, AppState> appstate_table_placeholder;

      name           contract;
      appstate_table appstate_t;

      GyftieClass (const name& contract) ;

      void set_config (const name& gftorderbook, const name& gyftiegyftie);
      
      void set_state (const uint32_t account_count,
                     const uint32_t prior_step_user_count,
                     const uint32_t pol_user_count_decayx100,  // 2%
                     const uint32_t pol_step_increasex100);  // 1%

      void change_throttle (const uint32_t& throttle);
      GyftieClass::AppState get_state ();
      void pause ();
      void unpause ();
      uint64_t get_next_sender_id ();
      uint64_t increment_account_count ();
      float get_usercount_factor ();

};

#endif