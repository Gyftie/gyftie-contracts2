 #include "../../include/reputation.hpp"

ReputationClass::ReputationClass (const name& contract) : profileClass (contract), contract (contract) {}

uint64_t ReputationClass::get_rank_profile_count (const uint64_t& rank)
{
    auto rank_index = profileClass.profile_t.get_index<"byrank"_n>();
    auto rank_itr = rank_index.lower_bound(rank);
    eosio::check (rank_itr != rank_index.end(), "Profiles with rank not found.");

    uint64_t voter_count = 0;
    while (rank_itr != rank_index.end() && rank_itr->rank == rank) {
        voter_count++;
        rank_itr++;
    }

    return voter_count;
}

uint64_t ReputationClass::get_votes_from_rank (const name& account, const uint64_t& rank)
{
    auto p_itr = profileClass.profile_t.find (account.value);
    eosio::check (p_itr != profileClass.profile_t.end(), "Profile to promote is not found.");

    uint64_t vote_count =0;
    vector<name> votes = p_itr->promotion_votes;
    for (auto voter : votes) {
        if (profileClass.profile_t.get(voter.value).rank == rank) {
            vote_count++;
        }
    }

    return vote_count;
}

uint64_t ReputationClass::get_next_strongest_rank (const uint64_t& rank) 
{
    auto rank_index = profileClass.profile_t.get_index<"byrank"_n>();
    if (rank == 0) {
        return rank_index.rbegin()->rank;
    }
    
    auto rank_itr = rank_index.lower_bound(rank);
    rank_itr--;
    eosio::check (rank_itr != rank_index.end(), "Profile with stronger rank not found.");

    return rank_itr->rank;
}


std::set<int> ReputationClass::get_voting_ranks (const name& account)
{
    auto p_itr = profileClass.profile_t.find (account.value);
    eosio::check (p_itr != profileClass.profile_t.end(), "Profile to promote is not found.");

    vector<name> votes = p_itr->promotion_votes;
    std::set<int> rank_set;
    for (auto voter : votes) {
        rank_set.insert (profileClass.profile_t.get(voter.value).rank);
    }
    return rank_set;
}