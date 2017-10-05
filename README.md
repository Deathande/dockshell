# Dock Shell
## Shell interpreter for CS4512, systems programming.

Currently being developed in C because we are only alowed to use the C standard library anyway.

## Compiling
./configure && make

## Running the wait command
Since the wait command only waits for child processes you can test it by running `fork_test` first. `fork_test` will fork a child process that sleeps for 10 seconds and prints the pid of that child process to the console. That pid can be given to wait and the wait command will wait until the child has finished.


