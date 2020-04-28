#ifndef JOURNAL_H
#define JOURNAL_H

#include <string>
#include <vector>

// Returns string of formatted current date and time
std::string getTimeAndDate();

// Writes to file 
void logger(std::string logpath, std::string function, std::vector<std::string> &args);

#endif