#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <fcntl.h>

// ROP Gadgets section
void gadget_1() {
    __asm__ volatile (
        "pop %rdi\n"     // Pop a value into rdi (first argument to syscall)
        "pop %rsi\n"     // Pop a value into rsi (second argument to syscall)
        "pop %rdx\n"     // Pop a value into rdx (third argument to syscall)
        "syscall\n"      // Invoke the syscall (execve, exit, etc.)
        :
        : /* No input operands */
        : "%rdi", "%rsi", "%rdx"  // Clobber list (telling the compiler that these registers will be modified)
    );
}

void gadget_2() {
    __asm__ volatile (
        "ret\n"          // Just return from this function to allow chaining
    );
}

void init(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}

void main() {
    char buffer[256];
    char username[100];
    char password[100];

    printf("==========================================\n");
    printf("               Bank Login:                \n");
    printf("==========================================\n");
    printf("Username: ");
    read(0, username, 100);
    printf("Password: ");
    read(0, password, 100);

    printf("==========================================\n");
    printf("Welcome, %s\n", username);
    printf("==========================================\n");

    printf("Please enter your security token: ");
    read(0, buffer, 300);

    // Call ROP gadgets to trigger shell execution or similar
    gadget_1();
    gadget_2();
}
