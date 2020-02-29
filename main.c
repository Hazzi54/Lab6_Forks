#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//        Proc tree
//
//             1
//          ___|___
//         |       |
//         2       3
//         |     __|__
//         |    |     |
//         4    5     6 

int main() {
    pid_t pid1, pid2, pid3, pid4, pid5;
    int *stat;
    pid1 = fork();

    if(pid1 == 0) {
        printf("2. pid = %d, ppid = %d\n", getpid(), getppid());
        pid2 = fork();
        if(pid2 == 0)
            printf("4. pid = %d, ppid = %d\n", getpid(), getppid());
        else
            wait(stat);
    }

    else {
        printf("1. pid = %d, ppid = %d\n", getpid(), getppid());
        pid3 = fork();
        if(pid3 == 0) {
            printf("3. pid = %d, ppid = %d\n", getpid(), getppid());
            pid4 = fork();
            if(pid4 == 0) {
                printf("5. pid = %d, ppid = %d\n", getpid(), getppid());
            }
            else {
                pid5 = fork();
                if(pid5 == 0) {
                    printf("6. pid = %d, ppid = %d\n", getpid(), getppid());
                }
                else {
                    waitpid(pid4, stat, WUNTRACED);
                    waitpid(pid5, stat, WUNTRACED);
                }
            }
        }
        else {
            waitpid(pid3, stat, WUNTRACED);
            waitpid(pid1, stat, WUNTRACED);
        }
    }
    return 0;
}
