#pragma once

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <time.h>
#include <thread>

using namespace std;

char buf[4096];
string user;
int i=0;
bool boolean = true;
string error = "error";
string correct = "correct";
int  bytesReceived;
string choiceStr,response = "1",choice;
int clientProcess(int sock,string check);



int clockCheck(clock_t start,string *temp)
{
    while(stoi(*temp)<=0 || stoi(*temp)>=6)
    {
        if((clock()-start)/CLOCKS_PER_SEC >= 10)
        {
            cout << "" <<  endl;
            cout << "Geçerli zaman diliminde bir seçim yapılmadığı için çıkış yapılıyor." << endl;
            exit(1);
        }
        /*if(stoi(*choice)>0 && stoi(*choice)<6){
            break;
        }*/
            
    }
    return 0;
        
}

class Client 
{
    public:
        bool check_number(string str) 
        {
            for (int i = 0; i < str.length(); i++)
                if (isdigit(str[i]) == false)
                    return false;
            return true;
        }

        string clientTransfer(int sock)
        {
            string tarName,tarSurname,noStr,valueStr,targetNo,value;
            
            
                            
            send(sock, choice.c_str(), choice.size() + 1, 0);
            bytesReceived = recv(sock, buf, 4096, 0);
                            
            string oldValue = (string(buf,0, bytesReceived));
            cout << "***Farklı banka ile yapılan işlemlerde $5 işlem ücreti olarak göndericiden alınır.***"<< endl;
            cout<< "" << endl;
            cout << "Hesap Bakiyeniz: $"<< oldValue << endl;
            cout << "Para Gönderilecek Hesap No: ";
            cin >> targetNo;

            if(!check_number(targetNo)){ cout << "Yanlış bir karakter girdiniz!" <<endl; return error;}
                    
            send(sock, targetNo.c_str(), targetNo.size() + 1, 0);
            bytesReceived = recv(sock, buf, 4096, 0);
                            
            cout << "Para Gönderilecek Kişi İsmi: ";
            cin >> tarName;
                            
            send(sock, tarName.c_str(), tarName.size() + 1, 0);
            bytesReceived = recv(sock, buf, 4096, 0);
                            
            cout << "Para Gönderilecek Kişi Soyismi: ";
            cin >> tarSurname;
                            
            send(sock, tarSurname.c_str(), tarSurname.size() + 1, 0);
            bytesReceived = recv(sock, buf, 4096, 0);
                            
            cout << "Göndermek istenen para miktarı: $";
            cin >> value;

            if(!check_number(value)){ cout << "Yanlış bir karakter girdiniz!" <<endl; return error;}
                            
            send(sock, value.c_str(), value.size() + 1, 0);
            bytesReceived = recv(sock, buf, 4096, 0);

            string bakiyeLast = (string(buf,0, bytesReceived));
            int bakiyeInt = stoi(bakiyeLast);
            if(bakiyeInt==-1)
            {
                cout<< "" << endl;
                cout << "Yanlış hesap Bilgileri girildi."<<endl;
                return error;
            }
            else if(bakiyeInt==-2)
            {
                cout << "Hesabınızda yeterli bakiye bulunmamaktadır."<<endl;
                return error;
            }
            else{      
                cout << "Hesap Bakiyeniz: $"<< bakiyeLast << endl;
            }
            return correct;
        }

        string clientWithdraw(int sock)
        {
            string value="0";
            
            send(sock, choice.c_str(), choice.size() + 1, 0);
            bytesReceived = recv(sock, buf, 4096, 0);

             if (bytesReceived == -1 || bytesReceived == 0)
            {
                cout << "Server Disconnected." <<endl;
                return error;
            }

            string oldValue = (string(buf,0, bytesReceived));
            int toplamBakiye = stoi(oldValue);
            do {
                if(stoi(value) > toplamBakiye)
                {
                cout << "Hesabınızda bulunandan daha fazla bir miktar girdiniz!" << endl;
                }
            cout << "Hesap Bakiyeniz: "<< oldValue << endl;
            cout<< ""<< endl;
            cout << "Lütfen çekmek istediğiniz tutarı giriniz: ";
            cin >> value;

            if(!check_number(value)){ cout << "Yanlış bir karakter girdiniz!" <<endl; return error;}

            cout<< "" << endl;
            }while(stoi(value) > toplamBakiye);

            send(sock, value.c_str(), value.size() + 1, 0);
            bytesReceived = recv(sock, buf, 4096, 0);

            if (bytesReceived == -1 || bytesReceived == 0)
            {
                cout << "Server Disconnected." <<endl;
                return error;
            }
                            
                            
            toplamBakiye = stoi((string(buf,0, bytesReceived)));
            if(toplamBakiye != -1) {
                cout << "Hesap Bakiyeniz: " << (string(buf,0, bytesReceived)) <<endl;
            }
            cout<< ""<< endl;
            return correct;
        }

        string clientDeposit(int sock)
        {
            string value;
            
            send(sock, choice.c_str(), choice.size() + 1, 0);
            bytesReceived = recv(sock, buf, 4096, 0);

            if (bytesReceived == -1 || bytesReceived == 0)
            {
                cout << "Server Disconnected." <<endl;
                return error;
            }

            cout << "Hesap Bakiyeniz: "<< (string(buf,0, bytesReceived)) << endl;
            cout<< ""<< endl;
                            
            cout << "Lütfen yatırmak istediğiniz tutarı giriniz: ";
            cin >> value;

            if(!check_number(value)){ cout << "Yanlış bir karakter girdiniz!" <<endl; return error;}

            cout<< ""<< endl;
            send(sock, value.c_str(), value.size() + 1, 0);
            bytesReceived = recv(sock, buf, 4096, 0);

             if (bytesReceived == -1 || bytesReceived == 0)
            {
                cout << "Server Disconnected." <<endl;
                return error;
            }

            cout << "Hesap Bakiyeniz: " << (string(buf,0, bytesReceived)) <<endl;
            cout<< ""<< endl;     
            
            return correct;
        }

        string clientShowInfo(int sock)
        {
            
            send(sock, choice.c_str(), choice.size() + 1, 0);
            for(int i=0;i<5;i++)
            {
                if(i==0)
                {
                    cout << "İsim: ";
                }
                else if(i==1)
                {
                    cout << "Soyisim: ";
                }
                else if(i==2)
                {
                    cout << "Banka Adı: ";
                }
                else if(i==3)
                {
                    cout << "Hesap Numarası: ";
                }else
                {
                    cout << "Hesap Bakiyesi: $";
                                    
                }
                bytesReceived = recv(sock, buf, 4096, 0);

                 if (bytesReceived == -1 || bytesReceived == 0)
                {
                    cout << "Server Disconnected." <<endl;
                    return error;
                }

                cout << string(buf,0, bytesReceived) << endl;
                send(sock, response.c_str(), response.size() + 1, 0);

                

            }
            return correct;
            
        }

        

        int userChoice()
        {

            do 
            {
                cout<< ""<< endl;
                cout << "1-Hesap Bilgilerini Gösterme." << endl;
                cout << "2-Hesaba Para Yatırma." << endl;
                cout << "3-Hesaptan Para Çekme." << endl;
                cout << "4-Başka Hesaba Para Yatırma." << endl;
                cout << "5-Quit." << endl;
                cout<< ""<< endl;
                cout << "Lütfen yapmak istediğiniz işlem numarasını giriniz: ";

                /*
                choice = "-1";
                clock_t start = clock();
                thread thread(clockCheck,start,&choice);    // fail
                thread.detach();*/

                cin >> choice;

                                
                if(!check_number(choice)){ cout << "Yanlış bir karakter girdiniz!" <<endl; return 5;}

                cout<< ""<< endl;

                if(stoi(choice)<=0 || stoi(choice)>=6)
                {
                    cout << "Yanlış bir seçim yapıldı.Yeniden Deneyin."<<endl;
                    cout<< ""<< endl;
                }

            }while(stoi(choice)<=0 || stoi(choice)>=6);

            return stoi(choice);
        }

        static string clientEntryCheck(int sock)
        {
            cout << "Username: ";
		    cin >> user;

            //		Send to server
            int sendRes = send(sock, user.c_str(), user.size() + 1, 0);
            
            if (sendRes == -1 )
            {
                cout << "Could not send to server! Whoops!\r\n";
                return error;
            }

            //		Wait for response
            
            memset(buf, 0, 4096);
            string gelen;
            int bytesReceived = recv(sock, buf, 4096, 0);
            
            //username checking

            cout << "Password: ";
            cin >> user;

            send(sock, user.c_str(), user.size() + 1, 0);
            bytesReceived = recv(sock, buf, 4096, 0);

            clientProcess(sock,(string(buf,0, bytesReceived)));

            return correct;
        }

        string connectToServer()
        {
            //	Create a socket
            int sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock == -1)
            {
                cout << "Can't create socket!" <<endl;
                return error;
            }

            //	Create a hint structure for the server we're connecting with
            int port = 54000;
            string ipAddress = "127.0.0.1";

            sockaddr_in hint;
            hint.sin_family = AF_INET;
            hint.sin_port = htons(port);
            inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

            //	Connect to the server on the socket
            int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
            if (connectRes == -1)
            {
                return error;
            }

            clientEntryCheck(sock);
            

            return correct;
            
        }


};