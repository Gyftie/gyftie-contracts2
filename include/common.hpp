#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>
#include <eosio/crypto.hpp>
#include <eosio/time.hpp>
#include <eosio/system.hpp>
#include <string>
#include <algorithm> // std::find
#include <eosio/singleton.hpp>
#include <eosio/transaction.hpp>

#include <math.h>

using namespace eosio;

namespace common {

    static const symbol         S_GFT           ("GFT", 8);
    static const symbol         S_EOS           ("EOS", 4);

    static const uint64_t       SCALER          = 100000000;

    static const uint8_t        PAUSED          = 1;
    static const uint8_t        UNPAUSED        = 0;

    static const uint8_t        NEW_CHALLENGE   = 1;
    static const uint8_t        VALIDATED       = 2;

}