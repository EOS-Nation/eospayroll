/**
 * ACTION setpayee
 *
 * Set payee details to EOS payroll with paid currency preferences
 *
 * Zero the total quantity asset of `total_payout`
 *
 * @param {name} name - EOSIO name of payee
 * @param {symbol_code} currency - EOSIO symbol currency being paid (ex: "USD", "CAD", "RMB")
 * @example
 *
 * setpayer( "myaccount", "CAD" );
 */
void eospayroll::setpayee( name name, symbol_code currency )
{
	check( has_auth( name ) || has_auth( get_self() ), "missing required authority");
    check( currency.is_valid(), "currency symbol_code is not valid");
	check( is_account( name ), "account does not exist");
    check_currency_exists( currency );

    if (payee_exists( name )) {
        modify_payee( name, currency );
    } else {
        emplace_payee( name, currency );
    }
}

/**
 * ACTION rmvpayee
 *
 * Removes payee from EOS payroll
 *
 * @param {name} name - EOSIO name of payee to be removed
 * @example
 *
 * rmvpayee( "myaccount" );
 */
void eospayroll::rmvpayee( name name )
{
	require_auth( get_self() );
    check_payee_exists( name );
    erase_payee( name );
}

void eospayroll::erase_payee( name name ) {
    auto payee_itr = _payee.find(name.value);
	_payee.erase(payee_itr);
}

void eospayroll::emplace_payee( name name, symbol_code currency ) {
    _payee.emplace( get_self(), [&](auto& row) {
        row.name        = name;
        row.currency    = currency;
    });
}

void eospayroll::modify_payee( name name, symbol_code currency ) {
    auto payee_itr = _payee.find( name.value );
    _payee.modify( payee_itr, get_self(), [&](auto& row) {
        row.currency    = currency;
    });
}

bool eospayroll::payee_exists( name name ) {
    auto payee_itr = _payee.find( name.value );
    return payee_itr != _payee.end();
}

void eospayroll::check_payee_exists( name name ) {
    check( payee_exists( name ), "[payee.name] no matching results" );
}