#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <vector>
#include <string>

/* FOREGROUND */
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

class Company ;
class Employee ;
class JobSeeker ;
class Job ;

class Cli {
    public:
        // A Cli object takes the global vectors of the app as references
        Cli(std::vector<Company*> &companies, std::vector<Employee*> &employees, std::vector<JobSeeker*> &jobSeekers, std::vector<Job*> &jobs) ;

        // Init path for log file
        void setLogPath(std::string path);

        // Waits for input from user before going on
        void wait();
        void printHeader() ;
        void printQuitOrReturn() ;
        void printCompanies(std::vector<Company*> &companies) ;
        void printEmployees(std::vector<Employee*> &employees) ;
        void printJobs(std::vector<Job*> &jobs) ;
        void printJobSeekers(std::vector<JobSeeker*> &jobSeekers) ;

        // Box info
        void printInfoJS(int id);
        void printInfoComp(int id) ;
        void printInfoEmp(int id);

        // Create profile or login
        void printMenu();
        
        void printMenuCreateProfile();
        void printMenuCreateProfileComp();
        void printMenuCreateProfileEmp();
        void printMenuCreateProfileJS();
        // Gets id of user
        void printLogin();

        
        // Company Menu
        void printMenuCompany(int id);
        
        // JobSeeker Menu
        void printMenuJobSeeker(int id);

        // Employee Menu
        void printMenuEmployee(int id) ;
        

    private:
    
        std::vector<Company*> &_companies ;
        std::vector<Employee*> &_employees ;
        std::vector<JobSeeker*> &_jobSeekers ;
        std::vector<Job*> &_jobs ;
        std::string _logpath;
} ;

#endif