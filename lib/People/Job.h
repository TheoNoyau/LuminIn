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

    // Class constructeur
    // A job needs an id as PK, a title, a vector of skills and a linked Company
    Job(const int id, std::string title, std::vector<std::string> skills, Company &c);

    // Accessors
    int getId () ;
    std::string getTitle () ;
    std::vector<std::string> getSkills () ;
    Company &getCompany () ;

    private:

    int _id ;
    std::string _title;
    std::vector<std::string> _skills ;
    Company &_company ;
};

#endif
