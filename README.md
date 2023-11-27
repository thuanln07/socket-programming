# socket-programming
## Real-time-chat-application-in-c
[![Open Source Love](https://img.shields.io/badge/Open%20Source-%E2%9D%A4-red.svg)](https://github.com/thuanln07/socket-programming)

Using Socket programming to make a real-time chatroom in c 

## Note-: 
1.  The above code is tested for Linux, it should work with MAC-OS and windows but is untested. 
2. You may run multiple client instances to test the script

### Chatroom functionality
#####compile

    make

#####usage


| Command       | Parameter             | Desription                          |
| ------------- | --------------------- | ----------------------------------- |
| quit          |                       | Leave the chatroom                  |
| ./client           |  "text from client"               | send the msg to all online users ("use")    |
| ./server           |   "text from server"         | Send the msg to a particular user              |

### Server
Each user is handled by a seperate thread in the server.The threads synchronise access to a global linked list 
storing the user information

### Client
When the client connects to the server, it executes a chatroom shell. Each client has 2 running threads one for sending commands and other for receiving msgs, both working in sync with each other.

### TO DO and Contributions
Feel free to contribute and collaborate 
1. Making a testing environment to check for subtle synchronisation bugs
2. Resolving same user-name conflicts
3. adding feature to change user name
4. BUG-: When a user is typing and at the same moment receives a msg in the chatroom
