#include "route.h"

Route::Route(const std::string& airline, int airline_Id,const std::string& src_Airport,int src_Airport_Id,const std::string& dest_Airport,
            int dest_Airport_Id, int stops, double time, double cost)
        : airline(airline), airline_Id(airline_Id), src_Airport(src_Airport), src_Airport_Id(src_Airport_Id), dest_Airport(dest_Airport), dest_Airport_Id(dest_Airport_Id)
        ,stops(stops), time(time), cost(cost) {}
//get airline id
int Route::getairlineId() const { return airline_Id; };
//get airline 
const std::string& Route::getairline() const { return airline;};
//get source airport id
int Route::getSrcId() const { return src_Airport_Id;};
//get destination airport id
int Route::getDestId() const {return dest_Airport_Id;};
//get source airport code
const std::string& Route::getSrcAirport() const {return src_Airport;};
//get destination airport 
const std::string& Route::getDestAirport() const {return dest_Airport;};
//get no of stops
int Route::getStops() const {return stops;};
//get time
double  Route::getTime() const {return time;};
//get cost
double Route::getCost() const {return cost;};