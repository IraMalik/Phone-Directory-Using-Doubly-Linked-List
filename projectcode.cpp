#include <iostream>
#include <string>
using namespace std;

struct Phone {
    string num;
    string name;
    string email;
    int searchCount;
    Phone* next;
    Phone* prev;
};

Phone* start = nullptr;

Phone* createPhone() {
    Phone* newPhone = new Phone;
    newPhone->prev = nullptr;
    newPhone->next = nullptr;
    return newPhone;
}

void addContact(string name, string num, string email) {
    if (num.length() != 10) {
        cout << "Invalid phone number. Phone number must have 10 digits." << endl;
        return;
    }
    Phone* newPhone = createPhone();
    newPhone->num = num;
    newPhone->name = name;
    newPhone->email = email;
    newPhone->searchCount = 0;
    if (start == nullptr)
        start = newPhone;
    else {
        Phone* temp = start;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newPhone;
        newPhone->prev = temp;
    }
    cout << "New contact added." << endl;
}

void updateContact(string name) {
    Phone* current = start;

    while (current != nullptr) {
        if (current->name == name) {
            cout << "Contact found." << endl;
            int choice;
            cout << "Enter 1 to update name, 2 to update number, or 3 to update email: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter new name: ";
                    cin >> current->name;
                    cout << "Contact name updated successfully." << endl;
                    break;
                case 2:
                    cout << "Enter new number: ";
                    cin >> current->num;
                    cout << "Contact number updated successfully." << endl;
                    break;
                case 3:
                    cout << "Enter new email: ";
                    cin >> current->email;
                    cout << "Contact email updated successfully." << endl;
                    break;
                default:
                    cout << "Invalid choice." << endl;
            }
            return;
        }
        current = current->next;
    }
    cout << "Contact not found." << endl;
}

void sortContacts() {
    if (start == nullptr || start->next == nullptr) {
        return;
    }

    Phone* current;
    bool sorted = false;

    while (!sorted) {
        current = start;
        sorted = true;

        while (current->next != nullptr) {
            if (current->name > current->next->name) {
                swap(current->name, current->next->name);
                swap(current->num, current->next->num);
                swap(current->email, current->next->email);
                sorted = false;
            }
            current = current->next;
        }
    }
}

void displayContacts() {
    if (start == nullptr) {
        cout << "No contacts found." << endl;
        return;
    }

    Phone* temp = start;
    while (temp != nullptr) {
        cout << "Name: " << temp->name << endl;
        cout << "Number: " << temp->num << endl;
        cout << "Email: " << temp->email << endl;
        temp = temp->next;
        cout << endl;
    }
}

char searchContact(string name) {
    Phone* temp = start;
    while (temp != nullptr) {
        if (temp->name == name) {
            temp->searchCount++;
            return 'F';
        }
        temp = temp->next;
    }
    return 'N';
}

void deleteContact(string name) {
    Phone* current = start;

    while (current != nullptr) {
        if (current->name == name) {
            if (current == start) {
                start = current->next;
                if (start != nullptr) {
                    start->prev = nullptr;
                }
            } else {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                }
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                }
            }
            cout << "Deleted contact '" << current->name << "'" << endl;
            delete current;
            return;
        }
        current = current->next;
    }
    cout << "This contact does not exist in this directory." << endl;
}

int main() {
    int choice, a = 1;
    string name, num, email;
    char result;

    while (a == 1) {
        cout << "Choices:\n1. Add contact\n2. Search Contact\n3. Display all contacts\n4. Update contact\n5. Delete contact\n6. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter number: ";
                cin >> num;
                cout << "Enter email: ";
                cin >> email;
                cout << "Enter name: ";
                cin >> name;
                addContact(name, num, email);
                break;
            
            case 2:
                cout<<"Enter person name to search: ";
                cin>>name;
                result=searchContact(name);
                if (result == 'F') {
                    cout<<"Contact found."<<endl;
                } else {
                    cout<<"Contact not found."<<endl;
                }
                break;

            case 3:
                sortContacts();
                displayContacts();
                break;

            case 4:
                cout<<"Enter Name: ";
                cin>>name;
                updateContact(name);
                break;

            case 5:
                cout<<"Enter name of contact to be deleted: ";
                cin>>name;
                deleteContact(name);
                break;

            case 6:
                cout<<"Exiting directory"<<endl;
                a = 0;
                break;

            default:
                cout<<"Invalid choice"<<endl;
        }
    }
    return 0;
}