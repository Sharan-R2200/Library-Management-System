#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Book {
public:
    int id;
    char title[50];
    char author[50];
    bool isIssued;

    void input() {
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Title: ";
        cin.getline(title, 50);

        cout << "Enter Author: ";
        cin.getline(author, 50);

        isIssued = false;
    }

    void display() {
        cout << "ID: " << id
             << " | Title: " << title
             << " | Author: " << author
             << " | Status: " << (isIssued ? "Issued" : "Available")
             << endl;
    }
};

// 🔹 Add Book
void addBook() {
    Book b;
    ofstream file("library.dat", ios::binary | ios::app);

    b.input();
    file.write((char*)&b, sizeof(b));

    file.close();
    cout << "Book added successfully!\n";
}

// 🔹 Display Books (FIXED)
void displayBooks() {
    Book b;
    ifstream file("library.dat", ios::binary);

    if (!file) {
        cout << "No records found!\n";
        return;
    }

    cout << "\n---- Library Records ----\n";

    bool found = false;

    while (file.read((char*)&b, sizeof(b))) {
        // 🔥 Skip garbage/empty records
        if (b.id != 0 && strlen(b.title) > 0) {
            b.display();
            found = true;
        }
    }

    if (!found) {
        cout << "No valid records found!\n";
    }

    file.close();
}

// 🔹 Search Book
void searchBook() {
    int searchId;
    cout << "Enter Book ID to search: ";
    cin >> searchId;

    Book b;
    ifstream file("library.dat", ios::binary);

    bool found = false;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.id == searchId) {
            b.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Book not found!\n";

    file.close();
}

// 🔹 Issue Book
void issueBook() {
    int id;
    cout << "Enter Book ID to issue: ";
    cin >> id;

    fstream file("library.dat", ios::binary | ios::in | ios::out);
    Book b;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.id == id) {
            if (!b.isIssued) {
                b.isIssued = true;

                file.seekp(-sizeof(b), ios::cur);
                file.write((char*)&b, sizeof(b));

                cout << "Book issued successfully!\n";
            } else {
                cout << "Book already issued!\n";
            }
            file.close();
            return;
        }
    }

    cout << "Book not found!\n";
    file.close();
}

// 🔹 Return Book
void returnBook() {
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;

    fstream file("library.dat", ios::binary | ios::in | ios::out);
    Book b;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.id == id) {
            if (b.isIssued) {
                b.isIssued = false;

                file.seekp(-sizeof(b), ios::cur);
                file.write((char*)&b, sizeof(b));

                cout << "Book returned successfully!\n";
            } else {
                cout << "Book was not issued!\n";
            }
            file.close();
            return;
        }
    }

    cout << "Book not found!\n";
    file.close();
}

// 🔹 Main Menu
int main() {
    int choice;

    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
