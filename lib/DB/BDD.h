#ifndef CSV_H
#define CSV_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class JobSeeker ;
class Company ;
class Job ;
class Employee ;

// Sets the path to DB files
void setPath(std::string path);

// Read all the companies from the companies database table
// Return a vector of those Companies
std::vector<Company> getCompanies() ;

// Read all the JobSeekers from the jobseekers database table
// Return a vector of those JobSeekers
std::vector<JobSeeker> getJobSeekers() ;

// Read all the Jobs from the jobs database table
// Return a vector of those Jobs
std::vector<Job> getJobs () ;

// Read all the Employees from the employees database table
// Return a vector of those Employees
std::vector<Employee> getEmployees () ;

// Retruns the company object corresponding to the id given as a parameter
Company getCompany(int const id) ;

// Create a line in the database table
// The database table will differ according to the object given
void createEntry (Company &c) ;
void createEntry (JobSeeker &js) ;
void createEntry (Employee &e) ;
void createEntry (Job &j) ;

// Update/modify a line in the database table 
// The database table will differ according to the object given
void updateEntry (std::vector<Company> &list) ;
void updateEntry (std::vector<JobSeeker> &list) ;
void updateEntry (std::vector<Employee> &list) ;
void updateEntry (std::vector<Job> &list) ;

// Delete a line in the database table
// The database table will differ according to the object given
void deleteEntry (Company &c) ;
void deleteEntry (JobSeeker &js) ;
void deleteEntry (Employee &e) ;
void deleteEntry (Job &o) ;

#endif
