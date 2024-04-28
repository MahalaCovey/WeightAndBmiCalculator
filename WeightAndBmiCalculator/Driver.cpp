// Mahala Covey
// CIS 1202 800
// May 3, 2024

// Driver for the program.
#include "User.h"
#include "MetricData.h"
#include "ImperialData.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>

using namespace std;

// File record structure 
struct BaseRecord
{
	double height;
	bool isMetric;
	double weight;
};

// Function prototypes
User createBaseUser();
void showCategory(double);
int getMenu();
User::Record readLastRecord();
void printAllRecords(string);

int main()
{
	int menuChoice; // User's menu choice
	User person;    // User's base info
	fstream file;
	string fileName = "BmiData.dat";


	filesystem::path filePath{ fileName };

	if (!filesystem::exists(filePath)) {
		cout << "\nFile doesn't exist." << endl;
		cout << "Creating file..." << endl;
		person = createBaseUser();
	}
	else {
		cout << "\nWelcome back.  Your last recorded measurements were:" << endl;
		User::Record record = readLastRecord();
		person.setHeight(record.height);
		person.setIsMetric(record.isMetric);
	}

	// Handle menu input
	do
	{
		menuChoice = getMenu();

		switch (menuChoice)
		{
		case 1: // Enter new record
		{
			User* user = nullptr;

			if (person.getIsMetric() == true)
			{
				user = new MetricData(person.getHeight(), 0);
			}
			else
			{
				int ht = person.getHeight();
				double feet = ht / 12;
				int inches = ht % 12;
				user = new ImperialData(feet, inches, 0);
			}

			if (user == nullptr) {
				cerr << "Error: Memory allocation failed." << endl;
				break; // Exit the case if memory allocation failed
			}

			file.open(fileName, ios::out | ios::app | ios::binary);
			if (!file.is_open()) {
				cerr << "Error: Failed to open the file for writing." << endl;
				delete user;
				break;
			}

			user->addRecord(file);
			cout << "metric bmi = " << user->getBmi() << endl;
			showCategory(user->getBmi());

			delete user; // Clean up dynamically allocated memory
			file.close();
			break;
		}
		case 2: // Display records from file
			printAllRecords(fileName);
			break;
		case 3:
			cout << "Last Record:" << endl;
			readLastRecord();
			break;
		case 4: // Exit
			// Close the file before exiting
			file.close();
			break;
		}
	} while (menuChoice != 4);

	return 0;
}

User createBaseUser()
{
	User base;
	double height1;
	double height2;
	char measurementType;


	cout << "Welcome!  Would you like to use metric or imperial units? (m/i): ";
	cin >> measurementType;

	// Validate input for measurment type
	while (tolower(measurementType) != 'm' && tolower(measurementType) != 'i')
	{
		cout << "ERROR: Please enter 'm' to use metric units or 'i' to use imperial units: ";
		cin >> measurementType;
	}

	if (tolower(measurementType) == 'm')
	{
		cout << "Enter your height in centimeters: ";
		cin >> height1;

		// Validate input for height
		while (height1 <= 0)
		{
			cout << "ERROR: Please enter a positive value for your height: ";
			cin >> height1;
		}

		base.setHeight(height1);
		base.setIsMetric(true);
	}
	else
	{
		cout << "Enter your height in feet and inches: ";
		cin >> height1 >> height2;

		// Validate input for weight
		while ((height1 + height2) <= 0)
		{
			cout << "ERROR: Please enter positive values for your height: ";
			cin >> height1 >> height2;
		}

		base.setHeight(height1, height2);
		base.setIsMetric(false);

	}

	// Write name and height to file
	BaseRecord baseRec = { base.getHeight() };
	return base;
}


void showCategory(double bmi)
{
	cout << "At " << bmi << ", your current BMI category is ";

	if (bmi < 18.5)
	{
		cout << "underweight.";
	}
	else if (bmi >= 18.5 && bmi < 24.9)
	{
		cout << "normal weight.";
	}
	else if (bmi >= 24.9 && bmi < 30)
	{
		cout << "overweight.";
	}
	else
	{
		cout << "obese.";
	}
}

void printAllRecords(string f) {
	// Open the file in binary mode
	ifstream file(f, ios::binary);
	if (!file.is_open()) {
		cerr << "Error: Failed to open the file for reading." << endl;
		return;
	}

	// Read and print each record in the file
	User::Record record;
	cout << "Height" << endl;
	while (file.read(reinterpret_cast<char*>(&record), sizeof(User::Record))) {
		//		cout << "Name: " << record.name << endl;
		cout << "Height: " << record.height << endl;
		cout << "Is metric: " << (record.isMetric ? "Yes" : "No") << endl;
		cout << "Weight: " << record.weight << endl;
		cout << "BMI: " << record.bmi << endl;
		cout << endl;
	}

	// Close the file
	file.close();
}

User::Record readLastRecord() {
	User::Record lastRecord = {};
	// Open the file in binary mode
	ifstream file("BmiData.dat", ios::binary);
	if (!file.is_open()) {
		cerr << "Error: Failed to open the file for reading." << endl;
		return lastRecord;
	}

	// Get the size of the file
	file.seekg(0, ios::end);
	streampos fileSize = file.tellg();
	file.seekg(0, ios::beg);

	// Check if the file has at least one record
	if (fileSize < static_cast<long long>(sizeof(User::Record))) {
		cerr << "Error: File is empty or does not contain a complete record." << endl;
		file.close();
		return lastRecord;
	}

	// Move the file pointer to the last record
	file.seekg(-static_cast<long long>(sizeof(User::Record)), ios::end);
	if (file.fail()) {
		cerr << "Error: Failed to read the last record." << endl;
		file.close();
		return lastRecord;
	}

	// Read the last record
	file.read(reinterpret_cast<char*>(&lastRecord), sizeof(User::Record));

	// Close the file
	file.close();

	// Print the last record

	if (lastRecord.isMetric) {
		cout << "Height: " << lastRecord.height << " centimeters" << endl;
	}
	else {
		int ht = lastRecord.height;
		double feet = ht / 12;
		int inches = ht % 12;
		cout << "Height: " << feet << " feet and " << inches << " inches" << endl;

	}
	cout << "Is metric: " << (lastRecord.isMetric ? "Yes" : "No") << endl;
	cout << "Weight: " << lastRecord.weight << endl;
	cout << "BMI: " << lastRecord.bmi << endl;
	return lastRecord;
}

int getMenu()
{
	int choice; // Holds user's menu choice

	// Display the menu
	cout << "1. Enter new record" << endl
		<< "2. Display records from file" << endl
		<< "3. Display last record from file" << endl
		<< "4. Exit" << endl;

	// Get menu choice
	cin >> choice;

	// Validate user's menu choice
	while (choice < 1 || choice > 4)
	{
		cout << "ERROR: Please enter a number 1-4: ";
		cin >> choice;
	}

	return choice;
}

