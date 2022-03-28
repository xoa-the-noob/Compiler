#include<stdio.h>
#include<string.h>
int main(void)
{
    FILE *p1,*p2;
    char c,temp;
    int hash=-1,header=-1;
    p1 = fopen("S1P2.c","r");
    p2 = fopen("header.txt","w");

    if(!p1)
    {
        printf("\nFile cant be opened");
    }
    else{
        while((c = fgetc(p1)) != EOF )
        {
            if(c == '#')
            {
                hash = 1;
            }
            else if(c=='<')
            {
                if(hash == 1)
                {
                    header = 1;
                }
                else
                    continue;
            }
            else if(c=='>')
            {
                if(hash ==1)
                {
                    header = 0;
                    hash = 0;
                }
                else
                    continue;
            }

            if(hash == 1 && header == 1 && c != '>' && c != '<')
            {
                fputc(c,p2);
            }
    }
    }
    fclose(p1);
    fclose(p2);

    p2 = fopen("header.txt","r");

    while( ( (c = fgetc(p2)) != EOF ) )
    {
        printf("%c",c);
    }

    fclose(p2);

    return 0;
}
