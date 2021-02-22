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

using namespace std;

class Functions
{
    private:
        struct Bank{
            
            string name;
            int hesapNo;
            int totalAmount;

        };
        
        struct Person{
            string userName;
            string name;
            string surName;
            string password;
            Bank banka;

        };
    
        static Person *dataBase()
        {       
                static Person musteri1;
                static Person musteri2;
                static Person musteri3;
                static Person musteri4;
                static Person musteri5;
                static Person musteri6;

                static Person arrayPerson[6] = {musteri1,musteri2,musteri3 ,musteri4,musteri5,musteri6};
                return arrayPerson;
        }  
    
    public:
        
        static string *returnArray(Person person){
            static string array[5];

            
            array[0] = person.name;
            array[1] = person.surName;
            array[2] = person.banka.name;
            array[3] = to_string(person.banka.hesapNo);
            array[4] = to_string(person.banka.totalAmount);
            return array;
            }
        
        static int userNameCheck(string name)
        {
            Person * arrayPerson;
            arrayPerson = dataBase();
            int tmp =0;

            string isim;
            for(int i=0;i<6;i++){
                isim = (arrayPerson+i)->userName;
                if((name) == (isim)){
                    return 1;
                }
            }
            cout << "Wrong Username" <<endl;
            return 0;
        }
        
        static int userPassCheck(string pass,string name)
        {
            Person * arrayPerson;
            arrayPerson = dataBase();
            int tmp =0;
            
            //cout << arrayPerson->password << endl;
            //cout << (arrayPerson+1)->nameSurname <<endl;
            string password;
            string isim;
            for(int i=0;i<6;i++){
                isim = (arrayPerson+i)->userName;
                if((name) == (isim)){
                    password = (arrayPerson+i)->password;
                    
                    if((pass) == (password)){
                        cout << "Correct Password" <<endl;
                        cout << "Login Process Succesfull."<< endl;
                        return 1;
                    }
                }
            }
            cout << "Wrong Password" <<endl;
            cout << "Login Failed."<< endl;
            return 0;
        }
        
        static string *showAccountInfo(string userName){
            Person *p;

            p=dataBase();

            string isim,*array;

            for(int i=0;i<6;i++){

                isim = (p+i)->userName;

                if((userName) == (isim)){

                    array = returnArray(*(p+i));
                    
                    return array;
                    
                }
            }
            return 0;
        }
        
        static int deposit(string username,int value){

            Person *p;


            p=dataBase();
            string isim;

            for(int i=0;i<6;i++){

                isim = (p+i)->userName;

                if((username) == (isim)){

                    (p+i)->banka.totalAmount += value;
                    
                    return (p+i)->banka.totalAmount;
                    
                }
            }




            return 0;
        }
        
        static int withdraw(string username,int value){
            Person *p;
            p=dataBase();
            string isim;

            for(int i=0;i<6;i++){

                isim = (p+i)->userName;

                if((username) == (isim)){
                    if((p+i)->banka.totalAmount>=value){

                        (p+i)->banka.totalAmount -= value;
                    
                        return (p+i)->banka.totalAmount;
                    }
                    else{
                        return -1;
                    }
                    
                }
            }
            return 0;
        }
        
        static int transfer(string username,int accountNo,string tarName,string tarSurname, int value){

            Person *p;
            p=dataBase();
            string isim,gidenIsim,gidenSoyisim;
            int userValue,bankaNo,gidenValue, islemUcreti = 0;
            int locationUser,locationTar=-1;

            transform(tarName.begin(), tarName.end(),tarName.begin(), ::toupper);
            transform(tarSurname.begin(), tarSurname.end(),tarSurname.begin(), ::toupper);
            
            
            

            for(int i=0;i<6;i++){ //find the user's total value 
                isim = (p+i)->userName;
                if((username) == (isim)){
                    locationUser = i;
                    userValue = (p+i)->banka.totalAmount;
                    break;
                }
            }
            for(int i=0;i<6;i++){
                bankaNo = (p+i)->banka.hesapNo;
                
                gidenIsim = (p+i)->name;
                
                gidenSoyisim = (p+i)->surName;

                transform(gidenIsim.begin(), gidenIsim.end(),gidenIsim.begin(), ::toupper);
                transform(gidenSoyisim.begin(), gidenSoyisim.end(),gidenSoyisim.begin(), ::toupper);
                

                if((accountNo == bankaNo) && (gidenIsim==tarName) && (gidenSoyisim==tarSurname)){
                    locationTar = i;
                    break;
                }
            }
            if(locationTar==-1){
                return -1;
            }
            if((p+locationUser)->banka.name!=(p+locationTar)->banka.name)
                {
                islemUcreti = 5;
                } 
            
            if(userValue >= (value + islemUcreti))
            {
                if (islemUcreti>0)
                {
                    (p+locationUser)->banka.totalAmount = (p+locationUser)->banka.totalAmount - (value+islemUcreti);
                    (p+locationTar)->banka.totalAmount = (p+locationTar)->banka.totalAmount + value;
                    return (p+locationUser)->banka.totalAmount;
                }

                (p+locationUser)->banka.totalAmount = (p+locationUser)->banka.totalAmount - value;
                (p+locationTar)->banka.totalAmount = (p+locationTar)->banka.totalAmount + value;
                return (p+locationUser)->banka.totalAmount;

            }else
            {

                return -2;
            }



        }

        static void addValuesFromTxt(){

            Person * arrayPerson;
            arrayPerson = dataBase();

            string userName,name,surname,password,bankaName;
            int hesapNo,paraValue;
            
            fstream dosyaOku("database.txt");
            string satir = "";

            if ( dosyaOku.is_open() ){
                
                for(int i=0;i<6;i++){

                    dosyaOku >> userName >> name>> surname >> password >> bankaName >> hesapNo >> paraValue; 
                    
                    (arrayPerson+i)->userName = userName;
                    (arrayPerson+i)->name = name;
                    (arrayPerson+i)->surName = surname;
                    (arrayPerson+i)->password = password;
                    (arrayPerson+i)->banka.name = bankaName;
                    (arrayPerson+i)->banka.hesapNo = hesapNo;
                    (arrayPerson+i)->banka.totalAmount = paraValue;
                }
                dosyaOku.close();
            }
            
        }
        
        void addValuesToTxt(){
            Person * arrayPerson;
            arrayPerson = dataBase();

            string userName,name,surname,password,bankaName;
            int hesapNo,paraValue;

            fstream dosyaOku("database.txt",ios::out | ios::ate);
            string satir = "";

            if ( dosyaOku.is_open() ){
                
                for(int i=0;i<6;i++){
                    userName = (arrayPerson+i)->userName ;
                    name = (arrayPerson+i)->name;
                    surname = (arrayPerson+i)->surName;
                    password = (arrayPerson+i)->password;
                    bankaName = (arrayPerson+i)->banka.name;
                    hesapNo = (arrayPerson+i)->banka.hesapNo;
                    paraValue = (arrayPerson+i)->banka.totalAmount;

                    dosyaOku << userName << " "<< name << " " << surname << " "  << password << " "  << bankaName << " "  << hesapNo << " "  << paraValue << endl; 
                }
                dosyaOku.close();
            }

        }
};
