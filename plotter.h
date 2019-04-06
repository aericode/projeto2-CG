#ifndef PLOTTER
#define PLOTTER
#include <iostream>
#include <fstream>

#include "vec3.h"

#include <vector>
#include <string>

using namespace std;
typedef vec3 Color;

class Plotter
{
private:

	int xSize;
	int ySize;
    std::string  fileName;
    int fileLineCount;
    Color* pixelColor;

public:
	Plotter(){}

	Plotter(int xSize_,int ySize_,std::string fileName_){

		fileName = fileName_;

		xSize = xSize_;
		ySize = ySize_;

		fileLineCount = (xSize*ySize) + 3;

		pixelColor = new Color[fileLineCount];

		clear();

		plotFile();
	}

	~Plotter(){
		delete[] pixelColor;
	}

	int matrixToLine(int x, int y){
		return x + y*xSize;
	}


	bool isValidLocation(int x, int y){
		bool validX = (x < xSize) && (x >= 0);
		bool validY = (y < ySize) && (y >= 0);

		return validX && validY;
	}

	void changePixel(int x, int y, Color color = Color(0,0,0)){
		//se estiver fora do limite simplesmente ignora
		if(!isValidLocation(x,y)){return;}

		int indexLine = 3 + matrixToLine(x,y);
		pixelColor[indexLine] = color;
	}

	void clear(){
		for(int i = 3;i < fileLineCount;i++){
			pixelColor[i]= Color(255,255,255);
		}
	}

	
	void plotFile(){
		std::ofstream myfile;

		myfile.open(fileName.c_str());



		myfile<< "P3" <<std::endl;
		myfile<< std::to_string(xSize) + " " +  std::to_string(ySize) <<std::endl;
		myfile<< "255" <<std::endl;


		for(int i = 4;i < fileLineCount;i++){
			myfile<<pixelColor[i]<<std::endl;
		}
	}
};

#endif