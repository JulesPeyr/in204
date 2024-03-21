#include<string>
#include<iostream>
#include"hitable.h"
#include<vector>
#include<fstream>
#include"material.h"
#include "drawing.h"

using namespace std;

//used to store parameters
struct parameters {
	int height{360};
	int width{720};
	int ns{10};
	Rvector camera_origin{Rvector(0.0,0.0,0.0)};
	Rvector camera_subject{Rvector(0.0,0.0,-1.0)};
	Rvector camera_vertical{Rvector(0.0,1.0,0.0)};
	string output_file{"output_file.ppm"};
	float camera_fov{90};
	vector<hitable*> objects;
	vector<material*> materials;
};

//used to find a string's position in a string vector
int find(string needle, vector<string> &haystack) {
	int ret=-1;
	unsigned int i=0;
	while(i<haystack.size()) {
		if(haystack[i]==needle)
			ret=i;
		i++;
	}
	return ret;
}

material *find_material(string needle, vector<material*> haystack) {
	material *ret=NULL;
	unsigned int i=0;
	while(i<haystack.size()) {
		if(haystack[i]->tag==needle)
			return haystack[i];
		i++;
	}
	return ret;

}

//function used to set a parameter
void set(parameters *param, string name, vector<string> values) {
	vector<string> flags = {"height","width","ns","camera_origin","camera_subject",
		"camera_vertical","camera_fov","sphere","material_matte","material_metal","material_dielectric", "output_file"};
	//TEMP DEFAULT MATTER
	matte *tempMat=new matte(Rvector(0.8,0.1,0.1));
	int n=find(name, flags);
	switch(n) {
		//setting height
		case 0:
			if(values.size()!=1) {
				cout << "Too many arguments for the flag " << name << " : " << values.size() << " (expected 1)";
				break;
			}
			param->height=stoi(values[0]);
			break;
		//setting width
		case 1:
			if(values.size()!=1) {
				cout << "Too many arguments for the flag " << name << " : " << values.size() << " (expected 1)";
				break;
			}
			param->width=stoi(values[0]);
			break;
		//setting ns
		case 2:
			if(values.size()!=1) {
				cout << "Too many arguments for the flag " << name << " : " << values.size() << " (expected 1)";
				break;
			}
			param->ns=stoi(values[0]);
			break;
		//setting camera_origin
		case 3:
			if(values.size()!=3) {
				cout << "Too many/few arguments for the flag " << name << " : " << values.size() << " (expected 3)";
				break;
			}
			param->camera_origin=Rvector(stof(values[0]),stof(values[1]),stof(values[2]));	
			break;
		//setting camera_subject
		case 4:
			if(values.size()!=3) {
				cout << "Too many/few arguments for the flag " << name << " : " << values.size() << " (expected 3)";
				break;
			}
			param->camera_subject=Rvector(stof(values[0]),stof(values[1]),stof(values[2]));	
			break;
		//setting camera_vertical
		case 5:
			if(values.size()!=3) {
				cout << "Too many/few arguments for the flag " << name << " : " << values.size() << " (expected 3)";
				break;
			}
			param->camera_vertical=Rvector(stof(values[0]),stof(values[1]),stof(values[2]));	
			break;
		//setting camera_fov
		case 6:
			if(values.size()!=1) {
				cout << "Too many/few arguments for the flag " << name << " : " << values.size() << " (expected 1)";
				break;
			}
			param->camera_fov=stof(values[0]);
			break;
		//creating a sphere
		case 7:
			if(values.size()!=5) {
				cout << "Too many/few arguments for the flag " << name << " : " << values.size() << " (expected 5)";
				break;
			}
			cout << "creating sphere " << stof(values[0]) << " / " << stof(values[1]) << " / " << stof(values[2]) << " / " << stof(values[3]) << endl;
			if(find_material(values[4],param->materials)==NULL)
				cout << "Undefined material tag : " << values[4] << ". Ignoring flag..." << endl;
			param->objects.push_back(new sphere(Rvector(stof(values[0]),stof(values[1]),stof(values[2])), stof(values[3]), find_material(values[4],param->materials)));
			break;
		//creating a matte material
		case 8:
			if(values.size()!=4) {
				cout << "Too many/few arguments for the flag " << name << " : " << values.size() << " (expected 5)";
				break;
			}
			param->materials.push_back(new matte(Rvector(stof(values[0]),stof(values[1]),stof(values[2]))));
			param->materials.back()->tag=values[3];
			break;
		//creating a metal material
		case 9:
			if(values.size()!=5) {
				cout << "Too many/few arguments for the flag " << name << " : " << values.size() << " (expected 5)";
				break;
			}
			param->materials.push_back(new metal(Rvector(stof(values[0]),stof(values[1]),stof(values[2])),stof(values[3])));
			param->materials.back()->tag=values[4];
			break;
		//creating a glass
		case 10:
			if(values.size()!=2) {
				cout << "Too many/few arguments for the flag " << name << " : " << values.size() << " (expected 5)";
				break;
			}	
			param->materials.push_back(new dielectric(stof(values[0])));
			param->materials.back()->tag=values[1];
			break;
		//setting output file name
		case 11:
			if(values.size()!=1) {
				cout << "Too many/few arguments for the flag " << name << " : " << values.size() << " (expected 5)";
				break;
			}	
			param->output_file=values[0];
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
	//used to store all the parameters
	parameters *ret = new parameters;

	//opening the file...
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
				set(ret, flag_name,values);
			}
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
	if(argc<2) {
		cout << "Error. Not enough arguments" << endl;
		return 0;
	}
	parameters *param = load(argv[1]);


	//

    	
    	float dist_to_focus = 10.0;
    	float aperture = 0.1;
	
	//initialize the camera
    	camera cam(param->camera_origin,param->camera_subject,param->camera_vertical,param->camera_fov, float(param->width)/float(param->height));
	//initialize canvas
    	drawing img(param->width, param->height);
	//param multi-threading
    	int max_threads = thread::hardware_concurrency();
	//init world
	int world_size=param->objects.size();
	hitable **world = new hitable*[world_size];
	for(int i=0; i<world_size; i++)
		world[i]=param->objects[i];
    	img.draw_image_multithreaded(param->output_file.c_str(), max_threads, param->ns, cam, new hitable_list(world,world_size));	
	
	
	return 0;
}
