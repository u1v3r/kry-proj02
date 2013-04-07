#ifndef GLOBAL_FCS_H_
#define GLOBAL_FCS_H_

#include <gmp.h>
#include "util.h" /* uint32 a uint64 */

void mod_exp(mpz_t z, mpz_t e, mpz_t m, mpz_t res);
void mod_exp_ui(mpz_t z, unsigned long e, mpz_t m, mpz_t res);
void get_random_seeds(uint32 *seed1, uint32 *seed2);
void modular_inverse(mpz_t u, mpz_t v, mpz_t res);

#endif /* GLOBAL_FCS_H_ */
