project(gyftie)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( gftmultisig gftmultisig gftmultisig.cpp )
target_include_directories( gftmultisig PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( gftmultisig ${CMAKE_SOURCE_DIR}/../ricardian )
