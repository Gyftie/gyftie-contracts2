
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 create '[]' -p gyftietoke22
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 unpause '[]' -p gyftietoke22
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 reset '[]' -p gyftietoke22


cleos -u https://jungle2.cryptolions.io push action gyftietoke22 createprof '["gyftieuser52"]' -p gyftietoke11

cleos -u https://jungle2.cryptolions.io push action gyftietoke22 createbadge '["SMS Verified", "Verified that user can receive SMS messages", "0.12345678 GFT", "info url", "another image", "textsms", "gyftieoracle"]' -p gyftietoke11

cleos -u https://jungle2.cryptolions.io push action gyftietoke22 issuebadge '["gyftieuser52", 0, "User is now SMS Verified"]' -p gyftietoke22
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 unissuebadge '["gyftieuser52", 0]' -p gyftietoke22
cleos -u https://jungle2.cryptolions.io push action gyftietoke22 removeprof '["gyftieuser52"]' -p gyftietoke22


cleos -u https://jungle2.cryptolions.io push action gyftietoke22 setconfig '["gftorderbook","gyftiegyftie","gyftieoracle"]' -p gyftietoke11

cleos -u https://jungle2.cryptolions.io get table gyftietoke22 gyftietoke22 profiles
cleos -u https://jungle2.cryptolions.io get table gyftietoke22 gyftietoke22 badgeaccts
cleos -u https://jungle2.cryptolions.io get table gyftietoke22 gyftietoke22 appstates


cleos -u https://jungle2.cryptolions.io push action eosio updateauth '{
    "account": "gyftietoke22",
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
                    "actor": "gyftietoke22",
                    "permission": "eosio.code"
                },
                "weight": 1
            }
        ],
        "waits": []
    }
}' -p gyftietoke22@owner

cleos -u https://jungle2.cryptolions.io push action eosio updateauth '{
    "account": "gyftietoke22",
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
                    "actor": "gyftietoke22",
                    "permission": "eosio.code"
                },
                "weight": 1
            }
        ],
        "waits": []
    }
}' -p gyftietoke22@owner