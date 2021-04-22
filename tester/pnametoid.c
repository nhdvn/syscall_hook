#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    long int pid = syscall(333, argv[1]);

    if (pid == -1)
    {
	    printf("unknown pname \n");}
    else
    {  
	    printf("found pid: %ld \n", pid);
	}

    return 0;
}