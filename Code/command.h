/*This is a pair-programming submission by:
 *James Zhang (cssc1203)
 *Gerald Lappay (cssc1164)
 *
 *Submission is on account: cssc1203/cs570/a02
 */

#include <sys/stat.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <cstdlib> 

#define semicolon ";" 
#define pipe "|" 
#define less "<" 
#define greater ">" 
#define amper "&"

#define BUFFER_SIZE 100

void build_commands(list<string> tokens);
void execute_commands(list<string> commands);
