
#!/usr/bin/env bash

CONTRACT=eosio
ENDPOINT=http://localhost:8888

cleos -u $ENDPOINT set contract $CONTRACT ./ eospayroll.wasm eospayroll.abi
