#include "gen.h"

#include <time.h>
#include <sys/time.h> 	/* gettimeofday */
#include <unistd.h> 	/* getpid */
#include <stdio.h>
#include <stdlib.h>

/*static int s_counder = 1;*/
/*static int fermat_primes[3] = {3,17,65537};*/

void generate(unsigned int b_size){

	mpz_t p, q, n, d, e, phi;
	mpz_t phi_p, phi_q, p_mod;
	int p_size = b_size/2, q_size = b_size - b_size/2;

	mpz_init(p);mpz_init(q);
	mpz_init(n);
	mpz_init(d);mpz_init(e);
	mpz_init(phi);mpz_init(phi_p);mpz_init(phi_q);
	mpz_init(p_mod);

	do{
		/* prvocisla p,q */
		do{

			do{
				/* p */
				gen_prime(p_size,p);
				/* q */
				gen_prime(q_size,q);
			}while(mpz_cmp(p,q) == 0);/* p a q sa nerovnaju */

			/* phi */
			mpz_sub_ui(phi_p,p,1);
			mpz_sub_ui(phi_q,q,1);
			mpz_mul(phi,phi_q,phi_p);

			/* e */
			if(mpz_cmp_ui(phi,65537) > 0){ /* phi > 65537 */
				mpz_set_ui(e,65537);
			}else if(mpz_cmp_ui(phi,17) > 0){/* phi > 17 */
				mpz_set_ui(e,17);
			}else{
				mpz_set_ui(e,3);
			}


			mpz_mod(p_mod,p,e);
		}while(mpz_cmp_ui(p_mod,1) == 0);/* (p mod e)!=1 */

		/* modulus n */
		mpz_mul(n,p,q);

		/* d */
		modular_inverse(e,phi,d);
	} while(mpz_cmp_ui(d,0) == 0); /* dokial nenajdes spravne, pre ktore existuj inverzia */
#ifdef DEBUG
	gmp_printf("p: %Zd\nq: %Zd\nn: %Zd\nphi: %Zd\ne: %Zd\nd: %Zd\n",p,q,n,phi,e,d);
#endif

	gmp_printf("0x%Zx 0x%Zx 0x%Zx 0x%Zx 0x%Zx\n",p,q,n,e,d);

	mpz_clear(p);mpz_clear(q);mpz_clear(n);mpz_clear(d);mpz_clear(e);mpz_clear(phi);
	mpz_clear(phi_p);mpz_clear(phi_q);mpz_clear(p_mod);
}


void gen_prime(unsigned int b_size, mpz_t res){

	gmp_randstate_t state;
	struct timeval r_time;

	gettimeofday(&r_time,NULL);
	gmp_randinit_default(state);
	gmp_randseed_ui(state,(r_time.tv_sec * 1000) + (r_time.tv_usec / 1000));

	do{
		mpz_urandomb(res,state,b_size);
		mpz_setbit(res,0);
		mpz_setbit(res,b_size - 1);
		mpz_setbit(res,b_size - 2);
	}while(mpz_probab_prime_p(res,20) == 0);
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

    /* Make sure u3 = gcd(u,v) == 1 */
    if (mpz_cmp_ui(u3,1) != 0){
    	mpz_set_ui(res,0);
        return;
    }

    /* Ensure a positive result */
    if (i < 0){
        mpz_sub(res,v,u1);
    }
    else {
    	mpz_set(res,u1);
    }

    mpz_clear(u1);mpz_clear(u3);mpz_clear(v1);mpz_clear(v3);mpz_clear(t1);mpz_clear(t3);mpz_clear(q);
}
