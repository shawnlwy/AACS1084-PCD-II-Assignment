#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<limits.h>
#pragma warning(disable:4996)

void main();
void staffMenu();
void Login();
void SignUp();
void Staff();
void AddRecord();
void SearchRecord();
void DisplayRecord();
void DeleteRecord();
void ModifyRecord();
void StaffStatistics();

typedef struct {
	char phone[15];
	char email[30];
} CONTACT;

typedef struct {
	char name[40], staffId[11], pwdRecovery[50], position[11];
	char password[50];
	char gender;
	CONTACT contact;
	int yearsOfService;
}STAFF;


void staffMenu()
{
	int mode;

	do {
		system("cls");
		printf("==================================\n");
		printf("\n\tWelcome To Staff\n");
		printf("==================================\n");
		printf("User login\n");
		printf("1. Login Staff\n");
		printf("2. Sign Up Staff\n");
		printf("3. Back to Main Menu\n");
		printf("0. exit\n");
		printf("==================================");
		printf("\nEnter a number to mode (1 or 2 or 3 or 0) :");
		scanf("%d", &mode);

		switch (mode)
		{
		case 1: Login(); break;
		case 2: SignUp(); break;
		case 3: system("cls");main();break;
		case 0: exit(-1); break;
		default:printf("Invalid entry");
		}
	} while (mode != 0);

	system("pause");
}

void SignUp() {
	char sId[20], passwd[30];

	printf("\nNow please enter Staff ID and password as credentials for system login.\n");

	printf("\nEnter Staff Id:");
	scanf(" %s", sId);

	do {
		printf("\nEnter Password:");
		scanf(" %s", passwd);

		if (strncmp(passwd, "ST", 2) != 0 || strlen(passwd) != 5) {
			printf("Password should start with 'ST' and followed by 3 digits (e.g. 'ST001')\n");
		}
	} while (strncmp(passwd, "ST", 2) != 0 || strlen(passwd) != 5);

	Login();
}


void Login() {
	char sId[20], passwd[30];

	system("cls");
	printf("\t===========================\n");
	printf("\t\tLogin\n");
	printf("\t===========================\n");
	printf("Enter Staff ID:");
	scanf("%s", sId);

	printf("\n");
	printf("Enter Your Password:");
	scanf("%s", passwd);

	if (strlen(sId) >= 5 && strlen(sId) <= 20 && strlen(passwd) >= 5 && strlen(passwd) <= 20)
	{
		printf("Login Successful!\n");
		system("pause");
		Staff();
	}
	else {
		printf("Login failed!\n");
		system("pause");
		return 0;
	}
}


void Staff() {
	int choice;
	do {
		printf("====================================\n");
		printf("\t\tWelcome\t\n");
		printf("====================================\n");
		printf("User login\n");
		printf("1. Add Record\n");
		printf("2. Display Record\n");
		printf("3. Search Record\n");
		printf("4. Modify Record\n");
		printf("5. Delete Record\n");
		printf("6. Staff Statistics\n");
		printf("7. Back to Main Menu\n");
		printf("0. Exit\n");
		printf("==================================");
		printf("\nEnter a number to mode ( 1 or 2 or 3 or 4 or 5 or 6) :");
		scanf(" %d", &choice);

		switch (choice) {
		case 1:
			AddRecord();
			break;
		case 2:
			DisplayRecord();
			break;
		case 3:
			SearchRecord();
			break;
		case 4:
			ModifyRecord();
			break;
		case 5:
			DeleteRecord();
			break;
		case 6:
			StaffStatistics();
			break;
		case 7:
			system("cls");main();break;
		case 0:
			printf("Exit");
			exit(-1);
			break;
		default:
			printf("Invalid choice\n");
		}
	} while (choice != 0);
	return 0;
}

void AddRecord() {

	system("cls");
	printf("\t*********\n");
	printf("\t\tADD STAFF\n");
	printf("\t*********\n");
	printf("\n");
	FILE* fp;
	STAFF addStaff;
	fp = fopen("staff.bin", "ab");
	char an;

	if (fp == NULL) {
		printf("Error opening file.....");
	}
	do {
		printf("Do you want to add a record ?(Y/N) ");
		rewind(stdin);
		scanf(" %c", &an);

		if (toupper(an) == 'Y') {
			printf("\nEnter Staff ID:");
			scanf(" %s", addStaff.staffId);

			printf("\nEnter name:");
			scanf(" %[^\n]", addStaff.name);

			printf("\nEnter gender (m or f):");
			scanf(" %c", &addStaff.gender);

			printf("\nEnter password:");
			scanf(" %s", addStaff.password);

			printf("\nEnter password recovery:");
			scanf(" %s", addStaff.pwdRecovery);

			printf("\nEnter position:");
			scanf(" %s", addStaff.position);

			printf("\nEnter phone:");
			scanf(" %s", addStaff.contact.phone);

			printf("\nEnter email:");
			scanf(" %s", addStaff.contact.email);

			printf("\nEnter how many years of services: ");
			scanf(" %d", &addStaff.yearsOfService);

			fwrite(&addStaff, sizeof(STAFF), 1, fp);
			fclose(fp);
			printf("\n");
			printf("Added successfully!!!\n");
		}
		else {
			printf("GOOD BYE..\n");
			printf("\n");
			return;
		}
	} while (toupper(an) == 'Y');

}

void SearchRecord() {
	printf("\n");
	printf("\t++++++++++++++++++++++++\n");
	printf("\t+SEARCHING FOR STAFF+\n");
	printf("\t++++++++++++++++++++++++\n");
	printf("\n");

	FILE* fp;
	STAFF tempStaff;

	int searchId[11];
	fp = fopen("staff.bin", "rb");
	if (fp == NULL) {
		printf("Error opening file...\n");
		return;
	}

	int found = 0;

	printf("\tEnter Staff ID to search: ");
	scanf("\t%s", &searchId);

	while (fread(&tempStaff, sizeof(STAFF), 1, fp) != 0) {
		if (strcmp(tempStaff.staffId, searchId) == 0)
			printf("\n");
		printf("\t==================================================\n");
		printf("\tSTAFF ID              :  %s\n", tempStaff.staffId);
		printf("\tSTAFF NAME            :  %s\n", tempStaff.name);
		printf("\tGENDER                :  %c\n", tempStaff.gender);
		printf("\tPASSWORD              :  %s\n", tempStaff.password);
		printf("\tPASSWORD RECOVERY     :  %s\n", tempStaff.pwdRecovery);
		printf("\tPOSITION              :  %s\n", tempStaff.position);
		printf("\tPHONE                 :  %s\n", tempStaff.contact.phone);
		printf("\tEMAIL                 :  %s\n", tempStaff.contact.email);
		printf("\tYears Of Service      :  %d\n", tempStaff.yearsOfService);
		printf("\t==================================================\n\n");
		found = 1;
		break;

	}

	if (!found)
		printf("Record with name '%s' not found!!!\n", searchId);
	printf("\n");

	fclose(fp);
}

void DisplayRecord() {
	printf("\t+++++++++++++++++++++++++\n");
	printf("\t+DISPLAYING FOR STAFF\t+\n");
	printf("\t+++++++++++++++++++++++++\n");

	FILE* fp;
	STAFF tempStaff;
	int count = 0;
	fp = fopen("staff.bin", "rb");

	if (fp == NULL) {
		printf("Error file opening...");
		return;
	}
	while (fread(&tempStaff, sizeof(STAFF), 1, fp) == 1) {
		printf("\n");
		printf("\t*************\n");
		printf("\tSTAFF ID              :  %s\n", tempStaff.staffId);
		printf("\tSTAFF NAME            :  %s\n", tempStaff.name);
		printf("\tGENDER                :  %c\n", tempStaff.gender);
		printf("\tPASSWORD              :  %s\n", tempStaff.password);
		printf("\tPASSWORD RECOVERY     :  %s\n", tempStaff.pwdRecovery);
		printf("\tPOSITION              :  %s\n", tempStaff.position);
		printf("\tPHONE                 :  %s\n", tempStaff.contact.phone);
		printf("\tEMAIL                 :  %s\n", tempStaff.contact.email);
		printf("\tYears Of Service      :  %d\n", tempStaff.yearsOfService);
		printf("\n\n");

		count++;
	}

	if (count == 0) {
		printf("No record found !!!\n");
	}
	fclose(fp);
}


void DeleteRecord() {

	system("cls");
	printf("\t***********\n");
	printf("\t\tDELETE STAFF\n");
	printf("\t***********\n");

	FILE* fp;
	FILE* fp1;
	STAFF tempStaff;
	char id1[11];
	int found = 0;

	fp = fopen("staff.bin", "rb");
	fp1 = fopen("temp.bin", "wb");

	printf("\nEnter staff ID to delete:");
	scanf("%s", &id1);

	while (fread(&tempStaff, sizeof(STAFF), 1, fp) == 1) {
		if (strcmp(tempStaff.staffId, id1) == 0) {
			found = 1;
			printf("\tSTAFF FOUND\n");
			printf("\t*************\n");
			printf("\tSTAFF ID              :  %s\n", tempStaff.staffId);
			printf("\tSTAFF NAME            :  %s\n", tempStaff.name);
			printf("\tGENDER                :  %c\n", tempStaff.gender);
			printf("\tPASSWORD              :  %s\n", tempStaff.password);
			printf("\tPASSWORD RECOVERY     :  %s\n", tempStaff.pwdRecovery);
			printf("\tPOSITION              :  %s\n", tempStaff.position);
			printf("\tPHONE                 :  %s\n", tempStaff.contact.phone);
			printf("\tEMAIL                 :  %s\n", tempStaff.contact.email);
			printf("\tYears Of Service      :  %d\n", tempStaff.yearsOfService);
			printf("\n\n");
			printf("\tAre you sure to delete this staff? (Y/N): ");

			char an2;
			scanf(" %c", &an2);

			system("cls");

			if (toupper(an2) == 'Y') {
				printf("\n");
				printf("\tStaff deleted !!!\n");
				printf("\n");
			}
			else {
				fwrite(&tempStaff, sizeof(STAFF), 1, fp1);
			}

		}
		else {
			fwrite(&tempStaff, sizeof(STAFF), 1, fp1);
		}
	}
	if (!found) {
		printf("Staff Not Found!!!\n");
		printf("\n");
	}

	fclose(fp);
	fclose(fp1);
	remove("staff.bin");
	rename("temp.bin", "staff.bin");
	return;
}

void ModifyRecord() {

	system("cls");
	printf("\t**********\n");
	printf("\t\tMODIFY STAFF\n");
	printf("\t**********\n");

	char ans, cont, staffId[5], updPass[50], pwdRecovery[25];
	int i = 0, sCount, modiCount = 0, found = 0;
	FILE* fp;
	STAFF s[10];
	fp = fopen("staff.bin", "rb");
	if (fp == NULL) {
		printf("Error opening file!");
		return;
	}
	while (fread(&s[i], sizeof(STAFF), 1, fp)) {
		i++;
	}
	sCount = i;
	fclose(fp);

	do {
		printf("\nEnter Staff ID to be Modified :");
		rewind(stdin);
		scanf("%s", staffId);
		found = 0;
		printf("\nStaff ID Name        Position Password Password Recovery   Contact     Email");
		printf("\n======== =========== ======== ======== ================= ============  ==========");
		for (i = 0; i < sCount; i++) {
			if (strcmp(staffId, s[i].staffId) == 0) {
				found = 1;
				printf("\n % -8s % -10s % -9s % -7s % -17s % -13s % -9s\n",
					s[i].staffId, s[i].name, s[i].position, s[i].password, s[i].pwdRecovery, s[i].contact.phone, s[i].contact.email);

				printf("\nCurrent Password|%s|", s[i].password);
				printf("\nUpdate password:");
				scanf("%s", &updPass);

				printf("\nCurrent Password Recovery|%s|", s[i].pwdRecovery);
				printf("\nUpdate password recovery:");
				rewind(stdin);
				scanf(" %[^\n]", pwdRecovery);

				printf("Confirm to Modify (y=yes)? :");
				rewind(stdin);
				scanf(" %c", &ans);

				if (toupper(ans) == 'Y') {
					strcpy(s[i].password, updPass);
					strcpy(s[i].pwdRecovery, pwdRecovery);
					modiCount++;
				}
				printf("\n\n");
				printf("Updated record:\n");
				printf("\nStaff ID Name        Position Password Password Recovery   Contact     Email");
				printf("\n======== =========== ======== ======== ================= ============  ==========");
				printf("\n % -8s % -10s % -9s % -7s % -17s % -13s % -9s\n",
					s[i].staffId, s[i].name, s[i].position, s[i].password, s[i].pwdRecovery, s[i].contact.phone, s[i].contact.email);
			}
		}
		if (!found)
			printf("\nNo staff found with code = %s\n", staffId);

		printf("\nAny more record to modify (y=yes)?:");
		rewind(stdin);
		scanf(" %c", &cont);

	} while (toupper(cont) == 'Y');

	fp = fopen("staff.bin", "wb");
	if (fp == NULL) {
		printf("Error opening file!");
		return;
	}

	for (i = 0; i < sCount; i++)
		fwrite(&s[i], sizeof(STAFF), 1, fp);

	fclose(fp);
	printf("\n\t%d Record(s) modified\n\n", modiCount);
}

void StaffStatistics() {
	printf("\n");
	printf("\t************\n");
	printf("\t\tSTAFF STATISTICS\n");
	printf("\t************\n");

	FILE* fp;
	STAFF tempStaff;
	int count = 0, totalYearsOfService = 0;

	fp = fopen("staff.bin", "rb");
	if (fp == NULL) {
		printf("Error opening file...");
		return;
	}

	while (fread(&tempStaff, sizeof(STAFF), 1, fp) == 1) {
		count++;
		totalYearsOfService += tempStaff.yearsOfService;
	}

	fclose(fp);

	if (count == 0) {
		printf("\n");
		printf("No staff found\n");
		return;
	}
	printf("\n");
	printf("\tTotal staff: %d\n", count);
	printf("\tTotal years of service: %d\n", totalYearsOfService);
	printf("\n");
}