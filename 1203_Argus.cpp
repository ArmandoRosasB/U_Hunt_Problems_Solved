#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream> 
#include <queue>

using namespace std;

class query{
    private:
        int id;
        int period;
        int change;
    
    public:
        query(int, int, int);
        query();
        ~query();
        int getId() const;
        int getPeriod() const;
        int getChange() const;
        void applyChange();
        string toString();
};

query:: query(int id, int period, int change){
    this->id = id;
    this->period = period;
    this->change = change;
}

query:: query(){
    id = 0;
    period = 0;
    change = 0;
}
query:: ~query(){}
int query:: getId() const{
    return id;
}

int query::getPeriod() const{
    return period;
}

int query:: getChange() const{
    return change;
}

void query:: applyChange(){
    period += change;
}

string query:: toString(){
    stringstream aux;

    aux << id <<"\n";

    return aux.str();
}


bool operator<(const query& , const query&);



int main (int argc, char* argv[]){
    priority_queue<query> q;

    int id, period, n;
    string condition;

    while (true){
        cin >> condition;
        if(condition == "#")
            break;
        cin>> id >> period;
        q.push(query(id, period, period));
    }

    cin>>n;
    for(int i = 0; i<n; i++){
        query aux = q.top();
        cout<< aux.toString();
        q.pop();
        aux.applyChange();
        q.push(aux);

    }

    system("pause");
    return 0;
}

bool operator<(const query& q1, const query& q2){
    if(q1.getPeriod() == q2.getPeriod())
        return (q1.getId() > q2.getId());
    return (q1.getPeriod()> q2.getPeriod());
}

