/*
 * graph.h
 *
 *  Created on: 3/11/2018
 *      Author: pperezm
 */
#include <iostream>
#include <exception>
#include <sstream>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

/***********************************************************/
/*********************** WeightedGraph *********************/
/***********************************************************/

template<class Vertex, class Edge>
class WeightedGraph {
public:
	virtual void addEdge(Vertex, Vertex, Edge) = 0;
	virtual bool containsVertex(Vertex) const = 0;
	virtual std::vector<Vertex> getVertexes() const = 0;
	virtual std::map<Vertex, Edge> getConnectionFrom(Vertex) const = 0;
	virtual std::string toString() const = 0;
};



/***********************************************************/
/************************ WListGraph ***********************/
/***********************************************************/

template<class Vertex, class Edge>
class WListGraph : public WeightedGraph<Vertex, Edge>{
private:
	bool direction;
	std::set<Vertex> vertexes;
	std::map<Vertex, std::map<Vertex, Edge> > edges;

public:
	WListGraph(bool dir = true);
	void addEdge(Vertex, Vertex, Edge);
	bool containsVertex(Vertex) const;
	std::vector<Vertex> getVertexes() const;
	std::map<Vertex, Edge> getConnectionFrom(Vertex) const;
	std::string toString() const;
};

template <class Vertex, class Edge>
WListGraph<Vertex, Edge>::WListGraph(bool dir) {
	direction = dir;
}

template <class Vertex, class Edge>
void WListGraph<Vertex, Edge>::addEdge(Vertex from, Vertex to, Edge cost) {
	typename std::set<Vertex>::iterator it;

	it = vertexes.find(from);
	if (it == vertexes.end()) {
		vertexes.insert(from);
		edges.insert(std::pair<Vertex, std::map<Vertex, Edge> >(from, std::map<Vertex, Edge>()));
	}

	it = vertexes.find(to);
	if (it == vertexes.end()) {
		vertexes.insert(to);
		edges.insert(std::pair<Vertex, std::map<Vertex, Edge> >(to, std::map<Vertex, Edge>()));
	}

	edges[from].insert(std::pair<Vertex, Edge>(to, cost));
	if (!direction) {
		edges[to].insert(std::pair<Vertex, Edge>(from, cost));
	}
}

template <class Vertex, class Edge>
bool WListGraph<Vertex, Edge>::containsVertex(Vertex v) const {
	return (vertexes.find(v) != vertexes.end());
}

template <class Vertex, class Edge>
std::vector<Vertex> WListGraph<Vertex, Edge>::getVertexes() const {
	std::vector<Vertex> result(vertexes.begin(), vertexes.end());
	return result;
}

template <class Vertex, class Edge>
std::map<Vertex, Edge> WListGraph<Vertex, Edge>::getConnectionFrom(Vertex v) const {
	/*if (!containsVertex(v)) {
		throw NoSuchElement();
	}*/

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
/*Personalización priority queue*/
struct Compare
{
	template <class Vertex, class Edge>
	bool operator()(std::pair<Vertex, Edge> a, std::pair<Vertex, Edge> b){
		 return a.second > b.second;
	}
};

template <class Vertex, class Edge>
bool encontrar(std::set<std::pair<Vertex, Edge>>s1, Vertex v){
	typename std::set<std::pair<Vertex, Edge>>:: iterator itr;
	for(itr = s1.begin(); itr != s1.end(); itr++){
		if((*itr).first == v){
			return true;
		}
	}
	return false;
}

/***********************************************************/
/************************* Dijkstra ************************/
/***********************************************************/

template <class Vertex, class Edge>
Edge Dijkstra(const Vertex& start, const Vertex& target, const WeightedGraph<Vertex, Edge>* graph) {
	std::set<std::pair<Vertex, Edge>> visited;
	std::priority_queue<std::pair<Vertex, Edge>, std::vector<std::pair<Vertex, Edge>>, Compare> xVisit; 
	typename std::map<Vertex, Edge>::iterator itr;

	xVisit.push(make_pair(start, 0));

	Edge result;

	while (!xVisit.empty()) {
		Vertex v = xVisit.top().first;  Edge e =xVisit.top().second; xVisit.pop();

		if (encontrar(visited, v) == false) { 
			visited.insert(make_pair(v, e));
			std::map<Vertex, Edge> connected = graph->getConnectionFrom(v);
			for (itr = connected.begin(); itr != connected.end(); itr++) {
				xVisit.push(make_pair(itr->first, e + itr->second));
			}
		}
		if(v == target){
			result = e;
			break;
		}
	}	

	return result;
	
}                                                                                                                                       




bool differenceOfOne(std::string, std::string);
std::vector<std::string> separateString(std::string);

int main(int argc, char* argv[]) {
    int t, n;
    std::string palabra;
    typename  std::map<int, std::set<std::string>> :: iterator i;
    typename std::set<std::string> :: iterator j;

    std::cin>> t;

    while(t--){
        std::map<int, std::set<std::string>> aux;
        WListGraph<std::string, int>* wordGraph = new WListGraph<std::string, int>(false);

            for(;;){
                std::cin>> palabra;
                if(palabra == "*")
                    break;
                n = palabra.size();
                i = aux.find(n);
                if(i == aux.end())
                    aux[n].insert(palabra);
                else{ 
                    for(j = (*i).second.begin(); j !=(*i).second.end();j++){
                        if(differenceOfOne(*j, palabra)){
                            wordGraph->addEdge(*j, palabra, 1);
                        }
                    }
                    aux[n].insert(palabra);
                }
            }
			//std::cout<<"\n"<<wordGraph->toString();
			std::string query;
			std::vector<std::string> string_vec;

			for(int r = 0; r < 3; r++){
				fflush(stdin);
				std::getline(std::cin, query);
				string_vec = separateString(query);
				std::cout<< string_vec[0] << " "<< string_vec[1] <<" "<< Dijkstra(string_vec[0], string_vec[1], wordGraph)<<std::endl;
			}
            

    }

    

    system("pause");
    return 0;
}


bool differenceOfOne(std::string one, std::string two){
    int cont = 0;

    for(int i = 0 ; i< one.size(); i++){
        if(one[i] != two[i])
            cont++;
    }

    return (cont == 1);
}

std::vector<std::string> separateString(std::string s){
	std::vector<std::string> v;
	std::string aux;
	std::stringstream input_stringstream(s);

		while (std::getline(input_stringstream, aux, ' ')){
			v.push_back(aux);
		}


	return v;

}