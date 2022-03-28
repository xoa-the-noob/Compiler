#include<stdio.h>
int main(void)
{
    //comment1
    char str[] = "a1,";

      int i, l, s;
      i=0;
        if( (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_') )
        {
            s=1; i++;
        }
        else  printf("Not an identifier");
        if( s==1 )
        {
            for( l = i ; l <= (strlen(str) - 1) ; l++)
            {
                /*if( str[l] == ',' || str[l] == ' ')
                {
                    printf("Not an indentifier");
                    break;
                }*/
                if(!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || (str[i] == '_')) )
                {
                 printf("Not an indentifier");
                    break;
                }
            }
                printf("An identifier");
        }

    return 0;
}


