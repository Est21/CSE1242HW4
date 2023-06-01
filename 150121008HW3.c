#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string
{
  char *ch;
  int length;
}String;

void updatestrlen(String *s)
{
  int i;
  for(i=0; s->ch[i] != '\0';i++);
  s->length = i;
}
int isEqual(String *str1,String *str2)
{
  int i;
  int counter=0;
  for (i = 0;str1->ch[i]!= '\0'; i++)
  {
    if(str1->ch[i]==str2->ch[i])
      counter++;
    else if (str1->ch[i]!=str2->ch[i])
      break;
  }
  
  if(counter == str1->length == str2->length)
    return 1;
  return 0;
}
int charAt(String *s,int i)
{
  char ch;
  if(0 < i && i < s->length)
    ch = s->ch[i];
  else
    return -1;
  return ch;
}
String *concat(String *s1, String *s2)
{
  String *tempStr;
  tempStr = (String*) malloc(sizeof(String));

  tempStr->length = s1->length + s2->length;
  tempStr->ch = (char *) malloc(sizeof(char)*(s1->length + s2->length));

  int i,j;

  for(i= 0;i< s1->length; i++)
    tempStr->ch[i] = s1->ch[i];
  for(i = s1->length , j=0;i < s1->length + s2->length;i++,j++)
    tempStr->ch[i] = s2->ch[j];

  tempStr->ch[s1->length + s2->length]= '\0';
  
  return tempStr;
}

unsigned int strSearch(String *s1, String *s2)
{
  int i;
  int s2Index, letterCounter=0;

  for(i=0,s2Index=0; i< s1->length;i++)
  {
      if(s1->ch[i] == s2->ch[s2Index])
      {
        s2Index++;
        
      }
      else if((s2Index> 0 && s2Index < s2->length) && s1->ch[i] != s2->ch[s2Index])
      {
         s2Index=0;
         letterCounter=0;
      }
      if(s2Index > 0 && s1->ch[i] != ' ')
        letterCounter++;    
  }
  return letterCounter;
}

unsigned int findScore(String *s1)
{
  unsigned int score=0;
  int i;
  char ch;
  for(i = 0; i < s1->length;i++)
  {
    ch = s1->ch[i];
    if( ch =='A' || ch =='E' || ch =='I' || ch =='O' || ch =='U' || ch =='L'
    || ch =='N' || ch =='R' || ch =='S' || ch =='T' ||
    ch =='a' || ch =='e' || ch =='i' || ch =='o' || ch =='u' || ch =='l'
    || ch =='n' || ch =='r' || ch =='s' || ch =='t') 
      score+= 1;
    else if(ch =='D' || ch =='G' || ch =='d' || ch =='g')
      score +=2;
    else if(ch =='B' || ch =='C' || ch =='M' || ch =='P' 
    || ch =='b' || ch =='c' || ch =='m' || ch =='p')
      score +=3;
    else if(ch =='F' || ch =='H' || ch =='V' || ch =='W' || ch =='Y' 
    || ch =='f' || ch =='h' || ch =='v' || ch =='w' || ch =='y')
      score +=4;
    else if(ch =='K' || ch =='k')
      score +=5;
    else if(ch =='J' || ch =='X' || ch =='j' || ch =='x')
      score +=8;
    else if(ch =='Q' || ch =='Z' || ch =='q' || ch =='z')
      score +=10;
  }
  return score;
}


int main()
{
  String str1;
  str1.ch = (char*) malloc(50*sizeof(char)+sizeof(int)); 
  String str2;
  str2.ch = (char*) malloc(50*sizeof(char)+sizeof(int));
  String statStr;
  statStr.ch = (char*) malloc(4*sizeof(char)+sizeof(int));
  statStr.ch = "stat";
  String statStr;
  statStr.ch = (char*) malloc(4*sizeof(char)+sizeof(int));
  statStr.ch = "stat";
  String exitStr;
  exitStr.ch = (char*) malloc(4*sizeof(char)+sizeof(int));
  exitStr.ch = "stat";

  int selectOption;
  int exitStatus=0;
  int index=0;
  strcpy(str1.ch,"strcpy");
  strcpy(str2.ch,"strcpyn");

  updatestrlen(&str1);
  updatestrlen(&str2);

  while(!exitStatus)
  {
    updatestrlen(&str1);
    updatestrlen(&str2);

    if(selectOption == 1)
    {
      printf("%c\n",(char)charAt(&str1,index));
    }
    else if(selectOption == 2)
    {
      printf("%s",concat(&str1,&str2)->ch);
    }
    else if(selectOption == 3)
    {
      printf("%d",strSearch(&str1,&str2));
    }
    else if(selectOption == 4)
    {
      printf("%d",findScore(&str1));
    }
    else
    {
      if(isEqual(&str1,&exitStr))
        break;
      else if(isEqual(&str1,&statStr))
        continue;

    }
    
  }
    printf("%s\n",statStr.ch);
    printf("%s\n",str2.ch);
    
}