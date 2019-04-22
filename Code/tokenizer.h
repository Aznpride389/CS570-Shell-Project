#include <iostream>
#include <ctype.h>
#include <vector>
#include <list>
#include <string>
#include <readline/readline.h>

using namespace std;

int isSpecial (char);
int isWhiteSpace (char);
int isAlphaNum (char);
int isPunct (char);
char escapeCharacter(char);
void build_commands(list<string> tokens);		

list<string> parse(char*);

