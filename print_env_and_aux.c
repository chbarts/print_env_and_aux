#include <sys/auxv.h>
#include <errno.h>
#include <stdio.h>

#define print_int_val(key, val) printf("%s: %ul\n", key, val)
#define print_string_val(key, val) printf("%s: %s\n", key, (char *) val)

static char *sarr[] =
    { "AT_BASE", "AT_BASE_PLATFORM", "AT_CLKTCK", "AT_DCACHEBSIZE", "AT_EGID",
    "AT_ENTRY", "AT_EUID", "AT_EXECFD", "AT_EXECFN", "AT_GID", "AT_HWCAP",
    "AT_HWCAP2", "AT_ICACEBASESIZE", "AT_L1D_CACHEGEOMETRY", "AT_L1D_CACHESIZE",
    "AT_L1I_CACHEGEOMETRY", "AT_L1I_CACHESIZE", "AT_L2_CACHEGEOMETRY",
    "AT_L2_CACHESIZE", "AT_L3_CACHEGEOMETRY", "AT_L3_CACHESIZE", "AT_PAGESZ",
    "AT_PHDR", "AT_PHENT", "AT_PHNUM", "AT_RANDOM", "AT_SECURE",
    "AT_UCACHEBSIZE", "AT_UI", NULL
};

static unsigned long arr[] =
    { AT_BASE, AT_BASE_PLATFORM, AT_CLKTCK, AT_DCACHEBSIZE, AT_EGID,
    AT_ENTRY, AT_EUID, AT_EXECFD, AT_EXECFN, AT_GID, AT_HWCAP,
    AT_HWCAP2, AT_ICACEBASESIZE, AT_L1D_CACHEGEOMETRY, AT_L1D_CACHESIZE,
    AT_L1I_CACHEGEOMETRY, AT_L1I_CACHESIZE, AT_L2_CACHEGEOMETRY,
    AT_L2_CACHESIZE, AT_L3_CACHEGEOMETRY, AT_L3_CACHESIZE, AT_PAGESZ,
    AT_PHDR, AT_PHENT, AT_PHNUM, AT_RANDOM, AT_SECURE, AT_UCACHEBSIZE,
    AT_UID, 0
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
    for (i = 0; sarr[i] != NULL; i++) {
        val = getauxval(arr[i]);
        if ((0 == val) && (ENOENT == errno)) {
            printf("%s not found.\n", sarr[i]);
            continue;
        }

        switch (arr[i]) {
        case AT_BASE_PLATFORM:
        case AT_EXECFN:
        case AT_PLATFORM:
            print_string_val(sarr[i], val);
            break;
        default:
            print_int_val(sarr[i], val);
        }
    }

    return 0;
}
