/*This is a pair-programming submission by:
 *James Zhang (cssc1203)
 *Gerald Lappay (cssc1164)
 *
 *Submission is on account: cssc1203/cs570/a02
 */

#include "tokenizer.h"
#include "command.h"

int main() {
	static char* line_read = (char*)NULL;
	/*Tokenize input similar to what was done
	 * in A01.
	 */
	while (1) {
		line_read = readline("> ");
		if (line_read != 0) {
			list<string> tokens = parse(line_read);

			// handles blank line
			if (tokens.size() == 0) {
				continue;
			}
		build_commands(tokens);	
		}
		else break;
	}
}
/*Generates a list of executable commands from
 *Previously parsed text using tokenizer from A01.
 */
void build_commands(list<string> tokens){
	list<string> commands;
	list<string>::iterator command_it;

	command_it = commands.begin();	
	/*Iterate through tokens and slowly build them as commands
	 *until we hit either a ";" or "|".
	 *If we do, run execute_commands on everything we've built
	 *so far.
	 */
	while(tokens.size() !=0){
		string token = tokens.front();
		tokens.pop_front();
		//Handling "<" and ">"
		if(token.compare(less) == 0 || token.compare(greater) == 0){
			tokens.pop_front();
			cout<<"IO redirection and background not implemented";
			continue;
		}
		//Handling "&".
		else if(token.compare(amper) ==0){
			cout<<"IO redirection and background not implemented";
			continue;
		}
		//If we hit ";" or "|", token building stops, run execute_commands.
		else if (token.compare(pipe) !=0 && token.compare(semicolon) !=0){
			if(token.compare(pipe) ==0){
				cout<<"Pipe not implemented \n";
			}
			commands.insert(command_it,token);
		}
		else{
			execute_commands(commands);
			commands.clear();
		}
	}
}

//Executes valid list of commands from build_commands.
void execute_commands(list<string> commands){
	string first_token = commands.front();
	
	//Handle "cd".
	if(first_token == "cd"){
		if(commands.size() !=2){
			cout<<"Accepts exactly one argument \n";
			return;
		}
		commands.pop_front();
		string dir_name = commands.front();

		struct stat info;

		if( stat( dir_name.c_str(), &info ) != 0 ){
    			cout<<"Directory does not exist or is not accessible. \n";
			return;
		}
		chdir(dir_name.c_str());	
	}
	//Handle "pwd".
	else if(first_token == "pwd"){
		if(commands.size() !=1){
			return;
		}
		char pwd[BUFFER_SIZE];
		getcwd(pwd,BUFFER_SIZE);
		if (pwd == '\0'){
			cout<<"Unable to obtain current directory \n";
			return;
		}
		cout<<pwd<<endl;

	}
	//Assume program is to be launched.
	else{
		//Building argv pointer system.
		char* argv[BUFFER_SIZE];
		int i = 0;
		while(commands.size() !=0){
			argv[i] = (char*) (commands.front().c_str());
			commands.pop_front();
			++i;
		}
		argv[i] = '\0'; //"The last entry in argv must be NULL."
		//Forking.
		pid_t cpid;
 		cpid = fork();
		
    		if (cpid == 0){
			execvp(argv[0],(char* const*) argv);
        		exit(0);           //Kill the child.
		}
		//Error/Success messages.
		else if(cpid <0){
			cout<<"Unable to spawn program \n";
			return;
		}
    		else{
			cpid = wait(NULL);
			if(cpid == -1){
				cout<<"Process exited with error \n";
			}
			else{
				cout<<"Process exited successfully \n";
			}	
		}
	}
}
