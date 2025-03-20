# Chat Application

This project is a command-line-based peer-to-peer chat application built in C. It allows multiple computers to connect and exchange messages over TCP Socket using a simple user interface that mimics a UNIX shell.

## Features

- **help**: Displays information about available commands.
- **myip**: Shows the IP address of the current process (excluding local address `127.0.0.1`).
- **myport**: Shows the port number on which the process is listening for connections.
- **connect `<destination>` `<port>`**: Establishes a TCP connection to the specified IP and port.
- **list**: Lists all active connections with their details.
- **terminate `<connection ID>`**: Ends a specific connection identified by its ID.
- **send `<connection ID>` `<message>`**: Sends a message to the specified connection ID.
- **exit**: Closes all active connections and terminates the application.

## Build Instructions

1. Clone this repository and navigate to the project directory.
2. Run the following command to compile the program:
   
```bash
make
```
This will compile the source files in the `src` directory and generate the executable in the `bin` directory.

## Usage

Launch the application by specifying a port number as a command-line argument:

```bash
./bin/chat_app <port>
```

## Command Summary

| Command                      | Description                                                                 |
|------------------------------|-----------------------------------------------------------------------------|
| `help`                       | Displays information about available commands.                             |
| `myip`                       | Displays the IP address of the current process.                            |
| `myport`                     | Displays the port number the process is listening on.                      |
| `connect <IP> <port>`        | Establishes a TCP connection to the specified IP and port.                 |
| `list`                       | display the IP address and the listening port of all the peers.            |
| `terminate <connection ID>`  | Ends a specific connection identified by its ID.                          |
| `send <connection ID> <msg>` | Sends a message to a specified connection.                                |
| `exit`                       | Closes all active connections and terminates the application.              |

## Additional Targets in Makefile

1. Clean Build Files:
```bash
make clean
```
This removes all compiled files and the bin directory.

2. Memory Debugging:
```bash
make memcheck
```
This runs the application with Valgrind to check for memory leaks, using port 5000 as an example.
