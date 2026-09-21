#include "Datasets.h"

// Class for analyzing all countries
class Treetreed{
    private:
        // The array to store data for all countries
        Datasets* AllDatasets[512] = {nullptr};

        // A counter for counting the number of countries in the array
        int counter{0};

        // Store the series code when building the tree for other function accessing it
        std::string SeriesCode;
        
        // Class for creating a tree structure to analyze data for all countries
        class Node{
            public:
                // The array to store pointers to all countries in a node
                Datasets *baka[512];
                Node *left;
                Node *right;

                // For determining the next node goes left or right when building the tree based on the mean of this node
                double Min;
                double Max;

                // Constructor for node
                Node():left(nullptr), right(nullptr){}
                Node(Node *lef, Node *righ, Datasets *b[512], double Mi, double Ma):left(lef), right(righ), Min(Mi), Max(Ma){
                    if (b != nullptr){
                        for (int i{0}; i<512; i++){
                            baka[i] = b[i];
                        }
                    }
                    else{
                        for (int i{0}; i<512; i++)
                        {
                            baka[i] = nullptr;
                        }
                        
                    }
                }
        };

        // Root of the tree
        Node *root{nullptr};

    public:
        // Destructor to prevent memory leak
        ~Treetreed();
        // Helper function for the destructor to delete all nodes in the tree
        void Discord(Node *hajimi);

        // Loads all data
        void LOAD_P3();

        // Lists country name and all country codes based on the given country name
        void LIST_P3(std::string Country_name); 

        // Outputs the series code of the country with the smallest mean for a given series code
        void COUNTRY_MIN_P3(std::string Country_Code);

        // Outputs the min mean for a given series code
        double GI(std::string Series_Code);
        // Outputs the max mean for a given series code
        double GA(std::string Series_Code);

        // Helper function to get all countries with means strictly less than a value
        Datasets** StrictlyLess(Node *baka, double value, std::string Series_Code, Datasets **res);
        // Helper function to get all countries with means greater or equal to a value
        Datasets** Greater(Node *baka, double value, std::string Series_Code, Datasets **res);

        // Determine if there is only one node in the tree
        bool OnlyOneNode(Node *node) const;
        // Determine if means are identical by a factor of 1e-3
        bool MeansIdentical(Node *node, std::string Series_Code) const;

        // Helper function to recursively build the tree
        void buildBaka(Node *baka1, std::string Series_Code, double min, double max);

        // Outputs the min and max data for a given series code
        void RANGE_P3(std::string Series_Code);

        // Build the tree for a given series code
        void BUILD_P3(std::string Series_Code);

        // Helper function to find and output all country names with means less than the given mean
        void find_less(Node *node, double mean);
        // Helper function to find and output all country names with means greater to the given mean
        void find_greater(Node *node, double mean);
        // Helper function to find and output all country names with means equal to the given mean
        void find_equal(Node *node, double mean);
        // The function to find and output all country names corresponding to the operation
        void FIND_P3(double mean, std::string operation);

        // Helper function to find the index of the country in a node that we intended to delete
        int FindIndex(std::string Country_Name, Node *node);
        // Helper function to delete a country in a node, returns true if successfully deleted, false otherwise
        void Delete(int index, Node *node);
        // The function to delete a country from any nodes in which it is found
        void DELETE_P3(std::string Country_Name);

        // The function output country names given the condition "lowest"  or "highest" by outputting countries that appear in the leftmost leaf or rightmost leaf respectively
        void LIMITS_P3(std::string condition);

        // Helper function to output a interval [L,R] for a given node
        void OutputInterval(Node *node);

        // Search the given country in the tree and output the interval [L,R] of every node that contains this country
        void TRACE_P3(std::string Country_Name);    
};