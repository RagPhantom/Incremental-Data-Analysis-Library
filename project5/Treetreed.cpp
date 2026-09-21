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

    for (int i = 0; i < 512; i++) {
        HashTableStatus[i] = "Empty";
    }

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
            insert(obj);
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
    double min{-1};
    double max{-1};

    // Get the node with mininum mean and the node with maximum mean in order to compare if they are identical by a factor of 1e-3
    for (int i = 0; i < 512 && node -> baka[i] != nullptr; i++)
    {
        if (node->baka[i]->getMean(Series_Code) == -1){
            continue;
        }
        if (min == -1){
            min = node->baka[i]->getMean(Series_Code);
        }
        if (max == -1){
            max = node->baka[i]->getMean(Series_Code);
        }
        if (node->baka[i]->getMean(Series_Code) > max){
            max = node->baka[i]->getMean(Series_Code);
        }
        if (node->baka[i]->getMean(Series_Code) < min){
            min = node->baka[i]->getMean(Series_Code);
        }
    }

    // All countries do not have valid data
    if (min == -1){
        return true;
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
        // loop through all countries and add country with means less than the give mean
        while (node->baka[a] != nullptr){
            if (node->baka[a]->getMean(SeriesCode) < mean){
                QualifiedCountries.push_back(node->baka[a]);
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
        // loop through all countries and add with means greater than the given mean
        while (node->baka[a] != nullptr){
            if (node->baka[a]->getMean(SeriesCode) > mean){
                QualifiedCountries.push_back(node->baka[a]);
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
        // loop through all countries and add with means equal to the given mean to the QualifiedCountries arraylist
        while (node->baka[a] != nullptr){
            if (fabs(node->baka[a]->getMean(SeriesCode) - mean) <= 1e-3){
                QualifiedCountries.push_back(node->baka[a]);
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

// --- Project 4 ---

// Implementation for primary hash function
int Treetreed::hashProject(std::string Country_Code){
    int D0 = Country_Code[0] - 65;
    int D1 = Country_Code[1] - 65;
    int D2 = Country_Code[2] - 65;

    W = D0 * 26 * 26 + D1 * 26 + D2;
    return W % 512;
}

// Implementation for secondary hash function
int Treetreed::hashSekai(){
    int Sekai = W/512;

    if (Sekai % 2 == 1){
        return (Sekai % 512);
    }
    else{
        return (Sekai % 512) + 1;
    }
}

// Returns the index of the country located in the HashTable
int Treetreed::lookup(std::string Country_Code){
    int i{0};
    int projectHash = hashProject(Country_Code);
    int sekaiHash = hashSekai();

    while (i < 512){
        int index = (projectHash + i * sekaiHash) % 512;

        // If the status for one of the index is Empty, meaning there has been no insertion in this index (country code doex not exist in hash table), return -1
        if (HashTableStatus[index] == "Empty"){
            return -1;
        }

        // If the country code at the index produced by the hash function is the same as input country code, print index X searches Y
        if (HashTableStatus[index] == "Occupied" && HashTable[index]->getCountryCode() == Country_Code){
            return index;
        }
        i++;
    }
    return -1;
}

void Treetreed::LOOKUP_P4(std::string Country_Code){
    // Count the number of times of computing hash functions
    int i{0};
    int projectHash = hashProject(Country_Code);
    int sekaiHash = hashSekai();

    while (i < 512){
        int index = (projectHash + i * sekaiHash) % 512;

        // If the status for one of the index is Empty, meaning there has been no insertion in this index (country code doex not exist in hash table), print failure
        if (HashTableStatus[index] == "Empty"){
            std::cout << "failure" << std::endl;
            return;
        }
        // If the country code at the index produced by the hash function is the same as input country code, print index X searches Y
        if (HashTableStatus[index] == "Occupied" && HashTable[index]->getCountryCode() == Country_Code){
            std::cout << "index " << index << " searches " << i+1 << std::endl;
            return;
        }
        i++;
    }
    std::cout << "failure" << std::endl;
}

void Treetreed::REMOVE_P4(std::string Country_Code){
    int index = lookup(Country_Code);
    // If this country does not exist in the hash table
    if (index == -1){
        std::cout << "failure" << std::endl;
    }
    else{
        // If there is a tree built, also remove this country from the tree
        if (root != nullptr){
            std::string Country_Name = HashTable[index]->getCountryName();
            DELETE_P3(Country_Name);

            HashTable[index] = nullptr;
            HashTableStatus[index] = "PreviouslyOccupied";
        }
        // If no tree built, only remove the country and map its status to PreOccupied
        else{
            HashTable[index] = nullptr;
            HashTableStatus[index] = "PreviouslyOccupied";
            
            std::cout << "success" << std::endl;
        }
    }
}

// Helper function to insert this country into the hash table
void Treetreed::insert(Datasets *element){
    if(lookup(element->getCountryCode()) != -1){
        return;
    }
    // H1, primary hash function
    int hash1 = hashProject(element->getCountryCode());
    // H2, secondary hash function
    int hash2 = hashSekai();
    // To record the index (where should it be put at) in the hash table
    int index{-1};

    for (int j{0}; j<512; j++){
            // Compute the index
            index = (hash1 + j * hash2) % 512;
            if (HashTableStatus[index] == "Empty" || HashTableStatus[index] == "PreviouslyOccupied"){
                // If the status for this index is "Empty" or "PreviouslyOccupied", insert and break, else loop again
                HashTable[index] = element;
                HashTableStatus[index] = "Occupied";
                break;
            }
        }
}

void Treetreed::INSERT_P4(std::string Country_Code){
    // Judge if inserted into the hash table
    bool isInserted{false};
    // If this country does not exist in the hash table
    if (lookup(Country_Code) == -1){
        // To record the index (where should it be put at) in the hash table
        int index{-1};

        // H1, primary hash function
        int hash1 = hashProject(Country_Code);
        // H2, secondary hash function
        int hash2 = hashSekai();

        int i{0};

        // Loop through all data to get the index of the datasets object
        for (i; i<512; i++){
            if (AllDatasets[i]->getCountryCode() == Country_Code){
                break;
            }
        }

        // Protection to avoid the scenario of index out of bound     
        if (i == 512){
                    std::cout << "failure" << std::endl;
                    return;
                }

        for (int j{0}; j<512; j++){
            // Compute the index
            index = (hash1 + j * hash2) % 512;
            if (HashTableStatus[index] == "Empty" || HashTableStatus[index] == "PreviouslyOccupied"){
                // If the status for this index is "Empty" or "PreviouslyOccupied", insert and break, else loop again
                HashTable[index] = AllDatasets[i];
                HashTableStatus[index] = "Occupied";
                isInserted = true;
                break;
            }
        }
    }

    // If the timeseries object is inserted into the hash table, print success, else print failure
    if (isInserted){
        std::cout << "success" << std::endl;
        return;
    }
    std::cout << "failure" << std::endl;
}

void Treetreed::MergeSort(Datasets *array[], int start, int end){
    int midpoint = (start + end)/2;
    if (start == end){
        return;
    }
    MergeSort(array, start, midpoint);
    MergeSort(array, midpoint+1, end);
    merge(array, start, midpoint+1, end);
}

void Treetreed::merge(Datasets *array[], int start_left, int start_right, int end_right){
    // The size for MergedArray
    int size = end_right - start_left + 1;

    // Equals to end_left - start_left + 1;
    int left_size = start_right - start_left;

    int right_size = end_right - start_right + 1;
    Datasets *MergedArray[size]{};

    // The index for arrayleft
    int a{0};

    // The index for arrayright
    int b{0};

    // Combining two arrays
    for (int i{0}; i < size; i++){
        // If all elements in arrayleft is already merged into MergedArray, simply take all remaining elements in arrayright
        // When a is greater than last index in the "left array"
        if (a >= left_size){
            MergedArray[i] = array[start_right + b];
            b++;
        }
        // If all elements in arrayright is already merged into MergedArray, simply take all remaining elements in arrayleft
        // When b is greater than last index in the "right array"
        else if (b >= right_size){
            MergedArray[i] = array[start_left + a];
            a++;
        }
        // If the left element is smaller than the right element, take the element in array left
        else if (array[start_left + a]->getCountryCode() < array[start_right + b]->getCountryCode()){
            MergedArray[i] = array[start_left + a];
            a++;
        }
        // If the right element is smaller than the left element, take the element in array right
        else{
            MergedArray[i] = array[start_right + b];
            b++;
        }
    }

    for (int i{0}; i < size; i++){
        array[start_left + i] = MergedArray[i];
    }
}

void Treetreed::CLEAN_P4(){
    // Temporary Datasets array to store timeseries Excalibur!
    Datasets *Excalibur[512]{nullptr};

    // Counter for index in Temporary Datasets array Excalibur
    int baka{0};

    // If the element is not nullptr, add it to Excalibur
    for (int i{0}; i<512; i++){
        if (HashTable[i] != nullptr){
            Excalibur[baka] = HashTable[i];
            baka++;
        }
        HashTable[i] = nullptr;
        HashTableStatus[i] = "Empty";
    }

    // Since baka is 1 greater than the last index(size), we input the end index as baka-1
    MergeSort(Excalibur, 0, baka-1);
    
    for (int i{0}; i<512; i++){
        // If index is smaller than the size of Excalibur, copy the element in Excalibur[i] to HashTable[i]
        if (i < baka){
            insert(Excalibur[i]);
        }
        // If index is greater than the size of Excalibur, meaning we already reached the end of array, set HashTable[i] to null pointer
    }
    // This function always success
    std::cout << "success" << std::endl;
}

// --- Project 5 ---

// Initialize the graph's nodes with no edges.
void Treetreed::INITIALIZE_P5(){
    // Removes all the existing edges, no need to initialize since there is already an array storing all countries (AllDatasets[512])
    AdjacencyList.clear();

    for (int i{0}; i < counter; i++){
        AdjacencyList[AllDatasets[i]];
    }

    // [Output a success
    std::cout << "success" << std::endl;
}

// Update edges based on the relations: "greater", "less", or "equal".
void Treetreed::UPDATE_EDGES_P5(std::string Series_Code, double threshold, std::string relation){
    // Check each element in AllDatasets, if satisfy the condition, put it into the "AllQualifiedData array"
    BUILD_P3(Series_Code);

    // Clear all the things inside QualifiedCountries
    QualifiedCountries.clear();

    // Find all countries with means have this relation with threshold
    FIND_P3(threshold, relation);


    // Tuple for later add into the relationship set in the adjacency list
    auto tuple = std::make_tuple(Series_Code, threshold, relation);


    bool newRelationAdded{false};

    // Loop through all qualified countries in order to add edges
    for(auto i = QualifiedCountries.begin(); i < QualifiedCountries.end(); i++){
            for (auto j = i+1; j < QualifiedCountries.end(); j++){
            // If the key (destination country) exist in the map, add all of the edges related
                if (AdjacencyList.at(*i).find(*j) != AdjacencyList.at(*i).end()){
                    // Insert, and see if it successfully inserted it
                    auto InsertionSuccess = AdjacencyList.at(*i).at(*j).insert(tuple).second;
                    AdjacencyList.at(*j).at(*i).insert(tuple);

                    // Or the "if successfully inserted" with previous possible relation added
                    newRelationAdded = InsertionSuccess || newRelationAdded;
            }
            // If the key (destination country) not exist in the map, add it and all of the edges related
                else{
                    // In case if I want to make a set
                    // std::set<int> s = {1,2,3};
                    AdjacencyList.at(*i).insert({*j, {tuple}});
                    AdjacencyList.at(*j).insert({*i, {tuple}});
                    newRelationAdded = true;
            }
        }
    }

    // Output a failure if no new relationships have been added
    if (newRelationAdded){
        std::cout << "success" << std::endl;
    }
    else{
        std::cout << "failure" << std::endl;
    }
}

// Output all countrie names that are adjacent to the given country
void Treetreed::ADJACENT_P5(std::string Country_Code){
    // Get the index of the country code in the hash table
    int index = lookup(Country_Code);

    // print failure and return when the country is not in the graph (also not in the hashtable)
    if (index == -1){
        std::cout << "failure" << std::endl;
        return;
    }

    // Get the target country
    Datasets *country = HashTable[index];

    // Get the inner map that stores all destination countries and set of edges for each destination country
    auto inner_map = AdjacencyList.at(country);

    // If there is no destination country, print none and return
    if (inner_map.empty()){
        std::cout << "none" << std::endl;
        return;
    }

    // Print out all the destination country names in inner map if there is
    for(auto &i : inner_map){
        std::cout << i.first->getCountryName() << " ";
    }
    std::cout << std::endl;
}


// Depth First helper function to determine if the two countries are connected by a path in the graph
bool Treetreed::DFS(std::string Country_Code1, std::string Country_Code2){
    // Get the index of the country code in the hash table
    int index1 = lookup(Country_Code1);
    int index2 = lookup(Country_Code2);
   
    // Get both countries
    Datasets* Country1 = HashTable[index1];
    Datasets* Country2 = HashTable[index2];

    // Create a vector to store path
    std::vector<Datasets *> path = {Country1};
    
    // Create a stack to store the entire path found each time
    std::stack<std::vector<Datasets*>> todo;

    // Create a visited set to store all visited nodes
    std::set<Datasets *> visited;

    // Push path into todo stack
    todo.push(path);

    while (!todo.empty()){
        // Returns the first line and added to the current path
        path = todo.top();
        
        // Delete the first line from todo stack
        todo.pop();

        // If current node == destination node, return true (found a path)
        if (path.back() == Country2){
            return true;
        }


        // Check if our current node is in visited
        bool isinVisited = false;
        for (auto &i: visited){
            if (path.back() == i){
                isinVisited = true;
            }
        }
        if (isinVisited == false){
            visited.insert(path.back());
        // Get the inner map from the newest element in the path (current node)
            
            auto inner_map = AdjacencyList.at(path.back());
            for (auto &j : inner_map){
                // Get the node adjacent to current node
                auto destination_country = j.first;

                // Make a copy to the path to prevent push back node to previous path
                auto new_path = path;
                
                // Push the adjacent node to path
                new_path.push_back(destination_country);

                // Push the path to todo
                todo.push(new_path);
            }
        }
        
    }
    return false;
}

// Determines if the two countries are connected by a path in the graph
void Treetreed::PATH_P5(std::string Country_Code1, std::string Country_Code2){
    bool PathExist = DFS(Country_Code1,Country_Code2);
    if (PathExist){
        std::cout << "true" << std::endl;
    }
    else{
        std::cout << "false" << std::endl;
    }
}

// If the two countries are connected by an edge, list their relationships
void Treetreed::RELATIONSHIPS_P5(std::string Country_Code1, std::string Country_Code2){
    int index1 = lookup(Country_Code1);
    int index2{lookup(Country_Code2)};

    Datasets *Country1 = HashTable[index1];
    Datasets *Country2 = HashTable[index2];

    // Get the value for inner_map (Storing a vector of destination country and the set of tuples)
    auto inner_map = AdjacencyList.at(Country1);
    // If inner_map has the key of Country2, meaning they share an edge
    if (inner_map.count(Country2) != 0){
        // Get the set of tuples storing elements of {Series_Code, Threshold, Relation} pairs
        auto set_of_relashinship_tuple = inner_map.at(Country2);

        // Loop through the inner set to print each tuple
        for (auto &i : set_of_relashinship_tuple){
            auto Series_Code = std::get<0>(i);
            auto Threshold = std::get<1>(i);
            auto Relation = std::get<2>(i);
            std::cout << '(' << Series_Code << ' ' << Threshold << ' ' << Relation << ')' << ' ';
        }
        std::cout << std::endl;
    }
    else{
        std::cout << "none" << std::endl;
    }
}