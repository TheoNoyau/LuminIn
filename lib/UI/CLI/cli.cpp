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
	cout << "Your choice: ";
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
	cout << "Your choice: ";
    cin >> choice;
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
	cout << "Your choice: ";
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
	cout << BOLD(FMAG("* Jobseeker - Create Profile *")) << endl << endl ;
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
	system("clear");
	printHeader() ;
	cout << BOLD(FMAG("* Jobseeker - Menu *")) << endl << endl ;
	cout << "Profile: " << endl;
	cout << "1. Add a skill" << endl;
	cout << "2. Add a colleague" << endl;
	cout << "3. Change zipcode" << endl;
	cout << "4. Transition to jobseeker" << endl;
	cout << "Search for jobs: " << endl;
	cout << "5. Search by skills" << endl;
	cout << "6. Search by skills and zipcode" << endl;
	printQuitOrReturn();
	switch (choice) {
		case '1':
			system("clear");
			cout << BOLD(FMAG("* Jobseeker - Add Skills *")) << endl << endl ;
			cout << "Enter skills you want to add: (type 'end' to quit)" << endl;
			string skill;
			while (cin >> skill && skill.compare('end')) _jobSeekers[JobSeeker::getIndex(id)].skills.push_back(skill);
			printMenuJobSeeker(id);
			break;
		case '2':
			system("clear");
			string name;
			char colleagueId;
			cout << BOLD(FMAG("* Jobseeker - Add Colleague *")) << endl << endl ;
			cout << "Search for the name of your colleague: ";
			cin >> ename;
			// printemployees(ename);
			cout << "Enter the ID of your colleague from the list above: (type 'end' to quit) ";
			while (cin >> colleagueId && colleagueId.compare('end')){
				Employee *e = _employees[Employee::getIndex(stoi(colleagueId))];
				_jobSeekers[JobSeeker::getIndex(id)].colleagues.push_back(e);
			}
			printMenuJobSeeker(id);
			break;
		case '3':
			system("clear");
			cout << BOLD(FMAG("* Jobseeker - Change zipcode *")) << endl << endl ;
			string zipcode;
			cout << "Enter new zipcode: ";
			cin >> zipcode;
			_employees[JobSeeker::getIndex(id)].setZipcode(zipcode);
			printMenuJobSeeker(id);
			break;
		case '4':
			system("clear");
			string cname;
			int cid;
			cout << BOLD(FMAG("* Jobseeker -  Transition *")) << endl << endl ;
			cout << "Search for the name of you new company: ";
			cin >> name;
			cout << "Enter the ID of your new company: ";
			cin >> cid;
			Company *c = _companies[Company::getIndex(cid)];
			Employee *e = _jobSeekers[JobSeeker::getIndex(id)].jobSeekerToEmployee(_employees, _jobSeekers, c);
			cout << "Succesfuly added you as an employee of " << c->getName() << "!" << endl;
			printMenuEmployee(e->getId());
		case '5':
			
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

