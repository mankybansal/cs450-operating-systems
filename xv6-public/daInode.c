#include "types.h"
#include "user.h"
#include "syscall.h"

int main(int argc, char *argv[]) {
	damageDirInode(atoi(argv[1]));
	exit();
}
