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

    while (sqlite3_column_text(stmt, 0)) {
        dataLine.clear() ;
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

}

void createEntry (Employee &e) 
{

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
