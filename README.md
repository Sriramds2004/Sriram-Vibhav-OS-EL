
## Custom System Call Implementation 

This repository contains all the files and materials we used to make our project.  The pair of programs demonstrates how a user-space program can invoke a custom system call implemented in the kernel to perform a specific operation—in this case, computing the SHA-256 hash of a file. The system call implementation in the kernel ensures proper handling of resources, error conditions, and security considerations.


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



## Kernel Space System Call Implementation

This code is part of the Linux kernel and implements the custom system call hash_file for computing the SHA-256 hash of a file.

Include Headers: It includes necessary kernel headers like linux/kernel.h, linux/syscalls.h, etc.

Define Constants: It defines constants such as MAX_FILE_PATH_LEN and SHA256_DIGEST_SIZE similar to the user-space program.

System Call Definition:

It defines the system call SYSCALL_DEFINE6(hash_file, ...) with six arguments.
The arguments include the filename, filename length, and buffer for hash output.
Inside the system call function, it performs the following steps:
Allocates memory for a buffer to read file content (buf).
Opens the file specified by the user.
Allocates a hash transformation object (tfm) and initializes a hash descriptor (desc) for SHA-256 hashing.
Reads the file content in chunks, updates the hash, and finalizes the hash computation.
Copies the computed hash value to the user-space buffer.
Frees allocated resources and closes the file.
Error Handling: It includes error handling to handle cases where file opening fails, memory allocation fails, or hash computation encounters an error.


