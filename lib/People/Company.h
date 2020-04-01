#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <string>
#include <vector>

class Company
{
    public:

    Company(std::string name, std::string zipcode, std::string email);
    void createProfile(std::vector<Company> &list) ;
    void deleteProfile(std::vector<Company> &list) ;
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
