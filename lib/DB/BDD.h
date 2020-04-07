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

// Read all the companies from the companies database table
// Return a vector of those Companies
std::vector<Company> getCompanies (std::fstream& db) ;

// Read all the JobSeekers from the jobseekers database table
// Return a vector of those JobSeekers
std::vector<JobSeeker> getJobSeekers (std::fstream& db, std::fstream& dbEmployees, std::fstream& dbCompanies) ;

// Read all the Jobs from the jobs database table
// Return a vector of those Jobs
std::vector<Job> getJobs () ;

// Read all the Employees from the employees database table
// Return a vector of those Employees
std::vector<Employee> getEmployees (std::fstream& db, std::fstream& dbCompanies) ;

// Retruns the company object corresponding to the id given as a parameter
Company getCompany(std::fstream& db, int const id) ;

// Create a line in the database table
// The database table will differ according to the object given
void createEntry (std::fstream &db, Company &c) ;
void createEntry (std::fstream &db, JobSeeker &js) ;
void createEntry (std::fstream &db, Employee &e) ;
void createEntry (std::fstream &db, Job &j) ;

// Update/modify a line in the database table 
// The database table will differ according to the object given
void updateEntry (std::fstream &db, Company &c) ;
void updateEntry (std::fstream &db, JobSeeker &js) ;
void updateEntry (std::fstream &db, Employee &e) ;
void updateEntry (std::fstream &db, Job &o) ;

// Delete a line in the database table
// The database table will differ according to the object given
void deleteEntry (const Company &c) ;
void deleteEntry (const JobSeeker &js) ;
void deleteEntry (const Employee &e) ;
void deleteEntry (const Job &o) ;

#endif
