#include "../../include/proposal.hpp"

ProposalClass::ProposalClass (const name& contract) : 
    proposal_t (contract, contract.value), 
    profileClass (contract),
    contract (contract) {}

iterator<std::bidirectional_iterator_tag, const ProposalClass::Proposal> ProposalClass::create (const name& proposer, const string& notes) {
    require_auth (proposer);

    Permit::permit (contract, proposer, name{0}, Permit::PROPOSE);

    return proposal_t.emplace (proposer, [&](auto &p) {
        p.proposal_id       = proposal_t.available_primary_key();
        p.created_date      = current_block_time().to_time_point().sec_since_epoch();
        p.proposer          = proposer;
        p.notes             = notes;
        p.votes_for         = 1;
        p.voters_for.push_back(proposer);
        p.votes_against     = 0;

        // DEPLOY 
        p.rank              = profileClass.profile_t.get(proposer.value).rank;
        p.expiration_date   = current_block_time().to_time_point().sec_since_epoch() + (60 * 60 * 24 * 30);  // 30 days
    });
}

auto ProposalClass::load (const uint64_t& proposal_id) {
    auto p_itr = proposal_t.find (proposal_id);
    eosio::check (p_itr != proposal_t.end(), "Proposal is not found.");
    return *p_itr;
}

iterator<std::bidirectional_iterator_tag, const ProposalClass::Proposal> ProposalClass::remove (const uint64_t& proposal_id) {

    auto p_itr = proposal_t.find (proposal_id);
    eosio::check (p_itr != proposal_t.end(), "Proposal ID is not found.");

    Permit::permit (contract, p_itr->proposer, name{0}, Permit::REMOVE_PROPOSAL);

    return proposal_t.erase (p_itr);
}

void ProposalClass::check_vote (const Proposal p, const name& voter) {
    auto voter_for_itr = std::find (p.voters_for.begin(), p.voters_for.end(), voter);
    eosio::check (voter_for_itr == p.voters_for.end(), "User has already voted (for).");

    auto voter_against_itr = std::find (p.voters_against.begin(), p.voters_against.end(), voter);
    eosio::check (voter_against_itr == p.voters_against.end(), "User has already voted (against).");

    eosio::check (current_block_time().to_time_point().sec_since_epoch() <= p.expiration_date, "Proposal has expired.");
}

ProposalClass::Proposal ProposalClass::vote_for (const name& voter, const uint64_t& proposal_id) {
    Permit::permit (contract, voter, name{0}, Permit::AUTH_ACTIVITY);
    
    auto prop = load (proposal_id);
    check_vote (prop, voter);

    proposal_t.modify (prop, contract, [&](auto &p) {
        p.votes_for++;
        p.voters_for.push_back (voter);
    });
    return prop;
}

ProposalClass::Proposal ProposalClass::vote_against (const name& voter, const uint64_t& proposal_id) {
    Permit::permit (contract, voter, name{0}, Permit::AUTH_ACTIVITY);

    auto prop = load (proposal_id);
    check_vote (prop, voter);
    
    proposal_t.modify (prop, contract, [&](auto &p) {
        p.votes_for++;
        p.voters_for.push_back (voter);
    });

    return prop;
}