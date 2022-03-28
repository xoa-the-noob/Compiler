#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include <stdlib.h>


int isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
   ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
   ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
   ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return 1;
    else
        return 0;
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
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' ||
    ch == '>' ||ch == '=' || ch == '<' ||ch == '!' || ch == '&' ||ch == '|')
        return 1;
    else
        return 0;
}

int isSeperator(char ch)
{
    if((ch == ';') ||(ch == ',') || (ch == '\''))
        return 1;
    else
        return 0;
}

int isParenthesis(char ch)
{
    if( (ch == '(') || (ch == ')') || (ch == '[') || (ch == ']') )
        return 1;
    else
        return 0;
}

int isBracket(char ch)
{
    if( (ch == '{') || (ch == '}') )
        return 1;
    else
        return 0;
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

int isNumericConstantDFA(char *lex)
{
    int i, l, s;
    i=0;
    if(isdigit(lex[i]))
    {
        s=1;
        i++;
    }
    else if(lex[i]=='.')
    {
        s=2;
        i++;
    }
    else
        s=0;
    l=strlen(lex);
    if(s==1)
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
                s=1;
            else if(lex[i]=='.')
            {
                s=2;
                i++;
                break;
            }
            else
            {
                s=0;
                break;
            }
        }
    if(s==2)
        if(isdigit(lex[i]))
        {
            s=3;
            i++;
        }
        else
            s=0;
    if(s==3)
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
                s=3;
            else
            {
                s=0;
                break;
            }
        }
    if(s==3)
        s=1;
    return s;
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
   return;
}

int main(void)
{
    char superString[1000000];
    char c;
    FILE *p1;

    p1 = fopen("170204048_Asm1_O1.txt","r");

    if(!p1)
    {
        printf("\nFile  cant be opened");
    }
    else{
        //while((c = fgetc(p1)) != EOF )
        //{
            fgets (superString, 1000000, p1);

        //}
    }
    //printf("%c",superString[0]);
    detectTokens(superString);

    //puts(superString);

    return 0;
}
