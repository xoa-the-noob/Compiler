/*
Ahsanullah University of Science and Technology
Department of Computer Science and Engineering
Lab Final Examination
Course: CSE 4130 (Formal Languages and Compilers Lab)
Year/Sems: 4/1                           Session: FALL 2020
ID: 170204048                    Set:2
*/
#include<stdio.h>
char line[1000][1000];
int main()
{
    FILE *p1,*p2,*p3,*p4;
    char c,d,e;
    int i,j;

    p4 = fopen("in2.txt","w");
    p3 = fopen("in1.txt","r");
    char str[1009];
    int a=1;
    int b=0;

    while(fgets(str, sizeof(str),p3))
    {
        char buffer[20];
        itoa(a,buffer,10);
        char temp2 = buffer[0];
        char temp3 = buffer[1];
        fputc(temp2,p4);
        fputc(temp3,p4);
        fputs(str,p4);
        strcpy(line[b],str);
        a++;
        b++;
    }
    fclose(p4);
    fclose(p3);

    int chk=0;
    for(i=0; i<999 ; i++)
    {
        char *ret1 = strstr(line[i], "if");
        char *ret2 = strstr(line[i], "else");

        if(ret1 != NULL)
        {
            chk++;
        }
        if(ret2 != NULL)
        {
            chk--;
        }
        if(chk < 0)
        {
            printf("\nUnmatched else at line %d",i+1);
            chk = 0;

        }
    }



    return 0;
}

