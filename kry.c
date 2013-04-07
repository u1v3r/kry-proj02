#define _POSIX_C_SOURCE 200809L

#include "kry.h"

int main(int argc, char **argv) {

	if(argc < 3 && argc > 5){
		perror("bad params\n");
		exit(1);
	}

	/* TODO pridat kontorlu parametrov */

	switch (argv[1][1]) {
		case CMD_GENERATE:
			if(atoi(argv[2]) <= 10){
				perror("kratky kluc\n");
				exit(1);
			}

			rsa_generate(atoi(argv[2]));
			break;
		case CMD_ENCRYPT:
			rsa_encrypt(argv[2],argv[3],argv[4]);
			break;
		case CMD_DECRYPT:
			rsa_decrypt(argv[2],argv[3],argv[4]);
			break;
		case CMD_CRACK:
			rsa_crack(argv[2],argv[3],argv[4]);
			break;
		default:
			printf("Unknown command\n");
			break;
	}

	return 0;
}
