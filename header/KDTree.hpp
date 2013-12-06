//
//  KDTree.hpp
//  
//
//  Created by Sivaram Ambikasaran on 12/3/13.
//
//

#ifndef __KDTREE_HPP__
#define __KDTREE_HPP__

#include <iostream>
#include <Eigen/Dense>

class KDTree {
private:
        unsigned n_Locations;           //      Number of locations.
        unsigned n_Dimension;           //      Number of dimensions.

        Eigen::MatrixXd sorted_Locations;      //      Array of sorted locations.
        
        void merge_Sorted_Lists(unsigned n_Left_Start, unsigned n_Left_Size, unsigned n_Right_Start, unsigned n_Right_Size, unsigned n_Index);
        void merge_Sort(unsigned n_Start, unsigned n_Size, unsigned n_Index);
        void sort_KDTree(unsigned n_Start, unsigned n_Size, unsigned n_Index);

public:
        //      Constructor.
        //      Usage:
        //      KDTree(10000, 3, locations);
        KDTree(const unsigned n_Locations, const unsigned n_Dimension, double* locations);
        
        //      KDTree sorting.
        void sort_KDTree();
        
        //      Obtains all the sorted location.
        //      Usage:
        //      get_Location(location);
        void get_Location(double* locations);
        
        //      Given an index, obtains the location from the sorted location.
        //      n_Index <= n_Locations.
        //      Usage:
        //      get_Location(1234, location);
        void get_Location(const unsigned n_Index, double* location);
        
        //      Given an index and dimension, obtains the location from the sorted location.
        //      n_Index <= n_Locations and n_Coordinate <= n_Dimension
        //      Usage:
        //      get_Location(1234, 2, location);
        void get_Location(const unsigned n_Index, const unsigned n_Coordinate, double& location);
};
#endif /* defined(__KDTREE_HPP__) */
