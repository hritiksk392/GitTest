%option noyywrap
%{
#include "y.tab.h"
#
%}
%%
(ab)* return A;
[c]+ return C;
[d]+ return D;
.|"\n" return 0;
%%
