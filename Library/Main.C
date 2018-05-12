///   N - P a r t i c l e   S i m u l a t i o n

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

    double          unit_t      = atof( get_config( "unit_t", "Configs" ).c_str() );
    double          unit_l      = atof( get_config( "unit_l", "Configs" ).c_str() );
    double          unit_m      = atof( get_config( "unit_m", "Configs" ).c_str() );

    int             sim_time    = atof( get_config( "sim_time", "Configs" ).c_str() );
    int             out_freq    = atof( get_config( "out_freq", "Configs" ).c_str() );
    string          out_dir     = get_config( "out_dir", "Configs" );

    string          out_file    = "";
    stringstream    time_string;

    //  get distribution parameters.

    int                 dist_count  = count_lines("Distributions");

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

    //  instantiate distributions of particles.

    vector<Particles>       distributions(dist_count);

    for( int i = 0; i < dist_count; i++ ){

        distributions[i]    = Particles( input[i] );
        distributions[i].move( x[i], y[i], z[i] );
        distributions[i].guide( vx[i], vy[i], vz[i] );

    };

    //  initialize interaction manager.

    Interactions interactions;

    interactions.scale_time( unit_t );
    interactions.scale_length( unit_l );
    interactions.scale_mass( unit_m );

    //  iterate through time.
    //  interact each distribution with all others.

    for( int t = 0; t < sim_time; t++ ){

        //  splash.

        cout << "\r" << "Time: " << t << "    " << t * unit_t << "  s";
        cout.flush();

        //  calculate acceleration for each distribution.

        for( int i = 0; i < dist_count; i++ ){
            for( int j = 0; j < dist_count; j++ ){
                interactions.gravitate( distributions[i], distributions[j] );
            };
        };

        //  propagate using     dx = v * dt.

        for( int i = 0; i < dist_count; i++ ){

            distributions[i].propagate( unit_t );

            // output.

            out_file.clear();
            time_string.str("");
	        time_string << t;
	        out_file += output[i] + time_string.str() + ".dat";

            distributions[i].write( out_file );

	    };
    };

    cout << endl;

}
