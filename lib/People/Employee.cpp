#include "Employee.h"

using namespace std;

Employee::Employee(const int id, string name, string firstname, string email, string zipcode, vector<string> skills, vector<Employee> &list) : _id(id), _name(name), _firstname(firstname), _email(email), _zipcode(zipcode), _skills(skills), _oldColleagues(list)
{

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

void createProfile(vector<Employee> &list)
{

}

void addSkill(string name)
{

}

void addOldColleague(const Employee &e)
{

}

void updateZipcode(string zipcode)
{

}

void deleteProfile(vector<Employee> &list)
{

}

void employeeToJobSeeker(vector<Employee> employees, vector<JobSeeker> jobseekers)
{

}

std::vector<Job> searchForJobs(vector<Job> &list, const vector<string> skills, string zipcode = "")
{
    vector<Job> jobs ;
    return jobs ;
}

vector<Employee> searchForOldColleagues(vector<Employee> employees, const Company &company)
{
    vector<Employee> emp ;
    return emp ;
}

vector<Employee> searchForOldColleagues(vector<Employee> employees, vector<string> skills)
{
    vector<Employee> emp ;
    return emp ;
}
