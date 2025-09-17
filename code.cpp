/* In a hospital management system, there's a requirement to maintain a record of patients waiting in
the emergency room. Implement a singly linked list to manage this queue efficiently. The
system should allow receptionists to add patients to the end of the queue, doctors to remove
patients from the front of the queue for examination, and nurses to move patients up in priority if
their condition deteriorates. Additionally, the system should provide functionality to display the
current queue, search for specific patients, and update patient information as needed. The goal is
to streamline the patient management process, ensuring timely and efficient care delivery in the
emergency room. */

#include <iostream>
using namespace std;

struct Patient {
    string name;
    int age;
    int ID;
    string condition;
    Patient* next;
};

// Create a new patient
Patient* create_patient(string name, int age, int id, string condition) {
    Patient* newPatient = new Patient;
    newPatient->name = name;
    newPatient->age = age;
    newPatient->ID = id;
    newPatient->condition = condition;
    newPatient->next = NULL;
    return newPatient;
}

// Add patient to end of queue
Patient* add_patient(Patient* head) {
    int id, age;
    string name, condition;
    cout << "Enter Patient's name: ";
    cin >> name;
    cout << "Enter Patient's Age: ";
    cin >> age;
    cout << "Enter patient ID: ";
    cin >> id;
    cout << "Enter Patient's condition: ";
    cin >> condition;

    Patient* newPatient = create_patient(name, age, id, condition);

    if (!head) return newPatient;

    Patient* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newPatient;

    return head;
}

// Remove patient from front of queue
Patient* examine_patient(Patient* head) {
    if (!head) {
        cout << "Queue is empty.\n";
        return head;
    }
    Patient* temp = head;
    cout << "Examining patient: " << temp->name << " (ID: " << temp->ID << ")\n";
    head = head->next;
    delete temp;
    return head;
}

// Prioritize patient by moving to front
Patient* prioritize_patient(Patient* head, int id) {
    if (!head || head->ID == id) return head;

    Patient* prev = head;
    Patient* curr = head->next;

    while (curr) {
        if (curr->ID == id) {
            prev->next = curr->next;
            curr->next = head;
            head = curr;
            cout << "Patient with ID " << id << " moved to front.\n";
            return head;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Patient with ID " << id << " not found.\n";
    return head;
}

// Search for a patient
void search_patient(Patient* head, int id) {
    while (head) {
        if (head->ID == id) {
            cout << "Found: " << head->name << ", Age: " << head->age
                 << ", Condition: " << head->condition << endl;
            return;
        }
        head = head->next;
    }
    cout << "Patient with ID " << id << " not found.\n";
}

// Update patient info
void update_patient(Patient* head, int id) {
    while (head) {
        if (head->ID == id) {
            cout << "Enter new name: ";
            cin >> head->name;
            cout << "Enter new age: ";
            cin >> head->age;
            cout << "Enter new condition: ";
            cin >> head->condition;
            cout << "Patient updated successfully.\n";
            return;
        }
        head = head->next;
    }
    cout << "Patient with ID " << id << " not found.\n";
}

// Display full queue
void display_queue(Patient* head) {
    if (!head) {
        cout << "Queue is empty.\n";
        return;
    }
    cout << "Current ER Queue:\n";
    while (head) {
        cout << "[ID: " << head->ID << "] " << head->name
             << ", Age: " << head->age << ", Condition: " << head->condition << "\n";
        head = head->next;
    }
}

int main() {
    Patient* head = NULL;
    int choice, id;
cout << "\n--- ER Queue Menu ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Examine Patient\n";
        cout << "3. Prioritize Patient\n";
        cout << "4. Search Patient\n";
        cout << "5. Update Patient\n";
        cout << "6. Display Queue\n";
        cout << "0. Exit\n";
       
    do {
    cout << endl;
    cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: head = add_patient(head); break;
            case 2: head = examine_patient(head); break;
            case 3:
                cout << "Enter Patient ID to prioritize: ";
                cin >> id;
                head = prioritize_patient(head, id);
                break;
            case 4:
                cout << "Enter Patient ID to search: ";
                cin >> id;
                search_patient(head, id);
                break;
            case 5:
                cout << "Enter Patient ID to update: ";
                cin >> id;
                update_patient(head, id);
                break;
            case 6: display_queue(head); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
