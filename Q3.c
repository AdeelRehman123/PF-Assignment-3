#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validateEmail(char* email) {
    int at = 0;
    int dot = 0;
    int index = -1;
    int length = strlen(email);

    if (length == 0) {
        return 0;
    }

    for (int i = 0; i < length; i++) {
        if (email[i] == '@') {
            at++;
            index = i;
        }
        if (index!= -1 && email[i] == '.') {
            dot = 1;
        }
    }

    if (at == 1 && dot) {
        return 1;
    }
    return 0;
}

int main() {
    char *email;
    int length;


    printf("Enter an email address: ");
    
    email = (char*) malloc(100 * sizeof(char));

    if (email == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    fgets(email, 100, stdin);
    length = strlen(email);
    if (email[length - 1] == '\n') {
        email[length - 1] = '\0';
    }

    if (validateEmail(email)) {
        printf("Valid Email\n");
    } else {
        printf("Invalid Email\n");
    }

    free(email);

    return 0;
}


