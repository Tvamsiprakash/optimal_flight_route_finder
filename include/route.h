#ifndef ROUTE_H
#define ROUTE_H
#include<string>

class Route {

    private:
        const std::string& airline;
        int airline_Id;
        const std::string& src_Airport;
        int src_Airport_Id;
        const std::string& dest_Airport;
        int dest_Airport_Id;
        int stops;
        double time;
        double cost;

    public:
        Route(const std::string& airline, int airline_Id, const std::string& src_Airport,
            int src_Airport_Id, const std::string& dest_Airport, int dest_Airport_Id, int stops, double time, double cost);

        int getairlineId() const;
        const std::string& getairline() const;
        int getSrcId() const;
        int getDestId() const;
        const std::string& getSrcAirport() const;
        const std::string& getDestAirport() const;
        int getStops() const;
        double  getTime() const;
        double getCost() const;

};
#endif