#ifndef GEN_H_
#define GEN_H_

#include "defs.h"
#include "global_fcs.h"
#include <gmp.h>

#define COMPOSITE 0
#define PRIME 1

void generate(unsigned int b_size);
void gen_prime(unsigned int b_size, mpz_t res);
void modular_inverse(mpz_t u, mpz_t v, mpz_t res);
int rabin_miller(mpz_t n, unsigned int t, gmp_randstate_t rand_state);
int rabin_miller_test(mpz_t n, mpz_t a, mpz_t n_minus, mpz_t d,mpz_t a_power);

#endif /* GEN_H_ */
