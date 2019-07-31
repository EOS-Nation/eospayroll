
void eospayroll::payout( name _self,
						 name payee_name,
						 uint64_t pay_rate,
						 uint8_t pay_interval,
						 uint32_t last_pay,
						 name currency_name,
						 uint64_t payee_id,
						 string memo )
{
	require_auth( get_self() );
	auto iterator = _payees.find(payee_id);
	for (uint8_t pay_count = 0; pay_count < payee_id; pay_count++) {

		/*Basic currency switch, needs improvement. There is code to have price, (USD
		at least), grabbed through Oraclize (WIP).*/

		switch (currency_name.value) {

		case "can"_n.value:
			currency_value = can_to_eos;
			break;

		case "usd"_n.value:
			currency_value = usd_to_eos;
			break;

		case "krn"_n.value:
			currency_value = krn_to_eos;
			break;

		default:
			break;
		}

		//Basic time delay switch, creates a delay value in seconds based on selected inverval (WIP)

		switch (pay_interval) {

		case 1:
			pay_delay = last_pay + 604800;
			break;

		case 2:
			pay_delay = last_pay + 604800 * 2;
			break;

		case 3:
			pay_delay = last_pay + 604800 * 3;
			break;

		case 4:
			pay_delay = last_pay + 604800 * 4;
			break;

		default:
			break;
		}

		check(last_pay <= pay_delay, "Paid too recently!");

		/*Error message with which account and by what delay would be better*/

    	pay_rate = pay_rate * currency_value;

		asset pay_amount(pay_rate, eos_symbol);

		/*Transfer of EOS to payees based on their calculated pay amount.
		Memo is currently whatever was entered during addmodpayee. We
		could concatenate a custom memo with times, the number of times paid++, roles,
		or other data (WIP).*/

		action( permission_level{ get_self(), "active"_n }, "eosio.token"_n, "transfer"_n,
			make_tuple( get_self(), // from
						payee_name, // to
						pay_amount, // quantity
						memo )      // memo
		).send();

		auto setter = [&]( auto& row ) {
			row.last_pay = now();
		};
	}
}
/*There is also code for deffered transactions that will pay automatically
after the pay delay has expired (WIP)*/
