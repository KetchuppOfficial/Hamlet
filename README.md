![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

# Hamlet

This project is a task of the programming course by [Ilya Dedinsky (aka ded32)](https://github.com/ded32).

## General information

This program sorts lines of a text in lexicographic order. There are two ways of sorting: forward and backward.

## Build and run

**Hamlet** is released for Linux only.

**Step 1:** Clone this repository.
```bash
git clone git@github.com:KetchuppOfficial/Hamlet.git
cd Hamlet
```

**Step 2:** Clone submodule.
```bash
git submodule init
git submodule update
```

**Step 3:** Build the project.
```bash
make
```

You'll see something like this:

```bash
username@machine:~/Hamlet$ make
Collecting dependencies for "src/Sorting.c"...
Collecting dependencies for "src/Hamlet.c"...
Collecting dependencies for "src/main.c"...
Compiling "src/main.c"...
Compiling "src/Hamlet.c"...
Compiling "src/Sorting.c"...
Collecting dependencies for "src/My_Lib.c"...
Compiling "src/My_Lib.c"...
ar: creating My_Lib.a
Linking project...

```

**Step 4:** Running.
```bash
make run IN=input_file_name OUT=output_file_name
```
The program won't work, if you don't specify **input_file_name** and **output_file_name**.
