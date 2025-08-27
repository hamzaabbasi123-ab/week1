#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Book class definition
class Book {
private:
    int bookID;
    string title;
    string author;
    int quantity;
    
public:
    // Default constructor
    Book() : bookID(0), title(""), author(""), quantity(0) {}
    
    // Parameterized constructor
    Book(int id, string t, string a, int q) : bookID(id), title(t), author(a), quantity(q) {}
    
    // Member functions
    void displayBook() const {
        cout << "ID: " << bookID << " | Title: " << title 
             << " | Author: " << author << " | Quantity: " << quantity << endl;
    }
    
    // Getters
    int getBookID() const { return bookID; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getQuantity() const { return quantity; }
    
    // Setters
    void setQuantity(int q) { quantity = q; }
    
    // Function to save book data to file
    void saveToFile(ofstream &outFile) const {
        outFile << bookID << endl;
        outFile << title << endl;
        outFile << author << endl;
        outFile << quantity << endl;
    }
    
    // Function to load book data from file
    void loadFromFile(ifstream &inFile) {
        inFile >> bookID;
        inFile.ignore();
        getline(inFile, title);
        getline(inFile, author);
        inFile >> quantity;
    }
};

const int MAX_BOOKS = 100;
Book books[MAX_BOOKS];
int bookCount = 0;
const string BOOKS_FILE = "library.txt";

// Function prototypes
void addBook();
void viewAllBooks();
void borrowBook();
void returnBook();
void saveBooksToFile();
void loadBooksFromFile();

int main() {
    loadBooksFromFile();
    
    int choice;
    
    do {
        cout << "\n=== LIBRARY MANAGEMENT SYSTEM ===" << endl;
        cout << "1. Add New Book" << endl;
        cout << "2. View All Books" << endl;
        cout << "3. Borrow a Book" << endl;
        cout << "4. Return a Book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer
        
        switch(choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewAllBooks();
                break;
            case 3:
                borrowBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                saveBooksToFile();
                cout << "Data saved successfully. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while(choice != 5);
    
    return 0;
}

// Function to add a new book
void addBook() {
    if(bookCount >= MAX_BOOKS) {
        cout << "Maximum number of books reached!" << endl;
        return;
    }
    
    int id, quantity;
    string title, author;
    
    cout << "\nEnter Book Details:" << endl;
    cout << "Book ID: ";
    cin >> id;
    cin.ignore();
    cout << "Title: ";
    getline(cin, title);
    cout << "Author: ";
    getline(cin, author);
    cout << "Quantity: ";
    cin >> quantity;
    
    // Check if book ID already exists
    for(int i = 0; i < bookCount; i++) {
        if(books[i].getBookID() == id) {
            cout << "Book with this ID already exists!" << endl;
            return;
        }
    }
    
    books[bookCount] = Book(id, title, author, quantity);
    bookCount++;
    cout << "Book added successfully!" << endl;
}

// Function to view all books
void viewAllBooks() {
    if(bookCount == 0) {
        cout << "No books available in the library!" << endl;
        return;
    }
    
    cout << "\n=== ALL BOOKS IN LIBRARY ===" << endl;
    for(int i = 0; i < bookCount; i++) {
        books[i].displayBook();
    }
}

// Function to borrow a book
void borrowBook() {
    if(bookCount == 0) {
        cout << "No books available in the library!" << endl;
        return;
    }
    
    int id;
    cout << "Enter Book ID to borrow: ";
    cin >> id;
    
    for(int i = 0; i < bookCount; i++) {
        if(books[i].getBookID() == id) {
            if(books[i].getQuantity() > 0) {
                books[i].setQuantity(books[i].getQuantity() - 1);
                cout << "Book borrowed successfully!" << endl;
                cout << "Remaining quantity: " << books[i].getQuantity() << endl;
            } else {
                cout << "Sorry, this book is currently out of stock!" << endl;
            }
            return;
        }
    }
    
    cout << "Book with ID " << id << " not found!" << endl;
}

// Function to return a book
void returnBook() {
    if(bookCount == 0) {
        cout << "No books in the library system!" << endl;
        return;
    }
    
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;
    
    for(int i = 0; i < bookCount; i++) {
        if(books[i].getBookID() == id) {
            books[i].setQuantity(books[i].getQuantity() + 1);
            cout << "Book returned successfully!" << endl;
            cout << "Current quantity: " << books[i].getQuantity() << endl;
            return;
        }
    }
    
    cout << "Book with ID " << id << " not found in library system!" << endl;
}

// Function to save all books to file
void saveBooksToFile() {
    ofstream outFile(BOOKS_FILE);
    if(!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    
    outFile << bookCount << endl;
    for(int i = 0; i < bookCount; i++) {
        books[i].saveToFile(outFile);
    }
    
    outFile.close();
}

// Function to load books from file
void loadBooksFromFile() {
    ifstream inFile(BOOKS_FILE);
    if(!inFile) {
        cout << "No existing library data found. Starting fresh." << endl;
        return;
    }
    
    inFile >> bookCount;
    inFile.ignore();
    
    for(int i = 0; i < bookCount; i++) {
        Book temp;
        temp.loadFromFile(inFile);
        books[i] = temp;
    }
    
    inFile.close();
    cout << "Library data loaded successfully!" << endl;
}