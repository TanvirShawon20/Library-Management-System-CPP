#include <bits/stdc++.h>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    int available_copies;

    Book() {
        
    }
    Book(int i, string t, string a, int c) {
        id = i;
        title = t;
        author = a;
        available_copies = c;
    }

    string serialize() const {
        return to_string(id) + "|" + title + "|" + author + "|" + to_string(available_copies);
    }

    static Book deserialize(const string &line) {
        stringstream ss(line);
        string temp;
        Book b;

        getline(ss, temp, '|');
        b.id = stoi(temp);
        getline(ss, b.title, '|');
        getline(ss, b.author, '|');
        getline(ss, temp, '|');
        b.available_copies = stoi(temp);

        return b;
    }
};

class Library {
private:
    vector<Book> books;
    const string FILE_NAME = "books.txt";

public:
    void loadBooks() {
        ifstream file(FILE_NAME);
        if(!file) return;

        books.clear();
        string line;

        while(getline(file, line)) {
            books.push_back(Book::deserialize(line));
        }
        file.close();
    }

    void saveBooks() {
        ofstream file(FILE_NAME);
        if(!file) return;

        for(const auto &b : books) {
            file << b.serialize() << "\n";
        }
        file.close();
    }

    void addBook() {
        int id, copies;
        string title, author;

        cout << "Enter book ID: ";
        cin >> id;

        for(auto &b : books) {
            if(b.id == id) {
                cout << "Book ID already exists.\n";
                return;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter book title: ";
        getline(cin, title);
        cout << "Enter book author: ";
        getline(cin, author);
        cout << "Enter number of copies: ";
        cin >> copies;

        books.push_back(Book(id, title, author, copies));
        saveBooks();
        cout << "Book added successfully.\n";
    }

    void displayBooks() {
        if(books.empty()) {
            cout << "No books available.\n";
            return;
        }

        cout << "\n--- Books ---\n";
        for(const auto &b : books) {
            cout << "ID: " << b.id << " | Title: " << b.title
                 << " | Author: " << b.author
                 << " | Copies: " << b.available_copies << "\n";
        }
    }

    void searchBook() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string title;
        cout << "Enter title: ";
        getline(cin, title);

        for(const auto &b : books) {
            if(b.title == title) {
                cout << "Found -> ID: " << b.id << " | Author: " << b.author
                     << " | Copies: " << b.available_copies << "\n";
                return;
            }
        }
        cout << "Not found.\n";
    }

    void borrowBook() {
        int id;
        cout << "Enter ID: ";
        cin >> id;

        for(auto &b : books) {
            if(b.id == id) {
                if(b.available_copies > 0) {
                    b.available_copies--;
                    saveBooks();
                    cout << "Borrowed.\n";
                } else {
                    cout << "No copies available.\n";
                }
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void returnBook() {
        int id;
        cout << "Enter ID: ";
        cin >> id;

        for(auto &b : books) {
            if(b.id == id) {
                b.available_copies++;
                saveBooks();
                cout << "Returned.\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void deleteBook() {
        int id;
        cout << "Enter ID: ";
        cin >> id;

        for(auto it = books.begin(); it != books.end(); ++it) {
            if(it->id == id) {
                books.erase(it);
                saveBooks();
                cout << "Deleted.\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void updateBook() {
        int id;
        cout << "Enter book ID to update: ";
        cin >> id;

        for(auto &b : books) {
            if(b.id == id) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter new title: ";
                getline(cin, b.title);
                cout << "Enter new author: ";
                getline(cin, b.author);
                cout << "Enter new copies: ";
                cin >> b.available_copies;

                saveBooks();
                cout << "Book updated successfully.\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    Library lib;
    lib.loadBooks();

    int choice;

    while(true) {
        cout << "\n--- Library System ---\n";
        cout << "1. Add Book\n";
        cout << "2. Delete Book\n";
        cout << "3. View Books\n";
        cout << "4. Search Book\n";
        cout << "5. Borrow Book\n";
        cout << "6. Return Book\n";
        cout << "7. Update Book\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: lib.addBook(); break;
            case 2: lib.deleteBook(); break;
            case 3: lib.displayBooks(); break;
            case 4: lib.searchBook(); break;
            case 5: lib.borrowBook(); break;
            case 6: lib.returnBook(); break;
            case 7: lib.updateBook(); break;
            case 8: return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}