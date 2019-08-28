/* eslint-disable prettier/prettier */
const assert = require("assert");
const eoslime = require("../../eoslime").init("local");
const util = require("util")

const GYFTIETOKEN_WASM = "../gyftie/gyftietoken/gyftietoken.wasm";
const GYFTIETOKEN_ABI = "../gyftie/gyftietoken/gyftietoken.abi";
const TOKEN_WASM = "../gyftie/token/token.wasm";
const TOKEN_ABI = "../gyftie/token/token.abi";
const GFTORDERBOOK_WASM = "../gyftie/gftorderbook/gftorderbook.wasm";
const GFTORDERBOOK_ABI = "../gyftie/gftorderbook/gftorderbook.abi";

let gyftieTokenContract, eosTokenContract, gftOrderBookContract, gyftieOracle;
let gyftieTokenAccount, eosTokenAccount, gftOrderBookAccount;
let member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, gyftiegyftie;
let member11, member12, member13, member14, member15;

async function assetToFloat(assetStr, precision) {
    if (typeof precision === "undefined") {
      precision = 4;
    }
    // console.log(typeof assetStr)
    // console.log(assetStr)
    return parseFloat(
      Math.round(
        parseFloat(assetStr.substring(0, assetStr.length - 4)) * 10 ** precision
      ) /
        10 ** precision
    ).toFixed(precision);
  }

async function getGftSupply () {
  const stat = await gyftieTokenContract.provider.eos.getTableRows({
    code: gyftieTokenAccount.name,
    scope: "GFT",
    table: "stat",
    json: true
  });
  return stat.rows[0].supply;
}

async function getGftBalance (member) {

    const balances = await gyftieTokenContract.provider.eos.getTableRows({
        code: gyftieTokenAccount.name,
        scope: gyftieTokenAccount.name,
        table: "profiles2",
        lower_bound: member.name,
        limit: 1,
        json: true
    });

    const totalGft = await addGft(balances.rows[0].gft_balance, await addGft(balances.rows[0].staked_balance, balances.rows[0].unstaking_balance));

    const accounts = await gyftieTokenContract.provider.eos.getTableRows({
        code: gyftieTokenAccount.name,
        scope: member.name,
        table: "accounts",
        json: true
    });

    if (accounts.rows[0] === undefined) {
        assert.equal(totalGft, "0.00000000 GFT");
        return balances.rows[0].gft_balance;
    }
    assert.equal (totalGft, accounts.rows[0].balance);
    return accounts.rows[0].balance;
}

async function getProfile (member) {
  const profiles = await gyftieTokenContract.provider.eos.getTableRows({
    code: gyftieTokenAccount.name,
    scope: gyftieTokenAccount.name,
    table: "profiles2",
    lower_bound: member.name,
    limit: 1,
    json: true
  });
  return profiles.rows[0];
}

async function getStakedGft (member) {
  const profile = await getProfile (member);
  return profile.staked_balance;
}

async function createDefaultBadges () {
  await gyftieTokenContract.createbadge ("verifysms", "SMS Verified", "Verified that user can receive SMS messages", "0.10000000 GFT", "", "", "textsms", "gyftieoracle", 1);
    await gyftieTokenContract.createbadge ("verifyemail", "Email Verified", "Verified that user can receive Emails", "0.20000000 GFT", "", "", "email", "gyftieoracle", 1);
    await gyftieTokenContract.createbadge ("govtidver", "Government-issued ID Verified", "User has saved hash of Government-issued ID on chain for future verification", "0.30000000 GFT", "", "", "portrait", "gyftieoracle", 1);
    await gyftieTokenContract.createbadge ("vouchirl", "Vouched for In Real Life (IRL)", "Someone in real life has vouched for user", "0.40000000 GFT", "", "", "group", "gyftieoracle", 1);
    await gyftieTokenContract.createbadge ("buygft", "Purchased GFT", "User has purchased GFT", "1.00000000 GFT", "", "", "local_grocery", "gyftieoracle", 1);
    await gyftieTokenContract.createbadge ("identified", "Fully identified", "User has completed all 5 onboarding steps", "0.00000000 GFT", "", "", "how_to_reg", "gyftieoracle", 1);
}


async function addGft (gft1, gft2) {
    // console.log ('typeof gft1: ', typeof gft1)
    const gftFloat1 = await assetToFloat(gft1, 8)
    // console.log ('gftFloat1         :    ', gftFloat1);
    // console.log ('typeof gftFloat1  :', typeof gftFloat1);
    
    const gftFloat2 = await assetToFloat(gft2, 8)
    // console.log ('gftFloat2         :    ', gftFloat2);
    // console.log ('typeof gftFloat2  :', typeof gftFloat2);

    const sumGft = parseFloat(parseFloat(gftFloat1) + parseFloat(gftFloat2)).toFixed(8) + ' GFT'
    // console.log ('Sum GFT: ', sumGft);
    return sumGft;
}

describe("Gyftie Testing", function() {
  this.timeout(150000);

  let accounts;

  before(async () => {
    accounts = await eoslime.Account.createRandoms(20);
    gyftieTokenAccount = accounts[0];
    eosTokenAccount = accounts[1];
    gyftiegyftie = accounts[2];
    member1 = accounts[3];
    member2 = accounts[4];
    member3 = accounts[5];
    member4 = accounts[6];
    gftOrderBookAccount = accounts[7];
    gyftieOracle = accounts[8];
    member5 = accounts[9];
    member6 = accounts[10];
    member7 = accounts[11];
    member8 = accounts[12];
    member9 = accounts[13];
    member10 = accounts [14];

    member11 = accounts[15];
    member12 = accounts[16];
    member13 = accounts[17];
    member14 = accounts[18];
    member15 = accounts[19];

    console.log(" Gyftie Account        : ", gyftieTokenAccount.name);
    console.log(" EOS Token Account     : ", eosTokenAccount.name);
    console.log(" GFT Orderbook         : ", gftOrderBookAccount.name);
    console.log(" GyftieGyftie          : ", gyftiegyftie.name);
    console.log(" Gyftie Oracle         : ", gyftieOracle.name);
    console.log(" Member 1              : ", member1.name);
    console.log(" Member 2              : ", member2.name);
    console.log(" Member 3              : ", member3.name);
    console.log(" Member 4              : ", member4.name);
    console.log(" Member 5              : ", member5.name);
    console.log(" Member 6              : ", member6.name);
    console.log(" Member 7              : ", member7.name);
    console.log(" Member 8              : ", member8.name);
    console.log(" Member 9              : ", member9.name);
    console.log(" Member 10             : ", member10.name);
    console.log(" Member 11             : ", member11.name);
    console.log(" Member 12             : ", member12.name);
    console.log(" Member 13             : ", member13.name);
    console.log(" Member 14             : ", member14.name);
    console.log(" Member 15             : ", member15.name);

    await gyftieTokenAccount.addPermission(
        gyftieTokenAccount.name,
      "active",
      gyftieTokenAccount.name,
      "eosio.code"
    );
    await gyftieTokenAccount.addPermission(
        gyftieTokenAccount.name,
      "owner",
      gyftieTokenAccount.name,
      "eosio.code"
    );
    await gftOrderBookAccount.addPermission(
        gftOrderBookAccount.name,
      "active",
      gftOrderBookAccount.name,
      "eosio.code"
    );

    gyftieTokenContract = await eoslime.AccountDeployer.deploy(
      GYFTIETOKEN_WASM,
      GYFTIETOKEN_ABI,
      gyftieTokenAccount
    );
    eosTokenContract = await eoslime.AccountDeployer.deploy(
      TOKEN_WASM,
      TOKEN_ABI,
      eosTokenAccount
    );
    gftOrderBookContract = await eoslime.AccountDeployer.deploy(
      GFTORDERBOOK_WASM,
      GFTORDERBOOK_ABI,
      gftOrderBookAccount
    );

    await gyftieTokenContract.setconfig(gftOrderBookAccount.name, gyftiegyftie.name, gyftieOracle.name, {from: gyftieTokenAccount });
    //await gyftieTokenContract.setstate(222, 222, 2, 1, {from: gyftieTokenAccount });
    await gyftieTokenContract.unpause({from: gyftieTokenAccount });

    await gftOrderBookContract.setconfig(gyftieTokenAccount.name, eosTokenAccount.name, "EOS", 4, {from: gyftieTokenAccount.name})
    await gftOrderBookContract.unpause({from: gftOrderBookAccount });
    await gftOrderBookContract.setstate("5.0000 EOS", {from: gftOrderBookAccount });
    await gftOrderBookContract.setrewconfig(750000, 250000, {from: gftOrderBookAccount });

    await eosTokenContract.create(eosTokenAccount.name, "1000000000.0000 EOS", {from: eosTokenAccount });
    await eosTokenContract.issue(member1.name, "100000.0000 EOS", "memo", {from: eosTokenAccount});
    await eosTokenContract.issue(member2.name, "100000.0000 EOS", "memo", {from: eosTokenAccount});
    await eosTokenContract.issue(member3.name, "100000.0000 EOS", "memo", {from: eosTokenAccount});
    await eosTokenContract.issue(member4.name, "100000.0000 EOS", "memo", {from: eosTokenAccount});

    await eosTokenContract.transfer(member1.name, gftOrderBookAccount.name, "1000.0000 EOS", "memo", {from: member1});
    await eosTokenContract.transfer(member2.name, gftOrderBookAccount.name, "1000.0000 EOS", "memo", {from: member2});
    await eosTokenContract.transfer(member3.name, gftOrderBookAccount.name, "1000.0000 EOS", "memo", {from: member3});
    await eosTokenContract.transfer(member4.name, gftOrderBookAccount.name, "1000.0000 EOS", "memo", {from: member4});

    await gftOrderBookContract.addbucket(0, 10000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(10001, 20000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(20001, 30000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(30001, 40000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(50001, 70000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(70001, 100000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(100001, 150000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(150001, 200000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(200001, 300000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(300001, 500000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(500001, 700000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(700001, 1000000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(1000001, 2000000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(2000001, 3000000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(3000001, 4000000, { from: gftOrderBookAccount });
    await gftOrderBookContract.addbucket(4000001, 5000000, { from: gftOrderBookAccount });

    await gyftieTokenContract.create ({ from: gyftieTokenAccount });
    await gyftieTokenContract.issue (gyftieTokenAccount.name, "8.00000000 GFT", "memo", {from: gyftieTokenAccount});

    console.log (" Completed Gyftie setup procedures")

    // create default badges
  });

  it("TEST 1 :::: Should gyft to member 1", async () => {

    // await gyftieTokenContract.gyft2(gyftieTokenAccount.name, member1.name, "idhash", "friend", "idexpiration", { from: gyftieTokenAccount });
    await gyftieTokenContract.createprof (member1.name, { from: gyftieOracle });

    const profiles = await gyftieTokenContract.provider.eos.getTableRows({
      code: gyftieTokenAccount.name,
      scope: gyftieTokenAccount.name,
      table: "profiles2",
      lower_bound: member1.name,
      limit: 1,
      json: true
    });
    console.log(profiles);

    assert.equal(profiles.rows.length, 1);
    assert.equal(profiles.rows[0].account, member1.name);
  });

  it("TEST 2 :::: Should create and assign a badge", async () => {

    // await gyftieTokenContract.issuetostake (member1.name, '1.00000000 GFT', 'First issue of a badge in automated test.', { from: gyftieTokenAccount })


    await gyftieTokenContract.createbadge ('badgeid1', 
                'Badge Name #1', 
                'First badge created using test case',
                '1.23451234 GFT', 
                'info url', 
                'another image', 
                'icon name', 
                gyftieOracle.name,
                2, 
                { from: gyftieTokenAccount });

    const badges = await gyftieTokenContract.provider.eos.getTableRows({
        code: gyftieTokenAccount.name,
        scope: gyftieTokenAccount.name,
        table: "badges",
        json: true
    });
    console.log (badges)

    assert.equal(badges.rows.length, 1);

    let member1Profile = await getProfile(member1);
    console.log(typeof member1Profile);
    console.log(member1Profile);
    console.log("member 1 staked balance: ", member1Profile.staked_balance);
    const beforeBalance = member1Profile.staked_balance;
    console.log('Before Balance: ', beforeBalance);
    console.log('Expected GFT Balance, post reward: ', await addGft(beforeBalance, badges.rows[0].reward))

    // await getProfile(member1)
    await gyftieTokenContract.issuebadge (member1.name, 'badgeid1', 'First issue of a badge in automated test.', { from: gyftieOracle })
    // await printProfile(member1);

    const badgeaccts = await gyftieTokenContract.provider.eos.getTableRows({
        code: gyftieTokenAccount.name,
        scope: gyftieTokenAccount.name,
        table: "badgeaccts",
        json: true
    });
    member1Profile = await getProfile(member1);
    const afterBalance = member1Profile.staked_balance;
    console.log('After balance: ', afterBalance)

    assert.equal(badgeaccts.rows.length, 1);
    assert.equal(badgeaccts.rows[0].badge_holder, member1.name);

    assert.equal(await addGft(beforeBalance, badges.rows[0].reward), afterBalance);
  });

  it('TEST 3 :::: Should accelerate unstake', async () => {

    const beforeStake = await getStakedGft(member1);
    console.log(beforeStake);

    await gyftieTokenContract.accelunstake (member1.name, { from: gyftieTokenAccount });
    const afterStake = await getStakedGft(member1);
    console.log ("After Stake: ", afterStake);
    assert.equal (afterStake, '0.00000000 GFT');

    const beforeBalance = await getGftBalance(member1);
    console.log ("Before balance, member: ", beforeBalance);
    const beforeSupply = await getGftSupply();
    console.log("Before retire supply: ", beforeSupply);

    await gyftieTokenContract.remprofprep (member1.name, { from: gyftieTokenAccount });

    const afterSupply = await getGftSupply();
    console.log("After retire supply: ", afterSupply);

    assert.equal(afterSupply, await addGft(beforeSupply, "-" + beforeBalance));
  });

  // it('TEST 4 :::: Should create a new profile, add badge, then remove profile', async () => {

  //   await gyftieTokenContract.createprof (member2.name, { from: gyftieOracle});
  //   await gyftieTokenContract.createbadge ('badgeid2', 'Badge Name #2', 'Second Badge',
  //       '1.00000000 GFT', 'info url', 'another image', 'icon name', gyftieOracle.name, 2, { from: gyftieTokenAccount });

  //   await gyftieTokenContract.issuebadge (member2.name, 'badgeid2', 'Second badge for create/remove testing.', { from: gyftieOracle })

  //   const beforeTotalGft = await getGftSupply();
  //   console.log (" Before GFT Supply: ", beforeTotalGft);
  //   const beforeMember2Bals = await getGftBalance(member2)
  //   console.log (" Destroying profile for : ", member2.name, "; balance of: ", beforeMember2Bals);

  //   await gyftieTokenContract.accelunstake (member2.name, { from: gyftieTokenAccount });
  //   await gyftieTokenContract.remprofprep (member2.name, { from: gyftieTokenAccount });
  //   await gyftieTokenContract.removeprof (member2.name, { from: gyftieTokenAccount });

  //   const afterTotalGft = await getGftSupply();
  //   console.log (" After GFT Supply: ", afterTotalGft);

  //   assert.equal (await addGft(afterTotalGft, beforeMember2Bals), beforeTotalGft);
  // });

  it('TEST 5 :::: Should create a new identity badge, add referral, and issue badge', async () => {

    await gyftieTokenContract.createprof (member6.name, { from: gyftieOracle});
    await gyftieTokenContract.createprof (member7.name, { from: gyftieOracle});

    await gyftieTokenContract.createbadge ('identype', 'Identity Type Badge', 'Second Badge',
        '1.20000000 GFT', 'info url', 'another image', 'icon name', gyftieOracle.name, 1, { from: gyftieTokenAccount });

    await gyftieTokenContract.createbadge ('identifies', 'Identified Badge', 'Second Badge',
        '1.50000000 GFT', 'info url', 'another image', 'icon name', gyftieOracle.name, 1, { from: gyftieTokenAccount });

    await gyftieTokenContract.issuebadge (member6.name, 'identifies', 'Legit identity badge', { from: gyftieOracle })
    await gyftieTokenContract.referuser (member6.name, member7.name, { from: member7 });
    await gyftieTokenContract.issuebadge (member7.name, 'identype', 'Identity type badge', { from: gyftieOracle })

    const member6Gft = await getGftBalance(member6)
    const member7Gft = await getGftBalance(member7)

    console.log (" Member 6 GFT: ", member6Gft);
    console.log (" Member 7 GFT: ", member7Gft);

    assert.equal ("2.70000000 GFT", member6Gft);
    assert.equal ("1.20000000 GFT", member7Gft);
  });

  it('TEST 6 :::: Should create a new identity badge, add referral from unverified user, and issue badge', async () => {

    await gyftieTokenContract.createprof (member8.name, { from: gyftieOracle});
    await gyftieTokenContract.createprof (member9.name, { from: gyftieOracle});

    const beforeMember8Gft = await getGftBalance (member8);
    const beforeMember9Gft = await getGftBalance (member9);

    await gyftieTokenContract.referuser (member8.name, member9.name, { from: member9 });
    await gyftieTokenContract.issuebadge (member9.name, 'identype', 'Identity type badge', { from: gyftieOracle })

    const member8Gft = await getGftBalance(member8)
    const member9Gft = await getGftBalance(member9)

    console.log (" Member 8 GFT: ", member8Gft);
    console.log (" Member 9 GFT: ", member9Gft);

    assert.equal (member8Gft, await addGft(beforeMember8Gft, "1.20000000 GFT"));
    assert.equal (member9Gft, await addGft(beforeMember9Gft, "1.20000000 GFT"));
  });

  // it('TEST 7 :::: Should remove a profile ', async () => {

  //   await gyftieTokenContract.accelunstake (member9.name, { from: gyftieTokenAccount});
  //   await gyftieTokenContract.remprofprep (member9.name, { from: gyftieTokenAccount});
  //   await gyftieTokenContract.removeprof (member9.name, { from: gyftieTokenAccount});

  //   const profiles = await gyftieTokenContract.provider.eos.getTableRows({
  //     code: gyftieTokenAccount.name,
  //     scope: gyftieTokenAccount.name,
  //     table: "profiles2",
  //     lower_bound: member9.name,
  //     limit: 1,
  //     json: true
  //   });
  //   console.log(profiles);

  //   assert.notEqual(profiles.rows[0].account, member9.name);
  // });

  it('TEST 8 :::: Should add an ID hash', async () => {

    await createDefaultBadges();
    await gyftieTokenContract.createprof (member2.name, { from: gyftieOracle});

    const hash = "this is a fake hash";
    await gyftieTokenContract.addhash (member1.name, member2.name, hash, "id expiration", {from: member1 });

    const member2profile = await getProfile (member2);
    console.log (member2profile);
    assert.equal (member2profile.idhash, hash);
  });

  it('TEST 9 :::: It should create a profile and issue tokens to stake', async () => {

    await gyftieTokenContract.createprof (member10.name, { from: gyftieOracle});

    await gyftieTokenContract.isstoskoracl (member10.name, "2.00000000 GFT", "Claim SMS tokens", {from: gyftieOracle });

    const member10profile = await getProfile (member10);
    console.log (member10profile);
    assert.equal (member10profile.staked_balance, "2.00000000 GFT");
  });


  // it('TEST 10 :::: It should place a buy , async () => {

  //   await gyftieTokenContract.createprof (member10.name, { from: gyftieOracle});

  //   await gyftieTokenContract.isstoskoracl (member10.name, "2.00000000 GFT", "Claim SMS tokens", {from: member10 });

  //   const member10profile = await getProfile (member10);
  //   console.log (member10profile);
  //   assert.equal (member10profile.staked_balance, "2.00000000 GFT");
  // });

  it('TEST 10 :::: Handle some basic member promotions', async () => {

    await gyftieTokenContract.setrank (member1.name, 1, { from: gyftieTokenAccount });
    await gyftieTokenContract.voteforuser (member1.name, member2.name, { from: member1 });

    await gyftieTokenContract.createprof (member3.name, { from: gyftieOracle });
    await gyftieTokenContract.voteforuser (member2.name, member3.name, { from: member2 });

    const member1Profile = await getProfile (member1);
    const member2Profile = await getProfile (member2);
    const member3Profile = await getProfile (member3);

    console.log("Member 1 Profile: ", member1Profile);
    console.log("Member 2 Profile: ", member2Profile);
    console.log("Member 3 Profile: ", member3Profile);

    assert.equal (member1Profile.rank, 1);
    assert.equal (member2Profile.rank, 1);
    assert.equal (member3Profile.rank, 2);
    
  });

  it('TEST 11 :::: Handle some advanced member promotions', async () => {

    await gyftieTokenContract.createprof (member11.name, { from: gyftieOracle });
    await gyftieTokenContract.setrank (member11.name, 5, { from: gyftieTokenAccount });

    await gyftieTokenContract.createprof (member12.name, { from: gyftieOracle });
    await gyftieTokenContract.setrank (member12.name, 5, { from: gyftieTokenAccount });

    await gyftieTokenContract.createprof (member13.name, { from: gyftieOracle });
    await gyftieTokenContract.setrank (member13.name, 5, { from: gyftieTokenAccount });

    await gyftieTokenContract.createprof (member14.name, { from: gyftieOracle });
    await gyftieTokenContract.setrank (member14.name, 5, { from: gyftieTokenAccount });

    await gyftieTokenContract.createprof (member15.name, { from: gyftieOracle });
    await gyftieTokenContract.setrank (member15.name, 5, { from: gyftieTokenAccount });

    await gyftieTokenContract.voteforuser (member11.name, member6.name, { from: member11 });
    await gyftieTokenContract.voteforuser (member12.name, member6.name, { from: member12 });
    await gyftieTokenContract.voteforuser (member13.name, member6.name, { from: member13 });

    const member6Profile = await getProfile (member6);
    // const member2Profile = await getProfile (member2);
    // const member3Profile = await getProfile (member3);

    console.log("Member 6 Profile: ", member6Profile);
    // console.log("Member 2 Profile: ", member2Profile);
    // console.log("Member 3 Profile: ", member3Profile);
    
  });

});
