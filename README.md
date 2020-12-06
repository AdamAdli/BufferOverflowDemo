# Buffer Overflow Demo
Heavily inspired by ECE568, this is a toy example I put together to share a simple stack buffer overflow attack with classmates in CSC469.

## Why do we use demo_setup.c?
Different GCC versions and OSes will have some differentiation in their stack layout.
In reality, successful buffer overflow attacks are not so trivial to do due to protection mechanisms like [Address Space Layout Randomization](https://en.wikipedia.org/wiki/Address_space_layout_randomization), [Stack Canaries](https://en.wikipedia.org/wiki/Buffer_overflow_protection#Canaries), and [Executable Space Protection](https://en.wikipedia.org/wiki/Executable_space_protection).

## So what's the point of this repo?
Just for fun. :)
Although dated and artificial, this is a small toy just to inspire interest in computer security.

## Demo Overview
For basic background knowledge, read Aleph One's [Smashing The Stack For Fun And Profit](https://inst.eecs.berkeley.edu/~cs161/fa08/papers/stack_smashing.pdf).

In this example, `demo_target.c` contains the vulnerable target program. You can run this program with `gdb` in order to investigate the memory address of `buf`.

Notice how there is an unsafe `strcpy` call copying `argv[1]` to `buf`. 

In `demo_exploit.c`, you should construct the arguments passed into the program `demo_target` through `exec` in a way to exploit the `strcpy` by overwriting `foo`'s stack's return address and spawning a shell by executing the `shellcode`.

