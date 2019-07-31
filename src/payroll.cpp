/**
 * ACTION addpayroll
 *
 * Add payroll details for payee's payouts per interval period
 *
 * @param {name} from - name of payor
 * @param {name} to - name of payee
 * @param {asset} quantity - quantity amount to be paid per payout period  (ex: "100.00 CAD")
 * @param {string} memo - memo used when sending transfer
 * @param {uint64_t} interval - minimum payout interval in seconds (ex: 60 * 60 * 24 * 7 = 604800 = 1 week)
 * @example
 *
 * addpayroll( "fromaccount", "toaccount", "100.00 CAD", "weekly salary", 604800 );
 */
void eospayroll::addpayroll( name from, name to, asset quantity, string memo, uint64_t interval )
{
	require_auth( from );
    check( quantity.is_valid(), "[quantity] is not valid");
	check_payee_exists( to );
    check_currency_exists( quantity.symbol.code() );
    emplace_payroll( from, to, quantity, memo, interval );
}

/**
 * ACTION rmvpayroll
 *
 * Removes payroll from EOS payroll table
 *
 * @param {uint64_t} id - payroll unique identifier
 * @example
 *
 * rmvpayroll( 0 );
 */
void eospayroll::rmvpayroll( uint64_t id )
{
	require_auth( get_self() );
    check_payroll_exists( id );
    erase_payroll( id );
}

void eospayroll::erase_payroll( uint64_t id ) {
    auto payroll_itr = _payroll.find( id );
	_payroll.erase( payroll_itr );
}

uint64_t eospayroll::emplace_payroll( name from, name to, asset quantity, string memo, uint64_t interval )
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

void eospayroll::update_payroll_timestamp( uint64_t id ) {
    auto payroll_itr = _payroll.find( id );

    _payroll.modify( payroll_itr, get_self(), [&](auto& row) {
        row.timestamp = current_time_point();
    });
}

bool eospayroll::payroll_exists( uint64_t id ) {
    auto payroll_itr = _payroll.find( id );
    return payroll_itr != _payroll.end();
}

void eospayroll::check_payroll_exists( uint64_t id ) {
    check( payroll_exists( id ), "[payroll.id] no matching results" );
}