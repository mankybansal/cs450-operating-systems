#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {

    int n = 23;
    int counts[n];

//
//	uint *ptr1 = malloc(sizeof(int));
//	printf(1,"%x\n", ptr1);
//	printf(1,"%x\n",myMemory(ptr1));


	if(fork()==0){
		uint *ptr2 = malloc(sizeof(int));
		printf(1,"%x\n", ptr2);
		printf(1,"%x\n",myMemory(ptr2));

		uint *ptr3 = malloc(sizeof(int));
		printf(1,"%x\n", ptr3);
		printf(1,"%x\n",myMemory(ptr3));
	}else{
		wait();
		uint *ptr = malloc(sizeof(int));
		printf(1,"%x\n",ptr);
		printf(1,"%x\n",myMemory(ptr));


		uint *ptr0 = malloc(sizeof(int));
		printf(1,"%x\n", ptr0);
		printf(1,"%x\n",myMemory(ptr0));

	}




//	if(fork()==0){
//		myMemory();
//	}else{
//		wait();
//		myMemory();
//	}

	exit();

    /*********************
     * Print Init Counts *
     *********************/

    // get system call counts
    getCallCount(counts, n);

    // pretty print all system call counts
    printf(1, "\n**********************\n");
    printf(1, "*  Init Call Counts  *\n");
    printf(1, "**********************\n");

    for (int i = 1; i < n; i++)
        printf(1, " - syscall #%d: %d\n", i, counts[i]);

    printf(1, "**********************\n\n");

    /*********************
     * Test System Calls *
     *********************/

    printf(1, "\n**********************\n");
    printf(1, "*  TESTING IN PARENT *\n");
    printf(1, "**********************\n");

    printf(1, "\n   **********************\n");
    printf(1, "   * Sample SystemCalls *\n");
    printf(1, "   **********************\n");

    // mkdir test
    printf(1, "\n   Calling mkdir()");
    mkdir("Hello World");
    printf(1, "\n   - Directory 'Hello World' created\n");

    // write test
    int sz, fd;
    char *c = (char *) malloc(sizeof("Hello World"));
    printf(1, "\n   Calling write()");
    fd = open("hello-world.txt", O_CREATE | O_WRONLY);
    write(fd, "Hello World", strlen("Hello World"));
    printf(1, "\n   - File hello-world.txt created");
    printf(1, "\n   - 'Hello World' written to file");
    printf(1, "\n   - %d bytes were written\n", sizeof(strlen("Hello World")));
    close(fd);

    printf(1, "\n   **********************\n\n");

    // get system call counts
    getCallCount(counts, n);

    // pretty print all system call counts
    printf(1, "\n   **********************\n");
    printf(1, "   * Parent Call Counts *\n");
    printf(1, "   **********************\n");

    for (int i = 1; i < n; i++)
        printf(1, "    - syscall #%d: %d\n", i, counts[i]);

    printf(1, "**********************\n");

    if (fork() == 0) {

        printf(1, "\n**********************\n");
        printf(1, "*  TESTING IN CHILD  *\n");
        printf(1, "**********************\n");

        printf(1, "\n   **********************\n");
        printf(1, "   * Sample SystemCalls *\n");
        printf(1, "   **********************\n");

        // read test
        printf(1, "\n   Calling read()");
        fd = open("hello-world.txt", O_RDONLY);
        sz = read(fd, c, 10);
        printf(1, "\n   - '%s' was read from file", c);
        printf(1, "\n   - %d bytes were read\n", sz);
        close(fd);

        // strcpy test
        char src[40];
        char dest[100];
        printf(1, "\n   Calling strcpy()");
        printf(1, "\n   - Copying string: Hello World");
        memset(dest, '\0', sizeof(dest));
        strcpy(src, "Hello World");
        strcpy(dest, src);
        printf(1, "\n   - Final copied string: %s\n", dest);

        printf(1, "\n  **********************\n\n");

        // get system call counts
        getCallCount(counts, n);

        // pretty print all system call counts
        printf(1, "\n   **********************\n");
        printf(1, "   *  Child Call Counts *\n");
        printf(1, "   **********************\n");

        for (int i = 1; i < n; i++)
            printf(1, "    - syscall #%d: %d\n", i, counts[i]);

        printf(1, "   **********************\n");
    }

    wait();

    exit();

}