eosio-cpp -I=include -R=resources src/gyftietoken/gyftietoken.cpp -o=gyftie/gyftietoken/gyftietoken.wasm
eosio-cpp -I=include -R=resources src/gyftietoken/gyftietoken.cpp -abigen -o=gyftie/gyftietoken/gyftietoken.abi
eosio-cpp -I=include -R=resources src/gftorderbook/gftorderbook.cpp -o=gyftie/gftorderbook/gftorderbook.wasm
eosio-cpp -I=include -R=resources src/gftorderbook/gftorderbook.cpp -abigen -o=gyftie/gftorderbook/gftorderbook.abi
eosio-cpp -I=include -R=resources src/gftmultisig/gftmultisig.cpp -o=gyftie/gftmultisig/gftmultisig.wasm
eosio-cpp -I=include -R=resources src/gftmultisig/gftmultisig.cpp -abigen -o=gyftie/gftmultisig/gftmultisig.abi