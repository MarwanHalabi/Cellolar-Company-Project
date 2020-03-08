#include "CLient.h"

Client::Client(string Client_name=NULL,string id=NULL,int pay=0,int disc=0,string Package_n = NULL,Date D_join=Date(0),double dept_amount=0)
{
	// Asign all parameters.
	C_Name = Client_name;
	ID_num = id;
	Package = Package_n;
	join_date = D_join;
	debt = dept_amount;
	monthly_payment = pay;
	discount = disc;
}
Client::~Client()//Distructor 
{
	Payment_history.clear();// clear payment history.
	C_Number.clear();// clear numbers list.
}
ostream& operator<<(ostream& os, Client& clie)// << operator for client.
{
	list <int> ::iterator itn;
	int count = 0;
	cout << "-----------------------------------------------" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "Client:             " << clie.getClientname() <<" |     ID:  "<< clie.get_ID() << endl;
	cout << "Package:            " << clie.getPackage() << endl;
	cout << "Join Date:          ";
	clie.getDate().show();
	cout << endl;
	cout << "Debt amount:        " << clie.get_debt() << endl;
	cout << "Monthly payment:    " << clie.get_monthly_payment() << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "Phone number:       " << endl;
	itn = clie.C_Number.begin();
	for (itn; itn != clie.C_Number.end(); itn++)
	{
		count++;
		cout << count << " :   0" << *itn << endl;
	}
	cout << "***********************************************" << endl;
	return os;
}
bool Client::check_num(int num)//Check if number is in numbers list.
{
	list <int> ::iterator i;
	i = C_Number.begin();
	for (i; i != C_Number.end(); i++)// go for all numbers.
	{
		if (*i == num)
			return true;
	}
	return false;
 }
void Client::setClientNumber(list <int> num)// sets new numbers list.
{
	list <int> ::iterator itn;
	itn = num.begin();
	for (itn; itn != num.end(); itn++)// go for all numbers.
	{
		C_Number.push_front(*itn);
	}
}
void Client::setPayment_history(map<Date, int> pay_hist)
{
	map<Date, int> ::iterator itn;
	itn = pay_hist.begin();
	for (itn; itn != pay_hist.end(); itn++)// go for all payments.
	{
		Payment_history.insert(pair<Date, int>(itn->first , itn->second)); 
	}
}

void Client::Show_payment_history()
{
	it4 = Payment_history.begin();
	if (it4 != Payment_history.end())
	{
		cout << "The payment history for: " << C_Name << ", ID:  " << ID_num << "." << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "-----------------------------------------------" << endl;
		for (it4; it4 != Payment_history.end(); it4++)
		{
			cout << "Date of Payment:";
			(it4->first).show();
			cout << ",  " << "Payment:  " << (it4->second) << "." << endl;
		}
		cout << "-----------------------------------------------" << endl;
		cout << "-----------------------------------------------" << endl;
	}
	else
	{
		cout << "There is no payments for: " << C_Name << ", ID:  " << ID_num << "." << endl;
	}
	cout << "***********************************************" << endl;
}
void Client::insert_Pay_history(int sum)// pay money and update it's parameter.
{
	Date D;
	debt -= sum; 
	Payment_history.insert(pair<Date, int>(D, sum));
	cout << "Payment_complete";
}
bool operator==(const Client& clie1, const Client& cli2)// == operator
{
	if (clie1.get_ID() == cli2.get_ID())// compares two clients.
		return true;
	else
		return false;
 }
 