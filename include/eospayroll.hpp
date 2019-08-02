#include <eosio/asset.hpp>
#include <eosio/symbol.hpp>
#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <eosio/system.hpp>
#include <eosio.token.hpp>

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
				_currency( receiver, receiver.value ),
				_payroll( receiver, receiver.value ),
				_payout( receiver, receiver.value )
        {}

		/**
		 * ACTION `setpayee`
		 *
		 * Set payee details to EOS payroll with paid currency preferences
		 *
		 * @param {name} name - account name of payee
		 * @param {symbol_code} currency - EOSIO symbol currency being paid (ex: "USD", "CAD", "RMB")
		 * @example
		 *
		 * setpayer( "payee.accnt", "CAD" );
		 */
        [[eosio::action]]
		void setpayee( name name, symbol_code currency );

		/**
		 * ACTION `rmvpayee`
		 *
		 * Removes payee from EOS payroll
		 *
		 * @param {name} name - EOSIO name of payee to be removed
		 * @example
		 *
		 * rmvpayee( "payee.accnt" );
		 */
		[[eosio::action]]
		void rmvpayee( name name );

		/**
		 * ACTION `setcurrency`
		 *
		 * Set currency rates
		 *
		 * @param {asset} rate - currency rate based on EOS price (ex: "4.56 CAD")
		 * @example
		 *
		 * setcurrency( "4.56 CAD" );
		 */
        [[eosio::action]]
		void setcurrency( asset rate );

		/**
		 * ACTION `rmvcurrency`
		 *
		 * Removes currency rate from EOS payroll
		 *
		 * @param {symbol_code} currency - EOSIO symbol code currency (ex: "CAD")
		 * @example
		 *
		 * rmvcurrency( "CAD" );
		 */
        [[eosio::action]]
		void rmvcurrency( symbol_code currency );

		/**
		 * ACTION `addpayroll`
		 *
		 * Add payroll details for payee's payouts per interval period
		 *
		 * @param {name} from - account name of sender
		 * @param {name} to - account name of payee
		 * @param {asset} quantity - quantity amount to be paid per payout period  (ex: "100.00 CAD")
		 * @param {string} memo - memo used when sending transfer
		 * @param {uint32_t} interval - minimum payout interval in seconds (ex: 60 * 60 * 24 * 7 = 604800 = 1 week)
		 * @example
		 *
		 * addpayroll( "sender.accnt", "payee.accnt", "100.00 CAD", "weekly salary", 604800 );
		 */
        [[eosio::action]]
		void addpayroll( name from,
						 name to,
					     asset quantity,
						 string memo,
						 uint32_t interval );

		/**
		 * ACTION `rmvpayroll`
		 *
		 * Removes payroll from EOS payroll table
		 *
		 * @param {uint64_t} id - payroll unique identifier
		 * @example
		 *
		 * rmvpayroll( 0 );
		 */
        [[eosio::action]]
		void rmvpayroll( uint64_t id );

		/**
		 * ACTION `payout`
		 *
		 * Performs payouts per sender's payroll
		 *
		 * `eosio.code@active` must be defined in sender's permission
		 *
		 * @param {name} from - account name of sender which authorizes payroll
		 * @example
		 *
		 * payout( "sender.acct" );
		 */
		[[eosio::action]]
		void payout( name from );

	private:
		/**
		 * TABLE `payee`
		 *
		 * Contains all info related to the payees
		 *
		 * @param {name} name - EOSIO name of payee
		 * @param {symbol_code} currency - preferred currency for payout
		 *
		 * @example
		 * {
		 *   "name": "myaccount",
		 *   "currency": "CAD"
		 * }
		 */
	    struct [[eosio::table("payee")]] payee_row {
			name     		name;
			symbol_code 	currency;

			auto primary_key() const { return name.value; }
		};

		/**
		 * TABLE `rate`
		 *
		 * Contains all info related to the currency rates
		 *
		 * @param {symbol_code} currency - currency code (ex: "CAD")
		 * @param {asset} rate - rate of currency valued in EOS (ex: "4.56 CAD")
		 * @param {time_point_sec} timestamp - last time currency rate was updated
		 *
		 * @example
		 * {
		 *   "currency": "CAD",
		 *   "rate": "4.56 CAD",
		 *   "timestamp": "2019-07-30T22:21:51"
		 * }
		 */
	    struct [[eosio::table("currency")]] currency_row {
			symbol_code    	currency;
			asset     		rate;
			time_point_sec 	timestamp;

			auto primary_key() const { return currency.raw(); }
		};

		/**
		 * TABLE `payroll`
		 *
		 * Contains all info related to the payroll
		 *
		 * @param {uint64_t} id - unique identifier of payroll
		 * @param {name} from - account name of sender
		 * @param {name} to - account name of payee
		 * @param {asset} quantity - quantity amount to be paid per payout period  (ex: "100.00 CAD")
		 * @param {uint32_t} interval - minimum payout interval in seconds (ex: 60 * 60 * 24 * 7 = 604800 = 1 week)
		 * @param {string} memo - memo used when sending transfer
		 * @param {time_point_sec} timestamp - last time payroll was paid
		 *
		 * @example
		 * {
		 *   "id": 0,
		 *   "from": "sender.accnt",
		 *   "to": "payee.accnt",
		 *   "quantity": "100.00 CAD",
		 *   "interval": 604800,
		 *   "memo": "weekly salary",
		 *   "timestamp": "2019-07-30T22:21:51"
		 * }
		 */
	    struct [[eosio::table("payroll")]] payroll_row {
			uint64_t        id;
			name			from;
			name			to;
			asset			quantity;
			string			memo;
			uint32_t		interval;
			time_point_sec	timestamp;

			auto 		primary_key() const { return id; }
			uint64_t  	by_from() const { return from.value; }
			uint64_t  	by_to() const { return to.value; }
		};

		/**
		 * TABLE `payout`
		 *
		 * Contains all info related to the payout
		 *
		 * @param {uint64_t} id - unique identifier of payout
		 * @param {name} from - account name of sender
		 * @param {name} to - account name of payee
		 * @param {asset} quantity - quantity amount to be paid per payout period  (ex: "100.00 CAD")
		 * @param {uint32_t} interval - minimum payout interval in seconds (ex: 60 * 60 * 24 * 7 = 604800 = 1 week)
		 * @param {string} memo - memo used when sending transfer
		 * @param {time_point_sec} timestamp - last time payout was paid
		 *
		 * @example
		 * {
		 *   "id": 0,
		 *   "transaction": "8dba3ce623551b766efe77db7b3b9151627a3bb6bfa8b5fc1609ad8a152c83bd",
		 *   "from": "sender.accnt",
		 *   "to": "payee.accnt",
		 *   "quantity": "10.0000 EOS",
		 *   "memo": "weekly salary",
		 *   "timestamp": "2019-07-30T22:21:51",
		 *   "rate": "5.65 CAD"
		 * }
		 */
	    struct [[eosio::table("payout")]] payout_row {
			uint64_t        id;
			checksum256		transaction;
			name			from;
			name			to;
			asset			quantity;
			string			memo;
			time_point_sec	timestamp;
			asset 			rate;

			auto 		primary_key() const { return id; }
		};

		// Multi-indexes
		using payee_table = multi_index <"payee"_n, payee_row>;
		using currency_table = multi_index <"currency"_n, currency_row>;
		using payout_table = multi_index <"payout"_n, payout_row>;

		typedef multi_index<"payroll"_n, payroll_row,
            indexed_by<"byfrom"_n, const_mem_fun<payroll_row, uint64_t, &payroll_row::by_from> >,
			indexed_by<"byto"_n, const_mem_fun<payroll_row, uint64_t, &payroll_row::by_to> >
        > payroll_table;

		payee_table _payee;
		currency_table _currency;
		payroll_table _payroll;
		payout_table _payout;

		// private methods

		// payee
		bool payee_exists( name name );
		void check_payee_exists( name name );
		void emplace_payee( name name, symbol_code currency );
		void modify_payee( name name, symbol_code currency );
		void erase_payee( name name );
		symbol_code get_payee_currency( name name );

		// currency
		bool currency_exists( symbol_code currency );
		void check_currency_exists( symbol_code currency );
		void emplace_currency( asset rate );
		void modify_currency( asset rate );
		void erase_currency( symbol_code currency );
		asset zero_currency( symbol_code currency );
		asset get_currency_rate( symbol_code currency );

		// payroll
		uint64_t emplace_payroll( name from, name to, asset quantity, string memo, uint32_t interval );
		void erase_payroll( uint64_t id );
		bool payroll_exists( uint64_t id );
		void check_payroll_exists( uint64_t id );
		void update_payroll_timestamp( uint64_t id );

		// payout
		uint64_t emplace_payout( name from, name to, asset quantity, string memo, asset rate );
		time_point_sec calculate_payout_timestamp( uint32_t interval );
		void transfer_eosio_token( name from, name to, asset quantity, string memo );

		// utils
		checksum256 get_trx_id();
	};