#include "Employee.h"

#include "JobSeeker.h"
#include "Job.h"
#include "Company.h"

#include <algorithm>

using namespace std;

Employee::Employee(string name, string firstname, string email, string zipcode, vector<string> skills, vector<Employee*> &list, Company &c) : _name(name), _firstname(firstname), _email(email), _zipcode(zipcode), _skills(skills), _oldColleagues(list), _company(&c)
{

}

Employee::Employee(Company &c) : _name("undefined"), _firstname("undefined"), _email("undefined"), _zipcode("undefined"), _company(&c)
{
    _id = -1 ;
}

Employee::Employee(const Employee &copy) : _id(copy._id), _name(copy._name), _firstname(copy._firstname), _email(copy._email), _zipcode(copy._zipcode), _skills(copy._skills), _oldColleagues(copy._oldColleagues), _company(copy._company)
{

}

int Employee::getIndex(const int id, vector<Employee*> &employees)
{
    int size = employees.size() ;
    
    for (int i = 0; i < size; i++) {
        if (employees[i]->getId() == id) return i ;
    }

    return -1; 
}

vector<Employee*> Employee::getEmployees(string name, vector<Employee*> &employees)
{
    vector<Employee*> res ;

    for (unsigned int i = 0; i < employees.size(); i++) {
        if (!employees[i]->getName().compare(name)) res.push_back(employees[i]) ;
    }

    return res ;
}

int Employee::getId()
{
    return _id;
}

string Employee::getName()
{
    return _name;
}

string Employee::getFirstname()
{
    return _firstname;
}

string Employee::getEmail()
{
    return _email;
}

string Employee::getZipcode()
{
    return _zipcode;
}

vector<string> Employee::getSkills()
{
    return _skills;
}

vector<Employee*> &Employee::getColleagues()
{
    return _oldColleagues;
}

Company &Employee::getCompany()
{
    return *_company;
}

void Employee::setId(int id)
{
    _id = id;
}

void Employee::setId(vector<Employee*> &list)
{
    _id = (int)list.size() + 1 ;
}

void Employee::setZipcode(string zipcode)
{
    _zipcode = zipcode ;
}

void Employee::setCompany(Company &c)
{
    _company = &c ;
}

void Employee::createProfile(vector<Employee*> &list)
{
    // Giving an id to the object
    setId(list) ;

    // Adding to the global vector of JobSeekers of the app
    list.push_back(this) ;
}

void Employee::addSkills(vector<string> skills)
{
    for (unsigned int i = 0; i < skills.size(); i++) {
        _skills.push_back(skills[i]) ;
    }
}

int Employee::addColleague(Employee &e)
{
    if (Employee::getIndex(e.getId(), _oldColleagues) != -1) return -1 ;
    _oldColleagues.push_back(&e) ;
    return 0 ;
}

void Employee::deleteProfile(vector<Employee*> &list)
{
    auto it = list.begin() + Employee::getIndex(_id, list) ;
    delete * it ;
    list.erase(it) ;
}

JobSeeker* Employee::employeeToJobSeeker(vector<Employee*> &employees, vector<JobSeeker*> &jobseekers)
{
    JobSeeker* js = new JobSeeker (_name, _firstname, _email, _zipcode, _skills, _oldColleagues) ;
    js->createProfile(jobseekers) ;

    this->deleteProfile(employees) ;

    // We add the employees of the company left in the colleagues
    for (auto e : employees) {
        if (e->getCompany().getId() == _company->getId()) {
            // If the employees aren't already colleagues
            if (Employee::getIndex(e->getId(), _oldColleagues) == -1) {
                js->addColleague(*e) ;
                
            }
        }
    }

    return js ;
}


vector<Job*> Employee::searchForJobs(vector<Job*> &list, const vector<string> skills)
{
    vector<Job*> jobs ;
    vector<pair<int, Job*>> jobsAndSkills ;

    bool found ;
    int size = 0 ;

    for (auto j : list) {
        size = 0 ;

        // Checks wether there are skills in common between skills and j->getSkills
        for (unsigned int i = 0; i < j->getSkills().size(); i++) {
            found = find(skills.begin(), skills.end(), j->getSkills()[i]) != skills.end() ;
            if (found) size++ ;
        }
        if (size > 0) jobsAndSkills.push_back(make_pair(size, j)) ; 
    }

    // Sort the jobs (ascending order) according to the size of their skills vector they have in common with skills
    sort(jobsAndSkills.begin(), jobsAndSkills.end()) ;
    
    // Get only jsAndSkills.second by descending order
    for (int i = jobsAndSkills.size() - 1; i >= 0 ; i--) jobs.push_back(jobsAndSkills[i].second);

    return jobs ;
}

vector<Job*> Employee::searchForJobs(vector<Job*> &list, const vector<string> skills, string zipcode)
{
    vector<Job*> jobs ;
    vector<pair<int, Job*>> jobsAndSkills ;

    bool found ;
    int size = 0 ;

    for (auto j : list) {
        size = 0 ;

        if (!j->getCompany().getZipcode().compare(zipcode)) {
            
            // Checks wether there are skills in common between skills and j->getSkills
            for (unsigned int i = 0; i < j->getSkills().size(); i++) {
                found = find(skills.begin(), skills.end(), j->getSkills()[i]) != skills.end() ;
                if (found) size++ ;
            }
            if (size > 0) jobsAndSkills.push_back(make_pair(size, j)) ;
        }

       
    } 
    
    // Sort the jobs (ascending order) according to the size of their skills vector they have in common with skills
    sort(jobsAndSkills.begin(), jobsAndSkills.end()) ;
    
    // Get only jsAndSkills.second by descending order
    if (jobsAndSkills.size() > 0) {
        for (int i = jobsAndSkills.size() - 1; i >= 0 ; i--) jobs.push_back(jobsAndSkills[i].second);
    }

    return jobs ;
}

vector<Employee*> Employee::searchForOldColleagues(Company &company)
{
    vector<Employee*> colleagues ;

    for (auto e : _oldColleagues) {
        if (e->getCompany().getId() == company.getId() && getIndex(e->getId(), _oldColleagues) != -1) colleagues.push_back(e) ;
    }

    return colleagues ;
}

vector<Employee*> Employee::searchForOldColleagues(vector<Job*> &jobs)
{
    vector<Employee*> colleagues ;
    vector<Job*> resJobs ;

    unsigned int i ;

    for (auto e : _oldColleagues) {
        Company c = e->getCompany() ;
        resJobs = this->searchForJobs(jobs, _skills) ; // Those are the jobs which fit the JobSeeker skills
        
        // We now need to filter the jobs with the company
        i = 0 ;
        while (i < resJobs.size() && resJobs[i]->getCompany().getId() != c.getId() && getIndex(e->getId(), _oldColleagues) != -1) i++ ;
        if (i < resJobs.size()) colleagues.push_back(e) ;
    }

    return colleagues ;
}

Employee& Employee::operator= (const Employee &employee) 
{ 
    _id = employee._id ;
    _name = employee._name ;
    _firstname = employee._firstname ;
    _email = employee._email ;
    _zipcode = employee._zipcode ;
    _skills = employee._skills ;
    _oldColleagues = employee._oldColleagues ;
    _company = employee._company ;

    return *this ;
}
