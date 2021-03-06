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
// CSV module: you don't have to put file name. Ex: "test/csv/"
// SQL module: put file name. Ex: "test/sql/database.db"
// SQL module: the file will automatically be created if doesn't exist but not the folder!
void setPath(std::string path);

// Initialize the sqlite DB
// Will create tables of all objects if they don't exist
void sqlInit() ;

// Reads all the companies from the companies database table
// Returns a vector of those Companies
std::vector<Company*> getCompanies() ;

// Reads all the JobSeekers from the jobseekers database table
// Returns a vector of those JobSeekers
std::vector<JobSeeker*> getJobSeekers() ;

// Reads all the Jobs from the jobs database table
// Returns a vector of those Jobs
std::vector<Job*> getJobs () ;

// Reads all the Employees from the employees database table
// Returns a vector of those Employees
std::vector<Employee*> getEmployees () ;

// Returns the company object corresponding to the id given as a parameter
Company* getCompany(int const id) ;

// Creates a line in the database table
// The database file/table will differ according to the object given
void createEntry (Company &c) ;
void createEntry (JobSeeker &js) ;
void createEntry (Employee &e) ;
void createEntry (Job &j) ;

// Rewrites whole content of vector passed as parameter to the correct file 
// The database file will differ according to the type of list given
void updateEntry (std::vector<Company*> &list) ;
void updateEntry (std::vector<JobSeeker*> &list) ;
void updateEntry (std::vector<Employee*> &list) ;
void updateEntry (std::vector<Job*> &list) ;

// Clear the vectors to avoid memory leaks
void clearVector (std::vector<Company*> &list) ;
void clearVector (std::vector<JobSeeker*> &list) ;
void clearVector (std::vector<Employee*> &list) ;
void clearVector (std::vector<Job*> &list) ;

#endif
