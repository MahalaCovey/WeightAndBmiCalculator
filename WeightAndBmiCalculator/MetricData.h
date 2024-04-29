// Mahala Covey
// CIS 1202 800
// May 3, 2024

// Specification file for the Metric Data class.
#ifndef METRIC_DATA_H
#define METRIC_DATA_H
#include "User.h"	
#include <string>
using namespace std;

class MetricData : public User
{
protected:
	double weight; // Weight in kilograms

public:
	MetricData(); // Default constructor
	MetricData(double, double); // Overloaded constructor for height in centimeters
	MetricData(double, double, double); // Overloaded constructor for height in feet and inches converted to inches
	void setWeight(double);
	double getWeight() const;
	double getBmi() const;
	void addRecord(string);

};
#endif