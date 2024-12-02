#pragma once
#include <cstdint>
#include <iostream>
#include <linux/limits.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <unistd.h>
#include <limits.h>
#include <vector>
#define __min(a,b)  (((int)(a) < (int)(b)) ? (a) : (b))

namespace fs = std::filesystem;

class Send {
private:
    char* filename_;
    struct stat sb_;
    char buffer_[1024];
    char *pathToFile_;
    const char* fileToCreate_ = "files/";

public:
    Send();
    Send(const Send &other);
    ~Send();
    Send& operator=(const Send&other);

    int sendBuffer(int fileDescriptor, char *buffer, int bufferSize,int chunkSize = 4*1024);
    int sendFileNameToDownload(int fileDescriptor, const std::string filename);
    void createDirectory();
    ssize_t getFileSize(const std::string filename);
    char *getExePath();
    fs::path getExePath(char *buffer);
    std::vector<std::string> split(const std::string& str, char delimiter);
    int64_t SendFile(int fileDescriptor, const std::string fileName, int chunkSize = 64*1024);
    int64_t sendFileFromServer(int fileDescriptor, const std::string fileName, int chunkSize = 64*1024);

    struct stat getSb();
    void setSb(struct stat sb);
    char* getFileName();
    void setFileName(char* filename);
    char* getBuffer();
    void setBuffer(char buffer[]);
    const char* getFileToCreate();
    void setFileToCreate(char * fileName);
    int getChunkSize();
};
