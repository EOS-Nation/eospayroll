#!/usr/bin/env bash

# SENDER=eosio
# PAYEE=eosio
# CONTRACT=eosio
# ENDPOINT=http://localhost:8888

SENDER=eosnpayroll1
PAYEE1=eosnationftw
PAYEE2=deniscarrier
CONTRACT=eosnpayroll1
ENDPOINT=https://jungle.eosn.io

# # setcurrency
# cleos -u $ENDPOINT push action $CONTRACT setcurrency \
#     "[\"4.33 USD\"]" \
#     -p $CONTRACT

# # setcurrency
# cleos -u $ENDPOINT push action $CONTRACT setcurrency \
#     "[\"5.65 CAD\"]" \
#     -p $CONTRACT

# # setpayee
# cleos -u $ENDPOINT push action $CONTRACT setpayee \
#     "[\"$PAYEE1\", \"USD\"]" \
#     -p $CONTRACT

# # setpayee
# cleos -u $ENDPOINT push action $CONTRACT setpayee \
#     "[\"$PAYEE2\", \"CAD\"]" \
#     -p $CONTRACT

# # addpayroll
# cleos -u $ENDPOINT push action $CONTRACT addpayroll \
#     "[\"$SENDER\", \"$PAYEE1\", \"150.00 USD\", \"test payroll using USD\", 60]" \
#     -p $CONTRACT

# # addpayroll
# cleos -u $ENDPOINT push action $CONTRACT addpayroll \
#     "[\"$SENDER\", \"$PAYEE2\", \"200.00 CAD\", \"test payroll using CAD\", 180]" \
#     -p $CONTRACT

# # rmvpayroll
# cleos -u $ENDPOINT push action $CONTRACT rmvpayroll \
#     "[0]" \
#     -p $CONTRACT

# payout
cleos -u $ENDPOINT push action $CONTRACT payout \
    "[\"$SENDER\"]" \
    -p $CONTRACT
