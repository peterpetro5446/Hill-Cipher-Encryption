# Hill Cipher Encryption - pa01

## Overview

This project implements a classical Hill cipher encryption system in C. The program reads a square matrix from a key file and plaintext from another file, processes the input, and encrypts the message using the Hill cipher method.

## Author

- **Name:** Peter Petro  
- **Email:** PE310601@ucf.edu  
- **NID:** 5448978  

## Course

- **Class:** CIS3360 - Security in Computing - Spring 2025  
- **Instructor:** Professor Michael McAlpin  
- **Due Date:** 02-24-2025  

## Files

- `pa01.c`: Source code implementing the Hill cipher encryption.
- `kX.txt`: Input file containing the encryption key matrix.
- `pX.txt`: Input file containing the plaintext to encrypt.

## Compilation and Execution

To compile and run the program:

```bash
gcc -o pa01 pa01.c
./pa01 kX.txt pX.txt
```
## To run bash script:

Enable script to be executable and run .c file with it.
```bash 
chmod +x pa01test.mod.sh
./pa01test.mod.sh pa01.c
``` 

If you wish to use professor given bash script place the pa01.c file inside of testfiles folder.
```bash 
chmod +x pa01test.old.sh
./pa01test.old.sh pa01.c
```

