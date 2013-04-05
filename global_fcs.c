#include "global_fcs.h"


void printf_b(unsigned int n){

	int c,k;

	for(c = 31; c >= 0; c--){
		k = n >> c;

		if (k & 1)
			printf("1");
		else
			printf("0");
	}

	printf("\n");
}

unsigned long mix(unsigned long a, unsigned long b, unsigned long c){

	a=a-b;  a=a-c;  a=a^(c >> 13);
	b=b-c;  b=b-a;  b=b^(a << 8);
	c=c-a;  c=c-b;  c=c^(b >> 13);
	a=a-b;  a=a-c;  a=a^(c >> 12);
	b=b-c;  b=b-a;  b=b^(a << 16);
	c=c-a;  c=c-b;  c=c^(b >> 5);
	a=a-b;  a=a-c;  a=a^(c >> 3);
	b=b-c;  b=b-a;  b=b^(a << 10);
	c=c-a;  c=c-b;  c=c^(b >> 15);
	return c;
}
