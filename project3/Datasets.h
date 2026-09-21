#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "TimeSeries.h"

class Datasets;

// Defining class Datasets for storing country years, country codes, and the data for each series
class Datasets{
    // All public variables are declared here
    public:
        // The constructor and destructor for datasets to make sure the variables are declared and destructed to prevent memory leak.
        Datasets() : head(nullptr){};
        ~Datasets();

        // The function to load all data for one country of the .csv file.
        void LOAD_P2(std::string country_name);

        // List the country name, country code, and all series names.
        void LIST_P2();

        // Add a data given a series code, year, and data.
        void ADD_P2(std::string Series_Code, int year, double data);

        // Update a data given a series code, year, and data.
        void UPDATE_P2(std::string Series_Code, int year, double data);

        // Print all valid data with corresponding years for a given series code
        void PRINT_P2(std::string Series_Code);

        // Delete all nodes to prevent memory leak
        void DELETE_P2(std::string Series_Code);

        // Find the series with biggest mean
        void BIGGEST_P2();

        // Output a string with the size and capacity of year and data arrays with a given series code
        void TS_P2(std::string Series_Code);

        // Return the corresponding country name
        std::string getCountryName() const;

        // Return the corresponding country code
        std::string getCountryCode() const;

        // Return the corresponding series code with smallest mean
        std::string getSeriesCodeForSmallestMean() const;

        // Returns the mean given a series code
        double getMean(std::string Series_Code) const;

        void ADD_TimeSeries(TimeSeries *timeseries);

        void setCountryName(std::string CountryName);
        void setCountryCode(std::string CountryCode);

    private:
        // Variables to store country name and country code
        std::string CountryName;
        std::string CountryCode;

        // The node class inside Datasets class in order to create a linkedlist to store data for each series
        class Node{
            public: 
                TimeSeries *baka;
                Node *next;
                Node(){
                    next = nullptr;
                    baka = nullptr;
                }
                Node(Node* n, TimeSeries* a);
        };

        Node *head = nullptr;
        Node *current = nullptr;
};