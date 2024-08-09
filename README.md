# Pipex
The **Pipex** project is a challenge within the 42 School curriculum aimed at deepening students' understanding of process management, inter-process communication (IPC), and the use of Unix system calls in C. The goal is to replicate the behavior of the shell pipe (`|`) by chaining multiple commands together, passing the output of one command as the input to the next.

## **Task**

The task was to implement a program that replicates the functionality of the Unix pipe (`|`) for two commands. The program needs to handle various tasks such as:

- Executing two commands with the first command's output being piped to the second command's input.
- Managing file descriptors, duplicating them as necessary to redirect input and output.
- Handling errors gracefully, including command execution failures, invalid arguments, and file access issues.

**Key objectives included:**
- Implementing a program that mimics the following shell command: **`< file1 cmd1 | cmd2 > file2`**, where the output of `cmd1` reading from `file1` is piped to `cmd2`, which writes to `file2`.
- Ensuring the program correctly handles edge cases, such as missing files, invalid commands, and permission errors.
- Demonstrating a deep understanding of Unix system calls, particularly `pipe()`, `dup2()`, `fork()`, and `execve()`.

## **Key Achievements**
- Successful Process Management: Implemented a robust solution that handles the creation and management of child processes, ensuring proper execution and termination of piped commands.
- Efficient Inter-Process Communication: Developed a reliable pipeline mechanism using Unix pipes, enabling seamless data transfer between commands.
- Comprehensive Error Handling: Integrated extensive error checking and handling to manage edge cases and unexpected scenarios, ensuring the program operates reliably in various conditions.

## Installation

To install the Project, follow these steps:
1. Clone the repository: **`git clone git@github.com:jakobsitory/02_pipex_42CC.git`**
2. Navigate to the project directory: **`cd 02_pipex_42CC`**
3. Build the project: **`make`**

## **Usage**

The `pipex` program should be executed as follows:

```bash
./pipex file1 cmd1 cmd2 file2
