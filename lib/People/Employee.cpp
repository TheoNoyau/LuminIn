#include "Employee.h"

using namespace std;

Employee::Employee(string name, string firstname, string email, string zipcode, vector<string> skills, vector<Employee> &list) : _name(name), _firstname(firstname), _email(email), _zipcode(zipcode), _skills(skills), _oldColleagues(list)
{

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
