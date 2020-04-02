#include "Job.h"

using namespace std ;

Job::Job(std::string title, std::vector<std::string> skills, Company &c) : _title(title), _skills(skills), _company(c)
{
    
}