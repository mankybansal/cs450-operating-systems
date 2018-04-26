#include "types.h"
#include "user.h"
#include "syscall.h"

int main(int argc, char *argv[]) {
	(argc <= 1) ? directoryWalker(".") : directoryWalker(argv[1]);
	exit();
}
