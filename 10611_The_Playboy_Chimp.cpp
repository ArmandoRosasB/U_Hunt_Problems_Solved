#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <vector>

using namespace std;


int lowBinarySearch(vector<int>, int, int, int);
int highBinarySearch(vector<int>, int, int, int);

int main(int argc, char* argv[]){
    int n, q, height, aux;
    cin >> n;
    vector<int> chimpLadies;

    for(int i = 0; i < n; i++)
    {
        cin>> aux;

        if (i != 0){
            if (chimpLadies.back() == aux){
                continue;
            }
        }
        chimpLadies.push_back(aux);
    }

    cin >> q;
    
    while (q--)
    {   
        cin >> height;
        aux  = lowBinarySearch(chimpLadies, 0, chimpLadies.size() - 1, height);
        if (aux != -1){
            cout<< aux << " ";
        }
        else{
            cout<< "X ";
        }

        aux  = highBinarySearch(chimpLadies, 0, chimpLadies.size() - 1, height);

        if (aux != -1){
            cout<< aux << endl;
        }
        else{
            cout<< "X" << endl;
        }
       
    }

    system("pause");
    return 0;
}

int lowBinarySearch(vector<int> preys, int start, int end, int target){
    int mid;
    while (start <= end){
        mid = (start + end) / 2;
        if (preys[mid] == target){
            if(mid == 0){
                return -1;
            }
            return preys[mid - 1];
        }

        if (preys[mid] > target)
            end = mid - 1;

        else if (preys[mid] < target)
            start = mid + 1;
    }

    if (end < 0)
        return -1;

    return preys[end];  
   
}

int highBinarySearch(vector<int> preys, int start, int end, int target){
    int mid;
    while (start <= end){
        mid = (start + end) / 2;

        if (preys[mid] == target){
            if(mid == preys.size() - 1){
                return -1;
            }
            return preys[mid + 1];
        }

        if (preys[mid] > target)
            end = mid - 1;
        else if (preys[mid] < target)
            start = mid + 1;
    }

    if (start >= preys.size())
        return -1;

    return preys[start];   
   
} 