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

    if(pid > 0){
        cout << "This is the parent process" << endl;
        cout << "The id of this process is ::" << getppid() << endl;
        exit(1);
        return;
    }
    if(pid == 0){
        cout << "This is the child process" << endl;
        cout << "The id of this process is ::" << getppid() << endl; 
        exit(0);
        return;
    } else {
        cout << "Fork failed" << endl;
    }
}

void WAIT(){
    pid_t status = fork();
    if(status == 0){
        cout << "This is the child process" << endl;
        cout << "Child PID::" << getpid() << endl;
        exit(200);
        return;
    } else if(status > 0){
        int status;
        pid_t terminated_pid = wait(&status);
        cout << "The status of the terminated process is ::" << status << endl;
        cout << "The id of the terminated process is ::" << terminated_pid << endl;
        if(terminated_pid == status){
            if(WIFEXITED(status)){
                cout << "The exit status id of the terminated process is " << WEXITSTATUS(status) << endl;
            } else {
                cout << "The child process exited abnormally" << endl;
            }
        }

    } else {
        cerr << "Error creating a fork" << endl;
    }
}

void READ(){
    const char* input = "input.txt";
    const char* output = "output.txt";
    int buffer = 1024;
    int input_r = open(input, O_RDONLY);
    if(input_r == -1){
        cerr << "Error opening the file" << endl;
    }

    int output_r = open(output, O_WRONLY | O_TRUNC | O_CREAT, 0666);
    if(output_r == -1){
        cerr << "Error creating the file or file does not exist" << endl;

    }
    char buf[buffer];
    ssize_t bytesRead;

    while((bytesRead = read(input_r, buf, buffer)) > 0){
        ssize_t bytesWrite = write(output_r, buf, bytesRead);
        cout << bytesRead << bytesWrite << endl;
        if(bytesRead != bytesWrite){
            cerr << "Error writing to the file" << endl;
            return;
        }
    }

    close(input_r);
    close(output_r);
    cout << "File copied successfully" << endl;

}

void PIPE(){
    int pipefd[2];
    if(pipe(pipefd) == -1){
        cout << "Error creating the pipe" << endl;
    }

    pid_t status = fork();
    if(status == 0){
        close(pipefd[0]);
        const char* message = "This is the message from the child process";
        int bytesWritten = write(pipefd[1], message, strlen(message));
        if(bytesWritten == -1){
            cerr << "Error writing to the pipe" << endl;
        }
        close(pipefd[1]);

    } else if(status > 0){
        close(pipefd[1]);
        char buffer[60];
        int bytesRead = read(pipefd[0], buffer, sizeof(buffer)); 
        if(bytesRead == -1){
            cerr << "Error reading from the file" << endl;
        }
        cout << "The message from the child process is " << buffer << endl;
        close(pipefd[0]);
    } else {
        cerr << "Error creating the fork" << endl;
    }

    return;

}

void INFO(){
    const char* file = "input.txt";
    struct stat fileStat;
    if(stat(file, &fileStat) == 0){
        cout << "File Size ::" << fileStat.st_size << endl;
        cout << "Number of links::" << fileStat.st_nlink << endl;
        cout << "Permission::" << fileStat.st_mode << endl;
    } else {
        cerr << "Error getting the file info" << endl;
    }

    const char* di = ".";
    DIR* dir = opendir(di);
    if(dir != nullptr){
        dirent* entry;
        while((entry = readdir(dir)) != nullptr){
            cout << entry->d_name << endl;
        }
        closedir(dir);
    } else {
        cerr << "Error opening the directory" << endl;
    }


}


int main(){
    int option;
    cin >> option;
    if(option == 1){
        FORK();
    } else if(option == 2){
        WAIT();
    } else if(option == 3){
        READ();
    } else if(option == 4){
        PIPE();
    } else if(option == 5){
        INFO();
    }
    return 1;
}