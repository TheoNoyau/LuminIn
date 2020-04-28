#include "journal.h"
#include <time.h>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

string getTimeAndDate()
{
    char time_s[100];
    time_t now = time(0);
    strftime(time_s, 100, "%Y/%m/%d %H:%M:%S", localtime(&now));

    return time_s;
}

void logger(string logpath, string function, vector<string> &args)
 {
    fstream log;
    log.open(logpath, ios::out | ios::app);
    int size = args.size();

    if (size != 0){
        if (size == 1) log << "[" << getTimeAndDate() << "] " << function << "() was called with argument [" << args[0] << "]." << endl;
        else {
            log << "[" << getTimeAndDate() << "] " << function << "() was called with arguments [";
            for (int i = 0; i < size; i++){
                log << args[i];
                if (i == size - 1) log << "].";
                else log << ", ";
            }
            log << endl;
        }
    } else log << "[" << getTimeAndDate() << "] " << function << "() was called." << endl;
}