#include<stdio.h>
#include<string.h>

char str[1000];
int i = 0;
int f,l;
int seven,three;
void E()
{
    int pos=-1,j,k,ls,rs;
    char str1[1000],str2[1000];
    char *dt1 = strstr(str, "+");
    char *dt2 = strstr(str, "-");

    if( dt1!= NULL && dt2 == NULL)
    {
        pos = dt1 - (str);
    }
    else if( dt1 == NULL && dt2!= NULL )
    {
        pos = dt2 - (str);
    }
    if(pos>-1)
    {
        for(j=0;j<pos;j++)
        {
        str1[j] = str[j];
        }
        str1[pos] = '\0';
        for(j=0,k=pos+1 ;j<l; j++,k++)
        {
            str2[j] = str[k];
        }
        str2[l] = '\0';
        puts(str1);
        puts(str2);

        i = 0;
        T(str1,pos);
        ls = f;

        i = 0;
        T(str2,strlen(str2));
        ls = f;

        if(ls == 1 && rs == 1)
        {
            f = 1;
            return;
        }
    }
    else
    {
        T(str,strlen(str));
    }
}
void T(char str[1000],int l)
{
    int chk=0;
    F(str);
    if(f == 1)
    {
        i++;
        if(i == l)
        {
            return;
        }

        if(str[i] == '*' || str[i] == '/')
        {
            i++;
            F(str);
            return;
        }
        else
        {
            f = 0;
            return;
        }
    }
}
void F(char str[1000])
{
    if(str[i] == 'a' || str[i] == 'b' ||str[i] == 'c' || str[i] == 'd' ||str[i] == 'e' ||
    str[i] == '0'||str[i] == '1'|| str[i] == '2' ||str[i] == '3' || str[i] == '4' ||
    str[i] == '5' || str[i] == '6' ||str[i] == '7' || str[i] == '8' ||str[i] == '9')
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
    gets(str);
    l = strlen(str);
    E();
    if( f == 1)
        printf("\ncorrect");
    else if( f == 0)
        printf("\nincorrect");
    return 0;
}



