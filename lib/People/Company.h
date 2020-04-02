#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <string>
#include <vector>

#include "JobSeeker.h"
#include "Company.h"
#include "Job.h"

class JobSeeker ;
class Employee ;
class Job ;

class Company
{
    public:    

    Company(std::string name, std::string zipcode, std::string email);
    void createProfile(std::vector<Company> &list) ;
    void updateProfile(std::string name, std::string zipcode, std::string email) ;
    void deleteProfile(std::vector<Company> &list) ;
    void createJob(std::string title, const std::vector<std::string> skills) ;
    void deleteJob(Job &j) ;
    std::vector<JobSeeker> searchForJobSeekers(std::vector<JobSeeker> &list, const std::vector<std::string> skills) ;
    std::vector<JobSeeker> searchForJobSeekers(std::vector<JobSeeker> &list, const std::vector<std::string> skills, std::string zipcode) ;

    private:

    int _id ;
    std::string _name;
    std::string _zipcode;
    std::string _email;
    std::vector<Job> _jobs ;
};

#endif
