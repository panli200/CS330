/* 
 * Part 1 Question1
 * a: The delimeter separate by space character
 * b: Using Strings instead of C strings because Strings has dynamic length, 
 *    and the syntax of comparing is much easier.
 */

#include "HALmod.h"

int main()
{
    char **cTokens;
    string tokens [MAX_COMMAND_LINE_ARGUMENTS];
    int tokenCount;
    
    do
    { 
        tokenCount = GetCommand (tokens);  
        cTokens = ConvertToC (tokens, tokenCount);       
        PrintReverse (cTokens, tokenCount);
        CleanUpCArray(cTokens, tokenCount);
	
    } while (ProcessCommand (tokens, tokenCount));

    return 0;
}
