// Mahala Covey
// CIS 1202 800
// May 3, 2024

// Implemenation file for the User class.
#include "User.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//***********************
// Default constructor. *
//***********************
User::User()
{
	height = 0;
}

//************************************************************************
// Overloaded constructor for height in centimeters.				     *
//************************************************************************
User::User(double h)
{
	/*height = h / 100;*/
	height = h;
	/*setIsMetric(true);*/
	isMetric = true;
}

//****************************************************************************
// Overloaded constructor for height in feet and inches converted to inches. *
//****************************************************************************
User::User(double f, double i)
{
	height = (f * 12) + i;
	/*setIsMetric(false);*/
	isMetric = false;
}


//************************************************************************
// The overloaded setHeight member function sets the value of the height *
// member in centimeters.												 *
// It also sets the isMetric member function to true.					 *
//************************************************************************
void User::setHeight(double h)
{
	/*height = h / 100; */
	height = h;
	/*setIsMetric(true);*/
	isMetric = true;

}

//************************************************************************
// The overloaded setHeight member function sets the value of the height *
// member in feet and inches converted to inches.						 *
// It also sets the isMetric member function to false.					 *
//************************************************************************
void User::setHeight(double f, double i)
{
	height = (f * 12) + i;
	/*setIsMetric(false);*/
	isMetric = false;
}

//*************************************************************************
// The setIsMetric member function sets the value of the isMetric member. *
//*************************************************************************
void User::setIsMetric(bool m)
{
	isMetric = m;
}


//*********************************************************
// The getHeight member function returns a User's height. *
//*********************************************************
double User::getHeight() const
{
	return height;
}

//***************************************************************************
// The getIsMetric member function returns a User's measurement preference. *
//***************************************************************************
bool User::getIsMetric() const
{
	return isMetric;
}

void User::addRecord(string filName)
{
	// Overridden in the derived calsses, MetricData and ImperialData
}

double User::getBmi() const
{
	// Overridden in the derived calsses, MetricData and ImperialData
	return 0;
}

double User::promptUserForWeight(bool isMetric) {
	double inputWeight;
	string units = isMetric ? "kilograms: " : "pounds: ";
	cout << "Enter your weight in " << units;
	cin >> inputWeight;

	// Validate input for weight
	while (inputWeight <= 0)
	{
		cout << "ERROR: Please enter a positive value for your weight: ";
		cin >> inputWeight;
	}
	return inputWeight;
}
