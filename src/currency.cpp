/**
 * ACTION setcurrency
 */
void eospayroll::setcurrency( asset rate )
{
	require_auth( get_self() );
    check( rate.is_valid(), "[rate] is not a valid EOSIO asset" );
    check( rate.symbol.precision() == 2, "[rate] precision must be 2");
    symbol_code currency = rate.symbol.code();

    if (currency_exists( currency )) {
        modify_currency( rate );
    } else {
        emplace_currency( rate );
    }
}

/**
 * ACTION rmvcurrency
 */
void eospayroll::rmvcurrency( symbol_code currency )
{
	require_auth( get_self() );
    currency_exists( currency );
    erase_currency( currency );
}

void eospayroll::erase_currency( symbol_code currency )
{
    auto currency_itr = _currency.find(currency.raw());
	_currency.erase(currency_itr);
}

void eospayroll::emplace_currency( asset rate )
{
    _currency.emplace( get_self(), [&](auto& row) {
        row.currency   = rate.symbol.code();
        row.rate       = rate;
        row.timestamp  = current_time_point();
    });
}

void eospayroll::modify_currency( asset rate )
{
    auto currency_itr = _currency.find( rate.symbol.code().raw() );
    _currency.modify( currency_itr, get_self(), [&](auto& row) {
        row.rate       = rate;
        row.timestamp  = current_time_point();
    });
}

bool eospayroll::currency_exists( symbol_code currency )
{
    auto currency_itr = _currency.find( currency.raw() );
    return currency_itr != _currency.end();
}

void eospayroll::check_currency_exists( symbol_code currency )
{
    check( currency_exists( currency ), "[currency] no matching results" );
}

asset eospayroll::zero_currency( symbol_code currency )
{
    const uint8_t precision = 2;
    return asset{0, symbol{currency, precision}};
}