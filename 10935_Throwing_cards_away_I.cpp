#include <iostream>
#include <stdlib.h>
#include <queue>
#include <list>

using namespace std;

void send_to_discarded(list<int>&, queue<int>&);
void send_help(list<int>&);

int main (int argc, char* argv[]){
    int n;
   
    while(true) {
        list<int> deck;
        queue<int> discarded;
        cin>> n;
        if (n == 0)
            break;
        for (int i = 0; i<n; i++){
            deck.push_back(i+1);
        }

        int i = 0;

        while(deck.size() > 1){
            if(i % 2 == 0){
                send_to_discarded(deck, discarded);
            } else{
                send_help(deck);
            }
            i++;
        }
        if (discarded.empty())
            cout<< "Discarded cards:";
        else
            cout<< "Discarded cards: ";
        while(!discarded.empty()){
            if(discarded.size() != 1)
                cout<< discarded.front() <<", ";
            else
                cout<< discarded.front();
            
            discarded.pop();
        }

        cout<<"\nRemaining card: "<< deck.front()<<endl;
        deck.pop_front();
    }

    return 0;
}

void send_to_discarded(list<int>& l1, queue<int>& q1){
    q1.push(l1.front());
    l1.pop_front();
}

void send_help(list<int>& l1){
    l1.push_back(l1.front());
    l1.pop_front();
}