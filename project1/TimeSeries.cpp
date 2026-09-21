#include "TimeSeries.h"

// Constructor of TimeSeries class
TimeSeries::TimeSeries():
// The capacity of dynamic arrays (both data and year)
capacity{2},
// The length (valid data number) of dynamic arrays (both data and year)
length{0}
{   
    // Declaration of the capacity of dynamic arrays (both data and year)
    year = new int[2]{};

    // Declaration of the length (valid data number) of dynamic arrays (both data and year)
    data = new double[2]{};
}

// Destructor of TimeSeries class
TimeSeries::~TimeSeries(){
    // Deallocate the memory for dynamic array year
    delete[] year;

    // Deallocate the memory for dynamic array data
    delete[] data;
    
    // Assigning a null pointer to the location of year
    year = nullptr;

    // Assigning a null pointer to the location of data
    data = nullptr;
}

// The function mean() that may calculate the mean of all valid data.
double TimeSeries::mean(){
    // Return 0 if there is no valid data
    if (length == 0){
        return 0;
    }

    // If there is valid data
    else{
        // Create a container for the final mean
        double Value{0};
        // Add all valid data together
        for (int i = 0; i < length; i++){
            Value += data [i];
        }
        // Mean = valid data / length
        Value = Value / length;
        // Return value
        return Value;
    }
}

// The function is_monotonic() that may verify if the series of all valid data is monotonic
bool TimeSeries::is_monotonic(){
    // Return 0 if there is no valid data
    if (length == 0){
        return false;
    }
    // Return 1 if there is only 1 valid data (monotonic)
    else if (length == 1){
        return true;
    }
    // If there are more than 1 valid data and the first data is smaller than the second one
    else if (data[0] < data[1]){
        // Determine if the series is monotonic by looping, judging if every later data is greater than the earlier one
        for (int i = 1; i < length; i++){
            if (data [i-1] > data [i]){
                // If one data does not fit in this trend of every later data is greater than the earlier one, return false
                return false;
            }
        }
        // If all data are in the trend of every later data is greater that the earlier one, return true
        return true;
    }
    // Else, if there are more than 1 valid data and the first data is greater than the second one
    else{
        // Determine if the series is monotonic by looping, judging if every later data is smaller than the earlier one
        for (int i = 1; i < length; i++){
            if (data [i-1] < data [i]){
                // If one data does not fit in this trend of every later data is smaller than the earlier one, return false
                return false;
            }
        }
        // If all data are in the trend of every later data is smaller that the earlier one, return true
        return true;
    }
}

// The function best_fit() that may calculate a best_fit line for all valid data if total valid data number > 1
bool TimeSeries::best_fit(double &m, double &b){
    // Set the slope and y-intercept to 0 if there is no valid data, and return false
    if (length == 0){
        m = 0;
        b = 0;
        return false;
    }

    // Some variables used later in the calculation of slope and y-intercept
    double xiSum{0};
    double yiSum{0};
    double SumOfxiyi{0};
    double xiSumyiSum{0};
    double xiSumSquare{0};
    double xiSquareSum{0};

    // Calculating some intermediate variables for later calculation of slope and y-intercept
    for (int i{0}; i < length; i++){
        xiSum += year[i];
        yiSum += data[i];
        SumOfxiyi += year[i] * data[i];
        xiSquareSum += year[i] * year[i];
    }
    xiSumyiSum += xiSum*yiSum;
    xiSumSquare = xiSum*xiSum;

    // Calculating the slope
    m = ((length * SumOfxiyi) - xiSumyiSum) / ((length * xiSquareSum) - xiSumSquare);

    // Calculating the y-intercept
    b = (yiSum - m*xiSum) / length;

    // Return true after calculations when there is valid data
    return true;
}

// The function LOAD_P1 that may receive data inputs
void TimeSeries::LOAD_P1(std::string filename){
    // A string type variable to store the string get from the command line
    std::string line;
    
    // An ifstream type variable to parse the string get from the command line
    std::ifstream file(filename);

    // While there are inputs
    while(std::getline(file, line)){
        // A variable to store each string in each line separated by ','
        std::string Value;
        
        // A variable to parse a line of input
        std::stringstream ss(line);

        // A counter to count the number of valid data in the input
        int counter{0};

        // A counter to count the year number from 1960
        int YearCounter{1960};

        // While getting a line of input
        while(std::getline(ss,Value,',')){
                // A variable to parse the string of input
                std::stringstream sss(Value);

                // If the counter == 2, means it is inputting the 3rd column, which corresponding to the countryname
                if (counter == 2){
                    CountryName = Value;
                }

                // If the counter == 3, means it is inputting the 4th column, which corresponding to the countrycode
                else if (counter == 3){
                    CountryCode = Value;
                }

                // If the counter > 3, it is inputting data
                else if (counter > 3){
                    // A variable to store one temporary data
                    double TempData;

                    // Read the temporary data into the variable
                    sss >> TempData;

                    // If the data is a valid data
                    if (TempData >= 0){
                        
                        // Judge if need to double the size of the array
                        if (length == capacity){
                        double_array_size();
                        }

                        // Store the year into year array
                        year[length] = YearCounter;

                        // Store the data into data array
                        data[length] = TempData;

                        // Increment the length for both arrays
                        length++;
                    }
                    // Increment the year number after parsing the current data
                    YearCounter++;
                }
                // Increment the counter (which column of data it is inputting)
                counter++;
            }
        }
    // Print success after loading data    
    std::cout << "success" << std::endl;
}

// The function PRINT_P1 that may print all valid data with corresponding years.
void TimeSeries::PRINT_P1(){
    // Print failure if there is no valid data
    if (length == 0){
        std::cout << "failure" << std::endl;
    }

    // If there is valid data
    else{
        // Print each element in year array and data array if there is a valid data with corresponding year
        for (int i{0}; i < length - 1; i++){
            if (data[i] >= 0){
                std::cout << '(' << year[i] << ',' << data[i] << ") ";
            }
        }
        // Print the last element in year array and data array if there is a valid data with corresponding year
        if (data[length-1] >= 0){
            std::cout << '(' << year[length - 1] << ',' << data[length - 1] << ')';
        } 
        std::cout << std::endl;
    }
}

// The function ADD_P1 that may implement the function of adding a valid data with corresponding year to the existing data and year arrays
void TimeSeries::ADD_P1(int yearValue, double dataValue){
    // A boolean variable to store if the user input year is already in the year array
    bool exist = false;
    for (int i{0}; i < length; i++){
        // If the user input year already exist, print failure
        if (yearValue == year[i]){
            exist = true;
            std::cout << "failure" << std::endl;
            }
        }
    // If the user input year does not exist, print success  
    if (!exist){
        std::cout << "success" << std::endl;
        // If the valid data number reaches capacity, double the array size
        if (length == capacity){
            double_array_size();
        }
        // Find the index to insert data
        int index{length};
        for (int i{0}; i < length; i++){
            if ((year[i]) > yearValue){
                index = i;
                break;
            }
        }
        // Shift each element in both array 1 to the right
        for (int i = length; i > index; i--){
            year[i] = year[i-1];
            data[i] = data[i-1];
        }
        // Insert the data and year into the array
        year[index] = yearValue;
        data[index] = dataValue;
        length++;
    }
}

// The function UPDATE_P1 that may implement the function of updating a valid data in a valid year
void TimeSeries::UPDATE_P1(int yearValue, double dataValue){
    // A boolean value to check if user input data does not exist
    bool dataDNE = true;
    // If user input a valid data
    if (dataValue >= 0){
        // Check if the user input year exists and update the corresponding data
        for (int i{0}; i < length; i++){
            if (yearValue == year[i]){
                data[i] = dataValue;
                std::cout << "success" << std::endl;
                dataDNE = false;
                break;
            }
        }
    }
    // If user input an invalid data
    else{
        int index{-1}; 
        // Check if the user input year exists in the year array
        for (int i{0}; i < length; i++){
            // If exists, find the index to delete data
            if (yearValue == year[i]){
                index = i;
                dataDNE = false;
                break;
            }
        }
        // If user input year exists in the year array
        if (!dataDNE){
            std::cout << "success" << std::endl;
            // Ignoring the invalid data and year in both array by shifting all elements 1 to the left
            for (int i{index}; i < length-1; i++){
                year[i] = year[i+1];
                data[i] = data[i+1];
            }
            // Assigning the last element in both arrays to 0 symbolize there is no element there
            year[length-1] = 0;
            data[length-1] = 0;
            length--;
        }
        
        // If the valid data number = capacity / 4.0, make the array size half
        if ((capacity >= 2) && (length*4 == capacity)){
            halve_array_size();
        }
    }
    // If user input a year that cannot be found in the year array, print failure
    if (dataDNE){
        std::cout << "failure" << std::endl;
    }
}

// The function MEAN_P1 that may implement the function of calculating the mean of all valid data by receiving the data and use the function mean() inside it
void TimeSeries::MEAN_P1(){
    // If there is no valid data, print failure
    if (length == 0){
        std::cout << "failure" << std::endl;
    }
    // If there is valid data, call the mean() function to generate a mean for data and print the value
    else{
        double M = mean();
        std::cout << "mean is " << M << std::endl;
    }  
}

// The function MONOTONIC_P1 that may implement the function of calculating the mean of all valid data by receiving the data and use the function mean() inside it
void TimeSeries::MONOTONIC_P1(){
    // If there is no valid data, print failure
    if (length == 0){
        std::cout << "failure" << std::endl;
    }
    else{
        // If there is valid data, call the is_monotonic() function and print is monotonic if series is monotonic (function returns true)
        if (is_monotonic()){
            std::cout << "series is monotonic" << std::endl;
        }
        // If there is valid data, print is not monotonic if series is not monotonic (function returns false)
        else{
            std::cout << "series is not monotonic" << std::endl;
        }
    }
}

// The function FIT_P1 that may implement the function of calculating a best_fit line for all valid data by receiving the data and use the function best_fit() inside it
void TimeSeries::FIT_P1(){
    // Create two variables for the slope and y-intercept
    double m{0};
    double b{0};
    // Call the function best_fit and if the function returns false, print failure
    if (!best_fit(m,b)){
        std::cout << "failure" << std::endl;
    }
    // If the function returns true, print the slope and intercept value
    else{
        std::cout << "slope is " << m << " intercept is " << b << std::endl;
    }
}

// The function double_array_size is for doubling the size of the array when the length of valid data reaches the limit
void TimeSeries::double_array_size(){
    // Double the capacity
    capacity *= 2;

    // Create a new dynamic array with the new capacity for copying the year array data
    int *NewYear{};
    NewYear = new int[capacity]{};

    // Create a new dynamic array with the new capacity for copying the data array data
    double *NewData{};
    NewData =  new double[capacity]{};

    // For two new arrays, point each element to the address of the old arrays
    for (int i{0}; i < length; i++){
        NewYear[i] = year[i];
        NewData[i] = data[i];
    }

    // Delete old arrays and point them to the new array
    delete[] year;
    delete[] data;

    year = NewYear;
    data = NewData;
}

// The function halve_array_size is for halving the size of the array when the length of valid data equasls to ¼ of the capacity
void TimeSeries::halve_array_size(){
    // Make the capacity half
    capacity /= 2;

    // Create a new dynamic array with the new capacity for copying the year array data
    // Create a new dynamic array with the new capacity for copying the data array data
    double *NewData;
    int *NewYear;
    NewData = new double[capacity]{};
    NewYear = new int[capacity]{};

    // For two new arrays, point each element to the address of the old arrays
    for (int i{0}; i < length; i++){
        NewData[i] = data[i];
        NewYear[i] = year[i];
    }

    // Delete old arrays and point them to the new array
    delete[] year;
    delete[] data;

    data = NewData;
    year = NewYear;
}