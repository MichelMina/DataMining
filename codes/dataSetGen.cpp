#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <fstream>
#include "Class.h"


bool Is_data_base_set(string FileName) {
	fstream DataSet;
	DataSet.open(FileName);
	if (!DataSet.is_open()) {
		DataSet.close();
		return false;
	}
	if (sizeof(DataSet) < 10) {  //it means that the file is nearly empty
		DataSet.close();
		return false;
	}
	else {
		DataSet.close();
		return true;
	}
}

bool generate(int CUSTOMERNUMBER)
{
	fstream file;
	file.open("DataSet.txt", ios::out);
	if (!file.is_open())
	{
		cerr << "cannot open file" << endl;
		return false;
	}
	srand(time(NULL));

	for (long i = 0; i < CUSTOMERNUMBER; i++)
	{
		file << "<customer>" << endl;
		file << "\t<customerID>" << i << "</customerID>" << endl;
		file << "\t<ageCategory>" << rand() % 4 << "</ageCategory>" << endl;
		file << "\t<gender>" << rand() % 2 << "</gender>" << endl;
		file << "\t<location>" << rand() % 4 << "</location>" << endl;
		file << "\t<paymentMethod>" << rand() % 4 << "</paymentMethod>" << endl;
		file << "\t<userRating>" << 1+(rand() % 4) << "</userRating>" << endl;
		file << "\t<interests>" << rand() % 5 << "</interests>" << endl;
		file << "</customer>" << endl;
	}
	file.close();
	return true;
}

bool appendToFile(customer *c)
{
	ofstream file;
	file.open("DataSet.txt", ios::app);
	//checking whether it's open 
	if (!file.is_open())
		return false;
	file << "<customer>" << endl;
	file << "\t<customerID>" << c->get_ID() << "</customerID>" << endl;
	file << "\t<geCategory>" << c->get_age() << "</ageCategory>" << endl;
	file << "\t<gender>" << c->get_gender() << "</gender>" << endl;
	file << "\t<location>" << c->get_Location() << "</location>" << endl;
	file << "\t<paymentMethod>" << c->get_payment_method() << "</paymentMethod>" << endl;
	file << "\t<userRating>" << c->get_user_rating() << "</userRating>" << endl;
	file << "\t<interests>" << c->get_interrest() << "</interests>" << endl;
	file << "</customer>" << endl;
	file.close();
	return true;
}