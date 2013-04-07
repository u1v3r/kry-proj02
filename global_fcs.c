#include "global_fcs.h"
#include <stdlib.h>


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

	mpz_clear(e);
}

void get_random_seeds(uint32 *seed1, uint32 *seed2){

	uint32 tmp_seed1, tmp_seed2;

	/* In a multithreaded program, every msieve object
	   should have two unique, non-correlated seeds
	   chosen for it */

	{
		/* <Shrug> For everyone else, sample the current time,
		   the high-res timer (hopefully not correlated to the
		   current time), and the process ID. Multithreaded
		   applications should fold in the thread ID too */

		uint64 high_res_time = read_clock();
		tmp_seed1 = ((uint32)(high_res_time >> 32) ^
				(uint32)time(NULL)) *
						(uint32)getpid();
		tmp_seed2 = (uint32)high_res_time;
	}

	/* The final seeds are the result of a multiplicative
	   hash of the initial seeds */

	(*seed1) = tmp_seed1 * ((uint32)40499 * 65543);
	(*seed2) = tmp_seed2 * ((uint32)40499 * 65543);
}

void modular_inverse(mpz_t u, mpz_t v, mpz_t res){
    mpz_t u1, u3, v1, v3, t1, t3, q;
    int i;

    mpz_init(q);mpz_init(t1);mpz_init(t3);

    mpz_init_set_ui(u1,1);
    mpz_init_set(u3,u);
    mpz_init_set_ui(v1,0);
    mpz_init_set(v3,v);

    i = 1;

    while (mpz_cmp_ui(v3,0) != 0){
    	mpz_div(q,u3,v3);
    	mpz_mod(t3,u3,v3);
    	mpz_mul(t1,q,v1);
    	mpz_add(t1,t1,u1);

    	mpz_set(u1,v1);
    	mpz_set(v1,t1);
    	mpz_set(u3,v3);
    	mpz_set(v3,t3);

        i = -i;
    }

    if (mpz_cmp_ui(u3,1) != 0){
    	mpz_set_ui(res,0);
        return;
    }

    if (i < 0){
        mpz_sub(res,v,u1);
    }
    else {
    	mpz_set(res,u1);
    }

    mpz_clear(u1);mpz_clear(u3);mpz_clear(v1);mpz_clear(v3);
    mpz_clear(t1);mpz_clear(t3);mpz_clear(q);
}
