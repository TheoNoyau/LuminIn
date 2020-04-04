#include "BDD.h"

#include <string>
#include <ostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "People/Company.h"
#include "People/JobSeeker.h"
#include "People/Employee.h"
#include "People/Job.h"

using namespace std;

const std::string CompanyFile = "../test/data/companies.csv";
const std::string EmployeeFile = "../test/data/employees.csv";
const std::string JobSeekerFile = "../test/data/jobseekers.csv";
const std::string JobsFile = "../test/data/jobs.csv";

vector<Company> getCompanies(fstream& db)
{
    vector<Company> companies;

    vector<string> dataLine;
    string row, data, temp;
    int companyId ;

    // Ignore first line of csv file
    getline(db, temp) ;
    while (getline(db, row))
    {
        dataLine.clear();
        stringstream s(row) ;

        while (getline(s, data, ',')) {
            dataLine.push_back(data) ;
        }
        companyId = stoi(dataLine[0]) ;
        Company company(companyId, dataLine[1], dataLine[2], dataLine[3]) ;
        companies.push_back(company) ;
    }

    return companies;
}

vector<JobSeeker> getJobSeekers()
{
    vector<JobSeeker> js;
    return js;
}

vector<Job> getJobs()
{
    vector<Job> jobs;
    return jobs;
}

vector<Employee> getEmployees()
{
    vector<Employee> employees;
    return employees;
}

void createEntry(const Company &c)
{
}

void createEntry(const JobSeeker &js)
{
}

void createEntry(const Employee &e)
{
}

void createEntry(const Job o)
{
}

void updateEntry(const Company &c)
{
}

void updateEntry(const JobSeeker &js)
{
}

void updateEntry(const Employee &e)
{
}

void updateEntry(const Job &o)
{
}

void deleteEntry(const Company &c)
{
}

void deleteEntry(const JobSeeker &js)
{
}

void deleteEntry(const Employee &e)
{
}

void deleteEntry(const Job &o)
{
}
