#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 100

void generatePassword(int length, int includeSpecialChars, char password[]) {
    const char *lowercase = "abcdefghijklmnopqrstuvwxyz";
    const char *uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *digits = "0123456789";
    const char *special = "!@#$%^&*()-_=+[]{}<>?/";

    char charset[MAX_PASSWORD_LENGTH] = "";
    strcat(charset, lowercase);
    strcat(charset, uppercase);
    strcat(charset, digits);
    if (includeSpecialChars) {
        strcat(charset, special);
    }

    int charsetLength = strlen(charset);

    for (int i = 0; i < length; i++) {
        password[i] = charset[rand() % charsetLength];
    }
    password[length] = '\0';
}

void evaluateStrength(const char *password) {
    int length = strlen(password);
    int hasLower = 0, hasUpper = 0, hasDigit = 0, hasSpecial = 0;

    for (int i = 0; i < length; i++) {
        if (password[i] >= 'a' && password[i] <= 'z') hasLower = 1;
        else if (password[i] >= 'A' && password[i] <= 'Z') hasUpper = 1;
        else if (password[i] >= '0' && password[i] <= '9') hasDigit = 1;
        else hasSpecial = 1;
    }

    int score = hasLower + hasUpper + hasDigit + hasSpecial;

    printf("\n🔍 Password strength: ");
    if (length >= 12 && score == 4) {
        printf("Strong ✅\n");
    } else if (length >= 8 && score >= 3) {
        printf("Moderate ⚠️\n");
    } else {
        printf("Weak ❌\n");
    }
}

int main() {
    srand(time(NULL));

    int length, includeSpecialChars;
    char password[MAX_PASSWORD_LENGTH];

    printf("=== Secure Password Generator ===\n");
    printf("Enter desired password length (max %d): ", MAX_PASSWORD_LENGTH - 1);
    scanf("%d", &length);

    if (length <= 0 || length >= MAX_PASSWORD_LENGTH) {
        printf("Invalid length.\n");
        return 1;
    }

    printf("Include special characters? (1 = Yes, 0 = No): ");
    scanf("%d", &includeSpecialChars);

    generatePassword(length, includeSpecialChars, password);
    printf("\n🔐 Generated password: %s\n", password);
    evaluateStrength(password);

    return 0;
}
