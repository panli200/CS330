#include "HALmod.h"

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
    else
	return 1;

}

//This converts the tokens into a c version of an array of words and returns the pointer to that array
char **ConvertToC (string tokens [], int tokenCount)
{
    char **cString;
    cString = new char *[tokenCount];
    
 
   for (int i=0; i<tokenCount; i++)
   {
    cString[i] = new char[tokens[i].length()+1];
	strncpy(cString[i],tokens[i].c_str(),tokens[i].length()+1);
    
   }	
	
    return cString;

}

//This cycles through the c string version of the array and frees up any memory that has been allocated
void CleanUpCArray (char ** cTokens, int tokenCount)
{
    for (int i=0; i<tokenCount; i++)
   {
        delete []cTokens[i] ;
   }
   delete []cTokens;
}

//This cycles in reverse through the c string version of the words and prints each word
void PrintReverse (char ** cTokens, int tokenCount)
{
    cout<<"The words in reverse are: ";
   for(int i=tokenCount-1; 0<=i; i--)
   {
    cout<< cTokens[i]<<" ";
   }
	cout<<endl;
}



