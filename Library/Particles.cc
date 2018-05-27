#include "Particles.hh"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

#include "Vector.hh"
#include "Vectors.hh"
#include "Particle.hh"

//////////////////////////////////////////////////////   C O N S T R U C T O R S

Particles :: Particles(){};

Particles :: Particles( int size )
{
    _size           = size;
    _particle       = new Particle[_size];
};

Particles :: Particles( string file_name )
{
    from_file( file_name );
};

Particles :: ~Particles(){};

////////////////////////////////////////////////////////////////   M E M B E R S

// Setting.

void        Particles :: from_file( string file_name )
{
    // Count lines from file.

    _size   = count_lines( file_name );

    // Copy data from file into Particles.

    ifstream in_file( file_name.c_str() );

    double    m,b,t,x,y,z,vx,vy,vz;
    string    line;

    _particle   = new Particle[_size];

    int i = 0;

    while( getline( in_file, line ) ){

        stringstream ss(line);

        if( ss >> m >> b >> t >> x >> y >> z >> vx >> vy >> vz ){

            _particle[i].set_mass( m );
            _particle[i].set_body( b );
            _particle[i].set_temp( t );
            _particle[i].set_position( x, y, z );
            _particle[i].set_velocity( vx, vy, vz );

            i += 1;

        };
    };

    in_file.close();
}

void        Particles :: set_mass( int i, double mass )
{
    _particle[i].set_mass( mass );
}

void        Particles :: set_body( int i, double body )
{
    _particle[i].set_body( body );
}

void        Particles :: set_position( int i, Vector position )
{
    _particle[i].set_position( position );
}

void        Particles :: set_position( int i, double e1, double e2, double e3 )
{
    _particle[i].set_position( e1, e2, e3 );
}

void        Particles :: set_velocity( int i, Vector velocity )
{
    _particle[i].set_velocity( velocity );
}

void        Particles :: set_velocity( int i, double e1, double e2, double e3 )
{
    _particle[i].set_velocity( e1, e2, e3 );
}

void        Particles :: set_acceleration( int i, Vector acceleration )
{
    _particle[i].set_acceleration( acceleration );
}

void        Particles :: set_acceleration( int i, double e1, double e2, double e3 )
{
    _particle[i].set_acceleration( e1, e2, e3 );
}

// Returning.

int         Particles :: get_size()
{
    return _size;
}

double      Particles :: get_mass( int i )
{
    return _particle[i].get_mass();
}

double      Particles :: get_body( int i )
{
    return _particle[i].get_body();
}

Vector      Particles :: get_position( int i )
{
    return _particle[i].get_position();
}

Vector      Particles :: get_velocity( int i )
{
    return _particle[i].get_velocity();
}

Vector      Particles :: get_acceleration( int i )
{
    return _particle[i].get_acceleration();
}

// Accessing.

int&        Particles :: size()
{
    return _size;
}

Particle&   Particles :: particle( int i )
{
    return _particle[i];
}

double&     Particles :: mass( int i )
{
    return _particle[i].mass();
}

double&     Particles :: body( int i )
{
    return _particle[i].body();
}

Vector&     Particles :: position( int i )
{
    return _particle[i].position();
}

Vector&     Particles :: velocity( int i )
{
    return _particle[i].velocity();
}

Vector&     Particles :: acceleration( int i )
{
    return _particle[i].acceleration();
}

////////////////////////////////////////////////////////////////   M E T H O D S

void        Particles :: populate( int e, vector<double> x, vector<double> pdf )
{
    vector<double>      cdf     = CDF( x, pdf );

    for( int i = 0; i < _size; i++ ){

        switch( e ){    // Need to allow particles to set their e1, v1, r1 ..etc.

            case 1:
                position(i).set_e1( from_cdf( x, pdf ) );  break;

            case 2:
                position(i).set_e2( from_cdf( x, pdf ) );  break;

            case 3:
                position(i).set_e3( from_cdf( x, pdf ) );  break;

        };
    };
}

void        Particles :: populate( int e, double a, double b )
{
    for( int i = 0; i < _size; i++ ){

        switch( e ){    // Need to allow particles to set their e1, v1, r1 ..etc.

            case 1:
                position(i).set_e1( between(a,b) );  break;

            case 2:
                position(i).set_e2( between(a,b) );  break;

            case 3:
                position(i).set_e3( between(a,b) );  break;

        };
    };
}

void        Particles :: propagate( double dt )
{
    for( int i = 0; i < _size; i++ ){
        _particle[i].propagate( dt );
        _particle[i].set_acceleration( 0, 0, 0 );
    };
}

void        Particles :: move( double x, double y, double z )
{
    for( int i = 0; i < _size; i++ ){
        _particle[i].position().e1() += x;
        _particle[i].position().e2() += y;
        _particle[i].position().e3() += z;
    };
}

void        Particles :: guide( double vx, double vy, double vz )
{
    for( int i = 0; i < _size; i++ ){
        _particle[i].velocity().e1() += vx;
        _particle[i].velocity().e2() += vy;
        _particle[i].velocity().e3() += vz;
    };
}

//////////////////////////////////////////////////////////////////   O U T P U T

void        Particles :: write( string file_name )
{
    ofstream    out_file( file_name.c_str() );

    out_file << "#<  mass        float64" << endl;
    out_file << "#<  body        float64" << endl;
    out_file << "#<  temp        float64" << endl;
    out_file << "#<  x           float64" << endl;
    out_file << "#<  y           float64" << endl;
    out_file << "#<  z           float64" << endl;
    out_file << "#<  vx          float64" << endl;
    out_file << "#<  vy          float64" << endl;
    out_file << "#<  vz          float64" << endl;

    for( int i = 0; i < _size; i++ ){ _particle[i].write( out_file ); };

    out_file.close();
}

void        Particles :: display( int i )
{
    _particle[i].display();
}
