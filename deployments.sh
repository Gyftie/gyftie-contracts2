cleos -u https://api.eosnewyork.io set contract -sjd -x 186400 gyftietokens gyftie/gyftietoken/ > gyftietoken_deploy.json
cleos -u https://api.eosnewyork.io multisig propose_trx redeploy2 '[{"actor": "gftma.x", "permission": "active"}, {"actor": "amandarachel", "permission": "active"}]' ./gyftietoken_deploy.json gftma.x
cleos -u https://api.eosnewyork.io  push action gyftmultisig addproposal '["gftma.x", "amandarachel", "redeploy2", "Too many changes to list - initial deployment of Gyftie 2.0", "https://github.com/gyftie/gyftie-contracts2/commit/0730bd33ff0d252d8f3eef718bec09e6cdfe3962"]' -p gftma.x
cleos -u https://api.eosnewyork.io multisig approve gftma.x redeploy2 '{"actor": "gftma.x", "permission": "active"}' -p gftma.x


cleos -u https://api.eosnewyork.io set contract -sjd -x 186400 gftorderbook gyftie/gftorderbook/ > gftorderbook_deploy.json
cleos -u https://api.eosnewyork.io multisig propose_trx ordbookdep '[{"actor": "gftma.x", "permission": "active"}, {"actor": "amandarachel", "permission": "active"}]' ./gftorderbook_deploy.json gftma.x
cleos -u https://api.eosnewyork.io  push action gyftmultisig addproposal '["gftma.x", "amandarachel", "ordbookdep", "GFT Order Book - redeploy", "https://github.com/gyftie/gyftie-contracts2/commit/0730bd33ff0d252d8f3eef718bec09e6cdfe3962"]' -p gftma.x
cleos -u https://api.eosnewyork.io multisig approve gftma.x ordbookdep '{"actor": "gftma.x", "permission": "active"}' -p gftma.x




cleos -u https://api.eosnewyork.io push action -sjd -x 86400 gyftietokens setconfig '["gftorderbook", "gyftiegyftie", "gyftieoracle"]' -p gyftietokens > gyftietokens_setconfig.json
cleos -u https://api.eosnewyork.io multisig propose_trx setconfig '[{"actor": "gftma.x", "permission": "active"}, {"actor": "amandarachel", "permission": "active"}]' ./gyftietokens_setconfig.json gftma.x
cleos -u https://api.eosnewyork.io  push action gyftmultisig addproposal '["gftma.x", "amandarachel", "setconfig", "Do this one last", "No Link"]' -p gftma.x
cleos -u https://api.eosnewyork.io multisig approve gftma.x setconfig '{"actor": "gftma.x", "permission": "active"}' -p gftma.x





cleos -u https://api.eosnewyork.io set contract -sjd -x 186400 gyftietokens gyftie/gyftietoken/ > gyftietoken_deploy.json
cleos -u https://api.eosnewyork.io multisig propose_trx redeploy2 '[{"actor": "gftma.x", "permission": "active"}, {"actor": "amandarachel", "permission": "active"}]' ./gyftietoken_deploy.json gftma.x
cleos -u https://api.eosnewyork.io  push action gyftmultisig addproposal '["gftma.x", "amandarachel", "redeploy2", "updated to the new proposal structure", "https://github.com/gyftie/gyftie-contracts2/commit/0904aaaf713de7c6a9c987aa3428490faa96ced0"]' -p gftma.x
cleos -u https://api.eosnewyork.io multisig approve gftma.x redeploy2 '{"actor": "gftma.x", "permission": "active"}' -p gftma.x


cleos -u https://api.eosnewyork.io set contract -sjd -x 186400 gftorderbook gyftie/gftorderbook/ > gftorderbook_deploy.json
cleos -u https://api.eosnewyork.io multisig propose_trx ordbookdep '[{"actor": "gftma.x", "permission": "active"}, {"actor": "danielflora3", "permission": "active"}]' ./gftorderbook_deploy.json gftma.x
cleos -u https://api.eosnewyork.io  push action gyftmultisig addproposal '["gftma.x", "danielflora3", "ordbookdep", "GFT Order Book - redeploy", "https://github.com/gyftie/gyftie-contracts2/commit/0730bd33ff0d252d8f3eef718bec09e6cdfe3962"]' -p gftma.x
cleos -u https://api.eosnewyork.io multisig approve gftma.x ordbookdep '{"actor": "gftma.x", "permission": "active"}' -p gftma.x


cleos -u https://api.eosnewyork.io push action -sjd -x 86400 gyftietokens setconfig '["gftorderbook", "gyftiegyftie", "gyftieoracle"]' -p gyftietokens > gyftietokens_setconfig.json
cleos -u https://api.eosnewyork.io multisig propose_trx setconfig '[{"actor": "gftma.x", "permission": "active"}, {"actor": "danielflora3", "permission": "active"}]' ./gyftietokens_setconfig.json gftma.x
cleos -u https://api.eosnewyork.io  push action gyftmultisig addproposal '["gftma.x", "danielflora3", "setconfig", "Do this one last", "No Link"]' -p gftma.x
cleos -u https://api.eosnewyork.io multisig approve gftma.x setconfig '{"actor": "gftma.x", "permission": "active"}' -p gftma.x


cleos -u https://api.eosnewyork.io push action -sjd -x 86400 gyftietokens unpause '[]' -p gyftietokens > gyftietokens_unpause.json
cleos -u https://api.eosnewyork.io multisig propose_trx unpause '[{"actor": "gftma.x", "permission": "active"}, {"actor": "danielflora3", "permission": "active"}]' ./gyftietokens_unpause.json gftma.x
cleos -u https://api.eosnewyork.io push action gyftmultisig addproposal '["gftma.x", "danielflora3", "unpause", "Unpause", "No Link"]' -p gftma.x
cleos -u https://api.eosnewyork.io multisig approve gftma.x unpause '{"actor": "gftma.x", "permission": "active"}' -p gftma.x

cleos -u https://api.eosnewyork.io push action -sjd -x 86400 gftorderbook unpause '[]' -p gftorderbook >  gftorderbook_unpause.json
cleos -u https://api.eosnewyork.io multisig propose_trx unpauseb '[{"actor": "gftma.x", "permission": "active"}, {"actor": "danielflora3", "permission": "active"}]' ./gftorderbook_unpause.json gftma.x
cleos -u https://api.eosnewyork.io push action gyftmultisig addproposal '["gftma.x", "danielflora3", "unpauseb", "Unpause", "No Link"]' -p gftma.x
cleos -u https://api.eosnewyork.io multisig approve gftma.x unpauseb '{"actor": "gftma.x", "permission": "active"}' -p gftma.x



cleos -u https://api.eosnewyork.io push action gyftietokens createbadge '["verifysms", "SMS Verified", "Verified that user can receive SMS messages", "0.10000000 GFT", "", "", "textsms", "gyftieoracle", 1]' -p gftma.x
cleos -u https://api.eosnewyork.io push action gyftietokens createbadge '["verifyemail", "Email Verified", "Verified that user can receive Emails", "0.20000000 GFT", "", "", "email", "gyftieoracle", 1]' -p gftma.x
cleos -u https://api.eosnewyork.io push action gyftietokens createbadge '["govtidver", "Government-issued ID Verified", "User has saved hash of Government-issued ID on chain for future verification", "0.30000000 GFT", "", "", "portrait", "gyftieoracle", 1]' -p gftma.x
cleos -u https://api.eosnewyork.io push action gyftietokens createbadge '["vouchirl", "Vouched for In Real Life (IRL)", "Someone in real life has vouched for user", "0.40000000 GFT", "", "", "group", "gyftieoracle", 1]' -p gftma.x
cleos -u https://api.eosnewyork.io push action gyftietokens createbadge '["buygft", "Purchased GFT", "User has purchased GFT", "1.00000000 GFT", "", "", "local_grocery", "gyftieoracle", 1]' -p gftma.x
cleos -u https://api.eosnewyork.io push action gyftietokens createbadge '["identified", "Fully identified", "User has completed all 5 onboarding steps", "0.00000000 GFT", "", "", "how_to_reg", "gyftieoracle", 1]' -p gftma.x

cleos -u https://api.eosnewyork.io push action gyftietokens issuebadge '["gftma.x", "verifysms", "User is now SMS Verified"]' -p gyftieoracle

cleos -u https://api.eosnewyork.io push action gyftietokens accelunstake '["purposebuilt"]' -p gftma.x
cleos -u https://api.eosnewyork.io push action gyftietokens remprofprep '["purposebuilt"]' -p gftma.x
cleos -u https://api.eosnewyork.io push action gyftietokens removeprof '["purposebuilt"]' -p gftma.x


"supply": "9684.65713013 GFT",




delete data in AWS
check orders
accelerate unstake
removeprof


cleos -u https://api.eosnewyork.io get table -l 1 --lower "digiscarcity" gyftietokens gyftietokens profiles
cleos -u https://api.eosnewyork.io get table gyftietokens digiscarcity accounts
cleos -u https://api.eosnewyork.io get table gyftietokens GFT stat
➜ cleos -u https://api.eosnewyork.io get table gyftietokens GFT stat

cleos -u https://api.eosnewyork.io get table --lower "purposebuilt" gyftietokens gyftietokens profiles