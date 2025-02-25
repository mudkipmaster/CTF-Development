#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <fcntl.h>  
#include <string.h>  // Required for strcmp

// Separate functions for ROP gadgets
void pop_rdi_gadget() { __asm__("pop %rdi; ret"); }
void pop_rsi_gadget() { __asm__("pop %rsi; ret"); }
void pop_rdx_gadget() { __asm__("pop %rdx; ret"); }
void align_stack() { __asm__("ret"); }

// Realistic functions
void set_value(int x) { printf("Setting value to: %d\n", x); }
void set_value2(int y) { printf("Setting another value to: %d\n", y); }
void calculate(int a, int b) {
    printf("Calculating %d + %d\n", a, b);
    int result = a + b;
    printf("Result: %d\n", result);
}

// Secure file read function
void security_check(char* param1, char* param2) {
    if (strcmp(param1, "skillissue") == 0 && strcmp(param2, "RobinBanks") == 0) {
        int fd = open("./flag.txt", O_RDONLY);
        if (fd != -1) {
            sendfile(STDOUT_FILENO, fd, NULL, 100);
            close(fd);
        }
        fflush(stdout);
    }
}

int main() {
    char buffer[256];  // Fixed buffer size
    char username[100] = {0};
    char password[100] = {0};

    printf("==========================================\n");
    fflush(stdout);
    printf("               Bank Login:                \n");
    fflush(stdout);
    printf("==========================================\n");
    fflush(stdout);
    printf("Username: \n");
    fflush(stdout);
    read(0, username, sizeof(username) - 1);  
    printf("Password: \n");
    fflush(stdout);
    read(0, password, sizeof(password) - 1);  

    printf("==========================================\n");
    fflush(stdout);
    printf("Welcome, %s\n", username);
    fflush(stdout);
    printf("==========================================\n");
    fflush(stdout);

    printf("Please enter your security token: \n");
    fflush(stdout);
    fgets(buffer, 400, stdin);  // Prevent buffer overflow


    puts("You entered: ");
    fflush(stdout);
    printf("%s", buffer);
    
    // Function calls that are now safe
    //set_value(42);
    //set_value2(84);
    //calculate(10, 20); 

    return 0;
}
