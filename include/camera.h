#ifndef CAMERAH
#define CAMERAH

#include <iostream>
#include "ray.h"

using namespace std;
typedef vec3 Color;

class Camera{
private:
	vec3 origin;
	vec3 vertical;
	vec3 horizontal;
	vec3 corner;

public:
	Camera(){}
	Camera(vec3 origin_, vec3 vertical_, vec3 horizontal_,vec3 corner_){
		origin     = origin_;
		vertical   = vertical_;
		horizontal = horizontal_;
		corner = corner_;
	}

	bool hit_sphere(const vec3& center, float radius, const ray& r){
		vec3 oc = r.origin() - center;
		float a = dot(r.direction(),r.direction());
		float b = 2.0 * dot(oc,r.direction());
		float c = dot(oc, oc) - radius*radius;

		float discriminant = b*b - 4*a*c;
		return (discriminant > 0);
	}

	vec3 fadeBG(const ray& r){
		//vetor unitario
		vec3 unit_direction = unit_vector(r.direction());

		//metade do Y do vetor unitário + 1 
		float t = 0.5*(unit_direction.y() + 1.0);

		//aumenta e diminui em funcao deste valor do (branco total ao azul)
		return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
	}

	//amostra para exibição de objetos em cena
	vec3 sample(const ray& r){
		if(hit_sphere(vec3(0,0,-1),0.5,r)){
			return vec3(1,0,0);
		}

		return fadeBG(r);
	}

	ray generateRay(float x, float y){
		vec3 direction = corner + x*horizontal + y*vertical;

		ray generated(origin, direction);

		return generated;
	}

};

#endif