#include "airport.h"
#include "route.h"
#include "graph.h"
#include <nlohmann/json (1).hpp>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;
using json = nlohmann::json;

void Graph::addairports(const Airport& airport) {
    if(airports.find(airport.getAirportId()) == airports.end()) {
        airports[airport.getAirportId()] = airport;
    }
}

void Graph::addRoute(const Route& route) {
    routes.push_back(route);
    adj_list[route.getSrcId()].push_back(make_pair(route.getDestId(), route));
}

void Graph::loadAirports(const string& filename) {
    ifstream file(filename);
    if(!file.is_open()) {
        cout << "error opening the file" << filename << endl;
        return;
    }
    string line;
    int total_airports = 0;
    while(getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while(getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if(tokens.size() < 8) {
            cerr << "Invalid format in line" << endl;
            continue;
        }
        try {
            int airportId = stoi(tokens[0]);
            string airportName = tokens[1];
            string airportCity = tokens[2];
            string airportCountry = tokens[3];

            string iata = tokens[4];
            // Remove quotes and check for empty/NULL values
            iata.erase(remove(iata.begin(), iata.end(), '\"'), iata.end());
            if (iata == "\\N" || iata.empty()) continue;  // Skip invalid codes

            // Only store valid 3-letter codes
            if (iata.length() == 3 && isalpha(iata[0])) {
                codeToId[iata] = airportId;
                idToCode[airportId] = iata;
            }
            double latitude = stod(tokens[6]); 
            double longitude = stod(tokens[7]);
            Airport airport(airportId, airportName, airportCity, airportCountry, iata, latitude, longitude);

            addairports(airport);
            ++total_airports;

        } catch(const std::invalid_argument& e) {
            cout << "Error: There is invalid data in line" << line << ".Exception" << e.what() << endl;
        } catch(const std::out_of_range& e) {
            cout << "Error: Out of range" << line << ".Exception" << e.what() << endl;
        }
    }
    cout << total_airports << "are Loaded" << endl;
}

void Graph::loadRoute(const string& filename) {
    ifstream file(filename);
    if(!file.is_open()) {
        cerr << "Error in opening the file" << filename << endl;
    }
    string line;
    int total_routes = 0;
    while(getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while(getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if(tokens.size() < 8) {
            cerr << "Error: Invalid format in the line" << endl;
            continue;
        }
        try {
            string airline = tokens[0];
            int airline_Id = (tokens[1] == "\\N" || tokens[1].empty()) ? 0 : stoi(tokens[1]);
            string src_Airport = tokens[2];
            int src_Airport_Id = (tokens[3] == "\\N" || tokens[3].empty()) ? 0 : stoi(tokens[3]);
            string dest_Airport = tokens[4];
            int dest_Airport_Id = (tokens[5] == "\\N" || tokens[5].empty()) ? 0 : stoi(tokens[5]);
            int stops = (tokens[7] == "\\N" || tokens[7].empty()) ? 0 : stoi(tokens[7]);
            double time = 1.0;
            double cost = 100;

            Route route(airline, airline_Id, src_Airport, src_Airport_Id, dest_Airport, dest_Airport_Id, stops, time, cost);
            addRoute(route);
            ++total_routes;
        } catch (const std::invalid_argument& e) {
            cerr << "Error: Invalid data in Line" << line << ".Exception" << e.what() << endl;
        } catch (const std::out_of_range& e) {
            cerr << "Error: Out of range in data" << line << ".Exception" << e.what() << endl;
        }
    }
}

vector<int> Graph::dijkstra(int srcId, int destId, const string& mode) {
    unordered_map<int, double> dist;
    unordered_map<int, int> prev;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    
    for(const auto& airport: airports) {
        dist[airport.first] = numeric_limits<double>::infinity();
        prev[airport.first] = -1;
    }
    dist[srcId] = 0;
    pq.push({0.0, srcId});

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if(u == destId) break;
        for(const auto& neighbour: adj_list[u]) {
            int v = neighbour.first;
            const Route& route = neighbour.second;
            double weight;
            if(mode == "time") {
                weight = route.getTime();
            }else if(mode == "cost") {
                weight = route.getCost();
            }else {
                weight = route.getStops();
            }
            double alt = dist[u] + weight;
            if(alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.push({alt, v});
            }
        }
    }
    vector<int> path;
    for(int at = destId; at != -1; at = prev[at]){
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    if(path.size() == 1 && path[0] != srcId) {
        return {};
    }
    return path;
}


const unordered_map<int, Airport>& Graph::getAirports() const{
    return airports;
}

const vector<Route>& Graph::getRoutes() const {
    return routes;
}

void Graph::exportOutputTojson(const string& filename, const vector<int>& path) const {
    json j;
    for(int id: path) {
        const Airport& a = airports.at(id);
        j["route"].push_back({
            {"id", a.getAirportId()},
            {"name", a.getAirportName()},
            {"lat", a.getLatitude()},
            {"lon", a.getLongitude()}
        });
    }
    ofstream o(filename);
    if (o.is_open()) {
        o << j.dump(4);  // Pretty print with 4-space indentation
        o.close();
    } else {
        cerr << "Unable to open file for writing: " << filename << endl;
    }
}
