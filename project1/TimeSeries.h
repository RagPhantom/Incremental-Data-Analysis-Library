#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// Declaration of class TimeSeries, this class is for analyzing a bunch of data inputs with corresponding years.
class TimeSeries;

// Defining class Timeseries.
class TimeSeries{
    // Defining public functions
    public: 
        // Declaration of the constructor TimeSeries.
        TimeSeries();

        // Declaration of the function mean() that may calculate the mean of all valid data.
        double mean();

        // Declaration of the function is_monotonic() that may verify if the series of all valid data is monotonic.
        bool is_monotonic();

        // Declaration of the function best_fit() that may calculate a best_fit line for all valid data if total valid data number > 1.
        bool best_fit(double &m, double &b);

        // Declaration of the function LOAD_P1 that may receive data inputs.
        void LOAD_P1(std::string filename);

        // Declaration of the function PRINT_P1 that may print all valid data with corresponding years.
        void PRINT_P1();

        // Declaration of the function ADD_P1 that may implement the function of adding a valid data with corresponding year to the existing data and year arrays.
        void ADD_P1(int yearValue, double dataValue);

        // Declaration of the function UPDATE_P1 that may implement the function of updating a valid data in a valid year.
        void UPDATE_P1(int yearValue, double dataValue);

        // Declaration of the function MEAN_P1 that may implement the function of calculating the mean of all valid data by receiving the data and use the function mean() inside it.
        void MEAN_P1();

        // Declaration of the function MONOTONIC_P1 that may implement the function of verifying if the series of all valid data is monotonic by receiving the data and use the function is_monotonic() inside it.
        void MONOTONIC_P1();

        // Declaration of the function FIT_P1 that may implement the function of calculating a best_fit line for all valid data by receiving the data and use the function best_fit() inside it.
        void FIT_P1();

        // Declaration of the function for doubling the size of the array when the length of valid data reaches the limit
        void double_array_size();

        // Declaration of the function for halving the size of the array when the length of valid data equasls to ¼ of the capacity
        void halve_array_size();

        // Declaration of the destructor of TimeSeries class.
        ~TimeSeries();

    private:    
        // How many spaces
        int capacity;
        // How many elements
        int length;
        
        // Declaration of a private variable year array.
        int *year{nullptr};

        // Declaration of a private variable data array.
        double *data{nullptr};

        // Declaration of a private variable CountryName use to store the country name
        std::string CountryName;

        // Declaration of a private variable CountryCode use to store the country code
        std::string CountryCode;
};