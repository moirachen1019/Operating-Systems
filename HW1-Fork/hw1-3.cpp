#include<iostream>
#include<unistd.h>
#include<vector>
#include<string>
#include<cstring>
#include<fcntl.h>
#include<sys/wait.h>
#define MAX_LINE 80
using namespace std;
int main(void)
{
	int should_run = 1; 
	vector<string> arg;
	string tmp;
	vector<char*> argv_t;
	char **argv;
	char buf[80];
	int n;
	int argc;
	int mode;
	pid_t pid;
	bool has_and;
	while(should_run){
		cout<<"osh>";
		fflush(stdout); //clear/flush the output buffer and move the buffered data to console/disk 
		n = read(STDIN_FILENO, buf ,80); //output: the number of bytes read
		//read command line: read 80 bytes from file descriptor STDIN_FILENO into the buffer starting at buf
		for(int i=0;i<n;i++){
			if(buf[i]==' '||i==n-1){ //whitespace or the end of buffer
				if(tmp.size()>0) 
					arg.push_back(tmp); //把用空白分開的字存入arg
				tmp = "";
			}
			else{
				tmp = tmp + buf[i];
			}
		}
		argc = arg.size(); //有幾個用空白分開的字
		argv = new char*[argc+1];                  
		for(int i=0;i<argc;i++){
			argv[i]=new char[arg[i].size()];
			strcpy(argv[i], arg[i].c_str());
		}
		argv[argc] = new char;
		argv[argc] = NULL;
        /**
		* your code!
		* After reading user input, the step are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		*/
		if(!strcmp(argv[0], "exit")){
			return 0;
		}
		pid_t pid;
		pid = fork();
		if(pid < 0){
			cout<<"Fork failed."<<endl;
			exit(1);
		}
		else if(pid == 0){
			if(execvp(argv[0],argv) == -1){
				cout<<"Error!"<<endl;
			}
			exit(1);
		}
		else {
			wait(NULL);
		}

		arg.clear();
		argv_t.clear();
		for(int i=0;i<argc;i++){
			delete [] argv[i];
		}		
		delete argv;
	}
	return 0;
}
