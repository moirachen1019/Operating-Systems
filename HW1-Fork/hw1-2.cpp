#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<iostream>
using namespace std;
int main(void)
{
	pid_t pid;
	cout << "Main Process ID : "<< getpid() << endl;
	pid = fork(); //fork1
	if(pid == 0){
		cout << "Fork 1. I'm the child "<< getpid() << ", my parent is " << getppid() << endl;
		pid = fork(); //fork2
		if(pid == 0){
			cout << "Fork 2. I'm the child "<< getpid() << ", my parent is " << getppid() << endl;
			pid = fork(); //fork3
			if(pid == 0){
				cout << "Fork 3. I'm the child "<< getpid() << ", my parent is " << getppid() << endl;
			}
			else if(pid > 0){
				wait(NULL);
			}
		}
		else if(pid > 0){
			wait(NULL);
		}
	}
	else if(pid > 0){
		wait(NULL);
		pid = fork(); //fork4
		if(pid == 0){
			cout << "Fork 4. I'm the child "<< getpid() << ", my parent is " << getppid() << endl;
		}
		else if(pid > 0){
			wait(NULL);
			pid = fork(); //fork6
			if(pid == 0){
				cout << "Fork 6. I'm the child "<< getpid() << ", my parent is " << getppid() << endl;
			}
			else if(pid > 0){
				wait(NULL);
			}
		}
		pid = fork(); //fork5
		if(pid == 0){
			cout << "Fork 5. I'm the child "<< getpid() << ", my parent is " << getppid() << endl;
		}
		else if(pid > 0){
			wait(NULL);
		}
	}
}
