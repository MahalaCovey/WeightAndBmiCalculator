// Mahala Covey
// CIS 1202 800
// May 3, 2024

// Implemenation file for the Imperial Data class.
#include "ImperialData.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
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


//***********************************************************************************
// The getBmi member function returns a User's body mass index from imperial units. *
//***********************************************************************************
double ImperialData::getBmi() const
{
	return weight / (pow(getHeight(), 2)) * 703;
}

void ImperialData::addRecord(fstream& file) {
	{
		setWeight(promptUserForWeight(false));
		Record rec = { getHeight(), getIsMetric(), getWeight(), getBmi() };

		int ht = getHeight();
		double feet = ht / 12;
		int inches = ht % 12;

		cout << "impericalRecord" << endl; // display to check vals
		cout << "ht= " << feet << " feet and " << inches << " inches" << endl;
		cout << "is= " << getIsMetric() << endl;
		cout << "wt= " << getWeight() << endl;
		cout << "bmi= " << getBmi() << endl;

		ofstream file("BmiData.dat", ios::binary | ios::app);

		file.write(reinterpret_cast<char*>(&rec), sizeof(rec));
		file.close();

	}

}