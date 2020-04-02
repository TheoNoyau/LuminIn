#include "Company.h"

using namespace std ;

Company::Company(string name, string zipcode, string email) : _name(name), _zipcode(zipcode), _email(email)
{
    
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