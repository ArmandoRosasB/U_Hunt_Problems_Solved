#include <iostream>
#include <stdlib.h>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <exception>
#include <string>
#include <sstream>
#include <cstdio>


/*********** Exception ***********/
class Exception : public std::exception {
protected:
	std::string text;

public:
	Exception() throw();
	~Exception() throw();
	virtual const char* what() const throw();
};

Exception::Exception() throw ()
	: text("Basic exception") {
}

Exception::~Exception() throw () {}

const char* Exception::what() const throw() {
	return text.c_str();
}

/*********** NoSuchElement ***********/
class NoSuchElement : public Exception {
public:
	NoSuchElement() throw();
};

NoSuchElement::NoSuchElement() throw () {
		text = std::string("NoSuchElement");
}


template<class Vertex, class Edge>
class WListGraph {
    private:
        bool direction; // False
        std::set<Vertex> vertexes;
        std::map<Vertex, std::map<Vertex, Edge>> edges;

    public:
        WListGraph();
        WListGraph(bool);
        void addEdge(Vertex, Vertex, Edge);
        bool containsVertex(Vertex) const;
        std::vector<Vertex> getVertexes() const;
        std::map<Vertex, Edge> getConnectionFrom(Vertex) const;
        std::string toString() const;

};

template <class Vertex, class Edge>
WListGraph<Vertex, Edge>:: WListGraph(){
    this-> direction = true;
}

template <class Vertex, class Edge>
WListGraph<Vertex, Edge>:: WListGraph(bool direction){
    this-> direction = direction;
}

template <class Vertex, class Edge>
void WListGraph<Vertex, Edge> :: addEdge(Vertex from, Vertex to, Edge cost){
    typename std::set<Vertex>:: iterator it;

    it = vertexes.find(from);
    if (it == vertexes.end()){
        vertexes.insert(from);
        edges.insert(std::pair<Vertex, std::map<Vertex, Edge>>(from, std::map<Vertex, Edge>()));
    }

    it = vertexes.find(to);
    if (it == vertexes.end()){
        vertexes.insert(to);
        edges.insert(std::pair<Vertex, std::map<Vertex, Edge>>(to, std::map<Vertex, Edge>()));
    }

    edges[from].insert(std::pair<Vertex, Edge>(to, cost));
    if (!direction){
        edges[to].insert(std::pair<Vertex, Edge>(from, cost));
    }
}

template <class Vertex, class Edge>
bool WListGraph<Vertex, Edge>::containsVertex(Vertex v) const {
	return (vertexes.find(v) != vertexes.end());
}

template <class Vertex, class Edge>
std:: vector<Vertex> WListGraph<Vertex, Edge> :: getVertexes() const {
    std::vector<Vertex> aux;

    typename std::set<Vertex>:: iterator it;
    for(it = vertexes.begin(); it != vertexes.end(); it++){
        aux.push_back(*it);
    }

    return aux;
}

template <class Vertex, class Edge>
std::map<Vertex, Edge> WListGraph<Vertex, Edge>:: getConnectionFrom(Vertex v) const{
    typename std::map<Vertex, std::map<Vertex, Edge>>:: iterator it;

    if(!containsVertex(v)){
        throw NoSuchElement();
    }
    std::map<Vertex, Edge> result(edges.at(v).begin(), edges.at(v).end());
	return result;
}

template <class Vertex, class Edge>
std::string WListGraph<Vertex, Edge>::toString() const {
	std::stringstream aux;

	typename std::set<Vertex>::iterator i;
	typename std::map<Vertex, Edge>::const_iterator j;

	for (i = vertexes.begin(); i != vertexes.end(); i++) {
		aux << (*i) << "\t";
		for (j = edges.at((*i)).begin(); j != edges.at((*i)).end(); j++) {
			aux << "(" << j->first << "," << j->second << ")\t";
		}
		aux << "\n";
	}
	aux << "\n";
	return aux.str();
}

template <typename Vertex, typename Edge>
bool findVertex(std::set<std::pair<Vertex, Edge>> vertexes, Vertex target){
    typename std::set<std::pair<Vertex, Edge>>:: iterator it;

    for(it = vertexes.begin(); it != vertexes.end(); it++){
        if (it->first == target){
            return true;
        }
    }
    return false;
}

// Compare Priority Queue
struct Compare
{
	template <class Vertex, class Edge>
	bool operator()(std::pair<Vertex, Edge> a, std::pair<Vertex, Edge> b){
		 return a.second > b.second;
	}
};


// Dijkstra
template <typename Vertex, typename Edge>
Edge Dijkstra(const Vertex& start, const Vertex& target, const WListGraph<Vertex, Edge>* graph){
    std::set<std::pair<Vertex, Edge>> visited;
    std::priority_queue<std::pair<Vertex, Edge>, std::vector<std::pair<Vertex, Edge>>, Compare> xVisit; 

    typename std::map<Vertex, Edge>:: iterator it;
    Edge totalDelay = -1;

    xVisit.push(std::pair<Vertex, Edge>(start, 0));

    while (!xVisit.empty()){
        Vertex v = xVisit.top().first; Edge e = xVisit.top().second; xVisit.pop();

        if (!findVertex(visited, v)){
            visited.insert(std::pair<Vertex, Edge>(v, e));

            std::map<Vertex, Edge> conections = graph->getConnectionFrom(v);
            for(it = conections.begin(); it != conections.end(); it++){
                xVisit.push(std::pair<Vertex, Edge>(it->first, e + it->second));
            }
        }

        if (v == target){
            totalDelay = e;
            return totalDelay;
        }
        
    }
    return totalDelay;
}


int main (int artc, char* argv[]){
    int N, i = 1;
    int n, m, S, T;
    int from, to, delay, totalDelay;

    std::cin >> N;

    while (N--){
        WListGraph<int, int>* servers = new WListGraph<int, int>(false);

        std::cin >> n >> m >> S >> T;       

        if (m == 0){
            std::cout << "Case #" << i++ << ": unreachable"<< std::endl;
            continue;
        }
        while (m--){
            std::cin >> from >> to >> delay;
            servers->addEdge(from, to, delay);
        }

        int totalDelay = Dijkstra(S, T, servers);

        if(totalDelay != 0){
            std::cout << "Case #" << i++ << ": "<< totalDelay << std::endl;
        }
        else {
            std::cout << "Case #" << i++ << ": unreachable"<< std::endl;

        }
  
    }

    system("pause");
    return  0;
}