#include <iostream>
#include "Date.h"

using namespace std;

Date::Date(char d, char m, int y) //Constructor
{
	day = d; month = m; year = y;
	day_number = (year - 1) * 360 + (month - 1) * 30 + day - 1;	//assume 30 days/month, 360 days/year
}

Date::Date(unsigned long Days_n) //Constructor for days since 1/1/0001
{
	day_number = Days_n;
	day = (char)(Days_n % 30 + 1);
	month = (char)((Days_n % 360) / 30 + 1);
	year = Days_n / 360 + 1;
}

Date::Date(const Date& d)  // CC 
{
	day = d.day;
	month = d.month;
	year = d.year;
	day_number = d.day_number;;
}

Date::Date()	// default constructor
{
	time_t rawtime;
	struct tm timeinfo;

	time(&rawtime);					 // time() returns the number of seconds elapsed since midnight (00:00:00), January 1, 1970
	localtime_s(&timeinfo, &rawtime);   // localtime_s converts this time to a structure representing the local time

	year = timeinfo.tm_year + 1900;
	month = timeinfo.tm_mon + 1;
	day = timeinfo.tm_mday;

	day_number = (year - 1) * 360 + (month - 1) * 30 + (day - 1);
}

void Date::show(void) const
{
	printf("%02d/%02d/%04d", day, month, year);
}

long Date::get_day_number(void)const
{
	return day_number;
}

char Date::get_day(void) const
{
	return day;
}
char Date::get_month(void) const
{
	return month;
}
int  Date::get_year() const
{
	return year;
}

void Date::set_day(char d)
{
	if (d<1 || d>30)
	{
		printf("Bad day\n");
		exit(1);
	}
	day_number += day - d;
	day = d;
}
void  Date::set_month(char m)
{
	if (m<1 || m>12)
	{
		printf("Bad month\n");
		exit(1);
	}
	month = m;
	day_number = (year - 1) * 360 + (month - 1) * 30 + day - 1;
}

void  Date::set_year(int y)
{
	if (y<1)
	{
		printf("Bad year\n");
		exit(1);
	}
	year = y;
	day_number = (year - 1) * 360 + (month - 1) * 30 + day - 1;
}

void Date::add(int D)
{
	*this = Date(day_number + D);
}
int Date::compare(const Date& d) const
{
	return (day_number - d.day_number);
}
int Date::Deffrence_in_years(const Date& d) const
{
	return (day_number - d.day_number) / 360;
}

//----------------- not class member ------------
Date from_day_number(unsigned long n)
{
	return Date(n);
}
bool operator<(const Date& d1, const Date& d2)
{
	return (d1.compare(d2) > 0) ? true : false;
}