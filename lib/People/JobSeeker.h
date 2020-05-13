#ifndef JOBSEEKER_H
#define JOBSEEKER_H

#include <iostream>
#include <string>
#include <vector>

class Company ;
class Job ;
class Employee ;

class JobSeeker
{
    public:

    // Class constructor
    // A JobSeeker needs and id as PK, a name, a firstname, an email, a zipcode, a vector of skills and a vector of old colleagues from old jobs
    JobSeeker(std::string name, std::string firstname, std::string email, std::string zipcode, std::vector<std::string> skills, std::vector<Employee*> &colleagues, std::string hashedPassword = "0000");

    // Accessors
    int getId() ;
    std::string getName() ;
    std::string getFirstname() ;
    std::string getEmail() ;
    std::string getZipcode() ;
    std::vector<std::string> getSkills() ;
    std::vector<Employee*> &getColleagues() ;
    std::string getHashedPassword() ;

    // Setter
    void setId(int id) ;
    void setId(std::vector<JobSeeker*> &list) ;
    void setZipcode(std::string zipcode);
    void setHashedPassword(std::string hashedPassword) ;

    // Static

    // Returns a reference of the object with the right id
    static int getIndex(const int id, std::vector<JobSeeker*> jobSeekers) ;

    // Creates a JobSeeker profile
    // Adds the JobSeeker created into the vector given as a parameter
    void createProfile(std::vector<JobSeeker*> &list, std::string password) ;

    // Adds new skills to the JobSeeker profile
    void addSkills(std::vector<std::string> skills) ;

    // Adds a colleague to the JobSeeker profile
    // Returns -1 if the Employee e is already in the JobSeeker's colleagues
    // Returns 1 otherwise
    int addColleague (Employee &e) ;

    // Updates the JobSeeker Status to Employee
    // The object is moved from one database table to another
    Employee* jobSeekerToEmployee (std::vector<Employee*> &employees, std::vector<JobSeeker*> &jobseekers, Company& company) ;

    // Deletes the JobSeeker profile in the list and in the database table
    void deleteProfile(std::vector<JobSeeker*> &list) ;

    // Looks for all the jobs according to a vector of skills (at least one skill in common)
    // Returns a vector of the Jobs corresponding 
    std::vector<Job*> searchForJobs(std::vector<Job*> &list, const std::vector<std::string> skills) ;

    // Looks for all the jobs according to a vector of skills (at least one skill in common) and a zipcode
    // Returns a vector of the Jobs corresponding
    std::vector<Job*> searchForJobs(std::vector<Job*> &list, const std::vector<std::string> skills, std::string zipcode) ;

    // Looks for old colleagues which are working in the company given as a parameter
    // Returns a vector of those colleagues
    std::vector<Employee*> searchForOldColleagues (Company &company) ;

    // Looks for old colleagues with their company looking for people with the skills of the JobSeeker.
    // Needs the jobs vector because needs to know what the companies are looking for.
    // Returns a vector of those colleagues
    std::vector<Employee*> searchForOldColleagues (std::vector<Job*> &jobs) ;

    // Operators overloading
    JobSeeker& operator= (const JobSeeker &js) ;

    private:

    int _id ;
    std::string _name;
    std::string _firstname ;
    std::string _email;
    std::string _zipcode;
    std::vector<std::string> _skills ;
    std::vector<Employee*> _oldColleagues ;
    std::string _hashedPassword ;
};

#endif
