//  Distributions Runner

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

#include "Utils.cc"
#include "Maths.cc"
#include "Vector.cc"
#include "Vectors.cc"
#include "Particle.cc"
#include "Particles.cc"
#include "Interactions.cc"

//  ////////////////////////////////////////////////////////////////////////////
//
//  This creates a single distribution from a selection of distributions listed
//  in the "Distributions" parameters file.
//
//  ////////////////////////////////////////////////////////////////////////////

int main()
{
    //  splash.

    cout << endl << "N - B o d y   D i s t r i b u t i o n    G e n e r a t o r"
         << endl;

    //   get distributions parameters from "Distributions".

    int                 dist_count  = count_lines("Distributions");
    int                 obj_count   = 0;

    vector<string>      input(dist_count);
    vector<string>      output(dist_count);
    vector<double>      x(dist_count);
    vector<double>      y(dist_count);
    vector<double>      z(dist_count);
    vector<double>      vx(dist_count);
    vector<double>      vy(dist_count);
    vector<double>      vz(dist_count);

    for( int i = 0; i < dist_count; i++ ){
        input[i]    = get_dist( i, "input", "Distributions" );
        output[i]   = get_dist( i, "output", "Distributions" );
        x[i]        = atof( get_dist( i, "x", "Distributions" ).c_str() );
        y[i]        = atof( get_dist( i, "y", "Distributions" ).c_str() );
        z[i]        = atof( get_dist( i, "z", "Distributions" ).c_str() );
        vx[i]       = atof( get_dist( i, "vx", "Distributions" ).c_str() );
        vy[i]       = atof( get_dist( i, "vy", "Distributions" ).c_str() );
        vz[i]       = atof( get_dist( i, "vz", "Distributions" ).c_str() );
    };

    //  create a single distribution.

    

}
