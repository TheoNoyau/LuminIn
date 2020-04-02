#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
#include <vector>

#include "JobSeeker.h"
#include "Company.h"
#include "Job.h"

class JobSeeker ;
class Company ;
class Job ;

class Employee
{
    public:    

    Employee(std::string name, std::string firstname, std::string email, std::string zipcode, std::vector<std::string> skills, std::vector<Employee> &list);
    void createProfile(std::vector<Employee> &list) ;
    void addSkill (std::string name) ;
    void addOldColleague (const Employee &e) ;
    void updateZipcode (std::string zipcode) ;
    void deleteProfile(std::vector<Employee> &list) ;
    void employeeToJobSeeker (std::vector<Employee> employees, std::vector<JobSeeker> jobseekers) ;
    std::vector<Job> searchForJobs(std::vector<Job> &list, const std::vector<std::string> skills, std::string zipcode = "") ;
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
