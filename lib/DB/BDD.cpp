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

string dbPath = "";

void setPath(string path)
{
    dbPath = path;
}

vector<Company> getCompanies()
{
    fstream db;
    db.open(dbPath + "/companies.csv", ios::in) ;
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

        companies.push_back(company) ;
    }
    db.close();
    return companies;
}

vector<JobSeeker> getJobSeekers()
{
    fstream db, dbEmployees, dbCompanies;
    db.open(dbPath + "/jobseekers.csv", ios::in);
    dbEmployees.open(dbPath + "/employees.csv", ios::in);
    dbCompanies.open(dbPath + "/companies.csv", ios::in);

    vector<Employee> employees;
    vector<JobSeeker> jobSeekers;
    vector<string> skills ;

    // Will be added to this vector the references to the colleagues corresponding to the IDs of the csv line
    vector<Employee> colleagues ;

    vector<string> dataLine;
    string row, data, temp;
    unsigned int colleagueId, jobseekerId ;

    employees = getEmployees() ;

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

        jobSeekers.push_back(js) ;
    }

    db.close();
    dbEmployees.close();
    dbCompanies.close();
    return jobSeekers;
}

vector<Job> getJobs()
{
    fstream db, dbCompanies;
    db.open(dbPath + "/jobs.csv", ios::in);
    dbCompanies.open(dbPath + "/companies.csv", ios::in);

    vector<Company> companies;
    vector<Job> jobs ;
    vector<string> skills ;

    vector<string> dataLine;
    string row, data, temp;
    unsigned int companyId, jobId ;

    companies = getCompanies() ;

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

        jobs.push_back(job) ;
    }
    db.close();
    dbCompanies.close();
    return jobs;
}

vector<Employee> getEmployees()
{
    fstream db, dbCompanies;
    db.open(dbPath + "/employees.csv", ios::in);
    dbCompanies.open(dbPath + "/companies.csv", ios::in);    

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
        Company company = getCompany(companyId) ;

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

        employees.push_back(emp) ;
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

    db.close();
    dbCompanies.close();
    return employees;
}

Company getCompany(int const id)
{
    fstream db;
    db.open(dbPath + "/companies.csv", ios::in);

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
            db.close();
            return company ;
        }
    }

    db.close();
    Company company ;
    return company;
}

void createEntry (Company &c) 
{   
    fstream db;
    db.open(dbPath + "/companies.csv", ios::in | ios::app);

    // Enter Company info
    db << c.getId() << "," << c.getName() << "," << c.getZipcode() << "," << c.getEmail() << ",\n";

    db.close();
}

void createEntry (JobSeeker &js) 
{
    fstream db;
    db.open(dbPath + "/jobseekers.csv", ios::in | ios::app);

    // Enter JobSeeker info into csv file
    db << js.getId() << "," << js.getName() << "," << js.getFirstname() << "," << js.getEmail() << "," << js.getZipcode() << ",";
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
    db << ",\n";

    db.close();
}

void createEntry (Employee &e)
{
    fstream db;
    db.open(dbPath + "/employees.csv", ios::in | ios::app);

    // Enter Employee info into csv file
    db << e.getId() << "," << e.getName() << "," << e.getFirstname() << "," << e.getEmail() << "," << e.getZipcode() << ",";
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
    db << e.getCompany().getId() << ",\n";

    db.close();
}

void createEntry (Job &j) 
{
    fstream db;
    db.open(dbPath + "/jobs.csv", ios::in | ios::app);

    // Enter Job info into csv
    db << j.getId() << "," << j.getTitle() << ",";
    int sizeSkills = j.getSkills().size();
    for (int i = 0; i < sizeSkills; i++){
        db << j.getSkills()[i];
        if (i == sizeSkills - 1) db << ",";
        else db << ";";
    }
    db << j.getCompany().getId() << ",\n";
    
    db.close();
}

void updateEntry(vector<Company> &list)
{
    fstream db;
    db.open(dbPath + "/companies.csv", ios::out);
    db << "id,nom,code postal,mail\n";
    db.close();
 
    int size = list.size();
    for (int i = 0; i < size; i++){
        // Enter new Company info
        Company c = list[i];
        createEntry(c);
    }
}

void updateEntry(vector<JobSeeker> &list)
{
    fstream db;
    db.open(dbPath + "/jobseekers.csv", ios::out);
    db << "id,nom,prenom,mail,code postal,competences,collegues\n";
    db.close();

    int size = list.size();
    for (int i = 0; i < size; i++){
        JobSeeker js = list[i];
        createEntry(js);
    }
}

void updateEntry(vector<Employee> &list)
{
    fstream db;
    db.open(dbPath + "/employees.csv", ios::out);
    db << "id,nom,prenom,mail,code postal,competences,collegues,entreprise\n";
    db.close();

    int size = list.size();
    for (int i = 0; i < size; i++){
        Employee e = list[i];
        createEntry(e);
    }
}

void updateEntry(vector<Job> &list)
{
    fstream db;
    db.open(dbPath + "/jobs.csv", ios::out);
    db << "id,titre,competences,entreprise\n";
    db.close();

    int size = list.size();
    for (int i = 0; i < size; i++){
        Job j = list[i];
        createEntry(j);
    }
}