//Please do not change the filename or will not work!!!
//DO NOT write anything before the first 3 lines or will not work also!!!!!
//Here are three numbers to get from file: 18123.12 12 16.15\0

#include <iostream>
#include <string>
#include <fstream>      // std::ifstream

using namespace std;
#pragma warning(disable:4996) //disable deprecateds

void imprime(const char *c) { 	cout << "line:" << c << endl; }

//Finds a substring after a character or string:
void string_find(string &str1, const char *search);
//Extracts a data from string str1 after search. Then new string points after that data
double string_to_double(string &str1, const char *search);
//Extracts a data from string str1 after search. Then new string points after that data
double string_to_double(string &str1, int i1 = 0);
//Counts number of lines in a file:
int countlines(ifstream &myfile);
//Extracts the data number "num" in the string. Caution, the first number num=0!!
double string_to_double2(string str1, int num);
//Extracts the data number "num" in line
double string_to_double2(char *line, int num);

//bool isnumber(string str1) { 	char p = str1.c_str()[0]; return (p >= '0' && p <= '9'); }
//Detect number:
bool isnumber(string str1) { if (str1.c_str()[0] >= '0' && str1.c_str()[0] <= '9')return true;else return false; }



void main()
{
	string a = "Rincon", b = " provincia de Malaga", c;

	c = "==== longitud=30 =============";
	cout << c << " size=" << c.size() << " length=" << c.length() << endl;

	c = a;

	c = a + " de la Victoria" + b;
	imprime(c.c_str());
	c = b;
	imprime((char *)c.c_str());

	
	char ch[] = "Test char line filled in to string";
	c.assign(ch);
	imprime(c.c_str());

	c = "Assigned directly";
	cout << c << endl;

	c.assign("Trying to obtain data 123.14 from this sentence");
	cout << c << endl;
	cout << "Obtained=" << string_to_double(c, "data") << endl;  

	cout << endl << "Now trying to obtain data from this file!" << endl;

	string line;
	ifstream myfile("string3.cpp");
	int numlines = countlines(myfile);
	cout << "This .cpp file has " << numlines << " lines" << endl;

	if (numlines == 0)
		cout << "I advised you not to change the name of this file!!!" << endl;
	else
	{
		getline(myfile, line);
		getline(myfile, line);
		getline(myfile, line); 
		cout << "Extracting three numbers from this line:" << endl << line << endl;

		double d1,d2; size_t i1; 
		d1 = string_to_double(line, "file:");
		i1 = (int) string_to_double(line);
		d2 = string_to_double(line);
		cout << "The 3 numbers=" << d1 << " " << i1 << " " << d2 << endl;
		myfile.close();
	}

	//      012345678901234567890123456789
	line = "Extract from index 1234 This is the remainder line ";
	cout << line << endl;
	int i1=(int) string_to_double(line, 19);
	cout << "Result=" << i1 << " remainder line=" << line << endl;

	line = "2	32.1dC	28.7dC	25.2dC	20.7dC	19.6dC	18.5dC	74 %	67 %	52 %	4 kph	2 kph	0 kph";
	cout << "\nExtracts different datas from this string:" << endl << line << endl;
	double d1,d2;
	//Obtain the 3rd number 28.7:
	string_find(line, "C");d1 = string_to_double(line);
	//Obtain the 5th number 20.7:
	string_find(line, "C"); string_find(line, "C"); d2 = string_to_double(line);
	string_find(line, "%");
	double d3 = string_to_double(line);
	cout << "3rd number (28.7)=" << d1 << endl;
	cout << "5th number (20.7)=" << d2 << endl;
	cout << "9th number (67)  =" << d3 << endl;
	cout << endl;

	cout << "\nDetects using string_to_double2() over string:" << endl;
	line = "N 2	32.1dC	28.7dC	25.2dC	20.7dC	19.6dC	18.5dC	74 %	67 %	52 %	4 kph	2 kph	0 kph";
	cout << "Position 2 (28.7)=" << string_to_double2(line, 2) << endl;
	cout << "Position 4 (20.7)=" << string_to_double2(line, 4) << endl;
	cout << "Position 8 (67)  =" << string_to_double2(line, 8) << endl;
	cout << endl;

	cout << "\nDetects using string_to_double2() over char array:" << endl;
	line = "N 2	32.1dC	28.7dC	25.2dC	20.7dC	19.6dC	18.5dC	74 %	67 %	52 %	4 kph	2 kph	0 kph";
	char line3[1024];strcpy(line3, line.c_str());
	cout << "Position 2 (28.7)=" << string_to_double2(line3, 2) << endl;
	cout << "Position 4 (20.7)=" << string_to_double2(line3, 4) << endl;
	cout << "Position 8 (67)  =" << string_to_double2(line3, 8) << endl;
	cout << endl;

	cout << endl << "Detection of number at the beginning of a string:" << endl;
	line = "0a"; cout << line; if (isnumber(line)) cout << " number\n"; else cout << " no number\n";
	line = "1a"; cout << line; if (isnumber(line)) cout << " number\n"; else cout << " no number\n";
	line = "2a"; cout << line; if (isnumber(line)) cout << " number\n"; else cout << " no number\n";
	line = "9a"; cout << line; if (isnumber(line)) cout << " number\n"; else cout << " no number\n";
	line = "z9a"; cout << line; if (isnumber(line)) cout << " number\n"; else cout << " no number\n";
	line = " 9a"; cout << line; if (isnumber(line)) cout << " number\n"; else cout << " no number\n";
	line = ".9a"; cout << line; if (isnumber(line)) cout << " number\n"; else cout << " no number\n";

	cout << "\n=== END ===" << endl; getchar();
}


//Finds a substring after a character or string:
void string_find(string &str1, const char *search)
{
	string str2(search);
	str1 = str1.substr(str1.find(str2) + str2.size());
}

//Extracts a data from string str1 after search. Then new string points after that data
double string_to_double(string &str1, const char *search)
{
	string str2(search);
	str1 = str1.substr(str1.find(str2) + str2.size());
	size_t pos;
	double ret = stod(str1, &pos);
	str1 = str1.substr(pos + 1);
	return ret;
}

//Extracts a data from string str1 after search. Then new string points after that data
double string_to_double(string &str1, int i1)
{
	size_t pos = (size_t)i1; str1 = str1.substr(pos);
	double ret = stod(str1, &pos);
	str1 = str1.substr(pos);
	return ret;
}

//Counts number of lines in a file:
int countlines(ifstream &myfile)
{
	string line; int numlines = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//cout << line << '\n';
			numlines++;
		}
		myfile.clear();
		myfile.seekg(0);//rewinds
	}
	return numlines;
}

//Extracts the data number "num" in the string
double string_to_double2(string str1, int num)
{
	int i1 = 0, max = (int) str1.size();
	size_t pos;
	for (int i = 0; i < max; i++)
	{
		if (isnumber(str1))
		{
			if (i1 == num) return stod(str1);
			i1++; stod(str1, &pos);
			str1 = str1.substr(pos + 1);
		}
		else str1 = str1.substr(1);
	}
	return -99999999;
}

//Extracts the data number "num" in line
double string_to_double2(char *line, int num)
{
	int i1 = 0, max = (int) strlen(line);
	for (int i = 0; i < max; i++)
	{
		if (line[0] >= '0' && line[0] <= '9')
		{
			if (i1 == num) return strtod(line,&line);
			strtod(line, &line);i1++;
		}
		else line++;
	}
	return -99999999;
}