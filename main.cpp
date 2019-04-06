#include <iostream>
#include <fstream>

#include "camera.h"
#include "ray.h"
#include "plotter.h"

typedef vec3 Color;

int main(){

	vec3 corner(-2.0,-1.0,-1.0);
	vec3 hor   (4.0,0.0,0.0);
	vec3 ver   (0.0,2.0,0.0);
	vec3 origin(0.0,0.0,0.0);

	Camera cam(origin,ver,hor,corner);

	int nx = 200;
	int ny = 100;

	Plotter plotter(nx,ny,"acabou.ppm");


	for (int j = 0; j <  ny-1; j++){
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
	plotter.plotFile();

}