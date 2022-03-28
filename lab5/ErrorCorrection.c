#include<stdio.h>
#include<string.h>

char str[1000];
int i = 0;
int f,l;
void S()
{
    if(str[i] == 'b')
    {
        i++;
        f = 1;
        return;
    }
    else
    {
        A();
        if( f == 1 )
        {
            B();
            return;
        }
    }
}
void A()
{
    for( i=0 ; i < l-1 ; i++)
    {
        if(str[i] == 'a')
        {
            f = 1;
        }
        else
        {
            f = 0;
        }
    }
}
void B()
{
    if( str[l-1] == 'b')
    {
        i++;
        f = 1;
        //printf("\n%c",str[i]);
        //printf("\nret b");
    }
    else
    {
        f = 0;
    }
    return;
}
int main()
{
    gets(str);
    l = strlen(str);
    S();
    if( f == 1)
        printf("\ncorrect");
    else if( f == 0)
        printf("\nincorrect");
    return 0;
}

