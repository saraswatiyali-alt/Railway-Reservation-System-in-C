
#include <stdio.h>
#include <string.h>

#define MAX 100
#define FARE 250

struct Ticket {
    int ticketNo;
    char name[50];
    int age;
    char source[30];
    char destination[30];
    int seats;
    float amount;
};

struct Ticket t[MAX];
int totalTickets = 0;
int nextTicket = 1001;

// Function declarations
void bookTicket();
void displayTickets();
void searchTicket();
void cancelTicket();
void calculateFare();
void availableSeats();
void showRevenue();
void sortTickets();
void saveTickets();
void loadTickets();

// Book railway ticket
void bookTicket() {
    int i, seats;

    if (totalTickets >= MAX) {
        printf("\nReservation limit reached!\n");
        return;
    }

    printf("\nEnter Passenger Name: ");
    scanf(" %49[^\n]", t[totalTickets].name);

    printf("Enter Passenger Age: ");
    scanf("%d", &t[totalTickets].age);

    printf("Enter Source Station: ");
    scanf(" %29[^\n]", t[totalTickets].source);

    printf("Enter Destination Station: ");
    scanf(" %29[^\n]", t[totalTickets].destination);

    printf("Enter Number of Seats: ");
    scanf("%d", &seats);

    if (seats <= 0 || seats > 6) {
        printf("\nYou can book between 1 and 6 seats!\n");
        return;
    }

    t[totalTickets].ticketNo = nextTicket++;
    t[totalTickets].seats = seats;
    t[totalTickets].amount = seats * FARE;

    printf("\n========== BOOKING CONFIRMED ==========\n");
    printf("Ticket Number : %d\n",
           t[totalTickets].ticketNo);
    printf("Passenger     : %s\n",
           t[totalTickets].name);
    printf("Source        : %s\n",
           t[totalTickets].source);
    printf("Destination   : %s\n",
           t[totalTickets].destination);
    printf("Seats         : %d\n",
           t[totalTickets].seats);
    printf("Total Fare    : Rs. %.2f\n",
           t[totalTickets].amount);
    printf("=======================================\n");

    totalTickets++;
}

// Display all tickets
void displayTickets() {
    int i;

    if (totalTickets == 0) {
        printf("\nNo Reservations Found!\n");
        return;
    }

    printf("\n========== ALL RESERVATIONS ==========\n");

    for (i = 0; i < totalTickets; i++) {
        printf("\nTicket Number : %d",
               t[i].ticketNo);
        printf("\nPassenger     : %s",
               t[i].name);
        printf("\nAge           : %d",
               t[i].age);
        printf("\nSource        : %s",
               t[i].source);
        printf("\nDestination   : %s",
               t[i].destination);
        printf("\nSeats         : %d",
               t[i].seats);
        printf("\nFare          : Rs. %.2f\n",
               t[i].amount);
    }
}

// Search ticket
void searchTicket() {
    int number, i, found = 0;

    printf("\nEnter Ticket Number: ");
    scanf("%d", &number);

    for (i = 0; i < totalTickets; i++) {
        if (t[i].ticketNo == number) {
            printf("\nTicket Found!\n");
            printf("Passenger: %s\n", t[i].name);
            printf("Age: %d\n", t[i].age);
            printf("From: %s\n", t[i].source);
            printf("To: %s\n", t[i].destination);
            printf("Seats: %d\n", t[i].seats);
            printf("Fare: Rs. %.2f\n", t[i].amount);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nTicket Not Found!\n");
}

// Cancel ticket
void cancelTicket() {
    int number, i, j, found = 0;

    printf("\nEnter Ticket Number to Cancel: ");
    scanf("%d", &number);

    for (i = 0; i < totalTickets; i++) {
        if (t[i].ticketNo == number) {
            printf("\nTicket for %s Cancelled!\n",
                   t[i].name);

            for (j = i; j < totalTickets - 1; j++) {
                t[j] = t[j + 1];
            }

            totalTickets--;
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nTicket Not Found!\n");
}

// Calculate ticket fare
void calculateFare() {
    int seats;
    float fare;

    printf("\nEnter Number of Seats: ");
    scanf("%d", &seats);

    if (seats <= 0 || seats > 6) {
        printf("\nInvalid Seat Count!\n");
        return;
    }

    fare = seats * FARE;

    printf("\n========== FARE DETAILS ==========\n");
    printf("Fare Per Seat : Rs. %d\n", FARE);
    printf("Total Seats   : %d\n", seats);
    printf("Total Fare    : Rs. %.2f\n", fare);
}

// Available seats
void availableSeats() {
    int booked = 0;
    int i;

    for (i = 0; i < totalTickets; i++) {
        booked += t[i].seats;
    }

    printf("\n========== SEAT DETAILS ==========\n");
    printf("Total Seats     : 100\n");
    printf("Booked Seats    : %d\n", booked);
    printf("Available Seats : %d\n", 100 - booked);
}

// Display total revenue
void showRevenue() {
    int i;
    float revenue = 0;

    for (i = 0; i < totalTickets; i++) {
        revenue += t[i].amount;
    }

    printf("\n========== REVENUE REPORT ==========\n");
    printf("Total Tickets: %d\n", totalTickets);
    printf("Total Revenue: Rs. %.2f\n", revenue);
}

// Sort tickets by ticket number
void sortTickets() {
    int i, j;
    struct Ticket temp;

    for (i = 0; i < totalTickets - 1; i++) {
        for (j = 0; j < totalTickets - i - 1; j++) {
            if (t[j].ticketNo > t[j + 1].ticketNo) {
                temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }

    printf("\nTickets Sorted Successfully!\n");
}

// Save tickets
void saveTickets() {
    FILE *fp = fopen("railway.dat", "wb");

    if (fp == NULL) {
        printf("\nFile Error!\n");
        return;
    }

    fwrite(&totalTickets, sizeof(int), 1, fp);
    fwrite(&nextTicket, sizeof(int), 1, fp);
    fwrite(t, sizeof(struct Ticket), totalTickets, fp);

    fclose(fp);

    printf("\nRecords Saved Successfully!\n");
}

// Load tickets
void loadTickets() {
    FILE *fp = fopen("railway.dat", "rb");

    if (fp == NULL)
        return;

    if (fread(&totalTickets, sizeof(int), 1, fp) != 1 ||
        totalTickets < 0 || totalTickets > MAX ||
        fread(&nextTicket, sizeof(int), 1, fp) != 1) {
        totalTickets = 0;
        nextTicket = 1001;
        fclose(fp);
        return;
    }

    if (fread(t, sizeof(struct Ticket),
              totalTickets, fp) != (size_t)totalTickets) {
        totalTickets = 0;
        nextTicket = 1001;
        fclose(fp);
        return;
    }

    fclose(fp);
}

// Main function
int main() {
    int choice;

    loadTickets();

    do {
        printf("\n\n");
        printf("=====================================\n");
        printf("       RAILWAY RESERVATION SYSTEM    \n");
        printf("=====================================\n");

        printf("1. Book Ticket\n");
        printf("2. Display All Tickets\n");
        printf("3. Search Ticket\n");
        printf("4. Cancel Ticket\n");
        printf("5. Calculate Fare\n");
        printf("6. Available Seats\n");
        printf("7. Revenue Report\n");
        printf("8. Sort Tickets\n");
        printf("9. Save Records\n");
        printf("10. Exit\n");

        printf("=====================================\n");
        printf("Enter Your Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid Input!\n");
            break;
        }

        switch (choice) {
            case 1:
                bookTicket();
                break;

            case 2:
                displayTickets();
                break;

            case 3:
                searchTicket();
                break;

            case 4:
                cancelTicket();
                break;

            case 5:
                calculateFare();
                break;

            case 6:
                availableSeats();
                break;

            case 7:
                showRevenue();
                break;

            case 8:
                sortTickets();
                break;

            case 9:
                saveTickets();
                break;

            case 10:
                saveTickets();
                printf("\nThank You for Using Railway System!\n");
                break;

            default:
                printf("\nInvalid Choice! Try Again.\n");
        }

    } while (choice != 10);

    return 0;
}
