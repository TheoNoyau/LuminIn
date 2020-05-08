#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <string>
#include <vector>

class JobSeeker ;
class Job ;
class Employee ;

class Company
{
    public:
    // Class contructor
    // A Company needs a name, zipcode and email     
    Company(std::string name, std::string zipcode, std::string email);
    Company();

    // Accessors
    int getId () ;
    std::string getName () ;
    std::string getZipcode () ;
    std::string getEmail () ;

    // Returns a vector of the jobs offers from the company
    std::vector<Job*> getJobs(std::vector<Job*>& jobs);

    // Returns a vector of jobs of the company with the given title
    std::vector<Job*> getJobs(std::vector<Job*>& jobs, std::string title);

    // Setter
    void setId(std::vector<Company*> &list);
    void setId(int id);

    // Static

    // Returns a reference of the object with the right id
    static int getIndex(const int id, std::vector<Company*> companies) ;

    // Returns a vector of companies with the attribute given in the parameters
    static std::vector<Company*> getCompanies(std::string name, std::vector<Company*> &companies) ;

    // Creates Company profile and adds it in the list 
    void createProfile(std::vector<Company*> &list) ;

    // Updates profile given a name, zipcode and email
    void updateProfile(std::vector<Company*> &list, std::string name, std::string zipcode, std::string email) ;

    // Deletes Company profile from the list and deletes all the jobs offers from the company
    // Also switches all the employees to job seekers
    void deleteProfile(std::vector<Company*> &list, std::vector<Job*> &jobs, std::vector<Employee*> &employees, std::vector<JobSeeker*> &jobSeekers) ;

    // Creates a job given a title and a list of skills
    void createJob(std::vector<Job*> &list, std::string title, const std::vector<std::string> skills) ;

    // Deletes a job
    void deleteJob(std::vector<Job*> &list, Job *j) ;

    // Searches for relevant job seekers given a list of skills (at least one skill in common)
    // Returns a list of JobSeeker
    std::vector<JobSeeker*> searchForJobSeekers(std::vector<JobSeeker*> &list, std::vector<std::string> skills) ;

    // Searches for relevant job seekers given a list of skills (at least one skill in common) and a zipcode
    // Returns a list of JobSeeker
    std::vector<JobSeeker*> searchForJobSeekers(std::vector<JobSeeker*> &list, std::vector<std::string> skills, std::string zipcode) ;

    // Operators overloading
    Company& operator= (const Company &company) ;

    private:

    int _id ;
    std::string _name;
    std::string _zipcode;
    std::string _email;
    std::vector<Job*> _jobs ;
};

#endif
