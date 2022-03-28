
#include<stdio.h>
int main(void)
{
    FILE *p1,*p2;
    char c;
    char str[1000];
    int i;
    int j='0';

    p1 = fopen("S1P3.c","r");
    p2 = fopen("num.txt","w");

    if(!p1)
    {
        printf("\nFile cant be opened");
    }
    else{
        while((c = fgetc(p1)) != EOF )
        {
                fputc(c,p2);
        }

        fclose(p1);
        fclose(p2);
        p2 = fopen("num.txt","r");
        while((c = fgetc(p2)) != EOF )
        {
            if( fgets (str, 1000, p2)!=NULL ) {
             /* writing content to stdout */
             //char k = j+ '0';

             //char k;
             //k = (char)j;
             strncat(str, &j, 1);
             puts(str);
             j++;
   }
        }

    }

   // fclose(p1);
   // fclose(p2);

    //p2 = fopen("num.txt","r");

    for(i=0;i<strlen(str);i++)
    {
        printf("%c",str[i]);
    }

    //fclose(p2);

    return 0;
}
