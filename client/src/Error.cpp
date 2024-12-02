#include "../headers/Error.hpp"
#include <system_error>

Error::Error() {

}

Error::Error(const Error &other) {
    this->c_ = other.c_;
}

Error::~Error() {

}

Error& Error::operator=(const Error&other) {
    if(this != &other)
    {
        *this = other;
    }
    return *this;
}

void Error::handleErrorReceived(int errorReceived) {
    switch(errorReceived) {
        case RECEIVE_NAME_LENGTH:
            std::cout << "Error: The name length wasn't receivede properly, not found or invalid" << std::endl;
            break;
        case RECEIVE_NAME:
            std::cout << "Error: The name wasn't received properly, not found or invalid" << std::endl;
            break;
        case RECEIVE_FILE_EXISTS:
            std::cout << "Error: File already exists";
            break;
        case RECEIVE_FILE_FAIL:
            std::cout << "Error: Failed to open file";
            break;
        case RECEIVE_FILE_SIZE:
            std::cout << "Error: File size wasn't receive properly" << std::endl;
            break;
        case RECEIVE_WRITE:
            std::cout << "Error: Receiving buffer didn't go as planned or couldn't write into the file" << std::endl;
    }
}


void Error::handleErrorSend(int errorSend) {
    switch(errorSend) {
        case SEND_FINDING_FILE_SIZE:
            std::cout << "Error: Counldn't find file size" << std::endl;
            break;
        case SEND_FILE_FAIL:
            std::cout << "Error: Failed to open file" << std::endl;
            break;
        case SEND_NAME_LENGTH:
            std::cout << "Error: Cannot find file name size" << std::endl;
            break;
        case SEND_FILE_NAME:
            std::cout << "Error: Cannot send file name" << std::endl;
            break;
        case SEND_FILE_SIZE:
            std::cout << "Error: Couldn't send file size" << std::endl;
            break;
        case SEND_WRITE:
            std::cout << "Error: Sending buffer didn't go as planned or couldn't write into the file" << std::endl;
    }
}
