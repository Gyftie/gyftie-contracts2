project(gyftie)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_subdirectory(gyftietoken)
add_subdirectory(gftorderbook)
add_subdirectory(gftmultisig)
add_subdirectory(token)
