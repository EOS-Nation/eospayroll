/**
 * ACTION addpayroll
 */
void eospayroll::addpayroll( name from, name to, asset quantity, string memo, uint32_t interval )
{
    require_auth( from );
    check( quantity.is_valid(), "[quantity] is not valid");
    check( is_account( from ), "[from] account does not exist");
    check( quantity.amount > 0, "[quantity] must be positive");
    check_currency_exists( quantity.symbol.code() );
    emplace_payroll( from, to, quantity, memo, interval );
}

/**
 * ACTION rmvpayroll
 */
void eospayroll::rmvpayroll( uint64_t id )
{
    check_payroll_exists( id );
    auto payroll_itr = _payroll.find( id );
    require_auth( payroll_itr->from );
    erase_payroll( id );
}

void eospayroll::erase_payroll( uint64_t id )
{
    auto payroll_itr = _payroll.find( id );
    _payroll.erase( payroll_itr );
}

uint64_t eospayroll::emplace_payroll( name from, name to, asset quantity, string memo, uint32_t interval )
{
    const uint64_t id = _payroll.available_primary_key();

    _payroll.emplace( get_self(), [&](auto& row) {
        row.id              = id;
        row.from            = from;
        row.to              = to;
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
