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
let member1, member2, member3, member4, member5, gyftiegyftie;

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

async function getGftBalances(member) {

    const balances = await gyftieTokenContract.provider.eos.getTableRows({
        code: gyftieTokenAccount.name,
        scope: gyftieTokenAccount.name,
        table: "profiles",
        lower_bound: member.name,
        limit: 1,
        json: true
    });

    const accounts = await gyftieTokenContract.provider.eos.getTableRows({
        code: gyftieTokenAccount.name,
        scope: member.name,
        table: "accounts",
        json: true
    });

    if (accounts.rows[0] === undefined) {
        assert.equal(balances.rows[0].gft_balance, "0.00000000 GFT");
        return balances.rows[0].gft_balance;
    }
    assert.equal (balances.rows[0].gft_balance, accounts.rows[0].balance);
    return accounts.rows[0].balance;
}

async function addGft (gft1, gft2) {
    // console.log ('typeof gft1: ', typeof gft1)
    const gftFloat1 = await assetToFloat(gft1, 8)
    // console.log ('gftFloat1         :    ', gftFloat1);
    // console.log ('typeof gftFloat1  :', typeof gftFloat1);
    
    const gftFloat2 = await assetToFloat(gft2, 8)
    // console.log ('gftFloat2         :    ', gftFloat2);
    // console.log ('typeof gftFloat2  :', typeof gftFloat2);

    const sumGft = parseFloat(gftFloat1) + parseFloat(gftFloat2) + ' GFT'
    // console.log ('Sum GFT: ', sumGft);
    return sumGft;
}

describe("Gyftie Testing", function() {
  this.timeout(150000);

  let accounts;

  before(async () => {
    accounts = await eoslime.Account.createRandoms(10);
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
    await gyftieTokenContract.setstate(222, 222, 2, 1, {from: gyftieTokenAccount });
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
  });

  it("Should gyft to member 1", async () => {

    // await gyftieTokenContract.gyft2(gyftieTokenAccount.name, member1.name, "idhash", "friend", "idexpiration", { from: gyftieTokenAccount });
    await gyftieTokenContract.createprof (member1.name, { from: gyftieOracle });

    const profiles = await gyftieTokenContract.provider.eos.getTableRows({
      code: gyftieTokenAccount.name,
      scope: gyftieTokenAccount.name,
      table: "profiles",
      lower_bound: member1.name,
      limit: 1,
      json: true
    });
    console.log(profiles);

    assert.equal(profiles.rows.length, 1);
    assert.equal(profiles.rows[0].account, member1.name);
  });

  it("Should create and assign a badge", async () => {

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

    assert.equal(badges.rows.length, 1);

    const beforeBalance = await getGftBalances (member1)
    console.log('Before Balance: ', beforeBalance);
    console.log('Expected GFT Balance, post reward: ', await addGft(beforeBalance, badges.rows[0].reward))

    await gyftieTokenContract.issuebadge (member1.name, 'badgeid1', 'First issue of a badge in automated test.', { from: gyftieOracle })

    const badgeaccts = await gyftieTokenContract.provider.eos.getTableRows({
        code: gyftieTokenAccount.name,
        scope: gyftieTokenAccount.name,
        table: "badgeaccts",
        json: true
    });
    const afterBalance = await getGftBalances (member1);
    console.log('After balance: ', afterBalance)

    assert.equal(badgeaccts.rows.length, 1);
    assert.equal(badgeaccts.rows[0].badge_holder, member1.name);

    assert.equal(await addGft(beforeBalance, badges.rows[0].reward), afterBalance);
  });

  it('Should create a new profile, add badge, then remove profile', async () => {

    await gyftieTokenContract.createprof (member2.name, { from: gyftieOracle});
    await gyftieTokenContract.createbadge ('badgeid2', 'Badge Name #2', 'Second Badge',
        '1.00000000 GFT', 'info url', 'another image', 'icon name', gyftieOracle.name, 2, { from: gyftieTokenAccount });

    await gyftieTokenContract.issuebadge (member2.name, 'badgeid2', 'Second badge for create/remove testing.', { from: gyftieOracle })

    const beforeTotalGft = await gyftieTokenContract.provider.eos.getTableRows({
        code: gyftieTokenAccount.name,
        scope: "GFT",
        table: "stat",
        json: true
    });
    console.log (" Before GFT Supply: ", beforeTotalGft.rows[0].supply);
    const beforeMember2Bals = await getGftBalances(member2)
    console.log (" Destroying profile for : ", member2.name, "; balance of: ", beforeMember2Bals);

    await gyftieTokenContract.removeprof (member2.name, { from: gyftieTokenAccount });

    const afterTotalGft = await gyftieTokenContract.provider.eos.getTableRows({
        code: gyftieTokenAccount.name,
        scope: "GFT",
        table: "stat",
        json: true
    });

    console.log (" After GFT Supply: ", afterTotalGft.rows[0].supply);

    assert.equal (await addGft(afterTotalGft.rows[0].supply, beforeMember2Bals), beforeTotalGft.rows[0].supply);
  });

  it('Should create a new identity badge, add referral, and issue badge', async () => {

    await gyftieTokenContract.createprof (member2.name, { from: gyftieOracle});
    await gyftieTokenContract.createprof (member3.name, { from: gyftieOracle});

    await gyftieTokenContract.createbadge ('identype', 'Identity Type Badge', 'Second Badge',
        '1.20000000 GFT', 'info url', 'another image', 'icon name', gyftieOracle.name, 1, { from: gyftieTokenAccount });

    await gyftieTokenContract.createbadge ('identified', 'Identified Badge', 'Second Badge',
        '1.50000000 GFT', 'info url', 'another image', 'icon name', gyftieOracle.name, 1, { from: gyftieTokenAccount });

    await gyftieTokenContract.issuebadge (member2.name, 'identified', 'Legit identity badge', { from: gyftieOracle })
    await gyftieTokenContract.referuser (member2.name, member3.name);
    await gyftieTokenContract.issuebadge (member3.name, 'identype', 'Identity type badge', { from: gyftieOracle })

    const member2Gft = await getGftBalances(member2)
    const member3Gft = await getGftBalances(member3)

    console.log (" Member 2 GFT: ", member2Gft);
    console.log (" Member 3 GFT: ", member3Gft);

    assert.equal ("3.90000000 GFT", member2Gft);
    assert.equal ("1.20000000 GFT", member3Gft);
  });

  it('Should create a new identity badge, add referral from unverified user, and issue badge', async () => {

    await gyftieTokenContract.createprof (member4.name, { from: gyftieOracle});

    await gyftieTokenContract.referuser (member2.name, member4.name);
    await gyftieTokenContract.issuebadge (member4.name, 'identype', 'Identity type badge', { from: gyftieOracle })

    const member2Gft = await getGftBalances(member2)
    const member4Gft = await getGftBalances(member4)

    console.log (" Member 2 GFT: ", member2Gft);
    console.log (" Member 4 GFT: ", member4Gft);

    assert.equal ("6.30000000 GFT", member2Gft);
    assert.equal ("1.20000000 GFT", member4Gft);
  });

});
