#include "Job.h"

#include "Company.h"

using namespace std ;

Job::Job(const int id, std::string title, std::vector<std::string> skills, Company &c) : _id(id), _title(title), _skills(skills), _company(c)
{
    
}

int Job::getId ()
{
    return _id ;
}

string Job::getTitle () 
{
    return _title ;
}

vector<std::string> Job::getSkills () 
{
    return _skills ;
}

Company &Job::getCompany () 
{
    return _company ;
}