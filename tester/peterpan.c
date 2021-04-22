#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int file = open("in.txt", O_WRONLY | O_CREAT | O_APPEND);

    printf("FILE DESCRIPTION: %d \n", file);

    if (write(file, "I AM BEING TARGETED", 19) == 19)
    {
        printf("WRITE SUCCESS \n");
    }
    else printf("WRITE FAILURE \n");
}