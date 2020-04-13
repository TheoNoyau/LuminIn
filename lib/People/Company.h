#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <string>
#include <vector>

class JobSeeker ;
class Job ;

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

    // Setter
    void setId(std::vector<Company> &list);
    void setId(int id);

    // Static

    // Returns a reference of the object with the right id
    static int getIndex(const int id, std::vector<Company> companies) ;

    // Creates Company profile and adds it in the list and DB 
    void createProfile(std::vector<Company> &list) ;

    // Updates profile given a name, zipcode and email
    void updateProfile(std::vector<Company> &list, std::string name, std::string zipcode, std::string email) ;

    // Deletes Company profile from the list and DB
    void deleteProfile(std::vector<Company> &list) ;

    // Creates a job given a title and a list of skills
    void createJob(std::vector<Job> &list, std::string title, const std::vector<std::string> skills) ;

    // Deletes a job
    void deleteJob(std::vector<Job> &list, Job &j) ;

    // Searches for relevant job seekers given a list of skills
    // Returns a list of JobSeeker
    std::vector<JobSeeker> searchForJobSeekers(std::vector<JobSeeker> &list, std::vector<std::string> skills) ;

    // Searches for relevant job seekers given a list of skills and a zipcode
    // Returns a list of JobSeeker
    std::vector<JobSeeker> searchForJobSeekers(std::vector<JobSeeker> &list, const std::vector<std::string> skills, std::string zipcode) ;

    // Operators overloading
    Company& operator= (const Company &company) ;

    private:

    int _id ;
    std::string _name;
    std::string _zipcode;
    std::string _email;
    std::vector<Job> _jobs ;
};

#endif
