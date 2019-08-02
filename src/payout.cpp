/**
 * ACTION payout
 */
void eospayroll::payout( name from )
{
	require_auth( from );

	bool payout_found = false;
    auto by_from = _payroll.get_index<"byfrom"_n>();
    for (auto payroll_itr = by_from.lower_bound(from.value), end_itr = by_from.upper_bound(from.value); payroll_itr != end_itr; ++payroll_itr) {
		// payroll attributes
		const name to = payroll_itr->to;
		const string memo = payroll_itr->memo;
		const asset quantity = asset{10000, symbol{"EOS", 4}};
		const uint32_t interval = payroll_itr->interval;

		// get currency rate
		check_payee_exists( to );
		symbol_code currency = get_payee_currency( to );
		asset rate = get_currency_rate( currency );

		// skip current payroll if timestamp is in the future
		if ( payroll_itr->timestamp > current_time_point() ) continue;

		// send eosio.token EOS transfer
		transfer_eosio_token( from, to, quantity, memo );

		// Update timestamp by interval amount
		by_from.modify( payroll_itr, get_self(), [&](auto& row) {
			row.timestamp = calculate_payout_timestamp( interval );
		});

		emplace_payout( from, to, quantity, memo, rate );
		payout_found = true;
    }
	check(payout_found, "no payouts available during this timestamp");
}

uint64_t eospayroll::emplace_payout( name from, name to, asset quantity, string memo, asset rate )
{
	const uint64_t id = _payout.available_primary_key();
    _payout.emplace( get_self(), [&](auto& row) {
		row.id 			= id;
		row.transaction = get_trx_id();
        row.from       	= from;
        row.to    		= to;
		row.quantity    = quantity;
		row.memo    	= memo;
		row.timestamp   = current_time_point();
		row.rate  		= rate;
    });
	return id;
}

time_point_sec eospayroll::calculate_payout_timestamp( uint32_t interval )
{
	return time_point_sec(interval + current_time_point().sec_since_epoch());
}

void eospayroll::transfer_eosio_token( name from, name to, asset quantity, string memo )
{
	// can specify the contract to send the action to as first argument
	token::transfer_action transfer("eosio.token"_n, {from, "active"_n});

	// transfer arguments are now passed as postional arguments
	transfer.send(from, to, quantity, memo);
}