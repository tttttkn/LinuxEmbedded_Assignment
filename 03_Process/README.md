# Process Management in Linux

This document provides an overview of process management in Linux, covering key concepts such as process creation, system calls for managing processes, and handling orphaned and zombie processes.

## Introduction to Processes

A **process** is an instance of a running program. Each process has a unique **Process ID (PID)** and operates in its own memory space. Key components of a process include:

- **Text Segment**: Contains the executable code.
- **Data Segment**: Includes global and static variables.
- **Heap**: Dynamically allocated memory.
- **Stack**: Temporary data storage (e.g., function parameters, return addresses).

### Program vs. Process
- **Program**: A set of instructions stored on disk.
- **Process**: A program that is currently executing and using system resources.

## Command-line Arguments

When a program starts, it can accept command-line arguments passed to the `main()` function:

- `argc`: The number of arguments passed.
- `argv[]`: An array of strings containing the arguments.

### Example of Command-line Arguments

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Number of arguments: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    return 0;
}
```

## Memory Layout of a Process

The memory allocated to a process is divided into several segments:

- `Text Segment`: Contains the machine code of the program (read-only).
- `Initialized Data Segment`: Contains global and static variables that are explicitly initialized (read/write).
- `Uninitialized Data Segment (BSS)`: Contains global and static variables that are not explicitly initialized (read/write).
- `Heap`: Dynamically allocated memory (grows upwards).
- `Stack`: Used for function calls and local variables (grows downwards).

Example of Memory Layout
```c
#include <stdio.h>
#include <stdlib.h>

char buffer[1024];  // Uninitialized data segment
int primes[] = {2, 3, 5, 7};  // Initialized data segment

void hello(int x) {
    int result;  // Stack frame for hello()
}

int main(int argc, char *argv[]) {
    static int key = 1;  // Initialized data segment
    static char buffer[1024];  // Uninitialized data segment
    char *p;  // Stack frame for main()
    p = malloc(1024);  // Heap segment
    return 0;
}
```

## Process Operations
### Creating a New Process

- Use the `fork()` system call to create a new process.
- The process that calls `fork()` is the parent process, and the new process is the child process.

Example of fork()
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child Process: PID = %d\n", getpid());
    } else if (pid > 0) {
        printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);
    } else {
        perror("fork");
        return 1;
    }
    return 0;
}
```

### Running a New Program
Use the `exec()` family of functions `(execl, execlp, execle, execv, execvp)` to replace the current process image with a new one.

Example of `execl()`
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Running 'ls -lah' after 2 seconds\n");
    sleep(2);
    execl("/bin/ls", "ls", "-l", "-h", NULL);
    return 0;
}
```

### Terminating a Process

- Use `exit()` or `_exit()` to terminate a process normally.
- Use `kill` to terminate a process abnormally.

## System Calls for Process Management

`wait()`
- The wait() system call is used to wait for a child process to terminate.
- It blocks the parent process until one of its child processes exits.
  
`waitpid()`: The waitpid() system call allows waiting for a specific child process.

## Orphaned and Zombie Processes
### Orphaned Processes

- If a parent process terminates before its child processes, the child processes become orphaned.
- Orphaned processes are adopted by the init process (PID 1).

### Zombie Processes

- If a child process terminates before the parent calls wait(), it becomes a zombie.
- Zombie processes remain in the system until the parent collects their status using wait() or waitpid().

### Preventing Zombie Processes

- Always call wait() or waitpid() in the parent process.
- Use the SIGCHLD signal to handle child process termination.