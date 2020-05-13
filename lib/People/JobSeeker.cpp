#include <algorithm>

#include "JobSeeker.h"

#include "Company.h"
#include "Employee.h"
#include "Job.h"

#include "DB/BDD.h"

using namespace std;

JobSeeker::JobSeeker(string name, string firstname, string email, string zipcode, vector<string> skills, vector<Employee*> &colleagues) : _name(name), _firstname(firstname), _email(email), _zipcode(zipcode), _skills(skills), _oldColleagues(colleagues)
{

}

int JobSeeker::getIndex(const int id, vector<JobSeeker*> jobSeekers)
{
    int size = jobSeekers.size() ;
    
    for (int i = 0; i < size; i++) {
        if (jobSeekers[i]->getId() == id) return i ;
    }

    return -1; 
}

int JobSeeker::getId() 
{
    return _id ;
}

string JobSeeker::getName()
{
    return _name;
}

string JobSeeker::getFirstname()
{
    return _firstname;
}

string JobSeeker::getEmail()
{
    return _email;
}

string JobSeeker::getZipcode()
{
    return _zipcode;
}

vector<string> JobSeeker::getSkills()
{
    return _skills;
}

vector<Employee*> &JobSeeker::getColleagues()
{
    return _oldColleagues;
}

void JobSeeker::setId(int id)
{
    _id = id;
}

void JobSeeker::setId(vector<JobSeeker*> &list)
{
    _id = (int)list.size() + 1 ;
}

void JobSeeker::setZipcode(string zipcode)
{
    _zipcode = zipcode ;
}

void JobSeeker::createProfile(vector<JobSeeker*> &list)
{
    // Giving an id to the object
    setId(list) ;

    // Adding to the global vector of JobSeekers of the app
    list.push_back(this) ;
}

void JobSeeker::addSkills(vector<string> skills)
{
    for (unsigned int i = 0; i < skills.size(); i++) {
        _skills.push_back(skills[i]) ;
    }
}

int JobSeeker::addColleague(Employee &e)
{
    if (Employee::getIndex(e.getId(), _oldColleagues) != -1) return -1 ;
    _oldColleagues.push_back(&e) ;
    return 0 ;
}

Employee* JobSeeker::jobSeekerToEmployee(vector<Employee*> &employees, vector<JobSeeker*> &jobseekers, Company& company)
{
    Employee* employee = new Employee (_name, _firstname, _email, _zipcode, _skills, _oldColleagues, company) ;
    employee->createProfile(employees, "") ;

    this->deleteProfile(jobseekers) ;

    return employee ;
}

void JobSeeker::deleteProfile(vector<JobSeeker*> &list)
{
    auto it = list.begin() + JobSeeker::getIndex(_id, list) ;
    delete * it ;
    list.erase(it) ;
}

vector<Job*> JobSeeker::searchForJobs(vector<Job*> &list, const vector<string> skills)
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

vector<Job*> JobSeeker::searchForJobs(vector<Job*> &list, const vector<string> skills, string zipcode)
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
    for (int i = jobsAndSkills.size() - 1; i >= 0 ; i--) jobs.push_back(jobsAndSkills[i].second);

    return jobs ;
}

vector<Employee*> JobSeeker::searchForOldColleagues(Company &company)
{
    vector<Employee*> colleagues ;

    for (auto e : _oldColleagues) {
        if (e->getCompany().getId() == company.getId() && Employee::getIndex(e->getId(), _oldColleagues) != -1) colleagues.push_back(e) ;
    }

    return colleagues ;
}

vector<Employee*> JobSeeker::searchForOldColleagues(vector<Job*> &jobs)
{
    vector<Employee*> colleagues ;
    vector<Job*> resJobs ;

    unsigned int i ;

    for (auto e : _oldColleagues) {
        Company c = e->getCompany() ;
        resJobs = this->searchForJobs(jobs, _skills) ; // Those are the jobs which fit the JobSeeker skills
        
        // We now need to filter the jobs with the company
        i = 0 ;
        while (i < resJobs.size() && resJobs[i]->getCompany().getId() != c.getId() && Employee::getIndex(e->getId(), _oldColleagues) != -1) i++ ;
        if (i < resJobs.size()) colleagues.push_back(e) ;
    }

    return colleagues ;
}

JobSeeker& JobSeeker::operator= (const JobSeeker &js) 
{
    _id = js._id ;
    _name = js._name ;
    _firstname = js._firstname ;
    _email = js._email ;
    _zipcode = js._zipcode ;
    _skills = js._skills ;
    _oldColleagues = js._oldColleagues ;

    return *this ;
}