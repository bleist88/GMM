#ifndef UTILS_HH
#define UTILS_HH

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int             count_lines( string file_name );
string          uncomment( string line );
string          get_var( string line );
string          get_val( string line );

string          get_config( string var, string file_name );
string          get_dist( int i, string param, string file_name );


#endif
