#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <fcntl.h>


void flag(){
    sendfile(STDOUT_FILENO, open("./flag.txt", 0),0,100);
    fflush(stdout);
}

void vuln(){
    char input_buffer[100];

    printf("Hey how's it going, this challenge is just a lil warmup, just a lil something y'know ;)\n");
    printf("So we gonna be doing a little printf argument shenanigans.\n");
    printf("So what was your name again?:");
    read(0, input_buffer, 400);
    puts("Well hello, ");
    printf(input_buffer);
    printf("Wait did I get that right? Could you tell me again please? I just want to make sure > ");
    read(0, input_buffer, 400);
    puts("Ah, now I got it for sure. Hello ");
    printf(input_buffer);

}


int main(){

    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    vuln();

    return 0;
}