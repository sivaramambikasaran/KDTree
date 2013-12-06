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
        unsigned n_Locations    =       atoi(argv[1]);
        unsigned n_Dimension    =       atoi(argv[2]);
        double* locations;
        locations               =       new double [n_Locations*n_Dimension];
        unsigned count          =       0;
        for (unsigned j=0; j<n_Locations; ++j) {
                for (unsigned k=0; k<n_Dimension; ++k) {
                        locations[count] =       double(rand())/double(RAND_MAX);
                        ++count;
                }
        }
        std::cout << std::scientific;
        for (unsigned j=0; j < n_Locations; ++j) {
                for (unsigned k=0; k < n_Dimension; ++k) {
                        std::cout << locations[j*n_Dimension+k] << "\t";
                }
                std::cout << std::endl;
        }

        KDTree* A               =       new KDTree(n_Locations, n_Dimension, locations);
        delete locations;

        double* sorted_Locations=       new double[n_Locations*n_Dimension];
        

        A->sort_KDTree();

        A->get_Location(sorted_Locations);
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