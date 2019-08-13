# EOS Nation Payroll

An EOSIO payroll smart contract developed by [DenisCarriere](https://github.com/DenisCarriere) and [Jmacktacular](https://github.com/Jmacktacular) used by EOS Nation's employee payroll system.

## ACTIONS

- [`setcurrency`](#action-setcurrency)
- [`rmvcurrency`](#action-rmvcurrency)
- [`addpayroll`](#action-addpayroll)
- [`rmvpayroll`](#action-rmvpayroll)
- [`payout`](#action-payout)

## TABLES


- [`currency`](#table-currency)
- [`payroll`](#table-payroll)
- [`payout`](#table-payout)



### ACTION `setcurrency`

Set currency rates

### params

- `@param {asset} rate` - currency rate based on EOS price

### example

```js
setcurrency( "4.56 CAD" );
```

### ACTION `rmvcurrency`

Removes currency rate from EOS payroll

### params

- `{symbol_code} currency` - EOSIO symbol code currency

### example

```js
rmvcurrency( "CAD" );
```

### ACTION `addpayroll`

Add payroll details for payee's payouts per interval period

### params

- `{name} from` - account name of sender
- `{name} to` - account name of payee
- `{asset} quantity` - quantity amount to be paid per payout period
- `{string} memo` - memo used when sending transfer
- `{uint32_t} interval` - minimum payout interval in seconds (ex: 60 * 60 * 24 * 7 = 604800 = 1 week)

### example

```js
addpayroll( "sender.accnt", "payee.accnt", "100.00 CAD", "weekly salary", 604800 );
```

### ACTION `rmvpayroll`

Removes payroll from EOS payroll table

### params

- `{uint64_t} id` - payroll unique identifier

### example

```js
rmvpayroll( 0 );
```

### ACTION `payout`

Performs payouts per sender's payroll

`eosio.code@active` must be defined in sender's permission

### params

- `{name} from` - account name of sender which authorizes payroll

### example

```js
payout( "sender.acct" );
```


### TABLE `currency`

Contains all info related to the currency rates

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

Contains all info related to the payroll

### params

- `{uint64_t} id` - unique identifier of payroll
- `{name} from` - account name of from
- `{name} to` - account name of to
- `{asset} quantity` - quantity amount to be paid per payout period
- `{uint32_t} interval` - minimum payout interval in seconds (ex: 60 * 60 * 24 * 7 = 604800 = 1 week)
- `{string} memo` - memo used when sending transfer
- `{time_point_sec} timestamp` - last time payroll was paid

### example

```json
{
    "id": 0,
    "from": "sender.accnt",
    "to": "payee.accnt",
    "quantity": "100.00 CAD",
    "memo": "weekly salary",
    "interval": 604800,
    "timestamp": "2019-07-30T22:21:51"
}
```

### TABLE `payout`

Contains all info related to the payout

- `{uint64_t} id` - unique identifier of payout
- `{checksum256} transaction` - identifier for transaction
- `{name} from` - account name of sender
- `{name} to` - account name of payee
- `{asset} quantity` - amount to be paid per payout period
- `{asset} rate` - rate of currency valued in EOS
- `{asset} eos_quantity` - quantity of EOS to be paid
- `{string} memo` - memo used when sending transfer
- `{time_point_sec} timestamp` - last time payout was paid


### example

```json
{
    "id": 0,
    "transaction": "8dba3ce623551b766efe77db7b3b9151627a3bb6bfa8b5fc1609ad8a152c83bd",
    "from": "sender.accnt",
    "to": "payee.accnt",
    "quantity": "100.00 CAD",
    "rate": "5.65 CAD",
    "eos_quantity": "10.0000 EOS",
    "memo": "weekly salary",
    "timestamp": "2019-07-30T22:21:51"
}
```
