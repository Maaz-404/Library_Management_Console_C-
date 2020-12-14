#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

int bookOptions() {

	system("cls");
	cout << "\n----------------  Library Management System  ---------------- \n" << endl;
	cout << "1. Add Book" << endl;
	cout << "2. Update Book" << endl;
	cout << "3. Delete Book" << endl;
	cout << "4. Show All Books" << endl;
	cout << "5. Issue Books" << endl;
	cout << "6. Issued Books - Show All Borrowers & Return Dates" << endl;
	cout << "7. Show Library Card Holders" << endl;
	cout << "8. Register New Library Cards" << endl;

	cout << "0. Exit" << endl;
	cout << "--- Choose any one option --- \n " << endl;
	cout << "Enter one option: ";

	int selectedOption = 0;
	cin >> selectedOption;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return selectedOption;
}


void addBook() {
	string bookTitle, bookAuthor, bookDetail, line;
	int count = 0;

	cout << endl << "\n --- Provide Book Details --- \n " << endl;
	cout << "Title: ";
	getline(cin, bookTitle);
	cout << "Author: ";
	getline(cin, bookAuthor);

	// reading file for number of books
	ifstream countData("library.dat");
	while (getline(countData, line)) {
		count++;
	}

	countData.close();

	// open file for writing
	ofstream writeToLibrary;

	writeToLibrary.open("library.dat", ios::app);

	bookDetail = to_string(count) + "   |  " + bookTitle + "   |    " + bookAuthor;

	// write
	writeToLibrary << bookDetail << endl;

	// close the opened file.
	writeToLibrary.close();

	cout << "Book added: " << bookDetail << endl;
}


void UpdateBook() {
	cout << endl << "--- Update Book --- \n " << endl;
	string id;
	cout << "Enter Book ID: ";
	cin >> id;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	bool bookExist = false;
	ifstream data("library.dat");
	ofstream temp;
	temp.open("temp.dat", ios::app); //Temporary file

	if (!data || !temp)
	{
		cout << "\n Error opening files!" << endl;
		return;
	}

	string strTemp;
	while (getline(data, strTemp))
	{
		size_t found = strTemp.find(id);
		if (found != string::npos) {
			string title, author;

			cout << " \n Book: " << strTemp << endl;

			cout << "\n New Book Title: ";
			getline(cin, title);
			cout << "New Book Author: ";
			getline(cin, author);

			strTemp = id + "    |   " + title + "   |    " + author;
			bookExist = true;
		}
		temp << strTemp << endl;
	}

	data.close();
	temp.close();

	if (bookExist) {
		// delete old file
		if (remove("library.dat") != 0)
			perror("Error deleting file");

		// rename new file to old file
		if (rename("temp.dat", "library.dat")) {
			perror("Error renaming");
			return;
		}

		cout << " \n Book Details Updated" << endl;

	}
	else cout << " \n No book found with ID " << id << endl;
}


void DeleteBook() {
	cout << endl << "--- Delete Book ---" << endl;
	string id;
	cout << "Enter Book ID: ";
	cin >> id;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	bool bookExist = false;
	ifstream data("library.dat");
	ofstream temp;
	temp.open("temp.dat", ios::app); //Temporary file

	if (!data || !temp)
	{
		cout << "Error opening files!" << endl;
		return;
	}

	string strTemp;
	bool delBook = false;
	while (getline(data, strTemp))
	{
		size_t found = strTemp.find(id);
		if (found != string::npos) {
			cout << "Book: " << strTemp << endl;
			bookExist = true;
			delBook = true;
		}
		if (delBook) {
			delBook = false;
			continue;
		}
		temp << strTemp << endl;
	}

	data.close();
	temp.close();

	if (bookExist) {

		// delete old file
		if (remove("library.dat") != 0)
			perror("Error deleting file");

		// rename new file to old file
		if (rename("temp.dat", "library.dat")) {
			perror("Error renaming");
			return;
		}

		cout << "Book Deleted" << endl;

	}
	else cout << "No book found with ID " << id << endl;
}

void show_Issued_books() {
	cout << " \n --- List of Issued books & Return Dates ---" << endl;

	ifstream data("borrow.dat");
	string row;
	cout << "\nBookID  |  Issued To   |   Book - Title   |   Return - Date \n" << endl;
	while (getline(data, row))
	{
		cout << row + " \n " << endl;
	}
}

void showBooks() {
	cout << " \n --- List of books ---" << endl;

	ifstream data("library.dat");
	string row;
	cout << "\nBookID  |  Book Title  | Book Author  \n "<<endl;
	while (getline(data, row))
	{
		
		cout << row  +" \n "<< endl;
	}
	show_Issued_books();
}


//Issue Books to borrowers
void Issue_Book() {
	string Issued_Books,bookTitle, line, Borrower_name, Date_for_return;
	int count = 0;

	cout << endl << "--- Provide Book Details ---" << endl;
	cout << "Title: ";
	getline(cin, bookTitle);
	cout << "Issued To: ";
	getline(cin, Borrower_name);
	cout << "Return Date: ";
	getline(cin, Date_for_return);

	// reading file for number of books
	ifstream countData("library.dat");
	while (getline(countData, line)) {
		count++;
	}

	countData.close();

	// open file for writing
	ofstream writeToBorrow;

	writeToBorrow.open("borrow.dat", ios::app);

	Issued_Books= to_string(count) + "   |    " + Borrower_name + "    |    " + bookTitle + "    |    " + Date_for_return;

	// write
	writeToBorrow<< Issued_Books<< endl;

	// close the opened file.
	writeToBorrow.close();

	cout << "Book Issued Details: " << Issued_Books << "To " << endl;
}

void library_card_holders() {

	cout << " \n --- List of books ---" << endl;

	ifstream data("registered_users.dat");
	string row;
	cout << "\nName of Card Holder    |    Department " << endl;
	while (getline(data, row))
	{

		cout << row + " \n " << endl;
	}

}

void register_cards() {

	string register_card, name, department;
	int count = 0;

	cout << endl << "--- Provide Registration Details ---" << endl;
	cout << "Name: ";
	getline(cin, name);
	cout << "Department: ";
	getline(cin, department);
	
	// reading file for number of books
	ifstream countData("registered_users.dat");
	while (getline(countData, register_card)) {
		count++;
	}

	countData.close();

	// open file for writing
	ofstream writeToBorrow;

	writeToBorrow.open("registered_users.dat", ios::app);

	register_card = to_string(count) + "   |    " + name + "    |    " + department;

	// write
	writeToBorrow << register_card << endl;

	// close the opened file.
	writeToBorrow.close();

	cout << "Register Card: " << register_card << endl;

}


void bookActions(int option) {
	switch (option) {
	case 1:
		addBook();
		break;
	case 2:
		UpdateBook();
		break;
	case 3:
		DeleteBook();
		break;
	case 4:
		showBooks();
		break;
	case 5:
		Issue_Book();
		break;
	case 6:
		show_Issued_books();
		break;
	case 7:
		library_card_holders();
		break;
	case 8:
		register_cards();
		break;
	}
}


void home() {
	int option = bookOptions();
	if (option != 0 && option <= 8) {
		bookActions(option);
	}
	else if (option > 8) {
		cout << endl << "!!! Enter Valid Option (1-8) !!!" << endl;
		option = bookOptions();
	}
	else {
		exit(0);
	}
}


int main() {
	cout << "*** WELCOME ***";
	string yn;
	while (true) {
		cout << endl << "--- Library Management System ---" << endl;
		home();
		cout << endl << "continue? (y/n) :";
		cin >> yn;
		
		if (yn != "y" || "Y") break;
	}
	return 0;
}