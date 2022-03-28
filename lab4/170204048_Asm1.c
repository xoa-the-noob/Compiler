#include<stdio.h>
int main(void)
{
    //comment1
    FILE *p1,*p2,*p3;
    char c,d,e;
    int f = 0;
    p1 =  fopen("input.c","r");
    p2 = fopen("offline1.1.txt","w");
    p3 = fopen("170204048_Asm1_O1.txt","w");

    if(!p1)
    {
        printf("\nFile  cant be opened");
    }  /*blcom1*/
    else{  //com2
        while((c = fgetc(p1)) != EOF )
        {
            if( c == '/' )    //com3
            {
                c = fgetc(p1);
                if(c == '/' )
                {
                    while( (c = fgetc(p1)) != '\n');     //com4
                }  /*..*/

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
    p2 = fopen("offline1.1.txt","r");

      while((c = fgetc(p2)) != EOF )
        {
            if(c == ' ')
            {
                //fputc('1',p3);
                fputc(c,p3);
                if((d = fgetc(p2)) != ' ')
                {
                     //fputc('2',p3);
                     fputc(d,p3);
                     continue;
                }
                else
                {
                while( (c = fgetc(p2)) == ' ');
                }
            }

            if (c == '\n')
            {
                    //fputc('3',p3);
                    //fputc(' ',p3);
                    continue;
            }

            else if (c == '  ' || c == '\t'){ f++;
            }
            else{
                //fputc('5',p3);
                fputc(c,p3);
            }
      }

         //printf("%d",f);
    fclose(p3);
    fclose(p2);

    p1 =  fopen("input.c","r");
     while( ( (c = fgetc(p1)) != EOF ) )
    {
        printf("%c",c);
    }

    fclose(p1);

    printf("\n");

    p3 = fopen("170204048_Asm1_O1.txt","r");

    while( ( (c = fgetc(p3)) != EOF ) )
    {
        printf("%c",c);
    }

    fclose(p3);


    return 0;
}

