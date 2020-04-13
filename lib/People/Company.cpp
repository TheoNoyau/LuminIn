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
        if (companies[i].getId() == id) return i ;
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

void Company::setId(vector<Company> &list)
{
    _id = (int)list.size() + 1;
}

void Company::setId(int id)
{
    _id = id;
}

void Company::createProfile(vector<Company> &list) 
{
    // Set an ID not used
    setId(list);

    // Add the profile to the vector
    list.push_back(*this);
}

void Company::updateProfile(vector<Company> &list, string name, string zipcode, string email) 
{
    _name = name;
    _zipcode = zipcode;
    _email = email;
    setId(_id);

    list.erase(list.begin() + getIndex(_id, list));
    list.push_back(*this);
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