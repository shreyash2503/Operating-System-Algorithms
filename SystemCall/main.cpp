# include <iostream>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <cstring>
# include <ctime>
# include <dirent.h>


using namespace std;


void FORK(){
    pid_t pid = fork();


    if(pid == 0){
        cout << "This is the child process" << endl;
        cout << "Child PID" << getpid() << endl;
        exit(1);
        return;
    } else if (pid > 0){
        cout << "This is the parent process" << endl;
        cout << "Parent PID" << getppid() << endl;
        exit(0);
        return;
    } else {
        cout << "Fork failed" << endl;
    }
    return;
}

void EXIT(){
	exit(0);
}


int WAIT(){
	pid_t child = fork();
    cout << child << endl;
	if(child == 0){
		cout << "Hello from the child process" << endl;
        cout << "Child PID" << getpid() << endl;
        exit(1);
	} else if (child > 0){
		int status;
		pid_t terminated_pid = wait(&status);
        cout << terminated_pid << endl;
        cout << status << endl;
		if(terminated_pid == child){
			if(WIFEXITED(status)){
				cout << "Child process exited with status " << WEXITSTATUS(status) << endl;

			} else {
				cerr << "Child process not exit noramlly " << endl;
			}
		}
	} else {
		cerr << "Fork failed " << endl;
        return -1;
	}

    return 1;

}


void READ(){
    const char* input = "input.txt";
    const char* output = "output.txt";
    const int buffer = 1024;

    int input_r = open(input, O_RDONLY);
    if(input_r == -1){
        cerr << "Error opening file " << input << endl;
        return;
    }

    int output_w = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(output_w == -1){
        cerr << "Error opening the file for writing " << endl;

    }
    char buf[buffer];
    ssize_t bytesRead;

    while((bytesRead = read(input_r, buf, buffer)) > 0){
        ssize_t bytesWritten = write(output_w, buf, bytesRead);
        if(bytesWritten != bytesRead){
            cerr << "Error writing to file " << endl;
            return;
        }
    }

    close(input_r);
    close(output_w);
    cout << "File copied successfully " << endl;
}

void LINK(){

    const char* sourceFile = "source.txt";
    const char* hardLink = "hardlink.txt";

    if(link(sourceFile, hardLink) == 0){
        cout << "Hard Link created successfully" << endl;
    } else {
        cerr << "Error creating the hard link" << endl;
    }


    if(unlink(sourceFile) == 0){
        cout << "Source file deleted successfully" << endl;
    } else {
        cerr << "Error deleting the source file" << endl;
    }

    struct stat fileStat;
    if(stat(hardLink, &fileStat) == 0){
        cout << "Hard link size: " << fileStat.st_size << endl;

    } else {
        cerr << "Error getting the file size" << endl;
    }
    return;
}

void PIPE(){
    int pipefd[2];

    if(pipe(pipefd) == -1){
        cerr << "Error creating the pipe" << endl;
        return;
    }

    pid_t pid = fork();

    if(pid == 0){
        close(pipefd[1]);

        char buffer[29];
        char buffer2[29];
        

        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer));
        ssize_t bytesRead2 = read(pipefd[0], buffer2, sizeof(buffer2));

        if(bytesRead > 0){
            cout << "Child Process Received -->" << buffer<< endl;
            cout << "Child Process Received -->" << buffer2 << endl;
        } else {
            cerr << "Error reading from pipe" << endl;
        }

        close(pipefd[0]);
    } else if(pid > 0){
        close(pipefd[0]);
        const char* message = "Hello World, This is a pipe ";
        const char* message2 = "I am from VIT";
        ssize_t bytesWritten = write(pipefd[1], message, strlen(message) + 1);
        ssize_t bytesWritten = write(pipefd[1], message2, strlen(message2) + 1);

        if(bytesWritten == -1){
            cerr << "Error writing to pipe" << endl;
        }
        close(pipefd[1]);

    } else {
        cerr << "Fork failed" << endl;
    }
    return;
}



void FIFO(){
    const char* fifoPath = "/mnt/c/Users/Shreyash/myfifo";

    if(mkfifo(fifoPath, 0666) == -1){
        cerr << "Error creating the FIFO" << endl;
        return;
    }

    int fd = open(fifoPath, O_WRONLY);
    if(fd == -1){
        cerr << "Error opening the FIFO" << endl;
        return;
    }

    const char* message = "Hello, FIFO";
    ssize_t bytesWritten = write(fd, message, strlen(message) + 1);

    if(bytesWritten == -1){
        cerr << "Error writing to FIFO" << endl;
        return;
    }

    close(fd);
    return;

}


void INFO(){
    const char* file = "input.txt";

    struct stat fileStat;

    if(stat(file, &fileStat) == 0){
        cout << "File Size::"<<fileStat.st_size << endl;
        cout << "Number of Links::"<<fileStat.st_nlink << endl;
        cout << "Permissions::"<<fileStat.st_mode << endl;
        
    } else {
        cerr << "Error getting the file info" << endl;
    }

    const char* dirname = ".";
    DIR* dir = opendir(dirname);
    if(dir != nullptr){
        dirent* entry;
        while((entry = readdir(dir)) != nullptr){
            cout << entry->d_name << endl;
        }
        closedir(dir);
    } else {
        cerr << "Error opening the directory" << endl;
    }

    cout << "Process ID::" << getpid() << endl;
    cout << "Parent Process ID::" << getppid() << endl;
    cout << "User ID::" << getuid() << endl;
    cout << "Group ID::" << getgid() << endl;
    cout << "Effective User ID::" << geteuid() << endl;
    cout << "Effective Group ID::" << getegid() << endl;

    time_t t = time(nullptr);
    cout << "Current Time::" << ctime(&t) << endl;
}

const char* dirname = ".";
DIR* dir = opendir(dirname);
if(dir != nullptr){
    dirent* entry;
    while((entry = readdir(dir)) != nullptr){
        cout << entry->d_name << endl;
    }
    close(dir);
}


int main(){
    
    int option;
    int flag = 0;
    while(true && flag == 0){

        cout << "1. Fork" << endl;
        cout << "2. Exit" << endl;
        cout << "3. Wait" << endl;
        cout << "4. Read" << endl;
        cout << "5. Link" << endl;
        cout << "6. Pipe" << endl;
        cout << "7. FIFO" << endl;
        cout << "8. Info" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        if(option == 1){
            // pid_t pid = fork();
            // if(pid == 0){
            //     cout << "This is the child process" << endl;
            //     cout << "Child PID" << getpid() << endl;
            // } else if (pid > 0){
            //     cout << "This is the parent process" << endl;
            //     cout << "Parent PID" << getppid() << endl;
            // } else {
            //     cout << "Fork failed" << endl;
            // }
            FORK();
        } else if(option == 2){
            EXIT();
        } else if(option == 3){
            WAIT();
        } else if(option == 4){
            READ();
        } else if(option == 5){
            LINK();
        } else if(option == 6){
            PIPE();
        } else if(option == 7){
            FIFO();
        } else if(option == 8){
            INFO();
        } else {
            cout << "Invalid option" << endl;
        }
    }


    return 1;


}
