#include <gyftietoken.hpp>

ACTION gyftietoken::voteforuser (const name voter, const name profile) {
    profileClass.vote_to_promote_profile (voter, profile);
}

ACTION gyftietoken::unvoteuser (const name voter, const name profile) {
    profileClass.unvote_to_promote_profile (voter, profile);
}

ACTION gyftietoken::unvoteprop(const name voter, const uint64_t proposal_id){

}

ACTION gyftietoken::addcomment (const name& commenter, 
                            const name& comment_type, 
                            const uint64_t& proposal_id,    // -1 for no proposal
                            const name& profile,            // "noprofile"_n for no profile
                            const uint64_t& parent_id, 
                            const string& comment_text) {

    commentClass.add_comment (commenter, comment_type, proposal_id,
                                profile, parent_id, comment_text);
}

ACTION gyftietoken::remcomment (const uint64_t& comment_id) {
    commentClass.remove_comment (comment_id);
}

ACTION gyftietoken::editcomment (const uint64_t& comment_id, const string& comment_text) {
    commentClass.edit_comment (comment_id, comment_text);
}

ACTION gyftietoken::chgthrottle (const uint32_t throttle)
{
    Permit::permit (get_self(), name{0}, name{0}, common::ANY_SIGNATORY);
    gyftieClass.change_throttle (throttle);
}

ACTION gyftietoken::xferzj () 
{
    require_auth ("gftma.x"_n);
    // xfer_account ("zombiejigsaw"_n, "gftma.x"_n);
}

// ACTION gyftietoken::remv2profs ()
// {
//     require_auth (get_self());
//     profileClass.removeAllV2();
// }

// ACTION gyftietoken::backupprofs (const name& profile) {
//     require_auth ("gftma.x"_n);
//     migration.backupprofs (profile);
// }

// ACTION gyftietoken::restoreprofs (const name& profile) {
//     require_auth ("gftma.x"_n);
//     migration.restoreprofs (profile);
// }

ACTION gyftietoken::referuser (const name& referrer, const name& account_to_refer) {
    require_auth (account_to_refer);
    
    profileClass.referred (referrer, account_to_refer);
}

ACTION gyftietoken::verifyuser (const name& verifier, const name& account_to_verify) {
    profileClass.verifyuser (verifier, account_to_verify);
}

ACTION gyftietoken::createbadge (const name& badge_id, 
                                    const string& badge_name, 
                                    const string& description, 
                                    const asset& reward, 
                                    const string& profile_image, 
                                    const string& badge_image, 
                                    const string& mat_icon_name, 
                                    const name& issuer, 
                                    uint8_t badge_type) {

    check (has_auth (get_self()) || has_auth ("gftma.x"_n), "Permission denied. Cannot create badge: " + badge_id.to_string());
    
    badgeClass.add_badge (badge_id, badge_name, description, reward, profile_image, badge_image, mat_icon_name, issuer, badge_type);
} 

ACTION gyftietoken::upgrade (const name& account) {
    Permit::permit (get_self(), account, name{0}, common::SELFORSIGNATORY_ACTIVITY);
    profileClass.upgrade (account);
}

ACTION gyftietoken::issuebadge (const name& badge_recipient, const name& badge_id, const string& notes) {

    profileClass.upgrade (badge_recipient);
    badgeClass.reward_badge(badge_recipient, badge_id, notes);
    badgeClass.check_verified (badge_recipient);
}

ACTION gyftietoken::issueidemp(const name& badge_recipient, const name& badge_id, const string& notes) {
    profileClass.upgrade (badge_recipient);
    badgeClass.reward_idempotent(badge_recipient, badge_id, notes);
    badgeClass.check_verified (badge_recipient);
}

ACTION gyftietoken::unissuebadge (const name& badge_recipient, const name& badge_id) {
    badgeClass.unreward_badge (badge_recipient, badge_id);
}

ACTION gyftietoken::addlocknote (const name account_to_lock, const string note)
{
    Permit::permit (get_self(), account_to_lock, name{0}, common::LOCK_ACTIVITY);
    lockClass.add_lock_note (account_to_lock, note);
}

ACTION gyftietoken::addlockchain (const name account_to_lock, const string note)
{
    Permit::permit (get_self(), account_to_lock, name{0}, common::ANY_SIGNATORY);
    LockChain::lockchain (get_self(), account_to_lock, note);
}

ACTION gyftietoken::unlockchain (const name account_to_unlock, const string note)
{
    Permit::permit (get_self(), account_to_unlock, name{0}, common::ANY_SIGNATORY);
    LockChain::unlockchain (get_self(), account_to_unlock, note);
}

ACTION gyftietoken::unlock (const name account_to_unlock, const string note) 
{
    Permit::permit (get_self(), account_to_unlock, name{0}, common::LOCK_ACTIVITY);
    lockClass.unlock (account_to_unlock, note);
}

ACTION gyftietoken::addlock (const name account_to_lock, const string note) 
{
    print (" \n Adding a lock \n");
    // require_auth (get_self());
    Permit::permit (get_self(), account_to_lock, name{0}, common::LOCK_ACTIVITY);
    lockClass.lock (account_to_lock, note);
}

ACTION gyftietoken::addsig (const name new_signatory) 
{
    Permit::add_signatory (get_self(), new_signatory);
}

ACTION gyftietoken::remsig (const name existing_signatory) 
{
    Permit::remove_signatory (get_self(), existing_signatory);
}

ACTION gyftietoken::dchallenge (const name challenged_account) 
{
    require_auth (get_self());
    challenge_table c_t (get_self(), get_self().value);
    auto c_itr = c_t.find (challenged_account.value);
    eosio::check (c_itr != c_t.end(), "Active challenge for account does not exist.");

    c_t.erase (c_itr);
}

ACTION gyftietoken::setconfig ( const name gftorderbook,
                                const name gyftie_foundation,
                                const name gyftieoracle)
{
    gyftieClass.set_config (gftorderbook, gyftie_foundation, gyftieoracle);
}

ACTION gyftietoken::reset () 
{
    require_auth (get_self());
    gyftieClass.appstate_t.remove ();
    badgeClass.reset();
}


ACTION gyftietoken::setusercnt (const uint32_t count) {
    gyftieClass.setusercnt (count);
}

ACTION gyftietoken::pause () 
{
    gyftieClass.pause();
}

ACTION gyftietoken::unpause () 
{
    gyftieClass.unpause ();
}

ACTION gyftietoken::sellnotify (const name& seller, const asset& amount) {
    require_auth(gyftieClass.get_state().gftorderbook);
    profileClass.selling_gft(seller, amount);
}
    
ACTION gyftietoken::buynotify (const name& buyer, const asset& amount) {
    require_auth(gyftieClass.get_state().gftorderbook);
    profileClass.buying_gft(buyer, amount);
}

ACTION gyftietoken::nchallenge (const name challenger_account, const name challenged_account, const string note)
{
    require_auth (challenger_account);

    Permit::permit (get_self(), challenger_account, challenged_account, common::CHALLENGE);
    //permit_account(challenger_account);
    eosio::check (challenger_account != challenged_account, "Account cannot challenge itself.");
    eosio::check (is_tokenholder (challenger_account), "Challenger is not a GFT token holder.");
    eosio::check (is_tokenholder (challenged_account), "Challenged account is not a GFT token holder.");
    eosio::check (! is_paused(), "Contract is paused." );

    accounts acnts(get_self(), challenged_account.value);
    const auto &ca = acnts.get(common::S_GFT.code().raw(), "no GFT balance object found");

    asset challenge_stake = adjust_asset (ca.balance, (float) 0.10000000);
    stake (challenger_account, challenge_stake);

    challenge_table c_t (get_self(), get_self().value);
    auto c_itr = c_t.find(challenged_account.value);
    eosio::check (c_itr == c_t.end(), "Account has already been challenged.");

    c_t.emplace (get_self(), [&](auto &c) {
        c.challenged_account = challenged_account;
        c.challenger_account = challenger_account;
        c.challenged_time = current_block_time().to_time_point().sec_since_epoch();
        c.challenge_notes.push_back (note);
        c.challenge_stake = challenge_stake;
    });

     action (
        permission_level{get_self(), "owner"_n},
        get_self(), "addlock"_n,
        std::make_tuple(challenged_account, note))
    .send();
}

ACTION gyftietoken::addcnote (const name scribe, const name challenged_account, const string note)
{
    require_auth (scribe);
    //permit_account (scribe);
    Permit::permit (get_self(), scribe, challenged_account, common::ANY);

    eosio::check (! is_paused(), "Contract is paused." );

    challenge_table c_t (get_self(), get_self().value);
    auto c_itr = c_t.find (challenged_account.value);
    eosio::check (c_itr != c_t.end(), "Account does not have an active challenge.");

    c_t.modify (c_itr, get_self(), [&] (auto &c) {
        c.challenge_notes.push_back (note);
    });
}

ACTION gyftietoken::validate (const name validator, const name account, const string idhash, const string id_expiration)
{
    // permit_account(validator);
    // permit_validator(validator, account);
    Permit::permit (get_self(), validator, account, common::VALIDATE);

    require_auth (validator);
    eosio::check (is_tokenholder (validator), "Validator is not a GFT token holder.");
    eosio::check (! is_paused(), "Contract is paused." );

    eosio::check (profileClass.isIDHashMatch (account, idhash), "ID hash provided does not match records. Account not validated.");
      
    challenge_table c_t (get_self(), get_self().value);
    auto c_itr = c_t.find (account.value);
    eosio::check (c_itr != c_t.end(), "Account does not have an active challenge.");

    // DEPLOY
    requnstake (c_itr->challenger_account, c_itr->challenge_stake);
    //unstake (c_itr->challenger_account, c_itr->challenge_stake);

    asset validator_amount = adjust_asset (c_itr->challenge_stake, (float) 0.200000000);
    asset challenged_amount = adjust_asset (c_itr->challenge_stake, (float) 0.400000000);
    asset redistribution_amount = c_itr->challenge_stake - validator_amount - challenged_amount;

    string to_validator_memo = string { "GFT-reward to the Validator. See 'How Gyftie Works' document - ask us for link." };
    string to_challenged_memo = string { "GFT-reward to the Challenged-then-Validated Account. See 'How Gyftie Works' document - ask us for link." };   
    string redistribution_memo = string { "Seized asset redistribution. See 'How Gyftie Works' document - ask us for link." };
    
    action (
        permission_level{get_self(), "owner"_n},
        get_self(), "transfer"_n,
        std::make_tuple(c_itr->challenger_account, validator, validator_amount, to_validator_memo))
    .send();

    action (
        permission_level{get_self(), "owner"_n},
        get_self(), "transfer"_n,
        std::make_tuple(c_itr->challenger_account, c_itr->challenged_account, challenged_amount, to_challenged_memo))
    .send();

    action (
        permission_level{get_self(), "owner"_n},
        get_self(), "transfer"_n,
        std::make_tuple(c_itr->challenger_account, get_self(), redistribution_amount, redistribution_memo))
    .send();

    c_t.erase (c_itr);    
}

ACTION gyftietoken::setrank (const name account, const uint64_t rank) 
{
    profileClass.setrank (account, rank);
}

ACTION gyftietoken::proposetrx (ignore<name> proposer,
                                    ignore<string> proposal_name,
                                    ignore<string> notes,
                                    ignore<transaction> trx) {
    name _proposer;
    string _proposal_name;
    string _notes;
    transaction_header _trx_header;

    _ds >> _proposer >> _proposal_name >> _notes;

    const char* trx_pos = _ds.pos();
    size_t size    = _ds.remaining();
    _ds >> _trx_header;

    require_auth( _proposer );
    check( _trx_header.expiration >= eosio::time_point_sec(current_time_point()), "transaction expired" );

    std::vector<char> pkd_trans;
    pkd_trans.resize(size);
    memcpy((char*)pkd_trans.data(), trx_pos, size);

    proposalClass.propose_trx (_proposer, _proposal_name, _notes, pkd_trans);
}

ACTION gyftietoken::execproposal (const uint64_t& proposal_id, const name& executer) {
    proposalClass.exec (proposal_id, executer);
}

ACTION gyftietoken::removeprop (const uint64_t proposal_id) 
{
    proposalClass.remove (proposal_id);
}

ACTION gyftietoken::propose (const name& proposer,
                                const string& proposal_name,
                                const string& notes) 
{
    eosio::check (! is_paused(), "Contract is paused." );
    proposalClass.create (proposer, proposal_name, notes);
}

ACTION gyftietoken::votefor (const name voter,
                            const uint64_t proposal_id) 
{
    proposalClass.vote_for (voter, proposal_id);
}

ACTION gyftietoken::voteagainst (const name voter,
                            const uint64_t proposal_id) 
{
    proposalClass.vote_against (voter, proposal_id);
}

// ACTION gyftietoken::archiveprops () {
//     require_auth ("gftma.x"_n);
//     proposalClass.archive ();
// }

// ACTION gyftietoken::clearprops () {
//     require_auth ("gftma.x"_n);
//     proposalClass.clearprops ();
// }

ACTION gyftietoken::createprof (const name& account) 
{
    Permit::permit (get_self(), get_self(), account, common::ORACLE_ACTIVITY);
    profileClass.create (account);
}

ACTION gyftietoken::smsverify (const name& account) 
{
    Permit::permit (get_self(), get_self(), account, common::ORACLE_ACTIVITY);
    // if account already exists in profiles 2, issue badge
    if (profileClass.existsInV2(account)) {
        badgeClass.reward_badge (account, "verifysms"_n, string("Successfully verified SMS"));
    } else if (profileClass.existsInV1(account)) {
        // if it exists in profiles 1, upgrade it and issue badge
        profileClass.upgrade (account);
        badgeClass.reward_badge (account, "verifysms"_n, string("Successfully verified SMS"));
    } else {
        // if it doesn't exist at all, createprof and issue badge
        profileClass.create (account);
        badgeClass.reward_badge (account, "verifysms"_n, string("Successfully verified SMS"));
    }
}

ACTION gyftietoken::accelunstake (const name& account) 
{
    // accelerate unstake 
    check (has_auth (get_self()) || has_auth ("gftma.x"_n), "Permission denied. Cannot accelerate unstake.");
    profileClass.accelunstake (account);
}

ACTION gyftietoken::remprofprep (const name& account) 
{
    // Ensure profile exists
    // Transfer tokens from account to gyftietokens account
    // Destruct (retire) tokens from circulation

    // Permit::permit (get_self(), account, name{0}, Permit::ANY_SIGNATORY);
    check (has_auth (get_self()) || has_auth ("gftma.x"_n), "Permission denied. Cannot prepare to remove profile.");

    accounts from_acnts(get_self(), account.value);
    const auto &from = from_acnts.get(common::S_GFT.code().raw(), "no GFT balance object found");

    if (from.balance.amount > 0) {
        string memo = string { "Transfer tokens to Gyftie for destruction" };
        action (
            permission_level{get_self(), "owner"_n},
            get_self(), "transfer"_n,
            std::make_tuple(account, get_self(), from.balance, memo))
        .send();

        string memo2 = string { "Destruct tokens from destroyed profile" };
        retire (from.balance, memo2);

        // string memo2 = string { "Destruct tokens from destroyed profile" };
        // action (
        //     permission_level{get_self(), "owner"_n},
        //     get_self(), "retire"_n,
        //     std::make_tuple(from.balance, memo2))
        // .send();
    }
    
    //profileClass.removeprof (account);
    gyftieClass.decrement_account_count();
    badgeClass.remove_badges (account);
}

ACTION gyftietoken::claim (const name account, const string claim_key) {
    require_auth (account);
}

ACTION gyftietoken::removeprof (const name& account) {
    
    check (has_auth (get_self()) || has_auth ("gftma.x"_n), "Permission denied. Cannot prepare to remove profile.");
    auto p_itr = profileClass.profile_t.find (account.value);
    check (p_itr != profileClass.profile_t.end(), "Gyftie profile not found in table 1: " + account.to_string());

    profileClass.removeprof (account);
}

ACTION gyftietoken::addhash (const name idchecker, const name idholder, const string idhash, const string id_expiration) {

    print (" \nAdding hash : ", idhash, "\n\n");
    require_auth (idchecker);
    Permit::permit (get_self(), idchecker, idholder, common::GYFT);

    profileClass.setidhash (idholder, idhash, id_expiration);

    string notes = string { "ID verified by " + idchecker.to_string() };
    action (
        permission_level{get_self(), "owner"_n},
        get_self(), "issuebadge"_n,
        std::make_tuple(idholder, "govtidver"_n, notes))
    .send();

}

// ACTION gyftietoken::gyft2 (const name from, 
//                             const name to, 
//                             const string idhash,
//                             const string relationship,
//                             const string id_expiration)
// {
//     gyftClass.throttle_check();
//     eosio::check (! is_paused(), "Contract is paused." );
//     Permit::permit (get_self(), from, to, Permit::GYFT);

    //permit_account(from);

    // require_auth (from);
    // eosio::check (is_tokenholder (from), "Gyfter must be a GFT token holder.");

    // asset creation_fee = get_one_gft() * 0;
    // if ( !is_account (to)) {
    //     creation_fee = create_account_from_request (from, to);
    // }

    // eosio::check (!profileClass.exists(to), "Recipient must not be a Gyftie account.");

    // profileClass.create (to, idhash, id_expiration);
    
    // config_table config (get_self(), get_self().value);
    // auto c = config.get();
   
    // asset issue_to_gyfter = get_gyfter_reward(from);
    // asset issue_to_gyftee = get_recipient_reward(); 

    // string to_gyfter_memo { "Vouch-Gyft-Earn GFT-creation to Gyfter. See 'How Gyftie Works' document - ask us for link." };
    // string to_gyftee_memo { "Vouch-Gyft-Earn GFT-creation to new user. See 'How Gyftie Works' document - ask us for link." };
    // string to_gyftiegyftie {"Vouch-Gyft-Earn GFT-creation to Gyftie venture (gyftiegyftie). See 'How Gyftie Works' document - ask us for link."};
    // string auto_liquidity_memo { "Vouch-Gyft-Earn GFT-creation to liquidity providers. See 'How Gyftie Works' document - ask us for link." };
 
    // float share_for_liquidity_reward = 0.100000000000;
    // asset gyft_inflation = issue_to_gyfter + issue_to_gyftee;
    // asset amount_to_gyftiegyftie = asset { static_cast<int64_t> (gyft_inflation.amount * (1 - share_for_liquidity_reward)), issue_to_gyfter.symbol };
    // asset liquidity_reward = gyft_inflation - amount_to_gyftiegyftie;

    // action (
    //     permission_level{get_self(), "owner"_n},
    //     get_self(), "issuetostake"_n,
    //     std::make_tuple(from, issue_to_gyfter - creation_fee, to_gyfter_memo))
    // .send();

    // action (
    //     permission_level{get_self(), "owner"_n},
    //     get_self(), "issue"_n,
    //     std::make_tuple(gyftieClass.get_state().gyftiegyftie, amount_to_gyftiegyftie, to_gyftiegyftie))
    // .send();

    // action (
    //     permission_level{get_self(), "owner"_n},
    //     get_self(), "issue"_n,
    //     std::make_tuple(gyftieClass.get_state().gftorderbook, liquidity_reward, auto_liquidity_memo))
    // .send();

    // action (
    //     permission_level{get_self(), "owner"_n},
    //     gyftieClass.get_state().gftorderbook, "addliqreward"_n,
    //     std::make_tuple(liquidity_reward))
    // .send();

    // action (
    //     permission_level{get_self(), "owner"_n},
    //     get_self(), "issuetostake"_n,
    //     std::make_tuple(to, issue_to_gyftee, to_gyftee_memo))
    // .send();

//     addgyft (from, to, issue_to_gyfter, issue_to_gyftee, relationship);
// }

ACTION gyftietoken::create()
{
    require_auth(get_self());

    eosio::check(S_GFT.is_valid(), "invalid symbol name");

    stats statstable(get_self(), S_GFT.code().raw());
    auto existing = statstable.find(S_GFT.code().raw());
    eosio::check(existing == statstable.end(), "token with symbol already exists");

    statstable.emplace(get_self(), [&](auto &s) {
        s.symbol = S_GFT;
        s.supply.symbol = S_GFT;
        s.issuer = get_self();
    });

    // profileClass.create (get_self(), "ISSUER-HASH-PLACEHOLDER", "NO EXPIRATION");
}

ACTION gyftietoken::issue(const name to, const asset quantity, const string memo)
{
    auto sym = quantity.symbol;
    eosio::check(sym.is_valid(), "invalid symbol name");
    eosio::check(memo.size() <= 256, "memo has more than 256 bytes");

    auto sym_name = sym.code().raw();
    stats statstable(_self, sym_name);
    auto existing = statstable.find(sym_name);
    eosio::check(existing != statstable.end(), "token with symbol does not exist, create token before issue");
    const auto &st = *existing;

    eosio::check (has_auth (st.issuer) || has_auth (get_self()), "issue requires authority of issuer or token contract.");
    
    eosio::check(quantity.is_valid(), "invalid quantity");
    eosio::check(quantity.amount > 0, "must issue positive quantity");
    eosio::check(quantity.symbol == st.symbol, "symbol precision mismatch");

    statstable.modify(st, eosio::same_payer, [&](auto &s) {
        s.supply += quantity;
    });

    add_balance(st.issuer, quantity, st.issuer);

    if (to != st.issuer)
    {
        //transfer (st.issuer, to, quantity, memo);
        SEND_INLINE_ACTION(*this, transfer, {st.issuer, "owner"_n}, {st.issuer, to, quantity, memo});
    }
}


ACTION gyftietoken::transfer(const name from, const name to, const asset quantity, const string memo)
{
    eosio::check (! is_paused(), "Contract is paused." );
    Permit::permit (get_self(), from, to, common::ANY);
    
    eosio::check(from != to, "cannot transfer to self");
    eosio::check (has_auth (get_self()) || has_auth (from), "Permission denied - cannot transfer.");

    auto sym = quantity.symbol.code().raw();
    stats statstable(_self, sym);
    const auto &st = statstable.get(sym);

    require_recipient(from);
    require_recipient(to);

    eosio::check(quantity.is_valid(), "invalid quantity");
    eosio::check(quantity.amount > 0, "must transfer positive quantity");
    eosio::check(quantity.symbol == st.supply.symbol, "symbol precision mismatch");
    eosio::check(memo.size() <= 256, "memo has more than 256 bytes");

    sub_balance(from, quantity);
    add_balance(to, quantity, get_self());
}

ACTION gyftietoken::xfertostake(const name from, const name to, const asset quantity, const string memo)
{
    transfer (from, to, quantity, memo);

    action (
        permission_level{get_self(), "owner"_n},
        get_self(), "stake"_n,
        std::make_tuple(to, quantity))
    .send();

    // eosio::transaction out{};
    // out.actions.emplace_back(permission_level{get_self(), "owner"_n}, 
    //     get_self(), "stake"_n, 
    //     std::make_tuple(to, quantity));
    // out.delay_sec = 1;
    // out.send(get_next_sender_id(), get_self());    
}

ACTION gyftietoken::isstoskoracl (const name to, const asset quantity, const string memo) 
{
    Permit::permit (get_self(), to, to, common::ORACLE_ACTIVITY);

    check(quantity <= asset{1000000000, S_GFT}, "Permission denied. Insufficent authority to issue " + 
            quantity.to_string() + " to stake."); 

    action (
        permission_level{get_self(), "owner"_n},
        get_self(), "issuetostake"_n,
        std::make_tuple(to, quantity, memo))
    .send();
}

ACTION gyftietoken::issuetostake (const name to, const asset quantity, const string memo)
{
    require_auth (get_self());
    issue (to, quantity, memo);

    action (
        permission_level{get_self(), "owner"_n},
        get_self(), "stake"_n,
        std::make_tuple(to, quantity))
    .send();
}

ACTION gyftietoken::unstaked2 (const name user, const asset quantity) 
{
    require_auth (get_self());
    unstake (user, quantity);
}

ACTION gyftietoken::stake (const name account, const asset quantity) 
{
    eosio::check (has_auth (account) || has_auth (get_self()), "Staking requires authority of account or token contract.");
    profileClass.stake (account, quantity);
}

ACTION gyftietoken::requnstake (const name user, const asset quantity)
{
    require_auth (user);
    eosio::check (quantity.amount > 0, "Requested unstake quantity must be greater than zero.");
    check (profileClass.existsInV2(user), "Cannot request unstake. User must upgrade profile to version 2 to unstake.");

    auto p_itr = profileClass.profile2_t.find (user.value);
    eosio::check (p_itr != profileClass.profile2_t.end(), "Account profile not found.");

    challenge_table c_t (get_self(), get_self().value);
    auto challenger_index = c_t.get_index<"bychallenger"_n>();
    auto challenger_itr = challenger_index.begin();

    asset challenged_balance = asset {0, quantity.symbol};
    while (challenger_itr->challenger_account == user && challenger_itr != challenger_index.end()) {
        challenged_balance += challenger_itr->challenge_stake;
        challenger_itr++;
    }

    eosio::check (p_itr->staked_balance - p_itr->unstaking_balance >= quantity, "Requested unstake quantity exceeds staked balance.");
    eosio::check (p_itr->staked_balance - p_itr->unstaking_balance - challenged_balance >= quantity, "Requested unstake quantity exceeds staked balance when accounting for your active challenges.");

    asset remaining_stake = quantity;

    uint32_t    delay_increment = 60 * 60 * 18;  
    uint32_t    delay = delay_increment;
    float       stake_increment = 0.05000000000;

    while (remaining_stake.amount > 0) {
        asset current_stake = asset {std::min(remaining_stake.amount, 
                                              adjust_asset (quantity, stake_increment).amount),
                                     remaining_stake.symbol};

        defer_unstake(user, current_stake, delay);
        delay += delay_increment;
        remaining_stake -= current_stake;
    }

    profileClass.profile2_t.modify (p_itr, get_self(), [&](auto &p) {
      
        p.unstaking_balance += quantity;
        p.staked_balance -= quantity;
    });
}
