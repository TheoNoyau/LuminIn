#include "Job.h"

using namespace std ;

Job::Job(std::string title, std::vector<std::string> skills, Company &c) : _title(title), _skills(skills), _company(c)
{
    
}

int Job::getIndex(const int id, vector<Job> jobs)
{
    int size = jobs.size() ;
    
    for (int i = 0; i < size; i++) {
        if (jobs[i].getId() == id) return i ;
    }

    return -1; 
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

void Job::setId(int id)
{
    _id = id;
}

Job& Job::operator= (const Job &job)
{
    _id = job._id ;
    _title = job._title ;
    _skills = job._skills ;
    _company = job._company ;

    return *this ;
}