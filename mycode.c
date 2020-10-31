#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int main(){
	
	void sigint_handler(int sig);
	int i, num = 0;
	int pipefds[2];
	int number;
	int math;


	if (signal(SIGINT, sigint_handler) == SIG_ERR){
		perror("signal");
		exit(1);
	}
	
	if(pipe(pipefds) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	pid_t pid = fork();
	
	if(pid == 0){
	printf("Enter an integer: \n");
	scanf("%d", &number);
	close(pipefds[0]); 
	write(pipefds[1], &number, sizeof(number));
	}
	else if(pid > 0){
	wait(NULL);
	close(pipefds[1]);
	read(pipefds[0], &math, sizeof(math));
	
	for (i = 2; i <= math / 2; ++i) {

        // condition for even
    if (math % i == 0){
        num = 2;
        break;
       }
    }

    if (math == 1){
        printf("This is not even neither odd number.\n");
    }
    else {
        if (num % 2 == 0)
            printf("%d is an even number.\n", math);
        else
            printf("%d is an odd  number.\n", math);
    }
}
	
	return EXIT_SUCCESS;
}

void sigint_handler(int sig){
	printf("Please try again\n");
}
