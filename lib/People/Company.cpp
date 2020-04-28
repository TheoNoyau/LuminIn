#include "Company.h"

#include "JobSeeker.h"
#include "Company.h"
#include "Job.h"

#include <vector>
#include <algorithm>

using namespace std ;

Company::Company(string name, string zipcode, string email) : _name(name), _zipcode(zipcode), _email(email)
{
    
}

Company::Company() : _name("undefined"), _zipcode("undefined"), _email("undefined")
{
   _id = -1 ; 
}

int Company::getIndex(const int id, vector<Company*> companies)
{
    int size = companies.size() ;
    
    for (int i = 0; i < size; i++) {
        if (companies[i]->getId() == id) return i ;
    }

    return -1; 
}

vector<Company*> Company::getCompanies(string name, vector<Company*> &companies)
{
    vector<Company*> res ;

    for (unsigned int i = 0; i < companies.size(); i++) {
        if (!companies[i]->getName().compare(name)) res.push_back(companies[i]) ;
    }

    return res ;
}

vector<Job*> Company::getJobs(vector<Job*> &jobs) {
    vector<Job*> res ;

    for (unsigned int i = 0; i < jobs.size(); i++) {
        if (jobs[i]->getCompany().getId() == _id) {
            res.push_back(jobs[i]) ;
        }
    }

    return res ;
}

vector<Job*> Company::getJobs(vector<Job*> &jobs, string title) {
    vector<Job*> res ;

    for (unsigned int i = 0; i < jobs.size(); i++) {
        if (jobs[i]->getCompany().getId() == _id && !jobs[i]->getTitle().compare(title)) {
            res.push_back(jobs[i]) ;
        }
    }

    return res ;
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

void Company::setId(vector<Company*> &list)
{
    _id = (int)list.size() + 1;
}

void Company::setId(int id)
{
    _id = id;
}

void Company::createProfile(vector<Company*> &list) 
{
    // Set a unique ID
    setId(list);

    // Add the profile to the vector
    list.push_back(this);
}

void Company::updateProfile(vector<Company*> &list, string name, string zipcode, string email) 
{
    _name = name;
    _zipcode = zipcode;
    _email = email;

    // list[getIndex(_id, list)] = this;
}

void Company::deleteProfile(vector<Company*> &list, vector<Job*> &jobs) 
{
    for (unsigned int i = 0; i < jobs.size(); i++) {
        if (jobs[i]->getCompany().getId() == _id) {
            deleteJob(jobs, *(jobs[i])) ;
        }
    }

    list.erase(list.begin() + getIndex(_id, list));  
    delete this;
}

void Company::createJob(vector<Job*> &list, string title, const vector<string> skills)
{
    // Create new job object and give it a unique id
    Job* newJob = new Job(title, skills, *this);
    newJob->setId(list);

    // Add it to list of Jobs
    list.push_back(newJob);

    // Add it to company's list of jobs
    _jobs.push_back(newJob);
}

void Company::deleteJob(vector<Job*> &list, Job &j) 
{
    // Delete from the global vector
    list.erase(list.begin() + Job::getIndex(j.getId(), list));
}

vector<JobSeeker*> Company::searchForJobSeekers(vector<JobSeeker*> &list, vector<string> skills)
{
    vector<JobSeeker*> js ;
    vector<string> jsSkills ;
    bool flag = false ;

    for (auto newJs : list) {
        flag = false ;

        // Checks wether there are skills in common between skills and newJs->getSkills
        for (unsigned int i = 0; i < newJs->getSkills().size(); i++) {
            flag = flag || (find(skills.begin(), skills.end(), newJs->getSkills()[i]) != skills.end()) ;
        }
        if (flag) js.push_back(newJs) ;
    }
     
    return js ;
}

vector<JobSeeker*> Company::searchForJobSeekers(vector<JobSeeker*> &list, vector<string> skills, string zipcode)
{
    vector<JobSeeker*> js ;
    vector<string> jsSkills ;
    bool flag = false ;

    for (auto newJs : list) {
        flag = false ;

        if (!newJs->getZipcode().compare(zipcode)) {
            // Checks wether there are skills in common between skills and newJs->getSkills
            for (unsigned int i = 0; i < newJs->getSkills().size(); i++) {
                flag = flag || (find(skills.begin(), skills.end(), newJs->getSkills()[i]) != skills.end()) ;
            }
            if (flag) js.push_back(newJs) ;
        }
    }
     
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