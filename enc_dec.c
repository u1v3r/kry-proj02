#include "enc_dec.h"

#include <time.h>
#include <sys/time.h> 	/* gettimeofday */
#include <unistd.h> 	/* getpid */
#include <stdio.h>
#include <stdlib.h>

void rsa_encrypt(char *s_e, char *s_n, char *s_m){
	mpz_t e, n, m, c;

	mpz_init(e);mpz_init(n);mpz_init(m);mpz_init(c);

	gmp_sscanf(s_e,"0x%Zx",e);
	gmp_sscanf(s_n,"0x%Zx",n);
	gmp_sscanf(s_m,"0x%Zx",m);

	mod_exp(m,e,n,c);

#ifdef DEBUG
	gmp_printf("e:0x%Zx\n",e);
	gmp_printf("n:0x%Zx\n",n);
	gmp_printf("m:0x%Zx\n",m);
	gmp_printf("c:0x%Zx\n",c);
#endif

	gmp_printf("0x%Zx\n",c);

	mpz_clear(e);mpz_clear(n);mpz_clear(m);mpz_clear(c);

}

void rsa_decrypt(char *s_d, char *s_n, char *s_c){
	mpz_t d, n, m, c;

	mpz_init(d);mpz_init(n);mpz_init(m);mpz_init(c);

	gmp_sscanf(s_d,"0x%Zx",d);
	gmp_sscanf(s_n,"0x%Zx",n);
	gmp_sscanf(s_c,"0x%Zx",c);

	mod_exp(c,d,n,m);

	gmp_printf("0x%Zx\n",m);

	mpz_clear(d);mpz_clear(n);mpz_clear(m);mpz_clear(c);
}

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
