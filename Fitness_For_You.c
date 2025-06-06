#include <stdio.h>
#include <string.h>

typedef struct account{
    char username[50];
    char password[17];
    int day;
    int month;
    int year;
    char phoneNum[15];
    char email[20];
    char city[50];
}Account;

void login (Account acc[], int *log, int a, char *user[]){
    char pass[17];
    int Valid;
    printf("===================================\n");
    printf("               Login            \n");
    printf("===================================\n");
    printf("Enter -1 to exit\n");

    do {
        printf("Username: ");
        scanf(" %[^\n]", user);

        if ((strcmp(user, "-1")) == 0){
            printf("Exiting...\n\n");
            return;
        }

        printf("Password: ");
        scanf(" %[^\n]", pass);

        for (int i = 0; i < a; i++) {
            if (strcmp(acc[i].username, user) == 0 && strcmp(acc[i].password, pass) == 0) {
                Valid = 1;
                break;
            }
        }

        if (!Valid) {
            printf("Something Went Wrong... Incorrect Username or Password!\n");
            continue;
        } else {
            printf("Login Successful!\n");
            (*log)++;
            return;
        }
        printf("===================================\n");
    } while(1);
}

void signUp(Account acc[], int *data){
    char temp[50];
    FILE *signUp = fopen("acc.txt", "a");
    printf("===================================\n");
    printf("               Sign Up            \n");
    printf("===================================\n");
    printf("Enter -1 to exit\n");

    do {
        int isDuplicate = 0;
        printf("Username\t: ");
        scanf(" %[^\n]", temp);

        if ((strcmp(temp, "-1")) == 0){
            printf("Exiting...\n\n");
            fclose(signUp);
            return;
        }

        for (int i = 0; i < *data; i++) {
            if (strcmp(temp, acc[i].username) == 0) {
                printf("Sorry, Username has been used, please pick a different username!\n");
                isDuplicate = 1;
                break;
            }
        }

        if (!isDuplicate) {
            strcpy(acc[*data].username, temp);
            fprintf(signUp, "%s#", acc[*data].username);
            break;
        }
    } while(1);

    do {
        printf("Password (Don't add any space)\t: ");
        scanf(" %s", temp);
        if (strlen(temp) > 16) {
            printf("Password is too long! Try again.\n");
        } else if (strlen(temp) < 5) {
            printf("Password is too short! Try again.\n");
        } else {
            strcpy(acc[*data].password, temp);
            fprintf(signUp, "%s#", acc[*data].password);
            break;
        }
    } while (1);

    printf("Your Birthdate in numbers (DD MM YYYY)\n");
    while (1) {
        printf("day\t: ");
        if (scanf(" %d", &acc[*data].day) == 1) {
            while (getchar() != '\n');
            break;
        } else {
            printf("Invalid input! Please enter a valid number.\n");
            while (getchar() != '\n');
        }
    }
    fprintf(signUp, "%d#", acc[*data].day);

    while (1) {
        printf("month\t: ");
        if (scanf(" %d", &acc[*data].month) == 1) {
            while (getchar() != '\n');
            break;
        } else {
            printf("Invalid input! Please enter a valid number.\n");
            while (getchar() != '\n');
        }
    }
    fprintf(signUp, "%d#", acc[*data].month);

    while (1) {
        printf("year\t: ");
        if (scanf(" %d", &acc[*data].year) == 1) {
            while (getchar() != '\n');
            break;
        } else {
            printf("Invalid input! Please enter a valid number.\n");
            while (getchar() != '\n');
        }
    }
    fprintf(signUp, "%d#", acc[*data].year);

    printf("Phone Number\t: ");
    scanf(" %[^\n]", acc[*data].phoneNum);
    fprintf(signUp, "%s#", acc[*data].phoneNum);

    printf("Email\t: ");
    scanf(" %[^\n]", acc[*data].email);
    fprintf(signUp, "%s#", acc[*data].email);

    printf("City\t: ");
    scanf(" %[^\n]", acc[*data].city);
    fprintf(signUp, "%s\n", acc[*data].city);

    fclose(signUp);
    (*data)++;
    printf("===================================\n\n");
}

void AccountDetails(Account acc[], int data, char user[]) {
    int found = 0, index;

    for (int i = 0; i < data; i++) {
        if (strcmp(acc[i].username, user) == 0) {
            index = i;
            found = 1;
            break;
        }
    }

    if (found) {
        printf("\n============= Account Details ===============\n");
        printf("Username        : %s\n", acc[index].username);
        printf("Birthdate       : %d-%d-%d\n", acc[index].day, acc[index].month, acc[index].year);
        printf("Phone Number    : %s\n", acc[index].phoneNum);
        printf("Email           : %s\n", acc[index].email);
        printf("City            : %s\n", acc[index].city);
        printf("==============================================\n");
    } else {
        printf("Error: Account not found!\n");
    }
}

void modifyAccount(Account accounts[], int jumlahData, char user[]) {
    int index = -1;

    for (int i = 0; i < jumlahData; i++) {
        if (strcmp(accounts[i].username, user) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: Account not found!\n");
        return;
    }

    int choice;
    printf("\n============= Modify Account Details ===============\n");
    printf("1. Change Password\n");
    printf("2. Change Birthdate\n");
    printf("3. Change Phone Number\n");
    printf("4. Change Email\n");
    printf("5. Change City\n");
    printf("6. Cancel\n");
    while (1) {
        printf("Choose an option: ");
        if (scanf("%d", &choice) == 1) {
            break;
        } else {
            printf("Invalid input! Please enter a valid number.\n");
            while (getchar() != '\n');
        }
    }

    switch (choice) {
        case 1:
            printf("Enter new password: ");
            scanf("%s", accounts[index].password);
            break;
        case 2:
            printf("Enter new birthdate (DD MM YYYY): ");
            scanf("%d %d %d", &accounts[index].day, &accounts[index].month, &accounts[index].year);
            break;
        case 3:
            printf("Enter new phone number: ");
            scanf("%s", accounts[index].phoneNum);
            break;
        case 4:
            printf("Enter new email: ");
            scanf("%s", accounts[index].email);
            break;
        case 5:
            printf("Enter new city: ");
            scanf("%s", accounts[index].city);
            break;
        case 6:
            printf("Modification canceled.\n");
            return;
        default:
            printf("Invalid choice!\n");
            return;
    }

    FILE *file = fopen("acc.txt", "w");
    if (!file) {
        printf("Error: Unable to update account file!\n");
        return;
    }

    for (int i = 0; i < jumlahData; i++) {
        fprintf(file, "%s#%s#%d#%d#%d#%s#%s#%s\n", accounts[i].username, accounts[i].password, accounts[i].day, accounts[i].month, accounts[i].year, accounts[i].phoneNum, accounts[i].email, accounts[i].city);
    }
    fclose(file);

    printf("Account details successfully updated!\n");

}

void AccountSet(int *log, Account acc[], int data, char user[]){
    int choice;
    while(1){
        printf("\n============= Account Setting ===============\n");
        printf("1. LogOut\n");
        printf("2. Account Details\n");
        printf("3. Edit Account Details\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf(" %d", &choice);

        switch (choice) {
        case 1:
            (*log) = 0;
            return;

        case 2:
            AccountDetails(acc, data, user);
            break;

        case 3:
            modifyAccount(acc, data, user);
            break;

        default:
            break;
        }
    }
}

int main() {
    Account accounts[100];
    int z = 1, choice, isLoggedIn = 0, jumlahData = 0;
    char user[50], pass[17];

    FILE *file = fopen("acc.txt", "r");
    if (!file) {
        printf("File not found!\n");
        return 1;
    }

    while(fscanf(file, "%[^#]#%[^#]#%d#%d#%d#%[^#]#%[^#]#%[^\n]\n", accounts[jumlahData].username, accounts[jumlahData].password, &accounts[jumlahData].day, &accounts[jumlahData].month, &accounts[jumlahData].year, accounts[jumlahData].phoneNum, accounts[jumlahData].email, accounts[jumlahData].city) != EOF) {
        jumlahData++;
    }
    fclose(file);

    while(z){
        if (isLoggedIn == 0){
            printf("=======================================================================\n");
            printf("  ______ _ _                         ______          __     __         \n");
            printf(" |  ____(_) |                       |  ____|         \\ \\   / /         \n");
            printf(" | |__   _| |_ _ __   ___  ___ ___  | |__ ___  _ __   \\ \\_/ /__  _   _ \n");
            printf(" |  __| | | __| '_ \\ / _ \\/ __/ __| |  __/ _ \\| '__|   \\   / _ \\| | | |\n");
            printf(" | |    | | |_| | | |  __/\\__ \\__ \\ | | | (_) | |       | | (_) | |_| |\n");
            printf(" |_|    |_|\\__|_| |_|\\___||___/___/ |_|  \\___/|_|       |_|\\___/ \\__,_|\n");
            printf("=======================================================================\n");
            printf("You have not logged in yet, please login or Sign-Up!\n");
            printf("1. Login\n");
            printf("2. Sign-Up\n");
            printf("3. Exit\n");
            printf("Choose: ");
            scanf(" %d", &choice);
            switch(choice){
                case 1:
                    login(accounts, &isLoggedIn, jumlahData, &user);
                    break;

                case 2:
                    signUp(&accounts, &jumlahData);
                    break;

                case 3:
                    printf("Program Exiting...");
                    z = 0;
                    break;

                default:
                    printf("Invalid input, please try again...\n\n");
            }
        } else {
            int pick;
            printf("=======================================================================\n");
            printf("  ______ _ _                         ______          __     __         \n");
            printf(" |  ____(_) |                       |  ____|         \\ \\   / /         \n");
            printf(" | |__   _| |_ _ __   ___  ___ ___  | |__ ___  _ __   \\ \\_/ /__  _   _ \n");
            printf(" |  __| | | __| '_ \\ / _ \\/ __/ __| |  __/ _ \\| '__|   \\   / _ \\| | | |\n");
            printf(" | |    | | |_| | | |  __/\\__ \\__ \\ | | | (_) | |       | | (_) | |_| |\n");
            printf(" |_|    |_|\\__|_| |_|\\___||___/___/ |_|  \\___/|_|       |_|\\___/ \\__,_|\n");
            printf("=======================================================================\n");
            printf("\nWelcome, %s.\n", user);
            printf("1. Account Setting\n");
            printf("2. Login History\n");
            printf("3. Delete Login History\n");
            printf("4. Account Details\n");
            printf("5. Edit Account Details\n");
            printf("6. Exit\n");
            printf("Choice: ");
            scanf(" %d", &pick);

            switch (pick){
                case 1:
                    AccountSet(&isLoggedIn, &accounts, jumlahData, user);
                    break;

                case 2:
                    

                case 3:

            }
        }
    }

    return 0;
}
