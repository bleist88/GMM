#ifndef VECTORS_HH
#define VECTORS_HH

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

#include "Vector.hh"

////////////////////////////////////////////////////////////////////////////////

class Vectors
{

//////////////////////////////////////////////////////   C O N S T R U C T O R S

public:

    Vectors();
    Vectors( int size );
    Vectors( int size, int coords );
    virtual ~Vectors();

////////////////////////////////////////////////////////////////   M E M B E R S

private:

    int         _size;          // number of vectors
    int         _coords;        // (1)cartesian, (2)cylindrical, (3)spherical
    Vector*     _vector;        // pointer to an array of vectors

public:

    // Set.

    void        set_coords( int coords );

    void        set( Vector vector[] );
    void        set_e1( double e1[] );
    void        set_e2( double e2[] );
    void        set_e3( double e3[] );

    void        set( int i, Vector vector );
    void        set_e1( int i, double e1  );
    void        set_e2( int i, double e2 );
    void        set_e3( int i, double e3 );

    // Return.

    int         get_size();
    int         get_coords();

    Vector      get( int i );
    double      get_e1( int i );
    double      get_e2( int i );
    double      get_e3( int i );
    double      get_mag( int i );

    // Access.

    int&        size();
    int&        coords();

    Vector&     vector( int i );
    double&     e1( int i );
    double&     e2( int i );
    double&     e3( int i );
    double&     mag( int i );

////////////////////////////////////////////////////////////////   M E T H O D S

private:

public:

    // Calculations.

    void        calc_mag();
    void        calc_mag( int i );
    void        scale( double factor );
    void        scale( int i, double factor );
    void        transform( int coords );

//////////////////////////////////////////////////////////////////   O U T P U T

private:

public:

    void        write( string file_name );
    void        write( ofstream& outfile );

////////////////////////////////////////////////////////////////////////////////
};
#endif
