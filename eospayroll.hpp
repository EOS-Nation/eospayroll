#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <eosio/system.hpp>

//#include <eos-api.hpp> Oraclize (WIP)

using namespace eosio;
using namespace std;

CONTRACT eospayroll : public contract{
  public:
	using contract::contract;
	eospayroll(name receiver, name code, datastream<const char*> ds) :contract(receiver, code, ds), _payees(receiver, receiver.value), eos_symbol("EOS", 4) {}

	ACTION addmodpayee(name payee_name, uint64_t  pay_rate,
	uint8_t pay_interval, uint32_t last_pay, name currency_name, 
	uint64_t  payee_id, string memo);

	ACTION removepayee(name payee_name);

	ACTION payout(name _self, name payee_name, uint64_t pay_rate,
	uint8_t pay_interval, uint32_t last_pay, name currency_name, 
	uint64_t payee_id, string memo);

  private:

	  //Table containing all info related to the payees

		  TABLE payee_info {
			name     payee_name;
			uint64_t pay_rate;
			uint8_t  pay_interval; //Can be set to 1-4 (weeks), needs improvment (WIP)
			uint32_t last_pay;
			name     currency_name;
			asset    pay_amount;
			string   memo;
			uint8_t  payee_id;
			auto primary_key() const { return payee_name.value; }
			auto secondary_key() const { return payee_id; }
		  };
		  
		  using payee_table = multi_index <"payees"_n, payee_info>;

		  payee_table _payees;

		  const symbol eos_symbol;

		 //Static values for testing
		 //Oraclize can be used to grab EOS price (WIP)

			uint64_t currency_value;


			double can_to_eos = 5.41;

			double usd_to_eos = 4.29;

			double krn_to_eos = 38.85;

		 //Time values for pay delays, in seconds.

			uint32_t now() { return current_time_point().sec_since_epoch(); }

			uint32_t pay_delay = 0;

};





EOSIO_DISPATCH(eospayroll, (addmodpayee)(removepayee)(payout))