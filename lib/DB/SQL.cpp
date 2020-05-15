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

void sqlInit()
{
    sqlite3* DB ;
    string sql ;
    sqlite3_open(dbPath.c_str(), &DB) ;

    // Company table
    sql = "CREATE TABLE IF NOT EXISTS COMPANY("
                 "ID INT PRIMARY KEY NOT NULL,"
                 "NAME TEXT NOT NULL,"
                 "CP CHAR(5) NOT NULL,"
                 "MAIL CHAR(50) NOT NULL,"
                 "PASSWORD TEXT);" ;

    sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL) ;

    // Employee table
    sql = "CREATE TABLE IF NOT EXISTS EMPLOYEE("
                 "ID INT PRIMARY KEY NOT NULL,"
                 "NAME TEXT NOT NULL,"
                 "FIRSTNAME TEXT NOT NULL,"
                 "MAIL CHAR(50) NOT NULL,"
                 "CP CHAR(5) NOT NULL,"
                 "SKILLS TEXT,"
                 "COLLEAGUES TEXT,"
                 "COMPANY_ID INT NOT NULL,"
                 "PASSWORD TEXT,"
                 "CONSTRAINT FK_COMPANY FOREIGN KEY (COMPANY_ID) REFERENCES COMPANY(ID));" ;

    sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL) ;

    // Job table
    sql = "CREATE TABLE IF NOT EXISTS JOB("
                 "ID INT PRIMARY KEY NOT NULL,"
                 "TITLE TEXT NOT NULL,"
                 "SKILLS TEXT NOT NULL,"
                 "COMPANY_ID INT NOT NULL,"
                 "CONSTRAINT FK_COMPANY FOREIGN KEY (COMPANY_ID) REFERENCES COMPANY(ID));" ;

    sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL) ;

    // JobSeeker table
    sql = "CREATE TABLE IF NOT EXISTS JOBSEEKER("
                 "ID INT PRIMARY KEY NOT NULL,"
                 "NAME TEXT NOT NULL,"
                 "FIRSTNAME TEXT NOT NULL,"
                 "MAIL CHAR(50) NOT NULL,"
                 "CP CHAR(5) NOT NULL,"
                 "SKILLS TEXT,"
                 "COLLEAGUES TEXTL,"
                 "PASSWORD TEXT);" ;

    sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL) ;

    sqlite3_close(DB) ;
}

std::vector<Company*> getCompanies() 
{
    sqlite3* DB ;
    sqlite3_stmt *stmt ;
    vector<Company*> companies ;
    string sql ;
    vector<string> dataLine ;

    sqlite3_open(dbPath.c_str(), &DB) ;
    
    sql = "SELECT * FROM COMPANY ;" ;
    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL) ;
    sqlite3_step(stmt) ;

    // Getting every row of request result
    while (sqlite3_column_text(stmt, 0)) {
        dataLine.clear() ;

        // Getting every column of row
        for (int i = 0; i < 5; i++) {
            dataLine.push_back(string((char*)sqlite3_column_text(stmt, i))) ;
        }

        Company *company = new Company(dataLine[1], dataLine[2], dataLine[3], dataLine[4]) ;
        company->setId(stoi(dataLine[0])) ;
        companies.push_back(company) ;

        sqlite3_step(stmt) ;
    }

    sqlite3_finalize(stmt) ;
    sqlite3_close(DB) ; 

    return companies ;
}

std::vector<JobSeeker*> getJobSeekers() 
{
    sqlite3* DB ;
    sqlite3_stmt *stmt ;

    vector<JobSeeker*> jobSeekers ;
    vector<Employee*> employees ;
    vector<Employee*> colleagues ;
    vector<string> skills ;

    string sql, data ;
    vector<string> dataLine ;
    stringstream s ;
    unsigned int colleagueId, jobseekerId ;
    
    employees = getEmployees() ;

    sqlite3_open(dbPath.c_str(), &DB) ;
    
    sql = "SELECT * FROM JOBSEEKER ;" ;
    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL) ;
    sqlite3_step(stmt) ;

    // Getting every row of request result
    while (sqlite3_column_text(stmt, 0)) {
        dataLine.clear();
        skills.clear();
        colleagues.clear();

        // Getting every column of row
        for (int i = 0; i < 8; i++) {
            dataLine.push_back(string((char*)sqlite3_column_text(stmt, i))) ;
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
            colleagues.push_back(employees[Employee::getIndex(colleagueId, employees)]) ;
        }

        JobSeeker* js = new JobSeeker(dataLine[1], dataLine[2], dataLine[3], dataLine[4], skills, colleagues, dataLine[7]) ;

        jobseekerId = stoi(dataLine[0]) ;
        js->setId(jobseekerId) ;

        jobSeekers.push_back(js) ;

        sqlite3_step(stmt) ;
    }

    sqlite3_finalize(stmt) ;
    sqlite3_close(DB) ; 

    return jobSeekers ;
}

std::vector<Job*> getJobs ()
{
    vector<Job*> jobs ;

    return jobs ;
}

std::vector<Employee*> getEmployees () 
{
    sqlite3* DB ;
    sqlite3_stmt *stmt ;

    vector<Employee*> employees ;
    vector<Employee*> colleagues ;
    vector<string> skills ;

    string sql, data ;
    vector<string> dataLine ;
    stringstream s ;
    unsigned int colleagueId, companyId, employeeId ;
    int colleagueIndex ;

    sqlite3_open(dbPath.c_str(), &DB) ;
    
    sql = "SELECT * FROM EMPLOYEE ;" ;
    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL) ;
    sqlite3_step(stmt) ;

    // Getting every row of request result
    while (sqlite3_column_text(stmt, 0)) {
        dataLine.clear();
        skills.clear();
        colleagues.clear();

        // Getting every column of row
        for (int i = 0; i < 9; i++) {
            dataLine.push_back(string((char*)sqlite3_column_text(stmt, i))) ;
        }

        // Setting of the company
        companyId = stoi(dataLine[7]) ;
        Company *company = getCompany(companyId) ;

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

            colleagueIndex = Employee::getIndex(colleagueId, employees) ;
            if (colleagueIndex == -1) {
                Employee *e = new Employee(*company) ;
                e->setId(colleagueId) ;
                colleagues.push_back(e) ;
            } else {
                colleagues.push_back(employees[colleagueIndex]) ;
            }

        }

        Employee *emp = new Employee(dataLine[1], dataLine[2], dataLine[3], dataLine[4], skills, colleagues, *company, dataLine[8]) ;

        employeeId = stoi(dataLine[0]) ;
        emp->setId(employeeId) ;

        employees.push_back(emp) ;

        sqlite3_step(stmt) ;
    }

    sqlite3_finalize(stmt) ;
    sqlite3_close(DB) ; 

    // Filling of all the colleagues that may not be initialized yet
    for (unsigned int i = 0; i < employees.size(); i++) {
        for (unsigned int j = 0; j < employees[i]->getColleagues().size(); j++) {
            if (!employees[i]->getColleagues()[j]->getName().compare("undefined")) {
                employees[i]->getColleagues()[j] = employees[Employee::getIndex(employees[i]->getColleagues()[j]->getId(), employees)] ;
            }
        }
    }

    return employees ;
}

Company* getCompany(int const id)
{
    Company *company ;
    sqlite3* DB ;
    sqlite3_stmt *stmt ;
    string sql ;
    vector<string> dataLine ;

    sqlite3_open(dbPath.c_str(), &DB) ;
    
    sql = "SELECT * FROM COMPANY WHERE ID=" + to_string(id) + ";" ;
    sqlite3_prepare(DB, sql.c_str(), -1, &stmt, NULL) ;
    sqlite3_step(stmt) ;

    if (sqlite3_column_text(stmt, 0)) {
        for (int i = 0; i < 5; i++) {
            dataLine.push_back(string((char*)sqlite3_column_text(stmt, i))) ;
        }

        company = new Company(dataLine[1], dataLine[2], dataLine[3], dataLine[4]) ;
        company->setId(stoi(dataLine[0])) ;
    } else company = new Company ;


    sqlite3_finalize(stmt) ;
    sqlite3_close(DB) ; 

    return company;
}

void createEntry (Company &c)
{
    sqlite3 *DB ;
    string sql = "INSERT INTO COMPANY VALUES(" + to_string(c.getId()) + ",'" + c.getName() + "','" + c.getZipcode() + "','" + c.getEmail() + "','" + c.getHashedPassword() + "');" ;

    sqlite3_open(dbPath.c_str(), &DB) ;

    sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL) ;

    sqlite3_close(DB) ;
}

void createEntry (JobSeeker &js) 
{
    sqlite3 *DB ;
    string sql = "INSERT INTO JOBSEEKER VALUES(" + to_string(e.getId()) + ",'" + e.getName() + "','" + e.getFirstname() + "','" + e.getEmail() + "','" + e.getZipcode() + "','" ;

    int sizeSkills = e.getSkills().size();
    for (int i = 0; i < sizeSkills; i++) {
        sql = sql + e.getSkills()[i];
        if (i < sizeSkills) sql = sql + ";";
    }
    sql = sql + "','";

    int sizeColleagues = e.getColleagues().size();
    for (int i = 0; i < sizeColleagues; i++){
        sql = sql + to_string(e.getColleagues()[i]->getId());
        if (i < sizeColleagues) sql = sql + ";";
    }
    sql = sql + "','" + e.getHashedPassword() + "');";

    sqlite3_open(dbPath.c_str(), &DB) ;

    sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL) ;

    sqlite3_close(DB) ;
}

void createEntry (Employee &e) 
{
    sqlite3 *DB ;
    string sql = "INSERT INTO EMPLOYEE VALUES(" + to_string(e.getId()) + ",'" + e.getName() + "','" + e.getFirstname() + "','" + e.getEmail() + "','" + e.getZipcode() + "','" ;

    int sizeSkills = e.getSkills().size();
    for (int i = 0; i < sizeSkills; i++) {
        sql = sql + e.getSkills()[i];
        if (i < sizeSkills) sql = sql + ";";
    }
    sql = sql + "','";

    int sizeColleagues = e.getColleagues().size();
    for (int i = 0; i < sizeColleagues; i++){
        sql = sql + to_string(e.getColleagues()[i]->getId());
        if (i < sizeColleagues) sql = sql + ";";
    }
    sql = sql + "'," + e.getCompany().getId() + ",'" e.getHashedPassword() + "');";

    sqlite3_open(dbPath.c_str(), &DB) ;

    sqlite3_exec(DB, sql.c_str(), NULL, 0, NULL) ;

    sqlite3_close(DB) ;
}

void createEntry (Job &j) 
{

}


void updateEntry (std::vector<Company*> &list) 
{
    sqlite3 *DB ;
    int size = list.size();

    sqlite3_open(dbPath.c_str(), &DB) ;

    // We remove the DB's content to fill it with the new values
    sqlite3_exec(DB, "DELETE FROM COMPANY; VACUUM", NULL, 0, NULL) ;

    // We then add the objects of list
    for (int i = 0; i < size; i++){
        // Enter new Company info
        Company *c = list[i];
        createEntry(*c);
    }

    sqlite3_close(DB) ;
}

void updateEntry (std::vector<JobSeeker*> &list) 
{
    sqlite3 *DB ;
    int size = list.size();

    sqlite3_open(dbPath.c_str(), &DB) ;

    // We remove the DB's content to fill it with the new values
    sqlite3_exec(DB, "DELETE FROM JOBSEEKER; VACUUM", NULL, 0, NULL) ;

    // We then add the objects of list
    for (int i = 0; i < size; i++){
        // Enter new Company info
        JobSeeker *js = list[i];
        createEntry(*js);
    }

    sqlite3_close(DB) ;
}

void updateEntry (std::vector<Employee*> &list) 
{
    sqlite3 *DB ;
    int size = list.size();

    sqlite3_open(dbPath.c_str(), &DB) ;

    // We remove the DB's content to fill it with the new values
    sqlite3_exec(DB, "DELETE FROM EMPLOYEE; VACUUM", NULL, 0, NULL) ;

    // We then add the objects of list
    for (int i = 0; i < size; i++){
        // Enter new Company info
        Employee *e = list[i];
        createEntry(*e);
    }

    sqlite3_close(DB) ;
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
