/**
 * ACTION addpayroll
 */
void eospayroll::addpayroll( name sender, name payee, asset quantity, string memo, uint64_t interval )
{
	require_auth( sender );
    check( quantity.is_valid(), "[quantity] is not valid");
    check( is_account( sender ), "[sender] account does not exist");
	check_payee_exists( payee );
    check_currency_exists( quantity.symbol.code() );
    emplace_payroll( sender, payee, quantity, memo, interval );
}

/**
 * ACTION rmvpayroll
 */
void eospayroll::rmvpayroll( uint64_t id )
{
    check_payroll_exists( id );
    auto payroll_itr = _payroll.find( id );
	require_auth( payroll_itr->sender );
    erase_payroll( id );
}

void eospayroll::erase_payroll( uint64_t id )
{
    auto payroll_itr = _payroll.find( id );
	_payroll.erase( payroll_itr );
}

uint64_t eospayroll::emplace_payroll( name sender, name payee, asset quantity, string memo, uint64_t interval )
{
    const uint64_t id = _payroll.available_primary_key();

    _payroll.emplace( get_self(), [&](auto& row) {
        row.id              = id;
        row.sender          = sender;
        row.payee           = payee;
        row.quantity        = quantity;
        row.memo            = memo;
        row.interval        = interval;
        row.timestamp       = time_point_sec(0);
    });
    return id;
}

void eospayroll::update_payroll_timestamp( uint64_t id )
{
    auto payroll_itr = _payroll.find( id );

    _payroll.modify( payroll_itr, get_self(), [&](auto& row) {
        row.timestamp = current_time_point();
    });
}

bool eospayroll::payroll_exists( uint64_t id )
{
    auto payroll_itr = _payroll.find( id );
    return payroll_itr != _payroll.end();
}

void eospayroll::check_payroll_exists( uint64_t id )
{
    check( payroll_exists( id ), "[id] no matching payroll results" );
}