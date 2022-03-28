#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void)
{
    FILE *p1, *p2;
    char c,num[1000];
    int i,k;
    int j = 0;
    p1 = fopen("S1P3Try2.c", "r");
    p2 = fopen("dfwithLine.txt", "w");

    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
      	while((c = fgetc(p1)) != EOF)
      	{
      	     char str[100000];
      	     fgets(str, 1000, p1);
             char temp = j + '0';
             putc(temp,p2);
             fputs(str,p2);
             j++;
        }
    }
    fclose(p1);
    fclose(p2);

    printf("Code With Line Number:\n\n");
    p2 = fopen("dfwithLine.txt", "r");
   while( ( (c = fgetc(p2)) != EOF ) )
        printf("%c", c);

    return 0;
}
