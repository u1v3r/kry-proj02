#include "global_fcs.h"


void mod_exp(mpz_t z, mpz_t e, mpz_t m, mpz_t res){

	mpz_t e_mod;

	mpz_init(e_mod);
	mpz_set_ui(res,1);

	while (mpz_cmp_ui(e,0) > 0){/* e > 0 */
		mpz_mod_ui(e_mod,e,2);
		if(mpz_cmp_ui(e_mod,1) == 0){
			mpz_mul(res,res,z);
			mpz_mod(res,res,m);
		}

		mpz_fdiv_q_2exp(e,e,1); /* exponent := exponent >> 1  */
		mpz_mul(z,z,z);
		mpz_mod(z,z,m);
	}

	mpz_clear(e_mod);
}

void mod_exp_ui(mpz_t z, unsigned long e_ui, mpz_t m, mpz_t res){

	mpz_t e;
	mpz_init_set_ui(e,e_ui);

	if(e_ui == 2){
		mpz_pow_ui(e,z,2);
		mpz_mod(res,e,m);
	}else{
		mod_exp(z,e,m,res);
	}
}
