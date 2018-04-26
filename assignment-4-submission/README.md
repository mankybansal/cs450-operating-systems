# CS 450 Operating Systems
Mayank Bansal<br>
A20392482<br>
mbansal5@hawk.iit.edu

Josiah Hunt<br>
A20350987<br>
jhunt5@hawk.iit.edu

## Group Programming Assignment 4
```
IN PROGRESS 
```

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

There are 5 programs to help run the assignment
### FSWalker
Checks the output_screenshots of the directory with inodes
```
$ fsWalker
```

### Inode Walker
Check output_screenshots from inodes from the following:
```
$ inWalker
```

### Comparing Outputs
Make sure you have run the `fsWalker` and `inWalker` before running this otherwise it will show no changes
```
$ coWalker
```

### Damaging the FS
Run the following command:

```
$ daInode
```


### Repairing Files

The following sequence will repair any inodes that are damaged:
```
$ fsWalker
$ inWalker
$ coWalker
$ reInode
```

```NOTE: RUN ALL THE COMMANDS IN ORDER```

## TEST PROGRAM
Here is a sample program that can be used to test the walkers and programs

```
$ mkdir hello
$ mkdir hello1
$ fsWalker
$ inWalker
$ coWalker
$ daInode [insert inode of hello]
```
Repair using:
```
$ fsWalker
$ inWalker
$ coWalker
$ reInode
```
Verify results:
```
$ fsWalker
$ inWalker
$ coWalker
```