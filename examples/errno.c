#include <errno.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    // pipe(0);
    printf("%d", errno);
}