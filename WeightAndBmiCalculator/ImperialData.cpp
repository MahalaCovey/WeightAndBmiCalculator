// Mahala Covey
// CIS 1202 800
// May 3, 2024

// Implemenation file for the Imperial Data class.
#include "ImperialData.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

//***********************
// Default constructor. *
//***********************
ImperialData::ImperialData()
{
	weight = 0;
}

//****************************************************
// Overloaded constructor for height in centimeters. *
//****************************************************
ImperialData::ImperialData(double h, double w) : User(h)
{
	weight = w;
}

//********************************************************
// Overloaded constructor for height in feet and inches. *
//********************************************************
ImperialData::ImperialData(double f, double i, double w) : User(f, i)
{
	weight = w;
}

//************************************************************************
// The setWeight member function sets the value of the weight in pounds. *
//************************************************************************
void ImperialData::setWeight(double w)
{
	weight = w;
}

//*******************************************************************
// The getWeight member function returns a User's weight in pounds. *
//*******************************************************************
double ImperialData::getWeight() const
{
	return weight;
}

//********************************************************************************************************************************
// The virtual overriden addRecord member function takes a file name as a parameter and sets the user's weight in imperial units *
// by calling the promptUserForWeight function. A Record is initialized with all the needed information and written to the file. *
//********************************************************************************************************************************
void ImperialData::addRecord(string fileName) 
{
		setWeight(promptUserForWeight(false));
		Record rec = { getHeight(), getIsMetric(), getWeight(), getBmi() };

		ofstream file(fileName, ios::binary | ios::app);
		file.write(reinterpret_cast<char*>(&rec), sizeof(rec));
		file.close();
}

//***************************************************************************************************
// The virtual overriden getBmi member function returns a User's BMI with regard to imperial units. *
//***************************************************************************************************
double ImperialData::getBmi() const
{
	return weight / (pow(getHeight(), 2)) * 703;
}