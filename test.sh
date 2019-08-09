#!/usr/bin/env bash

CODE=eospayroll
SENDER=alice
PAYEE=bob
TOKEN=eosio.token
ENDPOINT=http://localhost:8888

# setcurrency
cleos -u $ENDPOINT push action $CODE setcurrency \
    "[\"4.33 USD\"]" \
    -p $CODE

# setcurrency
cleos -u $ENDPOINT push action $CODE setcurrency \
    "[\"5.65 CAD\"]" \
    -p $CODE

# addpayroll
cleos -u $ENDPOINT push action $CODE addpayroll \
    "[\"$SENDER\", \"$PAYEE\", \"100.00 USD\", \"delete me\", 60]" \
    -p $SENDER

# addpayroll
cleos -u $ENDPOINT push action $CODE addpayroll \
    "[\"$SENDER\", \"$PAYEE\", \"250.00 USD\", \"payroll using USD\", 60]" \
    -p $SENDER

# addpayroll
cleos -u $ENDPOINT push action $CODE addpayroll \
    "[\"$SENDER\", \"$PAYEE\", \"250.00 CAD\", \"payroll using CAD\", 300]" \
    -p $SENDER

# addpayroll
cleos -u $ENDPOINT push action $CODE addpayroll \
    "[\"$SENDER\", \"$PAYEE\", \"350.00 CAD\", \"payroll using CAD\", 6000]" \
    -p $SENDER

# rmvpayroll
cleos -u $ENDPOINT push action $CODE rmvpayroll \
    "[0]" \
    -p $SENDER

cleos transfer $SENDER $CODE "3.0000 EOS"
