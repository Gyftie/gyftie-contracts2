cleos -u https://eos.greymass.com set contract -sjd -x 186400 gyftietokens gyftie/gyftietoken/ > gyftietoken_deploy.json
cleos -u https://eos.greymass.com multisig propose_trx redeploy '[{"actor": "gftma.x", "permission": "active"}, {"actor": "amandarachel", "permission": "active"}]' ./gyftietoken_deploy.json gftma.x
cleos -u https://eos.greymass.com  push action gyftmultisig addproposal '["gftma.x", "amandarachel", "redeploy", "Improved error handling for debugging profile cleanup", "https://github.com/gyftie/gyftie-contracts2/commit/7c6215fb023e0aa7fa64bfc63f30d0948186472b"]' -p gftma.x
cleos -u https://eos.greymass.com multisig approve gftma.x redeploy '{"actor": "gftma.x", "permission": "active"}' -p gftma.x

cleos -u https://eos.greymass.com set contract -sjd -x 186400 gyftietokens gyftie/gyftietoken/ > gyftietoken_deploy.json
cleos -u https://eos.greymass.com multisig propose_trx redeploy '[{"actor": "gftma.x", "permission": "active"}, {"actor": "danielflora3", "permission": "active"}]' ./gyftietoken_deploy.json gftma.x
cleos -u https://eos.greymass.com  push action gyftmultisig addproposal '["gftma.x", "danielflora3", "redeploy", "Improved error handling for debugging profile cleanup", "https://github.com/gyftie/gyftie-contracts2/commit/7c6215fb023e0aa7fa64bfc63f30d0948186472b"]' -p gftma.x
cleos -u https://eos.greymass.com multisig approve gftma.x redeploy '{"actor": "gftma.x", "permission": "active"}' -p gftma.x


cleos -u https://eos.greymass.com set contract -sjd -x 186400 gftorderbook gyftie/gftorderbook/ > gftorderbook_deploy.json
cleos -u https://eos.greymass.com multisig propose_trx redeploy '[{"actor": "gftma.x", "permission": "active"}, {"actor": "amandarachel", "permission": "active"}]' ./gftorderbook_deploy.json gftma.x
cleos -u https://eos.greymass.com  push action gyftmultisig addproposal '["gftma.x", "amandarachel", "redeploy", "Put sell orders under maintenance", "https://github.com/gyftie/gyftie-contracts2/commit/9b8e05cb8533f7a2c93fd758f8f4bacababcea2e"]' -p gftma.x
cleos -u https://eos.greymass.com multisig approve gftma.x redeploy '{"actor": "gftma.x", "permission": "active"}' -p gftma.x



cleos -u https://eos.greymass.com push action -sjd -x 86400 gyftietokens setconfig '["gftorderbook", "gyftiegyftie", "gyftieoracle"]' -p gyftietokens > gyftietokens_setconfig.json
cleos -u https://eos.greymass.com multisig propose_trx setconfig '[{"actor": "gftma.x", "permission": "active"}, {"actor": "amandarachel", "permission": "active"}]' ./gyftietokens_setconfig.json gftma.x
cleos -u https://eos.greymass.com  push action gyftmultisig addproposal '["gftma.x", "amandarachel", "setconfig", "Set configuration - adding gyftie oracle", "No Link"]' -p gftma.x
cleos -u https://eos.greymass.com multisig approve gftma.x setconfig '{"actor": "gftma.x", "permission": "active"}' -p gftma.x


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




delete data in AWS
check orders
accelerate unstake
removeprof


cleos -u https://eos.greymass.com get table -l 1 --lower "digiscarcity" gyftietokens gyftietokens profiles
cleos -u https://eos.greymass.com get table gyftietokens digiscarcity accounts
cleos -u https://eos.greymass.com get table gyftietokens GFT stat
➜ cleos -u https://eos.greymass.com get table gyftietokens GFT stat

cleos -u https://eos.greymass.com get table --lower "purposebuilt" gyftietokens gyftietokens profiles