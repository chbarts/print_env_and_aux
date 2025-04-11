#include <sys/auxv.h>
#include <errno.h>
#include <stdio.h>

#define ENTRY(NAME) { NAME, #NAME }

typedef struct {
    unsigned long num;
    char *name;
} entry;

static entry arr[] =
    { ENTRY(AT_BASE), ENTRY(AT_BASE_PLATFORM), ENTRY(AT_CLKTCK), ENTRY(AT_DCACHEBSIZE), ENTRY(AT_EGID),
    ENTRY(AT_ENTRY), ENTRY(AT_EUID), ENTRY(AT_EXECFD), ENTRY(AT_EXECFN), ENTRY(AT_FPUCW), ENTRY(AT_GID), ENTRY(AT_HWCAP),
    ENTRY(AT_HWCAP2), ENTRY(AT_ICACHEBSIZE), ENTRY(AT_L1D_CACHEGEOMETRY), ENTRY(AT_L1D_CACHESIZE),
    ENTRY(AT_L1I_CACHEGEOMETRY), ENTRY(AT_L1I_CACHESIZE), ENTRY(AT_L2_CACHEGEOMETRY),
    ENTRY(AT_L2_CACHESIZE), ENTRY(AT_L3_CACHEGEOMETRY), ENTRY(AT_L3_CACHESIZE), ENTRY(AT_PAGESZ),
    ENTRY(AT_PHDR), ENTRY(AT_PHENT), ENTRY(AT_PHNUM), ENTRY(AT_RANDOM), ENTRY(AT_SECURE), ENTRY(AT_UCACHEBSIZE),
    ENTRY(AT_UID), { 0, NULL }
};

int main(int argc, char *argv[])
{
    unsigned long val;
    int i;

    puts("Env:");
    for (i = argc + 1; argv[i] != NULL; i++) {
        puts(argv[i]);
    }

    puts("Aux:");
    for (i = 0; arr[i].name != NULL; i++) {
        val = getauxval(arr[i].num);
        if ((0 == val) && (ENOENT == errno)) {
            printf("%s not found.\n", arr[i].name);
            continue;
        }

        switch (arr[i].num) {
        case AT_BASE_PLATFORM:
        case AT_EXECFN:
        case AT_PLATFORM:
           printf("%s: %s\n", arr[i].name, (char *) val);
            break;
        default:
           printf("%s: %lu\n", arr[i].name, val);
           break;
        }
    }

    return 0;
}
