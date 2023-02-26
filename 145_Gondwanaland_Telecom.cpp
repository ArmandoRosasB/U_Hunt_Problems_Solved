#include <iostream>


using namespace std;

struct Costos
{
    float costs[3];
} letras[5];



int main(int argc, char* argv[]){
    char charging_step;
    string phone;
    int star_hour, end_hour, star_minute, end_minute;

    letras[0].costs[0] = .1;

    do{
        cin >> charging_step >> phone >> star_hour >> star_minute >>
        end_hour >> end_minute;



    } while (charging_step != '#');

 
    system("pause");
    return;
}