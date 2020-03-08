#include "Package.h"
Package::Package(string name = NULL, int num_of_clie=0, int Pack_Price=0 )//Constructor.
{	// Asign all parameters
	Package_name = name;
	Client_count = num_of_clie;
	Package_price = Pack_Price;
}
Package::Package(const Package& Pack)//Copy Constractor.
{
	// Asign all parameters
	Package_name = Pack.Package_name;
	Client_count = Pack.Client_count;
	Package_price = Pack.Package_price;
	Clients = Pack.Clients;
}
Package::~Package()//Distructor.
{ 
	Clients.clear(); 
}
ostream& operator<<(ostream& os, Package& P)// << operator.
{

	cout << "Package " << P.get_package_name() << ":" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "Number OF Clients:    " << P.get_client_count() << endl;
	cout << "Packge Price:         " << P.get_Package_price() << endl;
	cout << "-----------------------------------------------" << endl;
	list<Client>::iterator i;
	for (i = P.Clients.begin(); i != P.Clients.end(); i++) {
		cout << "-----------------------------------------------" << endl;
		cout << (*i) << endl;
	}
	cout << "***********************************************" << endl;
	cout << endl << endl;
	return os;
}
