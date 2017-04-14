#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NUM_USERS 100
#define MAX_NAME_SIZE 50
#define MAX_PASS_SIZE 50
#define MAX_EMAIL_SIZE 50

typedef struct User_Data
{
    char* userName;
    char* userPass;
    char* userEmail;
    bool  registered;
    struct User_Data* nextUser;
    bool loggedIn;
} UserData;

int hash(char* userName, char* userEmail){
    int prod = 1;
    printf("hash is using userName: %s\n", userName);
    int sizeOfName = sizeof(userName)/sizeof(char);
    for (int i = 0; i < sizeOfName; i++){
        prod = prod*(userName[i]+1);
    }
    return prod % MAX_NUM_USERS;
}

void registerUser(UserData** userData){
    //allocate space for user input fields
    char* userName = (char*) malloc(sizeof(char)*MAX_NAME_SIZE);
    char* userPass = (char*) malloc(sizeof(char)*MAX_PASS_SIZE);
    char* userEmail = (char*) malloc(sizeof(char)*MAX_EMAIL_SIZE);

    scanf("%s", userName);
    if (sizeof(userName)/(sizeof(char)) > MAX_NAME_SIZE) {
        printf("error: name must be less than %d characters.", MAX_NAME_SIZE);
        return;
    }

    scanf("%s", userPass);
    if (sizeof(userName)/(sizeof(char)) > MAX_PASS_SIZE) {
        printf("error: password must be less than %d characters.", MAX_PASS_SIZE);
        return;
    }

    scanf("%s", userEmail);
    if (sizeof(userEmail)/(sizeof(char)) > MAX_EMAIL_SIZE) {
        printf("error: email must be less than %d characgers.", MAX_EMAIL_SIZE);
        return;
    }

    //calculate hash number
    int hashNum = hash(userName, userEmail);

    //if data already used
    if ((*userData)[hashNum].registered){

        //go to first available node
        UserData* trk = &(*userData)[hashNum];
        while (trk -> nextUser != NULL) {
            trk = trk -> nextUser;
        }

        //allocate space
        trk -> nextUser = (UserData*) malloc(sizeof(UserData));
        trk -> nextUser -> userName = (char*) malloc(sizeof(char)*MAX_NAME_SIZE);
        trk -> nextUser -> userPass = (char*) malloc(sizeof(char)*MAX_PASS_SIZE);
        trk -> nextUser -> userEmail = (char*) malloc(sizeof(char)*MAX_EMAIL_SIZE);

        //save user data
        strcpy(trk -> nextUser -> userName, userName);
        strcpy(trk -> nextUser -> userPass, userPass);
        strcpy(trk -> nextUser -> userEmail, userEmail);
        trk -> nextUser -> registered = true;
        trk -> nextUser -> nextUser = NULL;
        trk -> nextUser -> loggedIn = false;
    }
    else {
        //save user data
        strcpy((*userData)[hashNum].userName, userName);
        strcpy((*userData)[hashNum].userPass, userPass);
        strcpy((*userData)[hashNum].userEmail, userEmail);
        (*userData)[hashNum].registered = true;
        (*userData)[hashNum].loggedIn = false;
    }
}

void registerUsersFromFile(FILE* dataFile, UserData** userData) {
    int userNum;
    char* userName = (char*) malloc(sizeof(char)*MAX_NAME_SIZE);
    char* userPass = (char*) malloc(sizeof(char)*MAX_PASS_SIZE);
    char* userEmail = (char*) malloc(sizeof(char)*MAX_EMAIL_SIZE);

    while (!feof(dataFile)) {
        fscanf(dataFile, "%i", &userNum);
        fscanf(dataFile, "%s", userName);
        fscanf(dataFile, "%s", userPass);
        fscanf(dataFile, "%s", userEmail);
        //go to end of line
        char c;
        do {
            c = fgetc(dataFile);
        }
        while (c != '\n' && c != EOF);
        if (c == EOF) return;

        if ((*userData)[userNum].registered) {

            //go to first available node
            UserData* trk = &(*userData)[userNum];
            while (trk -> nextUser != NULL) {
                trk = trk -> nextUser;
            }

            //allocate space
            trk -> nextUser = (UserData*) malloc(sizeof(UserData));
            trk -> nextUser -> userName = (char*) malloc(sizeof(char)*MAX_NAME_SIZE);
            trk -> nextUser -> userPass = (char*) malloc(sizeof(char)*MAX_PASS_SIZE);
            trk -> nextUser -> userEmail = (char*) malloc(sizeof(char)*MAX_EMAIL_SIZE);

            //save user data
            strcpy(trk -> nextUser -> userName, userName);
            strcpy(trk -> nextUser -> userPass, userPass);
            strcpy(trk -> nextUser -> userEmail, userEmail);
            trk -> nextUser -> registered = true;
            trk -> nextUser -> nextUser = NULL;
            trk -> nextUser -> loggedIn = false;
        }
        else {
            //save user data
            strcpy((*userData)[userNum].userName, userName);
            strcpy((*userData)[userNum].userPass, userPass);
            strcpy((*userData)[userNum].userEmail, userEmail);
            (*userData)[userNum].registered = true;
            (*userData)[userNum].loggedIn = false;
        }
    }
}

void loginUser(UserData** userData){
    char* userName = (char*) malloc(sizeof(char)*MAX_NAME_SIZE);
    char* userPass = (char*) malloc(sizeof(char)*MAX_PASS_SIZE);
    char* userEmail = (char*) malloc(sizeof(char)*MAX_EMAIL_SIZE);

    scanf("%s", userName);
    printf("read username: %s\n", userName);
    if (sizeof(userName)/(sizeof(char)) > MAX_NAME_SIZE) {
        printf("error: name must be less than %d characters.", MAX_NAME_SIZE);
        return;
    }

    scanf("%s", userPass);
    printf("read userpass: %s\n", userPass);
    if (sizeof(userName)/(sizeof(char)) > MAX_PASS_SIZE) {
        printf("error: password must be less than %d characters.", MAX_PASS_SIZE);
        return;
    }

    scanf("%s", userEmail);
    printf("read userEmail: %s\n", userEmail);
    if (sizeof(userEmail)/(sizeof(char)) > MAX_EMAIL_SIZE) {
        printf("error: email must be less than %d characgers.", MAX_EMAIL_SIZE);
        return;
    }

    //calculate hash number
    int hashNum = hash(userName, userEmail);
    printf("checking hash value: %d\n", hashNum);

    //find user in userdata
    UserData* usrPtr = NULL;
    do {
        usrPtr = &(*userData)[hashNum];
        printf("testing user pointer: \nuserName: %s\nuserPass: %s\nuserEmail: %s\n", usrPtr -> userName,
                                                                                      usrPtr -> userPass,
                                                                                      usrPtr -> userEmail);
        if (strcmp(usrPtr -> userName, userName) == 0) {
            if (strcmp(usrPtr -> userEmail, userEmail) == 0) {
                if (strcmp(usrPtr -> userPass, userPass) == 0) {
                    usrPtr -> loggedIn = true;
                    return;
                }
                else printf("error: wrong password.\n");
            }
            printf("error: wrong email.\n");
            return;
        }
        else {
            if (usrPtr -> nextUser != NULL) {
                usrPtr = usrPtr -> nextUser;
            }
            else {
                printf("error: user name not found\n");
                return;
            }
        }
    }
    while (1);
}

void logoutUser(UserData** userData){
    char* userName = (char*) malloc(sizeof(char)*MAX_NAME_SIZE);
    char* userPass = (char*) malloc(sizeof(char)*MAX_PASS_SIZE);
    char* userEmail = (char*) malloc(sizeof(char)*MAX_EMAIL_SIZE);
    bool registered;
    bool loggedIn;
    
    scanf("%s", userName);
    if (sizeof(userName)/(sizeof(char)) > MAX_NAME_SIZE) {
        printf("error: name must be less than %d characters.", MAX_NAME_SIZE);
        return;
    }

    scanf("%s", userEmail);
    if (sizeof(userEmail)/(sizeof(char)) > MAX_EMAIL_SIZE) {
        printf("error: email must be less than %d characgers.", MAX_EMAIL_SIZE);
        return;
    }

    //calculate hash number
    int hashNum = hash(userName, userEmail);

    //find user in userdata
    UserData* usrPtr = NULL;
    do {
        usrPtr = &(*userData)[hashNum];
        if (strcmp(usrPtr -> userName, userName) == 0) {
            if (strcmp(usrPtr -> userEmail, userEmail) == 0) {
                usrPtr -> loggedIn = false;
                return;
            }
            else {
                printf("error: wrong email.\n");
                return;
            }
        }
        else {
            if (usrPtr -> nextUser != NULL) {
                usrPtr = usrPtr -> nextUser;
            }
            else {
                printf("error: user not found.\n");
                return;
            }
        }
    }
    while (1);
}


int main(){
    //Initialize user data array
    UserData* userData = (UserData*) malloc(sizeof(UserData)*MAX_NUM_USERS);

    for (int i = 0; i < MAX_NUM_USERS; i++) {
        userData[i].userName = (char*) malloc(sizeof(char)*MAX_NAME_SIZE);
        userData[i].userPass = (char*) malloc(sizeof(char)*MAX_PASS_SIZE);
        userData[i].userEmail = (char*) malloc(sizeof(char)*MAX_EMAIL_SIZE);
        userData[i].registered = false;
        userData[i].nextUser = NULL;
        userData[i].loggedIn = false;
    }

    //load user data from file.
    FILE* dataFile = fopen("userdata.txt", "r");
    if (dataFile != NULL) {
        registerUsersFromFile(dataFile, &userData);
    }
    fclose(dataFile);

    //get control input
    char inChar;
    while (1) {
        inChar = getchar();
        if (inChar == '\n') continue;
        if (inChar == 'r') registerUser(&userData);
        if (inChar == 'l') loginUser(&userData);
        if (inChar == 'o') logoutUser(&userData);
        if (inChar == 'e') break;
        //test output
        int i = 0;
        UserData* trk = NULL;
        while (i < MAX_NUM_USERS) {
            trk = &userData[i];
            while (trk != NULL) {
                printf("user# %d name is: %s\nuser# %d pass is: %s\nuser# %d email is: %s\nlogged in: %d\n", 
                    i, trk -> userName, 
                    i, trk -> userPass,
                    i, trk -> userEmail,
                       trk -> loggedIn);
                trk = trk -> nextUser;
            }
        i++;
        }        
    }

    //test output
    int i = 0;
    UserData* trk = NULL;
    while (i < MAX_NUM_USERS) {
        trk = &userData[i];
        while (trk != NULL) {
            printf("user# %d name is: %s\nuser# %d pass is: %s\nuser# %d email is: %s\n, logged in: %d\n", 
                    i, trk -> userName, 
                    i, trk -> userPass,
                    i, trk -> userEmail,
                       trk -> loggedIn);
            trk = trk -> nextUser;
        }
        i++;
    }

    //save user data to file
    FILE* dataFile2 = fopen("userdata.txt", "w+");
    trk = NULL;
    for (int i = 0; i < MAX_NUM_USERS; i++) {
        trk = &userData[i];
        while (trk != NULL) {
            if (trk -> registered){
                fprintf(dataFile2, "%d %s %s %s %d %d\n", i, trk -> userName, 
                                                         trk -> userPass, 
                                                         trk -> userEmail, 
                                                         trk -> registered,
                                                         trk -> loggedIn);
            }
            trk = trk -> nextUser;
        }
    }

    //close file
    fclose(dataFile2);

    //free allocated memory
    UserData* current = NULL;
    UserData* prev    = NULL;
    for (int i = 0; i < MAX_NUM_USERS; i++) {
        current = &userData[i];
        while (current != NULL) {
            free(current -> userName);
            free(current -> userPass);
            free(current -> userEmail);
            prev = current;
            current = current -> nextUser;
        }
    }
    free(userData);
}
