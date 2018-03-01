# CS 450 Operating Systems
Mayank Bansal<br>
A20392482<br>
mbansal5@hawk.iit.edu

## Programming Assignment 2

The best way to learn how to implement a system call (or the control mechanism of an operating system) is to trace an existing system call and implement one. This assignment therefore consists of two parts. The first part asks you to trace the execution of the write()system call. The second part asks you to implement a system call that counts the number of a specific system call has been invoked.
<br>
1)	You will trace the write()system call. Assume that a user program executes the statement write(fd,10,n) but fd is undefined therefore the result of the execution will be an exception. You are asked to write down in a document which lines in which files of xv6 are executed. Organize the lines of code into blocks of code and explain the purpose of each of block. The result will be a story of what happened when a non-existing file descriptor is given to a write(). The story starts in the user space when the system call first gets executed and ends with a feedback to the user that fd is bad.
<br>
2)	We ask you to add the system call getCallCount() system call in xv6 such that when a valid system call number (as defined in syscall.h) is passed to it as an argument, it will return the number of times the referenced system call has been invoked in the user program that calls it. You need to design test cases and test programs to prove that your system call works as desired.



### Build & Run Instructions
Simply build the xv-6 repository with the following command:
```
$ make
```

After it builds, make and start the emulator by typing in:
```
$ make qemu-nox
```

This should now open the ```CS450$ ``` prompt to type in commands.

Verify the test program ```syscallCount``` shows up when you `ls`

Run the ```syscallCount``` test program with the following command:
```
CS450$ syscallCount
```
