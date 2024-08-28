#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#define MAX_SCHEDULES 500
#pragma warning (disable : 4996)

struct Time {

    int hours;
    int minutes;

};

struct TrainSchedule {

    char trainID[5];
    struct Time departureTime;
    struct Time arrivalTime;
    char departureStation[50];
    char destinationStation[50];
    char link[100];
    int seatcapacity;
    double price;

};

void main();
void scheduleMenu();
void view(struct TrainSchedule schedule);
void search(struct TrainSchedule schedule);
void add(struct TrainSchedule schedule);
void modify(struct TrainSchedule schedule);
void delete(struct TrainSchedule schedule);
void report(struct TrainSchedule schedule);


void scheduleMenu() {

    system("cls");

    int option;
    struct TrainSchedule schedule = { 0 };

    do {
        printf("\n\n          -----------------------------------------Train Scheduling----------------------------------------------\n\n");
        printf("                                                 1 - > View Schedule\n");
        printf("                                                 2 - > Search Schedules\n");
        printf("                                                 3 - > Add Schedule\n");
        printf("                                                 4 - > Modify Schedule\n");
        printf("                                                 5 - > Delete Schedule\n");
        printf("                                                 6 - > Report of Schedule\n");
        printf("                                                 7 - > Back to Main Menu\n");
        printf("                                                 8 - > Exit\n\n");
        printf("                                                 => ");
        scanf("%d", &option);

        switch (option)
        {
        case  1:view(schedule); break;
        case  2:search(schedule); break;
        case  3:add(schedule); break;
        case  4:modify(schedule); break;
        case  5:delete(schedule); break;
        case  6:report(schedule); break;
        case  7:system("cls");main();break;
        case  8: break;
        default:
            printf("Invalid option.....\n");
            system("pause");
            system("cls");
            break;
        }
    } while (option != 7 && option != 8);

    system("pause");
    system("cls");

}

void view(struct TrainSchedule schedule) {

    system("cls");

    FILE* views;
    views = fopen("trainSchedule.txt", "r");

    char space = 0;

    if (views == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("\n\n%-13s %-17s %-17s %-20s %-21s %-35s %-16s %s\n", "Train ID", "Departure Time", "Arrival Time", "Departure Station", "Destination Station", "Transfer Link", "Seat Capacity", "Price(RM)");
    printf("===========================================================================================================================================================\n\n");

    while (fscanf(views, "%[^|]|%02d|%02d|%02d|%02d|%[^|]|%[^|]|%[^|]|%d|%lf\n", schedule.trainID, &schedule.departureTime.hours, &schedule.departureTime.minutes, &schedule.arrivalTime.hours, &schedule.arrivalTime.minutes, schedule.departureStation, schedule.destinationStation, schedule.link, &schedule.seatcapacity, &schedule.price) == 10)
    {
        printf("%-13s %02d:%02d             %02d:%02d             %-20s %-21s %-35s %-16d %.2lf\n",
            schedule.trainID,
            schedule.departureTime.hours, schedule.departureTime.minutes,
            schedule.arrivalTime.hours, schedule.arrivalTime.minutes,
            schedule.departureStation,
            schedule.destinationStation,
            schedule.link,
            schedule.seatcapacity,
            schedule.price);

    }



    fclose(views);
    system("pause");
    system("cls");

}

void search(struct TrainSchedule schedule) {

    system("cls");

    FILE* searchs;
    searchs = fopen("trainSchedule.txt", "r");

    if (searchs == NULL) {
        printf("Error opening file");
        return -1;
    }


    char station[50];
    int found = 0;

    view(schedule);

    printf("\n\nEnter the station to search > ");
    scanf(" %[^\n]", station);

    while (fscanf(searchs, "%[^|]|%d|%d|%d|%d|%[^|]|%[^|]|%[^|]|%d|%lf\n", schedule.trainID, &schedule.departureTime.hours, &schedule.departureTime.minutes, &schedule.arrivalTime.hours, &schedule.arrivalTime.minutes, schedule.departureStation, schedule.destinationStation, schedule.link, &schedule.seatcapacity, &schedule.price) == 10)
    {
        if (strcmp(schedule.departureStation, station) == 0) {
            printf("\n\n");
            printf("Train ID            : %s\n", schedule.trainID);
            printf("Departure Time      : %02d:%02d\n", schedule.departureTime.hours, schedule.departureTime.minutes);
            printf("Arrival Time        : %02d:%02d\n", schedule.arrivalTime.hours, schedule.arrivalTime.minutes);
            printf("Departure Station   : %s\n", schedule.departureStation);
            printf("Destination Station : %s\n", schedule.destinationStation);
            printf("Transfer Link       : %s\n", schedule.link);
            printf("Seat Capacity       : %d\n", schedule.seatcapacity);
            printf("Price (RM)          : %.2lf\n", schedule.price);
            printf("\n\n");
            found = 1;
        }


    }

    if (found == 0) {
        printf("\n--------------------------------------------------Record not existing--------------------------------------------------\n\n");
    }

    fclose(searchs);
    system("pause");
    system("cls");
}

void add(struct TrainSchedule schedule) {

    system("cls");

    FILE* adds;
    adds = fopen("trainSchedule.txt", "a");

    if (adds == NULL) {
        printf("Error opening file");
        return;
    }

    char sure;
    int trainschedule = 0;

    while (1) {
        do {
            printf("\n\nEnter Train ID (Exit to stop): ");
            scanf("%s", schedule.trainID);

            // Check if the length of trainID is not equal to 4
            if (strlen(schedule.trainID) != 4) {
                printf("Train ID must contain exactly 4 characters.\n");
                continue;
            }
            break;

        } while (1);

        if (strcmp(schedule.trainID, "Exit") == 0) {
            break;
        }


        while (1) {
            printf("Enter Departure Time (hh:mm): ");
            scanf("%d:%d", &schedule.departureTime.hours, &schedule.departureTime.minutes);
            rewind(stdin);

            if (schedule.departureTime.hours < 0 || schedule.departureTime.hours > 23) {
                printf("Error: Departure time (hour) should be between 0 and 23.\n");
                continue; // Skip the rest of the loop and ask for input again
            }

            // Check if minutes are within the valid range (0-59)
            if (schedule.departureTime.minutes < 0 || schedule.departureTime.minutes > 59) {
                printf("Error: Departure time (minutes) should be between 0 and 59.\n");
                continue; // Skip the rest of the loop and ask for input again
            }

            break;
        }

        while (1) {
            printf("Enter Arrival Time (hh:mm): ");
            scanf("%d:%d", &schedule.arrivalTime.hours, &schedule.arrivalTime.minutes);
            rewind(stdin);

            if (schedule.arrivalTime.hours < 0 || schedule.arrivalTime.hours > 23) {
                printf("Error: Arrival time (hour) should be between 0 and 23.\n");
                continue; // Skip the rest of the loop and ask for input again
            }

            // Check if minutes are within the valid range (0-59)
            if (schedule.arrivalTime.minutes < 0 || schedule.arrivalTime.minutes > 59) {
                printf("Error: Arrival time (minutes) should be between 0 and 59.\n");
                continue; // Skip the rest of the loop and ask for input again
            }
            break;
        }

        printf("Enter Departure Station: ");
        scanf(" %[^\n]", schedule.departureStation);
        rewind(stdin);
        printf("Enter Destination Station: ");
        scanf(" %[^\n]", schedule.destinationStation);
        rewind(stdin);
        printf("Enter Transfer Link: ");
        rewind(stdin);

        int index = 0;
        while (1) {
            int ch = getchar();

            // Check for whitespace or newline character
            if (ch == ' ' || ch == '\n') {
                // If link is empty, set it to an empty string
                if (index == 0)
                    strcpy(schedule.link, "");
                else
                    schedule.link[index] = '\0'; // Terminate the string
                break;
            }
        }


        printf("Enter Seat Capacity: ");
        scanf("%d", &schedule.seatcapacity);
        rewind(stdin);
        printf("Enter Price(RM): ");
        rewind(stdin);
        scanf("%lf", &schedule.price);
        rewind(stdin);

        printf("Sure add into Train Schedule (y = yes || n = no) :");
        scanf(" %c", &sure);
        rewind(stdin);

        if (toupper(sure) == 'Y') {
            fprintf(adds, "%s|%02d|%02d|%02d|%02d|%s|%s|%s|%d|%.2lf\n", schedule.trainID, schedule.departureTime.hours, schedule.departureTime.minutes, schedule.arrivalTime.hours, schedule.arrivalTime.minutes, schedule.departureStation, schedule.destinationStation, schedule.link, schedule.seatcapacity, schedule.price);
            printf("\n\nSuccessfully Recorded.....\n\n");
            printf("Train ID            : %s\n", schedule.trainID);
            printf("Departure Time      : %02d:%02d\n", schedule.departureTime.hours, schedule.departureTime.minutes);
            printf("Arrival Time        : %02d:%02d\n", schedule.arrivalTime.hours, schedule.arrivalTime.minutes);
            printf("Departure Station   : %s\n", schedule.departureStation);
            printf("Destination Station : %s\n", schedule.destinationStation);
            printf("Transfer Link       : %s\n", schedule.link);
            printf("Seat Capacity       : %d\n", schedule.seatcapacity);
            printf("Price(RM)           : %.2lf\n\n", schedule.price);
            system("pause");
            system("cls");
            trainschedule++;
        }
        else
        {
            printf("Canceled adding\n");
            system("pause");
            system("cls");
            return;
        }
    }



    fclose(adds);
    int totalSchedules = 0;

    FILE* file = fopen("trainSchedule.txt", "r");

    if (file != NULL) {

        int c;

        while ((c = fgetc(file)) != EOF) {
            if (c == '\n') {
                totalSchedules++;
            }
        }
        fclose(file);
    }
    else {
        printf("Error opening file for counting schedules\n");
    }

    printf("\n\n\nTotal %d schedules recorded...\n", totalSchedules);

    system("pause");
    system("cls");
}

void modify(struct TrainSchedule schedule) {

    system("cls");

    FILE* modifys;

    struct TrainSchedule p[100];
    char ID[10];
    char newtrainID[10], newdepartureStation[25], newdestinationStation[25], newlink[35];
    int newDepartureTime_hours, newDepartureTime_minutes, newArrivalTime_hours, newArrivalTime_minutes, newseatcapacity;
    double newprice = 0;
    char sure;


    modifys = fopen("trainSchedule.txt", "r+");
    if (modifys == NULL) {
        printf("Error opening file\n");
        return;
    }

    int pCount = 0;
    int found = 0;

    // Read data from the file into the array of TrainSchedule structures
    while (fscanf(modifys, "%[^|]|%d|%d|%d|%d|%[^|]|%[^|]|%[^|]|%d|%lf\n", p[pCount].trainID, &p[pCount].departureTime.hours, &p[pCount].departureTime.minutes, &p[pCount].arrivalTime.hours, &p[pCount].arrivalTime.minutes, p[pCount].departureStation, p[pCount].destinationStation, p[pCount].link, &p[pCount].seatcapacity, &p[pCount].price) == 10) {
        pCount++;
    }

    fclose(modifys);

    view(schedule);


    printf("\n\nEnter Train ID to Modify : ");
    scanf("%s", ID);


    for (int i = 0; i < pCount; i++) {
        if (strcmp(p[i].trainID, ID) == 0) {
            found = 1;

            system("cls");

            printf("\n\nExisting Record >\t\t\t\t\t\t");

            printf("\nTrain ID            : %s", p[i].trainID);
            printf("\nDeparture Time      : %02d:%02d", p[i].departureTime.hours, p[i].departureTime.minutes);
            printf("\nArrival Time        : %02d:%02d", p[i].arrivalTime.hours, p[i].arrivalTime.minutes);
            printf("\nDeparture Station   : %s", p[i].departureStation);
            printf("\nDestination Station : %s", p[i].destinationStation);
            printf("\nTransfer Link       : %s", p[i].link);
            printf("\nSeat Capacity       : %d", p[i].seatcapacity);
            printf("\nPrice (RM)          : %1.2lf", p[i].price);
            rewind(stdin);

            printf("\n\nUpdated New Record >\n");
            do {
                printf("\n\nEnter New Train ID               : ");
                scanf("%s", newtrainID);

                // Check if the length of trainID is not equal to 4
                if (strlen(newtrainID) != 4) {
                    printf("Train ID must contain exactly 4 characters.\n");
                    continue;
                }
                break;

            } while (1);

            while (1) {
                printf("Enter new Departure Time (hh:mm) : ");
                scanf("%d:%d", &newDepartureTime_hours, &newDepartureTime_minutes);

                if (newDepartureTime_hours < 0 || newDepartureTime_hours > 23) {
                    printf("Error: Departure time (hour) should be between 0 and 23.\n");
                    continue; // Skip the rest of the loop and ask for input again
                }

                // Check if minutes are within the valid range (0-59)
                if (newDepartureTime_minutes < 0 || newDepartureTime_minutes > 59) {
                    printf("Error: Departure time (minutes) should be between 0 and 59.\n");
                    continue; // Skip the rest of the loop and ask for input again
                }
                break;
            }

            while (1) {
                printf("Enter new Arrival Time (hh:mm)   : ");
                scanf("%d:%d", &newArrivalTime_hours, &newArrivalTime_minutes);

                if (newArrivalTime_hours < 0 || newArrivalTime_hours > 23) {
                    printf("Error: Arrival time (hour) should be between 0 and 23.\n");
                    continue; // Skip the rest of the loop and ask for input again
                }

                // Check if minutes are within the valid range (0-59)
                if (newArrivalTime_minutes < 0 || newArrivalTime_minutes > 59) {
                    printf("Error: Arrival time (minutes) should be between 0 and 59.\n");
                    continue; // Skip the rest of the loop and ask for input again
                }
                break;
            }

            printf("Enter new Departure Station      : ");
            scanf(" %[^\n]", newdepartureStation);
            rewind(stdin);

            printf("Enter new Destination Station    : ");
            scanf(" %[^\n]", newdestinationStation);
            rewind(stdin);

            printf("Enter new Transfer Link          : ");
            scanf(" %[^\n]", newlink);
            rewind(stdin);

            printf("Enter new Seat Capacity          : ");
            scanf("%d", &newseatcapacity);

            printf("Enter new Price (RM)             : ");
            scanf("%lf", &newprice);


            printf("\n\nSure to modify (Y = yes) OR Press any character to Cancel > ");
            scanf(" %c", &sure);


            if (toupper(sure) == 'Y') {

                strcpy(p[i].trainID, newtrainID);
                p[i].departureTime.hours = newDepartureTime_hours;
                p[i].departureTime.minutes = newDepartureTime_minutes;
                p[i].arrivalTime.hours = newArrivalTime_hours;
                p[i].arrivalTime.minutes = newArrivalTime_minutes;
                strcpy(p[i].departureStation, newdepartureStation);
                strcpy(p[i].destinationStation, newdestinationStation);
                strcpy(p[i].link, newlink);
                p[i].seatcapacity = newseatcapacity;
                p[i].price = newprice;

                system("cls");
                printf("Record Updated\n");
                printf("\n\nNew Record >\n\n");
                printf("Train ID            : %s\n", newtrainID);
                printf("Departure Time      : %02d:%02d\n", newDepartureTime_hours, newDepartureTime_minutes);
                printf("Arrival Time        : %02d:%02d\n", newArrivalTime_hours, newArrivalTime_minutes);
                printf("Departure Station   : %s\n", newdepartureStation);
                printf("Destination Station : %s\n", newdestinationStation);
                printf("Transfer Link       : %s\n", newlink);
                printf("Seat Capacity       : %d\n", newseatcapacity);
                printf("Price (RM)          : %.2lf\n", newprice);
            }
            else {
                printf("Modification canceled.\n");
            }

            break;
        }
    }

    if (!found) {
        printf("Train ID not found\n");
        system("pause");
        system("cls");
        return;
    }

    // Open the file again to overwrite the modified records
    modifys = fopen("trainSchedule.txt", "w");

    if (modifys == NULL) {
        printf("Error opening file\n");
        exit(-1);
    }

    // Write the modified records to the file
    for (int i = 0; i < pCount; i++) {
        fprintf(modifys, "%s|%d|%d|%d|%d|%s|%s|%s|%d|%lf\n", p[i].trainID, p[i].departureTime.hours, p[i].departureTime.minutes, p[i].arrivalTime.hours, p[i].arrivalTime.minutes, p[i].departureStation, p[i].destinationStation, p[i].link, p[i].seatcapacity, p[i].price);
    }

    fclose(modifys);

    system("pause");
    system("cls");
}

void delete(struct TrainSchedule schedule) {

    system("cls");

    FILE* deletes;
    FILE* temp;
    deletes = fopen("trainSchedule.txt", "r");
    temp = fopen("temp.txt", "w");

    if (deletes == NULL || temp == NULL) {
        printf("Error opening file\n");
        return;
    }

    char ID[10];
    int found = 0;

    view(schedule);

    printf("\n\nEnter Train ID to Delete : ");
    scanf("%s", ID);

    while (fscanf(deletes, "%[^|]|%d|%d|%d|%d|%[^|]|%[^|]|%[^|]|%d|%lf\n", schedule.trainID, &schedule.departureTime.hours, &schedule.departureTime.minutes, &schedule.arrivalTime.hours, &schedule.arrivalTime.minutes, schedule.departureStation, schedule.destinationStation, schedule.link, &schedule.seatcapacity, &schedule.price) == 10)
    {
        if (strcmp(schedule.trainID, ID) == 0) {
            found = 1;
            printf("Schedule with Train ID \"%s\" deleted successfully.\n", ID);
        }
        else {
            fprintf(temp, "%s|%d|%d|%d|%d|%s|%s|%s|%d|%lf\n", schedule.trainID, schedule.departureTime.hours, schedule.departureTime.minutes, schedule.arrivalTime.hours, schedule.arrivalTime.minutes, schedule.departureStation, schedule.destinationStation, schedule.link, schedule.seatcapacity, schedule.price);
        }
    }

    fclose(deletes);
    fclose(temp);

    remove("trainSchedule.txt");
    rename("temp.txt", "trainSchedule.txt");

    if (!found) {
        printf("Train ID not found\n");
    }

    system("pause");
    system("cls");

}

void report() {
    system("cls");

    FILE* file = fopen("trainSchedule.txt", "r");

    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    int scheduleCountPerHour[24] = { 0 }; // Array to store count of schedules per hour

    // Read data from the file and calculate the count of schedules per hour
    int hours, minutes;
    while (fscanf(file, "%[^|]|%d|%d|%*d|%*d|%[^|]|%[^|]|%[^|]|%*d|%*lf\n", &hours, &minutes) == 2) {
        scheduleCountPerHour[hours]++;
    }

    fclose(file);

    // Display the bar chart
    printf("Train Schedule Report (Number of Schedules per Hour)\n");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < 24; i++) {
        printf("%02d:00 - %02d:59 |", i, i);

        // Print '*' for each schedule in the hour
        for (int j = 0; j < scheduleCountPerHour[i]; j++) {
            printf("*");
        }

        // Handle the case where there are no schedules for the hour
        if (scheduleCountPerHour[i] == 0) {
            printf(" No schedules");
        }

        printf("\n");
    }

    system("pause");
    system("cls");
}