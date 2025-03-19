## Thread Basics
- **Introduction to Threads**: Threads are lightweight processes that allow concurrent execution of tasks. They are managed independently by a scheduler.

## Comparison Between Process and Thread
- **Context Switching Time**: Threads are faster than processes due to their lighter nature.
- **Shared Memory**: Threads within the same process share memory, simplifying data sharing but increasing the risk of crashes affecting all threads.
- **Crash Behavior**:
  - Process crashes do not affect other processes.
  - Thread crashes terminate all threads in the process.
- **Process ID vs. Thread ID**:
  - Process ID is unique system-wide.
  - Thread ID is unique within a process and represented by `pthread_t`.

---

## Thread Operations
- **Creating Threads**: Use `pthread_create()` to create new threads.
- **Terminating Threads**: Use `pthread_exit()` to terminate threads and retrieve return values.
- **Thread ID**:
  - Use `pthread_self()` to get the current thread's ID.
  - Use `pthread_equal()` to compare thread IDs.

---

## Thread Synchronization
- **Mutex Basics**: Mutexes ensure exclusive access to shared resources.
- **Mutex Implementation**:
  1. Initialize the mutex.
  2. Lock the mutex before entering the critical section.
  3. Access shared resources.
  4. Unlock the mutex after exiting the critical section.

- **Condition Variables**:
  - **Signaling and Waiting**:
    - `pthread_cond_signal()`: Wakes up one waiting thread.
    - `pthread_cond_broadcast()`: Wakes up all waiting threads.
    - `pthread_cond_wait()`: Blocks a thread until a condition is signaled.

---

## Thread Management
- **Thread Termination**:
  - Normal termination.
  - Use `pthread_exit()` or `pthread_cancel()` to end threads.
  - If the main thread terminates, all threads terminate immediately.
- **Joinable Threads**: Use `pthread_join()` to wait for a thread to finish and retrieve its return value.
- **Detached Threads**: Use `pthread_detach()` to allow automatic cleanup of threads after they finish.

---

## Key Points
- **Threads vs. Processes**: Threads are lighter and share memory, making them ideal for concurrent tasks but more prone to crashes affecting all threads.
- **Synchronization**: Mutexes and condition variables are critical for ensuring thread-safe access to shared resources.
- **Thread Management**: Proper thread termination, joining, and detaching are crucial for avoiding resource leaks and ensuring efficient execution.
- **Deadlocks**: Manage mutexes carefully to avoid deadlocks caused by multiple locks.

---
