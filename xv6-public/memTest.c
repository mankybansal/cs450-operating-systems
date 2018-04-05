#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {

	// number of pages taken by this code
	int kstack = 3;

	/***********************
	 * Test myMemory Calls *
	 ***********************/

	printf(1, "\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(1, "> Test 0                           \n");
	printf(1, "> Checking inital memory usage      \n");
	printf(1, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	printf(1, "\n     Checking initial memory usage...\n");
	myMemory();

	printf(1, "\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(1, "> Test 1                           \n");
	printf(1, "> Adding 1024 bytes to memory       \n");
	printf(1, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	printf(1, "\n     Adding 1024 bytes to memory...\n");
	sbrk(1024);
	myMemory();

	// clean up test case
	sbrk(-1024);

	printf(1, "\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(1, "> Test 2                           \n");
	printf(1, "> Adding 4096 bytes to memory      \n");
	printf(1, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	printf(1, "\n     Adding 4096 bytes to memory...\n");
	sbrk(4096);
	myMemory();

	// clean up test case
	sbrk(-4096);

	printf(1, "\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(1, "> Test 3                           \n");
	printf(1, "> Adding 4096 bytes to memory      \n");
	printf(1, "> Adding 4096 bytes to memory      \n");
	printf(1, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	printf(1, "\n     Adding 4096 bytes to memory...\n");
	sbrk(4096);
	printf(1, "\n     Adding 4096 bytes to memory...\n");
	sbrk(4096);
	myMemory();

	// clean up test case
	sbrk(-4096);
	sbrk(-4096);

	printf(1, "\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(1, "> Test 4                           \n");
	printf(1, "> Adding 4097 bytes to memory      \n");
	printf(1, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	myMemory();

	printf(1, "\n     Adding 4097 bytes to memory...\n");
	sbrk(4097);
	myMemory();

	// clean up test case
	printf(1, "\n     Cleaning up test case...\n");
	sbrk(-4097);
	myMemory();

	printf(1, "\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(1, "> Test 5                           \n");
	printf(1, "> Adding 4097 bytes to memory      \n");
	printf(1, "> Removing 4097 bytes from memory  \n");
	printf(1, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	printf(1, "\n     Adding 4097 bytes to memory...\n");
	sbrk(4096);
	printf(1, "\n     Removing 4097 bytes from memory...\n");
	sbrk(-4096);
	myMemory();

	printf(1, "\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(1, "> Test 6                           \n");
	printf(1, "> Adding 56732 pages to memory      \n");
	printf(1, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	myMemory();

	printf(1, "\n     Adding 56730 pages to memory...\n");
	for (int i = 0; i < 56730; i++)
		if (!sbrk(4096)) break;
	myMemory();

	// clean up test case
	for (int i = 0; i < 56730; i++)
		if (!sbrk(-4096)) break;

	printf(1, "\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(1, "> Test 7                           \n");
	printf(1, "> Adding 56750 pages to memory      \n");
	printf(1, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	printf(1, "\n     Adding 56750 pages to memory...\n");
	for (int i = 0; i < 56750; i++)
		if (!sbrk(4096)) break;
	myMemory();

	// clean up test case
	printf(1, "\n     Cleaning up test case...\n");
	for (int i = 0; i < 56735 - kstack; i++)
		if (!sbrk(-4096)) break;
	myMemory();

	printf(1, "\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(1, "> Test 8                           \n");
	printf(1, "> Adding 1000 pages to memory      \n");
	printf(1, "> Removing 1000 pages from memory      \n");
	printf(1, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	printf(1, "\n     Adding 1000 pages to memory...\n");
	for (int i = 0; i < 1000; i++)
		if (!sbrk(4096)) break;

	printf(1, "\n     Removing 1000 pages to memory...\n");
	for (int i = 0; i < 1000; i++)
		if (!sbrk(-4096)) break;
	myMemory();

	printf(1, "\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(1, "> Test 9                           \n");
	printf(1, "> Adding 10 pages in parent      \n");
	printf(1, "> Adding 10 pages in child       \n");
	printf(1, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	myMemory();

	printf(1, "\n     Adding 10 pages in PARENT...\n");
	for (int i = 0; i < 10; i++)
		if (!sbrk(4096)) break;
	myMemory();


	if (fork() == 0) {
		printf(1, "\n     Adding 10 pages in CHILD...\n");
		for (int i = 0; i < 10; i++)
			if (!sbrk(4096)) break;
		myMemory();

		exit();
	} else {
		wait();

		// clean up test case
		printf(1, "\n     Cleaning up PARENT...\n");
		for (int i = 0; i < 10; i++)
			if (!sbrk(-4096)) break;
		myMemory();

	}

	printf(1, "\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(1, "> Test 10                           \n");
	printf(1, "> Adding 10 pages in parent      \n");
	printf(1, "> Adding 5 pages in parent      \n");
	printf(1, "> Adding 10 pages in child       \n");
	printf(1, "> Removing 5 pages in child       \n");
	printf(1, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	myMemory();

	if (fork() == 0) {
		printf(1, "\n     Adding 10 pages in CHILD...\n");
		for (int i = 0; i < 10; i++)
			if (!sbrk(4096)) break;
		myMemory();

		printf(1, "\n     Removing 5 pages in CHILD...\n");
		for (int i = 0; i < 5; i++)
			if (!sbrk(-4096)) break;
		myMemory();

		exit();
	} else {
		wait();

		printf(1, "\n     Adding 10 pages in PARENT...\n");
		for (int i = 0; i < 10; i++)
			if (!sbrk(4096)) break;
		myMemory();

		printf(1, "\n     Adding 5 pages in PARENT...\n");
		for (int i = 0; i < 5; i++)
			if (!sbrk(4096)) break;
		myMemory();

		// clean up test case
		printf(1, "\n     Cleaning up PARENT...\n");
		for (int i = 0; i < 15; i++)
			if (!sbrk(-4096)) break;
		myMemory();
	}

	printf(1, "\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(1, "> Test 11                           \n");
	printf(1, "> Adding 10 pages in parent      \n");
	printf(1, "> Adding 10 pages in child       \n");
	printf(1, "> Adding 15 pages in child of child    \n");
	printf(1, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	myMemory();

	if (fork() == 0) {
		if (fork() == 0) {

			printf(1, "\n     Adding 15 pages in CHILD of CHILD...\n");
			for (int i = 0; i < 15; i++)
				if (!sbrk(4096)) break;
			myMemory();

			exit();
		}else {
			wait();

			printf(1, "\n     Adding 10 pages in CHILD...\n");
			for (int i = 0; i < 10; i++)
				if (!sbrk(4096)) break;
			myMemory();
		}
		exit();
	} else {
		wait();

		printf(1, "\n     Adding 5 pages in PARENT...\n");
		for (int i = 0; i < 5; i++)
			if (!sbrk(4096)) break;
		myMemory();

		// clean up test case
		printf(1, "\n     Cleaning up PARENT...\n");
		for (int i = 0; i < 5; i++)
			if (!sbrk(-4096)) break;
		myMemory();
	}

	printf(1, "\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(1, "> Test 12                           \n");
	printf(1, "> Adding 56750 pages in parent      \n");
	printf(1, "> Adding 1000 pages in child       \n");
	printf(1, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	myMemory();

	if (fork() == 0) {
		printf(1, "\n     Adding 1000 pages in CHILD...\n");
		for (int i = 0; i < 1000; i++)
			if (!sbrk(4096)) break;
		myMemory();

		exit();
	} else {
		wait();

		printf(1, "\n     Adding 56750 pages in PARENT...\n");
		for (int i = 0; i < 56750; i++)
			if (!sbrk(4096)) break;
		myMemory();

		// clean up test case
		printf(1, "\n     Cleaning up PARENT...\n");
		for (int i = 0; i < 56735 - kstack; i++)
			if (!sbrk(-4096)) break;
		myMemory();
	}

	exit();
}