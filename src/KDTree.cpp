//
//  KDTree.cpp
//  
//
//  Created by Sivaram Ambikasaran on 12/3/13.
//
//

#include "KDTree.hpp"
#include <Eigen/Dense>

KDTree::KDTree(const unsigned n_Locations, const unsigned n_Dimension, double* locations, const unsigned n_Properties, double* properties) {
        this->n_Locations       =       n_Locations;
        this->n_Dimension       =       n_Dimension;
        this->n_Properties      =       n_Properties;

        sorted_Contents         =       Eigen::MatrixXd(n_Locations, n_Dimension+n_Properties);

        unsigned count_Location =       0;
        unsigned count_Property =       0;

        for (unsigned j=0; j<n_Locations; ++j) {
                for (unsigned k=0; k<n_Dimension; ++k) {
                        sorted_Contents(j,k)    =       locations[count_Location];
                        ++count_Location;
                }
                for (unsigned k=n_Dimension; k<n_Dimension+n_Properties; ++k) {
                        sorted_Contents(j,k)    =       properties[count_Property];
                        ++count_Property;
                }
        }
}

void KDTree::merge_Sorted_Lists(unsigned n_Left_Start, unsigned n_Left_Size, unsigned n_Right_Start, unsigned n_Right_Size, unsigned n_Index) {

        Eigen::MatrixXd temp_List(n_Left_Size+n_Right_Size, n_Dimension+n_Properties);

        unsigned j_Left =       n_Left_Start;
        unsigned j_Right=       n_Right_Start;

        unsigned j      =       0;

        while (j_Left < n_Left_Start + n_Left_Size && j_Right < n_Right_Start + n_Right_Size) {
                if (sorted_Contents(j_Left, n_Index) < sorted_Contents(j_Right, n_Index)) {
                        temp_List.row(j)=       sorted_Contents.row(j_Left);
                        ++j_Left;
                }
                else {
                        temp_List.row(j)=       sorted_Contents.row(j_Right);
                        ++j_Right;
                }
                ++j;
        }

        while (j_Left < n_Left_Start + n_Left_Size) {
                temp_List.row(j)        =       sorted_Contents.row(j_Left);
                ++j_Left;
                ++j;
        }

        while (j_Right < n_Right_Start + n_Right_Size) {
                temp_List.row(j)        =       sorted_Contents.row(j_Right);
                ++j_Right;
                ++j;
        }

        sorted_Contents.block(n_Left_Start, 0, n_Left_Size + n_Right_Size, n_Dimension+n_Properties)        =       temp_List;
}

void KDTree::merge_Sort(unsigned n_Start, unsigned n_Size, unsigned n_Index) {
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
}

void KDTree::sort_KDTree(unsigned n_Start, unsigned n_Size, unsigned n_Index) {
        if (n_Size<=1) {
                //      Do nothing
                return;
        }
        else {
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

void KDTree::get_Location_Properties(double* locations, double* properties) {
        unsigned count_Location         =       0;
        unsigned count_Property         =       0;
        for (unsigned j=0; j<n_Locations; ++j) {
                for (unsigned k=0; k<n_Dimension; ++k) {
                        locations[count_Location]       =       sorted_Contents(j,k);
                        ++count_Location;
                }
                for (unsigned k=n_Dimension; k<n_Dimension+n_Properties; ++k) {
                        properties[count_Property]      =       sorted_Contents(j,k);
                        ++count_Property;
                }
        }
}

void KDTree::get_Location_Properties(const unsigned n_Index, double* location, double* properties) {
        for (unsigned k=0; k<n_Dimension; ++k) {
                location[k]     =       sorted_Contents(n_Index,k);
        }
        for (unsigned k=0; k<n_Properties; ++k) {
                properties[k]   =       sorted_Contents(n_Index,k+n_Dimension);
        }
}