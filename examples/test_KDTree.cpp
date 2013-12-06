//
//  test_KDTree.cpp
//  
//
//  Created by Sivaram Ambikasaran on 12/3/13.
//
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "./KDTree.hpp"

void display(std::string display_String, unsigned n_Locations, unsigned n_Dimension, double* locations, unsigned n_Properties, double* properties) {
        std::cout << display_String << std::endl;
        
        unsigned count_Location  =       0;
        unsigned count_Property  =       0;
        
        for (unsigned j=0; j<n_Locations; ++j) {
                for (unsigned k=0; k<n_Dimension; ++k) {
                        std::cout << locations[count_Location] << "\t";
                        ++count_Location;
                }
                for (unsigned k=0; k<n_Properties; ++k) {
                        std::cout << properties[count_Property] << "\t";
                        ++count_Property;
                }
                std::cout << std::endl;
        }
        std::cout << std::endl;
}

int main(int argc, char** argv) {
        assert(argc==4);
        unsigned n_Locations    =       atoi(argv[1]);  //      Number of points.
        unsigned n_Dimension    =       atoi(argv[2]);  //      Dimension.
        unsigned n_Properties   =       atoi(argv[3]);  //      Number of properties.

        double* locations       =       new double [n_Locations*n_Dimension];   //      Stores all the locations.
        double* properties      =       new double [n_Locations*n_Properties];  //      Stores all the properties.
        
        //      Generates random locations and random values of property.
        unsigned count_Location =       0;
        unsigned count_Property =       0;
        for (unsigned j=0; j<n_Locations; ++j) {
                for (unsigned k=0; k<n_Dimension; ++k) {
                        locations[count_Location]       =       double(rand())/double(RAND_MAX);
                        ++count_Location;
                }
                for (unsigned k=0; k<n_Properties; ++k) {
                        properties[count_Property]      =       double(rand())/double(RAND_MAX);
                        ++count_Property;
                }
        }

        std::cout << std::scientific;

        //      Display the initial contents.
//        display("Initial contents: ", n_Locations, n_Dimension, locations, n_Properties, properties);

        //      Creates a KDTree given the locations.
        KDTree* A                       =       new KDTree(n_Locations, n_Dimension, locations, n_Properties, properties);
        delete locations;
        delete properties;

        double* sorted_Locations        =       new double[n_Locations*n_Dimension];
        double* sorted_Properties       =       new double[n_Locations*n_Properties];
        
        clock_t start, end;
        //      Sorts the locations based on KDTree.
        start   =       clock();
        A->sort_KDTree();
        end     =       clock();
        std::cout << "Time taken is: " << double(end-start)/double(CLOCKS_PER_SEC) << std::endl;

        //      Obtains the sorted location.
        A->get_Location_Properties(sorted_Locations, sorted_Properties);

        //      Display the sorted contents.
//        display("Sorted contents: ", n_Locations, n_Dimension, sorted_Locations, n_Properties, sorted_Properties);

        delete sorted_Locations;
        delete sorted_Properties;
        delete A;
}