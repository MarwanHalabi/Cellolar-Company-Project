#pragma once
#include "Client.h"
class Package
{
private:
	string Package_name;//Package name.
	int Client_count;   //Client count in this package.
	int Package_price;  //Package Price.
public:
	list <Client> Clients;//list of Clients.
	Package(string, int , int );//Constructor.
	Package(const Package& c);//Copy Constractor.
	~Package(); //Distructor.
	int get_client_count()const { return Client_count; }// Returns client count.
	int get_Package_price()const { return Package_price; }// Returns package Price.
	string get_package_name()const { return Package_name; }// Returns Package name.
	void set_Client_count(int x) { Client_count = x; }// Set client count.
	void set_Package_Price(int x) { Package_price = x; }// set package price.
	void set_Package_Name(string name) { Package_name = name; }// set package name.
	friend ostream& operator<<(ostream&, Package&);// << operator for packages.
};