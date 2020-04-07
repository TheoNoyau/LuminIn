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
    unsigned int companyId ;

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

        // Adding the company to the vector in a way that its ID corresponds to its index
        if (companyId >= companies.size()) companies.resize(companyId, company) ;
        else companies[companyId - 1] = company ;
    }

    return companies;
}

vector<JobSeeker> getJobSeekers(fstream& db, fstream& dbEmployees, fstream& dbCompanies)
{
    db.clear() ;
    db.seekg(0);

    vector<Employee> employees;
    vector<JobSeeker> jobSeekers;
    vector<string> skills ;

    // Will be added to this vector the references to the colleagues corresponding to the IDs of the csv line
    vector<Employee> colleagues ;

    vector<string> dataLine;
    string row, data, temp;
    unsigned int colleagueId, jobseekerId ;

    employees = getEmployees(dbEmployees, dbCompanies) ;

    // Ignore first line of csv file
    getline(db, temp) ;
    while (getline(db, row))
    {
        dataLine.clear();
        skills.clear();
        colleagues.clear();

        stringstream s ;
        s << row ;

        while (getline(s, data, ',')) {
            dataLine.push_back(data) ;
        }

        // Reading of the skills
        s.clear();
        s << dataLine[5] ;
        while (getline(s, data, ';')) {
            skills.push_back(data) ;
        }

        // Set colleagues
        s.clear();
        s << dataLine[6] ;
        while (getline(s, data, ';')) {
            colleagueId = stoi(data) ;
            colleagues.push_back(employees[colleagueId - 1]) ;
        }

        JobSeeker js(dataLine[1], dataLine[2], dataLine[3], dataLine[4], skills, colleagues) ;

        jobseekerId = stoi(dataLine[0]) ;
        js.setId(jobseekerId) ;

        if (jobseekerId >= jobSeekers.size()) jobSeekers.resize(jobseekerId, js) ;
        else jobSeekers[jobseekerId - 1] = js ;
    }

    return jobSeekers;
}

vector<Job> getJobs(fstream& db, fstream& dbCompanies)
{
    db.clear() ;
    db.seekg(0);
    vector<Company> companies;
    vector<Job> jobs ;
    vector<string> skills ;

    vector<string> dataLine;
    string row, data, temp;
    unsigned int companyId, jobId ;

    companies = getCompanies(dbCompanies) ;

    // Ignore first line of csv file
    getline(db, temp) ;
    while (getline(db, row))
    {
        dataLine.clear();
        skills.clear();
        
        stringstream s ;
        s << row ;

        while (getline(s, data, ',')) {
            dataLine.push_back(data) ;
        }

        // Reading of the skills
        s.clear();
        s << dataLine[2] ;
        while (getline(s, data, ';')) {
            skills.push_back(data) ;
        }

        companyId = stoi(dataLine[3]) ;
        Company company = companies[companyId - 1] ;

        Job job(dataLine[1], skills, company) ;
        jobId = stoi(dataLine[0]) ;
        job.setId(jobId) ;

        // Adding the job to the vector in a way that its ID corresponds to its index
        if (jobId >= jobs.size()) jobs.resize(jobId, job) ;
        else jobs[jobId - 1] = job ;
    }

    return jobs;
}

vector<Employee> getEmployees(fstream& db, fstream& dbCompanies)
{
    db.clear() ;
    db.seekg(0);

    vector<Employee> employees;
    vector<string> skills ;

    // Will be added to this vector the references to the colleagues corresponding to the IDs of the csv line
    vector<Employee> colleagues ;

    vector<string> dataLine;
    string row, data, temp;
    unsigned int employeeId, colleagueId, companyId ;

    // Ignore first line of csv file
    getline(db, temp) ;
    while (getline(db, row))
    {
        dataLine.clear();
        skills.clear();
        colleagues.clear();

        stringstream s ;
        s << row ;

        while (getline(s, data, ',')) {
            dataLine.push_back(data) ;
        }

        // Setting of the company
        companyId = stoi(dataLine[7]) ;
        Company company = getCompany(dbCompanies, companyId) ;

        // Reading of the skills
        s.clear();
        s << dataLine[5] ;
        while (getline(s, data, ';')) {
            skills.push_back(data) ;
        }

        // Reading of the colleagues IDs to add them to the colleague tab
        s.clear();
        s << dataLine[6] ;
        while (getline(s, data, ';')) {
            colleagueId = stoi(data) ;

            if (colleagueId >= employees.size()) {
                Employee e(company) ;
                e.setId(colleagueId) ;
                colleagues.push_back(e) ;
            } else {
                colleagues.push_back(employees[colleagueId - 1]) ;
            }

        }

        Employee emp(dataLine[1], dataLine[2], dataLine[3], dataLine[4], skills, colleagues, company) ;

        employeeId = stoi(dataLine[0]) ;
        emp.setId(employeeId) ;

        if (employeeId >= employees.size()) employees.resize(employeeId, emp) ;
        else employees[employeeId - 1] = emp ;
    }

    // Filling of all the colleagues that may not be initialized yet
    for (unsigned int i = 0; i < employees.size(); i++) {
        for (unsigned int j = 0; j < employees[i].getColleagues().size(); j++) {
            if (!employees[i].getColleagues()[j].getName().compare("undefined")) {
                Employee e(employees[employees[i].getColleagues()[j].getId() - 1]) ;
                employees[i].getColleagues()[j] = e ;
            }
        }
    }

    return employees;
}

Company getCompany(std::fstream& db, int const id)
{
    db.clear() ;
    db.seekg(0);

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
        if (companyId == id) {
            Company company(dataLine[1], dataLine[2], dataLine[3]) ;
            company.setId(companyId) ;
            return company ;
        }
    }

    Company company ;
    return company;
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
    int sizeSkills = js.getSkills().size();
    for (int i = 0; i < sizeSkills; i++) {
        db << js.getSkills()[i];
        if (i == sizeSkills - 1) db << ",";
        else db << ";";
    }
    int sizeColleagues = js.getColleagues().size();
    for (int i = 0; i < sizeColleagues; i++){
        db << js.getColleagues()[i].getId();
        if (i == sizeColleagues - 1) db << ",";
        else db << ";";
    }
    db << "\n";
}

void createEntry (fstream &db, Employee &e)
{
    db.clear();
    db.seekg(0);
    // Create new primary key not already existing
    unordered_set<int> pk;
    vector<string> dataLine;
    string row, data, temp;
    int employeeId ;
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
    employeeId = 1;
    while (pk.count(employeeId) == 1) {
        employeeId += 1;
    }
    e.setId(employeeId);
    
    db.clear();
    // Enter Employee info into csv file
    db << employeeId << "," << e.getName() << "," << e.getFirstname() << "," << e.getEmail() << "," << e.getZipcode() << ",";
    int sizeSkills = e.getSkills().size();
    for (int i = 0; i < sizeSkills; i++) {
        db << e.getSkills()[i];
        if (i == sizeSkills - 1) db << ",";
        else db << ";";
    }
    int sizeColleagues = e.getColleagues().size();
    for (int i = 0; i < sizeColleagues; i++){
        db << e.getColleagues()[i].getId();
        if (i == sizeColleagues - 1) db << ",";
        else db << ";";
    }
    db << e.getCompany().getId() << "\n";
}

void createEntry (fstream &db, Job &j) 
{
    db.clear();
    db.seekg(0);
    // Create new primary key not already existing
    unordered_set<int> pk;
    vector<string> dataLine;
    string row, data, temp;
    int jobId ;
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
    jobId = 1;
    while (pk.count(jobId) == 1) {
        jobId += 1;
    }
    j.setId(jobId);
    
    db.clear();
    // Enter Job info into csv
    db << jobId << "," << j.getTitle() << ",";
    int sizeSkills = j.getSkills().size();
    for (int i = 0; i < sizeSkills; i++){
        db << j.getSkills()[i];
        if (i == sizeSkills - 1) db << ",";
        else db << ";";
    }
    db << j.getCompany().getId() << "\n";
    
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
