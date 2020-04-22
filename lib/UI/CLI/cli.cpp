#include "cli.h"

#include "People/Company.h"
#include "People/Employee.h"
#include "People/JobSeeker.h"
#include "People/Job.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std ;

Cli::Cli(vector<Company*> &companies, vector<Employee*> &employees, vector<JobSeeker*> &jobSeekers, vector<Job*> &jobs) : _companies(companies), _employees(employees), _jobSeekers(jobSeekers), _jobs(jobs)
{

}

void Cli::wait()
{
	cout << "Press 'q' to continue..." << endl;
	char flag;
	do {
    	cin >> flag;
	} while (flag != 'q');
}

void Cli::printHeader()
{
        cout << "----- " << FWHT("Lumin") << BOLD(FCYN("In")) << " -----" << "\n\n" ;
}

void Cli::printQuitOrReturn()
{
	cout << "\n'q' to quit, 'r' to go back\n" << endl;
}

void Cli::printCompanies(vector<Company*> &companies) 
{
	cout << FWHT("id") << "  -  " << FGRN("Name") << "  -  " << FYEL("Zipcode") << endl ;
	for (unsigned int i = 0; i < companies.size(); i++) {
		cout << KWHT << companies[i]->getId() << RST << "  -  " << KGRN << companies[i]->getName() << RST << "  -  " << KYEL <<  companies[i]->getZipcode() << RST << endl ;
	}
}

void Cli::printEmployees(std::vector<Employee*> &employees)
{
	cout << FWHT("id") << "  -  " << FCYN("Last name") << "  -  " << FYEL("Firstname") << " - " << FGRN("Company") << endl ;
	for (unsigned int i = 0; i < employees.size(); i++) {
		cout << KWHT << employees[i]->getId() << RST << "  -  " << KCYN << employees[i]->getName() << RST << "  -  " << KYEL <<  employees[i]->getFirstname() << RST << "  -  " << KGRN << employees[i]->getCompany().getName() << RST << endl ;
	}
}

void Cli::printJobs(vector<Job*> &jobs) 
{
	cout << FWHT("id") << "  -  " << FMAG("Title") << "  -  " << FGRN("Company") << "  -  " << FBLU("Company e-mail") << "  -  " << FYEL("Company Zipcode") << endl ;
	for (unsigned int i = 0; i < jobs.size(); i++) {
		cout << KWHT << jobs[i]->getId() << RST << " - " << KMAG << jobs[i]->getTitle() << RST << " - " << KGRN <<  jobs[i]->getCompany().getName() << RST << "  -  " << KBLU << jobs[i]->getCompany().getEmail() << RST << "  -  " << KYEL <<  jobs[i]->getCompany().getZipcode() << RST << endl ;
	}
}

void Cli::printJobSeekers(std::vector<JobSeeker*> &jobSeekers)
{
	cout << FWHT("id") << "  -  " << FGRN("Name") << "  -  " << FYEL("Firstname") << "  -  " << FMAG("E-mail") << endl ;
	for (unsigned int i = 0; i < jobSeekers.size(); i++) {
		cout << KWHT << jobSeekers[i]->getId() << RST << "  -  " << KGRN << jobSeekers[i]->getName() << RST << "  -  " << KYEL <<  jobSeekers[i]->getFirstname() << RST << "  -  " << KMAG << jobSeekers[i]->getEmail() << RST << endl ; ;
	}
}

void Cli::printInfoJS(int id)
{
	JobSeeker *js = _jobSeekers[JobSeeker::getIndex(id, _jobSeekers)];
	cout << endl;
	cout << BOLD(FCYN("----------- INFO BOX ----------")) << endl;
	cout << BOLD(FCYN("|")) << endl;
	cout << BOLD(FCYN("|")) << BOLD("Personnal ID: ") << js->getId() << endl;
	cout << BOLD(FCYN("|")) << BOLD("Name: ") << js->getFirstname() << endl;
	cout << BOLD(FCYN("|")) << BOLD("Lastname: ") << js->getName() << endl;
	cout << BOLD(FCYN("|")) << BOLD("Email: ") << js->getEmail() << endl;
	cout << BOLD(FCYN("|")) << BOLD("Zipcode: ") << js->getZipcode() << endl;
	cout << BOLD(FCYN("-------------------------------")) << endl << endl;
}

void Cli::printInfoEmp(int id)
{
	Employee *e = _employees[Employee::getIndex(id, _employees)];
	cout << endl;
	cout << BOLD(FCYN("----------- INFO BOX ----------")) << endl;
	cout << BOLD(FCYN("|")) << endl;
	cout << BOLD(FCYN("|")) << BOLD("Personnal ID: ") << e->getId() << endl;
	cout << BOLD(FCYN("|")) << BOLD("Name: ") << e->getFirstname() << endl;
	cout << BOLD(FCYN("|")) << BOLD("Lastname: ") << e->getName() << endl;
	cout << BOLD(FCYN("|")) << BOLD("Email: ") << e->getEmail() << endl;
	cout << BOLD(FCYN("|")) << BOLD("Zipcode: ") << e->getZipcode() << endl;
	cout << BOLD(FCYN("|")) << BOLD("Company: ") << e->getCompany().getName() << endl;
	cout << BOLD(FCYN("-------------------------------")) << endl << endl;
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
    int id, flag;
	char choice;
    cout << "You are:" << endl;
    cout << "1. A Company" << endl;
    cout << "2. An Employee" << endl;
    cout << "3. A Jobseeker" << endl;
	printQuitOrReturn();
	cout << "Your choice: ";
    cin >> choice;
	if (choice != 'r' && choice != 'q') {
		cout << "Please enter your ID" << endl;
		cin >> id;
	}
	switch (choice) {
		case '1': {
			flag = Company::getIndex(id, _companies);
			if (flag == -1) {
				cout << endl;
				cout << BOLD(FRED("No company corresponding to ID given, please try again")) << endl;
				wait();
				printLogin();
			} else printMenuCompany(id); 
			break;
		}
		case '2': {
			flag = Employee::getIndex(id, _employees);
			if (flag == -1) {
				cout << endl;
				cout << BOLD(FRED("No employee corresponding to ID given, please try again")) << endl;
				wait();
				printLogin();
			} else printMenuEmployee(id); 
			break;
		}
		case '3': {
			flag = JobSeeker::getIndex(id, _jobSeekers);
			if (flag == -1) {
				cout << endl;
				cout << BOLD(FRED("No jobseeker corresponding to ID given, please try again")) << endl;
				wait();
				printLogin();
			} else printMenuJobSeeker(id); 
			break;
		}
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
	cout << BOLD(FBLU("* Employee - Create Profile *")) << endl << endl ;
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
	printCompanies(_companies);
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
	system("clear");
	printHeader() ;
	char choice;
	cout << BOLD(FBLU("* Employee - Menu *")) << endl << endl ;
	printInfoEmp(id);
	cout << UNDL("Your profile:") << endl;
	cout << "1. Add a skill" << endl;
	cout << "2. Add a colleague" << endl;
	cout << "3. Change zipcode" << endl;
	cout << "4. Change company" << endl;
	cout << "5. Transition your profile to Jobseeker status" << endl;
	cout << "6. Delete profile" << endl << endl;
	cout << UNDL("Search: ") << endl;
	cout << "7. Search for a job" << endl;
	cout << "8. Search for a colleague" << endl;
	printQuitOrReturn();
	cout << "Enter your choice: ";
	cin >> choice;
	switch (choice) {
		case '1': {
			system("clear");
			cout << BOLD(FMAG("* Employee - Add Skills *")) << endl << endl ;
			cout << "Enter skills you want to add: (type 'end' to quit)" << endl;
			string skill;
			vector<string> skills;
			while (cin >> skill && skill.compare("end")) {
				skills.push_back(skill);
				cout << "Added " << skill << " to list" << endl;
			}
			_employees[Employee::getIndex(id, _employees)]->addSkills(skills);
			cout << endl;
			cout << BOLD(FGRN("Successfuly added skills")) << endl;
			wait();
			printMenuEmployee(id);
			break;
		}
		case '2':{
			system("clear");
			string ename;
			int colleagueId, flag;
			vector<Employee*> employees;
			cout << BOLD(FMAG("* Employee - Add Colleague *")) << endl << endl ;
			cout << "Search for the lastname of your colleague: ";
			cin >> ename;
			employees = Employee::getEmployees(ename, _employees);
			if (employees.size() != 0){
				printEmployees(employees);
				cout << "Enter the ID of your colleague from the list above: ";
				cin >> colleagueId;
				flag = Employee::getIndex(colleagueId, _employees);
				if (flag == -1){
					cout << endl;
					cout << BOLD(FRED("ID not valid")) << endl;
					wait();
				} else {
					Employee *e = _employees[flag];
					_employees[Employee::getIndex(id, _employees)]->addColleague(*e);
					cout << endl;
					cout << BOLD(FGRN("Successfuly added ")) << "\x1B[1m" << e->getFirstname() << RST << " " << "\x1B[1m" << e->getName() << RST << BOLD(FGRN(" as a colleague")) << endl;
					wait();
				}
			} else {
				cout << endl;
				cout << BOLD(FRED("No name corresponding to your search")) << endl;
				wait();
			}
			printMenuEmployee(id);
			break;
		}
		case '3':{
			system("clear");
			cout << BOLD(FMAG("* Employee - Change zipcode *")) << endl << endl ;
			string zipcode;
			cout << "Enter new zipcode: ";
			cin >> zipcode;
			_employees[Employee::getIndex(id, _employees)]->setZipcode(zipcode);
			cout << endl;
			cout << BOLD(FGRN("Succesfuly updated your zipcode")) << endl;
			wait();
			printMenuJobSeeker(id);
			break;
		}
		case '4':{
			system("clear");
			string cname;
			int cid;
			vector<Company*> companies;
			cout << BOLD(FMAG("* Employee -  Change company *")) << endl << endl ;
			cout << "Search for the name of your new company: ";
			cin >> cname;
			companies = Company::getCompanies(cname, _companies);
			if (companies.size() != 0){
				printCompanies(companies);
				cout << "Enter the ID of your new company (see above): ";
				cin >> cid;
				Company *c = _companies[Company::getIndex(cid, _companies)];
				_employees[Employee::getIndex(id, _employees)]->setCompany(*c);
				cout << endl;
				cout << BOLD(FGRN("Succesfuly added you as an employee of ")) << "\x1B[1m" << c->getName() << RST << BOLD(FGRN("!")) << endl;
				wait();
				printMenuEmployee(id);
			} else {
				cout << endl;
				cout << BOLD(FRED("No company corresponding to your search")) << endl;
				wait();
				printMenuEmployee(id);
			}
			break;
		}
		case '5':{
			system("clear");
			cout << BOLD(FMAG("* Employee - Transition *")) << endl << endl ;
			cout << "All your current colleagues will be added to your list of colleagues." << endl;
			cout << BOLD("Are you sure you want to transition to Jobseeker status? (y/n): ");
			char choice; cin >> choice;
			if (choice == 'y') {
				JobSeeker *js = _employees[Employee::getIndex(id, _employees)]->employeeToJobSeeker(_employees, _jobSeekers);
				system("clear");
				cout << BOLD(FGRN("Succesfuly transitioned to Jobseeker status")) << endl;
				wait();
				printMenuJobSeeker(js->getId());
			} else if (choice == 'n') {
				cout << endl;
				cout << BOLD(FGRN("Operation aborted")) << endl;
				wait();
				printMenuEmployee(id);
			}
			break;
		}
		case '6':{
			system("clear");
			cout << BOLD(FMAG("* Employee - Delete Profile *")) << endl << endl ;
			cout << BOLD("Are you sure you want to delete your profile? (y/n): ");
			char choice; cin >> choice;
			if (choice == 'y') {
				_employees[Employee::getIndex(id, _employees)]->deleteProfile(_employees);
				system("clear");
				cout << BOLD(FRED("Succesfuly deleted your profile")) << endl;
				wait();
				printMenu();
			} else if (choice == 'n') {
				cout << endl;
				cout << BOLD(FGRN("Operation aborted")) << endl;
				wait();
				printMenuEmployee(id);
			}
			break;
		}
		case '7':{
			system("clear");
			vector<Job*> jobs;
			cout << BOLD(FMAG("* Employee - Search for available jobs *")) << endl << endl ;
			cout << "Do you want to search by: " << endl;
			cout << "1. Skills" << endl;
			cout << "2. Skills and zipcode" << endl;
			printQuitOrReturn();
			cout << "Enter your choice: ";
			char choice; cin >> choice;
			if (choice == '1'){
				vector<string> skills;
				string skill;
				cout << "Enter a list of skills (type 'end' to quit):" << endl; 
				while(cin >> skill && skill.compare("end")){
					skills.push_back(skill);
				}
				jobs = _employees[Employee::getIndex(id, _employees)]->searchForJobs(_jobs, skills);
				if (jobs.size() == 0){
					cout << endl;
					cout << BOLD(FRED("No job offer corresponding to the set of skills you entered")) << endl;
					wait();
					printMenuEmployee(id);
				}
				else printJobs(jobs);
			} else if (choice == '2'){
				vector<string> skills;
				string skill, zipcode;
				cout << "Enter a list of skills (type 'end' to quit):" << endl; 
				while(cin >> skill && skill.compare("end")){
					skills.push_back(skill);
				}
				cout << "Enter the zipcode area you want to search for: ";
				cin >> zipcode; 
				jobs = _employees[Employee::getIndex(id, _employees)]->searchForJobs(_jobs, skills, zipcode);
				if (jobs.size() == 0) {
					cout << endl;
					cout << BOLD(FRED("No job offer corresponding to the set of skills and zipcode you entered")) << endl;
					wait();
					printMenuEmployee(id);
				}
				else printJobs(jobs);
			} else if (choice == 'q') return;
			else if (choice == 'r') printMenuEmployee(id);
			else {
				cout << endl;
				cout << BOLD(FRED("Error, please try again")) << endl;
				wait();
				printMenuEmployee(id);
			}
			break;
		}
		case '8': {
			system("clear");
			int flag;
			cout << BOLD(FMAG("* Employee - Search for a colleague *")) << endl << endl ;
			cout << "Do you want to search by:" << endl;
			cout << "1. Company" << endl;
			cout << "2. Your personnal skills" << endl;
			printQuitOrReturn();
			cout << "Enter your choice: ";
			char choice; cin >> choice;
			if (choice == '1') {
				cout << "Enter the name of the Company you are interested in: ";
				string cname; cin >> cname;
				vector<Company*> companies = Company::getCompanies(cname, _companies);
				if (companies.size() == 0) {
					cout << endl;
					cout << BOLD(FRED("No company corresponding to name given")) << endl;
					wait();
					printMenuEmployee(id);
				} else {
					printCompanies(companies);
					cout << "Please enter the ID of the Company you are interested in (see above): ";
					int cid; cin >> cid;
					flag = Company::getIndex(cid, _companies);
					if (flag == -1) {
						cout << endl;
						cout << BOLD(FRED("No company corresponding to ID given, please try again")) << endl;
						wait();
						printMenuEmployee(id);
					} else {
						Company *c = _companies[flag];
						vector<Employee*> colleagues = _employees[Employee::getIndex(id, _employees)]->searchForOldColleagues(*c);
						if (colleagues.size() == 0) {
							cout << "You don't have any old colleagues working at " << c->getName() << endl;
							wait();
							printMenuEmployee(id);
						} else {
							cout << "Here is a list of your old colleagues working at " << c->getName() << ": " << endl << endl;
							printEmployees(colleagues);
							wait();
							printMenuEmployee(id);
						}
					}
				}
			} else if (choice == '2'){
				vector<Employee*> colleagues = _employees[Employee::getIndex(id, _employees)]->searchForOldColleagues(_jobs); 
				if (colleagues.size() == 0) {
					cout << "Unfortunately, you don't have any old colleagues working at a Company looking for your skills" << endl;
					wait();
					printMenuJobSeeker(id);
				} else {
					cout << "Search results: " << endl;
					printEmployees(colleagues);
					wait();
					printMenuJobSeeker(id);
				}
			} else if (choice == 'q') return;
			else if (choice == 'r') printMenuEmployee(id);
			else {
				cout << endl;
				cout << BOLD(FRED("Error, please try again")) << endl;
				wait();
				printMenuEmployee(id);
			}
			break;
		}
		case 'q':
			return;	
		case 'r':
			printMenu();
			break;
		default:
			cout << endl;
			cout << BOLD(FRED("Error, please try again")) << endl;
			wait();
			printMenuEmployee(id);
			break;
	}		
}

void Cli::printMenuJobSeeker(int id)
{
	system("clear");
	printHeader() ;
	char choice;
	cout << UNDL(BOLD(FMAG("* Jobseeker - Menu *"))) << endl << endl ;
	printInfoJS(id);
	cout << UNDL("Your profile:") << endl;
	cout << "1. Add a skill" << endl;
	cout << "2. Add a colleague" << endl;
	cout << "3. Change zipcode" << endl;
	cout << "4. Transition your profile to Employee status" << endl;
	cout << "5. Delete profile" << endl << endl;
	cout << UNDL("Search: ") << endl;
	cout << "6. Search for a job" << endl;
	cout << "7. Search for a colleague" << endl;
	printQuitOrReturn();
	cout << "Enter your choice: ";
	cin >> choice;
	switch (choice) {
		case '1': {
			system("clear");
			cout << BOLD(FMAG("* Jobseeker - Add Skills *")) << endl << endl ;
			cout << "Enter skills you want to add: (type 'end' to quit)" << endl;
			string skill;
			vector<string> skills;
			while (cin >> skill && skill.compare("end")) {
				skills.push_back(skill);
				cout << "Added " << skill << " to list" << endl;
			}
			_jobSeekers[JobSeeker::getIndex(id, _jobSeekers)]->addSkills(skills);
			cout << endl;
			cout << BOLD(FGRN("Successfuly added skills")) << endl;
			wait();
			printMenuJobSeeker(id);
			break;
		}
		case '2':{
			system("clear");
			string ename;
			int colleagueId, flag;
			vector<Employee*> employees;
			cout << BOLD(FMAG("* Jobseeker - Add Colleague *")) << endl << endl ;
			cout << "Search for the lastname of your colleague: ";
			cin >> ename;
			employees = Employee::getEmployees(ename, _employees);
			if (employees.size() != 0){
				printEmployees(employees);
				cout << "Enter the ID of your colleague from the list above: ";
				cin >> colleagueId;
				flag = Employee::getIndex(colleagueId, _employees);
				if (flag == -1){
					cout << endl;
					cout << BOLD(FRED("ID not valid")) << endl;
					wait();
					printMenuJobSeeker(id);
				} else {
					Employee *e = _employees[flag];
					_jobSeekers[JobSeeker::getIndex(id, _jobSeekers)]->addColleague(*e);
					cout << endl;
					cout << BOLD(FGRN("Successfuly added ")) << "\x1B[1m" <<e->getFirstname() << RST << " " << "\x1B[1m" << e->getName() << RST << BOLD(FGRN(" as a colleague")) << endl;
					wait();
					printMenuJobSeeker(id);
				}
				
			} else {
				cout << endl;
				cout << BOLD(FRED("No name corresponding to your search")) << endl;
				wait();
			}
			printMenuJobSeeker(id);
			break;
		}
		case '3':{
			system("clear");
			cout << BOLD(FMAG("* Jobseeker - Change zipcode *")) << endl << endl ;
			string zipcode;
			cout << "Enter new zipcode: ";
			cin >> zipcode;
			_jobSeekers[JobSeeker::getIndex(id, _jobSeekers)]->setZipcode(zipcode);
			cout << endl;
			cout << BOLD(FGRN("Succesfuly updated your zipcode")) << endl;
			wait();
			printMenuJobSeeker(id);
			break;
		}
		case '4':{
			system("clear");
			string cname;
			int cid;
			vector<Company*> companies;
			cout << BOLD(FMAG("* Jobseeker -  Transition *")) << endl << endl ;
			cout << "Search for the name of your new company: ";
			cin >> cname;
			companies = Company::getCompanies(cname, _companies);
			if (companies.size() != 0){
				printCompanies(companies);
				cout << "Enter the ID of your new company (see above): ";
				cin >> cid;
				Company *c = _companies[Company::getIndex(cid, _companies)];
				Employee *e = _jobSeekers[JobSeeker::getIndex(id, _jobSeekers)]->jobSeekerToEmployee(_employees, _jobSeekers, *c);
				cout << endl;
				cout << BOLD(FGRN("Succesfuly added you as an employee of ")) << "\x1B[1m" <<c->getName() << RST << BOLD(FGRN("!")) << endl;
				wait();
				printMenuEmployee(e->getId());
			} else {
				cout << endl;
				cout << BOLD(FRED("No company corresponding to your search")) << endl;
				wait();
			}
			printMenuJobSeeker(id);
			break;
		}
		case '5':{
			system("clear");
			cout << BOLD(FMAG("* Jobseeker - Delete Profile *")) << endl << endl ;
			cout << BOLD("Are you sure you want to delete your profile? (y/n): ");
			char choice; cin >> choice;
			if (choice == 'y') {
				_jobSeekers[JobSeeker::getIndex(id, _jobSeekers)]->deleteProfile(_jobSeekers);
				system("clear");
				cout << BOLD(FRED("Succesfuly deleted your profile")) << endl;
				wait();
				printMenu();
			} else if (choice == 'n') {
				cout << endl;
				cout << BOLD(FGRN("Operation aborted")) << endl;
				wait();
				printMenuJobSeeker(id);
			}
			break;
		}
		case '6':{
			system("clear");
			vector<Job*> jobs;
			cout << BOLD(FMAG("* Jobseeker - Search for available jobs *")) << endl << endl ;
			cout << "Do you want to search by: " << endl;
			cout << "1. Skills" << endl;
			cout << "2. Skills and zipcode" << endl;
			printQuitOrReturn();
			cout << "Enter your choice: ";
			char choice; cin >> choice;
			if (choice == '1'){
				vector<string> skills;
				string skill;
				cout << "Enter a list of skills (type 'end' to quit):" << endl; 
				while(cin >> skill && skill.compare("end")){
					skills.push_back(skill);
				}
				jobs = _jobSeekers[JobSeeker::getIndex(id, _jobSeekers)]->searchForJobs(_jobs, skills);
				if (jobs.size() == 0){
					cout << endl;
					cout << BOLD(FRED("No job offer corresponding to the set of skills you entered")) << endl;
					wait();
				}
				else printJobs(jobs);
			} else if (choice == '2'){
				vector<string> skills;
				string skill, zipcode;
				cout << "Enter a list of skills (type 'end' to quit):" << endl; 
				while(cin >> skill && skill.compare("end")){
					skills.push_back(skill);
				}
				cout << "Enter the zipcode area you want to search for: ";
				cin >> zipcode; 
				jobs = _jobSeekers[JobSeeker::getIndex(id, _jobSeekers)]->searchForJobs(_jobs, skills, zipcode);
				if (jobs.size() == 0) {
					cout << endl;
					cout << BOLD(FRED("No job offer corresponding to the set of skills and zipcode you entered")) << endl;
					wait();
				}
				else printJobs(jobs);
			} else if (choice == 'q') return;
			else if (choice == 'r') printMenuJobSeeker(id);
			else {
				cout << endl;
				cout << BOLD(FRED("Error, please try again")) << endl;
				wait();
			}
			printMenuJobSeeker(id);
			break;
		}
		case '7': {
			system("clear");
			int flag;
			cout << BOLD(FMAG("* Jobseeker - Search for a colleague *")) << endl << endl ;
			cout << "Do you want to search by:" << endl;
			cout << "1. Company" << endl;
			cout << "2. Your personnal skills" << endl;
			printQuitOrReturn();
			cout << "Enter your choice: ";
			char choice; cin >> choice;
			if (choice == '1') {
				cout << "Enter the name of the Company you are interested in: ";
				string cname; cin >> cname;
				vector<Company*> companies = Company::getCompanies(cname, _companies);
				if (companies.size() == 0) {
					cout << endl;
					cout << BOLD(FRED("No company corresponding to name given")) << endl;
					wait();
					printMenuJobSeeker(id);
				} else {
					printCompanies(companies);
					cout << "Please enter the ID of the Company you are interested in (see above): ";
					int cid; cin >> cid;
					flag = Company::getIndex(cid, _companies);
					if (flag == -1) {
						cout << endl;
						cout << BOLD(FRED("No company corresponding to ID given, please try again")) << endl;
						wait();
					} else {
						Company *c = _companies[flag];
						vector<Employee*> colleagues = _jobSeekers[JobSeeker::getIndex(id, _jobSeekers)]->searchForOldColleagues(*c);
						if (colleagues.size() == 0) {
							cout << "You don't have any old colleagues working at " << c->getName() << endl;
							wait();
						} else {
							cout << "Here is a list of your old colleagues working at " << c->getName() << ": " << endl << endl;
							printEmployees(colleagues);
							wait();
						}
						printMenuJobSeeker(id);
					}
				}
			} else if (choice == '2'){
				vector<Employee*> colleagues = _jobSeekers[JobSeeker::getIndex(id, _jobSeekers)]->searchForOldColleagues(_jobs); 
				if (colleagues.size() == 0) {
					cout << "Unfortunately, you don't have any old colleagues working at a Company looking for your skills" << endl;
					wait();
				} else {
					cout << "Search results: " << endl;
					printEmployees(colleagues);
					wait();
				}
				printMenuJobSeeker(id);
			} else if (choice == 'q') return;
			else if (choice == 'r') printMenuJobSeeker(id);
			else {
				cout << endl;
				cout << BOLD(FRED("Error, please try again")) << endl;
				wait();
				printMenuJobSeeker(id);
			}
			break;
		}
		case 'q':
			return;	
		case 'r':
			printMenu();
			break;
		default:
			cout << endl;
			cout << BOLD(FRED("Error, please try again")) << endl;
			wait();
			printMenuJobSeeker(id);
			break;
	}

}

