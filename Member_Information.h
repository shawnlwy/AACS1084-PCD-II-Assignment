#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning (disable:4996)

////   STUDENT ID     : 23WMD07195
////   STUDENT NAME   : LIONG KA KIEN
////   PROGRAMME      : DFT
////   TUTORIAL GROUP : 17

typedef struct {
    char memberId[11];
    char memberName[40];
    char passWord[25];
    char passwordRecovery[50];
    char genDer;
} PersonalInfo;

struct ContactInfo {
    char iC[15];
    char contactNumber[13];
};

typedef struct {
    PersonalInfo personalInfo;
    struct ContactInfo contactInfo;
} MEMBER;

void main();
void memberMenu();
void addMember();
void searchMember();
void modifyMember();
void displayMember();
void deleteMember();
void displayStatistic();
void memberReport();
void barChart(int loyaltyLevels[], char memberNames[][40], int numMembers);

void memberMenu() {
    int ans;

    while (1) {
        printf("\n\n");
        printf("\t=========================================\n");
        printf("\t\tMember Information Module:\n");
        printf("\t=========================================\n\n");
        printf("\t1. Adding Member\n");
        printf("\t2. Searching Member\n");
        printf("\t3. Modifying Member\n");
        printf("\t4. Displaying Member\n");
        printf("\t5. Deleting Member\n");
        printf("\t6. Gender Statistic\n");
        printf("\t7. Report\n");
        printf("\t8. Back to Main Menu\n");
        printf("\t9. Exit\n");

        printf("\n\n");

        printf("\tChoose One To Entry: ");
        scanf("%d", &ans);

        printf("\n\n");

        switch (ans) {
        case 1:
            addMember();
            break;
        case 2:
            searchMember();
            break;
        case 3:
            modifyMember();
            break;
        case 4:
            displayMember();
            break;
        case 5:
            deleteMember();
            break;
        case 6:
            displayStatistic();
            break;
        case 7:
            memberReport();
            break;
        case 8:
            system("cls");main();break;
        case 9:
            printf("\tYou have exited!!!!...\n");
            printf("\n\n");
            printf("\t\t\tBBBBB   Y   Y  EEEEE\tBBBBB   Y   Y  EEEEE\n");
            printf("\t\t\tB    B   Y Y   E    \tB    B   Y Y   E    \n");
            printf("\t\t\tBBBBB     Y    EEEE \tBBBBB     Y    EEEE \n");
            printf("\t\t\tB    B    Y    E    \tB    B    Y    E    \n");
            printf("\t\t\tBBBBB     Y    EEEEE\tBBBBB     Y    EEEEE\n\n\n");

            exit(0);
            break;
        default:
            printf("\tInvalid number, Try again.\n");
        }
    }
}

void addMember() {

    system("cls");
    MEMBER newMember;

    printf("\n\n");
    printf("\t==============================\n");
    printf("\t\tADDING MEMBER\n");
    printf("\t==============================\n");
    printf("\n\n");

    printf("\tEnter Member ID (000 to stop) : ");
    scanf("%10s", newMember.personalInfo.memberId);

    if (strcmp(newMember.personalInfo.memberId, "000") == 0) {
        printf("\n\n");
        printf("\tGo Back to Menu Page!!!\n");
        memberMenu();
    }

    printf("\tEnter Member Name             : ");
    scanf(" %39[^\n]", newMember.personalInfo.memberName);

    printf("\tEnter Password                : ");
    scanf(" %24s", newMember.personalInfo.passWord);

    printf("\tEnter Password Recovery       : ");
    scanf(" %49[^\n]", newMember.personalInfo.passwordRecovery);

    printf("\tEnter Gender ( Male = M / Female = F )   : ");
    scanf(" %c", &newMember.personalInfo.genDer);

    printf("\tEnter IC number (e.g. 112233-44-5555)    : ");
    scanf(" %14s", newMember.contactInfo.iC);

    printf("\tEnter Contact Number (e.g. 011-23456789) : ");
    scanf(" %12s", newMember.contactInfo.contactNumber);

    FILE* fp = fopen("member.dat", "ab");
    if (fp == NULL) {
        printf("FUnable to open the file!!!\n");
        return;
    }

    fwrite(&newMember, sizeof(MEMBER), 1, fp);
    fclose(fp);

    printf("\n\n");
    printf("\tMember is added successfully!!!!\n");
}

void searchMember() {

    system("cls");
    printf("\n\n");
    printf("\t=================================\n");
    printf("\t\tSEARCHING MEMBER\n");
    printf("\t=================================\n");
    printf("\n\n");

    FILE* fp;
    MEMBER tempMember;

    char searchID[11];
    int found = 0;
    fp = fopen("member.dat", "rb");
    if (fp == NULL) {
        printf("\tUnable to open the file!!!\n");
        return;
    }
    printf("\tEnter Member ID to search (000 to stop) : ");
    scanf("%s", searchID);
    if (strcmp(searchID, "000") == 0) {
        printf("\n\n");
        printf("\tGo Back to Menu Page!!!\n");
        fclose(fp);
        memberMenu();
    }
    printf("\n\n");

    while (fread(&tempMember, sizeof(MEMBER), 1, fp) != 0) {
        if (strcmp(tempMember.personalInfo.memberId, searchID) == 0) {
            printf("\t==================================================\n");
            printf("\tMember ID              :  %s\n", tempMember.personalInfo.memberId);
            printf("\tMember Name            :  %s\n", tempMember.personalInfo.memberName);
            printf("\tPassword               :  %s\n", tempMember.personalInfo.passWord);
            printf("\tPassword Recovery      :  %s\n", tempMember.personalInfo.passwordRecovery);
            printf("\tGender                 :  %c\n", toupper(tempMember.personalInfo.genDer));
            printf("\tIC Number              :  %s\n", tempMember.contactInfo.iC);
            printf("\tContact Number         :  %s\n", tempMember.contactInfo.contactNumber);
            printf("\t==================================================\n\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\tMember ID Is Not Found, Please Check The MemberId And Do It Again.\n");
    }

    fclose(fp);
}

void modifyMember() {

    system("cls");
    printf("\n\n");
    printf("\t=================================\n");
    printf("\t\tMODIFYING MEMBER\n");
    printf("\t=================================\n");
    printf("\n\n");

    FILE* fp;
    FILE* tempFile;
    MEMBER tempMember;
    MEMBER newMember;
    char searchID[11];
    int found = 0;

    fp = fopen("member.dat", "rb+");
    tempFile = fopen("temporary.dat", "wb");

    if (fp == NULL || tempFile == NULL) {
        printf("\tUnable to open the file!!!\n");
        return;
    }

    printf("\tEnter Member ID to modify (000 to stop) : ");
    scanf("%10s", searchID);
    printf("\n\n");
    if (strcmp(searchID, "000") == 0) {
        printf("\tGo Back to Menu Page!!!");
        fclose(fp);
        fclose(tempFile);
        memberMenu();
    }

    while (fread(&tempMember, sizeof(MEMBER), 1, fp) == 1) {
        if (strcmp(tempMember.personalInfo.memberId, searchID) == 0) {
            printf("\tEnter Member ID         : ");
            scanf("%10s", newMember.personalInfo.memberId);
            printf("\tEnter Member Name       : ");
            scanf(" %39[^\n]", newMember.personalInfo.memberName);
            printf("\tEnter Password          : ");
            scanf(" %24[^\n]", newMember.personalInfo.passWord);
            printf("\tEnter Password Recovery : ");
            scanf(" %49[^\n]", newMember.personalInfo.passwordRecovery);
            printf("\tEnter Gender ( Male = M / Female = F )   : ");
            scanf(" %c", &newMember.personalInfo.genDer);
            printf("\tEnter IC number (e.g. 112233-44-5555)    : ");
            scanf(" %14s", newMember.contactInfo.iC);
            printf("\tEnter Contact Number (e.g. 011-23456789) : ");
            scanf(" %12s", newMember.contactInfo.contactNumber);
            found = 1;
        }
        if (strcmp(tempMember.personalInfo.memberId, searchID) != 0)
            fwrite(&tempMember, sizeof(MEMBER), 1, tempFile);
        else
            fwrite(&newMember, sizeof(MEMBER), 1, tempFile);
    }

    if (!found) {
        printf("\tMember ID is not found.\n");
    }

    if (strcmp(tempMember.personalInfo.memberId, searchID) == 0)
        printf("\n\n\tMember Information is Changed!!\n");

    fclose(fp);
    fclose(tempFile);

    fp = fopen("member.dat", "wb");
    tempFile = fopen("temporary.dat", "rb");

    while (fread(&tempMember, sizeof(MEMBER), 1, tempFile) == 1) {
        fwrite(&tempMember, sizeof(MEMBER), 1, fp);
    }

    fclose(fp);
    fclose(tempFile);

    remove("temporary.dat");
}

void displayMember() {

    system("cls");
    printf("\n\n");
    printf("\t=================================\n");
    printf("\t\tDISPLAYING MEMBER\n");
    printf("\t=================================\n");
    printf("\n\n\n\n");

    FILE* fp;
    MEMBER tempMember;
    fp = fopen("member.dat", "rb");
    if (fp == NULL) {
        printf("\tFile is not created, go to add member function to create\n");
        return;
    }
    printf("=====================================================================================\n");
    printf("\t\t\t!!Member Information!!\n");
    printf("=====================================================================================\n\n");

    int count = 0;

    while (fread(&tempMember, sizeof(MEMBER), 1, fp) == 1) {
        printf("\tMember ID              :  %s\n", tempMember.personalInfo.memberId);
        printf("\tMember Name            :  %s\n", tempMember.personalInfo.memberName);
        printf("\tPassword               :  %s\n", tempMember.personalInfo.passWord);
        printf("\tPassword Recovery      :  %s\n", tempMember.personalInfo.passwordRecovery);
        printf("\tGender                 :  %c\n", toupper(tempMember.personalInfo.genDer));
        printf("\tIC Number              :  %s\n", tempMember.contactInfo.iC);
        printf("\tContact Number         :  %s\n", tempMember.contactInfo.contactNumber);
        printf("\n");
        printf("------------------------------------------------------------------------------------\n");

        count++;
    }

    if (count == 0) {
        printf("\n\n");
        printf("\t \t \t !!!!!No Record!!!!!");
        printf("\n\n\n");
    }

    fclose(fp);
}

void deleteMember() {
    system("cls");
    printf("\n\n");
    printf("\t=================================\n");
    printf("\t\tDELETING MEMBER\n");
    printf("\t=================================\n\n");

    FILE* fp;
    FILE* tempFile;
    MEMBER tempMember;
    char searchID[11];
    int found = 0;

    fp = fopen("member.dat", "rb");
    tempFile = fopen("temporary.dat", "wb");

    if (fp == NULL || tempFile == NULL) {
        printf("\tUnable to open the file!!!\n");
        return;
    }

    printf("\tEnter Member ID to delete (000 to stop) : ");
    scanf("%10s", searchID);
    printf("\n\n");

    if (strcmp(searchID, "000") == 0) {
        printf("\tGo Back to Menu Page!!!");
        fclose(fp);
        fclose(tempFile);
        memberMenu();
    }


    while (fread(&tempMember, sizeof(MEMBER), 1, fp) == 1) {
        if (strcmp(tempMember.personalInfo.memberId, searchID) == 0) {
            found = 1;
            printf("\tMember Found!\n\n");
            printf("==============================================================\n");
            printf("\tMember ID         : %s\n", tempMember.personalInfo.memberId);
            printf("\tName              : %s\n", tempMember.personalInfo.memberName);
            printf("\tGender            : %c\n", toupper(tempMember.personalInfo.genDer));
            printf("\tIC Number         : %s\n", tempMember.contactInfo.iC);
            printf("\tContact Number    : %s\n", tempMember.contactInfo.contactNumber);
            printf("==============================================================\n");
            printf("\n\n");
            printf("\tAre you sure to delete this member? (Y/N): ");

            char ans2;
            scanf(" %c", &ans2);

            system("cls");

            if (toupper(ans2) == 'Y') {
                printf("\n\n");
                printf("\tMember deleted successfully!\n");
            }
            else {
                fwrite(&tempMember, sizeof(MEMBER), 1, tempFile);
            }
        }
        else {
            fwrite(&tempMember, sizeof(MEMBER), 1, tempFile);
        }
    }

    if (!found) {
        printf("\tMember ID is not found.\n");
    }

    fclose(fp);
    fclose(tempFile);

    remove("member.dat");
    rename("temporary.dat", "member.dat");

    memberMenu();
}

void displayStatistic() {
    system("cls");
    printf("\n\n");
    printf("\t=================================\n");
    printf("\t\tMEMBER STATISTICS\n");
    printf("\t=================================\n\n");

    FILE* fp;
    MEMBER tempMember;
    int totalMembers = 0;
    int maleMembers = 0;
    int femaleMembers = 0;
    int unknowGender = 0;

    fp = fopen("member.dat", "rb");
    if (fp == NULL) {
        printf("\tUnable to open the file!!!!\n");
        return;
    }

    while (fread(&tempMember, sizeof(MEMBER), 1, fp) == 1) {
        totalMembers++;
        if (toupper(tempMember.personalInfo.genDer) == 'M') {
            maleMembers++;
        }
        else if (toupper(tempMember.personalInfo.genDer) == 'F') {
            femaleMembers++;
        }
        else
            unknowGender++;
    }

    fclose(fp);

    printf("\tTotal Members    : %d\n\n", totalMembers);
    printf("\t---------------------------------\n\n");
    printf("\tMale Members     : %d\n\n", maleMembers);
    printf("\t---------------------------------\n\n");
    printf("\tFemale Members   : %d\n\n", femaleMembers);
    printf("\t---------------------------------\n\n");
    if (unknowGender >= 1) {
        printf("\tInvalid Inputs   : %d\n\n", unknowGender);
        printf("\t---------------------------------\n\n\n");
    }

    char ans3;
    do {
        printf("\tDo you want to choose another function (Y/N) : ");
        scanf(" %c", &ans3);

        if (toupper(ans3) == 'Y') {
            memberMenu();
        }
        else if (toupper(ans3) == 'N') {
            printf("\n\tYou have exited!!!.......\n\n");
            printf("\n\n");
            printf("\t\t\tBBBBB   Y   Y  EEEEE\tBBBBB   Y   Y  EEEEE\n");
            printf("\t\t\tB    B   Y Y   E    \tB    B   Y Y   E    \n");
            printf("\t\t\tBBBBB     Y    EEEE \tBBBBB     Y    EEEE \n");
            printf("\t\t\tB    B    Y    E    \tB    B    Y    E    \n");
            printf("\t\t\tBBBBB     Y    EEEEE\tBBBBB     Y    EEEEE\n\n\n");
            exit(0);
        }
        else {
            printf("\tInvalid input, please try again!\n");
            displayStatistic();
        }
    } while (toupper(ans3) != 'Y' && toupper(ans3) != 'N');

}

void memberReport() {

    system("cls");
    printf("\n\n");
    printf("\t======================================\n");
    printf("\t\t\tREPORT\n");
    printf("\t======================================\n\n");
    printf("\t(MARK 0 - 100)\n\n");

    FILE* fp;
    MEMBER tempMember;
    int loyaltyLevels[100];
    char memberNames[100][40];
    int numMembers = 0;


    fp = fopen("member.dat", "rb");
    if (fp == NULL) {
        printf("\tUnable to open the file!!!\n");
        return;
    }


    while (fread(&tempMember, sizeof(MEMBER), 1, fp) == 1) {
        printf("\tEnter the level of the %s's member loyalty: ", tempMember.personalInfo.memberName);
        scanf("%d", &loyaltyLevels[numMembers]);

        if (loyaltyLevels[numMembers] <= 100 && loyaltyLevels[numMembers] >= 0) {
            printf("\n");

            strcpy(memberNames[numMembers], tempMember.personalInfo.memberName);
            numMembers++;
        }
        else {
            printf("\n\tInvalid number!!!\n");
            printf("\n\tChoose '7' to do again!!!!!!!\n");
            memberMenu();

        }
    }


    fclose(fp);


    barChart(loyaltyLevels, memberNames, numMembers);
}

void barChart(int loyaltyLevels[], char memberNames[][40], int numMembers) {
    system("cls");
    printf("\n\t=======================================\n");
    printf("\t\t\tBarchart\n");
    printf("\t=======================================\n\n");
    printf("       0---------1---------2---------3---------4---------5---------6---------7---------8---------9---------10\n");
    for (int i = 0; i < numMembers; i++) {
        printf("\t%s: ", memberNames[i]);
        printf("\n\t");
        for (int j = 0; j < loyaltyLevels[i]; j++) {
            printf("*");
        }
        printf("\n\n");
    }
    printf("\n       0---------1---------2---------3---------4---------5---------6---------7---------8---------9---------10\n");

    char ans4;
    do {
        printf("\n\n");
        printf("\tDo you want to choose another function (Y/N) : ");
        scanf(" %c", &ans4);

        if (toupper(ans4) == 'Y') {
            system("cls");
            memberMenu();
        }
        else if (toupper(ans4) == 'N') {
            printf("\n\tYou have exited!!!.......\n\n");
            printf("\n\n");
            printf("\t\t\tBBBBB   Y   Y  EEEEE\tBBBBB   Y   Y  EEEEE\n");
            printf("\t\t\tB    B   Y Y   E    \tB    B   Y Y   E    \n");
            printf("\t\t\tBBBBB     Y    EEEE \tBBBBB     Y    EEEE \n");
            printf("\t\t\tB    B    Y    E    \tB    B    Y    E    \n");
            printf("\t\t\tBBBBB     Y    EEEEE\tBBBBB     Y    EEEEE\n\n\n");
            exit(0);
        }
    } while (toupper(ans4) != 'Y' && toupper(ans4) != 'N');
}