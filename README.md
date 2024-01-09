* C - Simple Shell (Group project)

-Basics of programming
-Basics of C
-Basics of thinking like an engineer
-Group work 
-Learning how to learn

Learning Objectives At the end of this project, you are expected to be able to explain to anyone, without the help of Google:

# Who designed and implemented the original Unix operating system?
# Who wrote the first version of the UNIX shell?
# Who invented the B programming language (the direct predecessor to the C programming language)?
# Who is Ken Thompson?
# How does a shell work?
# What is a pid and a ppid?
# How to manipulate the environment of the current process?
# What is the difference between a function and a system call?
# How to create processes?
# What are the three prototypes of main?
# How does the shell use the PATH to find the programs?
# How to execute another program with the execve system call?
# How to suspend the execution of a process until one of its children terminates?
# What is EOF / “end-of-file”?

TASKS:

0. Betty would be proud (mandatory) Write a beautiful code that passes the Betty checks

1. Simple shell 0.1 (mandatory) Write a UNIX command line interpreter

2. Simple shell 0.2 (mandatory) Simple shell 0.1 +

//Handle command lines with arguments
3. Simple shell 0.3 (mandatory) Simple shell 0.2 +

//Handle the PATH fork must not be called if the command doesn’t exist
4. Simple shell 0.4 (mandatory) Simple shell 0.3 +

//Implement the exit built-in, that exits the shell You don’t have to handle any argument to the built-in exit
5. Simple shell 1.0 (mandatory) Simple shell 0.4 +

//Implement the env built-in, that prints the current environment
6. Simple shell 0.1.1 #advanced Simple shell 0.1 +

//Write your own getline function
7. Simple shell 0.2.1 #advanced Simple shell 0.2 +

//You are not allowed to use strtok
8. Simple shell 0.4.1 #advanced Simple shell 0.4 +

//Handle arguments for the built-in exit
9. setenv, unsetenv #advanced Simple shell 1.0 +

//Implement the setenv and unsetenv builtin commands
10. cd #advanced Simple shell 1.0 +

//Implement the builtin command cd
11. ; #advanced Simple shell 1.0 +

//Handle the commands separator ;
12. && and || #advanced Simple shell 1.0 +

//Handle the && and || shell logical operators
13. alias #advanced Simple shell 1.0 +

//Implement the alias builtin command
14. Variables #advanced Simple shell 1.0 +

//Handle variables replacement $? variable $$ variable
15. Comments #advanced Simple shell 1.0 +

//Handle comments (#)
16. File as input #advanced Simple shell 1.0 +
