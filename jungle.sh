
cleos -u https://jungle2.cryptolions.io push action gyftietoke23 create '[]' -p gyftietoke23
cleos -u https://jungle2.cryptolions.io push action gyftietoke23 unpause '[]' -p gyftietoke23
cleos -u https://jungle2.cryptolions.io push action gyftietoke23 reset '[]' -p gyftietoke23

cleos -u https://jungle2.cryptolions.io push action gyftietoke23 createprof '["gyftieuser52"]' -p gyftietoke11

cleos -u https://jungle2.cryptolions.io push action gyftietoke23 createbadge '["verifysms", "SMS Verified", "Verified that user can receive SMS messages", "0.10000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke23
cleos -u https://jungle2.cryptolions.io push action gyftietoke23 createbadge '["verifyemail", "Email Verified", "Verified that user can receive Emails", "0.20000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke23
cleos -u https://jungle2.cryptolions.io push action gyftietoke23 createbadge '["govtidver", "Government-issued ID Verified", "User has saved hash of Government-issued ID", "0.30000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke23
cleos -u https://jungle2.cryptolions.io push action gyftietoke23 createbadge '["vouchirl", "Vouched for In Real Life (IRL)", "Vouched for by someone in real life", "0.40000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke23
cleos -u https://jungle2.cryptolions.io push action gyftietoke23 createbadge '["buygft", "Purchased GFT", "User has purchased some GFT", "1.00000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke23
cleos -u https://jungle2.cryptolions.io push action gyftietoke23 createbadge '["identified", "Fully identified", "User has completed all 5 onboarding steps", "0.00000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke23

cleos -u https://jungle2.cryptolions.io push action gyftietoke23 issuebadge '["gyftieuser52", 0, "User is now SMS Verified"]' -p gyftietoke23
cleos -u https://jungle2.cryptolions.io push action gyftietoke23 unissuebadge '["gyftieuser52", 0]' -p gyftietoke23
cleos -u https://jungle2.cryptolions.io push action gyftietoke23 accelunstake '["gyftieuser52"]' -p gyftietoke23
cleos -u https://jungle2.cryptolions.io push action gyftietoke23 upgrade '["agyftieuser1"]' -p gyftietoke23

cleos -u https://jungle2.cryptolions.io push action gyftietoke23 removeprof '["gyftieuser52"]' -p gyftietoke23

cleos -u https://jungle2.cryptolions.io push action gyftietoke23 setconfig '["gftorderboo2","gyftiegyftie","gyftieoracle"]' -p gyftietoke23

cleos -u https://jungle2.cryptolions.io get table gyftietoke23 gyftietoke23 profiles
cleos -u https://jungle2.cryptolions.io get table gyftietoke23 gyftietoke23 badgeaccts
cleos -u https://jungle2.cryptolions.io get table gyftietoke23 gyftietoke23 appstates
cleos -u https://jungle2.cryptolions.io get table gyftietoke23 gyftietoke23 badges

cleos -u https://jungle2.cryptolions.io set contract gyftietoke23 gyftie/gyftietoken

cleos -u https://jungle2.cryptolions.io  push action gftorderboo2 setconfig '["gyftietoke23", "eosio.token", "EOS", 4]' -p gftorderboo2
cleos -u https://jungle2.cryptolions.io  push action gftorderboo2 unpause '[]' -p gftorderboo2
cleos -u https://jungle2.cryptolions.io  push action gftorderboo2 setstate '["5.0000 EOS"]' -p gftorderboo2
cleos -u https://jungle2.cryptolions.io  push action gftorderboo2 setrewconfig '[750000, 250000]' -p gftorderboo2

cleos -u https://jungle2.cryptolions.io push action eosio.token transfer '["gyftieuser53", "gftorderboo2", "1.0000 EOS", "should succeed"]' -p gyftieuser53
cleos -u https://jungle2.cryptolions.io push action gyftietoke23 accelunstake '["gyftieuser53"]' -p gyftietoke23
cleos -u https://jungle2.cryptolions.io push action gyftietoke23 transfer '["gyftieuser53", "gftorderboo2", "0.00010000 GFT", "should succeed"]' -p gyftieuser53

cleos -u https://jungle2.cryptolions.io push action gftorderboo2 limitbuygft '["gyftieuser53", "0.0100 EOS", "0.00000100 GFT"]' -p gyftieuser53
cleos -u https://jungle2.cryptolions.io push action gftorderboo2 marketsell '["gyftieuser53", "0.00001000 GFT"]' -p gyftieuser53


# cleos push action gftorderbook addbucket '[0, 10000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[10001, 20000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[20001, 30000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[30001, 50000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[50001, 70000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[70001, 100000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[100001, 150000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[150001, 200000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[200001, 300000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[300001, 500000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[500001, 700000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[700001, 1000000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[1000001, 2000000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[2000001, 3000000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[3000001, 4000000]' -p gftorderbook
# cleos push action gftorderbook addbucket '[4000001, 5000000]' -p gftorderbook


cleos -u https://jungle2.cryptolions.io push action eosio updateauth '{
    "account": "gyftietoke23",
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
        "accounts": [
            {
                "permission": {
                    "actor": "gyftietoke23",
                    "permission": "eosio.code"
                },
                "weight": 1
            }
        ],
        "waits": []
    }
}' -p gyftietoke23@owner

cleos -u https://jungle2.cryptolions.io push action eosio updateauth '{
    "account": "gyftietoke23",
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
        "accounts": [
            {
                "permission": {
                    "actor": "gyftietoke23",
                    "permission": "eosio.code"
                },
                "weight": 1
            }
        ],
        "waits": []
    }
}' -p gyftietoke23@owner