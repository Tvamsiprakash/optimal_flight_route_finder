#ifndef AIRPORT_H
#define AIRPORT_H
#include <string>

class Airport {
    private:
        int airportId;
        std::string airportName;
        std::string airportCity;
        std::string airportCountry;
        std::string iata;
        double latitude;
        double longitude;
    public:
        Airport() = default;
        Airport(int airportId, const std::string& airportName, const std::string& airportCity, const std::string& airportCountry, 
        const std::string& iata, double latitude, double longitude);
        int getAirportId() const;
        const std::string& getAirportName() const;
        const std::string& getAirportCity() const;
        const std::string& getAirportCountry() const;
        const std::string& getiata() const;
        double getLatitude() const;
        double getLongitude() const;
};


#endif