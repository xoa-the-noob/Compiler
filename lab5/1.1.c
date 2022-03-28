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
    if( str[i] == 'a' )
    {
        i++;
        f = 1;
    }
    else
    {
        f = 0;
        return;
    }
    if( i < l-1 )
    {
        A();
    }
}
void B()
{
    if( str[i] == 'b')
    {
        i++;
        f = 1;
        return;
    }
    else
    {
        f = 0;
        return;
    }
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
