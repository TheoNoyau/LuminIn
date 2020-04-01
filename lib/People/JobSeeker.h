#ifndef JOBSEEKER_H
#define JOBSEEKER_H

#include <iostream>
#include <string>
#include <vector>

class JobSeeker
{
    public:

    JobSeeker(std::string name, std::string firstname, std::string email, std::string zipcode, std::vector<string> skills, std::vector<int> colleaguesId);
    void createProfile(std::vector<JobSeeker> &list) ;
    void addSkills(std::vector<string> skills) ;
    void addColleague (const &Employee e) ;
    void updateZipcode (std::vector<string> zipcode) ;
    void updateToEmployee () ;
    void deleteProfile(std::vector<JobSeeker> &list) ;
    void createOccupation(std::string title, const std::vector<string> skills) ;
    void deleteOccupation(int id const) ;
    void searchForJobSeekers(const std::vector<string> skills, std::string zipcode = "") ;

    private:

    int _id ;
    std::string _name;
    std::string _zipcode;
    std::string _email;
};

#endif
