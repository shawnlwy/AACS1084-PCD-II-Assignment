#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<string.h>
#include<windows.h>
#pragma warning (disable:4996)

// Structure Declaration - Member Information Module
typedef struct {
	char memberID[11];
	char memberName[40];
	char password[25];
	char passwordRecovery[50];
	char gender;
} PersonalDetail;

struct ContactDetail {
	char ic[15];
	char contactNumber[13];
};

typedef struct {
	PersonalDetail personalInfo;
	struct ContactDetail contactInfo;
} MemberStruct;

// Structure Declaration - Train Scheduling Module
struct ScheduleTime {
	int hours, minutes;
};

struct ScheduleStruct {
	char trainID[5];
	struct ScheduleTime departureTime;
	struct ScheduleTime arrivalTime;
	char departureStation[17];
	char destinationStation[18];
	char link[32];
	int seatCapacity;
	double price;
};

// Structure Declaration - Ticket Booking Module
typedef struct {
	int day, month, year;
} Date;

typedef struct {
	int hrs, mins, secs;
} Time;

struct Payment {
	char method[21];
	Date paymentDate;
	Time paymentTime;
	double amount;
};

typedef struct {
	char bookingID[6];
	char memberBook[11];
	char trainBook[6];
	int seatQty;
	char bookingStatus[10];
	Date bookingDate;
	Time bookingTime;
	Date departureDate;
	struct Payment paymentInfo;
} BookingStruct;

// Function Declaration - Ticket Booking Module
void main();
void bookingMenu();
void bookingAdd();
void bookingDisplay();
void bookingSearch();
void bookingModify();
void bookingCancel();
void bookingReport();

// Function Declaration - Sub Function
int findBookingID(char id[]);
int findMemberID(char id[]);
int findTrainID(char id[]);

int stopCommand(char input[]);
int passwordVerify(char id[], char password[]);
int dateValidation(int day, int month, int year);
int dateFormatCheck(int day, int month, int year);
int checkSeatAvailable(char trainID[], int day, int month, int year);
int enterNumValidation(int maxNum);
int readFromFile(BookingStruct booking[]);
int writeToFile(BookingStruct booking[], int bCount);
double calPayAmount(int qty, char trainID[]);

void displaySchedule();
void displaySelectSchedule(char trainID[]);
void generateBookingID(char bookingID[]);
void displayModify(BookingStruct modify);
void trainBookNo();
void memberBookNo();
void revenueCal();

// Function Definition - Ticket Booking Module
void bookingMenu()
{
	int choice, enterNum;

	// Display Menu
	printf("=================================\n");
	printf("\tTrain Ticket Booking\n");
	printf("=================================\n");
	printf("[1] Reserve Ticket\n");
	printf("[2] Display Ticket Reservation\n");
	printf("[3] Search for Booked Tickets\n");
	printf("[4] Modify Ticket Reservation\n");
	printf("[5] Cancel Ticket Reservation\n");
	printf("[6] Ticket Booking Report\n");
	printf("[7] Back to Main Menu\n");
	printf("[8] Exit\n");
	printf("=================================\n");
	printf("Enter the Number of Your Choice: ");

	// Input Validation & Function Calling
	do {
		rewind(stdin);
		enterNum = scanf("%d", &choice);

		switch (choice)
		{
		case 1:system("cls");bookingAdd();break;
		case 2:system("cls");bookingDisplay();break;
		case 3:system("cls");bookingSearch();break;
		case 4:system("cls");bookingModify();break;
		case 5:system("cls");bookingCancel();break;
		case 6:system("cls");bookingReport();break;
		case 7:system("cls");main();break;
		case 8:printf("\nThanks for Coming.\n");exit(-1);break;
		default: // Check for Error Type
			if (enterNum)
				printf("Invalid. Please enter number between 1-8 : ");
			else
				printf("This is not a number. Please enter again : ");
		}
	} while (choice < 1 || choice > 8);
}

void bookingAdd() {
	SYSTEMTIME t;
	GetLocalTime(&t);
	BookingStruct booking;
	char choice, memberPassword[25];
	int seatAvailable, paymentSelect, enterNum;

	// Enter Member ID & Verification
	printf("==============================\n");
	printf("\tReserve Ticket\n");
	printf("==============================\n");
	printf("Enter Your Member ID: ");
	scanf(" %s", booking.memberBook);
	while (!findMemberID(booking.memberBook) && !stopCommand(booking.memberBook))
	{
		printf("[ Member ID Does Not Exist ] Please enter again / Enter XXX to stop: ");
		scanf(" %s", &booking.memberBook);
	};

	// Enter Password & Verification
	system("cls");
	printf("==============================\n");
	printf("\tReserve Ticket\n");
	printf("==============================\n");
	printf("Enter Your Password: ");
	scanf(" %[^\n]", memberPassword);
	while (!passwordVerify(booking.memberBook, memberPassword) && !stopCommand(memberPassword))
	{
		printf("[ Wrong Password ] Please enter again / Enter XXX to stop: ");
		scanf(" %[^\n]", memberPassword);
	}

	if (passwordVerify(booking.memberBook, memberPassword))
	{
		// Login Successful 
		printf("\nLogin Successful.\n");system("pause");system("cls");

			do {
				// Display Train Schedule
				for (int i = 1; i <= 103; i++)
				{
					printf("=");
				}
				printf("\n%44s Reserve Ticket %43s\n", "", "");
					displaySchedule();

				// Enter Train ID & Verification
				printf("Enter Train ID for Reservation: ");
				scanf(" %s", booking.trainBook);
				while (!findTrainID(booking.trainBook) && !stopCommand(booking.trainBook))
				{
					printf("[ Train ID Does Not Exist ] Please enter again / Enter XXX to stop: ");
					scanf(" %s", &booking.trainBook);
				};

				// Display Schedule Selected
				system("cls");
				for (int i = 1; i <= 103; i++)
				{
					printf("=");
				}
				printf("\n%44s Reserve Ticket %43s\n", "", "");
				displaySelectSchedule(booking.trainBook);

				// Enter Departure Date & Validation
				printf("Enter Departure Date (dd/mm/yyyy): ");
				scanf("%d/%d/%d", &booking.departureDate.day, &booking.departureDate.month, &booking.departureDate.year);
				while (dateValidation(booking.departureDate.day, booking.departureDate.month, booking.departureDate.year) < 0)
				{
					// Display Error Message
					if (dateValidation(booking.departureDate.day, booking.departureDate.month, booking.departureDate.year) == -1)
						printf("Date already passed. Please enter again: ");
					else
						printf("Invalid date format. Please enter again: ");
					rewind(stdin);
					scanf("%d/%d/%d", &booking.departureDate.day, &booking.departureDate.month, &booking.departureDate.year);
				}

				// Display Schedule Selected & Departure Date
				system("cls");
				for (int i = 1; i <= 103; i++)
				{
					printf("=");
				}
				printf("\n%44s Reserve Ticket %43s\n", "", "");
				displaySelectSchedule(booking.trainBook);
				printf("Departure Date: %02d/%02d/%d\n", booking.departureDate.day, booking.departureDate.month, booking.departureDate.year);
				printf("--------------------------\n");

				// Enter Seat Quantity & Verification
				seatAvailable = checkSeatAvailable(booking.trainBook, booking.departureDate.day, booking.departureDate.month, booking.departureDate.year);
				printf("Enter Quantity of Ticket (Now Available: %d): ", seatAvailable);
				booking.seatQty = enterNumValidation(seatAvailable);
				booking.paymentInfo.amount = calPayAmount(booking.seatQty, booking.trainBook);

				// Confirm Booking
				system("cls");
				for (int i = 1; i <= 103; i++)
				{
					printf("=");
				}
				printf("\n%44s Reserve Ticket %43s\n", "", "");
				displaySelectSchedule(booking.trainBook);
				printf("Departure Date: %02d/%02d/%d\n", booking.departureDate.day, booking.departureDate.month, booking.departureDate.year);
				printf("Seat Quantity : %d\n", booking.seatQty);
				printf("Total Amount  : RM %.02lf\n", booking.paymentInfo.amount);
				printf("--------------------------\n");
				printf("Confirm Booking (Y=Yes)? : ");
				scanf(" %c", &choice);

				if (toupper(choice) == 'Y')
				{
					// Store Booking Info
					generateBookingID(booking.bookingID);
					booking.bookingDate.day = t.wDay;
					booking.bookingDate.month = t.wMonth;
					booking.bookingDate.year = t.wYear;
					booking.bookingTime.hrs = t.wHour;
					booking.bookingTime.mins = t.wMinute;
					booking.bookingTime.secs = t.wSecond;

					// Payment Info
					system("cls");
					for (int i = 1; i <= 103; i++)
					{
						printf("=");
					}
					printf("\n%44s Reserve Ticket %43s\n", "", "");
					displaySelectSchedule(booking.trainBook);
					printf("Departure Date: %02d/%02d/%d\n", booking.departureDate.day, booking.departureDate.month, booking.departureDate.year);
					printf("Seat Quantity : %d\n", booking.seatQty);
					printf("Total Amount  : RM %.02lf\n", booking.paymentInfo.amount);
					printf("--------------------------\n");
					printf("[ Payment Method ]\n");
					printf("1. Credit Card\n");
					printf("2. Debit Card\n");
					printf("3. E-Wallet\n");
					printf("Select Your Payment Method: ");
					paymentSelect = enterNumValidation(3);

					printf("\nPayment Processing");Sleep(400);printf(".");Sleep(400);printf(".");Sleep(400);printf(".");

					// Store Payment Info
					switch (paymentSelect)
					{
					case 1: strcpy(booking.paymentInfo.method, "Credit Card");break;
					case 2: strcpy(booking.paymentInfo.method, "Debit Card");break;
					default: strcpy(booking.paymentInfo.method, "E-Wallet");break;
					}
					strcpy(booking.bookingStatus, "Booked");
					booking.paymentInfo.paymentDate.day = t.wDay;
					booking.paymentInfo.paymentDate.month = t.wMonth;
					booking.paymentInfo.paymentDate.year = t.wYear;
					booking.paymentInfo.paymentTime.hrs = t.wHour;
					booking.paymentInfo.paymentTime.mins = t.wMinute;
					booking.paymentInfo.paymentTime.secs = t.wSecond;

					// Add into File
					FILE* bookingFile = fopen("ticketBooking.txt", "a");
					if (bookingFile == NULL)
					{
						system("cls");
						printf("\aSomething wrong...Please restart the system.\n");
						exit(-1);
					}
					fprintf(bookingFile, "%s|%s|%s|%d|%s|%02d/%02d/%d|%02d:%02d:%02d|%02d/%02d/%d|%s|%02d/%02d/%d|%02d:%02d:%02d|%.02lf\n",
						booking.bookingID, booking.memberBook, booking.trainBook, booking.seatQty, booking.bookingStatus,
						booking.bookingDate.day, booking.bookingDate.month, booking.bookingDate.year,
						booking.bookingTime.hrs, booking.bookingTime.mins, booking.bookingTime.secs,
						booking.departureDate.day, booking.departureDate.month, booking.departureDate.year,
						booking.paymentInfo.method,
						booking.paymentInfo.paymentDate.day, booking.paymentInfo.paymentDate.month, booking.paymentInfo.paymentDate.year,
						booking.paymentInfo.paymentTime.hrs, booking.paymentInfo.paymentTime.mins, booking.paymentInfo.paymentTime.secs,
						booking.paymentInfo.amount);
					fclose(bookingFile);

					// Display Receipt
					system("cls");
					printf("========================================\n");
					printf("\t\tReceipt\n");
					printf("========================================\n");
					printf("Booking ID		: %s\n", booking.bookingID);
					printf("Member ID		: %s\n", booking.memberBook);
					printf("Train ID		: %s\n", booking.trainBook);
					printf("Seat Quantity		: %d\n", booking.seatQty);
					printf("Booking Date		: %02d/%02d/%d\n", booking.bookingDate.day, booking.bookingDate.month, booking.bookingDate.year);
					printf("Departure Date		: %02d/%02d/%d\n", booking.departureDate.day, booking.departureDate.month, booking.departureDate.year);
					printf("Payment Amount		: RM %.02lf\n", booking.paymentInfo.amount);
					printf("Payment Method		: %s\n", booking.paymentInfo.method);
					printf("========================================\n");
					printf("Ticket Reserved.\n");
				}
				// Continue or Back to Menu
				printf("\nReserve for other ticket (Y=Yes)? : ");
				scanf(" %c", &choice);
				system("cls");
			} while (toupper(choice) == 'Y');
	}

	bookingMenu();
}

void bookingDisplay() {
	int count = 0;
	BookingStruct booking;
	FILE* bookingFile = fopen("ticketBooking.txt", "r");
	if (bookingFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	// Display Header
	for (int i = 1; i <= 112; i++)
	{
		printf("=");
	}
	printf("\n%44s Ticket Reservation %45s\n", "", "");
	for (int i = 1; i <= 112; i++)
	{
		printf("=");
	}
	printf("\n| %10s | %10s | %8s | %8s | %12s | %14s | %14s | %11s |\n",
		"Booking ID", "Member ID", "Train ID", "Quantity", "Booking Date", "Departure Date", "Booking Status", "Amount (RM)");
	for (int i = 1; i <= 112; i++)
	{
		printf("=");
	}
	printf("\n");

	// Display Booking
	while (fscanf(bookingFile, " %[^|]|%[^|]|%[^|]|%d|%[^|]|%d/%d/%d|%d:%d:%d|%d/%d/%d|%[^|]|%d/%d/%d|%d:%d:%d|%lf\n",
		booking.bookingID, booking.memberBook, booking.trainBook, &booking.seatQty, booking.bookingStatus,
		&booking.bookingDate.day, &booking.bookingDate.month, &booking.bookingDate.year,
		&booking.bookingTime.hrs, &booking.bookingTime.mins, &booking.bookingTime.secs,
		&booking.departureDate.day, &booking.departureDate.month, &booking.departureDate.year, booking.paymentInfo.method,
		&booking.paymentInfo.paymentDate.day, &booking.paymentInfo.paymentDate.month, &booking.paymentInfo.paymentDate.year,
		&booking.paymentInfo.paymentTime.hrs, &booking.paymentInfo.paymentTime.mins, &booking.paymentInfo.paymentTime.secs,
		&booking.paymentInfo.amount) != EOF)
	{
		count++;
		printf("| %-10s | %-10s | %-8s | %8d | %02d/%02d/%-6d | %02d/%02d/%-8d | %-14s | %11.02lf |\n",
			booking.bookingID, booking.memberBook, booking.trainBook, booking.seatQty, booking.bookingDate.day, booking.bookingDate.month, booking.bookingDate.year, 
			booking.departureDate.day, booking.departureDate.month, booking.departureDate.year, booking.bookingStatus, booking.paymentInfo.amount);
	};
	if (count == 0)
		printf("%112s\n", "");

	// Display Footer
	for (int i = 1; i <= 112; i++)
	{
		printf("=");
	}
	printf("\n%d booking(s) listed.\n\n", count);
	
	fclose(bookingFile);
	system("pause");
	system("cls");
	bookingMenu();
}

void bookingSearch() {
	BookingStruct booking;
	int search;
	char choice, trainID[5], bookingID[6], memberID[11];

	do {
		int count = 0;
		// Display Menu
		printf("=========================================\n");
		printf("\tSearch for Booked Tickets\n");
		printf("=========================================\n");
		printf("1. Search By Booking ID\n");
		printf("2. Search By Member ID\n");
		printf("3. Search By Train ID\n");
		printf("4. Back to Menu\n");
		printf("Enter the Number of Your Choice: ");
		search = enterNumValidation(4);

		if (search <= 3)
		{
			system("cls");
			printf("=========================================\n");
			printf("\tSearch for Booked Tickets\n");
			printf("=========================================\n");
			// Enter ID
			switch (search)
			{
			case 1:
				printf("Enter Booking ID: ");
				scanf(" %s", bookingID);break;
			case 2:
				printf("Enter Member ID	: ");
				scanf(" %s", memberID);break;
			default:
				printf("Enter Train ID	: ");
				scanf(" %s", trainID);
			}

			FILE* bookingFile = fopen("ticketBooking.txt", "r");
			if (bookingFile == NULL)
			{
				system("cls");
				printf("\aSomething wrong...Please restart the system.\n");
				exit(-1);
			}

			// Display Header
			system("cls");
			for (int i = 1; i <= 111; i++)
			{
				printf("=");
			}
			printf("\n%42s Search for Booked Tickets %42s\n", "", "");
			for (int i = 1; i <= 111; i++)
			{
				printf("=");
			}
			switch (search) {
			case 1:printf("\nSearch Criteria: Booking ID - %s\n", bookingID);break;
			case 2:printf("\nSearch Criteria: Member ID - %s\n", memberID);break;
			default:printf("\nSearch Criteria: Train ID - %s\n", trainID);
			}
			for (int i = 1; i <= 111; i++)
			{
				printf("=");
			}
			printf("\n| %10s | %9s | %8s | %8s | %12s | %14s | %14s | %11s |\n",
				"Booking ID", "Member ID", "Train ID", "Quantity", "Booking Date", "Departure Date", "Booking Status", "Amount (RM)");
			for (int i = 1; i <= 111; i++)
			{
				printf("=");
			}
			printf("\n");

			// Display Booking
			switch (search)
			{
			case 1:
				while (fscanf(bookingFile, " %[^|]|%[^|]|%[^|]|%d|%[^|]|%d/%d/%d|%d:%d:%d|%d/%d/%d|%[^|]|%d/%d/%d|%d:%d:%d|%lf\n",
					booking.bookingID, booking.memberBook, booking.trainBook, &booking.seatQty, booking.bookingStatus,
					&booking.bookingDate.day, &booking.bookingDate.month, &booking.bookingDate.year,
					&booking.bookingTime.hrs, &booking.bookingTime.mins, &booking.bookingTime.secs,
					&booking.departureDate.day, &booking.departureDate.month, &booking.departureDate.year, booking.paymentInfo.method,
					&booking.paymentInfo.paymentDate.day, &booking.paymentInfo.paymentDate.month, &booking.paymentInfo.paymentDate.year,
					&booking.paymentInfo.paymentTime.hrs, &booking.paymentInfo.paymentTime.mins, &booking.paymentInfo.paymentTime.secs,
					&booking.paymentInfo.amount) != EOF)
				{
					if (strcmp(booking.bookingID, bookingID) == 0)
					{
						printf("| %-10s | %-9s | %-8s | %8d | %02d/%02d/%-6d | %02d/%02d/%-8d | %-14s | %11.02lf |\n",
							booking.bookingID, booking.memberBook, booking.trainBook, booking.seatQty, booking.bookingDate.day, booking.bookingDate.month, booking.bookingDate.year,
							booking.departureDate.day, booking.departureDate.month, booking.departureDate.year, booking.bookingStatus, booking.paymentInfo.amount);
						count++;
					}
				};
				if (count == 0)
					printf("%111s\n", "");break;
			case 2:
				while (fscanf(bookingFile, " %[^|]|%[^|]|%[^|]|%d|%[^|]|%d/%d/%d|%d:%d:%d|%d/%d/%d|%[^|]|%d/%d/%d|%d:%d:%d|%lf\n",
					booking.bookingID, booking.memberBook, booking.trainBook, &booking.seatQty, booking.bookingStatus,
					&booking.bookingDate.day, &booking.bookingDate.month, &booking.bookingDate.year,
					&booking.bookingTime.hrs, &booking.bookingTime.mins, &booking.bookingTime.secs,
					&booking.departureDate.day, &booking.departureDate.month, &booking.departureDate.year, booking.paymentInfo.method,
					&booking.paymentInfo.paymentDate.day, &booking.paymentInfo.paymentDate.month, &booking.paymentInfo.paymentDate.year,
					&booking.paymentInfo.paymentTime.hrs, &booking.paymentInfo.paymentTime.mins, &booking.paymentInfo.paymentTime.secs,
					&booking.paymentInfo.amount) != EOF)
				{
					if (strcmp(booking.memberBook, memberID) == 0)
					{
						printf("| %-10s | %-9s | %-8s | %8d | %02d/%02d/%-6d | %02d/%02d/%-8d | %-14s | %11.02lf |\n",
							booking.bookingID, booking.memberBook, booking.trainBook, booking.seatQty, booking.bookingDate.day, booking.bookingDate.month, booking.bookingDate.year,
							booking.departureDate.day, booking.departureDate.month, booking.departureDate.year, booking.bookingStatus, booking.paymentInfo.amount);
						count++;
					}
				};
				if (count == 0)
					printf("%111s\n", "");break;
			default:
				while (fscanf(bookingFile, " %[^|]|%[^|]|%[^|]|%d|%[^|]|%d/%d/%d|%d:%d:%d|%d/%d/%d|%[^|]|%d/%d/%d|%d:%d:%d|%lf\n",
					booking.bookingID, booking.memberBook, booking.trainBook, &booking.seatQty, booking.bookingStatus,
					&booking.bookingDate.day, &booking.bookingDate.month, &booking.bookingDate.year,
					&booking.bookingTime.hrs, &booking.bookingTime.mins, &booking.bookingTime.secs,
					&booking.departureDate.day, &booking.departureDate.month, &booking.departureDate.year, booking.paymentInfo.method,
					&booking.paymentInfo.paymentDate.day, &booking.paymentInfo.paymentDate.month, &booking.paymentInfo.paymentDate.year,
					&booking.paymentInfo.paymentTime.hrs, &booking.paymentInfo.paymentTime.mins, &booking.paymentInfo.paymentTime.secs,
					&booking.paymentInfo.amount) != EOF)
				{
					if (strcmp(booking.trainBook, trainID) == 0)
					{
						printf("| %-10s | %-9s | %-8s | %8d | %02d/%02d/%-6d | %02d/%02d/%-8d | %-14s | %11.02lf |\n",
							booking.bookingID, booking.memberBook, booking.trainBook, booking.seatQty, booking.bookingDate.day, booking.bookingDate.month, booking.bookingDate.year,
							booking.departureDate.day, booking.departureDate.month, booking.departureDate.year, booking.bookingStatus, booking.paymentInfo.amount);
						count++;
					}
				};
				if (count == 0)
					printf("%111s\n", "");
			}

			// Display Footer
			for (int i = 1; i <= 111; i++)
			{
				printf("=");
			}
			printf("\n%d booking(s) listed.\n\n", count);

			// Looping
			printf("Search for other ticket reservation (Y=Yes)? : ");
			scanf(" %c", &choice);
			system("cls");
		}
		else
		{
			system("cls");
			break;
		}
	}	while (toupper(choice) == 'Y');

	bookingMenu();
}

void bookingModify() {
	BookingStruct modify;
	BookingStruct booking[100];
	int i, seatAvailable, paymentSelect;
	char choice, memberPassword[25];
	SYSTEMTIME t;
	GetLocalTime(&t);

	do {
		int found = 0, bCount = readFromFile(booking);
		// Display Header
		printf("=========================================\n");
		printf("\tModify Ticket Reservation\n");
		printf("=========================================\n");

		// Enter Booking ID & Verification
		printf("Enter Booking ID: ");
		scanf(" %s", modify.bookingID);
		for (i = 0; i < bCount; i++)
		{
			if (strcmp(modify.bookingID, booking[i].bookingID) == 0)
			{
				modify = booking[i];
				found = 1;
				break;
			}
		}
		while (!found && !stopCommand(modify.bookingID))
		{
			printf("[ Booking ID Does Not Exist ] Please enter again / Enter XXX to Stop: ");
			scanf(" %s", modify.bookingID);
			for (i = 0; i < bCount; i++)
			{
				if (strcmp(modify.bookingID, booking[i].bookingID) == 0)
				{
					modify = booking[i];
					found = 1;
					break;
				}
			}
		}

		if (found)
		{
			displayModify(modify);
			// Enter New Train ID
			printf("Enter New Train ID	: ");
			scanf(" %s", &modify.trainBook);
			while (!findTrainID(modify.trainBook) && !stopCommand(modify.trainBook))
			{
				printf("[ Train ID Does Not Exist ] Please enter again / Enter XXX to stop: ");
				scanf(" %s", &modify.trainBook);
			};

			displayModify(modify);
			// Enter New Departure Date
			printf("Enter New Departure Date (dd/mm/yyyy): ");
			scanf("%d/%d/%d", &modify.departureDate.day, &modify.departureDate.month, &modify.departureDate.year);
			while (dateValidation(modify.departureDate.day, modify.departureDate.month, modify.departureDate.year) < 0)
			{
				// Display Error Message
				if (dateValidation(modify.departureDate.day, modify.departureDate.month, modify.departureDate.year) == -1)
					printf("Date already passed. Please enter again: ");
				else
					printf("Invalid date format. Please enter again: ");
				rewind(stdin);
				scanf("%d/%d/%d", &modify.departureDate.day, &modify.departureDate.month, &modify.departureDate.year);
			};

			displayModify(modify);
			// Enter New Seat Quantity
			seatAvailable = checkSeatAvailable(modify.trainBook, modify.departureDate.day, modify.departureDate.month, modify.departureDate.year);
			printf("Enter Quantity of Ticket (Now Available: %d): ", seatAvailable);
			modify.seatQty = enterNumValidation(seatAvailable);
			modify.paymentInfo.amount = calPayAmount(modify.seatQty, modify.trainBook);

			// Store New Booking Info
			modify.bookingDate.day = t.wDay;
			modify.bookingDate.month = t.wMonth;
			modify.bookingDate.year = t.wYear;
			modify.bookingTime.hrs = t.wHour;
			modify.bookingTime.mins = t.wMinute;
			modify.bookingTime.secs = t.wSecond;

			displayModify(modify);
			// Enter New Payment Method
			printf("[ Payment Method ]\n");
			printf("1. Credit Card\n");
			printf("2. Debit Card\n");
			printf("3. E-Wallet\n");
			printf("Select New Payment Method: ");
			paymentSelect = enterNumValidation(3);

			// Store New Payment Info
			switch (paymentSelect)
			{
			case 1: strcpy(modify.paymentInfo.method, "Credit Card"); break;
			case 2: strcpy(modify.paymentInfo.method, "Debit Card"); break;
			default: strcpy(modify.paymentInfo.method, "E-Wallet"); break;
			}
			modify.paymentInfo.paymentDate.day = t.wDay;
			modify.paymentInfo.paymentDate.month = t.wMonth;
			modify.paymentInfo.paymentDate.year = t.wYear;
			modify.paymentInfo.paymentTime.hrs = t.wHour;
			modify.paymentInfo.paymentTime.mins = t.wMinute;
			modify.paymentInfo.paymentTime.secs = t.wSecond;

			// Confirm Modify
			displayModify(modify);
			printf("Confirm to Modify (Y=Yes)? : ");
			scanf(" %c", &choice);
			if (toupper(choice) == 'Y')
			{
				// Enter Password & Verification
				displayModify(modify);
				printf("Enter Your Password: ");
				scanf(" %[^\n]", memberPassword);
				while (!passwordVerify(modify.memberBook, memberPassword) && !stopCommand(memberPassword))
				{
					printf("[ Wrong Password ] Please enter again / Enter XXX to stop: ");
					scanf(" %[^\n]", memberPassword);
				}

				booking[i] = modify;
				writeToFile(booking, bCount);

				printf("\nModifying");Sleep(400);printf(".");Sleep(400);printf(".");Sleep(400);printf(".");
				displayModify(modify);
				printf("Modication Successful.\n");
			}
			printf("\nModify other ticket reservation (Y=Yes)? : ");
			scanf(" %c", &choice);
			system("cls");
		}
	}	while (toupper(choice) == 'Y');

	bookingMenu();
}

void bookingCancel() {
	char choice, deleteID[6], memberPassword[25];
	BookingStruct booking[100];
	int i, j;
	
	do {
		int found = 0, bCount = readFromFile(booking);
		printf("==========================================\n");
		printf("\tTicket Reservation Cancell\n");
		printf("==========================================\n");

		// Enter Booking ID & Verification
		printf("Enter Booking ID: ");
		scanf(" %s", deleteID);
		for (i = 0; i < bCount; i++)
		{
			if (strcmp(deleteID, booking[i].bookingID) == 0)
			{
				found = 1;
				break;
			}
		}
		while (!found && !stopCommand(deleteID))
		{
			printf("[ Booking ID Does Not Exist ] Please enter again / Enter XXX to Stop: ");
			scanf(" %s", deleteID);
			for (i = 0; i < bCount; i++)
			{
				if (strcmp(deleteID, booking[i].bookingID) == 0)
				{
					found = 1;
					break;
				}
			}
		}

		// Display Booking Details
		system("cls");
		printf("==========================================\n");
		printf("\tTicket Reservation Cancell\n");
		printf("==========================================\n");
		printf("Booking ID		: %s\n", booking[i].bookingID);
		printf("Member ID		: %s\n", booking[i].memberBook);
		printf("Train ID		: %s\n", booking[i].trainBook);
		printf("Seat Quantity		: %d\n", booking[i].seatQty);
		printf("Booking Status		: %s\n", booking[i].bookingStatus);
		printf("Booking Date		: %02d/%02d/%d\n", booking[i].bookingDate.day, booking[i].bookingDate.month, booking[i].bookingDate.year);
		printf("Booking Time		: %02d:%02d:%02d\n", booking[i].bookingTime.hrs, booking[i].bookingTime.mins, booking[i].bookingTime.secs);
		printf("Payment Amount		: RM %.02lf\n", booking[i].paymentInfo.amount);
		printf("Payment Method		: %s\n", booking[i].paymentInfo.method);
		printf("Payment Date		: %02d/%02d/%d\n", booking[i].paymentInfo.paymentDate.day, booking[i].paymentInfo.paymentDate.month, booking[i].paymentInfo.paymentDate.year);
		printf("Payment Time		: %02d:%02d:%02d\n", booking[i].paymentInfo.paymentTime.hrs, booking[i].paymentInfo.paymentTime.mins, booking[i].paymentInfo.paymentTime.secs);
		printf("Departure Date		: %02d/%02d/%d\n\n", booking[i].departureDate.day, booking[i].departureDate.month, booking[i].departureDate.year);

		// Confirm for Cancellation
		printf("Confirm to Cancell (Y=Yes)? : ");
		scanf(" %c", &choice);
		if (toupper(choice) == 'Y')
		{
			system("cls");
			printf("==========================================\n");
			printf("\tTicket Reservation Cancell\n");
			printf("==========================================\n");
			printf("Booking ID		: %s\n", booking[i].bookingID);
			printf("Member ID		: %s\n", booking[i].memberBook);
			printf("Train ID		: %s\n", booking[i].trainBook);
			printf("Seat Quantity		: %d\n", booking[i].seatQty);
			printf("Booking Status		: %s\n", booking[i].bookingStatus);
			printf("Booking Date		: %02d/%02d/%d\n", booking[i].bookingDate.day, booking[i].bookingDate.month, booking[i].bookingDate.year);
			printf("Booking Time		: %02d:%02d:%02d\n", booking[i].bookingTime.hrs, booking[i].bookingTime.mins, booking[i].bookingTime.secs);
			printf("Payment Amount		: RM %.02lf\n", booking[i].paymentInfo.amount);
			printf("Payment Method		: %s\n", booking[i].paymentInfo.method);
			printf("Payment Date		: %02d/%02d/%d\n", booking[i].paymentInfo.paymentDate.day, booking[i].paymentInfo.paymentDate.month, booking[i].paymentInfo.paymentDate.year);
			printf("Payment Time		: %02d:%02d:%02d\n", booking[i].paymentInfo.paymentTime.hrs, booking[i].paymentInfo.paymentTime.mins, booking[i].paymentInfo.paymentTime.secs);
			printf("Departure Date		: %02d/%02d/%d\n\n", booking[i].departureDate.day, booking[i].departureDate.month, booking[i].departureDate.year);

			// Enter Password & Verification
			printf("Enter Your Password: ");
			scanf(" %[^\n]", memberPassword);
			while (!passwordVerify(booking[i].memberBook, memberPassword) && !stopCommand(memberPassword))
			{
				printf("[ Wrong Password ] Please enter again / Enter XXX to stop: ");
				scanf(" %[^\n]", memberPassword);
			}

			for (j = i; j < bCount; j++)
			{
				strcpy(booking[j].bookingID, booking[j + 1].bookingID);
			}
			bCount--;
			writeToFile(booking, bCount);
			printf("\nProcessing");Sleep(400);printf(".");Sleep(400);printf(".");Sleep(400);printf(".");

			printf("Cancellation Successful.\n");
		}
		printf("\nCancell other ticket reservation (Y=Yes)? : ");
		scanf(" %c", &choice);
		system("cls");
	} while (toupper(choice) == 'Y');

	bookingMenu();
}

void bookingReport() {
	int report;
	char choice;

	do {
		// Display Menu
		printf("=====================================\n");
		printf("\tTicket Booking Report\n");
		printf("=====================================\n");
		printf("1. Train Booking Number\n");
		printf("2. Member Booking Number\n");
		printf("3. Revenue Calculation\n");
		printf("4. Back to Menu\n");
		printf("Enter the Number of Your Choice: ");
		report = enterNumValidation(4);

		if (report <= 3) // Look for Report
		{
			// Switch Cases
			switch (report)
			{
			case 1: trainBookNo();break;
			case 2: memberBookNo();break;
			default: revenueCal();
			}

			// Looping
			printf("\nSearch for other ticket reservation (Y=Yes)? : ");
			scanf(" %c", &choice);
			system("cls");
		}
		else // Bak to Menu
		{
			system("cls");
			break;
		}
	} while (toupper(choice) == 'Y');

	bookingMenu();
}

// Function Definition - Sub Function
int findBookingID(char id[])
{
	FILE* bookingFile = fopen("ticketBooking.txt", "r");
	if (bookingFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	BookingStruct tmpBInfo;
	while (fscanf(bookingFile, " %[^|]|%[^|]|%[^|]|%d|%[^|]|%d/%d/%d|%d:%d:%d|%d/%d/%d|%[^|]|%d/%d/%d|%d:%d:%d|%lf\n",
		tmpBInfo.bookingID, tmpBInfo.memberBook, tmpBInfo.trainBook, &tmpBInfo.seatQty, tmpBInfo.bookingStatus,
		&tmpBInfo.bookingDate.day, &tmpBInfo.bookingDate.month, &tmpBInfo.bookingDate.year,
		&tmpBInfo.bookingTime.hrs, &tmpBInfo.bookingTime.mins, &tmpBInfo.bookingTime.secs,
		&tmpBInfo.departureDate.day, &tmpBInfo.departureDate.month, &tmpBInfo.departureDate.year, tmpBInfo.paymentInfo.method,
		&tmpBInfo.paymentInfo.paymentDate.day, &tmpBInfo.paymentInfo.paymentDate.month, &tmpBInfo.paymentInfo.paymentDate.year,
		&tmpBInfo.paymentInfo.paymentTime.hrs, &tmpBInfo.paymentInfo.paymentTime.mins, &tmpBInfo.paymentInfo.paymentTime.secs,
		&tmpBInfo.paymentInfo.amount) != EOF)
	{
		if (strcmp(tmpBInfo.bookingID, id) == 0)
		{
			fclose(bookingFile);
			return 1;
		}
	}

	fclose(bookingFile);
	return 0;
}

int findMemberID(char id[])
{
	FILE* memberFile = fopen("member.dat", "rb");
	if (memberFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	MemberStruct tmpMemberInfo;
	while (fread(&tmpMemberInfo, sizeof(MemberStruct), 1, memberFile) != 0)
	{
		if (strcmp(id, tmpMemberInfo.personalInfo.memberID) == 0)
		{
			fclose(memberFile);
			return 1;
		}
	}
	fclose(memberFile);
	return 0;
}

int findTrainID(char id[])
{
	FILE* scheduleFile = fopen("trainSchedule.txt", "r");
	if (scheduleFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	struct ScheduleStruct tmpSchedule;
	while (fscanf(scheduleFile, " %[^|]|%d|%d|%d|%d|%[^|]|%[^|]|%[^|]|%d|%lf",
		tmpSchedule.trainID, &tmpSchedule.departureTime.hours, &tmpSchedule.departureTime.minutes, &tmpSchedule.arrivalTime.hours, &tmpSchedule.arrivalTime.minutes,
		tmpSchedule.departureStation, tmpSchedule.destinationStation, tmpSchedule.link, &tmpSchedule.seatCapacity, &tmpSchedule.price) != EOF)
	{
		if (strcmp(id, tmpSchedule.trainID) == 0)
		{
			fclose(scheduleFile);
			return 1;
		}
	}
	fclose(scheduleFile);
	return 0;
}

int stopCommand(char input[])
{
	if (strcmp(input, "XXX") == 0 || strcmp(input, "xxx") == 0)
	{
		printf("\nGoing Back");Sleep(400);printf(".");Sleep(400);printf(".");Sleep(400);printf(".");
		system("cls");
		bookingMenu();
		return (1);
	}
	else
		return 0;
}

int passwordVerify(char id[], char password[])
{
	FILE* memberFile = fopen("member.dat", "rb");
	if (memberFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	MemberStruct tmpMemberInfo;
	while (fread(&tmpMemberInfo, sizeof(MemberStruct), 1, memberFile) != 0)
	{
		if (strcmp(id, tmpMemberInfo.personalInfo.memberID) == 0 && strcmp(password, tmpMemberInfo.personalInfo.password) == 0)
		{
			fclose(memberFile);
			return 1;
		}
	}
	fclose(memberFile);
	return 0;
}

int dateValidation(int day, int month, int year)
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	int result = 1;
	int currentDay = t.wDay;
	int currentMonth = t.wMonth;
	int currentYear = t.wYear;

	// Compare with Current Date
	if (year < currentYear || (year == currentYear && month < currentMonth) || (year == currentYear && month == currentMonth && day < currentDay))
		result = -1;

	// Date Format Checking
	if (year < 0 || month < 1 || month > 12 || day < 1)
		result = -2;

	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (day > 31)
			result = -2;
		break;
	case 4: case 6: case 9: case 11:
		if (day > 30)
			result = -2;
		break;
	case 2:
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
		{
			if (day > 29)
				result = -2;
		}	else 
		{
			if (day > 28)
				result = -2;
		} break;
	default:result = -2;
	}
	return result;
}

int dateFormatCheck(int day, int month, int year)
{
	int result = 1;

	// Date Format Checking
	if (year < 0 || month < 1 || month > 12 || day < 1)
		result = 0;

	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (day > 31)
			result = 0;
		break;
	case 4: case 6: case 9: case 11:
		if (day > 30)
			result = 0;
		break;
	case 2:
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			if (day > 29)
				result = 0;
		}
		else
		{
			if (day > 28)
				result = 0;
		} break;
	default:result = 0;
	}
	return result;
}

int checkSeatAvailable(char trainID[], int day, int month, int year)
{
	int seatAvailable = 0;

	// Find Seat Capacity
	FILE* scheduleFile = fopen("trainSchedule.txt", "r");
	if (scheduleFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	struct ScheduleStruct tmpSchedule;
	while (fscanf(scheduleFile, " %[^|]|%d|%d|%d|%d|%[^|]|%[^|]|%[^|]|%d|%lf",
		tmpSchedule.trainID, &tmpSchedule.departureTime.hours, &tmpSchedule.departureTime.minutes, &tmpSchedule.arrivalTime.hours, &tmpSchedule.arrivalTime.minutes,
		tmpSchedule.departureStation, tmpSchedule.destinationStation, tmpSchedule.link, &tmpSchedule.seatCapacity, &tmpSchedule.price) != EOF)
	{
		if (strcmp(trainID, tmpSchedule.trainID) == 0)
		{
			seatAvailable = tmpSchedule.seatCapacity;
			break;
		}
	}
	fclose(scheduleFile);

	// Calculate Seat Available
	FILE* bookingFile = fopen("ticketBooking.txt", "r");
	if (bookingFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	BookingStruct tmpBInfo;
	while (fscanf(bookingFile, " %[^|]|%[^|]|%[^|]|%d|%[^|]|%d/%d/%d|%d:%d:%d|%d/%d/%d|%[^|]|%d/%d/%d|%d:%d:%d|%lf",
		tmpBInfo.bookingID, tmpBInfo.memberBook, tmpBInfo.trainBook, &tmpBInfo.seatQty, tmpBInfo.bookingStatus,
		&tmpBInfo.bookingDate.day, &tmpBInfo.bookingDate.month, &tmpBInfo.bookingDate.year,
		&tmpBInfo.bookingTime.hrs, &tmpBInfo.bookingTime.mins, &tmpBInfo.bookingTime.secs,
		&tmpBInfo.departureDate.day, &tmpBInfo.departureDate.month, &tmpBInfo.departureDate.year, tmpBInfo.paymentInfo.method,
		&tmpBInfo.paymentInfo.paymentDate.day, &tmpBInfo.paymentInfo.paymentDate.month, &tmpBInfo.paymentInfo.paymentDate.year,
		&tmpBInfo.paymentInfo.paymentTime.hrs, &tmpBInfo.paymentInfo.paymentTime.mins, &tmpBInfo.paymentInfo.paymentTime.secs,
		&tmpBInfo.paymentInfo.amount) != EOF)
	{
		// If there's booking before
		if (strcmp(trainID, tmpBInfo.trainBook) == 0 && tmpBInfo.departureDate.day == day &&
			tmpBInfo.departureDate.month == month && tmpBInfo.departureDate.year == year)
		{
			seatAvailable -= tmpBInfo.seatQty;
		}
	}

	fclose(bookingFile);
	return seatAvailable;
}

int enterNumValidation(int maxNum)
{
	int input, enterNum;
	enterNum = scanf("%d", &input);
	while (input < 1 || input > maxNum)
	{
		if (enterNum)
			printf("Invalid. Please enter number between 1-%d: ", maxNum);
		else
			printf("This is not a number. Please enter again: ");
		rewind(stdin);
		enterNum = scanf("%d", &input);
	}
	return input;
}

int readFromFile(BookingStruct booking[])
{
	int bCount = 0;

	FILE* bookingFile = fopen("ticketBooking.txt", "r");
	if (bookingFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	while (fscanf(bookingFile, " %[^|]|%[^|]|%[^|]|%d|%[^|]|%d/%d/%d|%d:%d:%d|%d/%d/%d|%[^|]|%d/%d/%d|%d:%d:%d|%lf\n",
		booking[bCount].bookingID, booking[bCount].memberBook, booking[bCount].trainBook,
		&booking[bCount].seatQty, booking[bCount].bookingStatus,
		&booking[bCount].bookingDate.day, &booking[bCount].bookingDate.month, &booking[bCount].bookingDate.year,
		&booking[bCount].bookingTime.hrs, &booking[bCount].bookingTime.mins, &booking[bCount].bookingTime.secs,
		&booking[bCount].departureDate.day, &booking[bCount].departureDate.month, &booking[bCount].departureDate.year,
		booking[bCount].paymentInfo.method,
		&booking[bCount].paymentInfo.paymentDate.day, &booking[bCount].paymentInfo.paymentDate.month, &booking[bCount].paymentInfo.paymentDate.year,
		&booking[bCount].paymentInfo.paymentTime.hrs, &booking[bCount].paymentInfo.paymentTime.mins, &booking[bCount].paymentInfo.paymentTime.secs,
		&booking[bCount].paymentInfo.amount) != EOF)
	{
		bCount++;
	}
	fclose(bookingFile);
	return bCount;
}

int writeToFile(BookingStruct booking[], int bCount)
{
	int i;

	FILE* bookingFile = fopen("ticketBooking.txt", "w");
	if (bookingFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}
	for (i = 0; i < bCount; i++)
	{
		fprintf(bookingFile, "%s|%s|%s|%d|%s|%02d/%02d/%d|%02d:%02d:%02d|%02d/%02d/%d|%s|%02d/%02d/%d|%02d:%02d:%02d|%.02lf\n",
			booking[i].bookingID, booking[i].memberBook, booking[i].trainBook, booking[i].seatQty, booking[i].bookingStatus,
			booking[i].bookingDate.day, booking[i].bookingDate.month, booking[i].bookingDate.year,
			booking[i].bookingTime.hrs, booking[i].bookingTime.mins, booking[i].bookingTime.secs,
			booking[i].departureDate.day, booking[i].departureDate.month, booking[i].departureDate.year,
			booking[i].paymentInfo.method,
			booking[i].paymentInfo.paymentDate.day, booking[i].paymentInfo.paymentDate.month, booking[i].paymentInfo.paymentDate.year,
			booking[i].paymentInfo.paymentTime.hrs, booking[i].paymentInfo.paymentTime.mins, booking[i].paymentInfo.paymentTime.secs,
			booking[i].paymentInfo.amount);
	}
	fclose(bookingFile);
}

double calPayAmount(int qty, char trainID[])
{
	double amount = 0;
	FILE* scheduleFile = fopen("trainSchedule.txt", "r");
	if (scheduleFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	struct ScheduleStruct schedule;
	while (fscanf(scheduleFile, " %[^|]|%d|%d|%d|%d|%[^|]|%[^|]|%[^|]|%d|%lf",
		schedule.trainID, &schedule.departureTime.hours, &schedule.departureTime.minutes, &schedule.arrivalTime.hours, &schedule.arrivalTime.minutes,
		schedule.departureStation, schedule.destinationStation, schedule.link, &schedule.seatCapacity, &schedule.price) != EOF)
	{
		if (strcmp(trainID, schedule.trainID) == 0)
		{
			amount = qty * schedule.price;
		}
	}
	
	fclose(scheduleFile);
	return amount;
}

void displaySchedule()
{
	FILE* scheduleFile = fopen("trainSchedule.txt", "r");
	if (scheduleFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	struct ScheduleStruct schedule;
	int count = 0;

	// Display Header
	for (int i = 1; i <= 103; i++)
	{
		printf("=");
	}
	printf("\n| %8s | %14s | %12s | %-20s | %-20s | %10s |\n",
		"Train ID", "Departure Time", "Arrival Time", "Departure Station", "Destination Station", "Price (RM)");
	for (int i = 1; i <= 103; i++)
	{
		printf("=");
	}
	printf("\n");

	// Display Schedule
	while (fscanf(scheduleFile, " %[^|]|%d|%d|%d|%d|%[^|]|%[^|]|%[^|]|%d|%lf",
		schedule.trainID, &schedule.departureTime.hours, &schedule.departureTime.minutes, &schedule.arrivalTime.hours, &schedule.arrivalTime.minutes,
		schedule.departureStation, schedule.destinationStation, schedule.link, &schedule.seatCapacity, &schedule.price) != EOF)
	{
		printf("| %-8s | %11d:%02d | %9d:%02d | %-20s | %-20s | %10.02lf |\n",
			schedule.trainID, schedule.departureTime.hours, schedule.departureTime.minutes, schedule.arrivalTime.hours, schedule.arrivalTime.minutes,
			schedule.departureStation, schedule.destinationStation, schedule.price);
		count++;
	}

	// Display Footer
	for (int i = 1; i <= 103; i++)
	{
		printf("=");
	}
	printf("\n%d schedule(s) listed.\n\n", count);
	fclose(scheduleFile);
}

void displaySelectSchedule(char trainID[])
{
	FILE* scheduleFile = fopen("trainSchedule.txt", "r");
	if (scheduleFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	struct ScheduleStruct schedule;

	// Display Header
	for (int i = 1; i <= 103; i++)
	{
		printf("=");
	}
	printf("\n| %8s | %14s | %12s | %-20s | %-20s | %10s |\n",
		"Train ID", "Departure Time", "Arrival Time", "Departure Station", "Destination Station", "Price (RM)");
	for (int i = 1; i <= 103; i++)
	{
		printf("=");
	}
	printf("\n");

	// Display Schedule
	while (fscanf(scheduleFile, " %[^|]|%d|%d|%d|%d|%[^|]|%[^|]|%[^|]|%d|%lf",
		schedule.trainID, &schedule.departureTime.hours, &schedule.departureTime.minutes, &schedule.arrivalTime.hours, &schedule.arrivalTime.minutes,
		schedule.departureStation, schedule.destinationStation, schedule.link, &schedule.seatCapacity, &schedule.price) != EOF)
	{
		if (strcmp(trainID, schedule.trainID) == 0)
		{
			printf("| %-8s | %11d:%02d | %9d:%02d | %-20s | %-20s | %10.02lf |\n",
				schedule.trainID, schedule.departureTime.hours, schedule.departureTime.minutes, schedule.arrivalTime.hours, schedule.arrivalTime.minutes,
				schedule.departureStation, schedule.destinationStation, schedule.price);
		}
	}

	// Display Footer
	for (int i = 1; i <= 103; i++)
	{
		printf("=");
	}
	printf("\n\n");
	fclose(scheduleFile);
}

void generateBookingID(char bookingID[])
{
	FILE* bookingFile = fopen("ticketBooking.txt", "r");
	if (bookingFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	// Get Latest Booking ID
	int count = 0;
	BookingStruct tmpBInfo;
	while (fscanf(bookingFile, " %[^|]|%[^|]|%[^|]|%d|%[^|]|%d/%d/%d|%d:%d:%d|%d/%d/%d|%[^|]|%d/%d/%d|%d:%d:%d|%lf\n",
		tmpBInfo.bookingID, tmpBInfo.memberBook, tmpBInfo.trainBook, &tmpBInfo.seatQty, tmpBInfo.bookingStatus,
		&tmpBInfo.bookingDate.day, &tmpBInfo.bookingDate.month, &tmpBInfo.bookingDate.year,
		&tmpBInfo.bookingTime.hrs, &tmpBInfo.bookingTime.mins, &tmpBInfo.bookingTime.secs,
		&tmpBInfo.departureDate.day, &tmpBInfo.departureDate.month, &tmpBInfo.departureDate.year, tmpBInfo.paymentInfo.method,
		&tmpBInfo.paymentInfo.paymentDate.day, &tmpBInfo.paymentInfo.paymentDate.month, &tmpBInfo.paymentInfo.paymentDate.year,
		&tmpBInfo.paymentInfo.paymentTime.hrs, &tmpBInfo.paymentInfo.paymentTime.mins, &tmpBInfo.paymentInfo.paymentTime.secs,
		&tmpBInfo.paymentInfo.amount) != EOF)
	{
		count++;
	}

	// Generate New Booking ID
	char letter;
	int num;
	sscanf(tmpBInfo.bookingID, "%c%d", &letter, &num);
	num++;
	sprintf(tmpBInfo.bookingID, "%c%04d", letter, num);

	strcpy(bookingID, tmpBInfo.bookingID);
	fclose(bookingFile);
}

void displayModify(BookingStruct modify)
{
	// Display Header
	system("cls");
	printf("=========================================\n");
	printf("\tModify Ticket Reservation\n");
	printf("=========================================\n");

	// Display Current Info
	printf("Booking ID		: %s\n", modify.bookingID);
	printf("Member ID		: %s\n", modify.memberBook);
	printf("Train ID		: %s\n", modify.trainBook);
	printf("Seat Quantity		: %d\n", modify.seatQty);
	printf("Booking Date		: %02d/%02d/%d\n", modify.bookingDate.day, modify.bookingDate.month, modify.bookingDate.year);
	printf("Departure Date		: %02d/%02d/%d\n", modify.departureDate.day, modify.departureDate.month, modify.departureDate.year);
	printf("Payment Amount		: RM %.02lf\n", modify.paymentInfo.amount);
	printf("Payment Method		: %s\n\n", modify.paymentInfo.method);
}

void trainBookNo()
{
	int i, count;
	double earnedProfit;
	BookingStruct tmpBInfo;
	struct ScheduleStruct schedule;

	FILE* bookingFile = fopen("ticketBooking.txt", "r");
	FILE* scheduleFile = fopen("trainSchedule.txt", "r");
	if (bookingFile == NULL || scheduleFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	// Display Header
	system("cls");
	for (i = 1; i <= 100; i++)
	{
		printf("=");
	}
	printf("\n%39s Train Booking Number %39s\n", "", "");
	for (i = 1; i <= 100; i++)
	{
		printf("=");
	}
	printf("\n%8s     %14s     %18s\n", "Train ID", "Booking Number", "Earned Profit (RM)");
	for (i = 1; i <= 100; i++)
	{
		printf("=");
	}

	// Display Content
	while (fscanf(scheduleFile, " %[^|]|%d|%d|%d|%d|%[^|]|%[^|]|%[^|]|%d|%lf",
		schedule.trainID, &schedule.departureTime.hours, &schedule.departureTime.minutes, &schedule.arrivalTime.hours, &schedule.arrivalTime.minutes,
		schedule.departureStation, schedule.destinationStation, schedule.link, &schedule.seatCapacity, &schedule.price) != EOF)
	{
		count = 0;
		earnedProfit = 0;
		printf("\n%-8s     ", schedule.trainID);
		rewind(bookingFile);
		while (fscanf(bookingFile, " %[^|]|%[^|]|%[^|]|%d|%[^|]|%d/%d/%d|%d:%d:%d|%d/%d/%d|%[^|]|%d/%d/%d|%d:%d:%d|%lf\n",
			tmpBInfo.bookingID, tmpBInfo.memberBook, tmpBInfo.trainBook, &tmpBInfo.seatQty, tmpBInfo.bookingStatus,
			&tmpBInfo.bookingDate.day, &tmpBInfo.bookingDate.month, &tmpBInfo.bookingDate.year,
			&tmpBInfo.bookingTime.hrs, &tmpBInfo.bookingTime.mins, &tmpBInfo.bookingTime.secs,
			&tmpBInfo.departureDate.day, &tmpBInfo.departureDate.month, &tmpBInfo.departureDate.year, tmpBInfo.paymentInfo.method,
			&tmpBInfo.paymentInfo.paymentDate.day, &tmpBInfo.paymentInfo.paymentDate.month, &tmpBInfo.paymentInfo.paymentDate.year,
			&tmpBInfo.paymentInfo.paymentTime.hrs, &tmpBInfo.paymentInfo.paymentTime.mins, &tmpBInfo.paymentInfo.paymentTime.secs,
			&tmpBInfo.paymentInfo.amount) != EOF)
		{
			if (strcmp(tmpBInfo.trainBook, schedule.trainID) == 0)
			{
				count++;
				earnedProfit += tmpBInfo.paymentInfo.amount;
			}
		}
		printf("%-14d     %-18.2lf     ", count, earnedProfit);
		for (i = 1; i <= count; i++)
		{
			printf("#");
		}
	}

	// Display Footer
	printf("\n");
	for (i = 1; i <= 100; i++)
	{
		printf("=");
	}

	fclose(bookingFile);
	fclose(scheduleFile);
}

void memberBookNo()
{
	int i, count;
	double amount;
	BookingStruct tmpBInfo;
	MemberStruct tmpMemberInfo;

	FILE* bookingFile = fopen("ticketBooking.txt", "r");
	FILE* memberFile = fopen("member.dat", "rb");
	if (bookingFile == NULL || memberFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	// Display Header
	system("cls");
	for (i = 1; i <= 100; i++)
	{
		printf("=");
	}
	printf("\n%39s Member Booking Number %39s\n", "", "");
	for (i = 1; i <= 101; i++)
	{
		printf("=");
	}
	printf("\n%-10s     %14s     %17s\n", "Member ID", "Booking Number", "Total Amount (RM)");
	for (i = 1; i <= 101; i++)
	{
		printf("=");
	}

	// Display Content
	while (fread(&tmpMemberInfo, sizeof(MemberStruct), 1, memberFile) != 0)
	{
		count = 0;
		amount = 0;
		printf("\n%-10s     ",	tmpMemberInfo.personalInfo.memberID);
		rewind(bookingFile);
		while (fscanf(bookingFile, " %[^|]|%[^|]|%[^|]|%d|%[^|]|%d/%d/%d|%d:%d:%d|%d/%d/%d|%[^|]|%d/%d/%d|%d:%d:%d|%lf\n",
			tmpBInfo.bookingID, tmpBInfo.memberBook, tmpBInfo.trainBook, &tmpBInfo.seatQty, tmpBInfo.bookingStatus,
			&tmpBInfo.bookingDate.day, &tmpBInfo.bookingDate.month, &tmpBInfo.bookingDate.year,
			&tmpBInfo.bookingTime.hrs, &tmpBInfo.bookingTime.mins, &tmpBInfo.bookingTime.secs,
			&tmpBInfo.departureDate.day, &tmpBInfo.departureDate.month, &tmpBInfo.departureDate.year, tmpBInfo.paymentInfo.method,
			&tmpBInfo.paymentInfo.paymentDate.day, &tmpBInfo.paymentInfo.paymentDate.month, &tmpBInfo.paymentInfo.paymentDate.year,
			&tmpBInfo.paymentInfo.paymentTime.hrs, &tmpBInfo.paymentInfo.paymentTime.mins, &tmpBInfo.paymentInfo.paymentTime.secs,
			&tmpBInfo.paymentInfo.amount) != EOF)
		{
			if (strcmp(tmpBInfo.memberBook, tmpMemberInfo.personalInfo.memberID) == 0)
			{
				count++;
				amount += tmpBInfo.paymentInfo.amount;
			}
		}
		printf("%-14d     %-17.2lf     ", count, amount);
		for (i = 1; i <= count; i++)
		{
			printf("#");
		}
	}

	// Display Footer
	printf("\n");
	for (i = 1; i <= 101; i++)
	{
		printf("=");
	}

	fclose(bookingFile);
	fclose(memberFile);
}

void revenueCal()
{
	Date startDate;
	Date endDate;
	int count = 0;
	double amount = 0;
	BookingStruct tmpBInfo;
	FILE* bookingFile = fopen("ticketBooking.txt", "r");
	if (bookingFile == NULL)
	{
		system("cls");
		printf("\aSomething wrong...Please restart the system.\n");
		exit(-1);
	}

	system("cls");
	printf("===================================\n");
	printf("\tRevenue Calculation\n");
	printf("===================================\n");
	printf("Enter Start Date (dd/mm/yyyy)	: ");
	scanf("%d/%d/%d", &startDate.day, &startDate.month, &startDate.year);
	while (!dateFormatCheck(startDate.day, startDate.month, startDate.year))
	{
		printf("Invalid Date Format. Please enter again: ");
		scanf("%d/%d/%d", &startDate.day, &startDate.month, &startDate.year);
	}
	printf("Enter End Date (dd/mm/yyyy)	: ");
	scanf("%d/%d/%d", &endDate.day, &endDate.month, &endDate.year);
	while (!dateFormatCheck(endDate.day, endDate.month, endDate.year))
	{
		printf("Invalid Date Format. Please enter again: ");
		scanf("%d/%d/%d", &endDate.day, &endDate.month, &endDate.year);
	}

	while (fscanf(bookingFile, " %[^|]|%[^|]|%[^|]|%d|%[^|]|%d/%d/%d|%d:%d:%d|%d/%d/%d|%[^|]|%d/%d/%d|%d:%d:%d|%lf\n",
		tmpBInfo.bookingID, tmpBInfo.memberBook, tmpBInfo.trainBook, &tmpBInfo.seatQty, tmpBInfo.bookingStatus,
		&tmpBInfo.bookingDate.day, &tmpBInfo.bookingDate.month, &tmpBInfo.bookingDate.year,
		&tmpBInfo.bookingTime.hrs, &tmpBInfo.bookingTime.mins, &tmpBInfo.bookingTime.secs,
		&tmpBInfo.departureDate.day, &tmpBInfo.departureDate.month, &tmpBInfo.departureDate.year, tmpBInfo.paymentInfo.method,
		&tmpBInfo.paymentInfo.paymentDate.day, &tmpBInfo.paymentInfo.paymentDate.month, &tmpBInfo.paymentInfo.paymentDate.year,
		&tmpBInfo.paymentInfo.paymentTime.hrs, &tmpBInfo.paymentInfo.paymentTime.mins, &tmpBInfo.paymentInfo.paymentTime.secs,
		&tmpBInfo.paymentInfo.amount) != EOF)
	{
		if ((tmpBInfo.bookingDate.year > startDate.year || (tmpBInfo.bookingDate.year == startDate.year && tmpBInfo.bookingDate.month > startDate.month) ||
			(tmpBInfo.bookingDate.year == startDate.year && tmpBInfo.bookingDate.month == startDate.month && tmpBInfo.bookingDate.day >= startDate.day)) &&
			(tmpBInfo.bookingDate.year < endDate.year || (tmpBInfo.bookingDate.year == endDate.year && tmpBInfo.bookingDate.month < endDate.month) ||
				(tmpBInfo.bookingDate.year == endDate.year && tmpBInfo.bookingDate.month == endDate.month && tmpBInfo.bookingDate.day <= endDate.day)))
		{
			count++;
			amount += tmpBInfo.paymentInfo.amount;
		}
	}

	// Display Information
	system("cls");
	printf("===================================\n");
	printf("\tRevenue Calculation\n");
	printf("===================================\n");
	printf("Start Date		: %02d/%02d/%d\n", startDate.day, startDate.month, startDate.year);
	printf("End Date		: %02d/%02d/%d\n", endDate.day, endDate.month, endDate.year);
	printf("Booking Number		: %d\n", count);
	printf("Total Revenue		: RM %.2lf\n", amount);

	fclose(bookingFile);
}