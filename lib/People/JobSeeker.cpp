#include "JobSeeker.h"

#include "Company.h"
#include "Employee.h"
#include "Job.h"

#include "DB/BDD.h"

using namespace std;

JobSeeker::JobSeeker(string name, string firstname, string email, string zipcode, vector<string> skills, vector<Employee> &colleagues) : _name(name), _firstname(firstname), _email(email), _zipcode(zipcode), _skills(skills), _oldColleagues(colleagues)
{

}

int JobSeeker::getId() 
{
    return _id ;
}

string JobSeeker::getName()
{
    return _name;
}

string JobSeeker::getFirstname()
{
    return _firstname;
}

string JobSeeker::getEmail()
{
    return _email;
}

string JobSeeker::getZipcode()
{
    return _zipcode;
}

vector<string> JobSeeker::getSkills()
{
    return _skills;
}

vector<Employee> &JobSeeker::getColleagues()
{
    return _oldColleagues;
}

void JobSeeker::setId(int id)
{
    _id = id;
}

void JobSeeker::createProfile(vector<JobSeeker> &list)
{
    // Adding to the database
    createEntry(*this) ;

    // Adding to the global vector of JobSeekers of the app
    if ((unsigned int)_id >= list.size()) list.resize(_id, *this) ;
    else list[_id - 1] = *this ;
}

void JobSeeker::addSkills(vector<string> skills)
{
    unsigned int i ;

    for (i = 0; i < skills.size(); i++) {
        _skills.push_back(skills[i]) ;
    }

    // Update in the DB
    updateEntry(*this) ;
}

void JobSeeker::addColleague(const Employee &e)
{

}

void JobSeeker::jobSeekerToEmployee(vector<Employee> employees, vector<JobSeeker> jobseekers)
{

}

void JobSeeker::deleteProfile(vector<JobSeeker> &list)
{

}

vector<Job> JobSeeker::searchForJobs(vector<Job> &list, const vector<string> skills)
{
    vector<Job> jobs ;
    return jobs ;
}

vector<Job> JobSeeker::searchForJobs(vector<Job> &list, const vector<string> skills, string zipcode)
{
    vector<Job> jobs ;
    return jobs ;
}

vector<Employee> JobSeeker::searchForOldColleagues(vector<Employee> employees, const Company &company)
{
    vector<Employee> emp ;
    return emp ;
}

vector<Employee> JobSeeker::searchForOldColleagues(vector<Employee> employees, vector<string> skills)
{
    vector<Employee> emp ;
    return emp ;
}

JobSeeker& JobSeeker::operator= (const JobSeeker &js) 
{
    _id = js._id ;
    _name = js._name ;
    _firstname = js._firstname ;
    _email = js._email ;
    _zipcode = js._zipcode ;
    _skills = js._skills ;
    _oldColleagues = js._oldColleagues ;

    return *this ;
}