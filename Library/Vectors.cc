#include "../Include/Vectors.hh"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

#include "../Include/Vector.hh"

//////////////////////////////////////////////////////   C O N S T R U C T O R S

Vectors :: Vectors(){}

Vectors :: Vectors( int size )
{
    _size       = size;
    _coords     = 1;
    _vector     = new Vector[size];
    for( int i = 0; i < _size; i++ ){ _vector[i].set_coords(_coords); };
}

Vectors :: Vectors( int size, int coords )
{
    _size       = size;
    _coords     = coords;
    _vector     = new Vector[size];
    for( int i = 0; i < _size; i++ ){ _vector[i].set_coords(_coords); };
}

Vectors :: ~Vectors(){}

////////////////////////////////////////////////////////////////   M E M B E R S

// Setting.

void        Vectors :: set_coords( int coords )
{
    _coords = coords;
}

void        Vectors :: set( Vector vector[] )
{
    for( int i = 0; i < _size; i++ ){ _vector[i].set( vector[i] ); };
}

void        Vectors :: set_e1( double e1[] )
{
    for( int i = 0; i < _size; i++ ){ _vector[i].set_e1( e1[i] ); };
}

void        Vectors :: set_e2( double e2[] )
{
    for( int i = 0; i < _size; i++ ){ _vector[i].set_e2( e2[i] ); };
}

void        Vectors :: set_e3( double e3[] )
{
    for( int i = 0; i < _size; i++ ){ _vector[i].set_e3( e3[i] ); };
}

void        Vectors :: set( int i, Vector vector )
{
    _vector[i].set( vector );
}

void        Vectors :: set_e1( int i, double e1 )
{
    _vector[i].set_e1( e1 );
}

void        Vectors :: set_e2( int i, double e2 )
{
    _vector[i].set_e2( e2 );
}

void        Vectors :: set_e3( int i, double e3 )
{
    _vector[i].set_e3( e3 );
}


// Returning.

int         Vectors :: get_size()
{
    return _size;
}

int         Vectors :: get_coords()
{
    return _coords;
}

Vector      Vectors :: get( int i )
{
    return _vector[i].get();
}

double      Vectors :: get_e1( int i )
{
    return _vector[i].get_e1();
}

double      Vectors :: get_e2( int i )
{
    return _vector[i].get_e2();
}

double      Vectors :: get_e3( int i )
{
    return _vector[i].get_e3();
}

double      Vectors :: get_mag( int i )
{
    return _vector[i].get_mag();
}

// Accessing.

int&        Vectors :: size()
{
    return _size;
}

int&        Vectors :: coords()
{
    return _coords;
}

Vector&     Vectors :: vector( int i )
{
    return _vector[i];
}

double&     Vectors :: e1( int i )
{
    return _vector[i].e1();
}

double&     Vectors :: e2( int i )
{
    return _vector[i].e2();
}

double&     Vectors :: e3( int i )
{
    return _vector[i].e3();
}

double&     Vectors :: mag( int i )
{
    return _vector[i].mag();
}

////////////////////////////////////////////////////////////////   M E T H O D S

// Calculations.

void        Vectors :: calc_mag()
{
    for( int i = 0; i < _size; i++ ){ _vector[i].calc_mag(); };
}

void        Vectors :: calc_mag( int i )
{
    _vector[i].calc_mag();
}

void        Vectors :: scale( double factor )
{
    for( int i = 0; i < _size; i++ ){ _vector[i].scale( factor ); };
}

void        Vectors :: scale( int i, double factor )
{
    _vector[i].scale( factor );
}

void        Vectors :: transform( int coords )
{
    for( int i = 0; i < _size; i++ ){ _vector[i].transform( coords ); };
}

//////////////////////////////////////////////////////////////////   O U T P U T

void        Vectors :: write( string file_name )
{
    ofstream out_file( file_name.c_str() );
    write( out_file );
    out_file.close();
}

void        Vectors :: write( ofstream &out_file )
{
    _vector[0].write_header( out_file );
    for( int i = 0; i < _size; i++ ){ _vector[i].write( out_file ); };
}
