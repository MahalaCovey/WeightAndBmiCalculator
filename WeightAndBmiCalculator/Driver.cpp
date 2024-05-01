// Mahala Covey
// CIS 1202 800
// May 3, 2024

/* Program Name: Weight And BMI Calculator
   Program Description: 
   This program stores a user's height and weight in metric or imperial units in a binary file. Their body mass index (BMI) is calculated and displayed
   with their height and weight information, as well as BMI category. They can choose to "reset" their binary file, erasing their data, thus allowing for new input. 
   Program Instructions:
   1) When the program is first run, a user must indicate whether they would like to use metric or imperial units for their data. They are then prompted for their 
   height in either centimeters if they chose metric units, or feet and inches (two numbers separated by a return/enter or space) if they chose imperial units.
   This data is only saved to the binary file once they enter at least one weight value. It is assumed that the user's height and measurement type will not change unless the
   file is reset. 
   2) A menu will then be displayed with options to enter weight values, view their data table, reset their file, and exit. The user can enter as many weight values 
   as they want. After the first weight value is given, they can exit the program and come back to it without needing to enter their old data into the program, as it 
   will be saved to the binary file.
   3) With height, measurement type, and at least one weight value give, the user can display their personal data table, which shows the information they entered
   and indicates their BMI for each weight value and category it falls under, ranging from underweight to obese.
   4) The user can reset their binary file to start from the beginning, allowing them to use a different measurement type and/or height. */

// Driver for the program.
#include "User.h"
#include "MetricData.h"
#include "ImperialData.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem> // For filesystem::path and filesystem::exists (C++20 Standard is used for this project)
#include <cmath>
using namespace std;

// Function prototypes
bool fileExists(string);
User createBaseUser();
int getMenu();
void viewTable(string, User);
void reset(string);
void showCategory(double);
User::Record getFirstRecord(string);
User::Record getLastRecord(string);

int main()
{
	int menuChoice; // User's menu choice
	User person;    // User's base info (height and measurement type)
	string const fileName = "BmiData.dat";

	// If the file exists, the user already entered their height and measurement type. The getFirstRecord function is called to load the 
	// user's height and measurement type from the file into the User person object for future BMI calculations.
	if (fileExists(fileName))
	{
		cout << "Welcome back!\n";
		User::Record base = getFirstRecord(fileName);
		person.setHeight(base.height);
		person.setIsMetric(base.isMetric);
	}

	// If the file does not exist, the User person object is initialized through the createBaseUser function, which gets height and
	// measurement type directly from the user.
	else 
	{
		person = createBaseUser();
	}

	// Handle menu input
	do
	{
		menuChoice = getMenu();

		switch (menuChoice)
		{
		case 1: // Enter New Weight
		{
			User* userPtr = nullptr;

			if (person.getIsMetric() == true)
			{
				userPtr = new MetricData(person.getHeight(), 0);
			}
			else
			{
				userPtr = new ImperialData(0, person.getHeight(), 0);
			}
			userPtr->addRecord(fileName);
			break;
		}
			
		case 2: // View Data Table
			viewTable(fileName, person);
			break;
			
		case 3: // Reset
			reset(fileName);
			break;
		}

	} while (menuChoice != 4);

	return 0;
}

//*************************************************************************************************************************************************
// The fileExists function takes a file name as a parameter and returns true if it exists within the program's directory or false if it does not. *
//*************************************************************************************************************************************************
bool fileExists(string fileName)
{
	filesystem::path filePath{ fileName };

	if (filesystem::exists(filePath))
		return true;
	else
		return false;
}

//***********************************************************************************************************************
// The createBaseUser function prompts the user for their measurement type, metric or imperial units, and their height. *
// After their input is validated, the User object is returned.															*
//***********************************************************************************************************************
User createBaseUser()
{
	User base;
	double height1;
	double height2;
	char measurementType;


	cout << "Nice to meet you! Let's start by getting your height.\nWould you like to use metric or imperial units? (m/i): ";
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
		cout << "Enter your height in feet and then inches: ";
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

	cout << "Thank you for letting me know how tall you are!\nPlease see the menu below and enter at least one weight value to save your data.\n";

	return base;
}

//***********************************************************************************************************************************
// The getMenu function displays a menu of choices, prompts and validates the user for a menu choice, and returns that menu choice. *
//***********************************************************************************************************************************
int getMenu()
{
	int choice; // Holds user's menu choice

	// Display the menu
	cout << "\n1. Enter New Weight\n"
		<< "2. View Data Table\n"
		<< "3. Reset Data\n"
		<< "4. Exit\n"
		<< "Enter your menu choice: ";

	// Get menu choice
	cin >> choice;

	// Validate user's menu choice
	while (choice < 1 || choice > 4)
	{
		cout << "ERROR: Please enter a number 1-4: ";
		cin >> choice;
	}

	cout << endl;

	return choice;
}

//************************************************************************************************************************
// The viewTable function takes a file name and User object as parameters. If the file exists, it is read to display the *
// records containing the user's height, weight and BMI. The results are formatted in an attractive table.				 *
// If the file does not exist, the user is informed that they must first enter their weight to see the table.		     *
//************************************************************************************************************************
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

		file.close();
	}
	else
	{
		cout << "You need to enter your weight to populate the table.\n";
	}
}

//***********************************************************************************************************************************************
// The reset function takes a file name as a parameter. After ensuring the file exists and the user wants to reset their data, the file name is *
// used to delete the file. The program then exits so the user can enter new data upon running the program again.								*
//***********************************************************************************************************************************************
void reset(string fileName)
{
	char check; // Holds user's decision to reset
	filesystem::path filePath{ fileName };

	if (fileExists(fileName))
	{
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
				cout << "ERROR: There was an issue deleting your data.\n";
			}
		}
		else // Don't reset
		{
			cout << "Keeping your data for now...\n";
		}
	}
	else
	{
		cout << "ERROR: You cannot reset your data because your data has not been saved. To save your data, enter your weight.\n";
	}
}

//***********************************************************************************************************************
// The showCategory function takes a BMI value as a parameter. The BMI is compared to its appropriate category, ranging *
// from underweight to obese, and printed out.																			*
//***********************************************************************************************************************
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

//**************************************************************************************************************************
// The getFirstRecord function takes a file name as a parameter. The file is read to retrieve the first record in the file *
// and returned as a User Record object.																				   *
//**************************************************************************************************************************
User::Record getFirstRecord(string fileName)
{
	ifstream file;
	User::Record firstRec = {};

	file.open(fileName, ios::in | ios::binary);

	file.clear();
	file.seekg(0L, ios::beg); // Seek first record
	file.read(reinterpret_cast<char*>(&firstRec), sizeof(firstRec));
	file.close();

	return firstRec;
}

//*************************************************************************************************************************
// The getFirstRecord function takes a file name as a parameter. The file is read to retrieve the last record in the file *
// and returned as a User Record object.																				  *
//*************************************************************************************************************************
User::Record getLastRecord(string fileName)
{
	ifstream file;
	User::Record lastRec = {};

	file.open(fileName, ios::in | ios::binary);

	file.clear();
	while (!file.eof()) 
	{
		file.read(reinterpret_cast<char*>(&lastRec), sizeof(lastRec)); // Reads last record after loop is at the end of the file
	}
	file.close();

	return lastRec;
}