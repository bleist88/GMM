#include "Particle.hh"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

#include "Vector.hh"
#include "Vectors.hh"

//////////////////////////////////////////////////////   C O N S T R U C T O R S

Particle :: Particle()
{
    _mass       = 0;
    _body       = 0;
    _temp       = 0;
}

Particle :: Particle( double mass )
{
    _mass       = mass;
    _body       = 0;
    _temp       = 0;
}

Particle :: Particle( double mass, double body )
{
    _mass       = mass;
    _body       = body;
    _temp       = 0;
}

Particle :: Particle( double mass, Vector position )
{
    _mass       = mass;
    _body       = 0;
    _temp       = 0;
    _position   = position;
}

Particle :: Particle( double mass, Vector position, Vector velocity )
{
    _mass       = mass;
    _body       = 0;
    _temp       = 0;
    _position   = position;
    _velocity   = velocity;
}

Particle :: ~Particle(){}


////////////////////////////////////////////////////////////////   M E M B E R S

// Setting.

void        Particle :: set_mass( double mass )
{
    _mass = mass;
}

void        Particle :: set_body( double body )
{
    _body = body;
}

void        Particle :: set_temp( double temp )
{
    _temp = temp;
}

void        Particle :: set_position( Vector position )
{
    _position.set( position );
}

void        Particle :: set_velocity( Vector velocity )
{
    _velocity.set( velocity );
}

void        Particle :: set_acceleration( Vector acceleration )
{
    _acceleration.set( acceleration );
}

void        Particle :: set_position( double e1, double e2, double e3 )
{
    _position.set( e1, e2, e3 );
}

void        Particle :: set_velocity( double e1, double e2, double e3 )
{
    _velocity.set( e1, e2, e3 );
}

void        Particle :: set_acceleration( double e1, double e2, double e3 )
{
    _acceleration.set( e1, e2, e3 );
}

// Returning.

double      Particle :: get_mass()
{
    return _mass;
}

double      Particle :: get_body()
{
    return _body;
}

double      Particle :: get_temp()
{
    return _temp;
}

Vector      Particle :: get_position()
{
    return _position.get();
}

Vector      Particle :: get_velocity()
{
    return _velocity.get();
}

Vector      Particle :: get_acceleration()
{
    return _acceleration.get();
}

// Accessing.

double&     Particle :: mass()
{
    return _mass;
}

double&     Particle :: body()
{
    return _body;
}

double&     Particle :: temp()
{
    return _temp;
}

Vector&     Particle :: position()
{
    return _position;
}

Vector&     Particle :: velocity()
{
    return _velocity;
}

Vector&     Particle :: acceleration()
{
    return _acceleration;
}

////////////////////////////////////////////////////////////////   M E T H O D S

void        Particle :: propagate( double dt )
{
    _velocity.e1() += dt * _acceleration.get_e1();
    _velocity.e2() += dt * _acceleration.get_e2();
    _velocity.e3() += dt * _acceleration.get_e3();

    _position.e1() += dt * _velocity.get_e1();
    _position.e2() += dt * _velocity.get_e2();
    _position.e3() += dt * _velocity.get_e3();

//    _acceleration.set( 0, 0, 0 );
}

//////////////////////////////////////////////////////////////////   O U T P U T

void        Particle :: write( ofstream &out_file )
{
    out_file << "    " << _mass;
    out_file << "    " << _body;
    out_file << "    " << _temp;
    out_file << "    " << _position.get_e1();
    out_file << "    " << _position.get_e2();
    out_file << "    " << _position.get_e3();
    out_file << "    " << _velocity.get_e1();
    out_file << "    " << _velocity.get_e2();
    out_file << "    " << _velocity.get_e3();
    out_file           << endl;
}

void        Particle :: write_in_line( ofstream &out_file )
{
    out_file << "<";
    out_file << "m:" << _mass                   << ",";
    out_file << "b:" << _body                   << ",";
    out_file << "T:" << _temp                   << ",";
    out_file << "x:" << _position.get_e1()      << ",";
    out_file << "y:" << _position.get_e2()      << ",";
    out_file << "z:" << _position.get_e3()      << ",";
    out_file << "vz:" << _velocity.get_e1()     << ",";
    out_file << "vy:" << _velocity.get_e2()     << ",";
    out_file << "vz:" << _velocity.get_e3()     << ">";
}

void        Particle :: display()
{
    cout << "## Particle ##" << endl;
    cout << "   mass          " << _mass << endl;
    cout << "   body          " << _body << endl;
    cout << "   temp          " << _temp << endl;
    cout << "   position      " ;  _position.display();
    cout << "   velocity      " ;  _velocity.display();
}
