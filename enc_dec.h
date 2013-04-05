#ifndef ENCRYPT_H_
#define ENCRYPT_H_

#include "defs.h"
#include <gmp.h>

void rsa_encrypt(char *s_e, char *s_n, char *s_m);
void rsa_decrypt(char *s_d, char *s_n, char *s_c);
void mod_exp(mpz_t z, mpz_t e, mpz_t m, mpz_t res);

#endif /* ENCRYPT_H_ */
