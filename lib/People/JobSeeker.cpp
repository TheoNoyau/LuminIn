#include "JobSeeker.h"

using namespace std;

JobSeeker::JobSeeker(string name, string firstname, string email, string zipcode, vector<string> skills, vector<Employee> colleagues) : _name(name), _firstname(firstname), _email(email), _zipcode(zipcode), _skills(skills), _oldColleagues(colleagues)
{

}

void JobSeeker::createProfile(vector<JobSeeker> &list)
{

}

void JobSeeker::addSkills(vector<string> skills)
{

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
