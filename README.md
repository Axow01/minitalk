# Minitalk
42 Quebec School

# Description
Minitalk is a simple chat system using unix signal. You have a server program that receive the message and a client program that sends it. We were only allowed to use the following signals: SIGUSR1 & SIGUSR2. To solve this problem you need to convert each char of the message into bytes and send each bit. In my case SIGUSR2 = 1 and SIGUSR1 = 0. After sending a byte the server catches it, and rebuild the char using bit shifting. The it prints out the char using the function write();. When all the bits in the byte have been catch, the server sends a signal to the client to confirm the reception of this char. Then the client continue to send the rest of the message. When the message is sent completly the server sends another signal to the client to confirm that all the message is received. To send a char the programs take about 0.092 seconds / chars, in my tests to send 100000 chars the programs take about 1m30.

# Install

1. Compile the project using Make. Do this in the project folder.

	``` make all ```

2. To clean the folder.

	``` make fclean ```

# Usage

1. Start the server program.

	``` ./server ```

2. Start the client program with the pid of the server.

	``` ./client <pid> <message> ```

3. Wait for the server confirmation (It could be long if the message is big).

![How to use the server program](https://i.imgur.com/1WSetqh.gif)

![How to use the client program](https://i.imgur.com/pSlOnWM.gif)

![Server final result](https://i.imgur.com/ycD3YpE.png)

# Credits

I did this project on my own, but this video help me a lot.

<iframe width="800" height="600" src="https://www.youtube.com/embed/83M5-NPDeWs" title="Sending and Handling Signals in C (kill, signal, sigaction)" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>
