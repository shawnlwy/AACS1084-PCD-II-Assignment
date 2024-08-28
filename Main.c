#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)

#include"Staff_Information.h"
#include"Member_Information.h"
#include"Train_Schedule.h"
#include"Ticket_Booking.h"

void main()
{
	int choice, typeCheck;

	do {
		// Display Menu
		printf("======================================\n");
		printf("\tTrain Ticketing System\n");
		printf("======================================\n");
		printf("[1] Staff Information\n");
		printf("[2] Member Information\n");
		printf("[3] Train Scheduling\n");
		printf("[4] Ticket Booking\n");
		printf("[5] Exit\n");
		printf("=====================================\n");
		printf("Enter the Number of Your Choice: ");

		// Input Validation & Function Calling
		do {
			rewind(stdin);
			typeCheck = scanf("%d", &choice);

			switch (choice)
			{
			case 1:system("cls");staffMenu();break;
			case 2:system("cls");memberMenu();break;
			case 3:system("cls");scheduleMenu();break;
			case 4:system("cls");bookingMenu();break;
			case 5:printf("\nThanks for Coming.\n");break;
			default: // Check for Error Type
				if (typeCheck)
					printf("Invalid. Please enter number between 1-5 : ");
				else
					printf("This is not a number. Please enter again : ");
			}
		} while (choice < 1 || choice > 5);
	} while (choice != 5);

	exit(-1);
}