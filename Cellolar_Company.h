#pragma once
#ifndef  _Cellolar_Company_H
#define _Cellolar_Company_H
#include "Package.h"
#define nominal_price 100;
#define Disc1 5;
#define Disc2 10;
#define Disc3 15;
class Cellular_Company
{
private:
	string Company_name;    // Company name.
	int Packages_count;     // Number of packages.
	int Total_Clients;      // Total clients.
	int Monthly_income;     // Monthly income of company.
	list <int> all_Numbers; // All numbers list.
	list <int> ::iterator itn;// iterator for all numbers list.
	map<string,Client> Clients_database; //map of clients <ID,Client>.
	map<string,Client>::iterator it;     //iteratore map pointeer for Clients.
	map<string,Package> packy;         // map of Packages wtih package name.
	map<string,Package>::iterator it2; //iteratore map pointeer for Packages.
	map<string, string> Customer_retention; // map of Customer retention and thier ID.
	map<string, string>::iterator it3;      //iteratore map pointeer for Customer retention.
public:
	Cellular_Company(string name); // constructor
	~Cellular_Company();//Distructor 
	int get_packages_count()const { return Packages_count; }// returns Package count.
	string get_Company_Name()const { return Company_name; }// returns Company name.
	int get_total_Clients()const { return Total_Clients; }//// returns total clients.
	int get_Monthly_income() const{ return Monthly_income; }//// returns total clients.

	void set_total_Clients(int size) { Total_Clients = size; }// set total clients number.***
	void set_Company_Name(string name) { Company_name = name; }//Set company name.

	bool check_number(int);// Check if number is in the data base.
    void add_client(Client);// Adds a client to the company to specific package.
	void remove_Client(string);// Removes a client from a company.
	string find_id(int ); // find ID by phone number and returns it.

	void debt_warning(string ID); // check debt for client by Id and print warning if there is a debt.
	void debt_update(string ID,int debt); // update debt.
	void Payment(string ID,int sum); // make a Payment for a client.
	void give_discount(string ID, int sum);// give a discount to a client.
	void Payment_history(string ID); // print payment history for specific client.
	void package_description(string ID); // print package description.
	int Discout_option(string ID);  // print Client Discount option for leaving clients.
	int better_price(string ID); // print Client better price option.
	void popular_package();//  print the popular package.
	void remove_number(int);// delete number from client and databases.
	int amount_of_numbers(string);//return amount of numbers for a client.
	void print_Package_clients(string);//print all the clients in specific package.
	void swap_Pack(string, string);//change package for clients.
	void printClient_byID(string); // print client by ID.
	void printClient_by_Phone_num(int);// print Client by phone number.
	void printAll_phones();//print all phones.
	void print_ALL_clients_Packages();//print all the packages with thier clints. 

	friend ostream& operator<<(ostream& os, Cellular_Company& C_C);//<< operator.
	void Run(string);// Run function
	void serialization(string file_out);// serialization to file.
	void desrialization(string file_out);// deserialization from file.
};
#endif