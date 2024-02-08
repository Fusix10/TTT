#include <winsock2.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define DEFAULT_BUFLEN 512
#define WM_SOCKET_EVENT (WM_USER + 1)
#include <iostream>
#include "Client.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        // Initialisation des sockets
        WSAAsyncSelect((SOCKET)wParam, hwnd, WM_SOCKET_EVENT, FD_READ | FD_CLOSE);
        break;

    case WM_SOCKET_EVENT:
        // Gestion des événements liés aux sockets
        if (lParam & FD_READ) {
            // Il y a des données à lire
            // Mettez votre code de lecture ici
        }

        if (lParam & FD_CLOSE) {
            // La connexion a été fermée
            // Mettez votre code de gestion de la fermeture ici
        }
        break;

    case WM_DESTROY:
        // Fermeture des sockets et quitter l'application
        WSACleanup();
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

Client::Client()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        MessageBox(NULL, L"Failed to create window", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    // Création de la classe de fenêtre
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"TicTacTeo";

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, L"Failed to create window", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    // Création de la fenêtre
    HWND hwnd = CreateWindowEx(
        0,                              // Style étendu
        L"TicTacTeo",       // Nom de la classe de fenêtre
        L"WSAAsyncSelect Example",      // Titre de la fenêtre
        WS_OVERLAPPEDWINDOW,            // Style de fenêtre
        CW_USEDEFAULT, CW_USEDEFAULT,    // Position de la fenêtre
        800, 600,                        // Taille de la fenêtre
        NULL, NULL,                      // Fenêtre parent et menu
        GetModuleHandle(NULL),           // Instance de l'application
        NULL);                           // Paramètre de création

    if (!hwnd) {
        MessageBox(NULL, L"Failed to create window", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    // Boucle principale du message


    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    verif = getaddrinfo("10.1.144.16", "6666", &hints, &result);

    if (verif != 0) {
        printf("getaddrinfo failed with error: %d\n", verif);
        WSACleanup();
        return;
    }
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        verif = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (verif == SOCKET_ERROR) {
            closesocket(sock);
            sock = INVALID_SOCKET;
        }
    }
}

void Client::Send(int size, int x, int y) {
    // Créer un document JSON
    rapidjson::Document document;
    document.SetObject();

    // Ajouter les données au document
    rapidjson::Value sizeValue;
    sizeValue.SetInt(size);
    document.AddMember("size", sizeValue, document.GetAllocator());

    rapidjson::Value xValue;
    xValue.SetInt(x);
    document.AddMember("x", xValue, document.GetAllocator());

    rapidjson::Value yValue;
    yValue.SetInt(y);
    document.AddMember("y", yValue, document.GetAllocator());

    // Convertir le document JSON en chaîne JSON
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    // Envoyer la chaîne JSON au serveur
    int result = send(sock, buffer.GetString(), buffer.GetLength(), 0);
    if (result == SOCKET_ERROR) {
        printf("Send failed with error: %d\n", WSAGetLastError());
    }
}

char* Client::Lisent() {
    do {
        verif = recv(sock, buffer, sizeof(buffer), 0);
        if (verif > 0)
            printf("Bytes received: %d\n", verif);
        else if (verif == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while (verif > 0);

    return NULL;
}
Client::~Client() {
    closesocket(sock);
    WSACleanup();
}
void Client::Update() {

    MSG msg;
    GetMessage(&msg, NULL, 0, 0);
    TranslateMessage(&msg);
    DispatchMessage(&msg);

}