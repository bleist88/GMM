#include "../Include/Maths.hh"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

vector<double>  arange( double front, double back, double step )
{
    int                 size    = (int) ( (back-front) / step );
    vector<double>      arange( size );

    for( int i = 0; i < size; i++ ) arange[i] = front + i*step;

    return arange;
}

////////////////////////////////////////////////////////////////////////////////

void            normalize( vector<double>* array, double val )
{
    // Adjust the array so that the minimum is zero.

    double  array_min = array->at(0);

    for( int i = 0; i < array->size(); i++ ){

        if( array->at(i) < array_min ) array_min = array->at(i);

    };

    for( int i = 0; i < array->size(); i++ ) array->at(i) -= array_min;

    // Scale the array so that the maximum is now val.

    double  array_max = array->at(0);

    for( int i = 0; i < array->size(); i++ ){

        if( array->at(i) > array_max ) array_max = array->at(i);

    };

    for( int i = 0; i < array->size(); i++ ) array->at(i) /= array_max/val;
}

////////////////////////////////////////////////////////////////////////////////

double          between( double a, double b)
{
    double diff, randy;
    diff    = b - a;
    randy   = a + (double)rand() * diff / (double)RAND_MAX;
    return randy;
}

////////////////////////////////////////////////////////////////////////////////

double          integrate( vector<double> x, vector<double> y )
{
    double      sum = 0;

    for( int i = 0; i < x.size()-1; i++ ){

        sum    += .5 * ( y[i+1] + y[i] ) * ( x[i+1] - x[i] );

    };

    return sum;
}

////////////////////////////////////////////////////////////////////////////////

double          interpolate( vector<double> x, vector<double> y, double xx )
{
    int     i       = 0;
    bool    found   = false;
    double  slope;
    double  yy;

    if( xx  < x.front() ){ yy = y.front(); }

    else if( xx >= x.back()  ){ yy = y.back();  }

    else{

        while( !found ){

            if( x[i] <= xx ){

                slope   = ( y[i+1] - y[i] ) / ( x[i+1] - x[i] );
                yy      = y[i] + slope * ( xx - x[i] );

                found   = true;
                i      += 1;

            };
        };
    };

    return yy;
}

////////////////////////////////////////////////////////////////////////////////

vector<double>  interpolate( vector<double> x, vector<double> y, vector<double> xx )
{
    vector<double>      yy( xx.size() );
    double              slope;

    // Loop through intervals of the given x[] and interpolate for all xx[]
    // within the interval.

    for( int i = 0; i < x.size()-1; i++ ){
        for( int j = 0; j < xx.size(); j++ ){

            if( x[i] <= xx[j] ){
                if( xx[j] < x[i+2] ){

                    slope   = ( y[i+1] - y[i] ) / ( x[i+1] - x[i] );
                    yy[j]   = y[i] + slope * ( xx[j] - x[i] );

                };
            };
        };
    };

    // For any xx[] points outside the domain of x[], set equal to the closest
    // value y[] of x[].

    for( int i = 0; i < xx.size(); i++ ){

        if( xx[i] <= x.front()   ){ yy[i] = y.front(); };
        if( xx[i] >= x.back()    ){ yy[i] = y.back();  };

    };

    return yy;
}

////////////////////////////////////////////////////////////////////////////////

vector<double>  CDF( vector<double> x, vector<double> pdf )
{
    vector<double>  cdf( x.size(), 0 );

    double          sum = 0;

    for( int i = 1; i < pdf.size(); i++ ){

        sum    += .5 * ( pdf[i] + pdf[i-1] ) * ( x[i] - x[i-1] );
        cdf[i]  = sum;

    };

    normalize( &cdf, 1 );

    return cdf;
}

////////////////////////////////////////////////////////////////////////////////

vector<double>  CDF( vector<double> x, double value )
{
    vector<double>  cdf( x.size(), 0 );

    double          sum = 0;

    for( int i = 1; i < x.size(); i++ ) cdf[i] = i;

    normalize( &cdf, 1 );

    return cdf;
}

////////////////////////////////////////////////////////////////////////////////

double          from_cdf( vector<double> x, vector<double> cdf )
{
    // Create a random number between 0-1 and then find the closest
    // match to the CDF.

    int     place;
    double  diff    = 1;

    double  randy   = between( 0, 1 );

    for( int i = 0; i < cdf.size(); i++ ){

        if( abs( cdf[i] - randy ) < diff ){

            diff    = abs( cdf[i] - randy );
            place   = i;

        };
    };

    return  x[place];
}
