#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "libs/axis.h"
#include "libs/custom_boost_point.h"
#include "libs/data.h"
#include "libs/profile.h"

int main(){
    // defining types
    typedef float precision;
    typedef boost::geometry::model::point<precision, 3, boost::geometry::cs::cartesian> point;
    typedef boost::geometry::model::box<point> box;
    // Loading data
    Data<float> myData;
    try{
        myData.load("../examples/angular_correlation_in_pixels.txt",2);
    }catch(std::exception &err){
        std::cout << err.what() << "\n";
    }
    myData.spherical2euclidean();
    // Creating tree 
    boost::geometry::index::rtree< QPoint, boost::geometry::index::quadratic<16, 4> > tree;
    std::vector<QPoint> vec;
    for (int i=0; i<myData.x().size(); ++i){
        QPoint gal(myData.ind()[i],myData.x()[i], myData.y()[i], myData.z()[i], myData.val()[i], myData.weight()[i], myData.sample()[i]);
        vec.push_back(gal);
        tree.insert(gal);
    }
    // Defining binning
    int nbins = 20;
    float min = 0.015;
    float max = 0.1;
    Axis<float> axis1, axis2;
    for (int i=0; i<nbins+1; ++i){
        float bin;
        bin = pow(10,log10(min) + (log10(max) - log10(min)) * float(i)/nbins);
        axis1.push_back(bin);
    }
    Profile<float,float> prof(axis1);
    // first loop
    auto start = std::chrono::high_resolution_clock::now();
    float dist_max = 2*sin(max/2.); //max distance in Euclidean space
    std::vector<QPoint> results;  // faster to create a single vector and to clear it than to create a new each time. 
    for (int i=0; i<myData.size(); ++i){
        if (i%1000==0)
            std::cout << i << "\n"; 
        point corner_min(vec.data()[i].x-dist_max,vec.data()[i].y-dist_max,vec.data()[i].z-dist_max);
        point corner_max(vec.data()[i].x+dist_max,vec.data()[i].y+dist_max,vec.data()[i].z+dist_max);
        box query_box(corner_min,corner_max);
        tree.query(boost::geometry::index::intersects(query_box), std::back_inserter(results));
        for (int j=0; j<results.size(); ++j){
            if(results.data()[j].ind > vec.data()[i].ind){
                float dist = sqrt( (vec.data()[i].x-results.data()[j].x)*(vec.data()[i].x-results.data()[j].x) + (vec.data()[i].y-results.data()[j].y)*(vec.data()[i].y-results.data()[j].y) + (vec.data()[i].z-results.data()[j].z)*(vec.data()[i].z-results.data()[j].z) );
                dist = 2*std::asin(dist/2.);
                if ( (dist<min) | (dist>=max) )
                    continue;    
                prof.fill(dist,vec.data()[i].val*results.data()[j].val,vec.data()[i].weight*results.data()[j].weight);
                //prof.fill(dist,vec.data()[i].val,vec.data()[i].weight);
                //prof.fill(dist,results.data()[j].val,results.data()[j].weight);
            }
        }
        results.clear();
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
   
    std::cout << "OUTPUT" << "\n";
    std::cout << prof.getData() << "\n";

    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << "Tree ellapsed time " << microseconds/1e6 << " s" <<  "\n";
}
