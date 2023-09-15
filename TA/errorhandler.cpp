#ifndef ERRORHANDLER_CPP
#define ERRORHANDLER_CPP

#include<string>

using namespace std;

struct ErrorHandler {
    string message;
    bool error;

    ErrorHandler(string _message = "", bool _error = true) {
        message = _message;
        error = _error;
    } 

    ErrorHandler() {}
};

#endif