#pragma once

#include <stdlib.h>
#include <map>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include "string"
#include "Date.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define new DEBUG_NEW

using namespace std;
class Client {
private:
	string C_Name;//Client Name
	string Package;//Package Name
	string ID_num;//ID number
	Date join_date;// Join Date
	double debt;//The debt amount
	int monthly_payment;// monthly payment
	int discount;// discount if available 

public:
	map<Date, int> Payment_history;// map of Payments and dates of payments
	map<Date, int>::iterator it4;//iteratore map pointeer for Payments
	list <int> C_Number;// phones numbers for client.
	Client(string, string,int,int, string, Date, double);//Constractor
	Client(const Client& Cli) :C_Name(Cli.C_Name),ID_num(Cli.ID_num),Package(Cli.Package),
	join_date(Cli.join_date),debt(Cli.debt), discount(Cli.discount), monthly_payment(Cli.monthly_payment),
	C_Number(Cli.C_Number), Payment_history(Cli.Payment_history){};//Copy Constractor
	~Client();//Distructor 
	string getClientname()const { return C_Name; }// Returns Client name.
	string getPackage()const { return Package; }//Returns package name.
	string get_ID()const { return ID_num; }// Returns clients ID.
	Date getDate()const { return join_date; }// Returns Date.
	int get_discount()const { return discount; }// Returns discount.
	double get_debt()const { return debt; }// Returns debt.
	int get_monthly_payment()const { return  monthly_payment; }//Returns  monthly payment amount.
	bool check_num(int num);// check if phone number is belongs client and returns true if yes and false if no.
	void insert_Pay_history(int);//add new payment to payment history.
	void Show_payment_history();// Print payment histroy.
	void setClientname(string name) { C_Name = name; }// sets Client name.
	void set_monthly_payment(int pay) { monthly_payment = pay; }// set 
	void setClientNumber(list <int> num);// Update client numbers list.******
	void setPayment_history(map<Date, int> pay_hist);
	void setdiscount(int disc) { discount = disc; }// set new discount.
	void ADD_Number(int num) { C_Number.push_front(num); }// Add new number to client.
	void remove_Number(int num) { C_Number.remove(num); }// deletes number.
	void set_ID(string ID) { ID_num = ID; }// set client ID.
	void setPackage(string pack) { Package = pack; }// set package name.
	void set_debt(double deb) { debt = deb; }// set debt amount.
	void ADD_debt(double deb) { debt += deb; }// add debt.
	int number_count() const { return C_Number.size(); };// retruns count of numbers
	int client_years() { Date D; return (D.Deffrence_in_years(join_date)); };// return the years of membership for specific client.
	friend ostream& operator<<(ostream& ,  Client& );// << operator.
	friend bool operator==(const Client&, const Client&);// == operator.
};
