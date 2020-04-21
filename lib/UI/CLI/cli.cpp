#include "cli.h"

#include "People/Company.h"
#include "People/Employee.h"
#include "People/JobSeeker.h"
#include "People/Job.h"

using namespace std ;

Cli::Cli(vector<Company*> &companies, vector<Employee*> &employees, vector<JobSeeker*> &jobSeekers, vector<Job*> &jobs) : _companies(companies), _employees(employees), _jobSeekers(jobSeekers), _jobs(jobs)
{

}

void Cli::printHeader()
{
        cout << "----- " << FWHT("Lumin") << BOLD(FCYN("In")) << " -----" << "\n\n" ;
}

void Cli::printQuitOrReturn()
{
	cout << "\n'q' to quit, 'r' to go back\n" << endl;
}

void Cli::printCompanies() 
{
	cout << "- Companies List -" << endl ;
	cout << FWHT("id") << " - " << FGRN("Name") << " - " << FYEL("Zipcode") << endl ;
	for (unsigned int i = 0; i < _companies.size(); i++) {
		cout << KWHT << _companies[i]->getId() << RST << " - " << KGRN << _companies[i]->getName() << RST << " - " << KYEL <<  _companies[i]->getZipcode() << RST << endl ;
	}
}

void Cli::printMenu()
{
    system("clear") ;
    printHeader();
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
	cout << "\n'q' to quit\n" << endl; 
    char choice;
    cin >> choice;
	switch (choice) {
		case '1':
			printLogin();
			break;
		case '2':
			printMenuCreateProfile();
			break;
		case 'q':
			return;
		default:
			cout << "Error, please try again" << endl;
			printMenu();
			break;
	}
}

void Cli::printLogin()
{
    system("clear");
	printHeader();
	cout << BOLD(FWHT("* Login *")) << endl << endl ;
    int id;
	char choice;
    cout << "You are:" << endl;
    cout << "1. A Company" << endl;
    cout << "2. An Employee" << endl;
    cout << "3. A Jobseeker" << endl;
	printQuitOrReturn();
    cin >> choice;
    system("clear");
    cout << "Please enter your ID" << endl;
    cin >> id;
	switch (choice) {
		case '1':
			printMenuCompany(id);
			break;
		case '2':
			printMenuEmployee(id);
			break;
		case '3':
			printMenuJobSeeker(id);
			break;
		case 'q':
			return;
		case 'r':
			printMenu();
			break;
		default:
			cout << "Error, please try again" << endl;
			printMenu();
			break;
	}
}

void Cli::printMenuCreateProfile() 
{
	char choice ;
	system("clear") ;
    printHeader();
	cout << BOLD(FWHT("* Register *")) << endl << endl ;
    cout << "You are:" << endl;
    cout << "1. A Company" << endl;
    cout << "2. An Employee" << endl;
    cout << "3. A Jobseeker" << endl;
	printQuitOrReturn() ;
	cin >> choice ;

	switch (choice) {
		case '1': 
			printMenuCreateProfileComp() ;
			break;
		case '2':
			printMenuCreateProfileEmp() ;
			break;
		case '3':
			printMenuCreateProfileJS() ;
			break ;
		case 'q':
			return ;
		case 'r':
			printMenu() ;
			break ;
		default:
			cout << "Error, please try again" << endl ;
			printMenuCreateProfile() ;
			break ;
	}
}

void Cli::printMenuCreateProfileComp() 
{
	string name, zipcode, email ;
	system("clear") ;
	printHeader() ;
	cout << BOLD(FGRN("* Company - Create Company*")) << endl << endl ;
	cout << "Enter a name for your company: " ;
	cin >> name ;
	cout << "Enter zipcode: " ;
	cin >> zipcode ;
	cout << "E-mail adress: " ;
	cin >> email ;

	Company *c = new Company(name, zipcode, email) ;
	c->createProfile(_companies) ;
	printMenuCompany(c->getId());
}

void Cli::printMenuCreateProfileEmp() 
{
	string name, firstname, email, zipcode, skill ;
	int idCompany, companyIndex;
	vector<string> skills ;
	vector<Employee*> colleagues ;
	system("clear") ;
	printHeader() ;
	cout << BOLD(FGRN("* Employee - Create Profile *")) << endl << endl ;
	cout << "Last name: " ;
	cin >> name ;
	cout << "First name: " ;
	cin >> firstname ;
	cout << "E-mail adress: " ;
	cin >> email ;
	cout << "Zipcode: " ;
	cin >> zipcode ;
	cout << "Enter a list of skills: (type 'end' to finish)" << endl;
	while (cin >> skill && skill.compare("end")) {
		cout << skill << " has been added to your skills" << endl ;
		skills.push_back(skill);
	}
	printCompanies();
	cout << "Id of the company you are working for (see above): ";
	cin >> idCompany ;
	while (Company::getIndex(idCompany, _companies) == -1) {
		cout << "Wrong company id" << endl ;
		cout << "Id of the company you are working for (see above): ";
		cin >> idCompany ;
	}

	companyIndex = Company::getIndex(idCompany, _companies) ;
	Company *c = _companies[companyIndex] ;
	Employee *e = new Employee(name, firstname, email, zipcode, skills, colleagues, *c) ;
	e->createProfile(_employees) ;
	printMenuEmployee(e->getId()) ;
}

void Cli::printMenuCreateProfileJS() 
{
	system("clear");
	string name, firstname, email, zipcode, skill;
	vector<string> skills;
	vector<Employee*> colleagues ;
	printHeader() ;
	cout << BOLD(FGRN("* Jobseeker - Create Profile *")) << endl << endl ;
	cout << "Lastname: ";
	cin >> name;
	cout << "Firstname: ";
	cin >> firstname;
	cout << "Email: ";
	cin >> email;
	cout << "Zipcode: ";
	cin >> zipcode;
	cout << "Enter a list of skills: (type 'end' to finish)" << endl;
	while (cin >> skill && skill.compare("end")) {
		cout << skill << " has been added to your skills" << endl ;
		skills.push_back(skill);
	}

	JobSeeker *js = new JobSeeker(name, firstname, email, zipcode, skills, colleagues);
	js->createProfile(_jobSeekers);
	printMenuJobSeeker(js->getId());
}

void Cli::printMenuCompany(int id)
{
	
}

void Cli::printMenuEmployee(int id)
{

}

void Cli::printMenuJobSeeker(int id)
{
	
}

