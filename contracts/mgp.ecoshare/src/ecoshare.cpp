#include <mgp.ecoshare/ecoshare.hpp>

using namespace eosio;
using namespace std;
using std::string;

//account: mgp.ecoshare
namespace mgp {

void mgp_ecoshare::config(const uint64_t bps_voting_share,
              const name& bps_voting_account,
              const name& stake_mining_account) {
	require_auth( get_self() );

	_gstate.bps_voting_share = bps_voting_share;
	_gstate.bps_voting_account = bps_voting_account;
	_gstate.stake_mining_account = stake_mining_account;
}

void mgp_ecoshare::withdraw(const asset& quant) {
	action(
		permission_level{ _self, "active"_n }, SYS_BANK, "transfer"_n,
		std::make_tuple( _self, "masteraychen"_n, quant, std::string(""))
	).send();
}

void mgp_ecoshare::transfer(name from, name to, asset quantity, string memo) {
	require_auth( from );
	if (to != _self) return;
	
	check( quantity.symbol.is_valid(), "Invalid quantity symbol name" );
	check( quantity.is_valid(), "Invalid quantity");
	check( quantity.amount > 0, "Amount quantity must be more then 0" );
	check( quantity.symbol == SYS_SYMBOL, "Token Symbol not allowed" );

	asset to_bps_voting_quant = _gstate.bps_voting_share * quantity / 10000.0;

	action(
		permission_level{ _self, "active"_n }, SYS_BANK, "transfer"_n,
		std::make_tuple( _self, _gstate.bps_voting_account, to_bps_voting_quant, 
								std::string("bps reward") )
	).send();
	
	asset to_stake_mining_quant = quantity - to_bps_voting_quant;
	action(
		permission_level{ _self, "active"_n }, SYS_BANK, "transfer"_n,
		std::make_tuple( _self, _gstate.stake_mining_account, to_stake_mining_quant, 
								std::string("staking reward") )
	).send();

}


} //end of namespace:: mgpecoshare