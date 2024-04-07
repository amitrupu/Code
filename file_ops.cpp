#include <stdio.h>
#include <malloc.h>

void foo() {
    int *p = (int *)malloc(sizeof(int) * 10);
    printf("%p %p\n", p, &p);
}
int main() {
    foo();
    foo();
    foo();

#if 0
    const char *fname = "file_ops.cpp";
    FILE *fp = fopen(fname, "r");
    if (!fp) {
        printf("Could not open %s file.\n", fname);
        return 1;
    }
    while (!feof(fp)) {
        // printf("%c", fgetc(fp));
        char *c;
        fscanf(fp, "%c", &c);
        printf("%c", c);
    }
    fclose(fp);
#endif
    return 0;
}