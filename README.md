Alpha Virtual Machine
=====================

A virtual machine that executes compiled executables of the javascript-like language `Alpha`.

Build
-----

Using a terminal, navigate in the project folder and type:

```sh
make
```

This will compile and link all files and libraries into a single file `alpha_vm`.

Run
---

After you have created an Alpha executable `*.abc` file with [Alpha Compiler](https://github.com/maninak/alpha_compiler), you can then launch the vm with the executable as an argument. 

```sh
./alpha_vm out.abc