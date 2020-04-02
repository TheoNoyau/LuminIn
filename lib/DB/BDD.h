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

std::vector<Company> getCompanies (std::string fileName) ;
std::vector<JobSeeker> getJobSeekers (std::string fileName) ;
std::vector<Job> getJobs (std::string fileName) ;
std::vector<Employee> getEmployees (std::string fileName) ;

void createCompanyEntry (std::string fileName, const Company &c) ;
void createJobSeekerEntry (std::string fileName, const JobSeeker &js) ;
void createEmployeeEntry (std::string fileName, const Employee &e) ;
void createJobEntry (std::string fileName, const Job o) ;

void updateCompanyEntry (std::string fileName, const Company &c) ;
void updateJobSeekerEntry (std::string fileName, const JobSeeker &js) ;
void updateEmployeeEntry (std::string fileName, const Employee &e) ;
void updateJobEntry (std::string fileName, const Job &o) ;

void deleteCompanyEntry (std::string fileName, const Company &c) ;
void deleteJobSeekerEntry (std::string fileName, const JobSeeker &js) ;
void deleteEmployeeEntry (std::string fileName, const Employee &e) ;
void deleteJobEntry (std::string fileName, const Job &o) ;

#endif
