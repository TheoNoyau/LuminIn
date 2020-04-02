#ifndef JOBSEEKER_H
#define JOBSEEKER_H

#include <iostream>
#include <string>
#include <vector>

#include "Company.h"
#include "Employee.h"
#include "Job.h"

class JobSeeker
{
    public:

    JobSeeker(std::string name, std::string firstname, std::string email, std::string zipcode, std::vector<string> skills, std::vector<Employee> colleagues);
    void createProfile(std::vector<JobSeeker> &list) ;
    void addSkills(std::vector<string> skills) ;
    void addColleague (const &Employee e) ;
    void jobSeekerToEmployee (std::vector<Employee> employees, std::vector<JobSeeker> jobseekers) ;
    void deleteProfile(std::vector<JobSeeker> &list) ;
    std::vector<Job> searchForJobs(std::vector<Job> &list, const std::vector<string> skills, std::string zipcode = "") ;
    std::vector<Employee> searchForOldColleagues (std::vector<Employee> employees, const &Company company) ;
    std::vector<Employee> searchForOldColleagues (std::vector<Employee> employees, std::vector<string> skills) ;

    private:

    int _id ;
    std::string _name;
    std::string _firstname ;
    std::string _email;
    std::string _zipcode;
    std::vector<string> _skills ;
    std::vector<Employee> _oldColleagues ;
};

#endif
