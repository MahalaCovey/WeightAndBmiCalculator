// Mahala Covey
// CIS 1202 800
// May 3, 2024

// Implemenation file for the Metric Data class.
#include "MetricData.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//***********************
// Default constructor. *
//***********************
MetricData::MetricData()
{
	weight = 0;
}

//****************************************************
// Overloaded constructor for height in centimeters. *
//****************************************************
MetricData::MetricData(double h, double w) : User(h)
{
	weight = w;
}

//********************************************************
// Overloaded constructor for height in feet and inches. *
//********************************************************
MetricData::MetricData(double f, double i, double w) : User(f, i)
{
	weight = w;
}

//***************************************************************************
// The setWeight member function sets the value of the weight in kilograms. *
//***************************************************************************
void MetricData::setWeight(double w)
{
	weight = w;
}

//**********************************************************************
// The getWeight member function returns a User's weight in kilograms. *
//**********************************************************************
double MetricData::getWeight() const
{
	return weight;
}


//*********************************************************************************
// The getBmi member function returns a User's body mass index from metric units. *
//*********************************************************************************
double MetricData::getBmi() const
{
	return weight / (pow((getHeight() / 100), 2));
}
void MetricData::addRecord(fstream& file) {
	{
		setWeight(promptUserForWeight(true));
		Record rec = { getHeight(), getIsMetric(), getWeight(), getBmi() };

		cout << "metricRecord" << endl; // display to check vals
		cout << "ht= " << getHeight() << endl;
		cout << "is= " << getIsMetric() << endl;
		cout << "ht= " << getHeight() << endl;
		cout << "bmi= " << getBmi() << endl;

		//		file.open("BmiData.dat", ios::out | ios::binary | ios::app);
		ofstream file("BmiData.dat", ios::binary | ios::app);



		file.write(reinterpret_cast<char*>(&rec), sizeof(rec));
		file.close();
		//		updateFileRecord(file, true, getWeight());

	}

}