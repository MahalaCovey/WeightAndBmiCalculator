// Mahala Covey
// CIS 1202 800
// May 3, 2024

// Implemenation file for the User class.
#include "User.h"
#include <string>
#include <iostream>
using namespace std;

//***********************
// Default constructor. *
//***********************
User::User()
{
	height = 0;
	isMetric = true; 
	record.height = 0;
	record.isMetric = true; 
	record.weight = 0;
	record.bmi = 0;
}

//****************************************************
// Overloaded constructor for height in centimeters. *
//****************************************************
User::User(double h)
{
	height = h;
	isMetric = true;
	record.height = 0;
	record.isMetric = true;
	record.weight = 0;
	record.bmi = 0;
}

//****************************************************************************
// Overloaded constructor for height in feet and inches converted to inches. *
//****************************************************************************
User::User(double f, double i)
{
	height = (f * 12) + i;
	isMetric = false;
	record.height = 0;
	record.isMetric = true;
	record.weight = 0;
	record.bmi = 0;
}

//************************************************************************
// The overloaded setHeight member function sets the value of the height *
// member in centimeters.												 *
// It also sets the isMetric member function to true.					 *
//************************************************************************
void User::setHeight(double h)
{
	height = h;
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

//*********************************************************************
// The getIsMetric member function returns a User's measurement type. *
//*********************************************************************
bool User::getIsMetric() const
{
	return isMetric;
}

//**************************************************************************
// The virtual addRecord member function takes a file name as a parameter. *
// It writes a Record object to the file.								   *
//**************************************************************************
void User::addRecord(string filName)
{
	// Overridden in the derived calsses, MetricData and ImperialData
}

//***********************************************************
// The virtual getBmi member function returns a User's BMI. *
//***********************************************************
double User::getBmi() const
{
	// Overridden in the derived calsses, MetricData and ImperialData

	return 0;
}

//***************************************************************************************************
// The promptUserForWeight member function takes a boolean value isMetric as a parameter to ask the *
// user to enter their weight in kilograms or pounds, as indicated by the passed in isMetric value. *
// After their input is validated, it is returned.													*
//***************************************************************************************************
double User::promptUserForWeight(bool isMetric) {
	double weight;
	string units = isMetric ? "kilograms: " : "pounds: ";
	cout << "Enter your weight in " << units;
	cin >> weight;

	// Validate weight
	while (weight <= 0)
	{
		cout << "ERROR: Please enter a positive value for your weight: ";
		cin >> weight;
	}

	return weight;
}