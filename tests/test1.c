#include <stdio.h>

void tits(char *a);

int main(void) {

    char a[10] = "titties";
    tits(a);

    return 0;
}

void tits(char *a) {
    printf("%d\n", sizeof(a));
    printf("%c", *(a+1));
}