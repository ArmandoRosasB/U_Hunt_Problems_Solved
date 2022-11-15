#include  <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class Coordenate{
    private:
        float x;
        float y;

    public: 
        Coordenate(float, float);
        Coordenate();
        ~Coordenate();
        float getX();
        float getY();
        bool compareX(Coordenate);
        bool compareY(Coordenate);
        bool North(Coordenate, Coordenate);
        bool South(Coordenate, Coordenate);
        bool East(Coordenate, Coordenate);
        bool West(Coordenate, Coordenate);

};

Coordenate:: Coordenate(float x, float y){
    this->x = x;
    this->y = y;
}

Coordenate:: Coordenate(){
    x = 0;
    y = 0;
}

Coordenate::~Coordenate(){}

float Coordenate:: getX(){
    return x;
}

float Coordenate:: getY(){
    return y;
}

bool Coordenate:: compareX(Coordenate c){
    if(x > c.x)
        return true;
    return false;
}
bool Coordenate:: compareY(Coordenate c){
    if(y > c.y)
        return true;
    return false;
}


bool Coordenate:: North (Coordenate ini, Coordenate end){
    float mid = (ini.y + end.y)/2;
    if((x >= ini.x) && (x <= end.x)){
        if(y < mid)
            return true;
    }
    return false;

}

bool Coordenate:: South (Coordenate ini, Coordenate end){
    float mid = (ini.y + end.y)/2;
    if((x >= ini.x) && (x <= end.x)){
        if(y > mid)
            return true;
    }
    return false;

}

bool Coordenate:: East (Coordenate ini, Coordenate end){
    float mid = (ini.x + end.x)/2;
    if((y >= ini.y) && (y <= end.y)){
        if(x < mid)
            return true;
    }
    return false;

}

bool Coordenate:: West (Coordenate ini, Coordenate end){
    float mid = (ini.x + end.x)/2;
    if((y >= ini.y) && (y <= end.y)){
        if(x > mid)
            return true;
    }
    return false;

}




void swap(Coordenate*, int, int);

int main(int argc, char* argv[]){
    int walls, x, y;
    Coordenate* coordenates;
    Coordenate shooter;
    while(true) {
        int north = 0, south = 0, east = 0, west = 0, max = 0;

        cin>>walls;
        if(walls == 0){
            break;
        }

        coordenates = new Coordenate[walls * 2];

        for(int i = 0; i<walls * 2; i++){
            cin>>x >> y;
            coordenates[i] = Coordenate(x, y);
        }

        cin>> x >> y;
        shooter = Coordenate(x, y);

        for(int i = 0; i<walls*2; i+=2){
            if(coordenates[i].compareX(coordenates[i+1])){
                swap(coordenates, i, i+1);
            }
            if(shooter.North(coordenates[i], coordenates[i+1]))
                north++;
            if(max < north)
                max = north;
            if(shooter.South(coordenates[i], coordenates[i+1]))
                south++;
            if(max < south) xc                  
                max = south;

            if(coordenates[i].compareY(coordenates[i+1])){
                swap(coordenates, i, i+1);
            }
            
            if(shooter.East(coordenates[i], coordenates[i+1]))
                east++;
            if(max < east)
                max = east;
            if(shooter.West(coordenates[i], coordenates[i+1]))
                west++;
            if(max < west)
                max = west;
            
        }

        cout<< max <<endl;


    }

    system("pause");
    return 0;
}

void swap(Coordenate* c, int posi, int pose){
    Coordenate aux;
    aux = c[posi];
    c[posi] = c[pose];
    c[pose] = aux;

}