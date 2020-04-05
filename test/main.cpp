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
    // First basic test
    Company c("KerLav", "31", "pro@gmail.com");
    TEST(!c.getEmail().compare("pro@gmail.com"));     

    fstream companiesTable, employeesTable, jobsTable, jobseekersTable ;

    companiesTable.open("test/data/csv/companies.csv", ios::in | ios::app) ;
    employeesTable.open("test/data/csv/employees.csv", ios::in | ios::app) ;
    jobsTable.open("test/data/csv/jobs.csv", ios::in | ios::app) ;
    jobseekersTable.open("test/data/csv/jobseekers.csv", ios::in | ios::app) ;

    vector<Company> companies ;
    vector<Employee> employees ;
    vector<Job> jobs ;
    vector<JobSeeker> jobSeekers ;

    // DB TESTS
    // getCompanies
    companies = getCompanies (companiesTable) ;
    {
        TEST (companies[0].getId() == 1) ;
        TEST (!companies[1].getName().compare("Google")) ;
        TEST (!companies[2].getZipcode().compare("31")) ;
    }

    // getCompany
    {
        Company cTest = getCompany(companiesTable, 2) ;
        TEST (!cTest.getName().compare("Google")) ;
    }
    {
        Company cTest = getCompany(companiesTable, 99999) ;
        TEST (!cTest.getName().compare("undefined")) ;
        TEST (cTest.getId() < 0) ;
    }

    // createEntry for each entry
    
    createEntry(companiesTable, c);
    JobSeeker js("Lavedrine", "Aymeric", "aymeric@lavedrine.net", "13006", {"prog","comedie"}, employees);
    createEntry(jobseekersTable, js);

    companiesTable.close();
    employeesTable.close();
    jobsTable.close();
    jobseekersTable.close();

    printf("%d/%d\n", tests_reussis, tests_executes);
    
    return tests_executes - tests_reussis;
}
