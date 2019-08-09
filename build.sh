#!/usr/bin/env bash

CODE=eospayroll
TOKEN=eosio.token

eosio-cpp -abigen -I include -R resource -contract $CODE -o $CODE.wasm src/$CODE.cpp
eosio-cpp -abigen -I include -R resource -contract $TOKEN -o $TOKEN.wasm src/$TOKEN.cpp