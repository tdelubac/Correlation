#include <stdexcept>
#include <iostream>

#include "libs/axis.h"
#include "libs/data.h"
#include "libs/profile.h"

int main(int argc, char *argv[])
{
    // Testing class data
    Data<float> myData;
    try{
        myData.load("../examples/angular_correlation_in_pixels.txt",2);
    }catch(std::exception &err){
        std::cout << err.what() << "\n";
    }
    size_t i = 1;
    std::cout << myData.x()[i] << " " << myData.y()[i] << " " << myData.z()[i] << " " << myData.val()[i] << " " << myData.weight()[i] << " " << myData.sample()[i] << "\n";

    // Testing profile class
    Axis<float> axis1, axis2;
    for (int i=0; i<10; ++i){
        axis1.push_back(i);
        axis2.push_back(i);
    }

    Profile<float,float> prof(axis1);
    
    std::cout << prof.getData() << "\n";
    prof.fill(3.5,1,2);
    prof.fill(3.5,2,1);
    prof.fill(-1,2,1);
    std::cout << prof.getData() << "\n";
}
