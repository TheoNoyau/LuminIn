#include "Employee.h"

#include "JobSeeker.h"
#include "Job.h"
#include "Company.h"

using namespace std;

Employee::Employee(string name, string firstname, string email, string zipcode, vector<string> skills, vector<Employee> &list, Company &c) : _name(name), _firstname(firstname), _email(email), _zipcode(zipcode), _skills(skills), _oldColleagues(list), _company(c)
{

}

Employee::Employee(vector<string> skills, vector<Employee> &list, Company &c) : _name("undefined"), _firstname("undefine"), _email("undefined"), _zipcode("undefined"), _skills(skills), _oldColleagues(list), _company(c)
{
    _id = -1 ;
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

vector<Employee> Employee::getColleagues()
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

void Employee::createProfile(vector<Employee> &list)
{

}

void Employee::addSkill(string name)
{

}

void Employee::addOldColleague(const Employee &e)
{

}

void Employee::updateZipcode(string zipcode)
{

}

void Employee::deleteProfile(vector<Employee> &list)
{

}

void Employee::employeeToJobSeeker(vector<Employee> employees, vector<JobSeeker> jobseekers)
{

}

vector<Job> Employee::searchForJobs(vector<Job> &list, const vector<string> skills)
{
    vector<Job> jobs ;
    return jobs ;
}

vector<Job> Employee::searchForJobs(vector<Job> &list, const vector<string> skills, string zipcode)
{
    vector<Job> jobs ;
    return jobs ;
}

vector<Employee> Employee::searchForOldColleagues(vector<Employee> employees, const Company &company)
{
    vector<Employee> emp ;
    return emp ;
}

vector<Employee> Employee::searchForOldColleagues(vector<Employee> employees, vector<string> skills)
{
    vector<Employee> emp ;
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

    return *this;
}
