#ifndef VECTOR_HH
#define VECTOR_HH

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class Vector
{

//////////////////////////////////////////////////////   C O N S T R U C T O R S

public:

    Vector();
    Vector( double e1, double e2, double e3 );
    Vector( int coords, double e1, double e2, double e3 );
    virtual ~Vector();

////////////////////////////////////////////////////////////////   M E M B E R S

private:

    int         _coords;            // (1)cartesian, (2)cyindrical, (3)spherical
    double      _e1, _e2, _e3;      // coefficients of the unit vectors
    double      _mag;               // magnitude of the vector

public:

    // Setting.

    void        set( Vector vector );
    void        set( double e1, double e2, double e3 );
    void        set( int coords, double e1, double e2, double e3 );

    void        set_coords( int coords );

    void        set_e1( double e1 );
    void        set_e2( double e2 );
    void        set_e3( double e3 );

    void        set_x( double x );
    void        set_y( double y );
    void        set_z( double z );

    void        set_rho( double rho );
    void        set_omega( double omega );
    void        set_zed( double zed );

    void        set_r( double r );
    void        set_theta( double theta );
    void        set_phi( double phi );

    // Getting.

    Vector      get();

    int         get_coords();
    double      get_e1();
    double      get_e2();
    double      get_e3();
    double      get_mag();

    // Accessing.

    int&        coords();
    double&     e1();
    double&     e2();
    double&     e3();
    double&     mag();

////////////////////////////////////////////////////////////////   M E T H O D S

private:

public:

    // Void Vector Operations.

    void        calc_mag();
    void        scale( double factor );
    void        add( Vector vector );
    void        subtract( Vector vector );
    void        cross( Vector vector );
    void        transform( int coords );

    // Return Vector Operations.

    Vector      scaled( double factor );
    Vector      added( Vector vector );
    Vector      subtracted( Vector vector );
    double      dotted( Vector vector );
    Vector      crossed( Vector vector );

//////////////////////////////////////////////////////////////////   O U T P U T

private:

public:

    void        display();
    void        write_header( ofstream &out_file );
    void        write( ofstream &out_file );

////////////////////////////////////////////////////////////////////////////////
};
#endif
