
## Custom System Call Implementation 

This repository contains all the files and materials we used to make our project. 

## User Space Program

This program is written in C and executed in user space. Its purpose is to invoke the custom system call hash_file implemented in the kernel and print the resulting SHA-256 hash of a specified file.

Include Headers: The program includes standard C headers like stdio.h, stdlib.h, and others necessary for various functionalities.

Constants: It defines some constants such as MAX_FILE_PATH_LEN and SHA256_DIGEST_SIZE for use in the program.

Main Function:

It defines a main function where the program execution begins.
It sets the filename variable to the path of the file for which the hash is to be computed.
It declares an array hash_output to store the resulting hash.
It calls the custom system call syscall(__NR_hash_file, ...) with appropriate arguments to compute the hash.
If the system call fails, it prints an error message using perror() and exits with failure status.
It prints the computed hash value in hexadecimal format.

##


