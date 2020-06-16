
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    printf("%d \n %d", getpid(), getppid());
}