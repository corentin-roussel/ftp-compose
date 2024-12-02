#include <cstdint>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include <string>

namespace fs = std::filesystem;

class Receive {
private:
    char *filename_;
    char *buffer_;

public:
    Receive();
    Receive(const Receive &other);
    ~Receive();
    Receive& operator=(const Receive&other);

    int receiveBuffer(int fileDescriptor, char *buffer, int bufferSize, int chunkSize = 4*1024);
    std::string receiveNameFile(int fileDescriptor);
    int64_t receiveFile(int fileDescriptor, int chunksize = 64*1024);
    int64_t receiveDownloadFile(int fileDescriptor, int chunkSize = 64*1024);
    fs::path getExePath(char *buffer);
    std::string getCurrentDirectory();
    bool fileExists(std::string fileName);


    char* getBuffer() {
        return buffer_;
    }

    void setBuffer(char* buffer) {
        buffer_ = buffer;
    }
};
