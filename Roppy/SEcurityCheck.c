#include <fcntl.h>
#include <unistd.h>

// Manually define the syscall numbers
#define SYS_write 1
#define SYS_read  0
#define SYS_open  2
#define SYS_close 3
#define SYS_sendfile 40

// Direct assembly for syscalls
void syscall_ret_gadget() __attribute__((section(".text")));
void syscall_ret_gadget() {
    __asm__ volatile (
        "syscall\n"  // Make the system call (using the syscall instruction)
        "ret\n"      // Return from the function
    );
}

// Custom implementation of strcspn
size_t custom_strcspn(const char *str, const char *delim) {
    size_t i = 0;
    while (str[i]) {
        for (size_t j = 0; delim[j]; ++j) {
            if (str[i] == delim[j]) {
                return i;
            }
        }
        i++;
    }
    return i;
}

// Write function to directly invoke the syscall
ssize_t custom_write(int fd, const void *buf, size_t count) {
    ssize_t ret;
    __asm__ volatile (
        "syscall\n"
        : "=a" (ret)  // Return value in 'ret' (syscall number returns in 'rax')
        : "a" (SYS_write), "D" (fd), "S" (buf), "d" (count)  // Syscall number and arguments in registers
    );
    return ret;
}

// Read function to directly invoke the syscall
ssize_t custom_read(int fd, void *buf, size_t count) {
    ssize_t ret;
    __asm__ volatile (
        "syscall\n"
        : "=a" (ret)  // Return value in 'ret' (syscall number returns in 'rax')
        : "a" (SYS_read), "D" (fd), "S" (buf), "d" (count)  // Syscall number and arguments in registers
    );
    return ret;
}

// Open function to directly invoke the syscall
int custom_open(const char *pathname, int flags) {
    int ret;
    __asm__ volatile (
        "syscall\n"
        : "=a" (ret)  // Return value in 'ret' (syscall number returns in 'rax')
        : "a" (SYS_open), "D" (pathname), "S" (flags)  // Syscall number and arguments in registers
    );
    return ret;
}

// Close function to directly invoke the syscall
int custom_close(int fd) {
    int ret;
    __asm__ volatile (
        "syscall\n"
        : "=a" (ret)  // Return value in 'ret' (syscall number returns in 'rax')
        : "a" (SYS_close), "D" (fd)  // Syscall number and arguments in registers
    );
    return ret;
}

// Sendfile function to directly invoke the syscall
ssize_t custom_sendfile(int out_fd, int in_fd, off_t *offset, size_t count) {
    ssize_t ret;
    __asm__ volatile (
        "syscall\n"
        : "=a" (ret)  // Return value in 'ret' (syscall number returns in 'rax')
        : "a" (SYS_sendfile), "D" (out_fd), "S" (in_fd), "d" (offset), "r" (count)  // Syscall number and arguments in registers
    );
    return ret;
}

// Custom security check
void security_check(char* param1, char* param2) {
    // Custom string comparison
    int i = 0;
    while (param1[i] != '\0' && param1[i] == param2[i]) {
        i++;
    }
    if (param1[i] == '\0' && param2[i] == '\0') {
        int fd = custom_open("./flag.txt", O_RDONLY);
        if (fd == -1) {
            return; // Error opening file
        }
        custom_sendfile(1, fd, NULL, 100);  // Direct syscall
        custom_close(fd);
    }
}

void _start() {
    char hi[8];
    char username[100];
    char password[100];

    // Print banner without libc
    const char banner[] = "==========================================\n"
                          "               Bank Login:                \n"
                          "==========================================\n";
    custom_write(1, banner, sizeof(banner) - 1);

    // Prompt for username and password
    const char username_prompt[] = "Username: ";
    custom_write(1, username_prompt, sizeof(username_prompt) - 1);
    custom_read(0, username, 100);
    username[custom_strcspn(username, "\n")] = '\0'; // Null-terminate username

    const char password_prompt[] = "Password: ";
    custom_write(1, password_prompt, sizeof(password_prompt) - 1);
    custom_read(0, password, 100);
    password[custom_strcspn(password, "\n")] = '\0'; // Null-terminate password

    const char welcome[] = "==========================================\n"
                           "Welcome, ";
    custom_write(1, welcome, sizeof(welcome) - 1);
    custom_write(1, username, custom_strcspn(username, "\n"));
    const char end_welcome[] = "\n==========================================\n";
    custom_write(1, end_welcome, sizeof(end_welcome) - 1);

    const char token_prompt[] = "Please enter your security token so we can really tell if it's you: ";
    custom_write(1, token_prompt, sizeof(token_prompt) - 1);
    custom_read(0, hi, 300);
    hi[custom_strcspn(hi, "\n")] = '\0'; // Null-terminate hi

    syscall_ret_gadget();
    security_check("skillissue", "RobinBanks");
}
