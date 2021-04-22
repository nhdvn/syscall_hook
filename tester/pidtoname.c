#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    int pid = atoi(argv[1]);

    int n = atoi(argv[2]);

    char *name = (char *) malloc(n * sizeof(char));

    int ret = syscall(334, pid, name, n);

    if (ret == 0)
    {
        printf("found pname: %s \n", name);
    }
    else if (ret == -1)
    {
        printf("unknow pid \n");
    }
    else 
    {
        printf("pname length: %d \n", ret);
    }
}