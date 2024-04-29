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
#include <cmath>


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
User* getDerived(User);
int getMenu();
User::Record readLastRecord(string);
void printAllRecords(string);
void reset(string);
bool fileExists(string);
void viewTable(string, User);


int main()
{
	int menuChoice; // User's menu choice
	User person;    // User's base info
	/*fstream file;*/
	string const fileName = "BmiData.dat";

	if (fileExists(fileName))
	{
		cout << "\nWelcome back. Your last recorded measurements were:" << endl;
		User::Record record = readLastRecord(fileName);
		person.setHeight(record.height);
		person.setIsMetric(record.isMetric);

		// Need to retain height and ismetric val!!! just use readFirstREc! method! Need to create
	}
	else 
	{
		cout << "\nFile doesn't exist." << endl;
		cout << "Creating file..." << endl;
		person = createBaseUser();
	}

	// Handle menu input
	do
	{
		menuChoice = getMenu();

		switch (menuChoice)
		{
		case 1: // Enter new record
		{
			User* userPtr = nullptr;

			if (person.getIsMetric() == true)
			{
				userPtr = new MetricData(person.getHeight(), 0);
			}
			else
			{
				/*int ht = person.getHeight();
				double feet =  ht/ 12;
				int inches = ht % 12;
				user = new ImperialData(feet, inches, 0);*/
				userPtr = new ImperialData(0, person.getHeight(), 0);
			}

			//if (userPtr == nullptr) {
			//	cerr << "Error: Memory allocation failed." << endl;
			//	break; // Exit the case if memory allocation failed
			//}

			//file.open(fileName, ios::out | ios::app | ios::binary);
			//if (!file.is_open()) {
			//	cerr << "Error: Failed to open the file for writing." << endl;
			//	delete userPtr;
			//	break;
			//}

			userPtr->addRecord(fileName);
			/*cout << "metric bmi = " << userPtr->getBmi() << endl;
			showCategory(userPtr->getBmi());*/

			//delete userPtr; // Clean up dynamically allocated memory
			//file.close();
			break;
		}
		case 2: // Before a
			/*cout << "Last Record:" << endl;
			readLastRecord(fileName);*/
			break;
			
		case 3: 
			/*printAllRecords(fileName);*/
			viewTable(fileName, person);
			break;
			
		case 4: // Reset
			reset(fileName);
			break;

		case 5: // Exit
			// Close the file before exiting
			//cout << "Is the file open? " << boolalpha << file.is_open(); // was no
			//file.close();
			break;
		}
	} while (menuChoice != 5);

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
	if (bmi < 18.5)
	{
		cout << "Underweight";
	}
	else if (bmi >= 18.5 && bmi < 24.9)
	{
		cout << "Normal Weight";
	}
	else if (bmi >= 24.9 && bmi < 30)
	{
		cout << "Overweight";
	}
	else
	{
		cout << "Obese";
	}
}

//void printAllRecords(string f) {
//	// Open the file in binary mode
//	ifstream file(f, ios::binary);
//	if (!file.is_open()) {
//		cerr << "Error: Failed to open the file for reading." << endl;
//		return;
//	}
//
//	// Read and print each record in the file
//	User::Record record;
//	cout << "Height" << endl;
//	while (file.read(reinterpret_cast<char*>(&record), sizeof(User::Record))) {
////		cout << "Name: " << record.name << endl;
//		cout << "Height: " << record.height << endl;
//		cout << "Is metric: " << (record.isMetric ? "Yes" : "No") << endl;
//		cout << "Weight: " << record.weight << endl;
//		cout << "BMI: " << record.bmi << endl;
//		cout << endl;
//	}
//
//	// Close the file
//	file.close();
//}
//
User::Record readLastRecord(string fileName) {
	User::Record lastRecord = {};
	// Open the file in binary mode
	ifstream file(fileName, ios::binary);
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
		double ht = lastRecord.height;
		double feet = floor(ht / 12);
		double inches = fmod(ht, 12);
		cout << "Height: " << feet << " feet and " << inches << " inches" << endl;

	}
	cout << "Is metric: " << (lastRecord.isMetric ? "Yes" : "No") << endl;
	cout << "Weight: " << lastRecord.weight << endl;
	cout << "BMI: ";
	printf("%.1f", lastRecord.bmi); // Print to one decimal point
	cout << endl;
	

	return lastRecord;
}

int getMenu()
{
	int choice; // Holds user's menu choice

	// Display the menu
	cout << "1. Enter New Weight" << endl
		<< "2. View Before And After Progress" << endl
		<< "3. View Data Table" << endl
		<< "4. Reset Data" << endl
		<< "5. Exit" << endl;

	// Get menu choice
	cin >> choice;

	// Validate user's menu choice
	while (choice < 1 || choice > 5)
	{
		cout << "ERROR: Please enter a number 1-5: ";
		cin >> choice;
	}

	return choice;
}

void reset(string fileName)
{
	char check;
	filesystem::path filePath{ fileName };

	cout << "Are you sure you want to reset? This will permanently delete all your data. (y/n): ";
	cin >> check;

	// Validate input for check
	while (tolower(check) != 'y' && tolower(check) != 'n')
	{
		cout << "ERROR: Please enter 'y' to reset or 'n' to keep your data: ";
		cin >> check;
	}

	if (tolower(check) == 'y') // Reset
	{
		if (filesystem::remove(fileName))
		{
			cout << "Your data was successfully deleted. After the program exits, enter brand new data by running it again!\n";
			exit(0);
		}
		else
		{
			cout << "There was an error deleting your data\n";
		}
	}
	else // Don't reset
	{
		cout << "Keeping your data for now...\n";
	}

}

bool fileExists(string fileName)
{
	filesystem::path filePath{ fileName };

	if (filesystem::exists(filePath))
		return true;
	else
		return false;
}

void viewTable(string fileName, User user)
{
	ifstream file;

	if (fileExists(fileName))
	{
		string heightType = user.getIsMetric() ? " cm" : " in";
		string weightType = user.getIsMetric() ? "(kg)" : "(lb)";

		file.open(fileName, ios::in | ios::binary);

		file.read(reinterpret_cast<char*>(&user.record), sizeof(user.record));

		cout << setw(30) << "Base Data\n";
		cout << "Height: " << user.getHeight() << heightType << endl << endl;

		cout << setw(32) << "Weight Data\n";
		cout << " Weight " << weightType << "\t\t" << "BMI\t\t" << "Category\n";

		while (!file.eof())
		{
			cout << setw(5) << user.record.weight << setw(20) << " ";
			printf("%.1f", user.record.bmi); // Print to one decimal point
			cout << setw(12) << " ";
			showCategory(user.record.bmi);
			cout << endl;

			file.read(reinterpret_cast<char*>(&user.record), sizeof(user.record));
		}

		cout << endl;


		// test
		cout << "First Record\n";
		file.clear();
		file.seekg(0L, ios::beg); // Seek first record
		file.read(reinterpret_cast<char*>(&user.record), sizeof(user.record));
		cout << setw(5) << user.record.weight << setw(20) << " ";
		printf("%.1f", user.record.bmi); // Print to one decimal point
		cout << setw(12) << " ";
		showCategory(user.record.bmi);
		cout << endl;

		
		cout << "Last Record\n";
		file.clear();
		while (!file.eof())
		{
			file.read(reinterpret_cast<char*>(&user.record), sizeof(user.record));
		}

		cout << setw(5) << user.record.weight << setw(20) << " ";
		printf("%.1f", user.record.bmi); // Print to one decimal point
		cout << setw(12) << " ";
		showCategory(user.record.bmi);
		cout << endl;


		file.close();
	}
	else
	{
		cout << "You need to enter your weight to populate the table.\n";
	}

}
