.DEFAULT_GOAL := check

.PHONY: clean

# Efface tout les fichiers temporaires et les produits finaux.
clean:
	rm -rf build

# Crée le répertoire qui accueille les fichiers temporaires et les produits finaux.
build:
	mkdir -p build

# Create Password module

build/password.o: lib/Security/password.cpp lib/Security/password.h
	g++ -Wall -Werror -pedantic -g -c lib/Security/password.cpp -I ./lib -o build/password.o

build/libpassword.a: build/password.o
	ar crs build/libpassword.a build/password.o

# Create Database management module to get and update data
# Change 'SQL.cpp' in 'BDD.cpp' to deal with CSV files instead of a real sql databse

build/BDD.o: lib/DB/SQL.cpp lib/DB/BDD.h lib/People/Company.h lib/People/JobSeeker.h lib/People/Employee.h lib/People/Job.h | build
	g++ -Wall -Werror -pedantic -g -c lib/DB/SQL.cpp -I ./lib -o build/BDD.o

build/libdb.a: build/BDD.o
	ar crs build/libdb.a build/BDD.o

# Create Logs module

build/journal.o: lib/Journal/journal.cpp lib/Journal/journal.h
	g++ -Wall -Werror -pedantic -g -c lib/Journal/journal.cpp -I ./lib -o build/journal.o

build/libjournal.a: build/journal.o
	ar crs build/libjournal.a build/journal.o

# Create 'People' module
# Consists of a set of classes to deal with objects such as Companies, Employees, JobSeekers and Jobs

build/Company.o: lib/People/Company.cpp lib/People/Company.h lib/People/Job.h lib/People/JobSeeker.h lib/People/Employee.h | build
	g++ -Wall -Werror -pedantic -g -c lib/People/Company.cpp -I ./lib -o build/Company.o

build/JobSeeker.o: lib/People/JobSeeker.cpp lib/People/JobSeeker.h lib/People/Company.h lib/People/Job.h lib/People/Employee.h lib/DB/BDD.h | build
	g++ -Wall -Werror -pedantic -g -c lib/People/JobSeeker.cpp -I ./lib -o build/JobSeeker.o

build/Employee.o: lib/People/Employee.cpp lib/People/Employee.h lib/People/Company.h lib/People/JobSeeker.h lib/People/Job.h | build
	g++ -Wall -Werror -pedantic -g -c lib/People/Employee.cpp -I ./lib -o build/Employee.o

build/Job.o: lib/People/Job.cpp lib/People/Job.h lib/People/Company.h | build
	g++ -Wall -Werror -pedantic -g -c lib/People/Job.cpp -I ./lib -o build/Job.o

build/libpeople.a: build/Company.o build/Employee.o build/Job.o build/JobSeeker.o
	ar crs build/libpeople.a build/Company.o build/Employee.o build/Job.o build/JobSeeker.o

# Create Command-Line Interface (CLI) module to interact with the user

build/cli.o: lib/UI/CLI/cli.cpp  lib/Security/password.h lib/UI/CLI/cli.h lib/People/Company.h lib/People/JobSeeker.h lib/People/Employee.h lib/People/Job.h lib/Journal/journal.h | build
	g++ -Wall -Werror -pedantic -g -c lib/UI/CLI/cli.cpp -I ./lib -o build/cli.o

build/libcli.a: build/cli.o
	ar crs build/libcli.a build/cli.o

# Create the test executable (used with 'make check') with all the libraries needed

build/test.o: test/main.cpp lib/Security/password.h lib/People/Company.h lib/People/JobSeeker.h lib/People/Employee.h lib/People/Job.h lib/DB/BDD.h lib/Journal/journal.h | build
	g++ -Wall -Werror -pedantic -g -c test/main.cpp -I ./lib -o build/test.o

build/test: build/test.o build/libpeople.a build/libdb.a build/libjournal.a build/libpassword.a | build
	g++ build/test.o build/libpeople.a build/libdb.a build/libjournal.a -Lbuild/ -lpeople -ldb -lpassword -l sqlite3 -o build/test

# Create the app executable (used with 'make app') with all the libraries needed

build/luminin.o: application/main.cpp lib/UI/CLI/cli.h lib/People/Company.h lib/People/JobSeeker.h lib/People/Employee.h lib/People/Job.h lib/DB/BDD.h lib/Journal/journal.h lib/Security/password.h | build
	g++ -Wall -Werror -pedantic -g -c application/main.cpp -I ./lib -o build/luminin.o
	
build/luminin: build/luminin.o build/libpeople.a build/libdb.a build/libcli.a build/libjournal.a build/libpassword.a | build
	g++ build/luminin.o build/libpeople.a build/libdb.a build/libcli.a build/libjournal.a -Lbuild/ -lpeople -ldb -lcli -lpassword -ljournal -l sqlite3 -o build/luminin

# S'assure de l'existence tout les programmes finaux (application, test, etc.)
# Par exemple : all: build/test build/appli
all: build/test build/luminin

# Lance le programme de test.
check: build/test
	./build/test

# Lance le programme final
app: build/luminin
	./build/luminin
