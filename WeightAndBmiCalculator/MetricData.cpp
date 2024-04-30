// Mahala Covey
// CIS 1202 800
// May 3, 2024

// Implemenation file for the Metric Data class.
#include "MetricData.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
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

//********************************************************************************************************************************
// The virtual overriden addRecord member function takes a file name as a parameter and sets the user's weight in metric units   *
// by calling the promptUserForWeight function. A Record is initialized with all the needed information and written to the file. *
//********************************************************************************************************************************
void MetricData::addRecord(string fileName) 
{
	setWeight(promptUserForWeight(true));
	Record rec = { getHeight(), getIsMetric(), getWeight(), getBmi() };

	ofstream file(fileName, ios::binary | ios::app);
	file.write(reinterpret_cast<char*>(&rec), sizeof(rec));
	file.close();
}

//*************************************************************************************************
// The virtual overriden getBmi member function returns a User's BMI with regard to metric units. *
//*************************************************************************************************
double MetricData::getBmi() const
{
	return weight / (pow((getHeight() / 100), 2));
}