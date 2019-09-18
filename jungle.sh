
# new accounts for Gyftie Jungle
Private key: 5KdLR4MJoJBaMcx5hXLn3qh2WWBATUZGSPnHcy46CqkbHcQZkWS
Public key: EOS8QZxg4dy5Ujiuz2v1agu1vNQBWiou3BJNMPiBomcFHMn79HPoa

gyftietoke24
gftorderboo4

usergyftie11
usergyftie12
usergyftie13
usergyftie14
usergyftie15

cleos -u https://jungle2.cryptolions.io set contract gyftietoke24 gyftie/gyftietoken
cleos -u https://jungle2.cryptolions.io set contract gftorderboo4 gyftie/gftorderbook

cleos -u https://jungle2.cryptolions.io push action gyftietoke24 setconfig '["gftorderboo4","gyftiegyftie","gyftieoracle"]' -p gyftietoke24



cleos -u https://jungle2.cryptolions.io push action gyftietoke24 create '[]' -p gyftietoke24
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 unpause '[]' -p gyftietoke24
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 reset '[]' -p gyftietoke24

cleos -u https://jungle2.cryptolions.io push action gyftietoke24 createprof '["usergyftie12"]' -p gyftieoracle

cleos -u https://jungle2.cryptolions.io push action gyftietoke24 createbadge '["verifysms", "SMS Verified", "Verified that user can receive SMS messages", "0.10000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke24
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 createbadge '["verifyemail", "Email Verified", "Verified that user can receive Emails", "0.20000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke24
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 createbadge '["govtidver", "Government-issued ID Verified", "User has saved hash of Government-issued ID", "0.30000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke24
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 createbadge '["vouchirl", "Vouched for In Real Life (IRL)", "Vouched for by someone in real life", "0.40000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke24
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 createbadge '["buygft", "Purchased GFT", "User has purchased some GFT", "1.00000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke24
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 createbadge '["identified", "Fully identified", "User has completed all 5 onboarding steps", "0.00000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke24

cleos -u https://jungle2.cryptolions.io push action gyftietoke24 issuebadge '["gyftietoke24", "verifysms", "User is now SMS Verified"]' -p gyftietoke24
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 issuebadge '["gyftietoke24", "verifyemail", "User is now SMS Verified"]' -p gyftietoke24
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 issuebadge '["gyftietoke24", "govtidver", "User is now SMS Verified"]' -p gyftietoke24
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 issuebadge '["gyftietoke24", "vouchirl", "User is now SMS Verified"]' -p gyftietoke24
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 issuebadge '["gyftietoke24", "identified", "User is now SMS Verified"]' -p gyftietoke24

cleos -u https://jungle2.cryptolions.io push action gyftietoke24 unissuebadge '["usergyftie11", 0]' -p gyftietoke24
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 accelunstake '["usergyftie11"]' -p gyftietoke24
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 upgrade '["agyftieuser1"]' -p gyftietoke24

cleos -u https://jungle2.cryptolions.io push action gyftietoke24 removeprof '["usergyftie11"]' -p gyftietoke24

cleos -u https://jungle2.cryptolions.io push action gyftietoke24 addcomment '["usergyftie12", "profile", -1, "usergyftie11", -1, "I met usergyftie12 in central park"]' -p usergyftie12
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 editcomment '[0, "Actually, it was a different park."]' -p usergyftie12
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 propose '["usergyftie11", "My Proposal to Solve Climate Change", "This is a really good idea that is going to do amazing things!"]' -p usergyftie11
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 votefor '[4, "usergyftie12"]' -p usergyftie12

cleos -u https://jungle2.cryptolions.io get table gyftietoke24 gyftietoke24 profiles
cleos -u https://jungle2.cryptolions.io get table gyftietoke24 gyftietoke24 badgeaccts
cleos -u https://jungle2.cryptolions.io get table gyftietoke24 gyftietoke24 appstates
cleos -u https://jungle2.cryptolions.io get table gyftietoke24 gyftietoke24 badges


cleos -u https://jungle2.cryptolions.io set contract -sjd -x 186400 gyftietoke24 gyftie/gyftietoken > gyftietoken_deploy.json
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 proposetrx ./gyftietoken_deploy.json -p usergyftie11
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 votefor '["usergyftie11", 8]' -p usergyftie11
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 votefor '["usergyftie13", 8]' -p usergyftie13

 "proposer": "usergyftie11",
  "proposal_name": "upgrade",
  "notes": "upgrade to addkey action",
  "trx": {



cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 setconfig '["gyftietoke24", "eosio.token", "EOS", 4]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 unpause '[]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 setstate '["3.3400 EOS"]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 setrewconfig '[750000, 250000]' -p gftorderboo4

cleos -u https://jungle2.cryptolions.io push action eosio.token transfer '["usergyftie11", "gftorderboo4", "50.0000 EOS", "should succeed"]' -p usergyftie11
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 transfer '["usergyftie11", "gftorderboo4", "0.80000000 GFT", "should succeed"]' -p usergyftie11

cleos -u https://jungle2.cryptolions.io push action gyftietoke24 accelunstake '["usergyftie11"]' -p gyftietoke24
cleos -u https://jungle2.cryptolions.io push action gyftietoke24 transfer '["usergyftie11", "gftorderboo4", "0.00010000 GFT", "should succeed"]' -p usergyftie11

cleos -u https://jungle2.cryptolions.io push action gftorderboo4 limitbuygft '["usergyftie11", "0.0100 EOS", "0.00000100 GFT"]' -p usergyftie11
cleos -u https://jungle2.cryptolions.io push action gftorderboo4 marketsell '["usergyftie11", "0.00001000 GFT"]' -p usergyftie11


cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[0, 10000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[10001, 20000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[20001, 30000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[30001, 50000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[50001, 70000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[70001, 100000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[100001, 150000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[150001, 200000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[200001, 300000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[300001, 500000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[500001, 700000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[700001, 1000000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[1000001, 2000000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[2000001, 3000000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[3000001, 4000000]' -p gftorderboo4
cleos -u https://jungle2.cryptolions.io  push action gftorderboo4 addbucket '[4000001, 5000000]' -p gftorderboo4


cleos -u https://jungle2.cryptolions.io push action eosio updateauth '{
    "account": "gftorderboo4",
    "permission": "active",
    "parent": "owner",
    "auth": {
        "keys": [
            {
                "key": "EOS8QZxg4dy5Ujiuz2v1agu1vNQBWiou3BJNMPiBomcFHMn79HPoa",
                "weight": 1
            }
        ],
        "threshold": 1,
        "accounts": [
            {
                "permission": {
                    "actor": "gftorderboo4",
                    "permission": "eosio.code"
                },
                "weight": 1
            }
        ],
        "waits": []
    }
}' -p gftorderboo4@owner

cleos -u https://jungle2.cryptolions.io push action eosio updateauth '{
    "account": "gftorderboo4",
    "permission": "owner",
    "parent": "",
    "auth": {
        "keys": [
            {
                "key": "EOS8QZxg4dy5Ujiuz2v1agu1vNQBWiou3BJNMPiBomcFHMn79HPoa",
                "weight": 1
            }
        ],
        "threshold": 1,
        "accounts": [
            {
                "permission": {
                    "actor": "gftorderboo4",
                    "permission": "eosio.code"
                },
                "weight": 1
            }
        ],
        "waits": []
    }
}' -p gftorderboo4@owner

EOS8QZxg4dy5Ujiuz2v1agu1vNQBWiou3BJNMPiBomcFHMn79HPoa


cleos -u https://jungle2.cryptolions.io push action eosio updateauth '{
    "account": "gyftieoracle",
    "permission": "active",
    "parent": "owner",
    "auth": {
        "keys": [
            {
                "key": "EOS85AboyypCNfuENiDo8986J3tGiXMQ46m1eTimB1GDzKvVHNqWj",
                "weight": 1
            }
        ],
        "threshold": 1,
        "accounts": [],
        "waits": []
    }
}' -p gftorderboo4@owner

cleos -u https://jungle2.cryptolions.io push action eosio updateauth '{
    "account": "gftorderboo4",
    "permission": "owner",
    "parent": "",
    "auth": {
        "keys": [
            {
                "key": "EOS85AboyypCNfuENiDo8986J3tGiXMQ46m1eTimB1GDzKvVHNqWj",
                "weight": 1
            }
        ],
        "threshold": 1,
        "accounts": [],
        "waits": []
    }
}' -p gftorderboo4@owner