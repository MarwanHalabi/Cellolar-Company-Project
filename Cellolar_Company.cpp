#include "Cellolar_Company.h"
#include <iostream>
using namespace std;


Cellular_Company::Cellular_Company(string name="NULL") /*:storage_amount(0)*/
{
	//Assign parameters.
	Total_Clients = 0;
	Monthly_income = 0;
	Company_name = name;
	Packages_count = 0;
}


Cellular_Company::~Cellular_Company()//Distructor 
{
	//Clear all databases
	Clients_database.clear();
	packy.clear();
	Customer_retention.clear();
	all_Numbers.clear();
}


void Cellular_Company::add_client(Client Clie)
{
	char input; // input variable.
	int  num;   // num variable.
	int bounus_discount=0; // bounus dicount if available.
	bool flag = true, flag2=true; // flags.
	it = Clients_database.find(Clie.get_ID());//find Client in database.
	it2 = packy.find(Clie.getPackage());//package in data \base.
	it3 = Customer_retention.find(Clie.get_ID());//find client in Customer retention.
	cout << endl << endl;
	cout << "***********************************************" << endl;
	cout << endl;
	if (it != Clients_database.end())//check if Client found at map clients
	{
		cout << "The Client already in the system!!" << endl;
		flag2 = false;
	}
	else // if the client no found check the client numbers.
	{
		list <int>::iterator it4;
		list <int> remove_numbers;
		for (it4 = Clie.C_Number.begin(); it4 != Clie.C_Number.end(); it4++) // go for all client numbers.
		{
			if (check_number(*it4)) // check number.
			{
				cout << "This Number: 0" << *it4 << " already in use!!, Do you want another number instead?  Y/N" << endl;
				cin >> input;// get char input.
				if (input == 'y' || input == 'Y') // check input.
				{
					while (flag)// offer new number instead of the given number.
					{
						num = rand() % 9999999 + 520000000;
						if (!check_number(num))
						{
							cout << "Would you like to get this number: 0" << num << " ?  Y/N" << endl;
							cin >> input;
							if (input == 'y' || input == 'Y')
							{
								Clie.ADD_Number(num);
								flag = false;
								all_Numbers.push_front(num);
							}
						}
					}
				}
				cout << "The number: 0"<< *it4 <<" has ben removed form client numbers database" << endl;
				remove_numbers.push_front(*it4); // add numbers that we want to delete.
				}
			else
			{
				all_Numbers.push_front(*it4); // add number to all numbers list.
			}
		}
		for (it4=remove_numbers.begin(); it4 != remove_numbers.end(); it4++)// go for number in remove numbers list.
		{
			Clie.remove_Number(*it4);
		}
	}
	if (flag2)
	{
		if (it3 != Customer_retention.end())// add discount if the coustmer was coustmer in the past.
		{
			bounus_discount = 10; 
			cout<<"You was our client in the past so you got discount for every number of: "<< bounus_discount <<"."<<endl;
		}
		Clie.setdiscount(bounus_discount);

		if (it2 != packy.end())//if Package name found
		{
			list<Client>::iterator i;
			(it2->second).set_Client_count((it2->second).get_client_count() + 1);//add client to available package.
			Clie.set_monthly_payment (((it2->second).get_Package_price()- bounus_discount)*Clie.number_count());// set monthly payment/
			(it2->second).Clients.push_front(Clie);// add client to package.
			cout << "Your package price is :" << (it2->second).get_Package_price() << endl;// print package price.
			cout << "The monthly price will be :" << Clie.get_monthly_payment() << endl;// print package price.

		}
		else//if Package name not found add new package with proper price. and add the client to it.
		{
			int pack_price= nominal_price;
			pack_price = (int)(pack_price -(double)(Clie.C_Number.size()*2/(25))*pack_price); // calculate price of package.
			Package pack(Clie.getPackage(),1, pack_price); //constract new package.
			cout << "Your package price is :" << pack_price << endl;// print package price.
			Clie.set_monthly_payment((pack_price- bounus_discount)*Clie.number_count());// set monthly payment of client.
			cout << "The monthly price will be :" << Clie.get_monthly_payment() << endl;// print package price.
			pack.Clients.push_front(Clie); // add client to the proper package.
			packy.insert(pair<string, Package>(Clie.getPackage(), pack)); // add package to the company
			Packages_count++; // count + 1 packages.
		}
		Monthly_income += Clie.get_monthly_payment(); // update mothly income.
		Clients_database.insert(pair<string, Client>(Clie.get_ID(), Clie)); // add client to database.
		Total_Clients++; // update total client count
		cout << "The System added the client!!" << endl;
		cout << endl;
		cout << "***********************************************" << endl;
	}
}


void Cellular_Company::remove_Client(string ID)
{
	char input;
	it = Clients_database.find(ID);
	cout << endl << endl;
	cout << "***********************************************" << endl;
	cout << endl;
	if (it != Clients_database.end()) // Check if client found.
	{
		it2 = packy.find((it->second).getPackage());// find package of client
		if ((it->second).get_debt() > 0) // check if there is a debt for this client.
		{
			cout << "There is a debt for this client!!, Do you want to pay it ?   Y/N" << endl; // ask  if they want to pay.
			cin >> input;
			if (input == 'y' || input == 'Y')// check input.
			{
				Customer_retention.insert(pair<string, string>(ID, (it->second).getClientname()));//add client to customer retention.
				itn = (it->second).C_Number.begin();
				for (itn; itn !=(it->second).C_Number.end(); itn++)// go for number and remove them.
				{
					all_Numbers.remove(*itn);
				}
				(it2->second).Clients.remove((it->second));//remove client form package.
				(it2->second).set_Client_count((it2->second).get_client_count() - 1);// set client count in package.
				Monthly_income -= (it->second).get_monthly_payment();// update monthly income of the company.
				Total_Clients--;// update total client.
				Clients_database.erase(it);// delete client from clients database.
				cout << "The system removed the client!! " << endl;
			}
			else// client don't want to pay debt.
			{
				cout << "The system can't remove this client because he has a debt!! " << endl;
			}
		}
		else// if there is no debt.
		{
			list <int> ::iterator itn;
			itn = (it->second).C_Number.begin();
			for (itn; itn != (it->second).C_Number.end(); itn++)// go for all numbers.
			{
				all_Numbers.remove(*itn);
			}
			Customer_retention.insert(pair<string, string>(ID, (it->second).getClientname()));// add client to customer retention.
			(it2->second).Clients.remove((it->second));// remove client from package.
			(it2->second).set_Client_count((it2->second).get_client_count() - 1);//update client count.
			Monthly_income -= (it->second).get_monthly_payment();// update monthly income.
			Total_Clients--;// update total clients.
			Clients_database.erase(ID);// delete client from data base.
			cout << "The system removed the client!! " << endl;		
		}
	}
	else
	{
		cout << "Client not found" << endl;
	}
	cout << endl;
	cout << "***********************************************" << endl;
}


void Cellular_Company::popular_package()// print the most popular package.
{
	int sum = 0,price=0;
	bool flag = false;
	string pack_name;
	it2 = packy.begin();
	for (it2; it2 != packy.end(); it2++) // go for all packages.
	{
		if (it2->second.get_client_count() > sum)// check if the client number are above sum.
		{
			sum = it2->second.get_client_count();
			pack_name = it2->second.get_package_name();
			price = it2->second.get_Package_price();
			flag = true;
		}
	}
	if (flag)
		cout << "The most popular package is: " << pack_name << " , Clients count: " << sum << " , Package Price:  " << price << "." << endl;// print pack.
	else
		cout << " There is no package available!!" << endl;
}


bool Cellular_Company::check_number(int num)// Check if number is in the data base.
{
	for (itn = all_Numbers.begin(); itn != all_Numbers.end(); itn++) // go for all numbers.
	{
		if (*itn == num)
		{
			return true;
		}
	}
	return false;
}


string Cellular_Company::find_id(int num)// find ID by phone number and returns it.
{
	it = Clients_database.begin();
	for (it; it != Clients_database.end(); it++) // gor for all clients.
	{
		if ((it->second).check_num(num)) // check if number is inside client.
			return (it->first);
	}
	return "NULL";
}


void Cellular_Company::remove_number(int num)
{
	string ID;
	ID = find_id(num);
	if (ID!="NULL")
	{
		it = Clients_database.find(ID);
		if ((it->second).C_Number.size() == 1)// if there is just one number.
			remove_Client(ID);
		else
		{
			(it->second).remove_Number(num); // remove number.
			all_Numbers.remove(num);// remove number from list.
			it2 = packy.find((it->second).getPackage()); // find package of this client
			Monthly_income -= (it->second).get_monthly_payment();// update monthly income.
			(it->second).set_monthly_payment((it->second).get_monthly_payment() - ((it2->second).get_Package_price()-(it->second).get_discount()));// update monthly payment.
			Monthly_income += (it->second).get_monthly_payment();
		}
	}
	else//client not found.
	{
		cout << "Number not found" << endl;
	}
}


int Cellular_Company::amount_of_numbers(string id) // return the amount of numbers of client.
{
	it = Clients_database.find(id);
	if (it != Clients_database.end())
		return (it->second).number_count(); 
	else
		cout << "The client not found" << endl;
	return 0;
}


void Cellular_Company:: print_Package_clients(string pack)// print all clients in specific package.
{
	it2 = packy.find(pack);
	if (it2 != packy.end())
		cout << it2->second << endl;
	else
		cout << "package not found." << endl; 
}


void Cellular_Company::swap_Pack(string ID, string Pack)// swap package of a client.
{
	it = Clients_database.find(ID);
	it2 = packy.find((it->second).getPackage());
	if (it != Clients_database.end())// if client not found.
	{
		if ((it2->first) == Pack)
		{
			cout << "You have entered the same package of this client." << endl;
		}
		else
		{
			if (packy.find(Pack) != packy.end())
			{
				(it2->second).Clients.remove(it->second);
				it2->second.set_Client_count(it2->second.get_client_count() - 1);// set client count.
				it2 = packy.find(Pack);// find pack.
				(it2->second).Clients.push_front(it->second);// push clients to new package.
				(it2->second).set_Client_count((it2->second).get_client_count() + 1);
				Monthly_income -= (it->second).get_monthly_payment();// update monthly income.
				(it->second).set_monthly_payment((it->second.C_Number.size())*((it2->second).get_Package_price() - (it->second).get_discount()));// update monthly payment for a client.
				Monthly_income += (it->second).get_monthly_payment();// update monthly income.
			}
			else
			{
				cout << "Package not found so the swap didn't done" << endl;
			}
		}
	}
	else
		cout << "The client not found" << endl;
}


void Cellular_Company::debt_warning(string ID)// if client has a debt print a messege.
{
	it = Clients_database.find(ID);
	if (it != Clients_database.end())
	{
		cout << "Client name:  " << (it->second).getClientname() << "." << endl << "ID:  " << (it->second).get_ID() << "."
			<< endl<< "The debt: " << (it->second).get_debt() << "." << endl;
	}
	else
		cout << "The client not found" << endl;
}

void Cellular_Company::debt_update(string ID, int debt) // update debt.
{
	it = Clients_database.find(ID);
	if (it != Clients_database.end())
	{
		it->second.ADD_debt(debt);
	}
	else
		cout << "The client not found" << endl;
}

void Cellular_Company::Payment(string ID, int sum)// make a payment for a specefic client.
{
	it = Clients_database.find(ID);
	if (it != Clients_database.end())
	{
		if (it->second.get_debt() < sum)// check if debt is less than sum.
		{
			cout << "you have payed " << it->second.get_debt() << " amount and you will get "<< sum-it->second.get_debt()<<" back." << endl;
			(it->second).insert_Pay_history((int)it->second.get_debt());//pay
			cout << "The data after payment:  " << endl;
			debt_warning(ID);
		}
		else
		{
			cout << "you have payed " << sum << " amount." << endl;
			(it->second).insert_Pay_history(sum);//pay
			cout << "The data after payment:  " << endl;
			debt_warning(ID);
		}
	}
	else
		cout << "The client not found" << endl;
}


void Cellular_Company::Payment_history(string ID)// print payment histroy of a client.
{
	it = Clients_database.find(ID);
	if (it != Clients_database.end())
	{
		(it->second).Show_payment_history();
	}
	else
		cout << "The client not found" << endl;
}


void Cellular_Company::package_description(string ID)// prin package description of specific client.
{
	it = Clients_database.find(ID);
	if (it != Clients_database.end())
	{
		it2 = packy.find(it->second.getPackage());
		cout << it2->second << endl;
		cout << "With discount of :" << it->second.get_discount() << "." << endl;
		cout << "The final price per number is :" << (it2->second).get_Package_price()-(it->second).get_discount() << "." << endl;

	}
	else
		cout << "The client not found" << endl;
}


void Cellular_Company::print_ALL_clients_Packages()//print all the products at the category
{
	int cnt = 0;
	it2 = packy.begin();
	if (it2 != packy.end())
	{
		for (it2; it2 != packy.end(); it2++)
		{
			cnt++;
			cout << "Package No' :  " << cnt <<" "<< (it2->second) << endl;
		}
	}
	else
		cout << "There is no package in this company."<< endl;

	
}


int Cellular_Company::better_price(string ID)// print and retrurn discount for better price for a client that want to check.
{
	Date D;
	int exp;
	int disc=0;
	it = Clients_database.find(ID);
	if (it != Clients_database.end())
	{
		it2 = packy.find(it->second.getPackage());
		exp = it->second.getDate().Deffrence_in_years(D);// calculate number of years in membership
		if ((exp >= 1) && (exp < 3))
		{
			disc = it->second.get_discount() +   Disc1;
			cout << "Discount option new Discount:" << disc << "." << endl;
			cout << "So The final price would be: :" << (it2->second.get_Package_price() - disc) << "." << endl;
		}
		else if (((exp >= 3) && (exp < 5)))
		{
			disc = it->second.get_discount()+ Disc2;
			cout << "Discount option new Discount:" << disc << "." << endl;
			cout << "So The final price would be: :" << (it2->second.get_Package_price() - disc) << "." << endl;
		}
		else if ((exp >= 5))
		{
			disc = it->second.get_discount()+ Disc3;
			cout << "Discount option new Discount:" << disc << "." << endl;
			cout << "So The final price would be: :" << (it2->second.get_Package_price() - disc )<< "." << endl;
		}
		else
		{
			cout << "There is no bounos discount available" << endl;
		}
	}
	return disc; //return discount
}


void Cellular_Company::give_discount(string ID, int sum)// give discount to a client
{
	it = Clients_database.find(ID);
	if (it != Clients_database.end())
	{
		it2 = packy.find(it->second.getPackage());
		Monthly_income -= it->second.get_monthly_payment(); // update mothly income.
		it->second.set_monthly_payment((it->second.get_monthly_payment() - sum));
		it->second.setdiscount(it->second.get_discount()+sum);
		Monthly_income += it->second.get_monthly_payment(); // update mothly income.
	}
	else
	{
		cout << "The client not found" << endl;
	}
}


int Cellular_Company::Discout_option(string ID)//  retrun a discount option for a client who want to leave.
{
	Date D;
	int exp;
	int disc=5;
	it = Clients_database.find(ID);
	if (it != Clients_database.end())
	{
		it2 = packy.find(it->second.getPackage());
		exp = it->second.getDate().Deffrence_in_years(D);
		if ((exp >= 1) && (exp < 3))
		{
			disc = it->second.get_discount() + Disc1;
		}
		else if (((exp >= 3) && (exp < 5)))
		{
			disc = it->second.get_discount() + Disc2;
		}
		else if ((exp >= 5))
		{
			disc = it->second.get_discount() + Disc3;
		}
		cout << "Discount option new Discount:" << disc << "." << endl;
		cout << "So The final price would be: :" << (it2->second.get_Package_price() - disc) << "." << endl;
	}
	return disc;
}


void Cellular_Company::printClient_byID(string ID)// print a client by ID
{
	it = Clients_database.find(ID);
	if (it != Clients_database.end())
	{
		cout << it->second << endl;
	}
	else
	{
		cout << "Client not found!!" << endl;
	}
}


void Cellular_Company::printClient_by_Phone_num(int num)// print a client by phone number.
{
	string Id = find_id(num);
	if (Id == "NULL")
		cout << "Client not found!!" << endl;
	else
	{
		it = Clients_database.find(Id);
		cout << it->second << endl;
	}
}


void Cellular_Company::printAll_phones()// print all phones in company
{
	itn = all_Numbers.begin();
	int  count = 0;
	for(itn;itn!= all_Numbers.end();itn++)
	{
		count++;
		cout << "Phone NO" << count << "  :0" << *itn << endl;
	}
}


ostream& operator<<(ostream& os, Cellular_Company& C_C)// << operator 
{
	map<string, Package>::iterator i = C_C.packy.begin();
	cout << "***********************************************" << endl;
	cout << "***********************************************" << endl;
	cout << " Company name is              :  " << C_C.Company_name << endl;
	cout << " Number of packges is         :  " << C_C.Packages_count << endl;
	cout << " Number of Clients            :  " << C_C.Total_Clients << endl;
	cout << " Monthly income of the company:  " << C_C.Monthly_income << endl;
	cout << "***********************************************" << endl;
	cout << "***********************************************" << endl;
	for (i; i != C_C.packy.end(); i++)
		cout << i->second << endl;

	cout << "***********************************************" << endl;
	return os;
}


void Cellular_Company::Run(string file="NULL") // Run function- simulation.
{
	
	int temp, flag = 1;
	char input;
	string company_name, catName;
	if (file != "NULL")
	{
		cout << "Do you want to read from file?  Y/N" << endl;
		cin >> input;

		if (input == 'y' || input == 'Y')
		{

			desrialization(file);
		}
	}
	if (Company_name != "NULL")
	{
		cout << "----- WELCOME TO " << Company_name << " Company -----" << endl;
	}
	else
	{
		cout << "Please enter company name!!" << endl;
		cin >> company_name;
		cout << "----- WELCOME TO " << Company_name << " Company -----" << endl;
	}
	while (flag)
	{
		// print all options.
		system("cls");
		cout << "+++++     MENU     +++++" << endl;
		cout << "0.  EXIT." << endl;
		cout << "1.  Add new client." << endl;
		cout << "2.  Remove client." << endl;
		cout << "3.  Check client debt." << endl;
		cout << "4.  Show client informations." << endl;
		cout << "5.  Show payments history of client." << endl;
		cout << "6.  client package details." << endl;
		cout << "7.  Discount option." << endl;
		cout << "8.  Package for leaving clients." << endl;
		cout << "9.  Show popular package." << endl;
		cout << "10. Show client by number." << endl;
		cout << "11. Show client numbers by ID." << endl;
		cout << "12. Show all packages." << endl;
		cout << "13. Make a payment for a client!!." << endl; 
		cout << "14. Update client debt." << endl; 
		cout << "15. Print all numbers." << endl; 
		cout << "16. Add package to company." << endl;
		cout << "17. Change company name." <<  endl;
		cout << "18. Give discount to a client." << endl;
		cout << "19. remove a number." << endl;
		cout << "20. Swap Pack for a client." << endl << endl;

		cout << "Enter your option :" << endl;

		cin >> temp;

		switch (temp)
		{
		case 0:
			return;
		case 1:
		{
			string C_Name, Package, ID_num;
			list <int> C_Number;
			Date join_date;
			int num_cnt, number;
			system("cls");
			cout << "Please enter the client name!!" << endl;
			cin >> C_Name;
			cout << "Please enter the client ID!!" << endl;
			cin >> ID_num;
			cout << "Please enter the package Name!!" << endl;
			cin >> Package;
			cout << "Please enter the how many numbers you want to add!!" << endl;
			cin >> num_cnt;
			for (int i = 0; i < num_cnt; i++)
			{
				cout << "Please enter the " << i + 1 << " number : " << endl;
				cin >> number;
				C_Number.push_front(number);
			}
			Client Clie(C_Name, ID_num, 0, 0, Package, join_date, 0);
			Clie.setClientNumber(C_Number);
			add_client(Clie);
			break;
		}
		case 2:
		{
			system("cls");
			string ID_num;
			cout << "Please enter the ID of the client you want to remove" << endl;
			cin >> ID_num;
			remove_Client(ID_num);
			break;
		}
		case 3:
		{
			system("cls");
			string ID_num;
			cout << "Check Client dept for client, please enter a Id number:" << endl;
			cin >> ID_num;
			debt_warning(ID_num);
			break;
		}
		case 4:
		{
			system("cls");
			string ID_num;
			cout << "Show Client information, please enter a Id number:" << endl;
			cin >> ID_num;
			printClient_byID(ID_num);
			break;
		}
		case 5:
		{
			system("cls");
			string ID_num;
			cout << "Show Client information, please enter a Id number:" << endl;
			cin >> ID_num;
			Payment_history(ID_num);
			break;
		}
		case 6:
		{
			system("cls");
			string ID_num;
			cout << "Show Client's Package details, please enter a Id number:" << endl;
			cin >> ID_num;
			package_description(ID_num);
			break;
		}
		case 7:
		{
			system("cls");
			string ID_num;
			cout << "Show if there is any possible discount, please enter a Id number:" << endl;
			cin >> ID_num;
			better_price(ID_num);
			break;
		}
		case 8:
		{
			system("cls");
			string ID_num;
			cout << "Show package for leaving client, please enter a Id number:" << endl;
			cin >> ID_num;
			Discout_option(ID_num);
			break;
		}
		case 9:
		{
			system("cls");
			cout << "popular package:" << endl;
			popular_package();
			break;
		}
		case 10:
		{
			system("cls");
			int num;
			cout << "Show client details by number, please enter a phone number:" << endl;
			cin >> num;
			printClient_by_Phone_num(num);
			break;
		}
		case 11:
		{
			system("cls");
			cout << *this << endl;
			break;
		}
		case 12:
		{
			system("cls");
			cout << "Showing all packges of the company below:  " << endl;
			print_ALL_clients_Packages();
			break;
		}
		case 13:
		{
			system("cls");
			string ID_num;
			int sum;
			cout << "You choosed to make a payment for specific client, please enter Id number :  " << endl;
			cin >> ID_num;
			cout << " please enter the amount of money you want to pay : " << endl;
			cin >> sum;
			Payment(ID_num, sum);
			break;
		}
		case 14:
		{
			system("cls");
			string ID_num;
			int sum;
			cout << "Updating client debt :   please enter client ID number : " << endl;
			cin >> ID_num;
			cout << " please enter the amount of debt you want to ADD : " << endl;
			cin >> sum;
			debt_update(ID_num, sum);
			break;
		}
		case 15:
		{
			system("cls");
			cout << "Showing all numbers of this company:  " << endl;
			printAll_phones();
			break;
		}
		case 16:
		{
			system("cls");
			string pack_name;
			int pack_price;
			cout << "Adding package to this company: please enter package name :   " << endl;
			cin >> pack_name;
			cout << " please enter the price of the pack: " << endl;
			cin >> pack_price;
			Package pack(pack_name, 0, pack_price);
			packy.insert(pair<string, Package>(pack_name, pack));
			break;
		}
		case 17:
		{
			system("cls");
			string company_name;
			cout << "Please enter company name to change it :   " << endl;
			cin >> company_name;
			set_Company_Name(company_name);
			break;
		}
		case 18:
		{
			system("cls");
			string ID_num;
			int dicount;
			cout << "Please enter client Id you want to give him a discount:   " << endl;
			cin >> ID_num;
			cout << " please enter the amount of discount you want to give : " << endl;
			cin >> dicount;
			give_discount(ID_num, dicount);
			break;
		}
		case 19:
		{
			system("cls");
			int number;
			cout << "Enter the number you want to remove from company at all :  " << endl;
			cin >> number;
			remove_number(number);
			break;
		}
		case 20:
		{
			system("cls");
			string ID_num, pack_name;
			cout << "Please enter the client ID number  :   " << endl;
			cin >> ID_num;
			cout << " Please enter the pack name you want swap :  " << endl;
			cin >> pack_name;
			swap_Pack(ID_num, pack_name);
			break;
		}
		default:
		{	
			system("cls");
			cout << "you have entered wrong option, please enter another option!!" << endl;
			break;
		}

		}
		char c;
		cout << "Enter E to EXIT , M to MENU :" << endl;
		cin >> c;

		if (c == 'e' || c == 'E')
			flag = 0;
	}
	serialization(file);
}


void Cellular_Company::desrialization(string file_in) // deserialize
{
	Clients_database.clear();
	fstream file;
	string line;
	file.open(file_in, ios::in);
	if (file.is_open())
	{
		file >> Company_name >> Packages_count >> Total_Clients >> Monthly_income;
		string pack_packname;
		int clie_cnt = 0, price = 0, total = 0;
		for (int i = 0; i < Packages_count; i++)//desrialization all packges in file.
		{
			file >> pack_packname >> clie_cnt >> price;
			Package pack(pack_packname, clie_cnt, price);
			packy.insert(pair<string, Package>(pack_packname, pack));
			total += clie_cnt;
		}
		string clie_name = "NULL", Package, ID_num;
		int num_cnt = 0, payment_cnt = 0, num = 0, monthly_payment = 0, discount = 0;
		unsigned long  numofdays = 0;
		double debt = 0;
		for (int i = 0; i < total; i++)//desrialization all clients in file.
		{
			
			file >> clie_name >> num_cnt;
			list <int> li;
			map<Date, int> pay_Hist;
			for (int j = 0; j < num_cnt; j++)
			{
				file >> num;
				li.push_front(num);
				all_Numbers.push_front(num);
			}
			file >> Package >> ID_num;
			file >> numofdays >> debt >> monthly_payment >> discount >> payment_cnt;
			Date D(numofdays);
			Client clie(clie_name, ID_num, monthly_payment, discount, Package, D, debt);
			clie.setClientNumber(li);
			it2 = packy.find(Package);
			for (int j = 0; j < payment_cnt; j++)
			{
				int pay=0;
				unsigned long day_number=0;
				file >> day_number >> pay;
				Date D_pay(day_number);
				pay_Hist.insert(pair<Date, int>(D_pay, pay));
			}
			clie.setPayment_history(pay_Hist);
			Clients_database.insert(pair<string, Client > (ID_num, clie));
			it2->second.Clients.push_front(clie); 
		}
		int retsize = 0;
		file >> retsize;
		string Id, name;
		for (int i = 0; i < retsize; i++)//desrialization all client in Customer_retention.
		{
			file >> Id >> name;
			Customer_retention.insert(pair<string, string >(Id, name));
		}

		file.close();
	}
	else
	{
		 cerr << "Enable to open file!!!" << endl;
	}
}


void Cellular_Company::serialization(string file_out) //serialization
{
	fstream file;
	file.open(file_out, ios::out);
	if (file.is_open()) {
		file << Company_name << " " << Packages_count// print company data to  file.
			<< " " << Total_Clients << " " << Monthly_income << endl;
		file << endl;
		for (it2 = packy.begin(); it2 != packy.end(); it2++)// print all packages to  file.
		{
			file << it2->second.get_package_name() << " "<< it2->second.get_client_count() <<" "
				<< it2->second.get_Package_price() << endl;
		}
		for (it = Clients_database.begin(); it != Clients_database.end(); it++)// print all clients to file. 
		{
			file << it->second.getClientname() << endl;
			file << it->second.C_Number.size() << endl;
			for (itn=it->second.C_Number.begin();  itn != it->second.C_Number.end(); itn++)
			{
				file << *itn << " ";
			}
			file << it->second.getPackage() << " "<< it->second.get_ID()
				<< " " << it->second.getDate().get_day_number()
				<< " " << it->second.get_debt() << " " << it->second.get_monthly_payment() << " " 
				<< it->second.get_discount() << endl;
			file << it->second.Payment_history.size()<<endl;
			map<Date, int>::iterator it5= it->second.Payment_history.begin();
			for (it5 ; it5 != it->second.Payment_history.end(); it5++)
			{
				file << it5->first.get_day_number() << " "<< (it5->second)<<endl;
			}
		}
		file << Customer_retention.size()<<endl;
		for (it3 = Customer_retention.begin(); it3 != Customer_retention.end(); it3++)// print tetention list to file.
		{
			file << it3->first << " " << it3->second << endl;
		}
		file.close();
	}
	else cerr << "Enable to save clients data!!!" << endl;

}
