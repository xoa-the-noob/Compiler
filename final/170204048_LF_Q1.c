/*
Ahsanullah University of Science and Technology
Department of Computer Science and Engineering
Lab Final Examination
Course: CSE 4130 (Formal Languages and Compilers Lab)
Year/Sems: 4/1                           Session: FALL 2020
ID: 170204048                    Set:2
*/
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
    int i,j,f;

    p1 =  fopen("input.txt","r");
    p2 = fopen("offline1.1.txt","w");

    char str[1009];
    int a=1;
    int b=0;
    if(!p1)
    {
        printf("\nFile  cant be opened");
    }
    else{
        while((c = fgetc(p1)) != EOF )
        {
            /*if( c == '/' && (c = fgetc(p1)) != '/' )
            {
                fputc(c,p2);
                continue;
            }*/
            if( c == '/' )
            {
                c = fgetc(p1);
                if(c == '/' )
                {
                    while( (c = fgetc(p1)) != '\n');
                }
                else if(c == '*')
                {
                    while( (c = fgetc(p1)) != 'EOF')
                    {
                        if((c = fgetc(p1)) == '*' && (c = fgetc(p1)) == '/')
                        {
                            break;
                        }
                    }

                }
                else
                    fputc(c,p2);
            }
            else
                fputc(c,p2);

        }
    }
    fclose(p1);
    fclose(p2);

    p4 = fopen("offline4.3.txt","w");
    p3 = fopen("offline1.1.txt","r");

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

    int sb=0;
    for(i=0 ; i<15 ;i++)
    {
        for(j=0 ; line[i][j] != '\0' ; j++)
        {
            if(line[i][j] == '+' ||line[i][j] == '-' ||line[i][j] == '/' ||line[i][j] == '*' ||line[i][j] == '%')
            {
                    sb++;
            }
        }
        if(sb > 0)
        {
            printf("\nLine no. %d : %d",i+1,sb);
            sb = 0;

        }
    }
    return 0;
}
