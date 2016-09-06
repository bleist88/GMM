#ifndef PARTICLES_HH
#define PARTICLES_HH

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

////////////////////////////////////////////////////////////////////////////////

class Particles
{

//////////////////////////////////////////////////////   C O N S T R U C T O R S

public:

    Particles();
    Particles( int size );
    Particles( string file_name );
    virtual ~Particles();

////////////////////////////////////////////////////////////////   M E M B E R S

private:

    int         _size;
    Particle*   _particle;

public:

    // Setting.

    void        from_file( string file_name );

    void        set_mass( int i, double mass );
    void        set_body( int i, double body );
    void        set_temp( int i, double temp );

    void        set_position( int i, Vector position );
    void        set_position( int i, double e1, double e2, double e3 );
    void        set_p1( int i, double p1 );
    void        set_p2( int i, double p2 );
    void        set_p3( int i, double p3 );

    void        set_velocity( int i, Vector velocity );
    void        set_velocity( int i, double e1, double e2, double e3 );

    void        set_acceleration( int i, Vector acceleration );
    void        set_acceleration( int i, double e1, double e2, double e3 );


    // Returning.

    int         get_size();

    double      get_mass( int i );
    double      get_body( int i );
    double      get_temp( int i );

    Vector      get_position( int i );
    Vector      get_velocity( int i );
    Vector      get_acceleration( int i );


    // Accessing.

    int&        size();

    Particle&   particle( int i );

    double&     mass( int i );
    double&     body( int i );
    double&     temp( int i );

    Vector&     position( int i );
    Vector&     velocity( int i );
    Vector&     acceleration( int i );

////////////////////////////////////////////////////////////////   M E T H O D S

private:

public:

    void        populate( int e, vector<double> x, vector<double> pdf );
    void        populate( int e, double a, double b );

    void        propagate( double dt );

    void        move( double x, double y, double z );
    void        guide( double vx, double vy, double vz );

//////////////////////////////////////////////////////////////////   O U T P U T

private:

public:

    void        write( string file_name );
    void        display( int i );

////////////////////////////////////////////////////////////////////////////////
};
#endif
