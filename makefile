.DEFAULT_GOAL := check

.PHONY: clean

# Efface tout les fichiers temporaires et les produits finaux.
clean:
	rm -rf build

# Crée le répertoire qui accueille les fichiers temporaires et les produits finaux.
build:
	mkdir -p build

build/BDD.o: lib/DB/BDD.cpp lib/DB/BDD.h lib/People/Company.h lib/People/JobSeeker.h lib/People/Employee.h lib/People/Job.h | build
	g++ -Wall -Werror -pedantic -g -c lib/DB/BDD.cpp -I ./lib -o build/BDD.o

build/journal.o: lib/Journal/journal.cpp lib/Journal/journal.h
	g++ -Wall -Werror -pedantic -g -c lib/Journal/journal.cpp -I ./lib -o build/journal.o

build/libjournal.a: build/journal.o
	ar crs build/libjournal.a build/journal.o

build/Company.o: lib/People/Company.cpp lib/People/Company.h lib/People/Job.h lib/People/JobSeeker.h lib/People/Employee.h | build
	g++ -Wall -Werror -pedantic -g -c lib/People/Company.cpp -I ./lib -o build/Company.o

build/JobSeeker.o: lib/People/JobSeeker.cpp lib/People/JobSeeker.h lib/People/Company.h lib/People/Job.h lib/People/Employee.h lib/DB/BDD.h | build
	g++ -Wall -Werror -pedantic -g -c lib/People/JobSeeker.cpp -I ./lib -o build/JobSeeker.o

build/Employee.o: lib/People/Employee.cpp lib/People/Employee.h lib/People/Company.h lib/People/JobSeeker.h lib/People/Job.h | build
	g++ -Wall -Werror -pedantic -g -c lib/People/Employee.cpp -I ./lib -o build/Employee.o

build/Job.o: lib/People/Job.cpp lib/People/Job.h lib/People/Company.h | build
	g++ -Wall -Werror -pedantic -g -c lib/People/Job.cpp -I ./lib -o build/Job.o

build/libdb.a: build/BDD.o
	ar crs build/libdb.a build/BDD.o

build/libpeople.a: build/Company.o build/Employee.o build/Job.o build/JobSeeker.o
	ar crs build/libpeople.a build/Company.o build/Employee.o build/Job.o build/JobSeeker.o

build/test.o: test/main.cpp lib/People/Company.h lib/People/JobSeeker.h lib/People/Employee.h lib/People/Job.h lib/DB/BDD.h lib/Journal/journal.h | build
	g++ -Wall -Werror -pedantic -g -c test/main.cpp -I ./lib -o build/test.o

build/test: build/test.o build/libpeople.a build/libdb.a build/libjournal.a | build
	g++ build/test.o build/libpeople.a build/libdb.a build/libjournal.a -Lbuild/ -lpeople -ldb -o build/test

build/cli.o: lib/UI/CLI/cli.cpp lib/UI/CLI/cli.h lib/People/Company.h lib/People/JobSeeker.h lib/People/Employee.h lib/People/Job.h lib/Journal/journal.h | build
	g++ -Wall -Werror -pedantic -g -c lib/UI/CLI/cli.cpp -I ./lib -o build/cli.o

build/libcli.a: build/cli.o
	ar crs build/libcli.a build/cli.o
	
build/luminin.o: application/main.cpp lib/UI/CLI/cli.h lib/People/Company.h lib/People/JobSeeker.h lib/People/Employee.h lib/People/Job.h lib/DB/BDD.h lib/Journal/journal.h| build
	g++ -Wall -Werror -pedantic -g -c application/main.cpp -I ./lib -o build/luminin.o
	
build/luminin: build/luminin.o build/libpeople.a build/libdb.a build/libcli.a build/libjournal.a | build
	g++ build/luminin.o build/libpeople.a build/libdb.a build/libcli.a build/libjournal.a -Lbuild/ -lpeople -ldb -lcli -o build/luminin

# S'assure de l'existence tout les programmes finaux (application, test, etc.)
# Par exemple : all: build/test build/appli
all: build/test build/luminin

# Lance le programme de test.
check: build/test
	./build/test

# Lance le programme final
app: build/luminin
	./build/luminin
