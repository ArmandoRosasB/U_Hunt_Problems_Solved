#include <iostream>
#include <stdlib.h>
#include <queue>
#include <map>
#include <iterator>

using namespace std;

bool blackOrWhite(int);

int main(int argc, char* argv[]){
    int t, aux;
    int n1, n2, n3, n4, n5;
    int countBlack, countWhite;

    while(true){
        cin >> t;

        if(t == 0)
            break;
        
        map<char, int> answers;
        queue<int> query;

        for(int i = 0; i<t; i++){
            cin>> n1 >> n2 >> n3 >> n4 >> n5; 
            query.push(n1);
            query.push(n2);
            query.push(n3);
            query.push(n4);
            query.push(n5);
        }      

        int i = 1;
        countBlack = 0;
        countWhite = 0;

        while(!query.empty()){
            aux = query.front();
            query.pop();

            if (blackOrWhite(aux))
                countBlack++;
            
            else
                countWhite++;
            
            switch(i){
                case 1:
                    answers['A'] = blackOrWhite(aux);
                    break;

                case 2:
                    answers['B'] = blackOrWhite(aux);
                    break;

                case 3:
                    answers['C'] = blackOrWhite(aux);
                    break;

                case 4:
                    answers['D'] = blackOrWhite(aux);
                    break;

                case 5:
                    answers['E'] = blackOrWhite(aux);
                    break;
            }
            if (i == 5){
                if(countBlack == 1){
                    for(auto itr = answers.begin(); itr != answers.end();itr++){
                        if((*itr).second == 1){
                            cout<< (*itr).first<<endl;
                            break;
                        }
                    }
                }

                else if(countBlack > 1 || countBlack == 0){
                    cout<< "*"<<endl;
                }      

                i = 0;
                countBlack = 0;
                countWhite = 0;
            }
                        
            i++;
        }

    	
    }

    system("pause");
    return 0;
}

bool blackOrWhite(int n){
    if (n > 127)
        return 0;
    else
        return 1;
}