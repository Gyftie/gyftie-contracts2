#ifndef COMMON_H
#define COMMON_H

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

    static const int    ANY                         =   0;
    static const int    GYFT                        =   1;
    static const int    VOTE                        =   2;
    static const int    CHALLENGE                   =   3;
    static const int    VALIDATE                    =   4;
    static const int    PROPOSE                     =   5;
    static const int    TRANSFER                    =   6;
    static const int    REMOVE_PROPOSAL             =   7;
    static const int    ANY_SIGNATORY               =   8;
    static const int    AUTH_ACTIVITY               =   9;
    static const int    LOCK_ACTIVITY               =   10;
    static const int    ORACLE_ACTIVITY             =   11;
    static const int    SELFORSIGNATORY_ACTIVITY    =   12;
    static const int    SELLGFT_ACTIVITY            =   13;
}

#endif