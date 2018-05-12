#ifndef MATHS_HH
#define MATHS_HH

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

vector<double>      arange( double front, double back, double step );

void                normalize( vector<double>* array, double val );

double              between( double a, double b );

double              integrate( vector<double> x, vector<double> y );

double              interpolate( vector<double> x, vector<double> y, double xx );

vector<double>      interpolate( vector<double> x, vector<double> y, vector<double> xx );

vector<double>      CDF( vector<double> x, vector<double> pdf );

vector<double>      CDF( vector<double> x, double value );

double              from_cdf( vector<double> x, vector<double> cdf );



#endif
