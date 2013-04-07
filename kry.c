#define _POSIX_C_SOURCE 200809L

#include "kry.h"

#define ERROR_MSG "bad params format\n"

int main(int argc, char **argv) {

	if(argc < 3 || argc > 5){
		printf(ERROR_MSG);
		return 1;
	}

	switch (argv[1][1]) {
		case CMD_GENERATE:

			if(atoi(argv[2]) <= 10){
				printf("kratky kluc\n");
				return 1;
			}

			rsa_generate(atoi(argv[2]));
			break;
		case CMD_ENCRYPT:

			if(argc != 5){
				printf(ERROR_MSG);
				return 1;
			}

			rsa_encrypt(argv[2],argv[3],argv[4]);
			break;
		case CMD_DECRYPT:

			if(argc != 5){
				printf(ERROR_MSG);
				return 1;
			}

			rsa_decrypt(argv[2],argv[3],argv[4]);
			break;
		case CMD_CRACK:

			if(argc != 5){
				printf(ERROR_MSG);
				return 1;
			}

			rsa_crack(argv[2],argv[3],argv[4]);
			break;
		default:
			printf("Unknown command\n");
			break;
	}

	return 0;
}
