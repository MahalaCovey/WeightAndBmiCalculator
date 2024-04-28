// Mahala Covey
// CIS 1202 800
// May 3, 2024

// Specification file for the Imperial Data class.
#ifndef IMPERIAL_DATA_H
#define IMPERIAL_DATA_H
#include "User.h"	
#include <string>
using namespace std;

class ImperialData : public User
{
protected:
	double weight; // Weight in pounds
	string type = "I'm imperial.";

public:
	ImperialData(); // Default constructor
	ImperialData(double, double); // Overloaded constructor for height in centimeters 
	ImperialData(double, double, double); // Overloaded constructor for height in feet and inches converted to inches
	void setWeight(double);
	double getWeight() const;
	double getBmi() const;
	void addRecord(fstream& file);

};
#endif