//
//  test_KDTree.cpp
//  
//
//  Created by Sivaram Ambikasaran on 12/3/13.
//
//

#include <iostream>
#include <cstdlib>
#include "./KDTree.hpp"

int main(int argc, char** argv) {
        assert(argc==3);
        unsigned n_Locations    =       atoi(argv[1]);  //      Number of points.
        unsigned n_Dimension    =       atoi(argv[2]);  //      Dimension.
        double* locations;                              //      Stores all the locations.
        locations               =       new double [n_Locations*n_Dimension];
        //      Generates random locations.
        unsigned count          =       0;
        for (unsigned j=0; j<n_Locations; ++j) {
                for (unsigned k=0; k<n_Dimension; ++k) {
                        locations[count] =       double(rand())/double(RAND_MAX);
                        ++count;
                }
        }
        std::cout << std::scientific;
        //      Displays the random locations to begin with.
        for (unsigned j=0; j < n_Locations; ++j) {
                for (unsigned k=0; k < n_Dimension; ++k) {
                        std::cout << locations[j*n_Dimension+k] << "\t";
                }
                std::cout << std::endl;
        }

        //      Creates a KDTree given the locations.
        KDTree* A               =       new KDTree(n_Locations, n_Dimension, locations);
        delete locations;

        double* sorted_Locations=       new double[n_Locations*n_Dimension];
        
        //      Sorts the locations based on KDTree.
        A->sort_KDTree();

        //      Obtains the sorted location.
        A->get_Location(sorted_Locations);

        //      Displays the sorted locations.
        std::cout << "Sorted locations are: " << std::endl;
        for (unsigned j=0; j < n_Locations; ++j) {
                for (unsigned k=0; k < n_Dimension; ++k) {
                        std::cout << sorted_Locations[j*n_Dimension+k] << "\t";
                }
                std::cout << std::endl;
        }

        delete sorted_Locations;
        delete A;
}