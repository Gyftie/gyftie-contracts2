cmake_minimum_required(VERSION 3.13)
project(gyftie)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( gftorderbook gftorderbook gftorderbook.cpp )
target_include_directories( gftorderbook PUBLIC ${CMAKE_SOURCE_DIR}/../include )
