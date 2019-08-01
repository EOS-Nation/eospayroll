#!/usr/bin/env bash

SENDER=eosio
PAYEE=eosio
CONTRACT=eosio
ENDPOINT=http://localhost:8888

# # setcurrency
# cleos -u $ENDPOINT push action $CONTRACT setcurrency \
#     "[\"5.56 CAD\"]" \
#     -p $CONTRACT

# # setpayee
# cleos -u $ENDPOINT push action $CONTRACT setpayee \
#     "[\"$PAYEE\", \"CAD\"]" \
#     -p $CONTRACT

# # addpayroll
# cleos -u $ENDPOINT push action $CONTRACT addpayroll \
#     "[\"$SENDER\", \"$PAYEE\", \"100.00 CAD\", \"test payroll\", 60]" \
#     -p $CONTRACT

# # rmvpayroll
# cleos -u $ENDPOINT push action $CONTRACT rmvpayroll \
#     "[0]" \
#     -p $CONTRACT

# payout
cleos -u $ENDPOINT push action $CONTRACT payout \
    "[\"$SENDER\"]" \
    -p $CONTRACT
