#include "crack.h"
#include "global_fcs.h"
#include <gmp.h>
#include <unistd.h> /* sysconf */

static msieve_obj *init_msieve_object(mpz_t input_integer);

void rsa_crack(char *s_e, char *s_n, char *s_c){

	mpz_t e, n, c, d, phi, p_minus, q_minus, m;
	mpz_t factors[2];
	msieve_obj *msieve_obj;
	msieve_factor *factor;
	int f_count = 0;

	mpz_init(e);mpz_init(n);mpz_init(c);
	mpz_init(d);mpz_init(phi);
	mpz_init(p_minus);mpz_init(q_minus);
	mpz_init(m);
	mpz_init(factors[0]);mpz_init(factors[1]);

	gmp_sscanf(s_e,"0x%Zx",e);
	gmp_sscanf(s_n,"0x%Zx",n);
	gmp_sscanf(s_c,"0x%Zx",c);

	msieve_obj = init_msieve_object(n);

	if(msieve_obj == NULL){
		perror("msieve obj init\n");
		exit(1);
	}

	msieve_run(msieve_obj);

	factor = msieve_obj->factors;

	while(factor != NULL){
		if(f_count > 1){/* pre istotu */
			break;
		}
		mpz_set_str(factors[f_count++],factor->number,10);
		factor = factor->next;
	}

	msieve_obj_free(msieve_obj);

	/* p - 1 & q - 1 */
	mpz_sub_ui(p_minus,factors[0],1);
	mpz_sub_ui(q_minus,factors[1],1);

	/* phi = p*q */
	mpz_mul(phi,p_minus,q_minus);

	/* d */
	modular_inverse(e,phi,d);

	/* m */
	mod_exp(c,d,n,m);

	gmp_printf("0x%Zx 0x%Zx 0x%Zx\n",factors[0],factors[1],m);

	mpz_clear(e);mpz_clear(n);mpz_clear(c);
	mpz_clear(d);mpz_clear(phi);
	mpz_clear(p_minus);mpz_clear(q_minus);
	mpz_clear(m);
	mpz_clear(factors[0]);mpz_clear(factors[1]);

}

static msieve_obj *init_msieve_object(mpz_t input_integer){

	msieve_obj *obj;
	uint32 seed1, seed2;
	char *savefile_name = NULL;
	char *logfile_name = NULL;
	char *nfs_fbfile_name = NULL;
	uint32 flags = 0;
	uint32 max_relations = 0;
	enum cpu_type cpu;
	uint32 cache_size1;
	uint32 cache_size2;
	uint32 num_threads = 0;
	uint32 which_gpu = 0;
	const char *nfs_args = NULL;
	char *input_integer_s = NULL;

	/* nic nevypisovat */
	flags &= ~(MSIEVE_FLAG_USE_LOGFILE | MSIEVE_FLAG_LOG_TO_STDOUT);

	/* pocet vlakien == pocet cpu */
	num_threads = (int)sysconf(_SC_NPROCESSORS_ONLN);

	get_random_seeds(&seed1,&seed2);
	get_cache_sizes(&cache_size1, &cache_size2);
	cpu = get_cpu_type();

	/* prevod mpz_t -> char* */
	input_integer_s = mpz_get_str(input_integer_s,10,input_integer);

	obj = msieve_obj_new(input_integer_s, flags,
			savefile_name, logfile_name,
			nfs_fbfile_name,
			seed1, seed2, max_relations,
			cpu, cache_size1, cache_size2,
			num_threads, which_gpu,
			nfs_args);

	return obj;
}
