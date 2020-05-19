#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>

// Returns whether the password hashedPassword matches the clear password given
bool checkPassword(std::string hashedPassword, std::string clearPassword) ;

#endif