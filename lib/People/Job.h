#ifndef JOB_H
#define JOB_H

#include <iostream>
#include <string>
#include <vector>

class Company ;

class Job
{
    public:    

    // Class constructeur
    // A job needs an id as PK, a title, a vector of skills and a linked Company
    Job(std::string title, std::vector<std::string> skills, Company &c);

    // Static

    // Returns a reference of the object with the right id
    static int getIndex(const int id, std::vector<Job*> jobs) ;

    // Returns a vector of jobs with the attribute given in the parameters
    static std::vector<Job*> getJobs(std::string title, std::vector<Job*> &jobs) ;

    // Accessors
    int getId () ;
    std::string getTitle () ;
    std::vector<std::string> getSkills () ;
    Company &getCompany () ;

    // Setter 
    void setId(int id);
    void setId(std::vector<Job*> &list);

    // Deletes job profile from the list
    void deleteJob(std::vector<Job*> jobs) ;

    // Operators overloading
    Job& operator= (const Job &job) ;

    private:

    int _id ;
    std::string _title;
    std::vector<std::string> _skills ;
    Company &_company ;
};

#endif
