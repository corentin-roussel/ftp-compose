#pragma once
#include <iostream>

typedef enum {
    RECEIVE_NAME_LENGTH = -1,
    RECEIVE_NAME = -2,
    RECEIVE_FILE_EXISTS = -3,
    RECEIVE_FILE_FAIL = -4,
    RECEIVE_FILE_SIZE = -5,
    RECEIVE_WRITE = -6
} ErrorReceive;

//typedef enum {
//    SEND_FINDING_FILE_SIZE = -1,
//    SEND_FILE_FAIL = -2,
//    SEND_NAME_LENGTH = -3,
//    SEND_FILE_NAME = -4,
//    SEND_FILE_SIZE = -5,
//    SEND_WRITE= -6
//} ErrorSend;

class Error {
private:
    char c_;

public:
    Error();
    Error(const Error &other);
    ~Error();
    Error& operator=(const Error&other);

    void handleErrorReceived(int errorReceive);
//    void handleErrorSend(int errorSend);
};
