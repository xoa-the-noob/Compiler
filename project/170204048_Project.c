#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include <stdlib.h>
char t[9999][9999],IdType[9999][9999],DataType[9999],Value[9999];
char identifier[1000][1000];
int l[9999],totalIdentifiers=0;
int rnum = 0;
char scope[1000][1000];
char line[100][9999];

typedef struct SymbolTable
{
    char name[100];
    char idType[100];
    char dataType[100];
    char scope[100];
    char value[100];
} SymbolTable;
SymbolTable st[9999];

int isDataType(char *s)
{
    if ((strcmp(s, "int") == 0) || (strcmp(s, "float") == 0) || (strcmp(s, "long") == 0) || (strcmp(s, "long long") == 0) || (strcmp(s, "double") == 0) || (strcmp(s, "char") == 0)) return 1;
    else return 0;
}
int isNumericConstantDFA(char *lex)
{
    int i, l, s;
    i=0;
    if(isdigit(lex[i])) { s=1; i++; }
    else if(lex[i]=='.') { s=2; i++; }
    else s=0;
    l=strlen(lex);
    if(s==1)
        for(; i<l; i++)
        {
            if(isdigit(lex[i])) s=1;
            else if(lex[i]=='.') { s=2; i++; break; }
            else { s=0; break; }
        }
    if(s==2)
        if(isdigit(lex[i])) { s=3; i++; }
        else s=0;
    if(s==3)
        for(; i<l; i++)
        {
            if(isdigit(lex[i])) s=3;
            else { s=0; break; }
        }
    if(s==3) s=1;
    return s;
}
void generateSymbolTable(int i)
{
    int m,n,o;
    int sl  = -1;
    char temp1[9999],temp2[9999],temp3[9999];
    for(m = 0 ; m < i ; m++)
    {
        if(l[m] == 1)
        {
            temp1[0] = '\0';
            temp2[0] = '\0';
            temp3[0] = '\0';
            sl++;
            rnum = sl+1;
        strcpy(st[sl].name,t[m]);

        strcpy(temp1,t[m+1]);

        if(isDataType(t[m-1]) == 1){
        strcpy(st[sl].dataType,t[m-1]);}

        char b2 = '\0';
        strcat(temp1,&b2);
        int x = strcmp(temp1,"(");
        int y = strcmp(temp1,"=");
        if( x == 0 )
        {
            char b2[10] = "func";
            st[sl].idType[0] = '\0';
            strcpy(st[sl].idType,b2);

        }
        else if( x == 1 )
        {
            char b2[10] = "var";
            st[sl].idType[0] = '\0';
            strcpy(st[sl].idType,b2);
             if( y == 0 )
             {
                 if(isNumericConstantDFA(t[m+2]) == 1){
                     strcpy(st[sl].value,t[m+2]);}
             }
        }

        int secondBracket = 0,firstBracket = 0,flag;
        int closing=-1,starting;
            for(n = m ; n >= 0 ; n--)
            {
            strcpy(temp2,t[n]);
            int x1 = strcmp(temp2,"{");
            int xx = strcmp(temp2,"}");
            int xy = strcmp(temp2,"(");
            if( xx == 0 )
            {
                      break;
            }
            if( x1 == 0 )
            {
                    secondBracket = 1;
                    break;
            }
            if( xy == 0 )
            {
                    firstBracket = 1;
                    break;
            }
            }
            if(secondBracket == 1){
              for(o = n ; o>=0 ; o--)
              {
                  strcpy(temp3,t[o]);
                  int y1 = strcmp(temp3,"(");
                  if( y1 == 0 )
                  {
                      strcpy(st[sl].scope,t[o-1]);
                      strcpy(scope[sl],t[o-1]);
                      break;
                  }
              }
            }
            else if(firstBracket == 1){
                  int y1 = strcmp(st[sl-1].idType,"func");
                  if( y1 == 0 )
                  {
                      int y2 = strcmp(st[sl-1].scope,"global");
                      if(y2 == 0)
                      {
                          strcpy(st[sl].scope,st[sl-1].name);
                          strcpy(scope[sl],st[sl-1].name);
                      }
                      else
                      {
                          strcpy(scope[sl],st[sl-1].scope);
                          strcpy(st[sl].scope,st[sl-1].scope);
                      }
                  }
            }

            else
            {
                char b2[10] = "global";
                st[sl].scope[0] = '\0';
                strcpy(st[sl].scope,b2);
                strcpy(scope[sl],b2);
            }
        }

    }
}

void removeDuplicate1()
{
    int i,j,k;
    char temp1[9999],temp2[9999],temp3[9999];
    for(i=0 ; i<rnum ; i++)
    {
        for(j=0; j<rnum ; j++)
        {
            if( i != j )
            {
                int x1 = strcmp(st[i].name,st[j].name);
                int x2 = strcmp(st[i].idType,st[j].idType);
                int x3 = strcmp(st[i].scope,st[j].scope);
                if( x1 == 0 && x2 == 0 && x3 == 0)
                {
                    int y1 = strcmp(st[i].value,"");
                    int y2 = strcmp(st[i].dataType,"");
                    if(y1 == 0)
                    {
                        strcpy(st[i].value,st[j].value);
                    }
                    if(y2 == 0)
                    {
                        strcpy(st[i].dataType,st[j].dataType);
                    }
                }
            }
        }
    }
}
void removeDuplicate2()
{
    int i,j,k;
    char temp1[9999],temp2[9999],temp3[9999];
    for( i = 0 ;i <rnum ; i++)
    {
        for(j=0; j<rnum ; j++)
        {
            if( i != j )
            {
                int x1 = strcmp(st[i].name,st[j].name);
                int x2 = strcmp(st[i].idType,st[j].idType);
                int x3 = strcmp(st[i].scope,st[j].scope);
                if( x1 == 0 && x2 == 0 && x3 == 0)
                {
                    int rowNo = j;
                    if(rowNo < rnum && rowNo > -1)
                    {
                        for(k = rowNo; k < rnum - 1; k++)
                        {
                            strcpy(st[k].name, st[k + 1].name);
                            strcpy(st[k].idType, st[k + 1].idType);
                            strcpy(st[k].dataType, st[k + 1].dataType);
                            strcpy(st[k].scope, st[k + 1].scope);
                            strcpy(st[k].value, st[k + 1].value);
                        }
                        strcpy(st[rnum - 1].name, "");
                        strcpy(st[rnum - 1].idType, "");
                        strcpy(st[rnum - 1].dataType, "");
                        strcpy(st[rnum - 1].scope, "");
                        strcpy(st[rnum - 1].value, "");
                        rnum--;
                  }
              }
            }
        }
    }
}

void storeTable(){
    FILE *fp;
    fp = fopen("symbolTable.txt", "w");
    fprintf(fp,"--------------------------------------------------------------------------------------------------\n");
    fprintf(fp,"SI No.\t\t|Name\t\t|Type\t\t|Data Type\t|Scope\t\t|Value\n");
    for (int i=0; i<rnum; i++)
    {
        fprintf(fp,"---------------------------------------------------------------------------------------------------\n");
        fprintf(fp,"%10d\t|",i);
        fprintf(fp,"%10s\t|",st[i].name);
        fprintf(fp,"%10s\t|",st[i].idType);
        fprintf(fp,"%10s\t|",st[i].dataType);
        fprintf(fp,"%10s\t|",st[i].scope);
        fprintf(fp,"%10s\t|\n",st[i].value);
    }
    fprintf(fp,"--------------------------------------------------------------------------------------------------");
    fclose(fp);
}


void insert()
{
    char name1[100], idtype[100], dataype1[100], scopearray[100], value[100];
    printf("Name: ");
    scanf("%s", &name1);
    printf("Type: ");
    scanf("%s",&idtype);
    printf("Data Type: ");
    scanf("%s", &dataype1);
    printf("Scope: ");
    scanf("%s",&scopearray);
    printf("Value: ");
    scanf("%s",&value);
    strcpy(st[rnum].name, name1);
    strcpy(st[rnum].idType, idtype);
    strcpy(st[rnum].dataType, dataype1);
    strcpy(st[rnum].scope, scopearray );
    strcpy(st[rnum].value, value );

    rnum++;

    storeTable();
}

void update()
{
    int rowNo,x;
    printf("Which row you want to update? - ");
    scanf("%d", &x);
    rowNo = x-1;

    if(rowNo < rnum && rowNo > -1)
    {
        while (1)
        {
            printf("\n:::: ----------- UPDATE MODE --------- ::::\n");
            printf("1.Update name\n2.Update Id Type\n3.Update Datatype\n4.Update Scope\n5.Update Value\n6. to exit from update mode.\n");
            printf("Select Operation: ");

            int option;
            scanf("%d", &option);

            if(option == 6) return;

            char str1[100];
            switch(option)
            {
            case 1:
                printf("Enter new name: ");
                scanf("%s",&str1);
                strcpy(st[rowNo].name, str1);
                break;
            case 2:
                printf("Enter new Id Type: ");
                scanf("%s",&str1);
                strcpy(st[rowNo].idType, str1);
                break;
            case 3:
                printf("Enter new Data Type: ");
                scanf("%s",&str1);
                strcpy(st[rowNo].dataType, str1);
                break;
            case 4:
                printf("Enter new scope: ");
                scanf("%s",&str1);
                strcpy(st[rowNo].scope, str1);
                break;
            case 5:
                printf("Enter new value: ");
                scanf("%s",&str1);
                strcpy(st[rowNo].value, str1);
                break;
            default:
                printf("\n\n:::: ---------- Value updated ----------- ::\n\n");
                storeTable();
            }
        }
    }
    else
    {
        printf("Invalid row number!!!\n");
    }

}

void deleteRow()
{
    int rowNo,x;
    printf("Which row you want to delete: ");
    scanf("%d", &x);
     rowNo = x-1;

    if(rowNo < rnum && rowNo > -1)
    {
        for(int i = rowNo; i < rnum - 1; i++)
        {
            strcpy(st[i].name, st[i + 1].name);
            strcpy(st[i].idType, st[i + 1].idType);
            strcpy(st[i].dataType, st[i + 1].dataType);
            strcpy(st[i].scope, st[i + 1].scope);
            strcpy(st[i].value, st[i + 1].value);
        }

        strcpy(st[rnum - 1].name, "");
        strcpy(st[rnum - 1].idType, "");
        strcpy(st[rnum - 1].dataType, "");
        strcpy(st[rnum - 1].scope, "");
        strcpy(st[rnum - 1].value, "");
        rnum--;

        printf("\n\n:::: ---------- %d ROW DELETED ----------- ::\n\n",rowNo);
    }
    storeTable();
}

void  searchData()
{
    while (1)
    {
        printf("\n:::: ----------- SEARCH MODE --------- ::::\n");
        printf("1.Search name\n2.Search Id Type\n3.Search Datatype\n4.Search Scope\n5.Search Value\n6. to exit from search mode.\n");
        printf("Select Operation: ");

        int option;
        scanf("%d", &option);
        if(option == 6) return;

        char str1[100];
        int found = 0;
        //int slNo = 1;

        switch(option)
        {
        case 1:
            printf("Enter a name: ");
            scanf("%s",&str1);
            printf("SI No.\t\t|Name\t\t|Type\t\t|Data Type\t|Scope\t\t|Value\n");
            for(int i = 0; i < rnum; i++)
            {
                if(strcmp(st[i].name, str1) == 0)
                {
                    found = 1;
                    printf("---------------------------------------------------------------------------------------------------\n");
                    printf("%10d\t|",i);
                    printf("%10s\t|",st[i].name);
                    printf("%10s\t|",st[i].idType);
                    printf("%10s\t|",st[i].dataType);
                    printf("%10s\t|",st[i].scope);
                    printf("%10s\t|\n",st[i].value);
                    //slNo++;
                }
            }
            break;
        case 2:
            printf("Enter a Id Type: ");
            scanf("%s",&str1);
            printf("SI No.\t\t|Name\t\t|Type\t\t|Data Type\t|Scope\t\t|Value\n");
            for(int i = 0; i < rnum; i++)
            {
                if(strcmp(st[i].idType, str1) == 0)
                {
                    found = 1;
                    printf("---------------------------------------------------------------------------------------------------\n");
                    printf("%10d\t|",i);
                    printf("%10s\t|",st[i].name);
                    printf("%10s\t|",st[i].idType);
                    printf("%10s\t|",st[i].dataType);
                    printf("%10s\t|",st[i].scope);
                    printf("%10s\t|\n",st[i].value);
                    //slNo++;
                }
            }
            break;
        case 3:
            printf("Enter a Data Type: ");
            scanf("%s",&str1);
            printf("SI No.\t\t|Name\t\t|Type\t\t|Data Type\t|Scope\t\t|Value\n");
            for(int i = 0; i < rnum; i++)
            {
                if(strcmp(st[i].dataType, str1) == 0)
                {
                    found = 1;
                    printf("---------------------------------------------------------------------------------------------------\n");
                    printf("%10d\t|",i);
                    printf("%10s\t|",st[i].name);
                    printf("%10s\t|",st[i].idType);
                    printf("%10s\t|",st[i].dataType);
                    printf("%10s\t|",st[i].scope);
                    printf("%10s\t|\n",st[i].value);
                    //slNo++;
                }
            }
            break;
        case 4:
            printf("Enter a scope: ");
            scanf("%s",&str1);
            printf("SI No.\t\t|Name\t\t|Type\t\t|Data Type\t|Scope\t\t|Value\n");
            for(int i = 0; i < rnum; i++)
            {
                if(strcmp(st[i].scope, str1) == 0)
                {
                    found = 1;
                    printf("---------------------------------------------------------------------------------------------------\n");
                    printf("%10d\t|",i);
                    printf("%10s\t|",st[i].name);
                    printf("%10s\t|",st[i].idType);
                    printf("%10s\t|",st[i].dataType);
                    printf("%10s\t|",st[i].scope);
                    printf("%10s\t|\n",st[i].value);
                    //slNo++;
                }
            }
            break;
        case 5:
            printf("Enter a value: ");
            scanf("%s",&str1);
            printf("SI No.\t\t|Name\t\t|Type\t\t|Data Type\t|Scope\t\t|Value\n");
            for(int i = 0; i < rnum; i++)
            {
                if(strcmp(st[i].value, str1) == 0)
                {
                    found = 1;
                    printf("---------------------------------------------------------------------------------------------------\n");
                    printf("%10d\t|",i);
                    printf("%10s\t|",st[i].name);
                    printf("%10s\t|",st[i].idType);
                    printf("%10s\t|",st[i].dataType);
                    printf("%10s\t|",st[i].scope);
                    printf("%10s\t|\n",st[i].value);
                    //slNo++;
                }
            }
            break;
        }
        if(found)printf("\n\n:::: ---------- DATA FOUND ----------- ::\n\n");
        else printf("\n\n:::: ---------- NOO DATA FOUND!! ----------- ::\n\n");
    }
}

void display()
{
    int slNo=1;
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("SI No.\t\t|Name\t\t|Type\t\t|Data Type\t|Scope\t\t|Value\n");
    for (int i=0; i<rnum; i++)
    {
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("%10d\t|",slNo);
        printf("%10s\t|",st[i].name);
        printf("%10s\t|",st[i].idType);
        printf("%10s\t|",st[i].dataType);
        printf("%10s\t|",st[i].scope);
        printf("%10s\t|\n",st[i].value);
        slNo++;
    }
    printf("--------------------------------------------------------------------------------------------------");
}

int isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||ch == '/' || ch == ',' || ch == ';' || ch == '>' ||ch == '<' || ch == '=' || ch == '(' || ch == ')' ||ch == '[' || ch == ']' || ch == '{' || ch == '}') return 1;
    else return 0;
}

int isKeyword(char *str)
{
    if(!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "while") || !strcmp(str, "do") ||    !strcmp(str, "break") || !strcmp(str, "continue")
   || !strcmp(str, "double") || !strcmp(str, "float") || !strcmp(str, "return") || !strcmp(str,    "char") || !strcmp(str, "case") || !strcmp(str, "char")
   || !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "short") || !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "unsigned")
   || !strcmp(str, "void") || !strcmp(str, "static") || !strcmp(str, "struct") || !strcmp(str, "goto"))
        return 1;
    else
    {
         int i, l, s;
        i = 0;
    if (str[0]=='i')
    {
        s = 1;
        i++;
    }
    else
    {
        s = 0;
    }
    if (s == 1)
    {
        if (str[1]== 'n')
            {
                s = 2;
            }
            else
            {
                s = 0;
            }
    }
    if(s ==2 )
    {
        if(str[2] == 't')
        {
            s = 3;
        }
        else
        {
            s = 0;
        }
    }
       if (s == 0 || s==1)
        return 0;
        else
            return 1;
    }

}


int isOperator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' ||ch == '>' ||ch == '=' || ch == '<' ||ch == '!' || ch == '&' ||ch == '|') return 1;
    else return 0;
}

int isSeperator(char ch)
{
    if((ch == ';') ||(ch == ',') || (ch == '\'')) return 1;
    else return 0;
}

int isParenthesis(char ch)
{
    if( (ch == '(') || (ch == ')') || (ch == '[') || (ch == ']') ) return 1;
    else return 0;
}

int isBracket(char ch)
{
    if( (ch == '{') || (ch == '}') ) return 1;
    else return 0;
}

int isIdentifierDFA(char *lex)
{
    int i, l, s;
    i = 0;
    if (isalpha(lex[i]) || lex[i] == '_')
    {
        s = 1;
        i++;
    }
    else
    {
        s = 0;
    }
    l = strlen(lex);
    if (s == 1)
    {
        for(; i < l; i++)
        {
            if (isalnum(lex[i]) || lex[i] == '_')
            {
                s = 2;
            }
            else
            {
                s = 0;
                break;
            }
        }
    }
    if (s == 0)
        return 0;
    else
        return 1;
}


char* subString(char* str, int startingIndex, int endingIndex) {
   int i;
   char* subStr = (char*)malloc( sizeof(char) * (endingIndex - startingIndex + 2));
   for (i = startingIndex; i <= endingIndex; i++)
      subStr[i - startingIndex] = str[i];
   subStr[endingIndex - startingIndex + 1] = '\0';
   return (subStr);
}
void detectTokens(char* str) {

   FILE *p2;
   p2 = fopen("170204048_Asm1_O2.txt","w");
   int startingIndex = 0, endingIndex = 0;
   int length = strlen(str);
   while (endingIndex <= length && startingIndex <= endingIndex)
   {
      if(isDelimiter(str[endingIndex]) == 0)
      endingIndex++;

      if(isDelimiter(str[endingIndex]) == 1 && startingIndex == endingIndex)
      {
         if(isOperator(str[endingIndex]) == 1)
         {
               printf("\n[Operator : %c] ", str[endingIndex]);
               fputs("[Operator ",p2);
               fputc(str[endingIndex],p2);
               fputs("]",p2);
         }
         if(isSeperator(str[endingIndex]) == 1)
         {
               printf("\n[Seperator : %c] ", str[endingIndex]);
               fputs("[Seperator ",p2);
               fputc(str[endingIndex],p2);
               fputs("]",p2);
         }
         if(isParenthesis(str[endingIndex]) == 1)
         {
               printf("\n[Parentheses : %c] ", str[endingIndex]);
               fputs("[Parentheses ",p2);
               fputc(str[endingIndex],p2);
               fputs("]",p2);
         }
         if(isBracket(str[endingIndex]) == 1)
         {
               printf("\n[Bracket : %c] ", str[endingIndex]);
               fputs("[Bracket ",p2);
               fputc(str[endingIndex],p2);
               fputs("]",p2);
         }
         endingIndex++;
         startingIndex = endingIndex;
      }
      else if(isDelimiter(str[endingIndex]) == 1 && startingIndex != endingIndex || (endingIndex == length && startingIndex != endingIndex))
      {
         char* subStr = subString(str, startingIndex, endingIndex - 1);
         if(isKeyword(subStr) == 1)
         {
              printf("\n[Keyword : %s] ", subStr);
              fputs("[Keyword ",p2);
              fputs(subStr,p2);
              fputs("]",p2);
         }
         else if(isNumericConstantDFA(subStr) == 1)
         {

            printf("\n[Numeric Constant : %s] ", subStr);
            fputs("[Numeric ",p2);
            fputs(subStr,p2);
            fputs("]",p2);
         }

         else if(isIdentifierDFA(subStr) == 1)
         {
             printf("\n[Identifier : %s] ", subStr);
             fputs("[Identifier ",p2);
             fputs(subStr,p2);
             fputs("]",p2);
         }
         else
         {
          printf("\nUnknown : %s",subStr);
          fputs("[Unknown ",p2);
          fputs(subStr,p2);
          fputs("]",p2);
         }
         startingIndex = endingIndex;
      }

   }
   fclose(p2);
   return;
}

int main(void)
{
    FILE *p1,*p2,*p3,*p4;
    char c,d,e;
    int f = 0;
    p1 =  fopen("input.c","w");
    p2 = fopen("offline1.1.txt","w");
    p3 = fopen("170204048_Asm1_O1.txt","w");

    printf("\nEnter the code. Type $$$$ to exit:\n");
    while(1)
    {
        scanf("%c",&c);
        if( c == '$' )
        {
            scanf("%c",&c);
            if( c == '$' )
            {
                scanf("%c",&c);
                if( c == '$' )
                {
                    scanf("%c",&c);
                    if( c == '$' )
                    {
                        break;
                    }
                }
            }

        }
        else
            fputc(c,p1);
    }
    fclose(p1);

    p1 =  fopen("input.c","r");
    if(!p1)
    {
        printf("\nFile  cant be opened");
    }
    else{
        while((c = fgetc(p1)) != EOF )
        {
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
    p2 = fopen("offline1.1.txt","r");

      while((c = fgetc(p2)) != EOF )
        {
            if(c == ' ')
            {
                fputc(c,p3);
                if((d = fgetc(p2)) != ' ')
                {
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
                    continue;
            }

            else if (c == '  ' || c == '\t'){ f++;
            }
            else{
                fputc(c,p3);
            }
      }

    fclose(p3);
    fclose(p2);

    printf("\n-----------------STEP 1: ------------------------\n");

    p3 = fopen("170204048_Asm1_O1.txt","r");

    while( ( (c = fgetc(p3)) != EOF ) )
    {
        printf("%c",c);
    }

    fclose(p3);

    char superString[1000000];
    p3 = fopen("170204048_Asm1_O1.txt","r");

    if(!p3)
    {
        printf("\nFile  cant be opened");
    }
    else{
        fgets (superString, 1000000, p1);
    }

    printf("\n-----------------STEP 2: ------------------------\n");

    detectTokens(superString);

    char temp[1000];
    char temp2[1000]={};
    int i = 0 , j = 0 , k = 0,m,n,x=0;
    p2 = fopen("170204048_Asm1_O2.txt","r");

    while( ( (c = fgetc(p2)) != EOF ) )
    {
        if(c == '[')
        {
            int x = strcmp(temp, "Identifier");
            int y = strcmp(temp, "Bracket");
            if( x == 0)
            {
                l[i] = 1;
                i++;
            }
            else if( x == 1 )
            {
                l[i] = 0;
                i++;
            }
            else if( y == 0 )
            {
                l[i] = 0;
                i++;
            }

            temp[0] = '\0';

            while( ( (c = fgetc(p2)) != ' ' ) )
            {
                    strncat(temp, &c, 1);

            }
            if( c == ' ')
            {
                j = 0;
                while( ( (c = fgetc(p2)) != ']' ) )
                {
                    strncat(temp2, &c, 1);
                    j = strlen(temp2);
                    temp2[j] = '\0';

                }
                for(m = 0 ; m < j ; m++)
                {
                    t[i][m] = temp2[m];
                }
                temp2[0] = '\0';
            }
            }
        }
    fclose(p2);

    p4 = fopen("170204048_Asm3_O1.txt","w");
    for(m = 0 ; m<=i ; m++)
    {
        fputc('[',p4);
        if(l[m] == 1)
        {
            totalIdentifiers++;
            fputs("id ",p4);
        }
        for( n = 0 ; t[m][n]!='\0' ; n++)
        {
            fputc(t[m][n],p4);
        }
        fputc(']',p4);
    }
    fclose(p4);

    printf("\n-----------------STEP 3: ------------------------\n");

    p2 = fopen("170204048_Asm3_O1.txt","r");

    while( ( (c = fgetc(p2)) != EOF ) )
    {
        printf("%c",c);
    }
    fclose(p2);

    generateSymbolTable(i);
    removeDuplicate1();
    removeDuplicate2();
    storeTable();
    printf("\n");
    while (1)
    {
        printf("1.Insert\n2.Update\n3.Delete \n4.Search\n5.Display\n6. exit\n");
        printf("Select Operation: ");
        int option;
        scanf("%d", &option);
        if(option == 1) insert(), printf("\n");
        else if(option == 2) update(), printf("\n");
        else if(option == 3) deleteRow(), printf("\n");
        else if(option == 4) searchData(), printf("\n");
        else if(option == 5) display(), printf("\n");
        else if(option == 6) break;
        else printf("Invalid Option");
    }




    printf("\n-----------------STEP 4: ------------------------\n");
    p3 = fopen("offline1.1.txt","r");
    p4 = fopen("offline4.2.txt","w");
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
    fclose(p3);
    fclose(p4);


    p3 = fopen("offline4.2.txt","r");

    while( ( (c = fgetc(p3)) != EOF ) )
    {
        printf("%c",c);
    }

    fclose(p3);

    p3 = fopen("offline4.2.txt","w");

    if(!p2)
    {
        printf("\nFile  cant be opened");
    }
    else{
        while((c = fgetc(p2)) != EOF )
        {
            if( !isOperator(c) && !isSeperator(c) && !isParenthesis(c) && !isDelimiter(c) && !isBracket(c) && c != '\n' )
            {
                strncat(temp, &c, 1);
            }
            else if( isOperator(c) || isSeperator(c) || isParenthesis(c) || isDelimiter(c) || isBracket(c) )
            {
                if(isKeyword(temp) == 0)
                {
                    fputs(temp,p3);
                }
                else if(isIdentifierDFA(temp) == 1)
                {
                    fputs("id ",p3);
                    fputs(temp,p3);
                }
                else if(isNumericConstantDFA(temp) == 1)
                {
                   fputs(temp,p3);
                }
                fputc(c,p3);
                temp[0] = '\0';

            }
            else
            {
                fputc(c,p3);
            }

       }
    }
    fclose(p2);
    fclose(p3);

    printf("\nUndeclared variables:\n");
    for(i=0 ; i<15 ;i++)
    {
        char str[100];
        strcpy(str,st[i].scope);
        int x1 = strcmp(str,"");
        if(x1 == 0)
        {
            puts(st[i].name);
        }
    }

    int sb=0;
    for(i=0 ; i<15 ;i++)
    {
        for(j=0 ; line[i][j] != '\0' ; j++)
        {
            if(line[i][j] == '{')
            {
                    sb++;
            }
            else if(line[i][j] == '}')
            {
                sb--;
            }
            else if(line[i][j] == ';' && line[i][j+1] == ';')
            {
                    printf("\nDuplicate token at line %d",i+1);
                    break;
            }
        }
        if(sb < 0)
        {
            printf("\nUnmatched } at line %d",i+1);
            sb = 0;

        }
    }
    if(sb != 0)
    {
        printf("\nUnmatched } at line %d",i);

    }
    int chk=0;
    for(i=0; i<15 ; i++)
    {
        char *ret1 = strstr(line[i], "if");
        char *ret2 = strstr(line[i], "else");

        char *dt1 = strstr((*(line + i)) , "int int");
        char *dt2 = strstr(line[i], "float float");
        char *dt3 = strstr(line[i], "double double");
        char *dt4 = strstr(line[i], "char char");

        if(dt1!= NULL)
        {
            printf("\nTwo or more datatypes in declaration specifier at line %d",i+1);
        }

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


