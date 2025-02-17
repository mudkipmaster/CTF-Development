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

void security_check(char* param1, char* param2){
    if(param1 == "skillissue" && param2 == "RobinBanks"){
        sendfile(STDOUT_FILENO, open("./flag.txt", 0),0,100);
        fflush(stdout);
    }
}

void main(){
    
    char username[100];
    char password[100];


    printf("==========================================");
    printf("               Bank Login:                ");
    printf("==========================================");
    printf("Username: ");
    read(0,username, 100);
    printf("Password: ");
    read(0, password, 100);    

    if(username == "Stupid" && password == "Dumb"){
        printf("==========================================");
        printf("Welcome, %s", &username);
        printf("==========================================");
    }

}
