#include <stdio.h>
#include "itoa.h"

int main() {
    printf("%s\n", i2dec(-39));
    printf("%s\n", ui2hex(95531 - 65536));
    printf("%s\n", ui2hex(9983));
    printf("%s\n", ui2oct(9983));
    printf("%s\n", f2a(0.9987, 2));
    printf("%s\n", f2a(0.008, 2));
    printf("%s\n", f2a(0.008, 5));
    printf("%s\n", f2a(5.008, 5)); // float has a really back precision.
    printf("%s\n", f2a(-1231.008, 5)); // float has a really back precision.
    return 0;
}
