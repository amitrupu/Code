#include <stdio.h>
int word_count(FILE *fp)
{
	int c = 1;
	char ch = fgetc(fp);
	while (ch != EOF) {
		if (ch == '\n') c++;
		ch = fgetc(fp);
	}
	return c;
}
int main()
{
	FILE *fwp = fopen("abc.txt", "w");
	fprintf(fwp, "%s\n", "abc");
	fprintf(fwp, "%s\n", "abf");
	fprintf(fwp, "%s", "abd");
	fclose(fwp);
	FILE *fp = fopen("abc.txt", "r");
	printf("%d\n", word_count(fp));
    {
        char ch = EOF;
        unsigned char uch = EOF;
        printf("%d %d %d\n", ch, EOF, (ch == EOF));
        printf("%d %d %d\n", uch, EOF, (uch == EOF));
    }
	return 0;
}
