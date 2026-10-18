#include <stdio.h>

#include<string.h>

struct Vehicle
{
    char number[20];
    char type[10];
    int slot;
    int entryTime;
};

int main()
{
    struct Vehicle vehicles[50];
    int count = 0;
    int choice;

    while (1) 
    {

    printf("\nPARKING MANAGEMENT SYSTEM\n");
    printf("1. Park Vehicle\n");
    printf("2. Remove Vehicle\n");
    printf("3. Search Vehicle\n");
    printf("4. Display Parked Vehicles\n");
    printf("5. Display Available Slots\n");
    printf("6. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
{
    case 1:
        printf("\n--- Park Vehicle ---\n");

        printf("Enter vehicle number: ");
        scanf("%19s", vehicles[count].number);

        printf("Enter vehicle type (Car/Bike): ");
        scanf("%9s", vehicles[count].type);

        vehicles[count].slot = count + 1;

        printf("Enter entry time: ");
        scanf("%d", &vehicles[count].entryTime);

        printf("\nVehicle parked successfully!\n");
        printf("Allocated Slot: %d\n", vehicles[count].slot);

        count++;
        break;
        
        if (count >= 50)
{
    printf("Parking is full!\n");
    break;
}

    case 2:
{
    char exitNumber[20];
    int found = 0;
    int exitTime, duration, fee;

    printf("\nEnter vehicle number to remove: ");
    scanf("%19s", exitNumber);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(vehicles[i].number, exitNumber) == 0)
        {
            printf("Enter exit time (0-23): ");
            scanf("%d", &exitTime);

            if (exitTime < vehicles[i].entryTime ||
                exitTime > 23)
            {
                printf("Invalid exit time!\n");
                found = 1;
                break;
            }

            duration = exitTime - vehicles[i].entryTime;

            if (duration == 0)
                duration = 1;

            fee = duration * 20;

            printf("\nVehicle Number: %s\n",
                   vehicles[i].number);
            printf("Parking Duration: %d hour(s)\n",
                   duration);
            printf("Parking Fee: Rs. %d\n", fee);

            for (int j = i; j < count - 1; j++)
            {
                vehicles[j] = vehicles[j + 1];
            }

            count--;
            printf("Vehicle removed successfully!\n");

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("Vehicle not found!\n");
    }

    break;
}


    case 3:
{
    char searchNumber[20];
    int found = 0;

    printf("\nEnter vehicle number to search: ");
    scanf("%19s", searchNumber);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(vehicles[i].number, searchNumber) == 0)
        {
            printf("\nVehicle Found!\n");
            printf("Vehicle Number: %s\n", vehicles[i].number);
            printf("Vehicle Type: %s\n", vehicles[i].type);
            printf("Parking Slot: %d\n", vehicles[i].slot);
            printf("Entry Time: %d\n", vehicles[i].entryTime);

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("\nVehicle not found!\n");
    }

    break;
}

    
       
case 4:
    printf("\n--- Parked Vehicles ---\n");

    if (count == 0)
    {
        printf("No vehicles are parked.\n");
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            printf("\nVehicle %d\n", i + 1);
            printf("Vehicle Number: %s\n", vehicles[i].number);
            printf("Vehicle Type: %s\n", vehicles[i].type);
            printf("Parking Slot: %d\n", vehicles[i].slot);
            printf("Entry Time: %d\n", vehicles[i].entryTime);
        }
    }

    break;


    case 5:
    printf("\n--- Available Slots ---\n");
    printf("Total Parking Slots: 50\n");
    printf("Occupied Slots: %d\n", count);
    printf("Available Slots: %d\n", 50 - count);
    break;

    case 6:
        printf("Thank you!\n");
        break;

    default:
        printf("Invalid choice!\n");
}
    }

}