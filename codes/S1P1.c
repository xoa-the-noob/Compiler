#include<stdio.h>
int main(void)
{
    /*comment1*/
    FILE *p1,*p2;
    char c;
    int flag = 0;

    p1 = fopen("S1P1.c","r");
    p2 = fopen("offline.txt","w");

    if(!p1)
    {
        printf("\nFile cant be opened");
    }
    else{
        while((c = fgetc(p1)) != EOF )
        {
            if(c == '/')
            {
                flag = 1;
                char d;
                if( d = fgetc(p1) == '*')
                {
                    char e,f;  //comment 2
                    while( e = fgetc(p1) != EOF)
                    {
                        if(e == '*')
                        {  /*comment3*/
                            f = fgetc(p1);
                            if(f == '/' )
                            {
                                flag = 0;
                                break;
                            }
                        }
                    }
                }
                else if (d = fgetc(p1) == '/')
                {
                    char e;
                    while(e = fgetc(p1) != EOF)
                    {
                        if(e == '\n')
                        {
                            flag = 0;
                            break;
                        }
                    }
                }
                else{
                    fputc(c,p2);
                }
            }

            if(flag == 0)
            {
                fputc(c,p2);
            }
            else
                fputc(c,p2);
        }
    }

    fclose(p1);
    fclose(p2);

    p2 = fopen("offline.txt.txt","r");

    while( ( (c = fgetc(p2)) != EOF ) )
    {
        printf(" %c ",c);
    }

    fclose(p2);

    return 0;
}
