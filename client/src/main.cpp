#include <cerrno>
#include <netinet/in.h>
#include <numeric>
#include <ostream>
#include <string.h>
#include <string>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include "../../transfer/headers/Send.hpp"
#include "../../transfer/headers/Receive.hpp"

int main(int argc, char* argv[]) {
    int client_socket;
    struct sockaddr_in server_socket;
    int connection;
    Send upload = Send();
    Receive receiving = Receive();

    upload.createDirectory();
    std::vector<std::string> split = upload.split(argv[1],':');

    if(argc != 4) {
        std::cout << "Please use the command appropriately ./lfp ip:port -type filename" << std::endl;
        exit(0);
    }


    if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Problem creating socket" << std::strerror(errno) << std::endl;
        exit(0);
    }

    server_socket.sin_port = htons(atoi(split.at(1).c_str()));
    server_socket.sin_addr.s_addr = INADDR_ANY;
    server_socket.sin_family = AF_INET;

    connection = connect(client_socket, (struct sockaddr *) &server_socket, sizeof(server_socket));
    if(connection < 0) {
        std::cerr << "Problem connecting to socket " << std::strerror(errno) << std::endl;
        exit(0);
    }

    std::string fileName = argv[3];
    bool transmitting = true;

    while(transmitting)
    {
        if(strcmp(argv[2], "-upload") == 0) {
            int type = 1;
            if(send(client_socket, &type, sizeof(type), 0) != sizeof(type)) {
                std::cout << "Check size of type varaible" << std::endl;
                transmitting = false;
            }
            std::cout << "uploading file" << std::endl;
            if(upload.SendFile(client_socket, fileName) < 0) {
                std::cerr << "File couldn't upload" << std::strerror(errno);
                transmitting = false;
            }
            std::cout << "file uploaded" << std::endl;
            transmitting = false;
        }else if (strcmp(argv[2], "-download") == 0) {
            int type = 2;
            if(send(client_socket, reinterpret_cast<char*>(&type), sizeof(type), 0) != sizeof(type)) {
                std::cout << "Check size of type varaible" << std::endl;
                transmitting = false;
            }
            std::cout << "downloading file" << std::endl;
            upload.sendFileNameToDownload(client_socket, fileName);
            if(receiving.receiveDownloadFile(client_socket) < 0) {
                std::cerr << "File couldn't be downloaded" << std::strerror(errno);
                transmitting = false;
            }
            std::cout << "file downloaded" << std::endl;
        }else {
            std::cout << "cannot compare the argv[2]" << std::endl;
        }
    }

    close(client_socket);
    exit(0);

}
