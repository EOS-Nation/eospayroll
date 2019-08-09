#!/usr/bin/env bash

CODE=eospayroll
TOKEN=eosio.token
USER=bob

ENDPOINT=http://localhost:8888

cleos create account eosio $CODE EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
cleos create account eosio $TOKEN EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
cleos create account eosio $USER EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

cleos set account permission $CODE active '{"threshold": 1,"keys": [{"key": "EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV","weight": 1}],"accounts": [{"permission": {"actor": "eospayroll","permission": "eosio.code"},"weight": 1}]}' owner
cleos set account permission $TOKEN active '{"threshold": 1,"keys": [{"key": "EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV","weight": 1}],"accounts": [{"permission": {"actor": "eospayroll","permission": "eosio.code"},"weight": 1}]}' owner

cleos -u $ENDPOINT set contract $CODE ./ $CODE.wasm $CODE.abi
cleos -u $ENDPOINT set contract $TOKEN ./ $TOKEN.wasm $TOKEN.abi

cleos push action eosio.token create '["eosio.token", "1000000000.0000 EOS"]' -p eosio.token
cleos push action eosio.token issue '["eosio.token", "1000000000.0000 EOS", "init"]' -p eosio.token
cleos push action eosio.token transfer '["eosio.token", "bob", "100.0000 EOS", "init"]' -p eosio.token
cleos push action eosio.token transfer '["eosio.token", "eospayroll", "100.0000 EOS", "init"]' -p eosio.token
