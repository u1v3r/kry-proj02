#define _POSIX_C_SOURCE 200809L

#include "kry.h"

int main(int argc, char **argv) {

	if(argc < 3 && argc > 5){
		perror("bad params\n");
		exit(1);
	}


	/* TODO pridat kontorlu parametrov */

	if(strcmp(argv[1],CMD_ENCRYPT) == 0){
		rsa_encrypt(argv[2],argv[3],argv[4]);
	}else if(strcmp(argv[1],CMD_DECRYPT) == 0){
		rsa_decrypt(argv[2],argv[3],argv[4]);
	}else if(strcmp(argv[1],CMD_GENERATE) == 0){

		if(atoi(argv[2]) <= 10){
			perror("kratky kluc\n");
			exit(1);
		}

		generate(atoi(argv[2]));
	}else if(strcmp(argv[1],CMD_CRACK) == 0){
		printf("CMD_CRACK\n");
	}else{
		perror("unknown command\n");
		exit(1);
	}

	return 0;
}
