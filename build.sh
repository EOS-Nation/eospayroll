#!/usr/bin/env bash

eosio-cpp -abigen -I include -R resource -contract eosnpayroll -o eosnpayroll.wasm src/eosnpayroll.cpp
