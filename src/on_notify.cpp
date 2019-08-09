[[eosio::on_notify("eosio.token::transfer")]]
void eospayroll::transfer( const name&    from,
                           const name&    to,
                           const asset&   quantity,
                           const string&  memo )
{
    // Only monitor incoming transfers to get_self() account
    if ( to != get_self() ) return;
    if ( from == "eosio.token"_n ) return;

    // authenticate incoming `from` account
    require_auth( from );

    check( quantity.amount == asset{30000, symbol{"EOS", 4}}.amount, "wrong amount you poor");

    // send the EOS!~
    eospayroll::payout_action payout("eospayroll"_n, { get_self(), "active"_n });
    payout.send( from );
}