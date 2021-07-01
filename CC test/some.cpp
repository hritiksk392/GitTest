#include<bits/stdc++.h>
#include<stdint.h>
using namespace std;
int state=0,flag=0,i,p=0,id=0,lineNo=1,jk=500;
char ch;
char Delimeters[]="{}()[];";
unordered_set <char>  delim = { '{','}','(',')','[',']',';'};
unordered_set <char>  relBOperator = { '<','>','=','!','='};
FILE *f;
string word ="";

unordered_map<string,int> symbolTable;
unordered_set <string> rel = { "<=",">=","==","!="};
unordered_set <string> kw =  {"int","if","else","for","while","break","string","return","main"};

void tokenNumberGen(){
	int i=0;
	for (auto x : kw ){
		symbolTable[x] = 100 +i++;
	}
	i=0;

	for(auto x : delim){
		word ="";
		word +=x;
		symbolTable[word] = 200 +i++;
	}
	for(auto x : relBOperator){
		word ="";
		word +=x;
		symbolTable[word] = 200 +i++;
	}
	for(auto x : rel){
		symbolTable[x] = 200 +i++;
	}
	symbolTable["*"] = 200 + i++;
	symbolTable["+"] = 200 + i++;
	symbolTable["&"] = 200 + i++;
	symbolTable["&&"] = 200 + i++;
	word = "";

}

void errorRoutine(){
	cout <<"Lexical error: Sign undefined -> "<<ch<<", line number "<<lineNo<<endl;
	while(ch!=EOF && ch!=';') ch = fgetc(f);
	state=0;
}

void commentDFA(){
	ch = fgetc(f);
	int stline = lineNo;
	while(ch!=EOF && ch!='#') {ch = fgetc(f);
		if(ch=='\n') lineNo++;
	} 

	if(ch==EOF) 
		cout <<"Lexical error: Comment Element missing, line number "<<stline<<endl;

	state=0;



}
void identifierDFA(){

	state = (isalpha(ch))?1:2;

	switch(state){
		case 1:
		word += ch;

		while(isalnum(ch=fgetc(f))) word+=ch;
		fseek(f,-1,SEEK_CUR);

		if(kw.find(word)!=kw.end()){
			

			cout<<"Token "<<symbolTable[word]<< " String Keyword "<<word<<", line number "<<lineNo<<endl;
      			 
		}
		else{
			if(symbolTable[word]==0) symbolTable[word] = jk++;
			cout <<"Token "<<symbolTable[word]<<" String Identifier "<<word<<", line number "<<lineNo<<endl;
		}
		break;

		case 2:
		word += ch;

		while(isdigit(ch=fgetc(f))) word+=ch;
		fseek(f,-1,SEEK_CUR);
		if(symbolTable[word]==0) symbolTable[word] = jk++;

		cout <<"Token "<<symbolTable[word]<<" String Number "<<word<<", line number "<<lineNo<<endl;
    	break;

    	default:
    	errorRoutine();

	}
	word = "";

}

void relationDFA(){
	word = "";
	word+=ch;
		switch(ch){
			case '<':
			state =1;
			break;

			case '=':
			state =2;
			break;

			case '>':
			state =3;
			break;

			case '!':
			state =4;
			break;


			default:
			errorRoutine();
			break;
		}

		switch(state){
			case 1:
			 ch=fgetc(f);
			
			 if(ch=='='){
			 	word+=ch;
			 	cout <<"Token "<<symbolTable[word]<<" String <= (LE),line number "<<lineNo<<endl;
			 }
			 else{
			 	cout <<"Token "<<symbolTable[word]<<" String < (LT),line number "<<lineNo<<endl;
			 	fseek(f,-1,SEEK_CUR);
			 }
			break;

			case 2:
			 ch=fgetc(f);
			 if(ch=='='){
			 	word+=ch;
			 	cout <<"Token "<<symbolTable[word]<<" String == (EQ),line number "<<lineNo<<endl;
			 }
			 else{
			 	cout <<"Token "<<symbolTable[word]<<" String = Assignment,line number "<<lineNo<<endl;
			 	fseek(f,-1,SEEK_CUR);
			 }
			break;

			case 3:
			 ch=fgetc(f);
			 if(ch=='='){
			 	word+=ch;
			 	cout <<"Token "<<symbolTable[word]<<" String >= (GE),line number "<<lineNo<<endl;
			 }
			 else{
			 	cout <<"Token "<<symbolTable[word]<<" String > (GT),line number "<<lineNo<<endl;
			 	fseek(f,-1,SEEK_CUR);
			 }
			break;

			case 4:
			 ch=fgetc(f);
			 if(ch=='='){
			 	word+=ch;
			 	cout <<"Token "<<symbolTable[word]<<" String != (NE),line number "<<lineNo<<endl;
			 }
			 else{
			 	cout <<"Token "<<symbolTable[word]<<" String ! (NEG),line number "<<lineNo<<endl;
			 	fseek(f,-1,SEEK_CUR);
			 }
			break;


			default:
			errorRoutine();
			break;

		}
	word="";

}

void stringLiteralDFA(){
	word ="";
	int stline = lineNo;
	ch = fgetc(f);
	while(ch!=EOF && ch!='"') {word+=ch; 
		if(ch=='\n') lineNo++;
		ch = fgetc(f);

	 }

	if(ch==EOF) 
		cout <<"Lexical error: String Literal missing, line number "<<stline<<endl;
	else{
		if(symbolTable[word]==0) symbolTable[word] = jk++;

		cout <<"Token "<<symbolTable[word]<<" String Literal =" <<word<< ",line number "<<lineNo<<endl;
		word="";
		state=0;
	}



}

void arithOperatorDFA(){
	word="";
	word+=ch;
	switch(ch){
		case '*':
		cout <<"Token "<<symbolTable[word]<<" multiplication operator *,line number "<<lineNo<<endl;
		break;
		case '+':
		cout <<"Token "<<symbolTable[word]<<" addition operator +,line number "<<lineNo<<endl;
		break;
		case '&':
		ch= fgetc(f);
		if(ch=='&') {
			word+=ch;
			cout <<"Token "<<symbolTable[word]<<" Logical and operator &&,line number "<<lineNo<<endl;}
		else{
			fseek(f,-1,SEEK_CUR);
			cout <<"Token "<<symbolTable[word]<<" Binary and operator,line number "<<lineNo<<endl;
		}
		break;


	}
	word="";

}
int main(){
	
  f=fopen("input.txt","r");
  bool exit=false;
	tokenNumberGen();
  while(!exit){

  	switch(state){
  		case 0:
  		 ch= fgetc(f);

  		if(isalnum(ch))
      	{
        	identifierDFA();
        	state=0;
     	}

 		else if(ch=='<' || ch=='>' ||ch=='=' ||ch=='!'){
 			relationDFA();
 			state=0;
 		}

 		else if(delim.find(ch)!=delim.end()){
 			word+=ch;

 			cout <<"Token "<<symbolTable[word]<<" String "<<ch<<",line number "<<lineNo<<endl;
 			state=0;

 		}

 		else if(ch =='*' || ch=='&'||ch=='+'){
 			arithOperatorDFA();
 			state =0;
 		}
 		else if(ch == '"'){
 			 stringLiteralDFA();
 			state =0;
 		}
     	else if(ch=='\n'){
     		lineNo++;
     	}
     	else if (ch == '#'){
     		commentDFA();
     		state=0;

     	}
     	else if(ch == ' '|| ch=='\t' || ch==EOF){
     		if(ch==EOF) exit =true;
 			continue;
 		}
     	else {
     		errorRoutine();
     	}
     	
     	
     	break;

  	}
  	word="";
  	if(ch==EOF) exit = true;


  }
  fclose(f);
  return 0;




}