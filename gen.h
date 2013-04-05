#ifndef GEN_H_
#define GEN_H_

#include "defs.h"
#include <gmp.h>

void generate(unsigned int b_size);
void gen_prime(unsigned int b_size, mpz_t res);
void modular_inverse(mpz_t u, mpz_t v, mpz_t res);

#endif /* GEN_H_ */
