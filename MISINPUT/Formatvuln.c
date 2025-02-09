#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <fcntl.h>


void init(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    }   

void flag(){
    sendfile(STDOUT_FILENO, open("./flag.txt", 0),0,100);
    fflush(stdout);
}

void vuln(){

    char second[20] = "secondInput";
    char input_buffer[20] = "firstInput";
    void* secret = &flag;

    printf("Hey how's it going, this challenge is just a lil warmup, just a lil something y'know ;)\n");
    printf("So we gonna be doing a little printf argument shenanigans.\n");
    printf("So what was your name again?:");
    read(0, input_buffer, 64);
    puts("Well hello, ");
    printf(input_buffer);

    printf("TESTING flag() address %p \n", &flag);

    printf("Say, do you remember what the password was again?");
    read(0, second, 64);
    printf("Ah so it was %s", second);

}


int main(){
    init();
    vuln();
    

return 0;
}