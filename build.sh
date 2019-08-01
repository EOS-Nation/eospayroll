#!/usr/bin/env bash

eosio-cpp -abigen -I include -R resource -contract eospayroll -o eospayroll.wasm src/eospayroll.cpp
