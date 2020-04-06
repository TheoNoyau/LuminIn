#ifndef JOBSEEKER_H
#define JOBSEEKER_H

#include <iostream>
#include <string>
#include <vector>

#include "Employee.h"

class Company ;
class Job ;
class Employee ;

class JobSeeker
{
    public:

    // Class constructor
    // A JobSeeker needs and id as PK, a name, a firstname, an email, a zipcode, a vector of skills and a vector of old colleagues from old jobs
    JobSeeker(std::string name, std::string firstname, std::string email, std::string zipcode, std::vector<std::string> skills, std::vector<Employee> &colleagues);

    // Accessors
    int getId() ;
    std::string getName() ;
    std::string getFirstname() ;
    std::string getEmail() ;
    std::string getZipcode() ;
    std::vector<std::string> getSkills() ;
    std::vector<Employee> &getColleagues() ;

    // Setter
    void setId(int id) ;

    // Creates a JobSeeker profile
    // Adds the JobSeeker created into the vector given as a parameter
    // Also stores it in the database
    void createProfile(std::vector<JobSeeker> &list) ;

    // Adds new skills to the JobSeeker profile
    // Changes are made in the object itself and into the database
    void addSkills(std::vector<std::string> skills) ;

    // Adds a colleague to the JobSeeker profile
    // Changes are made in the object itself and into the database
    void addColleague (const Employee &e) ;

    // Updates the JobSeeker Status to Employee
    // The object is moved from one database table to another
    void jobSeekerToEmployee (std::vector<Employee> employees, std::vector<JobSeeker> jobseekers) ;

    // Deletes the JobSeeker profile in the list and in the database table
    void deleteProfile(std::vector<JobSeeker> &list) ;

    // Looks for all the jobs according to a vector of skills
    // Returns a vector of the Jobs corresponding 
    std::vector<Job> searchForJobs(std::vector<Job> &list, const std::vector<std::string> skills) ;

    // Looks for all the jobs according to a vector of skills and a zipcode
    // Returns a vector of the Jobs corresponding
    std::vector<Job> searchForJobs(std::vector<Job> &list, const std::vector<std::string> skills, std::string zipcode) ;

    // Looks for old colleagues which are working in the company given as a parameter
    // Returns a vector of those colleagues
    std::vector<Employee> searchForOldColleagues (std::vector<Employee> employees, const Company &company) ;

    // Looks for old colleagues which have the skills given as a vector in the parameters
    // Returns a vector of those colleagues
    std::vector<Employee> searchForOldColleagues (std::vector<Employee> employees, std::vector<std::string> skills) ;

    // Operators overloading
    JobSeeker& operator= (const JobSeeker &js) ;

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
