#ifndef GYFT_H
#define GYFT_H

#include <string>

#include "common.hpp"
#include "profile.hpp"
#include "gyftie.hpp"

using std::vector;
using std::string;

using namespace common;

class GyftClass {

    public:

        TABLE Gyft
        {
            uint64_t    gyft_id;
            name        gyfter;
            name        gyftee;
            asset       gyfter_issue;
            asset       gyftee_issue;
            string      relationship;
            string      notes;
            uint32_t    gyft_date;
            uint16_t    likes;
            uint64_t    primary_key() const { return gyft_id; }
            uint64_t    by_gyfter() const { return gyfter.value; }
            uint64_t    by_gyftee() const { return gyftee.value; }
            uint64_t    by_gyftdate() const { return gyft_date; }
        };

        typedef eosio::multi_index<"gyfts"_n, Gyft,
            indexed_by<"bygyfter"_n,
                const_mem_fun<Gyft, uint64_t, &Gyft::by_gyfter>>,
            indexed_by<"bygyftee"_n,
                const_mem_fun<Gyft, uint64_t, &Gyft::by_gyftee>>,
            indexed_by<"bygyftdate"_n, 
                const_mem_fun<Gyft, uint64_t, &Gyft::by_gyftdate>>
            >
        gyft_table;

        name            contract;
        gyft_table      gyft_t;
        GyftieClass     gyftieClass;

        GyftClass (const name& contract);

        auto load (const uint64_t& gyft_id);

        iterator<std::bidirectional_iterator_tag, const GyftClass::Gyft> create (const ProfileClass::Profile& gyfter, 
                    const name& gyftee, 
                    const asset& gyfter_issue,
                    const asset& gyftee_issue, 
                    const string& relationship);
        
        void throttle_check ();
};

#endif