#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
#include <vector>

class JobSeeker ;
class Company ;
class Job ;

class Employee
{
    public:    

    // Class constructor
    // An employee needs an id as PK, a name, a firstname, an email, a zipcode, a liste of skills, a list of colleagues
    Employee(const int id, std::string name, std::string firstname, std::string email, std::string zipcode, std::vector<std::string> skills, std::vector<Employee> &list);

    // Accessors
    int getId() ;
    std::string getName() ;
    std::string getFirstname() ;
    std::string getEmail() ;
    std::string getZipcode() ;
    std::vector<std::string> getSkills() ;
    std::vector<Employee> getColleagues() ;

    // Creates Employee profile and adds it to the list and DB
    void createProfile(std::vector<Employee> &list) ;

    // Adds a profile to the list of skills 
    void addSkill (std::string name) ;

    // Adds a colleague to the old colleagues list
    void addOldColleague (const Employee &e) ;

    // Updates the zipcode
    void updateZipcode (std::string zipcode) ;

    // Deletes Employee profile from the list and DB
    void deleteProfile(std::vector<Employee> &list) ;

    // Transitions an Employee to a JobSeeker
    // Deletes profile from Employee list and adds it to JobSeekers list
    void employeeToJobSeeker (std::vector<Employee> employees, std::vector<JobSeeker> jobseekers) ;

    // Searches for a job given a list of skills and a zipcode
    // Returns a list of Jobs
    std::vector<Job> searchForJobs(std::vector<Job> &list, const std::vector<std::string> skills, std::string zipcode = "") ;

    // Searches for an old colleague given a company
    // Returns a list of Employee
    std::vector<Employee> searchForOldColleagues (std::vector<Employee> employees, const Company &company) ;

    // Searches for an old colleague given a list of skills 
    // Returns a list of Employee
    std::vector<Employee> searchForOldColleagues (std::vector<Employee> employees, std::vector<std::string> skills) ;

    private:

    int _id ;
    std::string _name;
    std::string _firstname ;
    std::string _email;
    std::string _zipcode;
    std::vector<std::string> _skills ;
    std::vector<Employee> &_oldColleagues ;
};

#endif
