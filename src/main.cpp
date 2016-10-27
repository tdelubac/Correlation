#include <stdexcept>
#include <iostream>

#include "libs/data.h"

int main(int argc, char *argv[])
{
    Data<float> myData;
    try{
        myData.load("../examples/angular_correlation_in_pixels.txt",2);
    }catch(std::exception &err){
        std::cout << err.what() << "\n";
    }
    size_t i = 1;
    std::cout << myData.x()[i] << " " << myData.y()[i] << " " << myData.z()[i] << " " << myData.val()[i] << " " << myData.weight()[i] << " " << myData.sample()[i] << "\n";
}
