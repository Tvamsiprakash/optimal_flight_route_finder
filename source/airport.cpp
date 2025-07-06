#include "airport.h"

Airport::Airport(int airportId, const std::string& airportName, const std::string& airportCity, const std::string& airportCountry, 
        const std::string& iata, double latitude, double longitude)
    : airportId(airportId), airportName(airportName), airportCity(airportCity), airportCountry(airportCountry), iata(iata), latitude(latitude), longitude(longitude){}

//get airport id
int Airport::getAirportId() const { return airportId; }
//get airport name
const std::string& Airport::getAirportName() const { return airportName; }
//get airport city
const std::string& Airport::getAirportCity() const { return airportCity; }
//get airport country
const std::string& Airport::getAirportCountry() const { return airportCountry; }
//get airport iata code
const std::string& Airport::getiata() const { return iata; }
//get latitude 
double Airport::getLatitude() const { return latitude; }
//get longitude
double Airport::getLongitude() const { return longitude; }

