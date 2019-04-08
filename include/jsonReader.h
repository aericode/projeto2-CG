#include "json.hpp"
#include <iostream>
#include <cstddef>
#include <algorithm>
#include <fstream>
#include <string>


#include "vec3.h"
#include "camera.h"


using json::JSON;
using namespace std;

typedef vec3 Color;

string stringFromFile(string filename)
{
    //pega o arquivo e transforma em uma string pronta para ser convertida em objeto
    string aux;
    string userInput;
    ifstream infile;
    infile.open (filename);
        while(!infile.eof()){
            getline(infile,aux);
            userInput += aux;
        }
    infile.close();

    return userInput;
}

JSON parseFile(string filename){
    JSON obj;
    string userInput = stringFromFile(filename);
    obj = JSON::Load(userInput);
    return obj;
}

Camera cameraFromJSON(JSON obj){
    if (obj["camera"].IsNull()){
        std::cout<<"no instructions for camera in JSON file"<<std::endl;
        return Camera();
    }else{
        string camParts[4] = {"origin","vertical","horizontal","corner"};
        vec3 aux[4];

        for(int i = 0; i < 4; i++){
            for(int j = 0;j < 3;j++){
                aux[i][j] = obj["camera"][camParts[i]][j].ToFloat();
            }
        }

        return Camera(aux[0],aux[1],aux[2],aux[3]);
    }
}

/*

void jsonToLines(JSON obj, Canvas& canvas){

    string index;
    string shape;

    int commandNumber = obj["commands"].ToInt();
    for(int i = 1;i <= commandNumber; i++){
        index = to_string(i);
        shape = obj[index]["shape"].ToString();

        if(shape == "line"){
            int x1 = obj[index]["x1"].ToInt();
            int y1 = obj[index]["y1"].ToInt();

            int x2 = obj[index]["x2"].ToInt();
            int y2 = obj[index]["y2"].ToInt();

            int thickness;
            if(obj[index]["thickness"].IsNull()){
                thickness = 1;
            }else{
                thickness = obj[index]["thickness"].ToInt();
            }

            canvas.drawLine(Location(x1,y1),Location(x2,y2),thickness);
        }else if(shape == "circle"){

            int x      = obj[index]["x"].ToInt();
            int y      = obj[index]["y"].ToInt();
            int radius = obj[index]["radius"].ToInt();

            canvas.circleMidPoint(Location(x,y),radius);
        }else if(shape == "interpolate"){

            string quad[4] = {"c00","c01","c10","c11"};

            Color c[4];

            for(int i = 0;i < 4;i++){

                if(obj[index][quad[i]].IsNull() && i!=0){
                    for(int j = i;j < 4;j++){
                        c[j] = c[i];
                    }
                    break;
                }
            
                int r = obj[index][quad[i]]["r"].ToInt();
                int g = obj[index][quad[i]]["g"].ToInt();
                int b = obj[index][quad[i]]["b"].ToInt();


                c[i] = Color(r,g,b);
            }

            canvas.interpolate(c[0],c[1],c[2],c[3]);
        }
    }
}
*/