cmake_minimum_required(VERSION 3.5)
project(gyftie)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( gyftie gyftie gftorderbook.cpp )
target_include_directories( gyftie PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( gyftie ${CMAKE_SOURCE_DIR}/../resources )
