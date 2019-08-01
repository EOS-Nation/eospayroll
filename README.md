# EOS Nation Payroll

A simple payroll smart contract developed by [DenisCarriere](https://github.com/DenisCarriere) and [Jmacktacular](https://github.com/Jmacktacular) for use EOS Nation's employee payroll.

## ACTIONS

- [`setpayee`](#action-setpayee)
- [`rmvpayee`](#action-rmvpayee)
- [`setcurrency`](#action-setcurrency)
- [`rmvcurrency`](#action-rmvcurrency)
- [`addpayroll`](#action-addpayroll)
- [`rmvpayroll`](#action-rmvpayroll)

## TABLES

- [`payee`](#table-payee)
- [`rate`](#table-rate)
- [`payroll`](#table-payroll)

### ACTION `setpayee`

Set payee details to EOS payroll with paid currency preferences

### params

- `{name} name` - EOSIO name of payee
- `{symbol_code} currency` - EOSIO symbol currency being paid (ex: "USD", "CAD", "RMB")

### example

```js
setpayer( "myaccount", "CAD" );
```

### ACTION `rmvpayee`

Removes payee from EOS payroll

### params

- `{name} name` - EOSIO name of payee to be removed

### example

```js
rmvpayee( "myaccount" );
```

### ACTION `setcurrency`

Set currency rates

### params

- `@param {asset} rate` - currency rate based on EOS price (ex: "4.56 CAD")

### example

```js
setcurrency( "4.56 CAD" );
```

### ACTION `rmvcurrency`

Removes currency rate from EOS payroll

### params

- `{symbol_code} currency` - EOSIO symbol code currency (ex: "CAD")

### example

```js
rmvcurrency( "CAD" );
```

### ACTION `addpayroll`

Add payroll details for payee's payouts per interval period

### params

- `{name} from` - name of payor
- `{name} to` - name of payee
- `{asset} quantity` - quantity amount to be paid per payout period  (ex: "100.00 CAD")
- `{string} memo` - memo used when sending transfer
- `{uint64_t} interval` - minimum payout interval in seconds (ex: 60 * 60 * 24 * 7 = 604800 = 1 week)

### example

```js
addpayroll( "fromaccount", "toaccount", "100.00 CAD", "weekly salary", 604800 );
```

### ACTION `rmvpayroll`

Removes payroll from EOS payroll table

### params

- `{uint64_t} id` - payroll unique identifier

### example

```js
rmvpayroll( 0 );
```

### TABLE `payee`

Table containing all info related to the payees

### params

- `{name} name` - EOSIO name of payee
- `{symbol_code} currency` - preferred currency for payout

### example

```json
{
    "name": "myaccount",
    "currency": "CAD"
}
```

### TABLE `rate`

Table containing all info related to the currency rates

### params

- `{symbol_code} currency` - currency code (ex: "CAD")
- `{asset} rate` - rate of currency valued in EOS (ex: "4.56 CAD")
- `{time_point_sec} timestamp` - last time currency rate was updated

### example

```json
{
    "currency": "CAD",
    "rate": "4.56 CAD",
    "timestamp": "2019-07-30T22:21:51"
}
```

### TABLE `payroll`

Table containing all info related to the payroll

### params

- `{uint64_t} id` - unique identifier of payroll
- `{name} from` - name of payor
- `{name} to` - name of payee
- `{asset} quantity` - quantity amount to be paid per payout period  (ex: "100.00 CAD")
- `{uint64_t} interval` - minimum payout interval in seconds (ex: 60 * 60 * 24 * 7 = 604800 = 1 week)
- `{string} memo` - memo used when sending transfer
- `{time_point_sec} timestamp` - last time payroll was paid

### example

```json
{
    "id": 0,
    "from": "fromaccount",
    "to": "toaccount",
    "quantity": "100.00 CAD",
    "interval": 604800,
    "memo": "weekly salary",
    "timestamp": "2019-07-30T22:21:51"
}
```