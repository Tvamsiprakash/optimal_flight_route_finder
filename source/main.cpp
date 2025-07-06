#include <iostream>
#include <fstream>
#include "graph.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: ./flight_route <srcId> <destId> <mode>" << endl;
        return 1;
    }

    string srcCode = argv[1];
    string destCode = argv[2];
    string mode = argv[3];

    if (mode != "time" && mode != "cost" && mode != "stops") {
        cerr << "Invalid mode. Use 'time', 'cost', or 'stops'." << endl;
        return 1;
    }

    Graph graph;
    graph.loadAirports("data/airports.dat");
    graph.loadRoute("data/routes.dat");
    if (graph.codeToId.find(srcCode) == graph.codeToId.end()) {
        cerr << "Source airport code not found: " << srcCode << endl;
        cerr << "Valid codes include: ";
        for (const auto& pair : graph.codeToId) {
            cerr << pair.first << " ";
        }
        cerr << endl;
        return 1;
    }
    if (graph.codeToId.find(destCode) == graph.codeToId.end()) {
        cerr << "Destination code not found: " << destCode << endl;
        return 1;
    }
    
    int srcId = graph.codeToId[srcCode];
    int destId = graph.codeToId[destCode];

    vector<int> path = graph.dijkstra(srcId, destId, mode);
    
    if (!path.empty()) {
        graph.exportOutputTojson("route.json", path);
    } else {
        cerr << "No path found" << endl;
        return 2;
    }

    return 0;
}
