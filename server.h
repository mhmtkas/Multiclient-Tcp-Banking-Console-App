//Mehmet Kas

#pragma once

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <thread>
#include "functions.h"

using namespace std;

string error = "error";
string correct= "correct";
string name ;
int bytesReceived;
string response = "1";

Functions f;

class Server
{
    public:

        string transfer(int clientSocket, string *array, char *buf)
        {
            f.addValuesFromTxt();

            cout << "***Starting Transfer Process***"<<endl;
            cout << " " << endl;

            send(clientSocket, array[4].c_str(), array[4].size() + 1, 0);
            bytesReceived = recv(clientSocket, buf, 4096, 0);

                        
            int targetNo = stoi(string(buf, 0, bytesReceived));
                        
            send(clientSocket, response.c_str(), response.size() + 1, 0);
            bytesReceived = recv(clientSocket, buf, 4096, 0);
                        

            string tarName = (string(buf, 0, bytesReceived));
                        
            send(clientSocket, response.c_str(), response.size() + 1, 0);
            bytesReceived = recv(clientSocket, buf, 4096, 0);
                        

            string tarSurname = (string(buf, 0, bytesReceived));
                        
            send(clientSocket, response.c_str(), response.size() + 1, 0);
            bytesReceived = recv(clientSocket, buf, 4096, 0);
                        

            int value = stoi(string(buf, 0, bytesReceived));

            int snc = f.transfer(name,targetNo,tarName,tarSurname,value);

            string sncStr = to_string(snc);

            send(clientSocket, sncStr.c_str(), sncStr.size() + 1, 0);

            f.addValuesToTxt();

            return correct;
        }
       
        string withdraw(int clientSocket, string *array, char *buf)
        {
            f.addValuesFromTxt();

            cout << "***Starting Withdraw Process***"<<endl;
            cout << " " << endl;
    
            send(clientSocket, array[4].c_str(), array[4].size() + 1, 0);
            bytesReceived = recv(clientSocket, buf, 4096, 0);

            if (bytesReceived == -1)
            {
                f.addValuesToTxt();
                cerr << "Error in recv(). Quitting" << endl;
                return error;
                
            }
 
            if (bytesReceived == 0)
            {   
                f.addValuesToTxt();
                cout << "Client disconnected " << endl;
                return error;
            }
                        
            int value = stoi(string(buf, 0, bytesReceived));
            int totalValue = f.withdraw(name,value); 
            string valueStr = to_string(totalValue);
                        
            send(clientSocket, valueStr.c_str(), valueStr.size() + 1, 0);
            f.addValuesToTxt();
            return correct;
        }

        string tryingToLogin(string name,int clientSocket, char *buf)
        {
            if(f.userNameCheck(name)){
                cout << "correct username" << endl;
            }
            
            send(clientSocket, correct.c_str(), correct.size() + 1, 0);
            bytesReceived = recv(clientSocket, buf, 4096, 0);
            return (string(buf, 0, bytesReceived));
        }
        
        string waitingChoice(int clientSocket,char *buf)
        {
            cout << "Waiting for choice."<<endl;
            cout << " " << endl;
            int bytesReceivedPass = recv(clientSocket, buf, 4096, 0);

            if (bytesReceivedPass == -1)
            {
                f.addValuesToTxt();
                cerr << "Error in recv(). Quitting" << endl;
                return error;    
            }
            if (bytesReceivedPass == 0)
            {   
                f.addValuesToTxt();
                cout << "Client disconnected " << endl;
                return error;
            }

            return (string(buf, 0, bytesReceivedPass));
        }

        string deposit(string name,int clientSocket, string *array, char *buf)
        {
            f.addValuesFromTxt();
            cout << "***Starting Deposit Process***"<<endl;
            cout << " " << endl;
                        
            send(clientSocket, array[4].c_str(), array[4].size() + 1, 0);
            int bytesReceived = recv(clientSocket, buf, 4096, 0);

            if (bytesReceived == -1)
            {
                f.addValuesToTxt();
                cerr << "Error in recv(). Quitting" << endl;
                return error;   
            }
 
            if (bytesReceived == 0)
            {   
                f.addValuesToTxt();
                cout << "Client disconnected " << endl;
                return error;           
            }
        
            int value = stoi(string(buf, 0, bytesReceived));
            int totalValue = f.deposit(name,value);
            string valueStr = to_string(totalValue);
                        
            send(clientSocket, valueStr.c_str(), valueStr.size() + 1, 0);
            f.addValuesToTxt();
            return correct;
        }
       
        void showInfo(int clientSocket, string *array, char *buf)
        {
            f.addValuesFromTxt();
            
            cout << "***Showing Account Info***"<<endl;
            cout << " " << endl;

            for(int i=0;i<5;i++){       
                send(clientSocket, (array[i]).c_str(), (array[i]).size() + 1, 0);  
                recv(clientSocket, buf, 4096, 0);  
            }
        }
        
        int createServerSocket()
        {
            int ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (ServerSocket == -1)
                {
                    cerr << "Can't create a socket! Quitting" << endl;
                    exit(1);
                }
 
            // Bind the ip address and port to a socket
            sockaddr_in hint;
            hint.sin_family = AF_INET;
            hint.sin_port = htons(54000);
            inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
 
            bind(ServerSocket, (sockaddr*)&hint, sizeof(hint));
 

            listen(ServerSocket, SOMAXCONN);
            cout << "Server is waiting.." << endl;
            return ServerSocket;
        }
        
        int newSocket(int ServerSocket)
        {
            sockaddr_in client;
            socklen_t clientSize = sizeof(client);
            int clientSocket = accept(ServerSocket, (sockaddr*)&client, &clientSize);
        
            char host[NI_MAXHOST];      // Client's remote name
            char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
    
            memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
            memset(service, 0, NI_MAXSERV);
    
            if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
            {
                cout << host << " connected on port " << service << endl;
            }
            else
            {
                inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
                cout << host << " connected on port " << ntohs(client.sin_port) << endl;
            }
            return clientSocket;

        }


};