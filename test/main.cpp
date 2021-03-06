#include "People/Employee.h"
#include "People/JobSeeker.h"
#include "People/Job.h"
#include "People/Company.h"
#include "DB/BDD.h"
#include "Journal/journal.h"
#include "Security/password.h"

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

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
    // setPath("test/data/csv");
    setPath("test/data/sql/db_luminin_test.db") ;
    sqlInit() ;

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

        // Tests comapany names with comma(s) (other functions are already tested below)
        Company* googleInc = new Company("Google, Inc.", "09700", "contact@google.fr") ;
        googleInc->createProfile(companies, "") ;
   
        
        updateEntry(companies) ;
        companies = getCompanies() ;

        int googleIncIndex = Company::getIndex(googleInc->getId(), companies) ;
        TEST(!companies[googleIncIndex]->getName().compare("Google, Inc.")) ;
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
        js->createProfile(jobSeekers, "");

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
        JobSeeker* js2 = new JobSeeker("AHOUI", "Jean", "undefined@test.fr", "13009", {"C++", "Java"}, jsColleagues) ;
        js2->createProfile(jobSeekers, "") ;
    
        Employee* e = js2->jobSeekerToEmployee(employees, jobSeekers, *(companies[1])) ;
        jsIndex = Employee::getIndex(e->getId(), employees) ;

        TEST (!employees[jsIndex]->getName().compare("AHOUI")) ;
        TEST (!employees[jsIndex]->getCompany().getName().compare(companies[1]->getName())) ;

        // searchForJobs with skills
        JobSeeker* js3 = new JobSeeker("TEST", "Kevin", "undefined@test.fr", "13009", {"C++", "Java"}, jsColleagues) ;
        js3->createProfile(jobSeekers, "") ;

        vector<Job*> resJobs1 = js3->searchForJobs(jobs, {"Python", "SQL", "C", "C++"}) ;
        vector<Job*> resJobs2 = js3->searchForJobs(jobs, {"Python"}) ;

        TEST (!resJobs1[0]->getTitle().compare("developpeur"));
        TEST (!resJobs1[0]->getCompany().getName().compare("Google"));

        TEST (!resJobs2[0]->getTitle().compare("developpeur")) ;

        // searchForJobs with skills and zipcode 
        resJobs1 = js3->searchForJobs(jobs, {"Python", "SQL", "C"}, "75009") ;
        resJobs2 = js3->searchForJobs(jobs, {"Python", "SQL", "C"}, "13009") ;

        TEST (!resJobs1[0]->getTitle().compare("developpeur"));
        TEST (!resJobs1[0]->getCompany().getName().compare("Google"));
        TEST (resJobs2.size() == 0) ;

        // Tests to check order: the jobs having the most skills in common must be in the first indexes
        Company* compTest = new Company("Company Test", "09700", "company-test@test.fr") ;
        compTest->createProfile(companies, "") ;

        compTest->createJob(jobs, "JobTest1", {"B", "E"}) ;
        compTest->createJob(jobs, "JobTest2", {"D", "B", "A"}) ;
        compTest->createJob(jobs, "JobTest3", {"A", "D", "E"}) ;

        resJobs1 = js3->searchForJobs(jobs, {"A", "B", "D"}) ;

        TEST(resJobs1.size() == 3) ;
        TEST(!resJobs1[0]->getTitle().compare("JobTest2")) ;
        TEST(!resJobs1[1]->getTitle().compare("JobTest3")) ;
        TEST(!resJobs1[2]->getTitle().compare("JobTest1")) ;

        compTest->deleteProfile(companies, jobs, employees, jobSeekers) ;

        // searchForOldColleagues with Company
        js3->addColleague(*(employees[1])) ;
        js3->addColleague(*(employees[2])) ;
        vector<Employee*> oldColleagues = js3->searchForOldColleagues(*(companies[0])) ;

        TEST (!oldColleagues[0]->getFirstname().compare("Mickey")) ;
        TEST (!oldColleagues[1]->getFirstname().compare("Minnie")) ;

        // searchForOldColleagues with skills
        js3->addSkills({"C", "Python", "SQL"}) ;
        vector<Employee*> oldColleagues2 = js3->searchForOldColleagues(jobs) ;

        TEST (Employee::getIndex(1, oldColleagues2) != - 1) ;

        js3->addSkills({"comedie", "gag"}) ;
        oldColleagues2 = js3->searchForOldColleagues(jobs) ;
        TEST (Employee::getIndex(2, oldColleagues2) != - 1) ;
    }

    // Employee Class Tests
    {
        vector<Employee*> colleagues ;
        colleagues.push_back(employees[0]) ;

        Employee* e = new Employee("KERNEVES", "Theo", "tkerneves@gmail.com", "13006", {"C++", "C"}, colleagues, *(companies[1])) ;

        // createProfile
        e->createProfile(employees, "");
        int eIndex = Employee::getIndex(e->getId(), employees) ;

        TEST (!employees[eIndex]->getName().compare("KERNEVES")) ;
        TEST (!employees[eIndex]->getColleagues()[0]->getFirstname().compare("Michel")) ;
        TEST (!employees[eIndex]->getCompany().getName().compare("Google")) ;

        // setCompany
        e->setCompany(*(companies[0])) ;
        TEST (!employees[eIndex]->getCompany().getName().compare("Disney")) ;

        // addSkills
        e->addSkills({"Nodejs", "React"}) ;

        TEST (!employees[eIndex]->getSkills()[2].compare("Nodejs")) ;
        TEST (!employees[eIndex]->getSkills()[3].compare("React")) ;

        // addColleague
        e->addColleague(*(employees[1])) ;

        TEST (!employees[eIndex]->getColleagues()[0]->getName().compare("Untel")) ;
        TEST (!employees[eIndex]->getColleagues()[1]->getFirstname().compare("Mickey")) ;
        TEST (!employees[eIndex]->getColleagues()[1]->getCompany().getName().compare("Disney")) ;

        // deleteProfile
        unsigned int sizeEmployees = employees.size() ;
        e->deleteProfile(employees, jobSeekers) ;
        TEST (employees.size() == sizeEmployees - 1) ;

        // employeeToJobSeeker
        Employee* e2 = new Employee("Blerfood", "Tagliatelle", "undefined@test.fr", "13009", {"C++", "Java"}, colleagues, *(companies[0])) ;
        e2->createProfile(employees, "") ;
    
        JobSeeker* js = e2->employeeToJobSeeker(employees, jobSeekers) ;
        eIndex = JobSeeker::getIndex(js->getId(), jobSeekers) ;

        TEST (!jobSeekers[eIndex]->getName().compare("Blerfood")) ;
        TEST (Employee::getIndex(2, js->getColleagues()) != -1) ; // Colleagues from Disney had been added

        // searchForJobs with skills
        Employee* e3 = new Employee("TEST", "Kevin", "undefined@test.fr", "13009", {"C++", "Java"}, colleagues, *(companies[1])) ;
        e3->createProfile(employees, "") ;

        vector<Job*> resJobs1 = e3->searchForJobs(jobs, {"Python", "SQL", "C", "C++"}) ;
        vector<Job*> resJobs2 = e3->searchForJobs(jobs, {"Python"}) ;

        TEST (!resJobs1[0]->getTitle().compare("developpeur"));
        TEST (!resJobs1[0]->getCompany().getName().compare("Google"));

        TEST (!resJobs2[0]->getTitle().compare("developpeur"));
        TEST (resJobs2.size() == 1) ;

        // searchForJobs with skills and zipcode 
        resJobs1 = e3->searchForJobs(jobs, {"Python", "SQL", "C"}, "75009") ;
        resJobs2 = e3->searchForJobs(jobs, {"Python", "SQL", "C"}, "13009") ;
        TEST (!resJobs1[0]->getTitle().compare("developpeur"));
        TEST (!resJobs1[0]->getCompany().getName().compare("Google"));
        TEST (resJobs2.size() == 0) ;

        // Tests to check order: the jobs having the most skills in common must be in the first indexes
        Company* compTest = new Company("Company Test", "09700", "company-test@test.fr") ;
        compTest->createProfile(companies, "") ;

        compTest->createJob(jobs, "JobTest1", {"B", "E"}) ;
        compTest->createJob(jobs, "JobTest2", {"D", "B", "A"}) ;
        compTest->createJob(jobs, "JobTest3", {"A", "D", "E"}) ;

        resJobs1 = e3->searchForJobs(jobs, {"A", "B", "D"}) ;

        TEST(resJobs1.size() == 3) ;
        TEST(!resJobs1[0]->getTitle().compare("JobTest2")) ;
        TEST(!resJobs1[1]->getTitle().compare("JobTest3")) ;
        TEST(!resJobs1[2]->getTitle().compare("JobTest1")) ;

        compTest->deleteProfile(companies, jobs, employees, jobSeekers) ; // Deletes all the jobs with it

        // searchForOldColleagues with Company
        e3->addColleague(*(employees[1])) ;
        e3->addColleague(*(employees[2])) ;
        vector<Employee*> oldColleagues = e3->searchForOldColleagues(*(companies[0])) ;

        TEST (!oldColleagues[0]->getFirstname().compare("Mickey")) ;
        TEST (!oldColleagues[1]->getFirstname().compare("Minnie")) ;

        // searchForOldColleagues with skills
        e3->addSkills({"C", "Python", "SQL"}) ;
        vector<Employee*> oldColleagues2 = e3->searchForOldColleagues(jobs) ;

        TEST (Employee::getIndex(1, oldColleagues2) != - 1) ;

        e3->addSkills({"comedie", "gag"}) ;
        oldColleagues2 = e3->searchForOldColleagues(jobs) ;
        TEST (Employee::getIndex(2, oldColleagues2) != - 1) ;
    }

    // Company Class Tests
    {
        // createProfile
        Company* polytech = new Company("Polytech","13009","polytech@univ-amu.fr");
        polytech->createProfile(companies, "");
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
        TEST(relevantJs.size() >= 2);
        TEST(JobSeeker::getIndex(1, relevantJs) != -1);
        TEST(JobSeeker::getIndex(3, relevantJs) != -1);
        TEST(JobSeeker::getIndex(2, relevantJs) == -1);

        // Not ordered list of skills
        relevantJs = polytech->searchForJobSeekers(jobSeekers, {"Python","C","SQL"});
        TEST(relevantJs.size() >= 1);
        TEST(JobSeeker::getIndex(2, relevantJs) != -1);

        // More skills than needed
        relevantJs = polytech->searchForJobSeekers(jobSeekers, {"Python","C",});
        TEST(JobSeeker::getIndex(2, relevantJs) != -1);

        // No matching
        relevantJs = polytech->searchForJobSeekers(jobSeekers, {"Rigoureux","Sportif"});
        TEST(relevantJs.size() == 0);
    
        // Test for search with zipcode
        relevantJs = polytech->searchForJobSeekers(jobSeekers, {"SQL","C","Python"}, "31300");
        TEST(relevantJs.size() == 0);

        relevantJs = polytech->searchForJobSeekers(jobSeekers, {"SQL","C","Python"}, "75020");
        TEST(JobSeeker::getIndex(2, relevantJs) != -1);

        // Francois should be in relevantJs even if it has only one skill in common with the skill given in parameters
        relevantJs = polytech->searchForJobSeekers(jobSeekers, {"Python"});
        TEST(JobSeeker::getIndex(2, relevantJs) != -1);

        // Tests to check order: the job seekers having the most skills in common must be in the first indexes
        vector<Employee*> jsColleagues ;
        jsColleagues.push_back(employees[0]) ;

        JobSeeker* jsTest1 = new JobSeeker("TEST1", "t1", "test@test.fr", "09100", {"A"}, jsColleagues) ;
        jsTest1->createProfile(jobSeekers, "");

        JobSeeker* jsTest2 = new JobSeeker("TEST2", "t2", "test@test.fr", "09100", {"A", "D", "B"}, jsColleagues) ;
        jsTest2->createProfile(jobSeekers, "");

        JobSeeker* jsTest3 = new JobSeeker("TEST3", "t3", "test@test.fr", "09100", {"D", "B"}, jsColleagues) ;
        jsTest3->createProfile(jobSeekers, "");

        relevantJs = polytech->searchForJobSeekers(jobSeekers, {"A", "B", "D"});
        TEST(relevantJs.size() == 3) ;
        TEST(relevantJs[0]->getId() == jsTest2->getId()) ;
        TEST(relevantJs[1]->getId() == jsTest3->getId()) ;
        TEST(relevantJs[2]->getId() == jsTest1->getId()) ;

        jsTest1->deleteProfile(jobSeekers) ;
        jsTest2->deleteProfile(jobSeekers) ;
        jsTest3->deleteProfile(jobSeekers) ;
    }
    // Logger testing
    {
        vector<string> args{"1","2"};
        logger("test/log/log.txt", "getTimeAndDate", args);
        vector<string> args2{};
        logger("test/log/log.txt", "getTimeAndDate", args2);
        vector<string> args3{"banane"};
        logger("test/log/log.txt", "getTimeAndDate", args3);
    }

    // Password handling testing
    {
        // Company password
        Company* compTest = new Company("Company Test", "75100", "company@test.fr") ;
        compTest->createProfile(companies, "MotDePasse123") ;

        TEST(compTest->getHashedPassword().compare("MotDePasse123")) ;
        TEST(checkPassword(compTest->getHashedPassword(),"Abdsgf") == false) ;
        TEST(checkPassword(compTest->getHashedPassword(), "MotDePasse123") == true);

        // Employee password
        vector<Employee*> colleagues ;
        Employee* empTest = new Employee("EMPLOYEE", "Test", "Test@employee.com", "13006", {"C++", "C"}, colleagues, *(companies[1])) ;
        empTest->createProfile(employees, "PaSsWord$123") ;

        TEST(empTest->getHashedPassword().compare("PaSsWord$123")) ;
        TEST(checkPassword(empTest->getHashedPassword(),"abcdertze*$5") == false) ;
        TEST(checkPassword(empTest->getHashedPassword(), "PaSsWord$123") == true);

        // Job Seeker password
        JobSeeker* jsTest = new JobSeeker("JOBSEEKER", "Test", "job@seeker.fr", "13009", {"C++", "Java"}, colleagues) ;
        jsTest->createProfile(jobSeekers, "choucroute64") ;

        TEST(jsTest->getHashedPassword().compare("choucroute64")) ;
        TEST(checkPassword(jsTest->getHashedPassword(),"abcdertze*$5") == false) ;
        TEST(checkPassword(jsTest->getHashedPassword(), "choucroute64") == true);

        // Transitions
        JobSeeker *jsEmp = empTest->employeeToJobSeeker(employees, jobSeekers) ;
        TEST(checkPassword(jsEmp->getHashedPassword(), "PaSsWord$123") == true) ;

        Employee *empJs = jsTest->jobSeekerToEmployee(employees, jobSeekers, *companies[0]) ;
        TEST(checkPassword(empJs->getHashedPassword(), "choucroute64") == true) ;

        jsEmp->deleteProfile(jobSeekers) ;
        empJs->deleteProfile(employees, jobSeekers) ;
        compTest->deleteProfile(companies, jobs, employees, jobSeekers) ;
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
