#include <eosio/asset.hpp>
#include <eosio/symbol.hpp>
#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <eosio/system.hpp>

using namespace eosio;
using namespace std;

class [[eosio::contract("eospayroll")]] eospayroll : public eosio::contract {
	public:
		using contract::contract;

		/**
         * Construct a new contract given the contract name
         *
         * @param {name} receiver - The name of this contract
         * @param {name} code - The code name of the action this contract is processing.
         * @param {datastream} ds - The datastream used
         */
        eospayroll( name receiver, name code, eosio::datastream<const char*> ds )
            : contract( receiver, code, ds ),
                _payee( receiver, receiver.value ),
				_currency( receiver, receiver.value )
        {}

		/**
		 * ACTION setpayee
		 */
        [[eosio::action]]
		void setpayee( name name, symbol_code currency );

		/**
		 * ACTION rmvpayee
		 */
		[[eosio::action]]
		void rmvpayee( name name );

		/**
		 * ACTION setcurrency
		 */
        [[eosio::action]]
		void setcurrency( asset rate );

		/**
		 * ACTION rmvcurrency
		 */
        [[eosio::action]]
		void rmvcurrency( symbol_code currency );

		// /**
		//  * ACTION payout
		//  */
		// [[eosio::action]]
		// void payout( name _self,
		// 			 name payee_name,
		// 			 uint64_t pay_rate,
		// 			 uint8_t pay_interval,
		// 			 uint32_t last_pay,
		// 			 name currency_name,
		// 			 uint64_t payee_id,
		// 			 string memo );

	private:
		/**
		 * TABLE payee
		 *
		 * Table containing all info related to the payees
		 *
		 * @param {name} EOSIO name of payee
		 * @param {symbol_code} preferred currency for payout
		 * @param {asset} total amount paid from payouts
		 * @param {timestamp} last time paid
		 *
		 * @example
		 * {
		 *   "name": "myaccount",
		 *   "currency": "CAD",
		 *   "total_payout": "100.00 CAD",
		 *   "last_payout": "2019-07-30T22:21:51"
		 * }
		 */
	    struct [[eosio::table("payee")]] payee_row {
			name     		name;
			symbol_code 	currency;
        	asset 			total_payout;
        	time_point_sec 	last_payout;

			auto primary_key() const { return name.value; }
		};

		/**
		 * TABLE rate
		 *
		 * Table containing all info related to the currency rates
		 *
		 * @param {symbol_code} currency - currency code (ex: "CAD")
		 * @param {asset} rate - rate of currency valued in EOS (ex: "4.56 CAD")
		 * @param {timestamp} last_time - last rate was updated
		 *
		 * @example
		 * {
		 *   "currency": "CAD",
		 *   "rate": "4.56 CAD",
		 *   "last_rate": "2019-07-30T22:21:51"
		 * }
		 */
	    struct [[eosio::table("currency")]] currency_row {
			symbol_code    	currency;
			asset     		rate;
			time_point_sec 	last_rate;

			auto primary_key() const { return currency.raw(); }
		};

		// Multi-indexes
		using payee_table = multi_index <"payee"_n, payee_row>;
		using currency_table = multi_index <"rate"_n, currency_row>;

		payee_table _payee;
		currency_table _currency;

		// Static values for testing
		// Oraclize can be used to grab EOS price (WIP)

		uint64_t currency_value;

		double can_to_eos = 5.41;

		double usd_to_eos = 4.29;

		double krn_to_eos = 38.85;

		// Time values for pay delays, in seconds.

		uint32_t now() { return current_time_point().sec_since_epoch(); }

		uint32_t pay_delay = 0;

		// private methods
		bool payee_exists( name name );
		void check_payee_exists( name name );
		void emplace_payee( name name, symbol_code currency );
		void modify_payee( name name, symbol_code currency );
		void erase_payee( name name );

		bool currency_exists( symbol_code currency );
		void check_currency_exists( symbol_code currency );
		void emplace_currency( asset rate );
		void modify_currency( asset rate );
		void erase_currency( symbol_code currency );
		asset zero_currency( symbol_code currency );
	};