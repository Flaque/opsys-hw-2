#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE 80

char** getInput();
char*  getStrInput();
void dispInput(char*[]);
int commandSize;

int main()
{
  //A pointer to an array of pointers to char.  In essence, an array of 
  //arrays.  Each of the second level arrays is a c-string. These hold
  //the command line arguments entered by the user.
  char** args = (char**) malloc(MAX_LINE);

  int more = 1;
  while (more)
  {
     printf("myShell> ");
     fflush(stdout);
     args = getInput(args);
    
     //if arg[0] holds 'quit', set more to 0, else invoke dispInput()
     if(0 == strcmp(args[0], "quit")){
       more = 0;
     }else{
       dispInput(args);
     }
  }
   return 0;
}

char* getStrInput()
{
  char* input = (char*) malloc(MAX_LINE);
  char* start = input;
  char c;

  while((c = getchar()) != '\n') {
    *input++ = c; //Increments memory pointer
  }
  *input = '\0'; //add c escape character
  return start;
}

//Reads input string from the key board.  Parses the input into arguments
//where any is any string of characters that either begin the input or is
//separated by the previous argument by a space.  Returns a pointer to an array 
//of pointers to char.  char* argv[] is the model.
//In the following example, the user has entered three arguments
//myShell> ls -l cpsc346 
//and optons  
char** getInput(char** words)
{
  char* strInput = getStrInput();
  const char space[2] = " ";
  char* token;
  token = strtok(strInput, space);
  int wordCount = 0;

  while(token != NULL)
  {
    words[wordCount] = token;
    token = strtok(NULL, space);
    ++wordCount;
  }
  
  commandSize = wordCount - 1;
  return words;
}


//Displays the arguments entered by the user and parsed by getInput
void dispInput(char** args)
{
	int i;
        
	for(i =0; i <= commandSize; i++){
		printf("%s ", args[i]);
	}
        printf("\n");
}  
