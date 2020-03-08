#pragma once
#include "time.h"

class Date {
private:
	char day, month;
	int year;
	unsigned long day_number;			// days since 1/1/0001
public:
	Date();
	Date(char, char, int);				// Constructor
	Date(unsigned long);
	Date(const Date& d);
	void show(void) const;				// print Date
	long get_day_number(void) const;	// return day_number

	char get_day(void) const;		// return the day
	char get_month(void) const;		// return the month
	int  get_year() const;			// return the year
	void set_day(char);			// set the day
	void set_month(char);			// set the month
	void set_year(int);			// set the year

	int compare(const Date&) const;
	int Deffrence_in_years(const Date&) const;
	void add(int);
	friend bool operator<(const Date&, const Date&);
};

Date from_day_number(unsigned long);