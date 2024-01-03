/*
Jonatan Ramirez-Marroquin
CSCI 467 Project Part Three
Professor Fatima
*/

// Libraries used in the program.
#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <mysql.h>

// Keep constants here.
#define HOST "courses"
#define USER "putusernamehere"
#define PASSWD "putpasswordhere"
#define DB "myDB"

// Function prototypes for customer interface.
void PartList(MYSQL *connection);
void AddToCart(MYSQL *connection);

using namespace std;

int main() {
	// Library Initialization.
	int sqlInit = mysql_library_init(0, NULL, NULL);

	// Object used for connection to MariaDB.
	MYSQL *connection;

	// Initialize connection to MariaDB.
	connection = mysql_init(NULL);

	// Establish connection to MariaDB, check if not successful.
	if(mysql_real_connect(connection, HOST, USER, PASSWD, DB, 0, NULL, 0) == NULL) {

		// If connection is not successful, print an error.
		cout << "The connection to MariaDB failed. Please try again!\n" << endl;
		exit(EXIT_FAILURE);
	}

	// Ask user for what should be done next.
	int userCommand;

	// Flag to exit loop.
	bool flag = true;

	// Run until user wants to exit.
	while(flag) {
		// Print a menu for the user to select from.
		cout << "********************************************" << endl;
		cout << "*               Report Menu                *" << endl;
		cout << "********************************************" << endl;
		cout << "* 1. List all Auto Parts.                  *" << endl;
		cout << "* 2. Add to Cart.                          *" << endl;
		cout << "* 3. Remove from Cart.                     *" << endl;
		cout << "* 4. Checkout.                             *" << endl;
		cout << "* 5. Exit.                                 *" << endl;
		cout << "********************************************" << endl << endl;

		// Prompt user for next step.
		cout << "Please enter your choice, then press ENTER: ";

		// Store user input in userCommand.
		cin >> userCommand;

		// Switch between the options.
		switch(userCommand) {
			// Part List: Option 1
			case 1:
				// Send the established connection to PartList function.
				PartList(connection);
				break;

			case 2:
				// Send the established connection to AddToCart function.
				AddToCart(connection);
				break;
	
			case 3:
				break;

			case 4:
				break;

			// Exit: Option 5
			case 5:
				cout << "Exit Program." << endl;

				// Set the flag to false to end the loop.
				flag = false;
				break;

			// If anything else is entered.
			default:
				cout << endl;
				cout << "Option not valid, try again!" << endl;
				break;
		}
	}
	mysql_close(connection);
	return 0;
}

// Function to list each auto part from the database including part Name, Description,
// Picture Link, Price, and Availability.
void PartList(MYSQL *connection) {

	// Object pointer for result set.
	MYSQL_RES *resultSet;

	// Object for single row of result set.
	MYSQL_ROW row;

	// SQL query for all auto parts in legacy and inventory database.
	mysql_query(connection, "SELECT partName, partDescription, partPicture, partPrice, partInventory FROM legacyDB JOIN inventoryDB USING (partID);");

	// Download whole result set and store it in resultSet.
	resultSet = mysql_store_result(connection);

	cout << "Part Name        Part Description                                                                       Part Picture Link        " << 
		"  Part Price    In Stock   " << endl;
	cout << "===============  =====================================================================================  =========================" << 
		"  ============  ===========" << endl;	

	// Fetch next row in the result set until NULL.
	while((row = mysql_fetch_row(resultSet)) != NULL) {
		cout << left << setw(15) << row[0] << "  " << setw(85) << row[1] << "  " << setw(25) << row[2] << "  " << setw(12) << row[3] <<
			"  " << setw(11) << row[4] << "\n" << endl;
	}

	// Once finished with result sets, free up memory.
	mysql_free_result(resultSet);
}

// Function to Add Product/s to Cart.
void AddToCart(MYSQL *connection) {
	
	// Call to print options.
	PartList(connection);

	string partName;
	string queryPart;

	// Object pointer for result set.
	MYSQL_RES *resultSet;

	// Object for single row of result set.
	MYSQL_ROW row;

	// Prompt user for a Part Name and store it in partName.
	cout << endl;
	cout << "What Part? (Enter Part Name): ";
	cin.ignore(100, '\n');
	getline(cin, partName);
	
	queryPart = string("SELECT partName FROM inventoryDB WHERE partName = '")+partName+string("';");

	// SQL query for parts with specified name.
        mysql_query(connection, queryPart.c_str());

	// Download whole result set and store it in resultSet.
	resultSet = mysql_store_result(connection);	
	
	row = mysql_fetch_row(resultSet);

	// Check if the result set is empty.
	if(row == NULL) {
		mysql_free_result(resultSet);
		cout << "There are no results with the Part Name " << partName << "." << endl;
	} else {
		// Once finished with result sets, free up memory.
		mysql_free_result(resultSet);

		int quantity;
		char * pEnd;
		int inventory;

		queryPart = string("SELECT partInventory FROM inventoryDB WHERE partName = '")+partName+string("';");

		// SQL query for parts with specified name.
        	mysql_query(connection, queryPart.c_str());

		// Download whole result set and store it in resultSet.
		resultSet = mysql_store_result(connection);

		row = mysql_fetch_row(resultSet);

		inventory = strtol (row[0],&pEnd,10);

		do {
			cout << "How many? (Enter Part Quantity): ";
			cin >> quantity;
			if(quantity <= 0) {
				cout << "Not enough items to add to cart. Try again." << endl;
			} else if (quantity > inventory) {
				cout << "The quantity selected is greater than the inventory. Try again." << endl;
			}

		} while(quantity <= 0 || quantity > inventory);
		// Once finished with result sets, free up memory.
		mysql_free_result(resultSet);
	}
}