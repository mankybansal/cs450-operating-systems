# CS 450 Operating Systems
Mayank Bansal<br>
A20392482<br>
mbansal5@hawk.iit.edu

## Programming Assignment 1

### Introduction

The code that was given to us from the MIT xv-6 repository already had the `>` or `redirect` operator implemented, so no changes had to be made to that part of the `sh.c` file. This part of the code has been highlighted with comments for reference.

### Changes

The shell prompt was changed to `CS450$ ` in the following section of the code, `getcmd`:
```
int getcmd(char *buf, int nbuf) {

    /******************/
    /* CS450 PROMPT */
    /****************/

    printf(2, "CS450$ ");
    memset(buf, 0, nbuf);
    gets(buf, nbuf);
    if (buf[0] == 0) // EOF
        return -1;
    return 0;
}
```


`echo`, `wc`, `cat`, `ls`, `rm` are some system calls that work with this program.

The file was changed to add the `#define PARA  6` representation for parallel commands. These were the structures defined for the redirect and parallel functions

```
/******************************/
/* REDIRECT COMMAND STRUCTURE */
/******************************/

struct redircmd {
    int type;
    struct cmd *cmd;
    char *file;
    char *efile;
    int mode;
    int fd;
};


/******************************/
/* PARALLEL COMMAND STRUCTURE */
/******************************/

struct paracmd {
    int type;
    struct cmd *left;
    struct cmd *right;
};

```

Here, the parallel command can have a left command and right command. The redirect structure takes a command, file name and the mode to which it should open the file. The `type` attribute of the command simply helps us determine what to do with that command.

Next, we add the constructors for these commands. These are the constructors to initialize the required data for the commands:

```
/********************************/
/* REDIRECT COMMAND CONSTRUCTOR */
/********************************/

struct cmd *redircmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd) {
    struct redircmd *cmd;

    cmd = malloc(sizeof(*cmd));
    memset(cmd, 0, sizeof(*cmd));
    cmd->type = REDIR;
    cmd->cmd = subcmd;
    cmd->file = file;
    cmd->efile = efile;
    cmd->mode = mode;
    cmd->fd = fd;
    return (struct cmd *) cmd;
}

/********************************/
/* PARALLEL COMMAND CONSTRUCTOR */
/********************************/

struct cmd *paracmd(struct cmd *left, struct cmd *right) {
    struct paracmd *cmd;

    cmd = malloc(sizeof(*cmd));
    memset(cmd, 0, sizeof(*cmd));
    cmd->type = PARA;
    cmd->left = left;
    cmd->right = right;
    return (struct cmd *) cmd;
}

```

As we can see, we set the command type, and set the rest of the attributes. Once we're done, we return the command structure pointer.

To parse the characters for both of these commands, the following functions are referenced below:
```
/**************************/
/* PARSE REDIRECT COMMAND */
/**************************/

struct cmd *parseredirs(struct cmd *cmd, char **ps, char *es) {
    int tok;
    char *q, *eq;

    while (peek(ps, es, "<>")) {
        tok = gettoken(ps, es, 0, 0);
        if (gettoken(ps, es, &q, &eq) != 'a')
            panic("missing file for redirection");
        switch (tok) {
            case '<':
                cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
                break;
            case '>':
                cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREATE, 1);
                break;
            case '+':  // >>
                cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREATE, 1);
                break;
        }
    }
    return cmd;
}
```

Similarly for the parallel command:
```

struct cmd *parseline(char **ps, char *es) {
    struct cmd *cmd;

    cmd = parsepipe(ps, es);

    while (peek(ps, es, "!")) {
        gettoken(ps, es, 0, 0);
        cmd = backcmd(cmd);
    }

    if (peek(ps, es, ";")) {
        gettoken(ps, es, 0, 0);
        cmd = listcmd(cmd, parseline(ps, es));
    }

    /**************************/
    /* PARSE PARALLEL COMMAND */
    /**************************/

    if (peek(ps, es, "&")) {
        gettoken(ps, es, 0, 0);
        cmd = paracmd(cmd, parseline(ps, es));
    }

    return cmd;
}
```

In the `void runcmd(struct cmd *cmd)` function, the cases to execute redirect and parallel were added:
```
/************************/
/* RUN REDIRECT COMMAND */
/************************/

case REDIR:
    rcmd = (struct redircmd *) cmd;
    close(rcmd->fd);
    if (open(rcmd->file, rcmd->mode) < 0) {
        printf(2, "open %s failed\n", rcmd->file);
        exit();
    }
    runcmd(rcmd->cmd);
    break;

/************************/
/* RUN PARALLEL COMMAND */
/************************/

case PARA:
    prcmd = (struct paracmd *) cmd;

    if (fork1() == 0)
        runcmd(prcmd->left);

    if (fork1() == 0)
        runcmd(prcmd->right);

    wait();
    wait();
    break;
```

In the `struct cmd *nulterminate(struct cmd *cmd)` function we add the case for redirect and parallel such as follows to terminate the current operations:
```
/********************************/
/* REDIRECT COMMAND CONSTRUCTOR */
/********************************/

case REDIR:
    rcmd = (struct redircmd *) cmd;
    nulterminate(rcmd->cmd);
    *rcmd->efile = 0;
    break;

/*******************************/
/* NULL TERMINATE PARALLEL CMD */
/*******************************/

case PARA:
    prcmd = (struct paracmd *) cmd;
    nulterminate(prcmd->left);
    nulterminate(prcmd->right);
    break;

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

This should now open the ```CS450$ ` prompt to type in commands.

### Test Cases
#### 1. Simple Parallel Operation

```
CS450$ echo A & echo B & echo C
```

This test case will run all operations in parallel. If you run the same command enough times, it will print A,B,C in different orders.

#### 2. Parallel Operation

```
CS450$ echo A & ls
```

#### 3. Simple Redirect Operation

```
CS450$ echo "Hello World" > file1
```

This is a simple test case that writes to a file. The file contents can be verified.

#### 4. Extended Redirect Operation

```
CS450$ echo "Hello World" > file1 ; cat file1 ; wc file1
```

This will write to the file, and the read the contents and then perform a word count in order.

#### 5. Parallel & Redirect Operation

```
CS450$ echo "Hello World" > file1; cat file1 & wc file1 & ls ; rm file1
```

If you run this command enough times, you can see the word count and file contents sometimes showing up in between the `ls` operation. This is a good test-case as it shows the parallel operations working with the redirect operation.

###### NOTE:

The screenshots for these outputs can be found in the submission.