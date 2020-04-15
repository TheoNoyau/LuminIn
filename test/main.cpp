#include "People/Employee.h"
#include "People/JobSeeker.h"
#include "People/Job.h"
#include "People/Company.h"
#include "DB/BDD.h"

#include <vector>
#include <string>
#include <fstream>

using namespace std ;

// Nombre total de tests exécutés. 
int tests_executes = 0;
// Pour chaque test qui réussi, cette variable sera incrémentée de 1.
// Le but est de la garder égale à test_executes.
int tests_reussis = 0;

#define STRINGIZE_(x) #x
#define STRINGIZE(x) STRINGIZE_(x)

// Incrémente le nombre de test exécutés de 1.
// Si le test réussi, incrémente le nombre de tests réussis de 1.
#define TEST(x) tests_executes += 1;    \
                if(x)                   \
                {                       \
                    tests_reussis += 1; \
                    printf("[SUCCES] ");\
                }                       \
                else                    \
                {                       \
                    printf("[ECHEC ] ");\
                }                       \
                printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": " STRINGIZE(x) "\n");


int main()
{
    // // First basic test
    // TEST(!c.getEmail().compare("pro@gmail.com"));

    
        

    // Sets the path to csv files
    setPath("test/data/csv");

    vector<Company*> companies ;
    vector<Employee*> employees ;
    vector<Job*> jobs ;
    vector<JobSeeker*> jobSeekers ;

    // // DB Test -> updateEntry for each file
    // // updateEntry for Company
    // {
    //     Company c("KerLav", "31", "pro@gmail.com");
    //     c.setId(1);
    //     Company c2("LavKer", "13", "pro@gmail.com");
    //     c2.setId(2);
    //     Company c3("jskdna", "13001", "pro@gmail.com");
    //     c3.setId(3);
    //     companies.push_back(c);
    //     companies.push_back(c2);
    //     companies.push_back(c3);
    //     updateEntry(companies);
    // }

    // vector<Employee> colleagues;
    // // updateEntry for JobSeeker
    // {
    //     JobSeeker js("Lavedrine", "Aymeric", "aymeric@lavedrine.net", "13006", {"prog","comedie"}, colleagues);
    //     js.setId(1);
    //     JobSeeker js2("Kerneves", "Theo ", "theoker@gmail.net", "09700", {"prog","comedie"}, colleagues);
    //     js2.setId(2);
    //     JobSeeker js3("Kerneves", "Aymeric", "aymeric@lavedrine.net", "13006", {"prog","comedie"}, colleagues); 
    //     js3.setId(3);
    //     jobSeekers.push_back(js);
    //     jobSeekers.push_back(js2);
    //     jobSeekers.push_back(js3);
    //     updateEntry(jobSeekers);
    // }

    // // updateEntry for Employee
    // {
    //     Employee e("Kerneves", "Theo", "theo.kerneves@gmail.com", "09700", {"trop bo", "trop fort"}, colleagues, c);
    //     e.setId(1);
    //     Employee e2("Lavedrine", "Aymeric", "theo.kerneves@gmail.com", "09700", {"trop bo", "trop fort"}, colleagues, c);
    //     e2.setId(2);
    //     Employee e3("Lavedrine", "Theo", "theo.kerneves@gmail.com", "09700", {"trop bo", "trop fort"}, colleagues, c);
    //     e3.setId(3);
    //     employees.push_back(e);
    //     employees.push_back(e2);
    //     employees.push_back(e3);
    //     updateEntry(employees);
    // }

    // // updateEntry for Job
    // {
    //     Job j("Developpeur Full Stack",{"CSS","HTML5","Python"},c);
    //     j.setId(1);
    //     Job j2("Dessinateur Full Stack",{"Crayon","Papier","Python"},c);
    //     j2.setId(2);
    //     jobs.push_back(j);
    //     jobs.push_back(j2);
    //     updateEntry(jobs);  
    // }

    // // DB TESTS
    // getCompanies
    companies = getCompanies() ;
    {
        TEST (companies[0]->getId() == 1) ;
        TEST (!companies[1]->getName().compare("Google")) ;
        TEST (!companies[2]->getZipcode().compare("31")) ;
    }

    // getCompany
    {
        Company *cTest = getCompany(2) ;
        TEST (!cTest->getName().compare("Google")) ;
    }
    {
        Company *cTest = getCompany(99999) ;
        TEST (!cTest->getName().compare("undefined")) ;
        TEST (cTest->getId() < 0) ;
    }

    // getEmployees
    employees = getEmployees() ;
    {
        // cout << employees[0].getColleagues()[0].getId() << endl ;
        TEST (!employees[0]->getName().compare("Untel")) ;
        TEST (!employees[0]->getSkills()[0].compare("C++")) ;

        TEST (!employees[1]->getCompany().getName().compare("Disney")) ;
        TEST (!employees[1]->getColleagues()[0]->getFirstname().compare("Minnie")) ;
        TEST (!employees[2]->getColleagues()[0]->getFirstname().compare("Mickey")) ;
        TEST (!employees[2]->getColleagues()[0]->getCompany().getName().compare("Disney")) ;
    }

    // getJobSeekers
    jobSeekers = getJobSeekers() ;
    {
        TEST (!jobSeekers[0]->getName().compare("Duck")) ;
        TEST (!jobSeekers[1]->getSkills()[2].compare("Python")) ;
        
        TEST (!jobSeekers[0]->getColleagues()[0]->getEmail().compare("mickey@mickeyville.gov")) ;
        TEST (!jobSeekers[0]->getColleagues()[0]->getCompany().getName().compare("Disney")) ;
    }


    // getJobs
    jobs = getJobs () ;
    {
        TEST (!jobs[0]->getTitle().compare("acteur")) ;
        TEST (!jobs[1]->getSkills()[1].compare("SQL")) ;
        TEST (!jobs[1]->getCompany().getName().compare("Google")) ;
    }

    // JobSeeker Class Tests
    {
        vector<Employee*> jsColleagues ;
        jsColleagues.push_back(employees[0]) ;

        JobSeeker* js = new JobSeeker("BERNARD", "Jean", "jean@bernard.fr", "13009", {"C++", "Java"}, jsColleagues) ;

        // createProfile
        js->createProfile(jobSeekers);

        // Get the index in the vector of JobSeekers of the JobSeeker created with createProfile()
        int jsIndex = JobSeeker::getIndex(js->getId(), jobSeekers) ;

        TEST (!jobSeekers[jsIndex]->getName().compare("BERNARD")) ;
        TEST (!jobSeekers[jsIndex]->getColleagues()[0]->getFirstname().compare("Michel")) ;

        // addSkill
        js->addSkills({"Nodejs", "React"}) ;

        TEST (!jobSeekers[jsIndex]->getSkills()[2].compare("Nodejs")) ;
        TEST (!jobSeekers[jsIndex]->getSkills()[3].compare("React")) ;

        // addColleague
        js->addColleague(*(employees[1])) ;

        TEST (!jobSeekers[jsIndex]->getColleagues()[0]->getName().compare("Untel")) ;
        TEST (!jobSeekers[jsIndex]->getColleagues()[1]->getFirstname().compare("Mickey")) ;
        TEST (!jobSeekers[jsIndex]->getColleagues()[1]->getCompany().getName().compare("Disney")) ;

        // deleteProfile
        unsigned int sizeJobSeekers = jobSeekers.size() ;
        js->deleteProfile(jobSeekers) ;
        TEST (jobSeekers.size() == sizeJobSeekers - 1) ;

        // jobSeekerToEmployee
        JobSeeker* js2 = new JobSeeker("BERNARD", "Jean", "jean@bernard.fr", "13009", {"C++", "Java"}, jsColleagues) ;
        js2->createProfile(jobSeekers) ;
    
        Employee* e = js2->jobSeekerToEmployee(employees, jobSeekers, *(companies[1])) ;
        jsIndex = Employee::getIndex(e->getId(), employees) ;

        TEST (!employees[jsIndex]->getName().compare(js2->getName())) ;
        TEST (!employees[jsIndex]->getCompany().getName().compare(companies[1]->getName())) ;

        // searchForJobs with skills
        vector<Job*> resJobs1 = js2->searchForJobs(jobs, {"Python", "SQL", "C"}) ;
        vector<Job*> resJobs2 = js2->searchForJobs(jobs, {"Python"}) ;

        TEST (!resJobs1[0]->getTitle().compare("developpeur"));
        TEST (!resJobs1[0]->getCompany().getName().compare("Google"));
        TEST (resJobs2.size() == 0) ;

        // searchForJobs with skills and zipcode 
        resJobs1 = js2->searchForJobs(jobs, {"Python", "SQL", "C"}, "75009") ;
        resJobs2 = js2->searchForJobs(jobs, {"Python", "SQL", "C"}, "13009") ;

        TEST (!resJobs1[0]->getTitle().compare("developpeur"));
        TEST (!resJobs1[0]->getCompany().getName().compare("Google"));
        TEST (resJobs2.size() == 0) ;
    }

    // Employee Class Tests
    {
        vector<Employee*> colleagues ;
        colleagues.push_back(employees[0]) ;

        Employee* e = new Employee("KERNEVES", "Theo", "tkerneves@gmail.com", "13006", {"C++", "C"}, colleagues, *(companies[1])) ;

        // createProfile
        e->createProfile(employees);
        int eIndex = Employee::getIndex(e->getId(), employees) ;

        TEST (!employees[eIndex]->getName().compare("KERNEVES")) ;
        TEST (!employees[eIndex]->getColleagues()[0]->getFirstname().compare("Michel")) ;
        TEST (!employees[eIndex]->getCompany().getName().compare("Google")) ;
    }

    // Company Class Tests
    {
        // createProfile
        Company* polytech = new Company("Polytech","13009","polytech@univ-amu.fr");
        polytech->createProfile(companies);
        int polytechIndex = Company::getIndex(polytech->getId(), companies);

        TEST(!companies[polytechIndex]->getName().compare("Polytech"));
        TEST(!companies[polytechIndex]->getEmail().compare("polytech@univ-amu.fr"));

        // updateProfile
        polytech->updateProfile(companies, "Polytech Marseille","13009","polytech-marseille@univ-amu.fr");

        TEST(!companies[polytechIndex]->getName().compare("Polytech Marseille"));
        TEST(!companies[polytechIndex]->getEmail().compare("polytech-marseille@univ-amu.fr"));

        // deleteProfile 
        // It works 
        // polytech->deleteProfile(companies);

        // createJob
        polytech->createJob(jobs, "Comedien",{"Drole","Marrant","Rigolo"});

        TEST(!jobs[2]->getTitle().compare("Comedien"));
        TEST(!jobs[2]->getSkills()[2].compare("Rigolo"));

        // deleteJob
        // It works 
        // polytech->deleteJob(jobs, jobs[2]);

        // searchForJobSeekers
        vector<JobSeeker*> relevantJs = polytech->searchForJobSeekers(jobSeekers, {"comedie"});
        TEST(relevantJs.size() == 2);
        TEST(!relevantJs[0]->getFirstname().compare("Donald"));
        TEST(!relevantJs[1]->getFirstname().compare("Aymeric"));

        // Not ordered list of skills
        relevantJs = polytech->searchForJobSeekers(jobSeekers, {"Python","C","SQL"});
        TEST(relevantJs.size() == 1);
        TEST(!relevantJs[0]->getFirstname().compare("Francois"));

        // No profile matching
        relevantJs = polytech->searchForJobSeekers(jobSeekers, {"Java","Sportif"});
        TEST(relevantJs.size() == 0);
    
        // Test for search with zipcode
        relevantJs = polytech->searchForJobSeekers(jobSeekers, {"SQL","C","Python"}, "31300");
        TEST(relevantJs.size() == 0);

        relevantJs = polytech->searchForJobSeekers(jobSeekers, {"SQL","C","Python"}, "75020");
        TEST(relevantJs.size() == 1);
        TEST(!relevantJs[0]->getFirstname().compare("Francois"));


    }

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

    printf("%d/%d\n", tests_reussis, tests_executes);
    
    return tests_executes - tests_reussis;
}
