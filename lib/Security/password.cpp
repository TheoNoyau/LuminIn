#include "password.h"
#include <string>
#include <sstream>

using namespace std;

bool checkPassword(string hashedPassword, string clearPassword) 
{
    hash<string> passwordHash ;
    size_t convertedHash ;
    stringstream ss(hashedPassword) ;
    
    // Converts hashedPassword in size_t
    ss >> convertedHash ;

    return passwordHash(clearPassword) == convertedHash ;
}