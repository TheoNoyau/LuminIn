#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>

// Returns whether the password given in parameters matches the hashed password stored in the DB
bool checkPassword(std::string hash1, std::string hash2) ;

#endif