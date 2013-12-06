//
//  KDTree.cpp
//  
//
//  Created by Sivaram Ambikasaran on 12/3/13.
//
//

#include "KDTree.hpp"
#include <Eigen/Dense>

KDTree::KDTree(const unsigned n_Locations, const unsigned n_Dimension, double* locations) {
        this->n_Locations       =       n_Locations;
        this->n_Dimension       =       n_Dimension;

        sorted_Locations        =       Eigen::MatrixXd(n_Locations, n_Dimension);

        unsigned count          =       0;
        for (unsigned j=0; j<n_Locations; ++j) {
                for (unsigned k=0; k<n_Dimension; ++k) {
                        sorted_Locations(j,k)   =       locations[count];
                        ++count;
                }
        }
//        std::cout << sorted_Locations << std::endl;
}

void KDTree::merge_Sorted_Lists(unsigned n_Left_Start, unsigned n_Left_Size, unsigned n_Right_Start, unsigned n_Right_Size, unsigned n_Index) {
//        std::cout << "merge_Sorted_Lists" << std::endl;
        
        Eigen::MatrixXd temp_List(n_Left_Size+n_Right_Size, n_Dimension);

        unsigned j_Left =       n_Left_Start;
        unsigned j_Right=       n_Right_Start;

        unsigned j      =       0;

//        std::cout << 1 << std::endl;
        while (j_Left < n_Left_Start + n_Left_Size && j_Right < n_Right_Start + n_Right_Size) {
                if (sorted_Locations(j_Left, n_Index) < sorted_Locations(j_Right, n_Index)) {
                        temp_List.row(j)=       sorted_Locations.row(j_Left);
                        ++j_Left;
                }
                else {
                        temp_List.row(j)=       sorted_Locations.row(j_Right);
                        ++j_Right;
                }
                ++j;
        }

//        std::cout << 1 << std::endl;
        while (j_Left < n_Left_Start + n_Left_Size) {
                temp_List.row(j)        =       sorted_Locations.row(j_Left);
                ++j_Left;
                ++j;
        }

//        std::cout << 1 << std::endl;
        while (j_Right < n_Right_Start + n_Right_Size) {
                temp_List.row(j)        =       sorted_Locations.row(j_Right);
                ++j_Right;
                ++j;
        }

//        std::cout << 1 << std::endl;
        sorted_Locations.block(n_Left_Start, 0, n_Left_Size + n_Right_Size, n_Dimension)        =       temp_List;
//        std::cout << "merge_Sorted_Lists" << std::endl;
}

void KDTree::merge_Sort(unsigned n_Start, unsigned n_Size, unsigned n_Index) {
//        std::cout << "merge_Sort" << std::endl;
        if (n_Size<=1) {
                //      Do nothing
                return;
        }
        else {
                unsigned n_Left_Start   =       n_Start;
                unsigned n_Left_Size    =       n_Size/2;
                unsigned n_Right_Start  =       n_Start+n_Left_Size;
                unsigned n_Right_Size   =       n_Size-n_Left_Size;

                merge_Sort(n_Left_Start, n_Left_Size, n_Index);
                merge_Sort(n_Right_Start, n_Right_Size, n_Index);

                merge_Sorted_Lists(n_Left_Start, n_Left_Size, n_Right_Start, n_Right_Size, n_Index);
        }
//        std::cout << "merge_Sort" << std::endl;
}

void KDTree::sort_KDTree(unsigned n_Start, unsigned n_Size, unsigned n_Index) {
        if (n_Size<=1) {
                //      Do nothing
                return;
        }
        else {
//                std::cout << n_Size << std::endl;
                n_Index                 =       n_Index%n_Dimension;
                merge_Sort(n_Start, n_Size, n_Index);

                ++n_Index;

                unsigned n_Left_Start   =       n_Start;
                unsigned n_Left_Size    =       n_Size/2;
                unsigned n_Right_Start  =       n_Start+n_Left_Size;
                unsigned n_Right_Size   =       n_Size-n_Left_Size;

                sort_KDTree(n_Left_Start, n_Left_Size, n_Index);
                sort_KDTree(n_Right_Start, n_Right_Size, n_Index);
        }
}

void KDTree::sort_KDTree() {
        if (n_Locations<=1) {
                //      Do nothing
                return;
        }
        else {
                //      Number of point on the left cluster
                sort_KDTree(0, n_Locations, 0);
        }
}

void KDTree::get_Location(double* locations) {
//        std::cout << sorted_Locations << std::endl;
        unsigned count  =       0;
        for (unsigned j=0; j<n_Locations; ++j) {
                for (unsigned k=0; k<n_Dimension; ++k) {
                        locations[count] =       sorted_Locations(j,k);
                        ++count;
                }
        }
}

void KDTree::get_Location(const unsigned n_Index, double* location) {
//        location        =       new double [n_Dimension];
        for (unsigned k=0; k<n_Dimension; ++k) {
                location[k]     =       sorted_Locations(n_Index,k);
        }
}

void KDTree::get_Location(const unsigned n_Index, const unsigned n_Coordinate, double& location) {
        location        =       sorted_Locations(n_Index, n_Coordinate);
}