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
    Company c(1, "KerLav", "31", "pro@gmail.com");
    TEST(!c.getEmail().compare("pro@gmail.com")); 

    fstream companiesIn, employeesIn, jobsIn, jobseekersIn ;
    fstream companiesOut, employeesOut, jobsOut, jobseekersOut ;

    companiesIn.open("test/data/csv/companies.csv", ios::in) ;
    employeesIn.open("test/data/csv/employees.csv", ios::in) ;
    jobsIn.open("test/data/csv/jobs.csv", ios::in) ;
    jobseekersIn.open("test/data/csv/jobseekers.csv", ios::in) ;

    companiesOut.open("test/data/csv/companies.csv", ios::out) ;
    employeesOut.open("test/data/csv/employees.csv", ios::out) ;
    jobsOut.open("test/data/csv/jobs.csv", ios::out) ;
    jobseekersOut.open("test/data/csv/jobseekers.csv", ios::out) ;

    vector<Company> companies ;
    vector<Employee> employees ;
    vector<Job> jobs ;
    vector<JobSeeker> jobSeekers ;

    // DB TESTS
    // getCompanies
    companies = getCompanies (companiesIn) ;
    {
        TEST (companies[0].getId() == 1) ;
        TEST (!companies[1].getName().compare("Google")) ;
        TEST (!companies[2].getZipcode().compare("13006")) ;
    }

    companiesIn.close();
    employeesIn.close();
    jobsIn.close();
    jobseekersIn.close();

    companiesOut.close();
    employeesOut.close();
    jobsOut.close();
    jobseekersOut.close();

    printf("%d/%d\n", tests_reussis, tests_executes);
    
    return tests_executes - tests_reussis;
}
