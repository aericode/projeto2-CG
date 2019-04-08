#include <iostream>
#include <fstream>

#include "json.hpp"
#include "jsonReader.h"
#include "camera.h"
#include "ray.h"
#include "plotter.h"

using json::JSON;
typedef vec3 Color;

int main(){

	JSON obj = parseFile("scene.json");
	Camera cam = cameraFromJSON(obj);


	int nx = 200;
	int ny = 100;

	Plotter plotter(nx,ny,"teste.ppm");


	for (int j = ny-1; j >= 0 ; j--){
		for(int i = 0; i <  nx; i++){
			float u = float(i) / float (nx);
			float v = float(j) / float (ny);

			ray r  = cam.generateRay(u,v); 

			vec3 col = cam.fadeBG(r);


			int ir  = int(255.99*col[0]);
			int ig  = int(255.99*col[1]);
			int ib  = int(255.99*col[2]);

			plotter.changePixel(i,j, Color(ir,ig,ib));
		}
	}
	plotter.changePixel(100,0, Color(255,0,0));
	plotter.plotFile();
	

}