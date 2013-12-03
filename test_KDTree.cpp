//
//  test_KDTree.cpp
//  
//
//  Created by Sivaram Ambikasaran on 12/3/13.
//
//

#include <iostream>
#include "./KDTree.hpp"

int main(int argc, char** argv) {
        unsigned n_Locations    =       100;
        unsigned n_Dimension    =       3;
        double** locations;
        locations       =       new double* [n_Locations];
        for (unsigned j=0; j<n_Locations; ++j) {
                locations[j]    =       new double[n_Dimension];
                for (unsigned k=0; k<n_Dimension; ++k) {
                        locations[j][k] =       j+k;
                }
        }
        KDTree* A        =       new KDTree(n_Locations, n_Dimension, locations);
}