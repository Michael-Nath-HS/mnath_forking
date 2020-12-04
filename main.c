#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
    srand(time(NULL));
    int c1, c2, status, random_number, file;
    printf("I am the parent with PID: %d. Producing children...\n", getpid());
    int sleep1, sleep2;
    c1 = fork();
    if (c1)
    {
        c2 = fork();
        if (c2)
        {
            int child_pid = wait(&status);
            printf("Parent exiting... Completed Child Process with PID: %d. Took %d seconds\n", child_pid, WEXITSTATUS(status));
            return 0;
        }
    }
    if (!c1)
    {
        file = open("/dev/random", O_RDONLY);
        read(file, &random_number, sizeof(random_number));
        close(file);
        printf("I am the first child with PID: %d\n", getpid());
        int sleep1 = (abs(random_number) % 9) + 2;
        sleep(sleep1);
        printf("Child 1 finished its beauty rest...\n");
        return sleep1;
    }
    if (!c2)
    {
        file = open("/dev/random", O_RDONLY);
        read(file, &random_number, sizeof(random_number));
        close(file);
        printf("I am the second child with PID: %d\n", getpid());
        int sleep2 = (abs(random_number) % 9) + 2;
        sleep(sleep2);
        printf("Child 2 has finished hibernating...\n");
        return sleep2;
    }
}
