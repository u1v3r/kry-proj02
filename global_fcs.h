#ifndef GLOBAL_FCS_H_
#define GLOBAL_FCS_H_

#include <gmp.h>
#include "global_fcs.h"

void mod_exp(mpz_t z, mpz_t e, mpz_t m, mpz_t res);
void mod_exp_ui(mpz_t z, unsigned long e, mpz_t m, mpz_t res);

#endif /* GLOBAL_FCS_H_ */
