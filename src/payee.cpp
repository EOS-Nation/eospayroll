/**
 * ACTION setpayee
 */
void eosnpayroll::setpayee( name name, symbol_code currency )
{
	check( has_auth( name ) || has_auth( get_self() ), "missing required authority");
    check( currency.is_valid(), "[currency] symbol_code is not valid");
	check( is_account( name ), "[name] account does not exist");
    check_currency_exists( currency );

    if (payee_exists( name )) {
        modify_payee( name, currency );
    } else {
        emplace_payee( name, currency );
    }
}

/**
 * ACTION rmvpayee
 */
void eosnpayroll::rmvpayee( name name )
{
    check( has_auth( name ) || has_auth( get_self() ), "missing required authority");
	require_auth( get_self() );
    check_payee_exists( name );
    erase_payee( name );
    // TO-DO also remove payee from payroll table
}

void eosnpayroll::erase_payee( name name )
{
    auto payee_itr = _payee.find(name.value);
	_payee.erase(payee_itr);
}

void eosnpayroll::emplace_payee( name name, symbol_code currency )
{
    _payee.emplace( get_self(), [&](auto& row) {
        row.name        = name;
        row.currency    = currency;
    });
}

void eosnpayroll::modify_payee( name name, symbol_code currency )
{
    auto payee_itr = _payee.find( name.value );
    _payee.modify( payee_itr, get_self(), [&](auto& row) {
        row.currency    = currency;
    });
}

bool eosnpayroll::payee_exists( name name )
{
    auto payee_itr = _payee.find( name.value );
    return payee_itr != _payee.end();
}

void eosnpayroll::check_payee_exists( name name )
{
    check( payee_exists( name ), "[name] no matching payee results" );
}