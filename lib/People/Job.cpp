#include "Job.h"
#include "Company.h"

using namespace std ;

Job::Job(std::string title, std::vector<std::string> skills, Company &c) : _title(title), _skills(skills), _company(c)
{
    
}

int Job::getIndex(const int id, vector<Job*> jobs)
{
    int size = jobs.size() ;
    
    for (int i = 0; i < size; i++) {
        if (jobs[i]->getId() == id) return i ;
    }

    return -1; 
}

vector<Job*> Job::getJobs(string title, vector<Job*> &jobs)
{
    vector<Job*> res ;

    for (unsigned int i = 0; i < jobs.size(); i++) {
        if (!jobs[i]->getTitle().compare(title)) res.push_back(jobs[i]) ;
    }

    return res ;
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

void Job::setId(vector<Job*> &list)
{
    _id = (int)list.size() + 1; 
}

void Job::deleteJob(vector<Job*> &jobs) {
    // jobs.erase(jobs.begin() + getIndex(_id, jobs)); 
    // auto it = jobs.begin() + Job::getIndex(_id, jobs) ;
    // delete * it ;
    // jobs.erase(remove(it, end(jobs), *it)) ; 
    jobs[Job::getIndex(_id, jobs)] = jobs.back() ;
    jobs.pop_back() ;
}

Job& Job::operator= (const Job &job)
{
    _id = job._id ;
    _title = job._title ;
    _skills = job._skills ;
    _company = job._company ;

    return *this ;
}