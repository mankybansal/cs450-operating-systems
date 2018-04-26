/************************
 * Mayank Bansal
 * A20392482
 * mbansal5@hawk.iit.edu
 *
 * Josiah Hunt
 * A20350987
 * jhunt5@hawk.iit.edu
 ************************/

#include "types.h"
#include "user.h"
#include "syscall.h"

int main(int argc, char *argv[]) {
	(argc <= 1) ? directoryWalker(".") : directoryWalker(argv[1]);
	exit();
}
