#ifndef JOB_H
#define JOB_H

#include <iostream>
#include <string>
#include <vector>

#include "Company.h"

class Company ;

class Job
{
    public:    

    Job(std::string title, std::vector<std::string> skills, Company &c);

    private:

    int _id ;
    std::string _title;
    std::vector<std::string> _skills ;
    Company &_company ;
};

#endif
