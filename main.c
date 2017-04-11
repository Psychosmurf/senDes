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
} UserData;

int hash(char* userName, char* userEmail){
    int prod = 1;
    for (int i = 0; i < 50; i++){
        prod = prod*(userName[i]+1);
    }
    return prod % MAX_NUM_USERS;
}

void registerUser(UserData** userData){
    //allocate space for user input fields
    char* userName = (char*) malloc(sizeof(char)*MAX_NAME_SIZE);
    char* userPass = (char*) malloc(sizeof(char)*MAX_PASS_SIZE);
    char* userEmail = (char*) malloc(sizeof(char)*MAX_EMAIL_SIZE);

    //get user input
    char c;
    int i;
    for (i = 0; i < MAX_NAME_SIZE; i++) {
        c = getchar();
        if (c == ';') {
            for (;i < MAX_NAME_SIZE; i++) {
                userName[i] = ' ';
            }
            break;
        }
        userName[i] = c;
    }

    int j;
    for (j = 0; j < MAX_PASS_SIZE; j++) {
        c = getchar();
        if (c == ';') {
            for (;j < MAX_PASS_SIZE; j++) {
                userPass[j] = ' ';
            }
            break;
        }
        userPass[j] = c;
    }   
    
    int k;
    for (k = 0; k < MAX_EMAIL_SIZE; k++) {
        c = getchar();
        if (c == ';') {
            for (;k < MAX_EMAIL_SIZE; k++) {
                userEmail[k] = ' ';
            }
            break;
        }
        userEmail[k] = c;
    }

    //check input format
    if (i >= MAX_NAME_SIZE) {
        printf("error: name must be less than %d characters.", MAX_NAME_SIZE); 
        return;
    }
    if (j >= MAX_PASS_SIZE) {
        printf("error: passowrd must be less than %d characters.", MAX_PASS_SIZE); 
        return;
    }
    if (k >= MAX_EMAIL_SIZE) {
        printf("error: email must be less than %d characters.", MAX_EMAIL_SIZE);
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
    }
    else {
        //save user data
        strcpy((*userData)[hashNum].userName, userName);
        strcpy((*userData)[hashNum].userPass, userPass);
        strcpy((*userData)[hashNum].userEmail, userEmail);
        (*userData)[hashNum].registered = true;
    }
}

void registerUsersFromFile(FILE* dataFile, UserData** userData) {
    printf("successfully entered user registration from file\n");
    int userNum;
    char* userName = (char*) malloc(sizeof(char)*MAX_NAME_SIZE);
    char* userPass = (char*) malloc(sizeof(char)*MAX_PASS_SIZE);
    char* userEmail = (char*) malloc(sizeof(char)*MAX_EMAIL_SIZE);
    bool registered;

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
        }
        else {
            //save user data
            strcpy((*userData)[userNum].userName, userName);
            strcpy((*userData)[userNum].userPass, userPass);
            strcpy((*userData)[userNum].userEmail, userEmail);
            (*userData)[userNum].registered = true;
        }
    }

    printf("successfully loaded user data from file\n");
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
    }

    //load user data from file.
    FILE* dataFile = fopen("userdata.txt", "r");
    registerUsersFromFile(dataFile, &userData);
    fclose(dataFile);

    
    

    //get control input
    char inChar;
    while (1) {
        inChar = getchar();
        if (inChar == '\n') break;
        if (inChar == 'r') registerUser(&userData);
    }

    //test output
    int i = 0;
    UserData* trk = NULL;
    while (i < MAX_NUM_USERS) {
        trk = &userData[i];
        while (trk != NULL) {
            printf("user# %d name is: %s\nuser# %d pass is: %s\nuser# %d email is: %s\n", i, trk -> userName, 
                                                                                          i, trk -> userPass,
                                                                                          i, trk -> userEmail);
            trk = trk -> nextUser;
        }
        i++;
    }

    //save user data to file
    FILE* dataFile2 = fopen("userdata2.txt", "w+");
    trk = NULL;
    for (int i = 0; i < MAX_NUM_USERS; i++) {
        trk = &userData[i];
        while (trk != NULL) {
            if (trk -> registered){
                fprintf(dataFile2, "%d %s %s %s %d\n", i, trk -> userName, 
                                                         trk -> userPass, 
                                                         trk -> userEmail, 
                                                         trk -> registered);
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
    
    return 0;
}
