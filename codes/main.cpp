
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <queue>
#include "Class.h"
#include "STL.h"
#define USERS 10000
using namespace std;


bool Age_Pie(List& Data, int AgeCategory);
bool generate_pie(int slices_number, string slices_names[], int slices_values[], string title);
bool Product_Pie(List &Data, int Chosen_product);


bool generate(int);
bool Is_data_base_set(string);
bool appendToFile(customer*);
bool extract_to_list(List&);


int lastCustomerID = USERS;

int main()
{
	List DataBase;
	/*Next part is in order not to make a new file*/
	if (!Is_data_base_set("DataSet.txt")) {
		if (!generate(USERS)) {
			cerr << "cannot set data";
			return 1;
		}
	}

	//admin choice
	char choice = -1;
	do {
		cout << "\n\t\tMain Menu "
			<< endl << "1:Add many random customers"
			<< endl << "2:Read the data from DataSet.txt file"
			<< endl << "3:Save the current customers' data to DataSet.txt file"
			<< endl << "4:Get statistics for certain age category"
			<< endl << "5:Get statistics for certain product"
			<< endl << "**********\nYour Answer: ";
		cin >> choice;
		cout << "**********"<<endl;
		cin.ignore();
		switch (choice) {
		case '1':
		{
					int many;
					cout << "Please enter how many random users you want to create\n**********\nYour Answer: ";
					cin >> many;
					cout << "**********\n";
					for (int i = 0; i<many; i++)
					{
						customer* c = new customer();
						c->random_customer();
						DataBase.add_Front(c);
					}
					break;
		}
		case '2':
		{
					extract_to_list(DataBase);
					break;
		}
		case '3':
		{
					for (int i = 0; i<DataBase.get_Size(); i++)
					{
						customer *temp = DataBase.get_Front();
						appendToFile(temp);
						DataBase.add_End(temp);
						DataBase.pop_Front();
					}
					break;
		}
		case '4':
		{
					int tempcategory = 0;
					cout << "Please choose the Age Category\n1- 16->25\n2- 26->40\n3- 41->60\n-4 Above"
                         << endl << "**********\nYour Answer: ";
					cin >> tempcategory;
					cout << "**********\n";
					Age_Pie(DataBase, tempcategory);
					/*TODO, open the file*/
					system("explorer report.html");
					break;
		}
		case '5':
		{
					int tempproduct = 0;
					cout << "Please choose the product\n1- TV\n2- PlayStation\n3- Mobile Phones\-4 Tablets\n5- Laptops"
                         << endl << "**********\nYour Answer: ";
					cin >> tempproduct;
					cout << "**********\n";
					Product_Pie(DataBase, tempproduct);
					/*TODO open the file*/
					system("explorer report.html");
					break;

		}
		}
	} while (true);

	return 0;
}

bool extract_to_list(List& DataBase) {
	string line;
	stack<string> s;
	queue<string> q;
	ifstream file;
	file.open("DataSet.txt");
	if (!file.is_open())
		return false;
	while (!file.eof()) {
		getline(file, line);
		if (line == "<customer>")
			s.push(line);
		else if (line == "</customer>") {
			s.pop();
			string arr[7] = { "0" };
			for (int i = 0; i < 7; i++)
			{
				arr[i] = q.front();
				q.pop();
			}
			customer *c = new customer(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]);
			DataBase.add_End(c);
		}
		else {
			int tempindex = line.find('>', 0);
			string temp = line.substr(tempindex + 1, line.find('<', tempindex + 1) - tempindex - 1);
			q.push(temp);
		}
	}
	file.close();
	return true;
}

/*Data mining*/

bool Age_Pie(List& Data, int AgeCategory)
{
	int Product_Percentage[6] = { 0 };
	int tempsize = Data.get_Size();
	Node *temp = Data.getHead();
	for (int i = 0; i<tempsize; i++)
	{

		if (temp->get_Data()->get_age() == AgeCategory)
		{
			switch (temp->get_Data()->get_interrest())
			{
			case 1:Product_Percentage[0]++; break;
			case 2:Product_Percentage[1]++; break;
			case 3:Product_Percentage[2]++; break;
			case 4:Product_Percentage[3]++; break;
			case 5:Product_Percentage[4]++; break;
			}
		}
		else;
		temp = temp->get_next();
	}

	string Products[] = { "TV", "PlayStation", "Mobile Phones", "Tablets", "Laptops", "Did not choose" };
	generate_pie(6, Products, Product_Percentage, "The Age Category " + to_string(AgeCategory) + " Chose these products");
	cout << "Reached last line in Age_pie function" << endl;
	return true;
}

bool Product_Pie(List &Data, int Chosen_product)
{
	int counter = 1;
	int total_rating = 0;
	float average_rating = 1;
	int AgeCategory_Percentage[5] = { 0 };
	int Datasize = Data.get_Size();
	Node *temp = Data.getHead();
	for (double i = 0; i<Datasize - 1; i++)
	{
		int temp_interrest = temp->get_Data()->get_interrest();
		int temp_agecat = temp->get_Data()->get_age();
		if (temp_interrest == Chosen_product)
		{
			switch (temp_agecat){
			case 1:AgeCategory_Percentage[0]++; break;
			case 2:AgeCategory_Percentage[1]++; break;
			case 3:AgeCategory_Percentage[2]++; break;
			case 4:AgeCategory_Percentage[3]++; break;
			}
			counter++;
			total_rating += temp->get_Data()->get_user_rating();
		}
		else;
		temp = temp->get_next();
	}
	string Ages[] = { "18 To 25", "26 To 40", "41 To 61", "Above 60", "Not Chosen" };
	average_rating = total_rating / counter;
	generate_pie(5, Ages, AgeCategory_Percentage, "Product #" + to_string(Chosen_product) + " Statistics\\nAverage Rating =" + to_string(average_rating));
	return true;
}


bool generate_pie(int slices_number, string slices_names[], int slices_values[], string title)
{
	/* the function takes the number of pie slices and its names with values
	* and the pie chart title
	* writes an HTML with JS that creates the chart
	* using the googlecharts API*/

	ofstream html;
	html.open("report.html");
	html << "<html>\n\t<head>\n"
		"\t\t<!--Load the AJAX API-->\n"
		"\t\t<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>\n"
		"\t\t<script type=\"text/javascript\">\n\n"
		"\t\t// Load the Visualization API and the corechart package.\n"
		"\t\tgoogle.charts.load('current', {'packages':['corechart']});\n\n"
		"\t\t// Set a callback to run when the Google Visualization API is loaded.\n"
		"\t\tgoogle.charts.setOnLoadCallback(drawChart);\n\n"
		"\t\t// Callback that creates and populates a data table,\n"
		"\t\t// instantiates the pie chart, passes in the data and\n"
		"\t\t// draws it.\n\t\tfunction drawChart() {\n\n"
		"\t\t\t// Create the data table.\n"
		"\t\t\tvar data = new google.visualization.DataTable();\n"
		"\t\t\tdata.addColumn('string', 'Category');\n"
		"\t\t\tdata.addColumn('number', 'Percentage');\n"
		"\t\t\tdata.addRows([\n";

	for (int i = 0; i<slices_number; i++)
		html << "\t\t\t\t['" << slices_names[i] << "', " << slices_values[i] << "],\n";

	html << "\t\t\t]);\n\n"
		"\t\t\t// Set chart options\n"
		"\t\t\tvar options = {'title':'" << title << "','width':400,'height':300,is3D: true,};\n\n"
		"\t\t\t        // Instantiate and draw our chart, passing in some options.\n"
		"\t\t\tvar chart = new google.visualization.PieChart(document.getElementById('chart_div'));\n"
		"\t\t\tchart.draw(data, options);\n"
		"\t\t  }\n"
		"\t\t</script>\n"
		"\t</head>\n\n"
		"\t<body>\n"
		"\t\t<!--Div that will hold the pie chart-->\n"
		"\t\t<div id=\"chart_div\"></div>\t\n"
		"</body>\n"
		"</html>";

	return true;
}
