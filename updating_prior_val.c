#include "types.h"
#include "user.h"

#define WNOHANG 	1

int main(int argc, char *argv[])
{
	printf(1, "\n This program tests the correctness of your lab#2\n");
    int prior_val, pid;
	if(argc < 3){
		printf(2, "Usage: nice pid priority\n");
	}
	pid = atoi(argv[1]);
	prior_val = atoi(argv[2]);
	if(prior_val < 0 || prior_val > 31){
		printf(2, "Invalid...\n");
	}
	updating_prior_val(pid, prior_val);
	exit(1);
}