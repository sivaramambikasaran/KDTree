//
//  KDTree.cpp
//  
//
//  Created by Sivaram Ambikasaran on 12/3/13.
//
//

#include "KDTree.hpp"

KDTree::KDTree(const unsigned n_Locations, const unsigned n_Dimension, double** locations) {
        this->n_Locations       =       n_Locations;
        this->n_Dimension       =       n_Dimension;
        this->locations         =       new double* [n_Locations];
        for (unsigned j=0; j<n_Locations; ++j) {
                this->locations[j]      =       new double[n_Dimension];
                for (unsigned k=0; k<n_Dimension; ++k) {
                        this->locations[j][k]   =       locations[j][k];
                }
        }
}

void KDTree::sort_KDTree() {
        sorted_Locations        =       new double* [n_Locations];
        for (unsigned j=0; j<n_Locations; ++j) {
                sorted_Locations[j]    =       new double[n_Dimension];
                for (unsigned k=0; k<n_Dimension; ++k) {
                        sorted_Locations[j][k] =       locations[j][k];
                }
        }
}

void KDTree::get_Location(double** locations) {
        locations       =       new double* [n_Locations];
        for (unsigned j=0; j<n_Locations; ++j) {
                locations[j]    =       new double[n_Dimension];
                for (unsigned k=0; k<n_Dimension; ++k) {
                        locations[j][k] =       sorted_Locations[j][k];
                }
        }
}

void KDTree::get_Location(const unsigned n_Index, double* location) {
        location        =       new double [n_Dimension];
        for (unsigned k=0; k<n_Dimension; ++k) {
                location[k]     =       sorted_Locations[n_Index][k];
        }
}

void KDTree::get_Location(const unsigned n_Index, const unsigned n_Coordinate, double& location) {
        location        =       sorted_Locations[n_Index][n_Coordinate];
}