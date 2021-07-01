%{
#include <stdio.h>
int acnt=0;
int ccnt=0;
int dcnt=0;
%}
%token A C D
%%
R: S { return 1;}
;
S: A C S {acnt++; ccnt++;} | A D S {acnt++; dcnt++;} | C S {ccnt++;} | D S {dcnt++;} | 
    ;
%%


void main(){
    printf("Give input:\n");
    yyparse();
    printf("Valid\n");
    
    printf("Number of substring of type (ab)* is %d\n",acnt);
    printf("Number of substring of type (c+) is %d\n",ccnt);

    printf("Number of substring of type (d+) is %d\n",dcnt);
    exit(0);

}
void yyerror(){
    printf("Invalid Statement\n");
    exit(0);
}