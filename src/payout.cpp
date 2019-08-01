/**
 * ACTION payout
 */
void eosnpayroll::payout( name sender )
{
	require_auth( sender );

    auto by_sender = _payroll.get_index<"bysender"_n>();
    auto payroll_itr = by_sender.find( sender.value );
	check( payroll_itr == by_sender.end(), "no payroll entries found");

    while (payroll_itr != by_sender.end()){
		print("sender:", payroll_itr->sender);
		print("payee:", payroll_itr->payee);
		print("quantity:", payroll_itr->quantity);
		print("memo:", payroll_itr->memo);
		print("interval:", payroll_itr->interval);
		print("timestamp:", payroll_itr->timestamp.sec_since_epoch());
    }

	// 	check(last_pay <= pay_delay, "Paid too recently!");

	// 	/*Error message with which account and by what delay would be better*/

    // 	pay_rate = pay_rate * currency_value;

	// 	asset pay_amount(pay_rate, eos_symbol);

	// 	/*Transfer of EOS to payees based on their calculated pay amount.
	// 	Memo is currently whatever was entered during addmodpayee. We
	// 	could concatenate a custom memo with times, the number of times paid++, roles,
	// 	or other data (WIP).*/

	// 	action( permission_level{ get_self(), "active"_n }, "eosio.token"_n, "transfer"_n,
	// 		make_tuple( get_self(), // from
	// 					payee_name, // to
	// 					pay_amount, // quantity
	// 					memo )      // memo
	// 	).send();

	// 	auto setter = [&]( auto& row ) {
	// 		row.last_pay = now();
	// 	};
	// }
}
/*There is also code for deffered transactions that will pay automatically
after the pay delay has expired (WIP)*/
