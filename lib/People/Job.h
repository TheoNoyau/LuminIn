#ifndef JOB_H
#define JOB_H

#include <iostream>
#include <string>
#include <vector>

#include "Company.h"

class Job
{
    public:    

    Job(std::string title, std::vector<std::string> skills, const &Company c);

    private:

    int _id ;
    std::string _title;
    std::vector<std::string> skills ;
    Company _company ;
};

#endif
