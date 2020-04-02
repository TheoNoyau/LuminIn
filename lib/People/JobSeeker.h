#ifndef JOBSEEKER_H
#define JOBSEEKER_H

#include <iostream>
#include <string>
#include <vector>

#include "Company.h"
#include "Employee.h"
#include "Job.h"

class Employee ;
class Company ;
class Job ;

class JobSeeker
{
    public:

    JobSeeker(std::string name, std::string firstname, std::string email, std::string zipcode, std::vector<std::string> skills, std::vector<Employee> colleagues);
    void createProfile(std::vector<JobSeeker> &list) ;
    void addSkills(std::vector<std::string> skills) ;
    void addColleague (const Employee &e) ;
    void jobSeekerToEmployee (std::vector<Employee> employees, std::vector<JobSeeker> jobseekers) ;
    void deleteProfile(std::vector<JobSeeker> &list) ;
    std::vector<Job> searchForJobs(std::vector<Job> &list, const std::vector<std::string> skills) ;
    std::vector<Job> searchForJobs(std::vector<Job> &list, const std::vector<std::string> skills, std::string zipcode) ;
    std::vector<Employee> searchForOldColleagues (std::vector<Employee> employees, const Company &company) ;
    std::vector<Employee> searchForOldColleagues (std::vector<Employee> employees, std::vector<std::string> skills) ;

    private:

    int _id ;
    std::string _name;
    std::string _firstname ;
    std::string _email;
    std::string _zipcode;
    std::vector<std::string> _skills ;
    std::vector<Employee> _oldColleagues ;
};

#endif
