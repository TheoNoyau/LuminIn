#ifndef CSV_H
#define CSV_H

#include <iostream>
#include <string>
#include <vector>
#include "../lib/People/Company.h"
#include "../lib/People/JobSeeker.h"
#include "../lib/People/Employee.h"

class JobSeeker ;
class Company ;
class Job ;
class Company ;

const std::string CompanyFile = "../test/data/companies.csv";
const std::string EmployeeFile = "../test/data/employees.csv";
const std::string JobSeekerFile = "../test/data/jobseekers.csv";
const std::string JobsFile = "../test/data/jobs.csv";

// Read all the companies from the companies database table
// Return a vector of those Companies
std::vector<Company> getCompanies () ;

// Read all the JobSeekers from the jobseekers database table
// Return a vector of those JobSeekers
std::vector<JobSeeker> getJobSeekers () ;

// Read all the Jobs from the jobs database table
// Return a vector of those Jobs
std::vector<Job> getJobs () ;

// Read all the Employees from the employees database table
// Return a vector of those Employees
std::vector<Employee> getEmployees () ;


// Create a line in the database table
// The database table will differ according to the object given
void createEntry (const Company &c) ;
void createEntry (const JobSeeker &js) ;
void createEntry (const Employee &e) ;
void createEntry (const Job o) ;

// Update/modify a line in the database table 
// The database table will differ according to the object given
void updateEntry (const Company &c) ;
void updateEntry (const JobSeeker &js) ;
void updateEntry (const Employee &e) ;
void updateEntry (const Job &o) ;

// Delete a line in the database table
// The database table will differ according to the object given
void deleteEntry (const Company &c) ;
void deleteEntry (const JobSeeker &js) ;
void deleteEntry (const Employee &e) ;
void deleteEntry (const Job &o) ;

#endif
