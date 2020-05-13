#include "Company.h"

#include "JobSeeker.h"
#include "Company.h"
#include "Job.h"
#include "Employee.h"

#include <vector>
#include <algorithm>
#include <sstream>

using namespace std ;

Company::Company(string name, string zipcode, string email, string hashedPassword) : _name(name), _zipcode(zipcode), _email(email), _hashedPassword(hashedPassword)
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

string Company::getHashedPassword() 
{
    return _hashedPassword ;
}

void Company::setId(vector<Company*> &list)
{
    _id = (int)list.size() + 1;
}

void Company::setId(int id)
{
    _id = id;
}

void Company::createProfile(vector<Company*> &list, string password) 
{
    hash<string> passwordHash ;
    stringstream ss ;

    // Set a unique ID
    setId(list);

    // Hash password and converting size_t into string
    ss << passwordHash(password) ;
    _hashedPassword = ss.str() ;

    // Add the profile to the vector
    list.push_back(this);
}

void Company::updateProfile(vector<Company*> &list, string name, string zipcode, string email) 
{
    _name = name;
    _zipcode = zipcode;
    _email = email;
}

void Company::deleteProfile(vector<Company*> &list, vector<Job*> &jobs, vector<Employee*> &employees, vector<JobSeeker*> &jobSeekers) 
{
     for (auto j : jobs) {
        if (j->getCompany().getId() == _id) j->deleteJob(jobs) ;
     }

    for (auto e : employees) {
        if (e->getCompany().getId() == _id) e->employeeToJobSeeker(employees, jobSeekers) ;
    }

    // Removing Company
    auto it = list.begin() + Company::getIndex(_id, list) ;
    delete * it ;
    list.erase(it) ;
    cout << "test" << endl ;
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

void Company::deleteJob(vector<Job*> &list, Job *j) 
{
    // Delete from the global vector
    auto it = list.begin() + Job::getIndex(j->getId(), list) ;
    delete * it ;
    list.erase(it) ;
}

vector<JobSeeker*> Company::searchForJobSeekers(vector<JobSeeker*> &list, vector<string> skills)
{
    vector<JobSeeker*> js ;
    vector<pair<int, JobSeeker*>> jsAndSkills ;

    bool found ;
    int size = 0 ;

    for (auto newJs : list) {
        size = 0 ;

        // Checks wether there are skills in common between skills and newJs->getSkills
        for (unsigned int i = 0; i < newJs->getSkills().size(); i++) {
            found = find(skills.begin(), skills.end(), newJs->getSkills()[i]) != skills.end() ;
            if (found) size++ ;
        }
        if (size > 0) jsAndSkills.push_back(make_pair(size, newJs)) ; 
    }

    // Sort the job seekers (ascending order) according to the size of their skills vector they have in common with skills
    sort(jsAndSkills.begin(), jsAndSkills.end()) ;
    
    // Get only jsAndSkills.second by descending order
    for (int i = jsAndSkills.size() - 1; i >= 0 ; i--) js.push_back(jsAndSkills[i].second);
     
    return js ;
}

vector<JobSeeker*> Company::searchForJobSeekers(vector<JobSeeker*> &list, vector<string> skills, string zipcode)
{
    vector<JobSeeker*> js ;
    vector<pair<int, JobSeeker*>> jsAndSkills ;

    bool found ;
    int size = 0 ;

    for (auto newJs : list) {
        size = 0 ;

        if (!newJs->getZipcode().compare(zipcode)) {
            // Checks wether there are skills in common between skills and newJs->getSkills
            for (unsigned int i = 0; i < newJs->getSkills().size(); i++) {
                found = find(skills.begin(), skills.end(), newJs->getSkills()[i]) != skills.end() ;
                if (found) size++ ;
            }
            if (size > 0) jsAndSkills.push_back(make_pair(size, newJs)) ; 
        }
    }

    // Sort the job seekers (ascending order) according to the size of their skills vector they have in common with skills
    sort(jsAndSkills.begin(), jsAndSkills.end()) ;
    
    // Get only jsAndSkills.second by descending order
    for (int i = jsAndSkills.size() - 1; i >= 0 ; i--) js.push_back(jsAndSkills[i].second);
     
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