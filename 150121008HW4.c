/*

    Mahmut Esat Çakmak
    150121008

    This code aims to take input as a file and allows us to process the given data according to the desired operation

*/
#include <stdio.h>
#include <stdlib.h>

int charAt(String *s,int i);
String *concat(String *s1, String *s2);
unsigned int strSearch(String *s1, String *s2);
unsigned int findScore(String *s1);
void updateLetterCount(String *str);
void updateWordCount(String *str);
void updatestrlen(String *s);
int initializeValues(char ch[100],String *str1,String *str2,int *selectOption);
int isEqual(String *str1,const char *ch);

// I have defined a global variable
int wordCounter= 0;
int letterCounter= 0;

// I have created a struct for string
typedef struct string
{
  char *ch;
  int length;
}String;

int main(int argc, char *argv[])
{
  // I have allocated memory for strings
  String str1;
  str1.ch = (char*) malloc(50*sizeof(char)+sizeof(int)); 
  String str2;
  str2.ch = (char*) malloc(50*sizeof(char)+sizeof(int));

  //I have defined soome useful variable
  // selectOption is storing second argument
  int selectOption;
  int index=0;
  // This char array is storing the incoming line using the fgets function
  char line[100];
  char *statStr = "stat";
  char *exitStr = "exit";

  // It checks if there are the correct number of argument 
  if (3<argc) 
  {
      printf("You should enter 3 argument!");
      return 0;
   }
  FILE *infilep, *outfilep;

  infilep = fopen(argv[1], "r");
  outfilep = fopen(argv[2], "w");

  if (infilep == NULL) {
      printf("Invalid input file name!");
      return 0;
   }

  while(fgets(line, sizeof(line), infilep) != NULL)
  {    
    // initializeValues function assigns the variables str1, str2, and selectOption
    initializeValues(line,&str1,&str2,&selectOption);
    // This functions update str1 and str2 lentgh
    updatestrlen(&str1);
    updatestrlen(&str2);
    // This function updates the word counters
    updateWordCount(&str1);

    if(selectOption == 1)
    {
      // This function updates the letter counters
      updateLetterCount(&str1);
      // It assigns index based on the data
      index = str2.ch[0] - '0';
      fprintf(outfilep,"%c\n",((char) charAt(&str1,index)));
      
    }
    else if(selectOption == 2)
    {
      updateLetterCount(&str1);
      updateLetterCount(&str2);

      fprintf(outfilep,"%s\n",concat(&str1,&str2)->ch);
      
    }
    else if(selectOption == 3)
    {
      updateLetterCount(&str1);
      updateLetterCount(&str2);
      updateWordCount(&str2);

      fprintf(outfilep,"%u\n",strSearch(&str1,&str2));
    }
    else if(selectOption == 4)
    {
      updateLetterCount(&str1);
      fprintf(outfilep,"%u\n",findScore(&str1));
    }
    else if(isEqual(&str1,statStr))
      {
        fprintf(outfilep,"The number of words: %d\n",wordCounter);
        fprintf(outfilep,"The number of alphabetic letters: %d\n",letterCounter);
      }
    else if(isEqual(&str1,exitStr))
      {
        fprintf(outfilep,"Program ends. Bye");
        break;
      }
  }
  fclose(infilep);
  fclose(outfilep);
}

int charAt(String *s,int i)
{
  char ch;
  if(0 < i && i < s->length)
  {
    // These operations are performed to convert the desired output into uppercase
    if(s->ch[i] >= 'A' && s->ch[i] <= 'Z')
      ch = s->ch[i];
    else if(s->ch[i] >= 'a' && s->ch[i] <= 'z')
      ch = s->ch[i] - ('a'-'A');
    else
      ch = s->ch[i];
  }
  else
    return -1;
  // Casting char to int because return type is int
  return (int)ch;
}
String *concat(String *s1, String *s2)
{
  // I have defined a new temporary string variable
  String *tempStr;
  tempStr = (String*) malloc(sizeof(String));

// +1 is for extra space between two strings
  tempStr->length = s1->length + s2->length +1;
  tempStr->ch = (char *) malloc(sizeof(char)*(s1->length + s2->length +1));

  int i,j;
// I have assigned the given data to the temporary variable
  for(i= 0;i< s1->length; i++)
    tempStr->ch[i] = s1->ch[i];

  tempStr->ch[s1->length] = ' ';

  for(i = s1->length+1 , j=0;i < s1->length + s2->length+1;i++,j++)
    tempStr->ch[i] = s2->ch[j];

  tempStr->ch[s1->length + s2->length+1]= '\0';
  
  return tempStr;
}
unsigned int strSearch(String *s1, String *s2)
{
  int i,j;
  int spaceIndex =0,wordBoolean=0;

  for(i=0,j=0; i< s1->length;i++)
  {
    
      if(s1->ch[i] == s2->ch[j])
      {
        wordBoolean =1;
        j++;
      }
      else if(j != s2->length)
      {
         j=0;
         wordBoolean=0;
      }
      if(wordBoolean && !((s1->ch[i+1] >= 'a' && s1->ch[i+1] <= 'z' )|| s1->ch[i+1] >= 'A' && s1->ch[i+1] <= 'Z'))
      {
        return i-spaceIndex;
        break;
      }

      if(s1->ch[i] == ' ')
      {
        spaceIndex = i;
      }
  }
    return 0;
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
void updateLetterCount(String *str)
{
  int i;
  char ch;
  for(i=0;i< str->length;i++)
  {
    ch = str->ch[i];
      if((ch >= 'a' && ch <='z') || (ch >= 'A' && ch <='Z'))
        letterCounter++;
  }
}
void updateWordCount(String *str)
{
  int i;
  int spaceIndex=-1;

  for(i =0;i<str->length;i++)
  {
    if(str->ch[i] == ' ')
      spaceIndex =i;
    if( (str->ch[spaceIndex +1] >= 'a' && str->ch[spaceIndex +1] <= 'z' )|| (str->ch[spaceIndex +1] >= 'A' && str->ch[spaceIndex +1] <= 'Z'))
      {
        wordCounter++;
        spaceIndex--;
      }
  }
}
void updatestrlen(String *s)
{
  int i;
  for(i=0; s->ch[i] != '\0';i++);
  s->length = i;
}
int initializeValues(char ch[100],String *str1,String *str2,int *selectOption)
{
  // it defines which value assign variable
  int partNumber = 0;
  int i,j =0;
  *selectOption = -1;

  for(i=0; ch[i] !='\0';i++)
  {
      if(ch[i] == ':' || ch[i] == ',')
      {
        partNumber++;
        continue;
      }
      if(partNumber ==0)
      {
        str1->ch[i] = ch[i];

        if(ch[i+1]==':' || ch[i+1]=='\0' || ch[i+1]=='\n')
       {
          str1->ch[i+1]= '\0';
          if(ch[i+1]=='\0' || ch[i+1]=='\n')
          {
            ch[i+1] ='\0';
            continue;
          }
        }
      }
      else if(partNumber ==1)
      {
        *selectOption = (int)ch[i] - '0';
      }
      else if(partNumber == 2)
      {
        str2->ch[j] = ch[i];
        
        if(ch[i+1]=='\0' || ch[i+1]=='\n')
       {
          str2->ch[j+1]= '\0';
          if(ch[i+1]=='\0' || ch[i+1]=='\n')
          {
            ch[i+1] ='\0';
            continue;
          }
        }
        
        j++;
      }    
      if(*selectOption == 4)
          return 1;
  }

  if (*selectOption == -1 )
     str2->ch[0] = '\0';

  return 0;
}
int isEqual(String *str1,const char *ch)
{
  int i =0;

  for (;str1->ch[i]!= '\0' && ch[i] != '\0'; i++)
  {
    if(str1->ch[i]!=ch[i])
      return 0;
  }

  if(str1->ch[i] == '\0' && ch[i]== '\0')
    return 1;
  
  return 0;
}
