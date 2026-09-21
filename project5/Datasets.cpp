#include "Datasets.h"

// The constructor for node class given the next node and timeseries object
Datasets::Node::Node(Node *n, TimeSeries *a)
{
    baka = a;
    next = n;
}

// The destructor to prevent memory leak.
Datasets::~Datasets()
{
    Node *current = head;
    // While current node is not null pointer, keep looping in order to delete all nodes
    while(current != nullptr){
        Node *temp = current;
        current = current->next;

        // Delete Timeseries object in a node
        delete temp->baka;
        temp->baka = nullptr;

        // Delete the node
        delete temp;
        temp = nullptr;
    }
}

void Datasets::ADD_TimeSeries(TimeSeries *timeseries){
    if (head == nullptr) {
        head = new Node(nullptr, timeseries);
        current = head;
    } else {
        Node *newNode = new Node(nullptr, timeseries);
        current->next = newNode;
        current = current->next;
    }
}

// The function to load all data for one country of the .csv file.
void Datasets::LOAD_P2(std::string country_name)
{
    // Create variables in order to store the value read in
    std::string line;
    std::ifstream file("lab2_multidata.csv");

    Node *current = head;

    // Get each line in .csv
    while (std::getline(file, line))
    {
        // A pointer to Timeseries object, Value to store each data separated by ','.
        TimeSeries *baka = nullptr;
        std::string Value;

        // A variable to parse a line of input
        std::stringstream ss(line);

        // A counter to count the number of valid data in the input
        int counter{0};
        int length{0};
        int YearCounter{1960};

        // Get every value
        while (std::getline(ss, Value, ','))
        {
            std::stringstream sss(Value);

            if (counter == 0)
            {
                // Judge if the first value read in equal to the user input country name and store the data for each Timeseries object if it is the user input country name
                if (Value == country_name)
                {
                    baka = new TimeSeries();
                    CountryName = Value;
                }
                else
                {
                    break;
                }
            }

            // If the Timeseries object is not null pointer, meaning the country name matched, start to store the country code, series name, series code, and data
            if (baka != nullptr)
            {
                if (counter == 1)
                {
                    CountryCode = Value;
                }

                // If the counter == 2, means it is inputting the 3rd column, which corresponding to the seriesname
                if (counter == 2)
                {
                    baka->setSeriesName(Value);
                }

                // If the counter == 3, means it is inputting the 4th column, which corresponding to the seriescode
                if (counter == 3)
                {
                    baka->setSeriesCode(Value);
                }

                if (counter > 3)
                {
                    // A variable to store one temporary data
                    double TempData;

                    // Read the temporary data into the variable
                    sss >> TempData;

                    // If the data is a valid data
                    if (TempData >= 0)
                    {

                        // Judge if need to double the size of the array
                        if (baka->getLength() == baka->getCapacity())
                        {
                            baka->double_array_size();
                        }

                        // Store the year into year array
                        baka->setYear(baka->getLength(), YearCounter);

                        // Store the data into data array
                        baka->setData(baka->getLength(), TempData);

                        // Increment the length for both arrays
                        length++;
                        baka->setLength(length);
                        
                        if (baka->getLength() == baka->getCapacity()){
                            baka->double_array_size();
                        }
                    }
                    // Increment the year number after parsing the current data
                    YearCounter++;
                }
                // Increment the counter for each column when storing value in order to get the correct country code, series name, series code, and year information
                counter++;
            }
        }
        // If the Timeseries object is not a null pointer, goes to the next object.
        if (baka != nullptr)
        {
            if (head == nullptr)
            {
                head = new Node(nullptr, baka);
                current = head;
            }
            else
            {
                Node *xinshuju = new Node(nullptr, baka);
                current->next = xinshuju;
                current = current->next;
            }
        }
    }
}
// List the country name, country code, and all series names.
void Datasets::LIST_P2()
{
    // Print the country name and country code
    std::cout << CountryName << " ";
    std::cout << CountryCode;

    // Go to the next node in order to print next series code.
    Node *current = head;
    while (current != nullptr)
    {
        std::cout << " " << current->baka->getSeriesName();
        current = current->next;
    }
    std::cout << std::endl;
}

// Add a data given a series code, year, and data.
void Datasets::ADD_P2(std::string Series_Code, int year, double data)
{
    Node *current = head;

    // Go to the next node before reaches the correct series code in order to find the corresponding series code given by user input
    while (current != nullptr){
        if (Series_Code == current->baka->getSeriesCode()){
            // Add year and data into year and data arrays respectively.
            current->baka->ADD_P1(year,data);
            return;
        }
        current = current->next;
    }
    std::cout << "failure" << std::endl;
}

// Update a data given a series code, year, and data.
void Datasets::UPDATE_P2(std::string Series_Code, int year, double data){
    Node *current = head;

    // Go to the next node before reaches the correct series code in order to find the corresponding series code given by user input
    while (current != nullptr){
        if (Series_Code == current->baka->getSeriesCode()){
            // Update year and data into year and data arrays respectively.
            current->baka->UPDATE_P1(year,data);
            return;
        }
        current = current->next;
    }
    std::cout << "failure" << std::endl;
}

void Datasets::PRINT_P2(std::string Series_Code){
        Node *current = head;

    // Go to the next node before reaches the correct series code in order to find the corresponding series code given by user input
    while (current != nullptr){
        // Print all valid data with corresponding years for a given series code
        if (Series_Code == current->baka->getSeriesCode()){
            current->baka->PRINT_P1();
            return;
        }
        current = current->next;
    }
    std::cout << "failure" << std::endl;
}

// Delete all nodes to prevent memory leak
void Datasets::DELETE_P2(std::string Series_Code){
        Node *current = head;
        Node *previous = nullptr;
    
    // Go to the next node when current node is not a null pointer in order to delete all nodes and prevent memory leak    
    while (current != nullptr){
        if (Series_Code == current->baka->getSeriesCode()){
            std::cout << "success" << std::endl;
            
            // Delete the Timeseries object inside each node and then delete the node in order to prevent memory leak
            if (current == head){
                Node *temp = head;
                head = current->next;
                current = current->next;
                delete temp->baka;
                delete temp;
                temp = nullptr;
                return;
            }
            else{
                Node *temp = current;
                current = current->next;
                previous->next = current;
                delete temp->baka;
                delete temp;
                temp = nullptr;
                return;
            }
        }
        previous = current;
        current = current->next;
    }
    // If there is no node, print "failure".
    std::cout << "failure" << std::endl;
}

// Find the series with biggest mean
void Datasets::BIGGEST_P2(){

    // Declare variables to get to each node and store a greatest mean value in order to compare with other means
    Node *current = head;
    Node *BigBaka = nullptr;
    double BakaMe{-1};
    
    // Go to the next node and get the mean, compare it with current mean stored and replace the current mean when needed
    while(current != nullptr){
        if (current->baka->getLength() > 0){
            if (BakaMe < current->baka->mean()){
                BakaMe = current->baka->mean();
                BigBaka = current;
            }
        }
        current = current->next;
    }

    // If there is no mean for each series, output "failure"
    if(BigBaka == nullptr){
        std::cout << "failure" << std::endl;
    }
    else{
        // Output the the series code of the series with biggest mean
        std::cout << BigBaka->baka->getSeriesCode() << std::endl;
    }
}

// Output a string with the size and capacity of year and data arrays with a given series code
void Datasets::TS_P2(std::string Series_Code){
    Node *current = head;
    
    // Get the correct node with given series code and output the size and capacity for this series
    while(current != nullptr){
        if(Series_Code == current->baka->getSeriesCode()){
            std::cout << "size is " << current->baka->getLength() << " capacity is " << current->baka->getCapacity() << std::endl;
            return;
        }
        current = current->next;
    }
    std::cout << "failure" << std::endl;
}

// Return the corresponding country name
std::string Datasets::getCountryName() const{
    return CountryName;
}

// Return the corresponding country code
std::string Datasets::getCountryCode() const{
    return CountryCode;
}

// Return the corresponding series code with smallest mean
std::string Datasets::getSeriesCodeForSmallestMean() const{
    Node *current = head;

    double SmallestMean{-1};
    std::string Series_Code;

    // Loop through the linked list and compare the mean for each timeseries
    while(current != nullptr){
        double meanC = current->baka->mean();
        if (SmallestMean == -1){
            SmallestMean = meanC;
            Series_Code = current->baka->getSeriesCode();
        }
        else{
            if (SmallestMean > meanC){
                SmallestMean = meanC;
                Series_Code = current->baka->getSeriesCode();
            }
        }

        current = current->next;
    }
    return Series_Code;
}

double Datasets::getMean(std::string Series_Code) const{
    Node *current = head;
    double data;

    while(current != nullptr){
        if (current->baka->getSeriesCode() == Series_Code){
            data = current->baka->mean();
            break;
        }
        current = current->next;
    }
return data;
}

void Datasets::setCountryName(std::string CountryName){
    this->CountryName = CountryName;
}

void Datasets::setCountryCode(std::string CountryCode){
    this->CountryCode = CountryCode;
}