#ifndef GRAPH_H
#define GRAPH_H

#include<string>
#include<unordered_map>
#include<utility>
#include "airport.h"
#include "route.h"
#include<vector>
#include<queue>
using namespace std;

class Graph {
    public:
        unordered_map<int, Airport> airports;
        vector<Route> routes;
        unordered_map<int, vector<pair<int, Route>>> adj_list;
        unordered_map<string, int> codeToId;
        unordered_map<int, string> idToCode;


        //functions to add airports and routes
        void addairports(const Airport& airport);
        void addRoute(const Route& route);

        //loaders
        void loadAirports(const string& filename);
        void loadRoute(const string& filename);

        vector<int> dijkstra(int srcId, int destId, const string& mode);

        //getter methods
        const unordered_map<int, Airport>& getAirports() const;
        const vector<Route>& getRoutes() const;

        void exportOutputTojson(const string& filename, const vector<int>& path) const;

};

#endif