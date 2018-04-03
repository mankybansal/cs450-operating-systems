# AS-3 Part-1

All programs are built and run on the screencast.


memTest: Allows you to see the difference between a program that frees memory, and one that doesn't.

To run: gcc -g -o memTest memTest.c

./memTest


dataTest: Does as instructed in problem description, allocating 100 ints, and trying to access memory that has already been freed.

To run: gcc -g -o dataTest dataTest.c

./dataTest



WRITE UP
The programs run successfully, despite leaking memory. Valgrind makes it very easy to isolate leaks with the --leak-check=yes command.
It even tells you exactly which line of code is causing the problem, be it an unfreed malloc, or an access to unallocated memory.


When accessing data after freeing it (in dataTest), Valgrind gives a lot of errors, in this case 100 because I try to access all 100 deallocated elements.
This is because we are accessing memory that we no longer have allocated. It is possible that something other than what we expect has been stored there.
It does not, however, show any memory leaks, because we successfully freed all memory.
