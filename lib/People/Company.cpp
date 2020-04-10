#include "Company.h"

#include "JobSeeker.h"
#include "Company.h"
#include "Job.h"

#include <vector>

using namespace std ;

Company::Company(string name, string zipcode, string email) : _name(name), _zipcode(zipcode), _email(email)
{
    
}

Company::Company() : _name("undefined"), _zipcode("undefined"), _email("undefined")
{
   _id = -1 ; 
}

int Company::getIndex(const int id, vector<Company> companies)
{
    int size = companies.size() ;
    
    for (int i = 0; i < size; i++) {
        if (companies[i].getId() == i) return i ;
    }

    return -1; 
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

void Company::setId(int id)
{
    _id = id;
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

Company& Company::operator= (const Company &company) 
{
    _id = company._id ;
    _name = company._name ;
    _zipcode = company._zipcode ;
    _email = company._email ;

    return *this ;
}