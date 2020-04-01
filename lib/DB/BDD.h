#ifndef CSV_H
#define CSV_H

#include <iostream>
#include <string>
#include <vector>

std::vector<Company> getCompanies (std::string fileName) ;
std::vector<JobSeeker> getJobSeekers (std::string fileName) ;
std::vector<Occupation> getOccupations (std::string fileName) ;
std::vector<Employee> getEmployees (std::string fileName) ;

void createCompanyEntry (const &Company c) ;
void createJobSeekerEntry (const &JobSeeker js) ;
void createEmployeeEntry (const &Employee e) ;
void createOccupationEntry (const &Occupation o) ;

void deleteCompanyEntry (const &Company c) ;
void deleteJobSeekerEntry (const &JobSeeker js) ;
void deleteEmployeeEntry (const &Employee e) ;
void deleteOccupationEntry (const &Occupation o) ;

#endif
