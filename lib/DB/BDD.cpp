#include "BDD.h"

#include <string>
#include <ostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_set>

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
    db.clear() ;
    db.seekg(0);
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
        Company company(dataLine[1], dataLine[2], dataLine[3]) ;
        company.setId(companyId) ;
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

void createEntry (fstream &db, Company &c) 
{   
    db.clear();
    db.seekg(0);
    // Create new primary key not already existing
    unordered_set<int> pk;
    vector<string> dataLine;
    string row, data, temp;
    int companyId ;
    getline(db, temp) ;
    while (getline(db, row))
    {
        dataLine.clear();
        stringstream s(row) ;

        while (getline(s, data, ',')) {
            dataLine.push_back(data) ;
        }
        pk.insert(stoi(dataLine[0])) ;
    }
    companyId = 1;
    while (pk.count(companyId) == 1) {
        companyId += 1;
    }
    c.setId(companyId);
    db.clear();
    db << companyId << "," << c.getName() << "," << c.getZipcode() << "," << c.getEmail() << "\n";
}

void createEntry (fstream &db, JobSeeker &js) 
{
    db.clear();
    db.seekg(0);
    // Create new primary key not already existing
    unordered_set<int> pk;
    vector<string> dataLine;
    string row, data, temp;
    int jobseekerId ;
    getline(db, temp) ;
    while (getline(db, row))
    {
        dataLine.clear();
        stringstream s(row) ;

        while (getline(s, data, ',')) {
            dataLine.push_back(data) ;
        }
        pk.insert(stoi(dataLine[0])) ;
    }
    jobseekerId = 1;
    while (pk.count(jobseekerId) == 1) {
        jobseekerId += 1;
    }
    js.setId(jobseekerId);
    db.clear();
    // Enter JobSeeker info into csv file
    db << jobseekerId << "," << js.getName() << "," << js.getFirstname() << "," << js.getEmail() << "," << js.getZipcode() << ",";
    for (unsigned int i = 0; i < js.getSkills().size(); i++) {
        db << js.getSkills()[i];
        if (i == js.getSkills().size() - 1) db << ",";
        else db << ";";
    }
    for (unsigned int i = 0; i < js.getColleagues().size(); i++){
        db << js.getColleagues()[i].getId();
        if (i == js.getColleagues().size() - 1) db << ",";
        else db << ";";
    }
    db << "\n";
}

void createEntry (fstream &db, const Employee &e)
{
    // db << "\n";
    // db << e.getId() << "," << e.getName() << "," << e.getFirstname() << "," << e.getEmail() << "," << e.getZipcode() << ",";
    // for (unsigned int i = 0; i < e.getSkills().size(); i++) {
    //     db << e.getSkills()[i];
    //     if (i == e.getSkills().size() - 1) db << ",";
    //     else db << ";";
    // }
    // for (unsigned int i = 0; i < e.getColleagues().size(); i++){
    //     db << e.getColleagues()[i].getId();
    //     if (i == e.getColleagues().size() - 1) db << ",";
    //     else db << ";";
    // }
    // db << e.getCompany().getId();
}

void createEntry (fstream &db, const Job o) 
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
