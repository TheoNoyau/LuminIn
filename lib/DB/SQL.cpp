#include "BDD.h"

#include <string>
#include <ostream>
#include <vector>
#include <sstream>
#include <sqlite3.h>

#include "People/Company.h"
#include "People/JobSeeker.h"
#include "People/Employee.h"
#include "People/Job.h"

using namespace std;

string dbPath = "";

void setPath(string path)
{
    dbPath = path;
}

std::vector<Company*> getCompanies() 
{
    vector<Company*> companies ;

    return companies ;
}

std::vector<JobSeeker*> getJobSeekers() 
{
    vector<JobSeeker*> jobSeekers ;

    return jobSeekers ;
}

std::vector<Job*> getJobs ()
{
    vector<Job*> jobs ;

    return jobs ;
}

std::vector<Employee*> getEmployees () 
{
    vector<Employee*> employees ;

    return employees ;
}

Company* getCompany(int const id)
{
    Company *company = new Company;

    return company;
}

void createEntry (Company &c)
{

}

void createEntry (JobSeeker &js) 
{

}

void createEntry (Employee &e) 
{

}

void createEntry (Job &j) 
{

}


void updateEntry (std::vector<Company*> &list) 
{

}

void updateEntry (std::vector<JobSeeker*> &list) 
{

}

void updateEntry (std::vector<Employee*> &list) 
{

}

void updateEntry (std::vector<Job*> &list) 
{

}

void clearVector (std::vector<Company*> &list) 
{

}

void clearVector (std::vector<JobSeeker*> &list) 
{

}

void clearVector (std::vector<Employee*> &list) 
{

}

void clearVector (std::vector<Job*> &list)
{

}
