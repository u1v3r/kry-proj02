#ifndef ENCRYPT_H_
#define ENCRYPT_H_

#include "defs.h"
#include "global_fcs.h"
#include <gmp.h>

void rsa_encrypt(char *s_e, char *s_n, char *s_m);
void rsa_decrypt(char *s_d, char *s_n, char *s_c);

#endif /* ENCRYPT_H_ */
