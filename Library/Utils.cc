#include "../Include/Utils.hh"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

int     count_lines( string file_name )
{
    ifstream    file;
    file.open( file_name.c_str() );
    string      line;

    int count = 0;

    while( getline(file,line) ){

        line    = uncomment(line);
        if( line.size() > 0 ){ count += 1; };
    };

    file.close();

    return count;
}

////////////////////////////////////////////////////////////////////////////////

string  uncomment( string line )
{
    return line.substr( 0, line.find_first_of("#") );
}

////////////////////////////////////////////////////////////////////////////////

string  get_var( string line )
{
    line    = uncomment( line );

    stringstream    ss(line);
    string          var, val;

    ss >> var >> val;

    return var;
}

////////////////////////////////////////////////////////////////////////////////

string  get_val( string line )
{
    line    = uncomment( line );

    stringstream    ss(line);
    string          var, val;

    ss >> var >> val;

    return val;
}

////////////////////////////////////////////////////////////////////////////////

string  get_config( string var, string file_name )
{

    ifstream    file( file_name.c_str() );
    string      line, line_var, line_val;

    while( getline(file,line) ){
        line    = uncomment(line);
        if( line.size() > 0 ){
            line_var = get_var(line);
            if( !line_var.compare(var) ){
                line_val    = get_val(line);
            };
        };
    };

    file.close();

    return line_val;
}

////////////////////////////////////////////////////////////////////////////////

string  get_dist( int i, string param, string file_name )
{
    ifstream        file( file_name.c_str() );
    string          line, out_param;
    string          input, output, x, y, z, vx, vy, vz;

    // Get variables from the specified line.

    int j = 0;
    while( getline(file,line) ){
        line    = uncomment(line);
        if( line.size() > 0 ){
            if( j == i ){
                stringstream ss(line);
                ss >> input >> output >> x >> y >> z >> vx >> vy >> vz;
            };
            j++;
        };
    };

    // Choose the specified variable and return it.

    if( !param.compare("input")     ){ out_param = input;   };
    if( !param.compare("output")    ){ out_param = output;  };
    if( !param.compare("x")         ){ out_param = x;       };
    if( !param.compare("y")         ){ out_param = y;       };
    if( !param.compare("z")         ){ out_param = z;       };
    if( !param.compare("vx")        ){ out_param = vx;      };
    if( !param.compare("vy")        ){ out_param = vy;      };
    if( !param.compare("vz")        ){ out_param = vz;      };

    file.close();

    return out_param;
}
