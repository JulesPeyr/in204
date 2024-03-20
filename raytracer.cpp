#include<string>
#include<iostream>
#include"hitable.h"
#include<vector>
#include<fstream>
#include"material.h"

using namespace std;

//used to store parameters
struct parameters {
	int height{720};
	int width{360};
	int ns{10};
	Rvector camera_origin{Rvector(0.0,0.0,0.0)};
	Rvector camera_subject{Rvector(0.0,0.0,-1.0)};
	Rvector camera_vertical{Rvector(0.0,1.0,0.0)};;
	float camera_fov{90};
	vector<sphere> spheres;
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
void set(parameters *param, string name, vector<string> values) {
	vector<string> flags = {"height","width","ns","camera_origin","camera_subject","camera_vertical","camera_fov","sphere"};
	//TEMP DEFAULT MATTER
	matte *tempMat=new matte(Rvector(0.8,0.1,0.1));
	int n=find(name, flags);
	switch(n) {
		//setting height
		case 0:
			if(values.size()!=1) {
				cout << "Too many arguments for the flag " << name << " : " << values.size() << " (excpected 1)";
				break;
			}
			param->height=stoi(values[0]);
			break;
		//setting width
		case 1:
			if(values.size()!=1) {
				cout << "Too many arguments for the flag " << name << " : " << values.size() << " (excpected 1)";
				break;
			}
			param->width=stoi(values[0]);
			break;
		//setting ns
		case 2:
			if(values.size()!=1) {
				cout << "Too many arguments for the flag " << name << " : " << values.size() << " (excpected 1)";
				break;
			}
			param->ns=stoi(values[0]);
			break;
		//setting camera_origin
		case 3:
			if(values.size()!=3) {
				cout << "Too many/few arguments for the flag " << name << " : " << values.size() << " (excpected 3)";
				break;
			}
			param->camera_origin=Rvector(stof(values[0]),stof(values[1]),stof(values[2]));	
			break;
		//setting camera_subject
		case 4:
			if(values.size()!=3) {
				cout << "Too many/few arguments for the flag " << name << " : " << values.size() << " (excpected 3)";
				break;
			}
			param->camera_subject=Rvector(stof(values[0]),stof(values[1]),stof(values[2]));	
			break;
		//setting camera_vertical
		case 5:
			if(values.size()!=3) {
				cout << "Too many/few arguments for the flag " << name << " : " << values.size() << " (excpected 3)";
				break;
			}
			param->camera_vertical=Rvector(stof(values[0]),stof(values[1]),stof(values[2]));	
			break;
		//setting camera_fov
		case 6:
			if(values.size()!=1) {
				cout << "Too many arguments for the flag " << name << " : " << values.size() << " (excpected 1)";
				break;
			}
			param->camera_fov=stof(values[0]);
			break;
		//creating a sphere
			if(values.size()!=5) {
				cout << "Too many arguments for the flag " << name << " : " << values.size() << " (expected 5)";
				break;
			}
			param->spheres.push_back(sphere(Rvector(stof(values[0]),stof(values[1]),stof(values[2])), stof(values[3]), tempMat));

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
			set(ret, flag_name,values);
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
