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
#include <cstdlib>
#include <stdint.h>
#include <sstream>
#include <ctime>

// Keep constants here.
#define HOST "courses"
#define USER "putusernamehere"
#define PASSWD "putpasswordhere"
#define DB "myDB"
int orderNumber;
int64_t maxCard = 9999999999999999;
int64_t minCard = 1000000000000000;

// Function prototypes for customer interface.
void PartList(MYSQL *connection);
void AddToCart(MYSQL *connection);
void RemoveFromCart(MYSQL *connection);
void Checkout(MYSQL *connection);

class shoppingCart {
	public:
		// Constructor.
		shoppingCart() {
			batteryAmt = 0;
			alternatorAmt = 0;
			brakesAmt = 0;
			radiatorAmt = 0;
			axleAmt = 0;
			transmissionAmt = 0;
			totalCost = 0;
		}
		// Add to Total Cost Function.
		float addCost(int amount, float cost) {
			return (totalCost += (amount * cost));
		}
		void resetTotal() {
			batteryAmt = 0;
			alternatorAmt = 0;
			brakesAmt = 0;
			radiatorAmt = 0;
			axleAmt = 0;
			transmissionAmt = 0;
			totalCost = 0;
		}

		// Add to Cart Functions.
		int addBattery(int a) {
			return (batteryAmt += a);
		}
		int addAlternator(int a) {
			return (alternatorAmt += a);
		}
		int addBrakes(int a) {
			return (brakesAmt += a);
		}
		int addRadiator(int a) {
			return (radiatorAmt += a);
		}
		int addAxle(int a) {
			return (axleAmt += a);
		}
		int addTransmission(int a) {
			return (transmissionAmt += a);
		}
		
		// Remove from Cart Functions.
		int subBattery(int a) {
			return (batteryAmt -= a);
		}
		int subAlternator(int a) {
			return (alternatorAmt -= a);
		}
		int subBrakes(int a) {
			return (brakesAmt -= a);
		}
		int subRadiator(int a) {
			return (radiatorAmt -= a);
		}
		int subAxle(int a) {
			return (axleAmt -= a);
		}
		int subTransmission(int a) {
			return (transmissionAmt -= a);
		}

		// Obtain total cost of parts.
		float getTotalCost() {
			return totalCost;
		}

		// Obtain current values of parts.
		int getBattery() {
			return batteryAmt;
		}
		int getAlternator() {
			return alternatorAmt;
		}
		int getBrakes() {
			return brakesAmt;
		}
		int getRadiator() {
			return radiatorAmt;
		}
		int getAxle() {
			return axleAmt;
		}
		int getTransmission() {
			return transmissionAmt;
		}

		// Set current values of parts.
		void setBattery(int amount) {
			batteryAmt = amount;
		}
		void setAlternator(int amount) {
			alternatorAmt = amount;
		}
		void setBrakes(int amount) {
			brakesAmt = amount;
		}
		void setRadiator(int amount) {
			radiatorAmt = amount;
		}
		void setAxle(int amount) {
			axleAmt = amount;
		}
		void setTransmission(int amount) {
			transmissionAmt = amount;
		}

	private:
		int batteryAmt;
		int alternatorAmt;
		int brakesAmt;
		int radiatorAmt;
		int axleAmt;
		int transmissionAmt;
		float totalCost;
};

shoppingCart newUser;

using namespace std;

int main() {

	srand(time(0));
	orderNumber = rand() % 100000;
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
				// Send the established connection to RemoveFromCart function.
				RemoveFromCart(connection);
				break;

			case 4:
				// Send the established connection to Checkout function.
				Checkout(connection);
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
	
	cout << endl;
	// Call to print options.
	PartList(connection);

	string partName;
	string queryPart;

	// Object pointer for result set.
	MYSQL_RES *resultSet;

	// Object for single row of result set.
	MYSQL_ROW row;

	// Prompt user for a Part Name and store it in partName.
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
			if(quantity == 0) {
				cout << "No items were to add to cart." << endl;
				exit;
			} else if (quantity < 0) {
				cout << "Invalid value, please try again!" << endl;
			} else if (quantity > inventory) {
				cout << "The quantity selected is greater than the inventory. Try again." << endl;
			}

		} while(quantity <= 0 || quantity > inventory);
		if(partName == "Battery") {
			newUser.addBattery(quantity);
		} else if(partName == "Alternator") {
			newUser.addAlternator(quantity);
		} else if(partName == "Brakes") {
			newUser.addBrakes(quantity);
		} else if(partName == "Radiator") {
			newUser.addRadiator(quantity);
		} else if(partName == "Axle") {
			newUser.addAxle(quantity);
		} else {
			newUser.addTransmission(quantity);
		}
		cout << "Success! " << partName << " in quantity: " << quantity << " was added to your cart." << endl << endl;
		// Once finished with result sets, free up memory.
		mysql_free_result(resultSet);
	}
}

// Function to Remove Product/s from Cart.
void RemoveFromCart(MYSQL *connection) {
	if(newUser.getBattery() <= 0 && newUser.getAlternator() <= 0 && newUser.getBrakes() <= 0 && newUser.getRadiator() <= 0 && newUser.getAxle() <= 0 && newUser.getTransmission() <= 0) {
		cout << "Your cart is empty!" << endl << endl;
		return;
	}
	
	cout << endl;
	// Call to print options.
	PartList(connection);

	string partName;
	string queryPart;

	// Object pointer for result set.
	MYSQL_RES *resultSet;

	// Object for single row of result set.
	MYSQL_ROW row;

	// Prompt user for a Part Name and store it in partName.
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
		int inCart;

		if(partName == "Battery") {
			inCart = newUser.getBattery();
		} else if(partName == "Alternator") {
			inCart = newUser.getAlternator();
		} else if(partName == "Brakes") {
			inCart = newUser.getBrakes();
		} else if(partName == "Radiator") {
			inCart = newUser.getRadiator();
		} else if(partName == "Axle") {
			inCart = newUser.getAxle();
		} else {
			inCart = newUser.getTransmission();
		}

		do {
			cout << "How many? (Enter Part Quantity): ";
			cin >> quantity;
			if(quantity == 0) {
				cout << "No items were to removed from cart." << endl;
				return;
			} else if (quantity < 0) {
				cout << "Invalid value, please try again!" << endl;
			} else if (quantity > inCart) {
				cout << "The quantity selected is greater than the items in the Cart. Try again." << endl;
			}

		} while(quantity <= 0 || quantity > inCart);
		if(partName == "Battery") {
			newUser.subBattery(quantity);
		} else if(partName == "Alternator") {
			newUser.subAlternator(quantity);
		} else if(partName == "Brakes") {
			newUser.subBrakes(quantity);
		} else if(partName == "Radiator") {
			newUser.subRadiator(quantity);
		} else if(partName == "Axle") {
			newUser.subAxle(quantity);
		} else {
			newUser.subTransmission(quantity);
		}
		cout << "Success! " << partName << " in quantity: " << quantity << " was removed to your cart." << endl << endl;
	}
}

// Function to Checkout.
void Checkout(MYSQL *connection) {
	float currentCost;
	string queryPart;
	char * pEnd;
	int inventory;
	// Object pointer for result set.
	MYSQL_RES *resultSet;

	// Object for single row of result set.
	MYSQL_ROW row;

	if(newUser.getBattery() > 0) {

		queryPart = string("SELECT partInventory FROM inventoryDB WHERE partName = 'Battery';");

		// SQL query for parts with specified name.
        	mysql_query(connection, queryPart.c_str());

		// Download whole result set and store it in resultSet.
		resultSet = mysql_store_result(connection);

		row = mysql_fetch_row(resultSet);

		inventory = strtol (row[0],&pEnd,10);

		if(inventory < newUser.getBattery()) {
			newUser.setBattery(inventory);
			newUser.addCost(newUser.getBattery(), 199.95);
			cout << "Your cart had more batteries than we have in stock. It was lowered to: " << newUser.getBattery() << ". Sorry for the Inconvenience." << endl;
			cout << "Battery: " << newUser.getBattery() << endl;
		} else {
			newUser.addCost(newUser.getBattery(), 199.95);
			cout << "Battery: " << newUser.getBattery() << endl;
		}	
		mysql_free_result(resultSet);
	}
	if(newUser.getAlternator() > 0) {
		queryPart = string("SELECT partInventory FROM inventoryDB WHERE partName = 'Alternator';");

		// SQL query for parts with specified name.
        	mysql_query(connection, queryPart.c_str());

		// Download whole result set and store it in resultSet.
		resultSet = mysql_store_result(connection);

		row = mysql_fetch_row(resultSet);

		inventory = strtol (row[0],&pEnd,10);

		if(inventory < newUser.getAlternator()) {
			newUser.setAlternator(inventory);
			newUser.addCost(newUser.getAlternator(), 174.99);
			cout << "Your cart had more alternators than we have in stock. It was lowered to: " << newUser.getAlternator() << ". Sorry for the Inconvenience." << endl;
			cout << "Alternator: " << newUser.getAlternator() << endl;
		} else {
			newUser.addCost(newUser.getAlternator(), 174.99);
			cout << "Alternator: " << newUser.getAlternator() << endl;
		}	
		mysql_free_result(resultSet);
	}
	if(newUser.getBrakes() > 0) {
		queryPart = string("SELECT partInventory FROM inventoryDB WHERE partName = 'Brakes';");

		// SQL query for parts with specified name.
        	mysql_query(connection, queryPart.c_str());

		// Download whole result set and store it in resultSet.
		resultSet = mysql_store_result(connection);

		row = mysql_fetch_row(resultSet);

		inventory = strtol (row[0],&pEnd,10);

		if(inventory < newUser.getBrakes()) {
			newUser.setBrakes(inventory);
			newUser.addCost(newUser.getBrakes(), 154.99);
			cout << "Your cart had more brakes than we have in stock. It was lowered to: " << newUser.getBrakes() << ". Sorry for the Inconvenience." << endl;
			cout << "Brakes: " << newUser.getBrakes() << endl;
		} else {
			newUser.addCost(newUser.getBrakes(), 154.99);
			cout << "Brakes: " << newUser.getBrakes() << endl;
		}	
		mysql_free_result(resultSet);

	}
	if(newUser.getRadiator() > 0) {
		queryPart = string("SELECT partInventory FROM inventoryDB WHERE partName = 'Radiator';");

		// SQL query for parts with specified name.
        	mysql_query(connection, queryPart.c_str());

		// Download whole result set and store it in resultSet.
		resultSet = mysql_store_result(connection);

		row = mysql_fetch_row(resultSet);

		inventory = strtol (row[0],&pEnd,10);

		if(inventory < newUser.getRadiator()) {
			newUser.setRadiator(inventory);
			newUser.addCost(newUser.getRadiator(), 179.95);
			cout << "Your cart had more radiators than we have in stock. It was lowered to: " << newUser.getRadiator() << ". Sorry for the Inconvenience." << endl;
			cout << "Radiator: " << newUser.getRadiator() << endl;
		} else {
			newUser.addCost(newUser.getRadiator(), 179.95);
			cout << "Radiator: " << newUser.getRadiator() << endl;
		}	
		mysql_free_result(resultSet);	
	}
	if(newUser.getAxle() > 0) {
		queryPart = string("SELECT partInventory FROM inventoryDB WHERE partName = 'Axle';");

		// SQL query for parts with specified name.
        	mysql_query(connection, queryPart.c_str());

		// Download whole result set and store it in resultSet.
		resultSet = mysql_store_result(connection);

		row = mysql_fetch_row(resultSet);

		inventory = strtol (row[0],&pEnd,10);

		if(inventory < newUser.getAxle()) {
			newUser.setAxle(inventory);
			newUser.addCost(newUser.getAxle(), 174.99);
			cout << "Your cart had more axles than we have in stock. It was lowered to: " << newUser.getAxle() << ". Sorry for the Inconvenience." << endl;
			cout << "Axle: " << newUser.getAxle() << endl;
		} else {
			newUser.addCost(newUser.getAxle(), 174.99);
			cout << "Axle: " << newUser.getAxle() << endl;
		}	
		mysql_free_result(resultSet);
	}
	if(newUser.getTransmission() > 0) {
		queryPart = string("SELECT partInventory FROM inventoryDB WHERE partName = 'Transmission';");

		// SQL query for parts with specified name.
        	mysql_query(connection, queryPart.c_str());

		// Download whole result set and store it in resultSet.
		resultSet = mysql_store_result(connection);

		row = mysql_fetch_row(resultSet);

		inventory = strtol (row[0],&pEnd,10);

		if(inventory < newUser.getTransmission()) {
			newUser.setTransmission(inventory);
			newUser.addCost(newUser.getTransmission(), 2199.99);
			cout << "Your cart had more transmissions than we have in stock. It was lowered to: " << newUser.getTransmission() << ". Sorry for the Inconvenience." << endl;
			cout << "Transmission: " << newUser.getTransmission() << endl;
		} else {
			newUser.addCost(newUser.getTransmission(), 2199.99);
			cout << "Transmission: " << newUser.getTransmission() << endl;
		}	
		mysql_free_result(resultSet);
	}
	if(newUser.getTotalCost() == 0) {
		cout << "Your Cart is empty!" << endl;
		return;
	}
	cout << "Your total is: " << "$" << fixed << setprecision(2) << newUser.getTotalCost() << endl;

	int64_t creditCard;
	int ccMonth;
	int ccYear;
	string ccM;
	string ccY;
	string card;
	string userName;
	string emailAddress;
	string mailingAddress;
	int count = 0;
	getline(cin, card);
	
	do{
		if(count >= 1) {
			cout << "Wrong card input, try again!" << endl;
			card = "";
		}
		// Prompt user for a Credit Card and store it in creditCard.
		cout << "Enter your Credit Card (Must be 16 digits): ";
		getline(cin, card);
		count++;

	} while(card.length() != 16);
	count = 0;
	do{
		if(count >= 1) {
			cout << "Wrong Month input, try again!" << endl;
			ccM = "";
		}
		// Prompt user for a expiration month.
		cout << "Enter the Expiration Month (Must be one or two digits): ";
		getline(cin, ccM);
		count++;

	} while(ccM.length() > 2);
	count = 0;
	do{
		if(count >= 1) {
			cout << "Wrong Year input, try again!" << endl;
			ccM = "";
		}
		// Prompt user for a expiration year.
		cout << "Enter the Expiration Year (Must be four digits): ";
		getline(cin, ccY);
		count++;

	} while(ccY.length() != 4);

	stringstream yearConvert(ccY);
	yearConvert >> ccYear;
	
	stringstream monthConvert(ccM);
	monthConvert >> ccMonth;

	if(ccYear < 2021) {
		cout << "Verification failed, exiting checkout." << endl;
		orderNumber = rand() % 100000;
		newUser.resetTotal();
		count = 0;
		return;
	} else if(ccYear == 2021 && ccMonth < 12) {
		cout << "Verification failed, exiting checkout." << endl;
		orderNumber = rand() % 100000;
		newUser.resetTotal();
		count = 0;
		return;
	} else if(ccYear > 2100) {
		cout << "Verification failed, exiting checkout." << endl;
		orderNumber = rand() % 100000;
		newUser.resetTotal();
		count = 0;
		return;
	} else if(ccMonth > 12) {
		cout << "Verification failed, exiting checkout." << endl;
		orderNumber = rand() % 100000;
		newUser.resetTotal();
		count = 0;
		return;
	}

	// Prompt user for their name.
	cout << "Enter your name (First and Last): ";
	getline(cin, userName);
	
	// Prompt user for their email address.
	cout << "Enter your email address (Ex. firstName@gmail.com): ";
	getline(cin, emailAddress);

	// Prompt user for their mailing address.
	cout << "Enter your mailing address (Street Name, City, State, Zip Code): ";
	getline(cin, mailingAddress);

	// Current date-time.
	time_t ttime = time(0);
	tm *local_time = localtime(&ttime);

	int realTime = 1900 + local_time->tm_year;
	int realMonth = 1 + local_time->tm_mon;
	string year(to_string(realTime));
	string month;
	if((local_time->tm_mon) < 10) {
		month = "0";
		month += to_string(realMonth);
	} else {
		month += to_string(realMonth);
	}

	string day;
	if((local_time->tm_mday) < 10) {
		day = "0";
		day += to_string(local_time->tm_mday);
	} else {
		day += to_string(local_time->tm_mday);
	}
	string dateTime = year + "-" + month + "-" + day;

	// Convert creditCard string to 64 bit int.
	stringstream cardConvert(card);
	cardConvert >> creditCard;

	string orderNum(to_string(orderNumber));
	string totalCost(to_string(newUser.getTotalCost()));
	queryPart = string("INSERT INTO ordersDB (orderNumber, orderTotal, status, orderDate) VALUES (")+orderNum +string(", ")+totalCost+string(", 'Processing', '")+dateTime+string("');");

	cout << "Order placed! Your order number is: " << orderNum << ". Order was placed on: " << dateTime << ". Your card XXXX XXXX XXXX " << card.substr(12, 15) 
		<< " will be charged: $" << fixed << setprecision(2) << newUser.getTotalCost() << ". Thank you for shopping!" << endl;
	// SQL query for parts with specified name.
        mysql_query(connection, queryPart.c_str());
	orderNumber = rand() % 100000;
	newUser.resetTotal();
	count = 0;
	cout << endl;
}
