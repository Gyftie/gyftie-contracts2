#include "../../include/gyft.hpp"

GyftClass::GyftClass (const name& contract) 
    : gyft_t (contract, contract.value), 
    gyftieClass (contract),
    contract (contract) {}

auto GyftClass::load (const uint64_t&  gyft_id) {
    auto g_itr = gyft_t.find (gyft_id);
    eosio::check (g_itr != gyft_t.end(), "Gyft event is not found.");
    return *g_itr;
}

iterator<std::bidirectional_iterator_tag, const GyftClass::Gyft> GyftClass::create (const ProfileClass::Profile& gyfter, 
                        const name& gyftee, 
                        const asset& gyfter_issue,
                        const asset& gyftee_issue, 
                        const string& relationship) {
                
    return gyft_t.emplace(contract, [&](auto &g) {
        g.gyft_id       = gyft_t.available_primary_key();
        g.gyfter        = gyfter.account;
        g.gyftee        = gyftee;
        g.gyfter_issue  = gyfter_issue;
        g.gyftee_issue  = gyftee_issue;
        g.relationship  = relationship;
        g.gyft_date     = current_block_time().to_time_point().sec_since_epoch();
    });
}

void GyftClass::throttle_check () {
    uint32_t throttle = gyftieClass.get_state().throttle;
    
    if (throttle < gyftieClass.get_state().account_count && throttle > 0) {
        auto gyftdate_index = gyft_t.get_index<"bygyftdate"_n>();
        auto gyftdate_itr = gyftdate_index.rbegin();

        for (int i=0; i< throttle; i++) {
            gyftdate_itr++;
        }

        uint32_t throttled_gyfts_ago = gyftdate_itr->gyft_date;
        uint32_t throttled_time_period = 60 * 60 * 24; // 24 hours
        eosio::check (  throttled_gyfts_ago < 
                            current_block_time().to_time_point().sec_since_epoch() - 
                            throttled_time_period, 
                        "Gyfts are throttled. Please wait a few hours and try again.");
    }
}