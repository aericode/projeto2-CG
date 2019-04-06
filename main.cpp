#include <iostream>
#include <fstream>

#include "ray.h"
#include "plotter.h"

typedef vec3 Color;

bool hit_sphere(const vec3& center, float radius, const ray& r){
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(),r.direction());
	float b = 2.0 * dot(oc,r.direction());
	float c = dot(oc, oc) - radius*radius;

	float discriminant = b*b - 4*a*c;
	return (discriminant > 0);
}

vec3 addColor(const ray& r){

	if(hit_sphere(vec3(0,0,1),0.5, r)){
		return vec3(1,0,0);
	}

	//vetor unitario
	vec3 unit_direction = unit_vector(r.direction());

	//metade do Y do vetor unitário + 1 
	float t = 0.5*(unit_direction.y() + 1.0);

	//aumenta e diminui em funcao deste valor do (branco total ao azul)
	return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
}

int main(){

	int nx = 200;
	int ny = 100;


	Plotter plotter(nx,ny,"helloworld.ppm");

	vec3 lower_left_corner(-2.0,-1.0,-1.0);
	vec3 horizontal(4.0,0.0,0.0);
	vec3 vertical  (0.0,2.0,0.0);
	vec3 origin    (0.0,0.0,0.0);

	for (int j = ny-1; j >=  0; j--){
		for(int i = 0; i <  nx; i++){
			float u = float(i) / float (nx);
			float v = float(j) / float (ny);
			ray r(origin, lower_left_corner + u*horizontal + v*vertical);
			vec3 col = addColor(r);


			int ir  = int(255.99*col[0]);
			int ig  = int(255.99*col[1]);
			int ib  = int(255.99*col[2]);

			plotter.changePixel(i,j, Color(ir,ig,ib));
		}
	}

	plotter.plotFile();

}