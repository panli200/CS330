/*
Answer:
Part 1 Step 3
a. It doesn't print all cases, because it under the child process. It only print part of cases.
b. shell
c. If remove the wait() function then the child and parent can run concurrently.
Part 2
Because the fork_return=fork(), which create a new process to execute. Even the child variable changed which not affect the parent.

*/


#include "HALmod.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int GetCommand (string tokens [])
{
    string commandLine;
    bool commandEntered;
    int tokenCount;

    do
    {
        cout << "HALshell> ";
        while (1)
        {
            getline (cin, commandLine);
            commandEntered = CheckForCommand ();
            if (commandEntered)
            {
                break;
            }
           
        }
    } while (commandLine.length () == 0);

    tokenCount = TokenizeCommandLine (tokens, commandLine);

    return tokenCount;
}

int TokenizeCommandLine (string tokens [], string commandLine)
{
    char *token [MAX_COMMAND_LINE_ARGUMENTS];
    char *workCommandLine = new char [commandLine.length () + 1];
    int i;
    int tokenCount;

    for (i = 0; i < MAX_COMMAND_LINE_ARGUMENTS; i ++)
    {
        tokens [i] = "";
    }
    strcpy (workCommandLine, commandLine.c_str ());
    i = 0;
    if ((token [i] = strtok (workCommandLine, " ")) != NULL)
    {
        i ++;
        while ((token [i] = strtok (NULL, " ")) != NULL)
        {
            i ++;
        }
    }
    tokenCount = i;

    for (i = 0; i < tokenCount; i ++)
    {
        tokens [i] = token [i];
    }

    delete [] workCommandLine;

    return tokenCount;
}


//Do not touch the below function
bool CheckForCommand ()
{
    if (cullProcess)
    {
        cullProcess = 0;
        cin.clear ();
        cout << "\b\b  \b\b";
        return false;
    }

    return true;
}

	
//This is a very paired down version of Dr. Hilderman's function
int ProcessCommand (string tokens [], int tokenCount)
{
int status;
pid_t fork_return;

    if (tokens [0] == "shutdown" || tokens [0] == "restart" || tokens [0] == "lo")
    {
    	if (tokenCount > 1)
    	{
       		cout << "HALshell: " << tokens [0] << " does not require any arguments" << endl;
        	return 1;
    	}
    	cout << endl;
    	cout << "HALshell: terminating ..." << endl;

        return 0;
        
    }
    else{
	    fork_return = fork(); //create a child and parent
		
        if(fork_return == 0)// under child process
		{	char ** words;
			words = ConvertToC( tokens,tokenCount);
			execvp( words[0], words);
			cout <<"Error under CHILD process"<<endl;
			exit(0);

		}	
		else if(fork_return > 1)//under parent process
		{
			wait(&status);
			return 1;				
		}
		else
		cout<<"Error";
	}

}
char ** ConvertToC (string tokens [], int tokenCount)
{
    char ** words;
    words = (char **) malloc (sizeof (char*) * (tokenCount+1));//allocate an extra word in string tokens

    for (int i=0; i<tokenCount; i++)
    {
        words[i]=strdup(tokens[i].c_str());
    }
	words[tokenCount] = NULL;// store an NULL to extra words

    return words;
}
