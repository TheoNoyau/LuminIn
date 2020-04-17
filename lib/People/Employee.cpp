#include "Employee.h"

#include "JobSeeker.h"
#include "Job.h"
#include "Company.h"

using namespace std;

Employee::Employee(string name, string firstname, string email, string zipcode, vector<string> skills, vector<Employee*> &list, Company &c) : _name(name), _firstname(firstname), _email(email), _zipcode(zipcode), _skills(skills), _oldColleagues(list), _company(c)
{

}

Employee::Employee(Company &c) : _name("undefined"), _firstname("undefined"), _email("undefined"), _zipcode("undefined"), _company(c)
{
    _id = -1 ;
}

Employee::Employee(const Employee &copy) : _id(copy._id), _name(copy._name), _firstname(copy._firstname), _email(copy._email), _zipcode(copy._zipcode), _skills(copy._skills), _oldColleagues(copy._oldColleagues), _company(copy._company)
{

}

int Employee::getIndex(const int id, vector<Employee*> employees)
{
    int size = employees.size() ;
    
    for (int i = 0; i < size; i++) {
        if (employees[i]->getId() == id) return i ;
    }

    return -1; 
}

int Employee::getId()
{
    return _id;
}

string Employee::getName()
{
    return _name;
}

string Employee::getFirstname()
{
    return _firstname;
}

string Employee::getEmail()
{
    return _email;
}

string Employee::getZipcode()
{
    return _zipcode;
}

vector<string> Employee::getSkills()
{
    return _skills;
}

vector<Employee*> &Employee::getColleagues()
{
    return _oldColleagues;
}

Company &Employee::getCompany()
{
    return _company;
}

void Employee::setId(int id)
{
    _id = id;
}

void Employee::setId(vector<Employee*> &list)
{
    _id = (int)list.size() + 1 ;
}

void Employee::setZipcode(string zipcode)
{

}

void Employee::setCompany(Company &c)
{

}

void Employee::createProfile(vector<Employee*> &list)
{
    // Giving an id to the object
    setId(list) ;

    // Adding to the global vector of JobSeekers of the app
    list.push_back(this) ;
}

void Employee::addSkills(vector<string> skills)
{

}

void Employee::addColleague(const Employee &e)
{

}

void Employee::deleteProfile(vector<Employee*> &list)
{

}

JobSeeker* Employee::employeeToJobSeeker(vector<Employee*> employees, vector<JobSeeker*> jobseekers)
{
    return NULL ;
}

vector<Job*> Employee::searchForJobs(vector<Job*> &list, const vector<string> skills)
{
    vector<Job*> jobs ;
    return jobs ;
}

vector<Job*> Employee::searchForJobs(vector<Job*> &list, const vector<string> skills, string zipcode)
{
    vector<Job*> jobs ;
    return jobs ;
}

vector<Employee*> Employee::searchForOldColleagues(vector<Employee*> employees, const Company &company)
{
    vector<Employee*> emp ;
    return emp ;
}

vector<Employee*> Employee::searchForOldColleagues(vector<Employee*> employees, vector<Job*> jobs)
{
    vector<Employee*> emp ;
    return emp ;
}

Employee& Employee::operator= (const Employee &employee) 
{ 
    _id = employee._id ;
    _name = employee._name ;
    _firstname = employee._firstname ;
    _email = employee._email ;
    _zipcode = employee._zipcode ;
    _skills = employee._skills ;
    _oldColleagues = employee._oldColleagues ;
    _company = employee._company ;

    return *this ;
}
