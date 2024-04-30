// Mahala Covey
// CIS 1202 800
// May 3, 2024

// Specification file for the User class.
#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User
{
private:
	double height; // Height in centimeters or feet and inches 
	bool isMetric; // Measurment preference in metric units or imperial units

public:
	User(); // Default constructor
	User(double); // Overloaded constructor for height in centimeters
	User(double, double); // Overloaded constructor for height in feet and inches converted to inches
	void setHeight(double); // Overloaded setter for height in centimeters
	void setHeight(double, double); // Overloaded setter for height in feet and inches converted to inches
	void setIsMetric(bool);
	double getHeight() const;
	bool getIsMetric() const;
	double promptUserForWeight(bool);
	virtual void addRecord(string);
	virtual double getBmi() const;
	struct Record // Declaration of structure that is used to read user information to a binary file
	{
		double height;
		bool isMetric;
		double weight;
		double bmi;
	} record;
};
#endif