#ifndef PARTICLE_HH
#define PARTICLE_HH

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

#include "Vector.hh"
#include "Vectors.hh"

////////////////////////////////////////////////////////////////////////////////

class Particle
{

//////////////////////////////////////////////////////   C O N S T R U C T O R S

public:

    Particle();
    Particle( double mass );
    Particle( double mass, double body );
    Particle( double mass, Vector position );
    Particle( double mass, Vector position, Vector velocity );
    virtual ~Particle();

////////////////////////////////////////////////////////////////   M E M B E R S

private:

    double      _mass;
    double      _body;
    double      _temp;

    Vector      _position;
    Vector      _velocity;
    Vector      _acceleration;

public:

    // Setting.

    void        set_mass( double mass );
    void        set_body( double body );
    void        set_temp( double temp );

    void        set_position( Vector position );
    void        set_velocity( Vector velocity );
    void        set_acceleration( Vector acceleration );

    void        set_position( double e1, double e2, double e3 );
    void        set_velocity( double e1, double e2, double e3 );
    void        set_acceleration( double e1, double e2, double e3 );

    // Returning.

    double      get_mass();
    double      get_body();
    double      get_temp();

    Vector      get_position();
    Vector      get_velocity();
    Vector      get_acceleration();

    // Accessing.

    double&     mass();
    double&     body();
    double&     temp();

    Vector&     position();
    Vector&     velocity();
    Vector&     acceleration();

////////////////////////////////////////////////////////////////   M E T H O D S

private:

public:

    void        propagate( double dt );

//////////////////////////////////////////////////////////////////   O U T P U T

private:

public:

    void        write( ofstream &out_file );
    void        write_in_line( ofstream &out_file );
    void        display();

////////////////////////////////////////////////////////////////////////////////
};
#endif
