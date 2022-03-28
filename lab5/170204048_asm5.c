#include<stdio.h>
#include<string.h>

char str[1000];
int i = 0;
int f,l;
void A()
{
    if(str[i] == 'a')
    {
        i++;
    }
    else
    {
        f = 0;
        return;
    }
    if( i == 1)
    {
        /*d();
        if(f == 1)
        {
            return;
        }*/
        //else
        //{
            X();
            if(f == 1)
            {
                d();
                return;
            }
            else
            {
                return;
            }
        //}
    }
}
void X()
{
    if(str[i] == 'b' && str[i+1] == 'b')
    {
        i++;
        i++;
        f = 1;
    }
    else if(str[i] == 'b' && str[i+1] == 'c')
    {
        i++;
        i++;
        f = 1;
    }
    else if(str[i] == 'y')
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
        X();
    }
}
void d()
{
    if(str[i] == 'd')
    {
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
    while(1)
    {
        f = -1;
        i = 0;
        //str[0] = '\0';
    gets(str);
    l = strlen(str);
    A();
    if( f == 1)
        printf("\ncorrect\n");
    else if( f == 0)
        printf("\nincorrect\n");
    }
    return 0;
}


