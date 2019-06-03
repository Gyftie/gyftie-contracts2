#ifndef PROFILE_H
#define PROFILE_H

#include <iterator>
#include <eosio/eosio.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/asset.hpp>

#include "common.hpp"

using std::string;
using std::vector;
using std::iterator;
using namespace eosio;


class ProfileClass
{

  private:
    name contract;

  public:
    struct [[ eosio::table, eosio::contract("gyftietoken") ]] Profile
    {
      name          account;
      uint32_t      rating_sum;
      uint16_t      rating_count;
      string        idhash;
      string        id_expiration;
      asset         gft_balance;
      asset         staked_balance;
      asset         unstaking_balance;

      // DEPLOY
      vector<name>  promotion_votes;
      uint64_t      rank = 0;
      uint64_t      by_rank() const { return rank; }

      uint64_t      voter_count;
      uint64_t      scaled_sum_rating;
      uint64_t      primary_key() const { return account.value; }
    };

    typedef eosio::multi_index<"profiles"_n, Profile,
      indexed_by<"byrank"_n,
        const_mem_fun<Profile, uint64_t, &Profile::by_rank>>>
      profile_table;

    profile_table profile_t;

    ProfileClass (const name& contract);
    Profile load (const name& account);
    iterator<std::bidirectional_iterator_tag, const Profile> create (const name& account, const string& idhash, const string& id_expiration);
    bool exists (const name& account);
    void unstake (const name& account, const asset& quantity);
    void stake (const name& account, const asset& quantity);
    void setrank (const name& account, const uint64_t& rank);
};

#endif