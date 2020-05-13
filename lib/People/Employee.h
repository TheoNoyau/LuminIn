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
    Employee(std::string name, std::string firstname, std::string email, std::string zipcode, std::vector<std::string> skills, std::vector<Employee*> &list, Company &c, std::string hashedPassword = "0000");
    Employee(Company &c) ;
    Employee(const Employee &copy) ;

    // Accessors
    int getId() ;
    std::string getName() ;
    std::string getFirstname() ;
    std::string getEmail() ;
    std::string getZipcode() ;
    std::vector<std::string> getSkills() ;
    std::vector<Employee*> &getColleagues() ;
    Company &getCompany();
    std::string getHashedPassword() ;

    // Setter
    void setId(int id);
    void setId(std::vector<Employee*> &list) ;
    void setZipcode(std::string zipcode) ;
    void setCompany(Company &c) ;

    // Static

    // Returns a reference of the object with the right id
    static int getIndex(const int id, std::vector<Employee*> &employees) ;

    // Returns a vector of employees with the attribute given in the parameters
    static std::vector<Employee*> getEmployees(std::string name, std::vector<Employee*> &employees) ;

    // Creates Employee profile and adds it to the list and DB
    // Password is the password which will be needed to log in
    // Password is hashed before being put in the global vector
    void createProfile(std::vector<Employee*> &list, std::string password) ;

    // Adds a profile to the list of skills 
    void addSkills (std::vector<std::string> skills) ;

    // Adds a colleague to the old colleagues list
    // Returns -1 if the Employee e is already in the Employee's colleagues
    // Returns 1 otherwise
    int addColleague (Employee &e) ;

    // Deletes Employee profile from the global vector
    // Also removes its reference from the employees or job seekers he was colleague with
    void deleteProfile(std::vector<Employee*> &list, std::vector<JobSeeker*> &jobSeekers) ;

    // Transitions an Employee to a JobSeeker
    // Deletes profile from Employee list and adds it to JobSeekers list
    JobSeeker* employeeToJobSeeker (std::vector<Employee*> &employees, std::vector<JobSeeker*> &jobseekers) ;

    // Looks for all the jobs according to a vector of skills (at least one skill in common)
    // Returns a vector of the Jobs corresponding
    std::vector<Job*> searchForJobs(std::vector<Job*> &list, const std::vector<std::string> skills) ;

    // Looks for all the jobs according to a vector of skills (at least one skill in common) and a zipcode
    // Returns a vector of the Jobs corresponding
    std::vector<Job*> searchForJobs(std::vector<Job*> &list, const std::vector<std::string> skills, std::string zipcode) ;

    // Searches for an old colleague given a company
    // Returns a list of Employee
    std::vector<Employee*> searchForOldColleagues (Company &company) ;

    // Looks for old colleagues with their company looking for people with the skills of the Employee.
    // Needs the jobs vector because needs to know what the companies are looking for.
    // Returns a vector of those colleagues
    std::vector<Employee*> searchForOldColleagues (std::vector<Job*> &jobs) ;

    // Operators overloading
    Employee& operator= (const Employee &employee) ;

    private:

    int _id ;
    std::string _name;
    std::string _firstname ;
    std::string _email;
    std::string _zipcode;
    std::vector<std::string> _skills ;
    std::vector<Employee*> _oldColleagues ;
    Company *_company ;
    std::string _hashedPassword ;
};

#endif
