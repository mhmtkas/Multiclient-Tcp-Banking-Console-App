//Mehmet Kas

#include "client.h"

Client client;


int clientProcess(int sock,string check)
{
    //	While loop:
    
    do 
    {
            //connecting and username/password checking
            if ( check == correct)
            {
                cout << ""<< endl;
                cout << "--Giriş İşlemi Başarılı--" << endl;
                
                boolean=false;
                bool control=true;
                do
                {
                    switch(client.userChoice()) 
                    {
                        case 1:
                            client.clientShowInfo(sock);
                        break;

                        case 2:
                            if(client.clientDeposit(sock)==error) { control = false; };
                        break;

                        case 3:
                            if(client.clientWithdraw(sock)==error) { control = false; };
                        break;

                        case 4:
                        {
                            if(client.clientTransfer(sock)==error) { control = false; };
                        }
                        break;

                        case 5:
                        {
                            cout << "Çıkış Yapılıyor.." << endl;
                            close(sock);
                            return 0;
                        }
                        break;
                    }
                
                }while(control);
            

            }else{

                cout << "Kullanıcı Girişi Başarısız! Kullanıcı adı veya parola hatalı." << endl;
                break;

            }

        
    } while(boolean);

    //	Close the socket
    cout << "Çıkış Yapılıyor.." << endl;
    close(sock);
    return 0;
    
}


int main()
{
    client.connectToServer();
    
	
}
