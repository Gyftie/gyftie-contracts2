cleos -u https://eos.greymass.com set contract -sjd -x 186400 gyftietokens gyftie/gyftietoken/ > gyftietoken_deploy.json
cleos -u https://eos.greymass.com multisig propose_trx redeploy '[{"actor": "gftma.x", "permission": "active"}, {"actor": "danielflora3", "permission": "active"}]' ./gyftietoken_deploy.json gftma.x
cleos -u https://eos.greymass.com multisig approve gftma.x redeploy '{"actor": "gftma.x", "permission": "active"}' -p gftma.x

cleos -u https://eos.greymass.com set contract -sjd -x 186400 gftorderbook gyftie/gftorderbook/ > gftorderbook_deploy.json
cleos -u https://eos.greymass.com multisig propose_trx ordbookdep '[{"actor": "gftma.x", "permission": "active"}, {"actor": "danielflora3", "permission": "active"}]' ./gftorderbook_deploy.json gftma.x
cleos -u https://eos.greymass.com multisig approve gftma.x ordbookdep '{"actor": "gftma.x", "permission": "active"}' -p gftma.x




cleos -u https://eos.greymass.com  push action gyftmultisig addproposal '["gftma.x", "amandarachel", "redeploy", "functionality for self sovereign contracts", "https://github.com/gyftie/gyftie-contracts2/commit/90bb1af6c0c80bab8921f0579e2a4fd850abd2cd"]' -p gftma.x


cleos -u https://eos.greymass.com  push action gyftmultisig addproposal '["gftma.x", "amandarachel", "ordbookdep", "GFT Order Book - redeploy", "https://github.com/gyftie/gyftie-contracts2/commit/0730bd33ff0d252d8f3eef718bec09e6cdfe3962"]' -p gftma.x




cleos -u https://eos.greymass.com push action -sjd -x 86400 gyftietokens setconfig '["gftorderbook", "gyftiegyftie", "gyftieoracle"]' -p gyftietokens > gyftietokens_setconfig.json
cleos -u https://eos.greymass.com multisig propose_trx setconfig '[{"actor": "gftma.x", "permission": "active"}, {"actor": "amandarachel", "permission": "active"}]' ./gyftietokens_setconfig.json gftma.x
cleos -u https://eos.greymass.com  push action gyftmultisig addproposal '["gftma.x", "amandarachel", "setconfig", "Do this one last", "No Link"]' -p gftma.x
cleos -u https://eos.greymass.com multisig approve gftma.x setconfig '{"actor": "gftma.x", "permission": "active"}' -p gftma.x





cleos -u https://eos.greymass.com set contract -sjd -x 186400 gyftietokens gyftie/gyftietoken/ > gyftietoken_deploy.json
cleos -u https://eos.greymass.com multisig propose_trx redeploy2 '[{"actor": "gftma.x", "permission": "active"}, {"actor": "amandarachel", "permission": "active"}]' ./gyftietoken_deploy.json gftma.x
cleos -u https://eos.greymass.com  push action gyftmultisig addproposal '["gftma.x", "amandarachel", "redeploy2", "updated to the new proposal structure", "https://github.com/gyftie/gyftie-contracts2/commit/0904aaaf713de7c6a9c987aa3428490faa96ced0"]' -p gftma.x
cleos -u https://eos.greymass.com multisig approve gftma.x redeploy2 '{"actor": "gftma.x", "permission": "active"}' -p gftma.x


cleos -u https://eos.greymass.com set contract -sjd -x 186400 gftorderbook gyftie/gftorderbook/ > gftorderbook_deploy.json
cleos -u https://eos.greymass.com multisig propose_trx ordbookdep '[{"actor": "gftma.x", "permission": "active"}, {"actor": "danielflora3", "permission": "active"}]' ./gftorderbook_deploy.json gftma.x
cleos -u https://eos.greymass.com  push action gyftmultisig addproposal '["gftma.x", "danielflora3", "ordbookdep", "GFT Order Book - redeploy", "https://github.com/gyftie/gyftie-contracts2/commit/0730bd33ff0d252d8f3eef718bec09e6cdfe3962"]' -p gftma.x
cleos -u https://eos.greymass.com multisig approve gftma.x ordbookdep '{"actor": "gftma.x", "permission": "active"}' -p gftma.x


cleos -u https://eos.greymass.com push action -sjd -x 86400 gyftietokens setconfig '["gftorderbook", "gyftiegyftie", "gyftieoracle"]' -p gyftietokens > gyftietokens_setconfig.json
cleos -u https://eos.greymass.com multisig propose_trx setconfig '[{"actor": "gftma.x", "permission": "active"}, {"actor": "danielflora3", "permission": "active"}]' ./gyftietokens_setconfig.json gftma.x
cleos -u https://eos.greymass.com  push action gyftmultisig addproposal '["gftma.x", "danielflora3", "setconfig", "Do this one last", "No Link"]' -p gftma.x
cleos -u https://eos.greymass.com multisig approve gftma.x setconfig '{"actor": "gftma.x", "permission": "active"}' -p gftma.x


cleos -u https://eos.greymass.com push action -sjd -x 86400 gyftietokens unpause '[]' -p gyftietokens > gyftietokens_unpause.json
cleos -u https://eos.greymass.com multisig propose_trx unpause '[{"actor": "gftma.x", "permission": "active"}, {"actor": "danielflora3", "permission": "active"}]' ./gyftietokens_unpause.json gftma.x
cleos -u https://eos.greymass.com push action gyftmultisig addproposal '["gftma.x", "danielflora3", "unpause", "Unpause", "No Link"]' -p gftma.x
cleos -u https://eos.greymass.com multisig approve gftma.x unpause '{"actor": "gftma.x", "permission": "active"}' -p gftma.x

cleos -u https://eos.greymass.com push action -sjd -x 86400 gftorderbook unpause '[]' -p gftorderbook >  gftorderbook_unpause.json
cleos -u https://eos.greymass.com multisig propose_trx unpauseb '[{"actor": "gftma.x", "permission": "active"}, {"actor": "danielflora3", "permission": "active"}]' ./gftorderbook_unpause.json gftma.x
cleos -u https://eos.greymass.com push action gyftmultisig addproposal '["gftma.x", "danielflora3", "unpauseb", "Unpause", "No Link"]' -p gftma.x
cleos -u https://eos.greymass.com multisig approve gftma.x unpauseb '{"actor": "gftma.x", "permission": "active"}' -p gftma.x



cleos -u https://eos.greymass.com push action gyftietokens createbadge '["verifysms", "SMS Verified", "Verified that user can receive SMS messages", "0.10000000 GFT", "", "", "textsms", "gyftieoracle", 1]' -p gftma.x
cleos -u https://eos.greymass.com push action gyftietokens createbadge '["verifyemail", "Email Verified", "Verified that user can receive Emails", "0.20000000 GFT", "", "", "email", "gyftieoracle", 1]' -p gftma.x
cleos -u https://eos.greymass.com push action gyftietokens createbadge '["govtidver", "Government-issued ID Verified", "User has saved hash of Government-issued ID on chain for future verification", "0.30000000 GFT", "", "", "portrait", "gyftieoracle", 1]' -p gftma.x
cleos -u https://eos.greymass.com push action gyftietokens createbadge '["vouchirl", "Vouched for In Real Life (IRL)", "Someone in real life has vouched for user", "0.40000000 GFT", "", "", "group", "gyftieoracle", 1]' -p gftma.x
cleos -u https://eos.greymass.com push action gyftietokens createbadge '["buygft", "Purchased GFT", "User has purchased GFT", "1.00000000 GFT", "", "", "local_grocery", "gyftieoracle", 1]' -p gftma.x
cleos -u https://eos.greymass.com push action gyftietokens createbadge '["identified", "Fully identified", "User has completed all 5 onboarding steps", "0.00000000 GFT", "", "", "how_to_reg", "gyftieoracle", 1]' -p gftma.x

cleos -u https://eos.greymass.com push action gyftietokens issuebadge '["gftma.x", "verifysms", "User is now SMS Verified"]' -p gyftieoracle

cleos -u https://eos.greymass.com push action gyftietokens accelunstake '["purposebuilt"]' -p gftma.x
cleos -u https://eos.greymass.com push action gyftietokens remprofprep '["purposebuilt"]' -p gftma.x
cleos -u https://eos.greymass.com push action gyftietokens removeprof '["purposebuilt"]' -p gftma.x


"supply": "9684.65713013 GFT",

cleos -u https://api.telos.kitchen push action -sjd -x 86400 eosio.token transfer '["seedsgifting", "hyphanewyork", "1.0000 TLOS", "test trx"]' -p seedssigners > test_transfer.json
cleos -u https://api.telos.kitchen multisig proposetrx testtrx '[{"actor": "hyphanewyork", "permission": "active"},{"actor": "illumination", "permission": "active"},{"actor": "sevenflash42", "permission": "active"},{"actor": "tchoptelacc1", "permission": "active"},{"actor": "thealchemist", "permission": "active"}]' ./test_transfer.json hyphanewyork
cleos -u https://api.telos.kitchen multisig approve hyphanewyork testtrx '{"actor": "hyphanewyork", "permission": "active"}' -p hyphanewyork
cleos -u https://api.telos.kitchen multisig exec hyphanewyork testtrx 


cleos -u https://eos.greymass.com push action -sjd -x 86400 eosio.token transfer '["thehyphabank", "vishalvishal", "651.0417 EOS", "$2500 USD @ $3.84/EOS, see proposal hypha1.....2g"]' -p thehyphabank > vishal_transfer.json
cleos -u https://eos.greymass.com multisig propose_trx vishal '[{"actor": "amazonjungle", "permission": "active"},{"actor": "illum1nation", "permission": "active"},{"actor": "sevenflash42", "permission": "active"},{"actor": "tchopeosacc1", "permission": "active"},{"actor": "onealchemist", "permission": "active"}]' ./vishal_transfer.json amazonjungle
cleos -u https://eos.greymass.com multisig approve amazonjungle vishal '{"actor": "amazonjungle", "permission": "active"}' -p amazonjungle
cleos -u https://eos.greymass.com multisig exec amazonjungle vishal 





delete data in AWS
check orders
accelerate unstake
removeprof


cleos -u https://eos.greymass.com get table -l 1 --lower "digiscarcity" gyftietokens gyftietokens profiles
cleos -u https://eos.greymass.com get table gyftietokens digiscarcity accounts
cleos -u https://eos.greymass.com get table gyftietokens GFT stat
➜ cleos -u https://eos.greymass.com get table gyftietokens GFT stat

cleos -u https://eos.greymass.com get table --lower "purposebuilt" gyftietokens gyftietokens profiles



cleos -u https:



cleos -u https://test.telos.kitchen push action gyftietokens issue '["gyftietokens", "100.00000000 TLOSGFT", "memo"]' -p gyftietokens
cleos -u https://test.telos.kitchen push action gyftietokens transfer '["gyftietokens", "agyftieuser2", "100.00000000 TLOSGFT", "memo"]' -p gyftietokens
cleos -u https://test.telos.kitchen push action gyftietokens transfer '["agyftieuser2", "gyftieassets", "1.00000000 TLOSGFT", "memo"]' -p agyftieuser2