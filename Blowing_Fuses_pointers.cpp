#include <iostream>
#include <stdlib.h>


using namespace std;

void change(int*, int*, int, int&);


int main(int argc, char* argv[]){
    int n, m, c;
    /*n: number of devices
      m: number of operations 
      c: capacity of the fuse
    */
    int *capacity, *state, *cases;
    int sequence = 1;
    while (true){
        int max, acum = 0;
        bool flag = false;
        cin>>n >> m >> c;

        if((n == 0) && (m == 0) && (c == 0))
            break;
        
        capacity = new int[n];
        state = new int[n];
        cases = new int[m];
        
        for(int i = 0; i<n; i++){
            cin>>capacity[i];
            state[i] = 0;
        }
        for(int i = 0; i<m; i++){
            cin>> cases[i];
        }

        for(int i = 0; i<m; i++){
            change(capacity, state, cases[i] - 1, acum);
            if(i == 0){
                max = acum;
            }
            if(acum > max){
                max = acum;
            }
            if(acum > c){
                flag = true;
                break;
            }
        }

        cout<< "Sequence "<< sequence++ <<endl;
        if(flag == false){
            cout<< "Fuse was not blown."<<endl;
            cout<< "Maximal power consumption was "<< max << " amperes."<<endl<<endl;
        } else if(flag == true){
            cout<< "Fuse was blown."<<endl<<endl;
        }	

    }

    system("pause");
    return 0;
}


void change(int* arr1, int* arr2, int position, int& collector){
    if(arr2[position] == 0){
        arr2[position] = 1;
        collector += arr1[position];
        return;
    }
    else if(arr2[position] == 1){
        arr2[position] = 0;
        collector -= arr1[position];
        return;
    }
}