#include "Company.h"

#include "JobSeeker.h"
#include "Employee.h"
#include "Job.h"

using namespace std ;

Company::Company(const int id, string name, string zipcode, string email) : _id(id), _name(name), _zipcode(zipcode), _email(email)
{
    
}

int Company::getId ()
{
    return _id ;
}

string Company::getName ()
{
    return _name ;
}

string Company::getZipcode ()
{
    return _zipcode ;
}

string Company::getEmail ()
{
    return _email ;
}

void Company::createProfile(vector<Company> &list) 
{

}

void Company::updateProfile(string name, string zipcode, string email) 
{

}

void Company::deleteProfile(vector<Company> &list) 
{
    
}

void Company::createJob(string title, const vector<string> skills)
{

}

void Company::deleteJob(Job &j) 
{

}

vector<JobSeeker> Company::searchForJobSeekers(vector<JobSeeker> &list, const vector<string> skills)
{
    vector<JobSeeker> js ;
    return js ;
}

vector<JobSeeker> Company::searchForJobSeekers(vector<JobSeeker> &list, const vector<string> skills, string zipcode)
{
    vector<JobSeeker> js ;
    return js ;
}