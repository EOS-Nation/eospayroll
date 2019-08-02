
#!/usr/bin/env bash

# CONTRACT=eosio
# ENDPOINT=http://localhost:8888
CONTRACT=eosnpayroll1
ENDPOINT=https://jungle.eosn.io

cleos -u $ENDPOINT set contract $CONTRACT ./ eospayroll.wasm eospayroll.abi
