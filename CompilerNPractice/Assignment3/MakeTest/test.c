#include <stdio.h>

extern int f1(void);
extern int f2(void);

int main(void)
{
    printf("Hello, world!\n");

    f1();
    f2();

    return 0;
}