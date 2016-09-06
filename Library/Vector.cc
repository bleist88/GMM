#include "../Include/Vector.hh"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

//////////////////////////////////////////////////////   C O N S T R U C T O R S

Vector :: Vector()
{
    _coords     = 1;
    _e1         = 0;
    _e2         = 0;
    _e3         = 0;
    calc_mag();
}

Vector :: Vector( double e1, double e2, double e3 )
{
    _coords     = 1;
    _e1         = e1;
    _e2         = e2;
    _e3         = e3;
    calc_mag();
}

Vector :: Vector( int coords, double e1, double e2, double e3 )
{
    _coords     = coords;
    _e1         = e1;
    _e2         = e2;
    _e3         = e3;
    calc_mag();
}

Vector :: ~Vector(){}


////////////////////////////////////////////////////////////////   M E M B E R S

// Setting.

void        Vector :: set( Vector vector )
{
    _coords     = vector.get_coords();
    _e1         = vector.get_e1();
    _e2         = vector.get_e2();
    _e3         = vector.get_e3();
    _mag        = vector.get_mag();
}

void        Vector :: set( double e1, double e2, double e3 )
{
    _e1 = e1;  _e2 = e2;  _e3 = e3;  calc_mag();
}

void        Vector :: set( int coords, double e1, double e2, double e3 )
{
    transform( coords );  _e1 = e1;  _e2 = e2;  _e3 = e3;  calc_mag();
}

void        Vector :: set_coords( int coords )
{
    _coords = coords;
}

void        Vector :: set_e1( double e1 )
{
    _e1 = e1;
}

void        Vector :: set_e2( double e2 )
{
    _e2 = e2;
}

void        Vector :: set_e3( double e3 )
{
    _e3 = e3;
}

void        Vector :: set_x( double x )
{
    transform(1);  _e1 = x;  calc_mag();
}

void        Vector :: set_y( double y )
{
    transform(1);  _e2 = y;  calc_mag();
}

void        Vector :: set_z( double z )
{
    transform(1);  _e3 = z;  calc_mag();
}

void        Vector :: set_rho( double rho )
{
    transform(2);  _e1 = rho;  calc_mag();
}

void        Vector :: set_omega( double omega )
{
    transform(2);  _e2 = omega; calc_mag();
}

void        Vector :: set_zed( double zed )
{
    transform(2);  _e3 = zed;  calc_mag();
}

void        Vector :: set_r( double r )
{
    transform(3); _e1 = r;  calc_mag();
}

void        Vector :: set_theta( double theta )
{
    transform(3);  _e2 = theta;  calc_mag();
}

void        Vector :: set_phi( double phi )
{
    transform(3);  _e3 = phi;  calc_mag();
}

// Getting.

Vector      Vector :: get()
{
    Vector vector( _e1, _e2, _e3 );
    return vector;
}

int         Vector :: get_coords()
{
    return _coords;
}

double      Vector :: get_e1()
{
    return _e1;
}

double      Vector :: get_e2()
{
    return _e2;
}

double      Vector :: get_e3()
{
    return _e3;
}

double      Vector :: get_mag()
{
    return _mag;
}

// Accessing.

int&        Vector :: coords()
{
    return _coords;
}

double&     Vector :: e1()
{
    return _e1;
}

double&     Vector :: e2()
{
    return _e2;
}

double&     Vector :: e3()
{
    return _e3;
}

double&     Vector :: mag()
{
    return _mag;
}

////////////////////////////////////////////////////////////////   M E T H O D S

// Void Vector Operations.

void        Vector :: calc_mag()
{
    _mag = sqrt( _e1*_e1 + _e2*_e2 + _e3*_e3 );
}

void        Vector :: scale( double factor )
{
    set(
        _e1 * factor,
        _e2 * factor,
        _e3 * factor
        );
}

void        Vector :: add( Vector vector )
{
    set(
        _e1 + vector.get_e1(),
        _e2 + vector.get_e2(),
        _e3 + vector.get_e3()
        );
}

void        Vector :: subtract( Vector vector )
{
    set(
        _e1 - vector.get_e1(),
        _e2 - vector.get_e2(),
        _e3 - vector.get_e3()
    );
}

void        Vector :: cross( Vector vector )
{
    set(
        _e2 * vector.get_e3() - _e3 * vector.get_e2(),
        _e3 * vector.get_e1() - _e1 * vector.get_e3(),
        _e1 * vector.get_e2() - _e2 * vector.get_e1()
    );
}

void        Vector :: transform( int coords )
{
    // Variables used in transformations.

    double  x, y, z;
    double  rho, omega, zed;
    double  r, theta, phi;

    // Determine which transformation to make.

    switch( _coords ){

        case 1:                                         // from cartesian
            x   = _e1;
            y   = _e2;
            z   = _e3;

            switch( coords ){

                case 2:                                     // to cylindrical
                    _e1     = sqrt( x*x + y*y );
                    _e2     = atan( x / y );
                    _e3     = z;
                    _coords = coords;
                    calc_mag();
                    break;

                case 3:                                     // to spherical
                    _e1     = sqrt( x*x + y*y + z*z );
                    _e2     = atan( sqrt(x*x+y*y) / z );
                    _e3     = atan( y / x );
                    _coords = coords;
                    calc_mag();
                    break;
            };  break;

        case 2:                                         // from cylindrical
            x       = _e1 * cos(_e2);
            y       = _e1 * sin(_e2);
            z       = _e3;

            switch( coords ){

                case 1:                                     // to cartesian
                    _e1     = x;
                    _e2     = y;
                    _e3     = z;
                    _coords = coords;
                    calc_mag();
                    break;

                case 3:                                     // to spherical
                    _e1     = sqrt( x*x + y*y + z*z );
                    _e2     = atan( sqrt(x*x+y*y) / z );
                    _e3     = atan( y / x );
                    _coords = coords;
                    calc_mag();
                    break;
            };  break;

        case 3:                                         // from spherical
            x       = _e1 * sin(_e2) * cos(_e3);
            y       = _e1 * sin(_e2) * sin(_e3);
            z       = _e1 * cos(_e2);

            switch( coords ){

                case 1:                                     // to cartesian
                    _e1     = x;
                    _e2     = y;
                    _e3     = z;
                    _coords = coords;
                    calc_mag();
                    break;

                case 2:                                     // to cylindrical
                    _e1     = sqrt( x*x + y*y );
                    _e2     = atan( x / y );
                    _e3     = z;
                    _coords = coords;
                    calc_mag();
                    break;
            };  break;
        };
}

// Return Vector Operations.

Vector      Vector :: scaled( double factor )
{
    Vector  out_vector;
    out_vector.set(
        _e1 * factor,
        _e2 * factor,
        _e3 * factor
    );
    return  out_vector;
}

Vector      Vector :: added( Vector vector )
{
    Vector  out_vector;
    out_vector.set(
        _e1 + vector.get_e1(),
        _e2 + vector.get_e2(),
        _e3 + vector.get_e3()
    );
    return  out_vector;
}

Vector      Vector :: subtracted( Vector vector )
{
    Vector  out_vector;
    out_vector.set(
        _e1 - vector.get_e1(),
        _e2 - vector.get_e2(),
        _e3 - vector.get_e3()
    );
    return  out_vector;
}

double      Vector :: dotted( Vector vector )
{
    return  _e1 * vector.get_e1() + _e2 * vector.get_e2() + _e3 * vector.get_e3();
}

Vector      Vector :: crossed( Vector vector )
{
    Vector  out_vector;
    out_vector.set(
        _e2 * vector.get_e3() - _e3 * vector.get_e2(),
        _e3 * vector.get_e1() - _e1 * vector.get_e3(),
        _e1 * vector.get_e2() - _e2 * vector.get_e1()
        );
    return  out_vector;
}

//////////////////////////////////////////////////////////////////   O U T P U T

void        Vector :: display()
{
    cout << "< " << _e1 << ", " << _e2 << ", " << _e3 << " >" << endl;
}

void        Vector :: write_header( ofstream &out_file )
{
    string f1, f2, f3;

    switch( _coords ){
        case 1:
            f1 = "x       ";  f2 = "y       ";  f3 = "z       ";  break;
        case 2:
            f1 = "rho     ";  f2 = "omega   ";  f3 = "zed     ";  break;
        case 3:
            f1 = "r       ";  f2 = "theta   ";  f3 = "phi     ";  break;
        default:
            f1 = "e1      ";  f2 = "e2      ";  f3 = "e3      ";  break;
    };

    out_file << "#   " << f1.c_str() << "float64" << endl;
    out_file << "#   " << f2.c_str() << "float64" << endl;
    out_file << "#   " << f3.c_str() << "float64" << endl;
}

void        Vector :: write( ofstream &out_file )
{
    out_file << "    " << _e1 << "    " << _e2 << "    " << _e3 << endl;
}
