#include <stdio.h>

char *fill(char *a, size_t size);

int main(void) {

    char a[5];
    size_t b;
    fgets(b, 1, stdin);
    fill(a, b);

    return 0;
}

char *fill(char *a, size_t size) {
    printf("%d", sizeof(a));
    return a;
}