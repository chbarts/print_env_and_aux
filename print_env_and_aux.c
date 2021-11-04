#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;

    puts("Env:");
    for (i = argc + 1; argv[i] != NULL; i++) {
        puts(argv[i]);
    }

    puts("Aux:");
    for (i = i + 1; argv[i] != NULL; i++) {
        puts(argv[i]);
    }

    return 0;
}
