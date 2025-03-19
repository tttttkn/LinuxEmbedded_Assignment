# Signal

# 1. Introduction

## Definition

- Signal is one of the oldest methods of inter-process communication in Unix systems.
- Signal is a software interrupt, a mechanism for handling asynchronous events.

## Example:

- These events can originate from external sources, such as when a user presses the Ctrl+C key combination.
- Or from internal program activities, such as dividing a number by zero.

---

## Signal Lifecycle

- **Generation**: First, a signal is raised/sent/generated.
- **Delivery**: A signal is pending until it is delivered.
- **Processing**: Once the signal is delivered, it can be handled in several ways.
  - Ignore the signal.
  - Catch and handle the signal.
  - Perform the default action.

## Processing

- Ignore the signal:
  - No action is taken.
  - SIGKILL and SIGSTOP cannot be ignored.
- Catch and handle the signal:
  - The kernel will pause the execution of the main thread and jump to the signal handler function registered by the user in the process.
  - SIGINT and SIGTERM are two commonly used signals.
  - SIGKILL and SIGSTOP cannot be caught.
- Perform the default action:
  - The action depends on the type of signal.

---

## Signal Lifecycle

- **Processing**

Main Program  
- [ ] Program begins  
- [x] Signal handler is installed  
- [ ] Execution continues  
- [x] Signal is raised  
- [ ] Handler executes  
- [x] Handler returns  
- [ ] Program execution continues  

---

# 2. Signal Handler

- We register the handling of a signal through the `signal()` system call.
- Signal is a software interrupt, so it is quite sensitive to execution timing. When the signal handler is executed, it takes over the process completely.
- It is necessary to exit the signal handler function as quickly as possible.

```c
sighandler_t signal(int signo, sighandler_t handler);
```

We register the handling of a signal  
Arguments:  
- signo: signal number.  
- handler: the function to execute when the signal is caught.

---

# 3. Some Basic Signals

- **SIGKILL**: Can only be sent using the `kill()` system call. The process cannot catch or ignore it. By default, it terminates the specified process.
- **SIGTERM**: Can only be sent using the `kill()` system call. By default, it terminates the specified process, but the process can catch this signal and clean up before terminating.
- **SIGINT**: This signal is sent to processes in the foreground process group. By default, it terminates the current process.
- **SIGCHLD**: Whenever a process stops, it sends SIGCHLD to its parent process. By default, SIGCHLD is ignored.
- **SIGSTOP**: Can only be sent using the `kill()` system call. The process cannot catch or ignore it. By default, it pauses the specified process.
- **SIGUSR1/SIGUSR2**: Signals available for user-defined purposes.

---

# 4. Sending Signals

- Signals can be sent using the `kill()` system call in the source code.
- Additionally, signals can be sent via the `kill` command in the terminal.
- A process can send a signal to itself using the `getpid()` function.

---

**Int kill (pid_1 pid, int signo):**

Send a signal to a specific process with a given PID.  
Arguments:  
- pid: PID of the process.  
- Signo: signal number.  
- Returns 0 on success, less than 0 on failure.

---

# 5. Blocking and Unblocking Signals

**Concept:**

- Signals interrupt the execution of a process. In many cases, this is undesirable when the process is executing critical code. Blocking signals helps solve this problem.

- Each process can specify which signals it wants to block. If a blocked signal occurs, it will be held in a pending queue by the kernel.

- The signal is only delivered to the process after it is unblocked.

- The list of blocked signals is called the signal mask.

---

## Signal sets:
```c
int sigemptyset(sigset_t *set);    // Initialize an empty set
int sigfillset(sigset_t *set);     // Initialize a full set
int sigaddset(sigset_t *set, int signo); // Add signal to set
int sigdelset(sigset_t *set, int signo); // Remove signal from set
int sigismember(const sigset_t *set, int signo); // Check membership
```


---

## Blocking Signals:
```c
int sigprocmask(int how, const sigset_t *newset, sigset_t *oldset);
```

- how
  - SIG_SETMASK: The process's signal mask is changed to newest.
  - SIG_BLOCK: newest is added to the signal mask (OR operation).
  - SIG_UNBLOCK: newest is removed from the signal mask.

- If `oldest` is not `NULL`, signrocmask retrieves the current signal mask and stores it in `oldest`.

- If `newest` is `NULL`, signrocmask skips changing the signal mask but retrieves the current signal mask and stores it in `oldest`. In other words, passing null to set is a way to retrieve the current signal mask.

---
