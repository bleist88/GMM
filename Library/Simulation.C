//  N - P a r t i c l e   S i m u l a t i o n

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

////////////////////////////////////////////////////////////////////////////////
// Simulation.

int main()
{
    //  splash.

    cout << endl << "N - B o d y   S i m u l a t i o n" << endl << endl;

    //  get configuration parameters.

    double          dt          = atof( get_config( "dt",       "Configs" ).c_str() );
    double          unit_t      = atof( get_config( "unit_t",   "Configs" ).c_str() );
    double          unit_l      = atof( get_config( "unit_l",   "Configs" ).c_str() );
    double          unit_m      = atof( get_config( "unit_m",   "Configs" ).c_str() );

    int             sim_time    = atof( get_config( "sim_time", "Configs" ).c_str() );
    int             out_freq    = atof( get_config( "out_freq", "Configs" ).c_str() );

    string          in_file     = get_config( "in_file", "Configs" );
    string          out_dir     = get_config( "out_dir", "Configs" );
    string          out_file    = "";

    stringstream    time_string;

    //  initialize interaction manager.

    Interactions    interactions;

    interactions.set_time( unit_t );
    interactions.set_length( unit_l );
    interactions.set_mass( unit_m );

    //  initialize distribution from input file.

    Particles       distribution( in_file );

    //  begin time iteration.

    for( int t = 0; t < sim_time; t++ ){

        //  splash.

        cout << "\r" << "Time: " << t << "    " << t * dt << "  s";
        cout.flush();

        time_string.str("");
        time_string << t;

        //  calculate the gravitational acceleration of each particle.

        interactions.gravitate( distribution );
        interactions.collide( distribution );

        //  propagate using     dx = v * dt.

        distribution.propagate( dt );

        //  write the output file for this time stamp.
        //  (this needs to have the out_freq incorporated.)

        out_file.clear();
        out_file    += out_dir + time_string.str() + ".dat";

        distribution.write( out_file );

    };  cout << endl;
}

    //  ////////////////////////////////////////////////////////////////////////
    //  get distribution parameters.
    //
    //  this section needs to be allocated to another function in another file.
    //
    //  1.  read distributions parameters file.
    //  2.  read input distribution files.
    //  3.  place them into a single distributions file.
    //      -   should they get some sort of marker to indicate the input file?
    //
    //int                 dist_count  = count_lines("Distributions");
    //
    //vector<string>      input(dist_count);
    //vector<string>      output(dist_count);
    //vector<double>      x(dist_count);
    //vector<double>      y(dist_count);
    //vector<double>      z(dist_count);
    //vector<double>      vx(dist_count);
    //vector<double>      vy(dist_count);
    //vector<double>      vz(dist_count);
    //
    //for( int i = 0; i < dist_count; i++ ){
    //    input[i]    = get_dist( i, "input", "Distributions" );
    //    output[i]   = get_dist( i, "output", "Distributions" );
    //    x[i]        = atof( get_dist( i, "x", "Distributions" ).c_str() );
    //    y[i]        = atof( get_dist( i, "y", "Distributions" ).c_str() );
    //    z[i]        = atof( get_dist( i, "z", "Distributions" ).c_str() );
    //    vx[i]       = atof( get_dist( i, "vx", "Distributions" ).c_str() );
    //    vy[i]       = atof( get_dist( i, "vy", "Distributions" ).c_str() );
    //    vz[i]       = atof( get_dist( i, "vz", "Distributions" ).c_str() );
    //};
    //
    //  instantiate distributions of particles.
    //
    //vector<Particles>       distributions(dist_count);
    //
    //for( int i = 0; i < dist_count; i++ ){
    //
    //    distributions[i]    = Particles( input[i] );
    //    distributions[i].move( x[i], y[i], z[i] );
    //    distributions[i].guide( vx[i], vy[i], vz[i] );
    //};

    //  this following part was placed in the time iteration loop.
    //
    //  calculate acceleration for each distribution.
    //
    //for( int i = 0; i < dist_count; i++ ){
    //    for( int j = i; j < dist_count; j++ ){
    //        interactions.gravitate(
    //            distributions[i], distributions[j], 1e-16
    //        );
    //    };
    //};
    //
    // output.
    //
    //out_file.clear();
    //time_string.str("");
    //time_string << t;
    //out_file += output[i] + time_string.str() + ".dat";
    //
    //distributions[i].write( out_file );

    //  ////////////////////////////////////////////////////////////////////////
