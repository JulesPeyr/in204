#include<string>
#include<iostream>
#include"hitable.h"
#include<vector>
#include<fstream>

using namespace std;

//used to store parameters
struct parameters {
	int height;
	int width;
	int ns;
	vector<hitable> objects;
};

//used to find a string's position in a string vector
int find(string needle, vector<string> &haystack) {
	int ret=-1;
	unsigned int i=0;
	while(i<haystack.size())
		if(haystack[i++]==needle)
			ret=i;
	return ret;
}

//function used to set a parameter
void set(string name, vector<string> values) {
	vector<string> flags = {"height","width","ns","sphere"};
	int n=find(name, flags);
	switch(n) {
		//setting height
		case 0:
			break;
		case 1:
			//TODO
			break;
		case 2:
			//TODO
			break;
		case 3:
			//TODO
			break;
		default:
			cout << "Unrecognised flag : " << name <<  ". Ignoring the flag..." << endl;
	}
}

//get next non-space char
char sksp(fstream &pf) {
	char c=pf.get();
	while(!pf.eof() && c==' ')
		c=pf.get();
	return c;
}


//function used to parse the input file
parameters *load(string fileName) {
	parameters *ret = new parameters;
	fstream pf(fileName);
	if(!pf.is_open()) {
		cout << "error loading the file : " << fileName << endl;
		delete ret;
		return NULL;
	}
	
	//reading the file
	char c;
	string flag_name;
	vector<string> values;
	while(!pf.eof()) {
		c=pf.get();
		//reading a new commentary
		if(c=='#') {
			cout << "> ";
			while(c!='\n' && !pf.eof()) {
				c=pf.get();
				cout << c;
			}
		}
		//reading a new flag
		if(c=='.') {
			c=sksp(pf);
			//getting flag name
			while(c!='(' && !pf.eof() && c!=' ') {
				flag_name+=c;
				c=pf.get();
			}
			cout << "flag name : " << flag_name << endl;
			c=sksp(pf);
			if(c==')') {
				cout << "Error : empty value for flag " << flag_name << ". Ignoring the flag..." << endl;
			} else {
				//geting flag values
				cout << "values :";
				while(c!=';' && !pf.eof()) {
					values.push_back("");
					while(c!=',' && c!=')' && !pf.eof() && c!=';') {
						values.back()+=c;
						c=pf.get();
					}
					cout << " #" << values.back();
					c=sksp(pf);
				}
				cout << endl;
			}
			set(flag_name,values);
			cout << endl;
		}
		values = {};
		values.shrink_to_fit();
		flag_name="";
	}
	return ret;
}



int main(int argc, char **argv) {
	
	//loading the scene
	if(argc<2)
		cout << "Error. Not enough arguments" << endl;
	parameters *param = load(argv[1]);
	
	
	return 0;
}
