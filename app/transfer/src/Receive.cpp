#include "../headers/Receive.hpp"
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/socket.h>


Receive::Receive() {

}

Receive::Receive(const Receive &other) {
    this->filename_ = other.filename_;
}

Receive::~Receive() {

}

Receive& Receive::operator=(const Receive&other) {
    if(this != &other)
    {
        *this = other;
    }
    return *this;
}

int Receive::receiveBuffer(int fileDescriptor, char* buffer,int bufferSize, int chunkSize) {
    int remainingBytes = 0;
    while(remainingBytes < bufferSize) {
        int bytesReceived =  recv(fileDescriptor, &buffer[remainingBytes], std::min(chunkSize, bufferSize - remainingBytes), 0);

        if(bytesReceived < 0) { return bytesReceived; }
        remainingBytes+=bytesReceived;
    }
    return remainingBytes;
}

std::string Receive::receiveNameFile(int fileDescriptor) {
    int nameLength;
    if (receiveBuffer(fileDescriptor, reinterpret_cast<char*>(&nameLength), sizeof(nameLength)) != sizeof(nameLength)) {
        return "Incorrect name length";
    }

    char* fileName = new char[nameLength + 1];
    memset(fileName, 0, nameLength + 1);

    if (receiveBuffer(fileDescriptor, fileName, nameLength) != nameLength) {
        delete[] fileName;
        return "Error receiving file name";
    }
    return fileName;
}

int64_t Receive::receiveDownloadFile(int fileDescriptor, int chunkSize) {

    int nameLength;
    if (receiveBuffer(fileDescriptor, reinterpret_cast<char*>(&nameLength), sizeof(nameLength)) != sizeof(nameLength)) {
        return -1;
    }

    char* fileName = new char[nameLength + 1];
    memset(fileName, 0, nameLength + 1);

    if (receiveBuffer(fileDescriptor, fileName, nameLength) != nameLength) {
        delete[] fileName;
        return -2;
    }
    char *bufferName = new char[64];
    std::string exePath = getExePath(bufferName);
    exePath.append("/");
    exePath.append(fileName);

    if(fileExists(exePath.c_str())) {
        std::cerr << "File already exists. " << std::strerror(errno) <<std::endl;
        exit(0);
    }
    fs::path filePath = fs::current_path();
    filePath.append(fileName);

    std::ofstream file(filePath, std::ofstream::binary);
    if(file.fail()) { return -1; }

    int64_t fileSize;
    if(receiveBuffer(fileDescriptor, reinterpret_cast<char *>(&fileSize), sizeof(fileSize)) != sizeof(fileSize)) {
        return -2;
    }


    char *buffer = new char[chunkSize];
    bool errored = false;
    int64_t bytesToDownload = fileSize;
    while(bytesToDownload != 0) {
        int receivedBytes = receiveBuffer(fileDescriptor, buffer, std::min(bytesToDownload, (int64_t)chunkSize));
        if((receivedBytes < 0) || !file.write(buffer, receivedBytes)) { errored = true; break; }
        bytesToDownload-=receivedBytes;
    }
    delete[] buffer;
    file.close();

    return errored ? -3 : fileSize;
}

int64_t Receive::receiveFile(int fileDescriptor, int chunkSize) {
    char* buffertest = new char[1024];

    int nameLength;
    if (receiveBuffer(fileDescriptor, reinterpret_cast<char*>(&nameLength), sizeof(nameLength)) != sizeof(nameLength)) {
        return -1;
    }

    char* fileName = new char[nameLength + 1];
    memset(fileName, 0, nameLength + 1);

    if (receiveBuffer(fileDescriptor, fileName, nameLength) != nameLength) {
        delete[] fileName;
        return -2;
    }

    if(fileExists(fileName)) {
        std::cerr << "File already exists. " << std::strerror(errno) <<std::endl;
        exit(0);
    }
    std::string fileReceive;
    fileReceive.append(getExePath(buffertest)); 
    fileReceive.append("/files/");

    std::string filePath = fileReceive.append(fileName);
    std::ofstream file(filePath, std::ofstream::binary);
    if(file.fail()) { return -1; }

    int64_t fileSize;
    if(receiveBuffer(fileDescriptor, reinterpret_cast<char *>(&fileSize), sizeof(fileSize)) != sizeof(fileSize)) {
        return -2;
    }


    char *buffer = new char[chunkSize];
    bool errored = false;
    int64_t bytesToDownload = fileSize;
    while(bytesToDownload != 0) {
        int receivedBytes = receiveBuffer(fileDescriptor, buffer, std::min(bytesToDownload, (int64_t)chunkSize));
        if((receivedBytes < 0) || !file.write(buffer, receivedBytes)) { errored = true; break; }
        bytesToDownload-=receivedBytes;
    }
    delete[] buffer;
    file.close();

    return errored ? -3 : fileSize;
}


fs::path Receive::getExePath(char *buffer) {
    ssize_t count = readlink("/proc/self/exe", buffer, 1024);
    buffer[count] = 0;
    return fs::path(buffer).parent_path();
}

std::string Receive::getCurrentDirectory() {
    return fs::current_path();
}

bool Receive::fileExists(std::string fileName) {
    char *buffer = new char[1024];
    std::string path = getExePath(buffer);
    path.append("/files/");

    for(const auto & entry : fs::directory_iterator(path)) {
        if(strcmp(fileName.c_str(), entry.path().c_str())) {
            return false;
        }
    }
    return true;
}
