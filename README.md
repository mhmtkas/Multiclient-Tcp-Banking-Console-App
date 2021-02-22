## Multiclient-Tcp-Banking-Console-App


   **Application is created on Linux so you can not clearly run on Windows, you have to modify somethings.**

**RUN:** 

*tcpServer.out and tcpClient.out are debugged files and ready to run in its directory with commands:*
```
./tcpServer.out
./tcpClient.out
```

If it doesn't work, you can compile again from tcpServer.cpp and tcpClient.cpp files.
**To Compile:**
```
g++ tcpServer.cpp -o tcpServer.out 

g++ tcpClient.cpp -o tcpClient.out 
```


All infos about users are saved in _database.txt_ in order _username_, _name_, _surname_, _password_, _bankName_, _accountNo_, _amount._

