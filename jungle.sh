
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 create '[]' -p gyftietoke22
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 unpause '[]' -p gyftietoke22
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 reset '[]' -p gyftietoke22

cleos -u https://jungle2.cryptolions.io push action gyftietoke22 createprof '["gyftieuser52"]' -p gyftietoke11

cleos -u https://jungle2.cryptolions.io push action gyftietoke22 createbadge '["verifysms", "SMS Verified", "Verified that user can receive SMS messages", "0.10000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke22
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 createbadge '["verifyemail", "Email Verified", "Verified that user can receive Emails", "0.20000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke22
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 createbadge '["govtidver", "Government-issued ID Verified", "User has saved hash of Government-issued ID", "0.30000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke22
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 createbadge '["vouchirl", "Vouched for In Real Life (IRL)", "Vouched for by someone in real life", "0.40000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke22
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 createbadge '["buygft", "Purchased GFT", "User has purchased some GFT", "1.00000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke22
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 createbadge '["identified", "Fully identified", "User has completed all 5 onboarding steps", "0.00000000 GFT", "info url", "another image", "textsms", "gyftieoracle", 1]' -p gyftietoke22

cleos -u https://jungle2.cryptolions.io push action gyftietoke22 issuebadge '["gyftieuser52", 0, "User is now SMS Verified"]' -p gyftietoke22
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 unissuebadge '["gyftieuser52", 0]' -p gyftietoke22
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 accelunstake '["gyftieuser52"]' -p gyftietoke22

cleos -u https://jungle2.cryptolions.io push action gyftietoke22 removeprof '["gyftieuser52"]' -p gyftietoke22

cleos -u https://jungle2.cryptolions.io push action gyftietoke22 setconfig '["gftorderbook","gyftiegyftie","gyftieoracle"]' -p gyftietoke22

cleos -u https://jungle2.cryptolions.io get table gyftietoke22 gyftietoke22 profiles
cleos -u https://jungle2.cryptolions.io get table gyftietoke22 gyftietoke22 badgeaccts
cleos -u https://jungle2.cryptolions.io get table gyftietoke22 gyftietoke22 appstates
cleos -u https://jungle2.cryptolions.io get table gyftietoke22 gyftietoke22 badges


cleos -u https://jungle2.cryptolions.io  push action gftorderboo2 setconfig '["gyftietoke22", "eosio.token", "EOS", 4]' -p gftorderboo2
cleos -u https://jungle2.cryptolions.io  push action gftorderboo2 unpause '[]' -p gftorderboo2
cleos -u https://jungle2.cryptolions.io  push action gftorderboo2 setstate '["5.0000 EOS"]' -p gftorderboo2
cleos -u https://jungle2.cryptolions.io  push action gftorderboo2 setrewconfig '[750000, 250000]' -p gftorderboo2

cleos -u https://jungle2.cryptolions.io push action eosio.token transfer '["gyftieuser53", "gftorderboo2", "1.0000 EOS", "should succeed"]' -p gyftieuser53
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 accelunstake '["gyftieuser53"]' -p gyftietoke22
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 transfer '["gyftieuser53", "gftorderboo2", "0.00010000 GFT", "should succeed"]' -p gyftieuser53

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
    "account": "gftorderboo2",
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
                    "actor": "gftorderboo2",
                    "permission": "eosio.code"
                },
                "weight": 1
            }
        ],
        "waits": []
    }
}' -p gftorderboo2@owner

cleos -u https://jungle2.cryptolions.io push action eosio updateauth '{
    "account": "gftorderboo2",
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
                    "actor": "gftorderboo2",
                    "permission": "eosio.code"
                },
                "weight": 1
            }
        ],
        "waits": []
    }
}' -p gftorderboo2@owner