#include "Treetreed.h"
#include <cmath>

// Destructor
Treetreed::~Treetreed(){
    // Delete all datasets in the array
    for (int i{0}; i<counter; i++){
        delete AllDatasets[i];
        AllDatasets[i] = nullptr;
    }
    // Delete all nodes in the tree with a helper function
    Discord(root);
}

// Helper function to delete all nodes inside the binary tree
void Treetreed::Discord(Node *hajimi){
    if (hajimi == nullptr){
        return;
    }
    else{
        Node *left = hajimi->left;
        Node *right = hajimi->right;
        
        // Delete subtrees recursively
        Discord(left);
        Discord(right);

        delete hajimi;
        hajimi = nullptr;
    }
}
// loads data in
void Treetreed::LOAD_P3(){
    // Creates variables in order to store the value read in
    std::string line;
    std::ifstream file("lab2_multidata.csv");
    
    // Sets up a previous country name in order to compare with the country name getline is reading right now to skip those line with same country names
    std::string previousCountry = "";
    Datasets *obj = nullptr;

    // Get a line from the excel file
    while(std::getline(file,line)){
        std::stringstream ss(line);
        std::string countryname;
        std::getline(ss, countryname, ',');

        std::string countrycode;
        std::getline(ss, countrycode, ',');

        // If the country name does not equal to the last country name, it means it is a new country and we need to add it to our Datasets array
        if (countryname != previousCountry){
            obj = new Datasets();
            obj->setCountryName(countryname);
            obj->setCountryCode(countrycode);

            AllDatasets[counter] = obj;
            counter++;
            previousCountry = countryname;
        }

        // Create a TimeSeries object for each line and add it to the node
        TimeSeries *obj2 = new TimeSeries();
        obj2->LOAD_P1(line);
        obj->ADD_TimeSeries(obj2);
    }
    std::cout << "success" << std::endl;
}

// Lists data with a given country name
void Treetreed::LIST_P3(std::string Country_name){
    // Found the right Datasets with the same country name as user input and list all data related to that country
    for(int i{0}; i<counter; i++){
        if (AllDatasets[i]->getCountryName() == Country_name){
            AllDatasets[i]->LIST_P2();
            return;
        }
    }
}

// Outputs the Series code of the time series for the given country with the smallest mean.
void Treetreed::COUNTRY_MIN_P3(std::string Country_Code){
    // Loop through all data sets and find the one with corresponding country code as user given
    for(int i{0}; i<counter; i++){
        if (AllDatasets[i]->getCountryCode().compare(Country_Code) == 0){
            // Get the series code for smallest mean and print it out
            std::cout << AllDatasets[i]->getSeriesCodeForSmallestMean() << std::endl;
            return;
        }
    }
    // If there is no such country code existed, print failure
    std::cout << "failure" << std::endl;
    
}

// Outputs the min mean for a given series code
double Treetreed::GI(std::string Series_Code){
    double minMean = -1;
    for(int i{0}; i<counter; i++){
        // Get the current mean to compare with minMean
        double currentValue = AllDatasets[i]->getMean(Series_Code);
        if (currentValue == -1){
            continue;
        }
        else{
            // If the current minMean is greater than the mean from current series with user input series code, update minMean to the current mean
            if (minMean == -1){
                minMean = currentValue;
            }
            else if (currentValue < minMean){
                minMean = currentValue;
            }
        }
    }
    return minMean;
}

// Outputs the max mean for a given series code
double Treetreed::GA(std::string Series_Code){
    double maxMean = -1;
    for(int i{0}; i<counter; i++){
        double currentValue = AllDatasets[i]->getMean(Series_Code);
        // Get the current max mean to compare with the maxMean
        if (currentValue == -1){
            continue;
        }
        else{
            // If the current maxMean is greater than the mean from current series with user input series code, update maxMean to the current mean
            if (maxMean == -1){
                maxMean = currentValue;
            }
            else if (currentValue >= maxMean){
                maxMean = currentValue;
            }
        }
    }
    return maxMean;
}

// Helper function to get all countries with means strictly less than a value
Datasets** Treetreed::StrictlyLess(Node *baka, double value, std::string Series_Code, Datasets **res){
    int count{0};
        // loop through all countries in the node and add all countries with means less than the midpoint of the node to the result array
        for (int i{0}; i<512 && baka->baka[i] != nullptr; i++){
            if (baka->baka[i]->getMean(Series_Code) < value && baka->baka[i]->getMean(Series_Code) != -1){
                res[count] = baka->baka[i];
                count++;
            }
        }
    return res;
}

// Helper function to get all countries with means greater or equal to a value
Datasets** Treetreed::Greater(Node *baka, double value, std::string Series_Code, Datasets **res){
    int count{0};
        // loop through all countries in the node and add all countries with means greater or equal to the midpoint of the node to the result array
        for (int i{0}; i<512 && baka->baka[i] != nullptr; i++){
            if (baka->baka[i]->getMean(Series_Code) >= value && baka->baka[i]->getMean(Series_Code) != -1){
                res[count] = baka->baka[i];
                count++;
            }
        }

    return res;
}

// Outputs the min and max data for a given series code
void Treetreed::RANGE_P3(std::string Series_Code){
    double minMean = GI(Series_Code);
    double maxMean = GA(Series_Code);
    std::cout << minMean << " " << maxMean << std::endl;
}

// Determine if there is only one node in the tree
bool Treetreed::OnlyOneNode(Node *node) const{
    if (node->baka[0] != nullptr && node->baka[1] == nullptr){
        return true;
    }
    return false;
}

// Determine if means are identical by a factor of 1e-3
bool Treetreed::MeansIdentical(Node *node, std::string Series_Code) const{
    if (node == nullptr || node->baka[0] == nullptr) {
        return true;
    }
    bool flag{true};
    double min{node->baka[0]->getMean(Series_Code)};
    double max{node->baka[0]->getMean(Series_Code)};

    // Get the node with mininum mean and the node with maximum mean in order to compare if they are identical by a factor of 1e-3
    for (int i = 1; i < 512 && node -> baka[i] != nullptr; i++)
    {
        if (node->baka[i]->getMean(Series_Code) > max){
            max = node->baka[i]->getMean(Series_Code);
        }
        if (node->baka[i]->getMean(Series_Code) < min){
            min = node->baka[i]->getMean(Series_Code);
        }
    }
    
    // If the difference between min mean and max mean is greater than 1e-3, then means not identical
    if (fabs(min - max) > 1e-3){
        flag = false;
    }
    return flag;
}

// Helper function to recursively build the tree
void Treetreed::buildBaka(Node *baka1, std::string Series_Code, double min, double max){

    double midpoint = (min + max) / 2.0;

    if (OnlyOneNode(baka1)){
        return;
    }
    if (MeansIdentical(baka1, Series_Code)){
        return;
    }
    else{
        Datasets **Resultleft = new Datasets*[512]();
        Datasets **Resultright = new Datasets*[512]();
        
        Datasets **left_data = StrictlyLess(baka1, midpoint, Series_Code, Resultleft);
        Datasets **right_data = Greater(baka1, midpoint, Series_Code, Resultright);

        // Recursively add left child and right child for the node if data in the left and right are not nullptr
        if(Resultleft[0] != nullptr){
            baka1->left = new Node(nullptr, nullptr, left_data, min, midpoint);
            buildBaka(baka1->left, Series_Code, min, midpoint);
        }
        if(Resultright[0] != nullptr){
            baka1->right = new Node(nullptr, nullptr, right_data, midpoint, max);
            buildBaka(baka1->right, Series_Code, midpoint, max);
        }  
        delete[] Resultleft;
        delete[] Resultright;
    }

}

// Build the tree for a given series code
void Treetreed::BUILD_P3(std::string Series_Code){
    SeriesCode = Series_Code;
    if(root != nullptr){
        Discord(root);
        root = nullptr;
    }
    
    double Mini = GI(Series_Code);
    double Maxi = GA(Series_Code);
    root = new Node(nullptr, nullptr, AllDatasets, Mini, Maxi);
    buildBaka(root, Series_Code, Mini, Maxi);
    
    std::cout << "success" << std::endl;
}

// Helper function to find and output all country names with means less than the given mean
void Treetreed::find_less(Node *node, double mean){
    if (node == nullptr){
        return;
    }
    if (node->Min >= mean){
        return;
    }
    if (node->left == nullptr && node->right == nullptr){
        int a{0};
        // loop through all countries and print country names with means less than the give mean
        while (node->baka[a] != nullptr){
            if (node->baka[a]->getMean(SeriesCode) < mean){
                std::cout << node->baka[a]->getCountryName() << " ";
            }
            a++;
        }
        return;
    }

    find_less(node->left, mean);
    find_less(node->right, mean);
}

// Helper function to find and output all country names with means greater to the given mean
void Treetreed::find_greater(Node *node, double mean){
    if (node == nullptr){
        return;
    }
    if (node->Max <= mean){
        return;
    }
    if (node->left == nullptr && node->right == nullptr){
        int a{0};
        // loop through all countries and print country names with means greater than the given mean
        while (node->baka[a] != nullptr){
            if (node->baka[a]->getMean(SeriesCode) > mean){
                std::cout << node->baka[a]->getCountryName() << " ";
            }
            a++;
        }
        return;
    }

    find_greater(node->left, mean);
    find_greater(node->right, mean);

}

// Helper function to find and output all country names with means equal to the given mean
void Treetreed::find_equal(Node *node, double mean){
    if (node == nullptr){
        return;
    }
    if (node->left == nullptr && node->right == nullptr){
        int a{0};
        // loop through all countries and print country names with means equal to the given mean
        while (node->baka[a] != nullptr){
            if (fabs(node->baka[a]->getMean(SeriesCode) - mean) <= 1e-3){
                std::cout << node->baka[a]->getCountryName() << " ";
            }
            a++;
        }
        return;
    }
    if ((node->Max + node->Min)/2.0 <= mean){
        find_equal(node->right, mean);
    }
    else{
        find_equal(node->left, mean);
    }
}

// The function to find and output all country names corresponding to the operation
void Treetreed::FIND_P3(double mean, std::string operation){
    if(root == nullptr){
        std::cout << "failure" << std::endl;
        return;
    }
    if(operation == "less"){
        find_less(root, mean);
    }
    if(operation == "equal"){
        find_equal(root, mean);
    }
    if(operation == "greater"){
        find_greater(root, mean);
    }
    std::cout << std::endl;
}

// Helper function to find the index of the country in a node that we intended to delete
int Treetreed::FindIndex(std::string Country_Name, Node *node){
    int i{0};
    // Find the index of the country in the array
    while(node->baka[i] != nullptr){
        if(node->baka[i]->getCountryName() == Country_Name){
            return i;
        }
        i++;
    }
    return -1;
}

// Helper function to delete a country in a node, returns true if successfully deleted, false otherwise
void Treetreed::Delete(int index, Node *node){
    if (index < 0){
        return;
    }
    int j = index;
    // Delete the country by the index and moving all countries after it one index forward
    while(j+1 < 512 && node->baka[j+1] != nullptr){
        node->baka[j] = node->baka[j+1];
        j++;
    }
    node->baka[j] = nullptr;
}

// The function to delete a country from any nodes in which it is found
void Treetreed::DELETE_P3(std::string Country_Name){
    if(root == nullptr){
        //std::cout << "hello";
        std::cout << "failure" << std::endl;
        return;
    }
    Node **current = &root;

    // Search the given country in the tree and delete it from all nodes containing it
    while ((*current) != nullptr){

        int index = FindIndex(Country_Name, *current);

        //std::cout << index << std::endl;
        if (index < 0){
            std::cout << "failure" << std::endl;
            return;
        }

        double mean = (*current)->baka[index]->getMean(SeriesCode);

        Delete(index, *current);

        // If the node is null (no country) and it is a leaf, than just delete it and all the subtrees
        if ((*current)->baka[0] == nullptr){
            Discord(*current);
            *current = nullptr;
            break;
        }
        if ((mean < (((*current)->Min + (*current)->Max)/2))){
            current = &((*current)->left);
        }
        else{
            current = &((*current)->right);
        }
    }
    std::cout << "success" << std::endl;
}

// The function output country names given the condition "lowest"  or "highest" by outputting countries that appear in the leftmost leaf or rightmost leaf respectively
void Treetreed::LIMITS_P3(std::string condition){
    if(root == nullptr){
        std::cout << "failure" << std::endl;
        return;
    }
    Node *current = root;

    if (condition == "lowest"){
        // Going to the leftmost leaf by keep going left until there is no left child
        while (current->left != nullptr){
            current = current->left;
            // If there is no left child but a right child, then go to the right child
            if (current->left == nullptr && current->right != nullptr){
                current = current->right;
            }
        }
    } 
    else if (condition == "highest"){
        // Going to the rightmost leaf by keep going right until there is no right child
        while (current->right != nullptr){
            current = current->right;
            // If there is no right child but a left child, then go to the left child
            if (current->right == nullptr && current->left != nullptr){
                current = current->left;
            }
        }
    }

    int i{0};
    // Going through all countries in the leaf and print out their names
    while (current->baka[i] != nullptr){
        std::cout << current->baka[i]->getCountryName() << " ";
        i++;
    }
    std::cout << std::endl;
}

// Helper function to output a interval [L,R] for a given node
void Treetreed::OutputInterval(Node *node){
    std::cout << node->Min << " " << node->Max << " ";
}

// Search the given country in the tree and output the interval [L,R] of every node that contains this country
void Treetreed::TRACE_P3(std::string Country_Name){
    if(root == nullptr){
        std::cout << "failure" << std::endl;
        return;
    }

    if (FindIndex(Country_Name, root) == -1){
        std::cout << "failure" << std::endl;
        return;
    }

    Node *current = root;
    // Search the given country in the tree and output the interval [L,R] of every node that contains this country
    while(current != nullptr){
        int i = FindIndex(Country_Name, current);
        OutputInterval(current);
        
        // If the node is a leaf, we only need to output the interval without getting further down to left and right subtrees
        if(current->left == nullptr && current->right == nullptr){
            break;
        }

        if(current->baka[i]->getMean(SeriesCode) < (current->Min + current->Max)/2){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }
    std::cout << std::endl;
}