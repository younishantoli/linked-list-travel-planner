#include <stdio.h> //library initialization
#include <string.h> //library initialization 
#include <stdlib.h> //library initialization
struct journey{ //city struct
    char name[20]; //name of city initialized
    int distance;  //distance number initialized
    struct journey* next; //pointer of type struct city named next initialized
};


void menu() { //main function to print options
    printf("0) Exit program.\n\n");
    printf("1) Clear Screen.\n\n");
    printf("2) Print all cities.\n\n");
    printf("3) Add a city.\n\n");
    printf("4) Delete a city by city name.\n\n");
    printf("5) Insert a city by position.\n\n");
}

struct journey *makecity(char NewName[], int NewDistance) { //make struct of type struct city called 'makecity'
    
    struct journey *NewCity = (struct journey *)malloc(sizeof(struct journey)); //make NewCity with correct memory allocation (done in class)


    strcpy(NewCity->name, NewName); //transferring information
    NewCity->distance = NewDistance; //transferring transformation
    NewCity->next = NULL; //the next node is NULL

    return NewCity; //NewCity returned & made
}


void choice0() { //choice 0 to exit and receive an inputted character
    printf("Process returned (0x0)\n");
    getchar();
    getchar();
    exit(0); 
}

void choice1() { //choice 1 to clear screen
    system("cls");
    menu();
}

void choice2(struct journey* head) { //choice 2
    int totaldistance = 0;

    if(head == NULL) { //if first node is empty
        printf("The list is empty.\n"); //say list is empty
        return;
    }

    printf("\n"); //new line

    struct journey *temporary = head; //new node called temporary of type struct city = head

    while(temporary != NULL) { // while that node isn't null
        totaldistance = temporary->distance + totaldistance; //the total distance updates
        printf("%-12s %-12d\n", temporary->name, temporary->distance); //print contents
        temporary = temporary->next; //temporary moves 
    }
    printf("\nTotal Distance: %d\n", totaldistance); //print what u want
}

void choice3(struct journey **head) { //choice 3 & double pointer changes the original head pointer in main
    char cityname[20]; //initialization
    int citydistance; //initialization

    printf("\nEnter city name and distaance from previous city: ");
    scanf("%s %d", cityname, &citydistance); //store input from user

    struct journey *newcity = makecity(cityname, citydistance); //make newcity

    if(*head == NULL) {  //if its null, the lsit is empty
        *head = newcity; //head points to the newcity
    } else { //or else
        struct journey *temporary = *head; //make temporary pointer to pointer head
        while(temporary->next != NULL) { // create temporary pointer that starts at the top of the list
            temporary = temporary->next; // move temporary to next node
        }
        temporary->next = newcity; //once you find last node, set next pointer to newcity
    }
    printf("New City added.\n"); //print what I want
}

void choice4(struct journey **head) { //choice 4 function
    char cityname[20]; //initialization

    if(*head == NULL) { // if list is empty
        printf("\nThe City List is Empty."); //print what I want
        return; 
    }

    printf("Enter city name to delete: "); //print what I want
    scanf("%s", cityname); //store it

    struct journey *temporary = *head; //create temporary node and set it equal to the head pointer
    struct journey *previous = NULL; //create previous and set it equal to NULL

    if (strcmp(temporary->name, cityname) == 0) {

        if(temporary->next != NULL) { //if the pointer to next isn't empty
            temporary->next->distance = temporary->next->distance + temporary->distance; //add up distances
        }
        *head = temporary->next; //head node is the next pointer from next (after deleted one basically)

        free(temporary); //delete temporary
        printf("City deleted.\n"); //delete the city
        return;
    }

    while(temporary != NULL) { //while it's not empty
        if(strcmp(temporary->name, cityname) == 0) { //compares current node to input of user
            if(temporary->next != NULL) { //if the next one is not null
                temporary->next->distance = temporary->next->distance + temporary->distance; //add distances
            } //else
                previous->next = temporary->next; //rmoeves it from the list
            free(temporary); //open up 'temporary' memory
            printf("City deleted.\n"); //print what I want
            return;
        }
    }
    previous = temporary;
    temporary = temporary->next;
}

void choice5(struct journey **head) { //choice 5 function
    char cityname[20]; //initialization
    int previouscitydistance; //initialization
    int position; //initialization
    int nextcitydistance; //initialization

    printf("Enter city name, distance from previous city, and position: "); //print what I want
    scanf("%s %d %d", cityname, &previouscitydistance, &position); //store it
    printf("Enter new distance for next city: "); //print what I want
    scanf("%d", &nextcitydistance); //store

    struct journey *newcity = makecity(cityname, previouscitydistance); //allocate and make new city node
    struct journey *temporary = *head; //new temp node  and set pointing to head node
    struct journey *previous = NULL; // new previous node is NULL

    for(int i = 1; i < position && temporary != NULL; i++) { //for loop
        previous = temporary; //previous is temp
        temporary = temporary->next; //temp points to next
    }
    if(previous == NULL) { //if inserting at position 1, newcity is the head
        newcity->next = *head; 
        *head = newcity;
    }
    else {
        previous->next = newcity; //otherwise pre->newcity->temp
        newcity->next = temporary;// ^^
    }

    if(newcity->next != NULL) { //if there's a city after this one,
        newcity->next->distance = nextcitydistance; //update distance
    }
    printf("City inserted.\n"); 
}

int main() { //main function LIKE PROJECT 3
    int choice;
    struct journey *head = NULL;
    head = makecity("Arlington", 67);
    head->next = ("Mansfield", 78);
    menu();
    while (1) {
        printf("\nEnter a choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 0: choice0();
                break;
            case 1: choice1();
                break;
            case 2: choice2(head);
                break;
            case 3: choice3(&head);
                break;
            case 4: choice4(&head);
                break;
            case 5: choice5(&head); //&head because the address of head; from the actual inside
                break;
            default: 
                printf("Enter a valid choice.\n");
                break;
        }
    }

    return 0;

}
