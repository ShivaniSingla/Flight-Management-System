#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHTS 50

struct Time {
    int hour;
    int minutes;
    int sec;
};

struct Date {
    int date;
    int month;
    int year;
};

struct City {
    char location[20];
};

struct Airline {
    char f_no[10];
    struct City dep;
    struct Date d_dep;
    struct Time t_dep;
    struct City des;
    struct Date d_arr;
    struct Time t_arr;
    int f_seat_available;
    int c_seat_available;
};

/* ---------- STAFF: CREATE / UPDATE ---------- */
void creation_update(struct Airline *arr) {
    int n;
    printf("How many flights do you want to add? ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_FLIGHTS) {
        printf("Invalid number.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("\nFlight %d\n", i + 1);

        printf("Enter flight number: ");
        scanf("%9s", arr[i].f_no);

        printf("Enter city of departure: ");
        scanf("%19s", arr[i].dep.location);

        printf("Enter departure date (dd-mm-yyyy): ");
        scanf("%d-%d-%d",
              &arr[i].d_dep.date,
              &arr[i].d_dep.month,
              &arr[i].d_dep.year);

        printf("Enter departure time (hh-mm-ss): ");
        scanf("%d-%d-%d",
              &arr[i].t_dep.hour,
              &arr[i].t_dep.minutes,
              &arr[i].t_dep.sec);

        printf("Enter city of arrival: ");
        scanf("%19s", arr[i].des.location);

        printf("Enter arrival date (dd-mm-yyyy): ");
        scanf("%d-%d-%d",
              &arr[i].d_arr.date,
              &arr[i].d_arr.month,
              &arr[i].d_arr.year);

        printf("Enter arrival time (hh-mm-ss): ");
        scanf("%d-%d-%d",
              &arr[i].t_arr.hour,
              &arr[i].t_arr.minutes,
              &arr[i].t_arr.sec);

        printf("First class seats available: ");
        scanf("%d", &arr[i].f_seat_available);

        printf("Coach seats available: ");
        scanf("%d", &arr[i].c_seat_available);
    }

    FILE *file = fopen("Data/flight_data.csv", "a");
    if (!file) {
        perror("File error");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file,
                "%s,%s,%d-%d-%d,%d:%d:%d,%s,%d-%d-%d,%d:%d:%d,%d,%d\n",
                arr[i].f_no,
                arr[i].dep.location,
                arr[i].d_dep.date, arr[i].d_dep.month, arr[i].d_dep.year,
                arr[i].t_dep.hour, arr[i].t_dep.minutes, arr[i].t_dep.sec,
                arr[i].des.location,
                arr[i].d_arr.date, arr[i].d_arr.month, arr[i].d_arr.year,
                arr[i].t_arr.hour, arr[i].t_arr.minutes, arr[i].t_arr.sec,
                arr[i].f_seat_available,
                arr[i].c_seat_available);
    }

    fclose(file);
    printf("\nFlight data saved successfully.\n");
}

/* ---------- READ FLIGHT DATA ---------- */
void read_flight() {
    char flight_no[10];
    printf("Enter flight number: ");
    scanf("%9s", flight_no);

    FILE *file = fopen("Data/flight_data.csv", "r");
    if (!file) {
        perror("File error");
        return;
    }

    char line[1024];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        struct Airline a;

        sscanf(line,
               "%9[^,],%19[^,],%d-%d-%d,%d:%d:%d,%19[^,],%d-%d-%d,%d:%d:%d,%d,%d",
               a.f_no,
               a.dep.location,
               &a.d_dep.date, &a.d_dep.month, &a.d_dep.year,
               &a.t_dep.hour, &a.t_dep.minutes, &a.t_dep.sec,
               a.des.location,
               &a.d_arr.date, &a.d_arr.month, &a.d_arr.year,
               &a.t_arr.hour, &a.t_arr.minutes, &a.t_arr.sec,
               &a.f_seat_available,
               &a.c_seat_available);

        if (strcmp(a.f_no, flight_no) == 0) {
            printf("\nFlight Number: %s\n", a.f_no);
            printf("Departure: %s %02d-%02d-%04d %02d:%02d:%02d\n",
                   a.dep.location,
                   a.d_dep.date, a.d_dep.month, a.d_dep.year,
                   a.t_dep.hour, a.t_dep.minutes, a.t_dep.sec);

            printf("Arrival: %s %02d-%02d-%04d %02d:%02d:%02d\n",
                   a.des.location,
                   a.d_arr.date, a.d_arr.month, a.d_arr.year,
                   a.t_arr.hour, a.t_arr.minutes, a.t_arr.sec);

            printf("First Class Seats: %d\n", a.f_seat_available);
            printf("Coach Seats: %d\n", a.c_seat_available);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Flight not found.\n");

    fclose(file);
}

/* ---------- LOGIN CHECK ---------- */
int check_user() {
    int role, code, attempts = 0;

    while (attempts < 5) {
        printf("\nAre you a customer or staff?\n");
        printf("Customer: 1 | Staff: 0\nEnter: ");
        scanf("%d", &role);

        if (role == 1)
            return 1;

        if (role == 0) {
            printf("Enter security code: ");
            scanf("%d", &code);

            if (code == 36)
                return 0;

            printf("Incorrect code.\n");
        } else {
            printf("Invalid input.\n");
        }
        attempts++;
    }

    return -1;
}

/* ---------- MAIN ---------- */
int main() {
    struct Airline flights[MAX_FLIGHTS];
    int choice;

    int user = check_user();
    if (user == -1) {
        printf("Too many attempts. Program terminated.\n");
        return 1;
    }

    if (user == 1) {
        printf("\nCustomer Portal\n");
        read_flight();
    } else {
        printf("\nStaff Portal\n");
        printf("1. Add flight data\n2. Read flight data\nEnter: ");
        scanf("%d", &choice);

        if (choice == 1)
            creation_update(flights);
        else if (choice == 2)
            read_flight();
        else
            printf("Invalid choice.\n");
    }

    return 0;
}