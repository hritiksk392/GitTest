#include<bits/stdc++.h>
#include<stdint.h>
using namespace std;
int state=0,flag=0,i,p=0,id=0,lineNo=1,jk=20;
char ch,word[20],kw[20000][20]={"int","float","char","long","double","if","else","for","while","void","do","switch","case","break"};
char Delimeters[]="{}()[];";
int32_t main(){
  FILE *f;
  f=fopen("input.txt","r");
  bool exit=false;
  while(exit!=true)
  {
    switch(state){
      case 0:
      ch=fgetc(f);
      if(isalnum(ch))
      {
        if(isalpha(ch))
        state=11;
        else
        state=13;
      }
      else if(ch=='<')
        state=1;
      else if(ch=='>')
        state=4;
      else if(ch=='!')
        state=7;
      else if(ch=='=')
        state=9;
      else if(ch=='{'||ch=='}'||ch=='('||ch==')'||ch=='['||ch==']'||ch==';')
        state=15;
      else if(ch=='\n')
        state=16;
      break;
      case 1:
      ch=fgetc(f);
      if(ch=='=')
      state=2;
      else
      state=3;
      break;
      case 2:
      cout<<"Token 151 string <=, line Number "<<lineNo<<endl;
      state=0;
      break;
      case 3:
      fseek(f,-1,SEEK_CUR);
      cout<<"Token 152 string <, line Number "<<lineNo<<endl;
      state=0;
      break;
      case 4:
      ch=fgetc(f);
      if(ch=='=')
      state=5;
      else
      state=6;
      break;
      case 5:
      cout<<"Token 153 string >=, line Number "<<lineNo<<endl;
      state=0;
      break;
      case 6:
      fseek(f,-1,SEEK_CUR);
      cout<<"Token 154 string >, line Number "<<lineNo<<endl;
      state=0;
      break;
      case 7:
      ch=fgetc(f);
      if(ch=='=')
      state=8;
      else
      {
        fseek(f,-1,SEEK_CUR);
        state=0;
      }
      break;
      case 8:
      cout<<"Token 155 string !=, line Number "<<lineNo<<endl;
      state=0;
      break;
      case 9:
      ch=fgetc(f);
      if(ch=='=')
      state=8;
      else
      {
        fseek(f,-1,SEEK_CUR);
        state=0;
      }
      break;
      case 10:
      printf("\n'==' is a relational operator.");
      cout<<"Token 156 string ==, line Number "<<lineNo<<endl;
      state=0;
      break;
      case 11:
      word[p++]=ch;
      while(isalnum(ch=fgetc(f)))
      {
        word[p++]=ch;
      }
      fseek(f,-1,SEEK_CUR);
      word[p]='\0';
      state=12;
      p=0;
      break;
      case 12:
      for(i=0;i<jk;i++)
      if(strcmp(kw[i],word)==0)
      {
        cout<<"Token "<<i+1<< " String "<<word<<", line number "<<lineNo<<endl;
        id=1;
        break;
      }
      if(id==0)
      {
        strcpy(kw[jk++],word);
        cout<<"Token "<<jk<<" String "<<word<<", line Number "<<lineNo<<endl ;
      }
      state=0;
      id=0;
      break;
      case 13:
      word[p++]=ch;
      while(isdigit(ch=fgetc(f)))
      {
        word[p++]=ch;
      }
      fseek(f,-1,SEEK_CUR);
      word[p]='\0';
      state=14;
      p=0;
      break;
      case 14:
      for(int i=0;i<20;i++)
      if(strcmp(kw[i],word))
      {
        cout<<"Token "<<i+107<< " String "<<word<<", line number "<<lineNo<<endl;
        break;
      }
      state=0;
      break;
      case 15:
      for(int i=0;i<7;i++)
      if(Delimeters[i]==ch)
      {
        cout<<"Token "<<i+100<< " String "<<ch<<", line number "<<lineNo<<endl;
        break;
      }
      state=0;
      break;
      case 16:
      state=0;
      lineNo++;
      break;
      default:
      break;
    }
    if(ch==EOF)
    exit=true;
  }
  fclose(f);
  return 0;
}
