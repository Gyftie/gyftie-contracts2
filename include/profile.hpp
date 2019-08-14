#ifndef PROFILE_H
#define PROFILE_H

#include <iterator>
#include <eosio/eosio.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/asset.hpp>

#include "common.hpp"
// #include "gyftie.hpp"

using std::string;
using std::vector;
using std::map;
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

      uint64_t      primary_key() const { return account.value; }
    };

    struct [[ eosio::table, eosio::contract("gyftietoken") ]] Profile2
    {
      name              account;
      string            idhash;
      string            id_expiration;
      string            info_url;
      asset             gft_balance         = asset {0, common::S_GFT};
      asset             staked_balance      = asset {0, common::S_GFT};
      asset             unstaking_balance   = asset {0, common::S_GFT};
      asset             net_purchases       = asset {0, common::S_GFT};

      vector<name>      promotion_votes_for_this_profile;
      vector<name>      profiles_this_profile_voted_for;
      uint64_t          rank = 0;

      map<name, string> attribute_pairs;

      time_point        created_date        = current_block_time().to_time_point();
      time_point        updated_date        = current_block_time().to_time_point();

      uint64_t          by_rank() const { return rank; }
      uint64_t          by_balance() const { return gft_balance.amount + 
                                                    staked_balance.amount + 
                                                    unstaking_balance.amount; }

      uint64_t          by_created () const { return created_date.sec_since_epoch(); }
      uint64_t          by_updated () const { return created_date.sec_since_epoch(); }
      uint64_t          by_netpurchases () const { return net_purchases.amount; }
      uint64_t          primary_key() const { return account.value; }
    };
    
    typedef eosio::multi_index<"profiles2"_n, Profile2,
      indexed_by<"byrank"_n,
        const_mem_fun<Profile2, uint64_t, &Profile2::by_rank>>,
      indexed_by<"bybalance"_n,
        const_mem_fun<Profile2, uint64_t, &Profile2::by_balance>>,
      indexed_by<"bycreated"_n,
        const_mem_fun<Profile2, uint64_t, &Profile2::by_created>>,
      indexed_by<"byupdated"_n,
        const_mem_fun<Profile2, uint64_t, &Profile2::by_updated>>,
      indexed_by<"bynetpur"_n,
        const_mem_fun<Profile2, uint64_t, &Profile2::by_netpurchases>>
    > profile2_table;

    struct [[ eosio::table, eosio::contract("gyftietoken") ]] Verify
    {
      uint64_t      verify_id;
      name          verifier;
      name          verified;
      uint32_t      verification_date;
      uint64_t      primary_key() const { return verify_id; }
      uint64_t      by_verifier() const { return verifier.value; }
      uint64_t      by_verified() const { return verified.value; }
    };

    typedef eosio::multi_index<"verifies"_n, Verify, 
      indexed_by<"byverifier"_n,
        const_mem_fun<Verify, uint64_t, &Verify::by_verifier>>,
      indexed_by<"byverified"_n,
        const_mem_fun<Verify, uint64_t, &Verify::by_verified>>
      > verify_table;

    typedef eosio::multi_index<"profiles"_n, Profile> profile_table;

    struct [[ eosio::table, eosio::contract("gyftietoken") ]] Referral
    {
      name          referred;
      name          referrer;
      uint64_t      primary_key() const { return referred.value; }
      uint64_t      by_referrer() const { return referrer.value; }
    };

    typedef eosio::multi_index<"referrals"_n, Referral, 
      indexed_by<"byreferrer"_n, 
        const_mem_fun<Referral, uint64_t, &Referral::by_referrer>>
      > referral_table;

    profile_table profile_t;
    profile2_table profile2_t;
    verify_table  verify_t;
    referral_table referral_t;

    ProfileClass (const name& contract) 
    : profile_t (contract, contract.value), 
      profile2_t (contract, contract.value),
      verify_t (contract, contract.value), 
      referral_t (contract, contract.value),
      contract (contract) {}

    iterator<std::bidirectional_iterator_tag, const ProfileClass::Profile2> 
    create (const name& account) {
      check (profile_t.find (account.value) == profile_t.end(), "Account " + 
          account.to_string() + " already has a Gyftie profile - table 1.");

      check (profile2_t.find (account.value) == profile2_t.end(), "Account " + 
          account.to_string() + " already has a Gyftie profile - table 2.");

      return profile2_t.emplace (contract, [&](auto &p) {
          p.account = account;
          p.gft_balance = asset {0, common::S_GFT};
          p.unstaking_balance = asset {0, common::S_GFT};
          p.staked_balance = asset {0, common::S_GFT};
      });         
    }

    iterator<std::bidirectional_iterator_tag, const ProfileClass::Profile2> 
    create (const name& account, const string& idhash, const string& id_expiration) {
      check (profile_t.find (account.value) == profile_t.end(), "Account " + 
          account.to_string() + " already has a Gyftie profile - table 1.");

      check (profile2_t.find (account.value) == profile2_t.end(), "Account " + 
          account.to_string() + " already has a Gyftie profile - table 2.");

      return profile2_t.emplace (contract, [&](auto &p) {
          p.account = account;
          p.idhash = idhash;
          p.id_expiration = id_expiration;
          p.gft_balance = asset {0, common::S_GFT};
          p.unstaking_balance = asset {0, common::S_GFT};
          p.staked_balance = asset {0, common::S_GFT};
      });         
    }

    void upgrade (const name& account) {
      bool checker = existsInV1 (account);
      print ("Exists in V1: ", std::to_string(checker), "\n");
      if (existsInV1(account)) {
        auto p_itr = profile_t.find (account.value);
        check (p_itr != profile_t.end(), "Upgrade failed. Profile for " + account.to_string() + " not found in profile - table 1.");

        print ("Adding " + account.to_string() + " to profile table 2.\n");
        profile2_t.emplace (contract, [&](auto &p) {
          p.account = account;
          p.idhash = p_itr->idhash;
          p.id_expiration = p_itr->id_expiration;
          p.gft_balance = p_itr->gft_balance;
          p.unstaking_balance = p_itr->unstaking_balance;
          p.staked_balance = p_itr->staked_balance;
        });         

        print ("Erasing record from profile table 1.");
        profile_t.erase (p_itr);
      }
    }

    void buying_gft (const name& account, const asset& amount) {
      if (existsInV2(account)) {
        auto p_itr = profile2_t.find (account.value);
        profile2_t.modify (p_itr, contract, [&](auto &p) {
          p.net_purchases += amount;
        }); 
      }

      string memo = string ("Buying GFT for the first time: " + amount.to_string());
      action (
        permission_level{contract, "owner"_n},
        contract, "issueidemp"_n,
        std::make_tuple(account, "buygft"_n, memo))
      .send();
    }

    void selling_gft (const name& account, const asset& amount) {
      if (existsInV2(account)) {
        auto p_itr = profile2_t.find (account.value);

        if (! ( account == "danielflora4"_n ||
                account == "gftma.x"_n ||
                account == "gyftiegyftie"_n ||
                account == "danielflora3"_n ||
                account == "zombiejigsaw"_n )) {
                  
          check (p_itr->net_purchases >= amount, "Account " + account.to_string() + 
            " cannot sell. Selling amount must be less than net purchases. Net purchases: " +
            p_itr->net_purchases.to_string() + "; Attempted selling amount: " + amount.to_string());
        }

        profile2_t.modify (p_itr, contract, [&](auto &p) {
          p.net_purchases -= amount;
        }); 
      }
    }

    bool isIDHashMatch (const name& account, const string& idhash) {
      if (existsInV2(account)) {
        auto p_itr = profile2_t.find (account.value);
        return p_itr->idhash.compare(idhash) == 0;
      } else if (existsInV1(account)) {
        auto p_itr = profile_t.find (account.value);
        return p_itr->idhash.compare(idhash) == 0;
      } else {
        check (false, "Cannot check idhash. Profile " + account.to_string() + " does not exist in either profile 1 or 2.");
      }
      return false;
    }

    bool existsInV1 (const name& account) {
      return profile_t.find (account.value) != profile_t.end();
    }

    bool existsInV2 (const name& account) {
      auto p_itr = profile2_t.find (account.value);
      if (p_itr == profile2_t.end()) {
        print (" User " + account.to_string() + " not found in profile table 2.");
        return false;
      }
      return true;
      // return profile2_t.find (account.value) != profile2_t.end();
    }

    bool exists (const name& account) {
      return existsInV1 (account) || existsInV2 (account);
    }

    void setidhash (const name& account, const string& idhash, const string& id_expiration) {

      if (existsInV2(account)) {
        auto p_itr = profile2_t.find (account.value);
        profile2_t.modify (p_itr, contract, [&](auto &p) {
          p.idhash = idhash;
          p.id_expiration = id_expiration;
        }); 
      } else if (existsInV1(account)) {
        auto p_itr = profile_t.find (account.value);
        profile_t.modify (p_itr, contract, [&](auto &p) {
          p.idhash = idhash;
          p.id_expiration = id_expiration;
        }); 
      } else {
        check (false, "Cannot set idhash. Profile " + account.to_string() + " does not exist in either profile 1 or 2.");
      }
    }
  
    void verifyuser (const name& verifier, const name& account_to_verify) {
      auto v_itr = verify_t.find (verifier.value);
      bool already_verified = false;
      while (v_itr != verify_t.end()) {
        check (v_itr->verified == account_to_verify, "Verifier has already verififed user. Verifier: " +
          verifier.to_string() + "; Account being verfied: " + account_to_verify.to_string());
          v_itr++;
      }

      verify_t.emplace (contract, [&](auto &v) {
        v.verifier = verifier;
        v.verified = account_to_verify;
        v.verification_date = current_block_time().to_time_point().sec_since_epoch();
      });
    }

    name get_referrer (const name& referred) {
      auto r_itr = referral_t.find (referred.value);
      if (r_itr == referral_t.end()) {
        return name{0};
      }
      else { 
        return r_itr->referrer;
      }
    }

    void referred (const name& referrer, const name& account_to_refer) {
      auto r_itr = referral_t.find (account_to_refer.value);
      check (r_itr == referral_t.end(), "Account has already been referred: " + account_to_refer.to_string());
      
      referral_t.emplace (contract, [&](auto &r) {
        r.referred = account_to_refer;
        r.referrer = referrer;
      });
    }

    void accelunstake (const name& account) {
     
      if (existsInV2(account)) {
        auto p_itr = profile2_t.find (account.value);
        profile2_t.modify (p_itr, contract, [&](auto &p) {
          p.gft_balance += p_itr->unstaking_balance + p_itr->staked_balance;
          p.unstaking_balance *= 0;
          p.staked_balance *= 0;
        });
      } else if (existsInV1(account)) {
        auto p_itr = profile_t.find (account.value); 
        profile_t.modify (p_itr, contract, [&](auto &p) {
          p.gft_balance += p_itr->unstaking_balance + p_itr->staked_balance;
          p.unstaking_balance *= 0;
          p.staked_balance *= 0;
        });
      } else {
        check (false, "Cannot accelunstake. Profile " + account.to_string() + " does not exist in either profile 1 or 2.");
      }
    }

    void unstake (const name& account, const asset& quantity) {

      if (existsInV2(account)) {
        auto p_itr = profile2_t.find (account.value);
        check (p_itr->unstaking_balance >= quantity, "Unstaking balance is less than requested.");
        profile2_t.modify (p_itr, contract, [&](auto &p) {
          p.gft_balance += p_itr->unstaking_balance + p_itr->staked_balance;
          p.unstaking_balance *= 0;
          p.staked_balance *= 0;
        });
      } else if (existsInV1(account)) {
        auto p_itr = profile_t.find (account.value); 
        check (p_itr->unstaking_balance >= quantity, "Unstaking balance is less than requested.");
        profile_t.modify (p_itr, contract, [&](auto &p) {
          p.gft_balance += p_itr->unstaking_balance + p_itr->staked_balance;
          p.unstaking_balance *= 0;
          p.staked_balance *= 0;
        });
      } else {
        check (false, "Cannot unstake. Profile " + account.to_string() + " does not exist in either profile 1 or 2.");
      }
    }

    void stake (const name& account, const asset& quantity) {
      
      if (existsInV2(account)) {
        auto p_itr = profile2_t.find (account.value);
        check (p_itr->gft_balance >= quantity, "Liquid balance is less than quantity unstaking.");
        profile2_t.modify (p_itr, contract, [&](auto &p) {
          p.gft_balance -= quantity;
          p.staked_balance += quantity;
        });
      } else if (existsInV1(account)) {
        auto p_itr = profile_t.find (account.value); 
        check (p_itr->gft_balance >= quantity, "Liquid balance is less than quantity unstaking.");
        profile_t.modify (p_itr, contract, [&](auto &p) {
          p.gft_balance -= quantity;
          p.staked_balance += quantity;
        });
      } else {
        check (false, "Cannot stake. Profile " + account.to_string() + " does not exist in either profile 1 or 2.");
      }
    }

    void removeprof (const name& account) {
      if (existsInV1(account)) {
        auto p_itr = profile_t.require_find (account.value);
        profile_t.erase (p_itr);
      } else if (existsInV2(account)) {
        auto p_itr = profile2_t.require_find (account.value);
        profile2_t.erase (p_itr);
      }

      auto verified_index = verify_t.get_index<"byverified"_n>();
      auto v_itr = verified_index.lower_bound (account.value);
      while (v_itr->verified == account && v_itr != verified_index.end()) {
        v_itr = verified_index.erase (v_itr);
      }

      auto verifier_index = verify_t.get_index<"byverifier"_n>();
      auto v_itr2 = verifier_index.lower_bound (account.value);
      while (v_itr2->verifier == account && v_itr2 != verifier_index.end()) {
        v_itr2 = verifier_index.erase (v_itr2);
      }

      auto r_itr = referral_t.find (account.value);
      if (r_itr != referral_t.end()) {
        referral_t.erase (r_itr);
      }

      auto referrer_index = referral_t.get_index<"byreferrer"_n>();
      auto r_itr2 = referrer_index.find (account.value);
      while (r_itr2->referrer == account && r_itr2 != referrer_index.end()) {
        r_itr2 = referrer_index.erase (r_itr2);
      } 
    }

    // only for testing
    void removeAllV2 () {
      auto p_itr = profile2_t.begin();
      while (p_itr != profile2_t.end()) {
        p_itr = profile2_t.erase (p_itr);
      }
    }

    // void setrank (const name& account, const uint64_t& rank) 
    // {
    //     require_auth (contract);

    //     auto p_itr = profile_t.find (account.value);
    //     check (p_itr != profile_t.end(), "Account to rank does not have a Gyftie profile.");
        
    //     profile_t.modify (p_itr, contract, [&](auto &p) {
    //         p.rank = rank;
    //     });
    // }

      // ACTION gyftietoken::promoteuser (const name account)
        // {
        //     profile_table profile_t (get_self(), get_self().value);
        //     auto p_itr = profile_t.find (account.value);
        //     eosio::check (p_itr != profile_t.end(), "Profile to promote is not found.");
        //     eosio::check (p_itr->rank != 1, "User rank is at highest level; cannot be promoted.");
        //     eosio::check (p_itr->promotion_votes.size() > 0, "There are no votes to promote this user.");

        //     print (" Promoting user: ", account, "\n");
        //     print (" Current rank: ", p_itr->rank, "\n");
        //     // bool promoted = false;
            
        //     std::set<int> potential_ranks = get_voting_ranks (account);
        //     int rank_profile_count, votes_from_rank, best_eligible_rank=0;

        //     auto potential_rank = potential_ranks.rbegin();
        //     while (potential_rank != potential_ranks.rend()) {

        //         rank_profile_count = get_rank_profile_count (*potential_rank);
        //         print ("  Rank Profile Count: ", *potential_rank, ".......", rank_profile_count, "\n");

        //         votes_from_rank = get_votes_from_rank(account, *potential_rank);
        //         print ("  Votes from Rank: ", *potential_rank, ".......", votes_from_rank, "\n");

        //         if (best_eligible_rank == 0) {
        //             best_eligible_rank = *potential_rank + rank_profile_count - votes_from_rank;
        //         } else {
        //             best_eligible_rank = std::min (  best_eligible_rank, 
        //                                         *potential_rank + rank_profile_count - votes_from_rank);
        //         }

        //         print ("---- Best eligible rank ", std::to_string(best_eligible_rank), "\n");
        //         potential_rank++;
        //     }

        //     if (p_itr->rank == 0 || best_eligible_rank < p_itr->rank) {
        //         print ("\n\n *** Promoting user: ", best_eligible_rank, "\n\n");
        //         profile_t.modify (p_itr, get_self(), [&](auto &p) {
        //             p.rank = best_eligible_rank;
        //         });
        //     } else { 
        //         eosio::check (false, "User does not have the votes to be promoted.");
        //     }
        // }
};

#endif