This project has been developed as part of the 42 curriculum by atabarea and medel-ca.

# Minishell

Minishell is a minimal command-line shell written in C. It supports basic functionalities like command execution, pipes, redirections, and environment variable handling, similar to a simplified version of Bash.

---

## Table of Contents

1. [Description](#description) 
2. [Instructions](#instructions)  
3. [Resources](#resources)  

---

## Description

Minishell is designed to demonstrate low-level system programming concepts in C, including:

- Executing system commands.
- Input/output redirections (`>`, `>>`, `<`).
- Command pipelines (`|`).
- Expanding environment variables (`$HOME`, `$PATH`, etc.).
- Basic built-in commands: `cd`, `echo`, `exit`, `export`, `unset`.
- Syntax error handling.

It serves as a learning exercise for processes, pipes, memory management, and command parsing in C.

---

## Instructions

1. Clone the repository

2. Go into the minishell folder
```console
cd minishell
```
3. Compile the program using Make
```console
make
```
4. Run the program:
```console
./minishell
```
5. A prompt will appear. You may enter your commands to be executed. Our minishell supports:
- Prompt display
- Command history (up and down arrows)
- System executables available from the environment (ls, cat, grep, etc)
- Local executables (./minishell)
- Builtin commands:
	- echo (and option -n)
	- cd (with only a relative or absolute path)
	- pwd (no options)
	- export (no options)
	- unset (no options)
	- env (no options or arguments)
	- exit (with exit number but no other options)
- Pipes | which redirect output from one command to input for the next
- Redirections:
	- '>' redirects output
	- '>>' redirects output in append mode
	- < redirects input
	- << DELIMITER displays a new prompt, reads user input until reaching DELIMITER, redirects user input to command input (does not update history)
- Environment variables (i.e. $USER or $VAR) that expand to their values.
- $? expands to the exit status of the most recently executed foreground pipeline.
- $$ expands to the process ID.
- User keyboard signals:
	- ctrl-c:
		When used in the father process displays a new prompt line.
		When used during the execution of a command ends the command (try with sleep 10)
	- ctrl-d
		When used in the father process exits the shell.
		When used during the execution of a command is ignored (try with sleep 10)
	- ctrl-\ does nothing
However, Minishell does not support \, ;, &&, ||, or wildcards.

---

## Resources

First aproximations to the project:
[Minishell: Building a mini-bash](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)
[MINISHELL 42: parsing](https://medium.com/@abkabex/minishell-42-f680eadde592)
[Minishell explained](https://42-cursus.gitbook.io/guide/3-rank-03/minishell)
[The bash guide](https://guide.bash.academy)

Lexer and Parser of the input:
[Arbol de sintaxis abstracta](https://es.wikipedia.org/wiki/%C3%81rbol_de_sintaxis_abstracta)
[Context free grammar](https://en.wikipedia.org/wiki/Context-free_grammar)
[Shell command lexer](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
[Lexical analyzer in C](https://www.geeksforgeeks.org/c/c-lexical-analyser-lexer/)

Executing child processes and redirections:
[Pipe() system call](https://www.geeksforgeeks.org/c/pipe-system-call/)

Other useful links:
[Explain shell](https://explainshell.com/)
