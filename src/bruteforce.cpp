#include <iostream>
#include <math.h>
#include <stdexcept>

#include "libs/axis.h"
#include "libs/data.h"
#include "libs/profile.h"

float Sky(float ra1, float dec1, float ra2, float dec2){
/* 
   Return angular distance on sphere.
   Assume pX[0] is RA and pX[1] is Dec. 
   Assume angles in radian.
*/
    double D_phi = dec2 - dec1;
    double D_lamb = ra2 - ra1;
    double D_sig;
    double term1, term2;
    term1 = sin(D_phi/2.) * sin(D_phi/2.);
    term2 = cos(dec1) * cos(dec2) * sin(D_lamb/2.) * sin(D_lamb/2.);
    
    D_sig = 2 * asin( sqrt(term1+term2) );
    return D_sig;
}

int main(int argc, char *argv[])
{
    // Loading data
    Data<float> myData;
    try{
        myData.load("../examples/angular_correlation_in_pixels.txt",2);
    }catch(std::exception &err){
        std::cout << err.what() << "\n";
    }
    // Defining binning
    int nbins = 20;
    float min = 0.015;
    float max = 0.5;
    Axis<float> axis1, axis2;
    for (int i=0; i<nbins+1; ++i){
        float bin;
        bin = pow(10,log10(min) + (log10(max) - log10(min)) * float(i)/nbins);
        axis1.push_back(bin);
    }

    Profile<float,float> prof(axis1);

    auto start = std::chrono::high_resolution_clock::now();
    // first loop
    for (int i=0; i<myData.size(); ++i){
        if (i%1000==0)
            std::cout << i << "\n";
        // second loop
        for (int j=i; j<myData.size(); ++j){
            float dist = Sky(myData.x()[i],myData.y()[i],myData.x()[j],myData.y()[j]);
            if ( (dist<min) | (dist>=max) )
                continue;
            prof.fill(dist,myData.val()[i]*myData.val()[j],myData.weight()[i]*myData.weight()[j]);
        }
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    
    std::cout << "OUTPUT" << "\n";
    std::cout << prof.getData() << "\n";

    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << "BruteForce ellapsed time " << microseconds/1e6 << " s" <<  "\n";
}
