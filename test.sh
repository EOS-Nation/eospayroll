#!/usr/bin/env bash

SENDER=eospayroll
PAYEE=bob
CODE=eospayroll
ENDPOINT=http://localhost:8888

# setcurrency
cleos -u $ENDPOINT push action $CODE setcurrency \
    "[\"4.33 USD\"]" \
    -p $CODE

# setcurrency
cleos -u $ENDPOINT push action $CODE setcurrency \
    "[\"5.65 CAD\"]" \
    -p $CODE

# setpayee
cleos -u $ENDPOINT push action $CODE setpayee \
    "[\"$PAYEE\", \"USD\"]" \
    -p $CODE

# addpayroll
cleos -u $ENDPOINT push action $CODE addpayroll \
    "[\"$SENDER\", \"$PAYEE\", \"100.00 USD\", \"delete me\", 60]" \
    -p $CODE

# addpayroll
cleos -u $ENDPOINT push action $CODE addpayroll \
    "[\"$SENDER\", \"$PAYEE\", \"250.00 USD\", \"test payroll using USD\", 60]" \
    -p $CODE

# addpayroll
cleos -u $ENDPOINT push action $CODE addpayroll \
    "[\"$SENDER\", \"$PAYEE\", \"250.00 USD\", \"test payroll using USD\", 300]" \
    -p $CODE

# addpayroll
cleos -u $ENDPOINT push action $CODE addpayroll \
    "[\"$SENDER\", \"$PAYEE\", \"350.00 USD\", \"test payroll using USD\", 6000]" \
    -p $CODE

# rmvpayroll
cleos -u $ENDPOINT push action $CODE rmvpayroll \
    "[0]" \
    -p $CODE

# payout
cleos -u $ENDPOINT push action $CODE payout \
    "[\"$SENDER\"]" \
    -p $CODE
