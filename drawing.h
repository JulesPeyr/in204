#ifndef DRAWING_H
#define DRAWING_H

#include <iostream>
#include <fstream>
#include "vector.h"

using namespace std;

class drawing {
	public:
		//constructors
		drawing() {}
		drawing(const int l, const int h) {
			length=l;
			height=h;
			canvas=new unsigned int [l*h];
			//init with a white canvas
			for(int i=0; i<l; i++) {
				for(int j=0; j<h; j++) {
					canvas[i+j*length]=0xFFFFFF;
				}
			}
		}

		//destructor
		~drawing() {
			delete[] canvas;
		}
		
		//methods
		inline void draw_pixel(int, int, color);
		void draw_image(const char *);
		void print_image();
		inline unsigned int rgb_to_int(color);
		inline unsigned char int_to_r(unsigned int);
		inline unsigned char int_to_g(unsigned int);
		inline unsigned char int_to_b(unsigned int);

		//size of the canvas
		int length,height;
		//storing image data, to access the color of pixel (i,j) we access canvas[i+j*l], the origin is in the bottom left corner.
		unsigned int *canvas;
};

//we store the three rgb values as a single int
inline unsigned int drawing::rgb_to_int(color c) {
	return((c.r()<<16)+(c.g()<<8)+c.b());
}

inline unsigned char drawing::int_to_r(unsigned int rgb) {
	return((unsigned char)(rgb>>16));
}

inline unsigned char drawing::int_to_g(unsigned int rgb) {
	return((unsigned char)((rgb&0xff00)>>8));
}

inline unsigned char drawing::int_to_b(unsigned int rgb) {
	return((unsigned char)(rgb&0xff));
}

inline void drawing::draw_pixel(int x, int y, color c) {
	canvas[x+(height-y-1)*length]=rgb_to_int(c);
}

void drawing::draw_image(const char *name_file) {
	cout << "Writing a new image ! name of the file : " << name_file << "\n";
	ofstream file;
	file.open(name_file);
	//writing to the file...
	file << "P3\n" << length << " " << height << "\n255\n";
	for(int j=0; j<height; j++) {
		for(int i=0; i<length; i++) {
			int px_c = canvas[i+j*length];
			int px_r = int_to_r(px_c);
			int px_g = int_to_g(px_c);
			int px_b = int_to_b(px_c);
			file << px_r << " " << px_g << " " << px_b << endl;
		}
	}
	//closing file
	file.close();
}

void drawing::print_image() {
	cout << "P3\n" << length << " " << height << "\n255\n";
	for(int j=0; j<height; j++) {
		for(int i=0; i<length; i++) {
			int px_c = canvas[i+j*length];
			int px_r = int_to_r(px_c);
			int px_g = int_to_g(px_c);
			int px_b = int_to_b(px_c);
			cout << px_r << " " << px_g << " " << px_b << endl;
		}
	}
}

#endif
