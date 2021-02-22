//Mehmet Kas


#include "server.h"
#include "functions.h"


Server server;

int serverProcess(int clientSocket)
{
    char buf[4096];
    while (true)
    {
        memset(buf, 0, 4096);
 
        // Wait for client to send data
        
        int bytesReceivedName = recv(clientSocket, buf, 4096, 0);

        if (bytesReceivedName == -1){ f.addValuesToTxt(); cerr << "Error in recv(). Quitting" << endl; break;}
 
        if (bytesReceivedName == 0){ f.addValuesToTxt(); cout << "Client disconnected " << endl; break;}

        name = (string(buf, 0, bytesReceivedName));
        cout << "Trying to Login: " << name << endl;
        

        if(f.userPassCheck(server.tryingToLogin(name,clientSocket,buf),name)) // checking password correct or not
        {
            string choice;
            send(clientSocket, correct.c_str(), correct.size() + 1, 0);
            
            while(true)
            {
                int choiceInt;
                
                string check= server.waitingChoice(clientSocket,buf);

                if(check==error) { break; }
                else{ choiceInt= stoi(check); }
                    

                cout << choiceInt <<endl;
                cout << " " << endl;

                f.addValuesFromTxt();

                string *array;
                array = f.showAccountInfo(name);

                switch (choiceInt)
                {
                    case 1:
                        server.showInfo(clientSocket,array,buf);   //show user's info
                    break;

                    case 2:
                        if(server.deposit(name,clientSocket,array,buf)==error) { break; }; // make deposit
                    break;  

                    case 3:
                        if(server.withdraw(clientSocket,array,buf)==error) { break; }; 
                    break;

                    case 4:
                        if(server.transfer(clientSocket,array,buf)==error) { break; };
                    break;         
                }
            }
        }
        else
        {
            send(clientSocket, error.c_str(), error.size() + 1, 0);
        }
    }
    // Close the socket
    close(clientSocket);
 
    return 0;
}

void Socket()
{
    // Create a socket
    int ServerSocket = server.createServerSocket();

    
    // Wait for a connection
    while(1)
    {      
        f.addValuesFromTxt();
        
        pid_t processId;

        
        // create new socket for every new client
        int clientSocket = server.newSocket(ServerSocket);

        processId = fork();
        //start child processes

        if (processId == 0)
        {   
            serverProcess(clientSocket);
        }
        else if(processId > 0){
            continue;
        }
        else
        {
            cout <<"Error: Fork" << endl;
            break;
        }
            
        
    }
}
   
int main(int argc, char* argv[]){
    
    // Starting Server

        Socket();

    return 0;
}
 
