#include <iostream>
#include <stdlib.h>


using namespace std;

int bubbleSort(int*, int);
void swap(int*&, int, int);

int main(int argc, char* argv[]){
    int t, n, swaps;
    int *train;

    cin>> t;

    while (t--){
        cin >> n;
        train = new int[n];

        for(int i = 0; i < n; i++){
            cin >> train[i];
        }

        swaps = bubbleSort(train, n);
        cout<<"Optimal train swapping takes " << swaps << " swaps."<<endl;

    }


    system("pause");
    return 0;
}

int bubbleSort(int* arr, int n){
    int acum = 0;
    for(int i = 0; i < n; i++){
        for(int j = 1; j < n - i; j++){
            if (arr[j - 1] > arr[j]){
                swap(arr, j - 1, j);
                acum++;
            }
        }
    }
    return acum;
}

void swap(int*& arr, int i , int j){
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}