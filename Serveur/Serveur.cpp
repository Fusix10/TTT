#include <winsock2.h>
#include <iostream>
#include <vector>
#include <thread>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#pragma comment(lib, "ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define WM_SOCKET_EVENT (WM_USER + 1)
#define SERVEUR_IP 10.1.144.16

struct ClientData {
    SOCKET socket;
    sockaddr_in address;
};

std::vector<std::thread> clientThreads;
std::vector<ClientData> clients;

void somefunction(int v[], int len) {
    std::cout << "vector has " << len << " elements,"
        << " first value is " << v[0] << ","
        << " last value is " << v[len - 1] << std::endl;
}

void handleJson(const char* json, SOCKET clientSocket) {
    rapidjson::Document doc;
    doc.Parse(json);

    if (!doc.HasParseError()) {
        if (doc.IsObject()) {
            if (doc.HasMember("size") && doc["size"].IsInt() &&
                doc.HasMember("x") && doc["x"].IsInt() &&
                doc.HasMember("y") && doc["y"].IsInt()) {
                int size = doc["size"].GetInt();
                int x = doc["x"].GetInt();
                int y = doc["y"].GetInt();

                // Faites quelque chose avec les valeurs (size, x, y)
                std::cout << "Received JSON: size=" << size << ", x=" << x << ", y=" << y << std::endl;

                // Exemple de réponse JSON
                rapidjson::Document response;
                response.SetObject();
                response.AddMember("result", "success", response.GetAllocator());

                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                response.Accept(writer);

                // Envoyer la réponse JSON au client
                send(clientSocket, buffer.GetString(), buffer.GetLength(), 0);
            }
        }
    }
    else {
        std::cerr << "Error parsing JSON: " << doc.GetParseError() << std::endl;
    }
}

void clientHandler(SOCKET clientSocket, sockaddr_in clientAddr) {
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;

    while (true) {
        iResult = recv(clientSocket, recvbuf, DEFAULT_BUFLEN, 0);
        if (iResult > 0) {
            recvbuf[iResult] = '\0';  // Null-terminate the received data

            // Handle JSON data
            handleJson(recvbuf, clientSocket);
        }
        else if (iResult == 0) {
            // La connexion a été fermée
            std::cout << "Client disconnected: " << inet_ntoa(clientAddr.sin_addr) << std::endl;
            closesocket(clientSocket);
            break;
        }
        else {
            // Erreur de réception
            std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            break;
        }
    }
}

void acceptClients(SOCKET listenSocket) {
    while (true) {
        SOCKET clientSocket;
        sockaddr_in clientAddr;
        int addrSize = sizeof(clientAddr);

        clientSocket = accept(listenSocket, (SOCKADDR*)&clientAddr, &addrSize);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }

        std::cout << "Client connected: " << inet_ntoa(clientAddr.sin_addr) << std::endl;

        // Créer un thread pour gérer ce client
        clients.push_back({ clientSocket, clientAddr });
        clientThreads.push_back(std::thread(clientHandler, clientSocket, clientAddr));
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_SOCKET_EVENT:
        printf("j'aime le poulet");
        if (lParam & FD_ACCEPT) {
            SOCKET listenSocket = (SOCKET)wParam;
            printf("j'aime vraiment beaucoup les cuisse d'arno");
            // Accepter de nouveaux clients
            std::thread(acceptClients, listenSocket).detach();
        }
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

int main() {
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 0), &WSAData);

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(4148);

    bind(listenSocket, (SOCKADDR*)&sin, sizeof(sin));
    listen(listenSocket, SOMAXCONN);

    // Création de la fenêtre pour recevoir les messages d'événements de socket
    HWND hwnd = CreateWindowEx(0, L"STATIC", L"AsyncServerWindow", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL);

    // Association de la socket avec la fenêtre pour recevoir les événements
    WSAAsyncSelect(listenSocket, hwnd, WM_SOCKET_EVENT, FD_ACCEPT);
    printf("serveur linked %c\n", sin.sin_addr.s_addr);
    printf("serveur linked %s\n", sin.sin_addr.s_addr);
    printf("serveur linked %l\n", sin.sin_addr.s_addr);
    printf("serveur linked %d\n", sin.sin_addr.s_addr);
    int addrsize = sizeof(sin);

    char* ip = inet_ntoa(sin.sin_addr);

    printf("%s", ip);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Fermer tous les threads et sockets
    for (size_t i = 0; i < clients.size(); ++i) {
        closesocket(clients[i].socket);
        clientThreads[i].join();
    }

    closesocket(listenSocket);
    WSACleanup();

    return 0;
}
