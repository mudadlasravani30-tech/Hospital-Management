#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

typedef struct {
    int id;
    char name[50];
    int age;
    char disease[50];
    char contact[15];
} Patient;

Patient patients[MAX_PATIENTS];
int patient_count = 0;

// Function Prototypes
void display_menu();
void add_patient();
void view_patients();
void search_patient();

int main() {
    int choice;

    do {
        display_menu();
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            choice = 0;
            while(getchar() != '\n'); // clear invalid input
        }

        switch(choice) {
            case 1: add_patient(); break;
            case 2: view_patients(); break;
            case 3: search_patient(); break;
            case 4: printf("\nExiting Hospital Management System. Goodbye!\n"); break;
            default: printf("\nInvalid choice. Please try again.\n");
        }

    } while(choice != 4);

    return 0;
}

// --- Menu Function ---
void display_menu() {
    printf("\n==========================================\n");
    printf("     Hospital Management System\n");
    printf("==========================================\n");
    printf("1. Add New Patient Record\n");
    printf("2. View All Patient Records\n");
    printf("3. Search Patient Record\n");
    printf("4. Exit\n");
    printf("------------------------------------------\n");
}

// --- Add Patient ---
void add_patient() {
    if(patient_count >= MAX_PATIENTS) {
        printf("\nPatient list full. Cannot add more.\n");
        return;
    }

    Patient p;
    printf("\n--- Add New Patient Record ---\n");
    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    getchar(); // consume newline

    printf("Enter Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%d", &p.age);
    getchar();

    printf("Enter Disease: ");
    fgets(p.disease, sizeof(p.disease), stdin);
    p.disease[strcspn(p.disease, "\n")] = 0;

    printf("Enter Contact Number: ");
    fgets(p.contact, sizeof(p.contact), stdin);
    p.contact[strcspn(p.contact, "\n")] = 0;

    patients[patient_count++] = p;

    printf("\nPatient record successfully added!\n");
}

// --- View Patients ---
void view_patients() {
    if(patient_count == 0) {
        printf("\nNo patient records found.\n");
        return;
    }

    printf("\n--- All Patient Records ---\n");
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("| %-4s | %-20s | %-4s | %-25s | %-15s |\n",
           "ID", "Name", "Age", "Disease", "Contact");
    printf("-------------------------------------------------------------------------------------------------\n");

    for(int i=0; i<patient_count; i++) {
        printf("| %-4d | %-20s | %-4d | %-25s | %-15s |\n",
               patients[i].id, patients[i].name, patients[i].age,
               patients[i].disease, patients[i].contact);
    }
    printf("-------------------------------------------------------------------------------------------------\n");
}

// --- Search Patient ---
void search_patient() {
    if(patient_count == 0) {
        printf("\nNo patient records to search.\n");
        return;
    }

    int search_id, found = 0;
    printf("\nEnter Patient ID to search: ");
    if(scanf("%d", &search_id) != 1) {
        printf("Invalid input.\n");
        while(getchar() != '\n');
        return;
    }

    for(int i=0; i<patient_count; i++) {
        if(patients[i].id == search_id) {
            printf("\n--- Patient Found ---\n");
            printf("ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Disease: %s\n", patients[i].disease);
            printf("Contact: %s\n", patients[i].contact);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("\nNo patient found with ID %d.\n", search_id);
}