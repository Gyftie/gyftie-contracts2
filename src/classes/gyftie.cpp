
#include "../../include/gyftie.hpp"


GyftieClass::GyftieClass (const name& contract) 
         : appstate_t (contract, contract.value),
         contract (contract) {}

void GyftieClass::set_config (const name& gftorderbook, const name& gyftiegyftie) {
    require_auth (contract);

    AppState state = appstate_t.get_or_create (contract, AppState());
    state.gftorderbook = gftorderbook;
    state.gyftiegyftie = gyftiegyftie;
    state.paused = PAUSED;
    
    ProfileClass pc = ProfileClass (contract);
    if (!pc.exists (gftorderbook)) {
        pc.create (gftorderbook, "GFT Order Book Account", "NO EXPIRATION");
    }

    if (!pc.exists (gyftiegyftie)) {
        pc.create (gyftiegyftie, "Gyftie Limited Account", "NO EXPIRATION");
    }

    appstate_t.set (state, contract);
}

void GyftieClass::set_state (const uint32_t account_count,
                        const uint32_t prior_step_user_count,
                        const uint32_t pol_user_count_decayx100,  // 2%
                        const uint32_t pol_step_increasex100)  // 1%
{
    require_auth (contract);

    AppState state = appstate_t.get_or_create (contract, AppState());
    state.account_count = account_count;
    state.prior_step_user_count = prior_step_user_count;
    state.pol_scaled_user_count_decay = pol_user_count_decayx100 * SCALER / 100;
    state.pol_scaled_step_increase = pol_step_increasex100 * SCALER / 100;
    appstate_t.set(state, contract);
}

void GyftieClass::change_throttle (const uint32_t& throttle) {

    AppState state = appstate_t.get_or_create (contract, AppState());
    state.throttle = throttle;
    appstate_t.set(state, contract);
}

GyftieClass::AppState GyftieClass::get_state () {
    return appstate_t.get_or_create (contract, AppState());  
}

void GyftieClass::pause () {
    require_auth (contract);
    AppState state = appstate_t.get_or_create (contract, AppState());
    state.paused = PAUSED;
    return appstate_t.set(state, contract);
}

void GyftieClass::unpause () {
    require_auth (contract);
    AppState state = appstate_t.get_or_create (contract, AppState());
    state.paused = UNPAUSED;
    return appstate_t.set(state, contract);
}

uint64_t GyftieClass::get_next_sender_id()
{
    AppState state = appstate_t.get_or_create (contract, AppState());

    uint64_t return_senderid = state.last_sender_id;
    return_senderid++;
    state.last_sender_id = return_senderid;
    appstate_t.set (state, contract);
    return return_senderid;
}

uint64_t GyftieClass::increment_account_count() {
    require_auth (contract);
    AppState state = appstate_t.get_or_create (contract, AppState());
    state.account_count++;
    appstate_t.set (state, contract);
    return state.account_count;
}

float GyftieClass::get_usercount_factor () {
    AppState state = appstate_t.get_or_create (contract, AppState());

    float increase_since_last_step = (float) (state.account_count - state.prior_step_user_count) / (float) state.prior_step_user_count;

    if (increase_since_last_step >= (float) state.pol_scaled_step_increase / SCALER) {
        float decay_percentage = (float) 1.00000000  - ( (float) state.pol_scaled_user_count_decay / (float) SCALER);
        state.scaled_user_count_factor *= (float) (decay_percentage);
        state.prior_step_user_count = state.account_count;
        appstate_t.set (state, contract);
    }

    return (float) state.scaled_user_count_factor / (float) SCALER;
}