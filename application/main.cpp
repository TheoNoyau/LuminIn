#include "People/Employee.h"
#include "People/JobSeeker.h"
#include "People/Job.h"
#include "People/Company.h"
#include "DB/BDD.h"
#include "UI/CLI/cli.h"

using namespace std ;

int main ()
{
    // Set path to the database
    setPath("application/data/csv");

    // Fetch all the objects
    vector<Company*> companies = getCompanies() ;
    vector<Employee*> employees = getEmployees() ;
    vector<JobSeeker*> jobSeekers = getJobSeekers () ;
    vector<Job*> jobs = getJobs() ;

    // App
    Cli app(companies, employees, jobSeekers, jobs);
    app.printMenu() ;

    // Save data to make it persistent
    updateEntry(companies) ;
    updateEntry(employees) ;
    updateEntry(jobSeekers) ;
    updateEntry(jobs) ;

    // Clear the vectors of pointers to avoid memory leak
    clearVector(companies) ;
    clearVector(employees) ;
    clearVector(jobSeekers) ;
    clearVector(jobs) ;

    return 0 ;
}