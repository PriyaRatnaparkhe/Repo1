#include<stdio.h>
#include<windows.h>
#include<string.h>
int main()
{
char response[5000]; // 5000 is bad we'll change it later on
char request[5000];
WORD ver;
WSADATA wsaData;
int serverSocketDescriptor,clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
int successCode,len;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData); // socket library initialized
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket \n");
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
{
printf("Unable to bind socket to port number 5050\n");
WSACleanup();
return 0;
}
listen(serverSocketDescriptor,10);
printf("TMServer is ready and is listening at port no 5050\n");
len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr*)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept client connection\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
successCode=recv(clientSocketDescriptor,request,sizeof(request),0);
if(successCode>0)
{
printf("Request arrived \n");
printf("%s\n",request);
}
strcpy(response,"<!DOCTYPE html>");
strcat(response,"<html lang='en'>");
strcat(response,"<head>");
strcat(response,"<meta charset='utf-8'>");
strcat(response,"<title>Whatever</title>");
strcat(response,"</head>");
strcat(response,"<body>");
strcat(response,"<h1>Welcome to thinking machines .</h1>");
strcat(response,"</body>");
strcat(response,"</html>");
char header[5000];
strcpy(header,"HTTP/1.1 200 OK\n");
strcat(header,"Content-Type: text/html\n");
// content type : iske bad ek space deke text\html likha h 
strcat(header,"Content-Lengh: ");
// content length : ke bar ek space diya h
char responseLength[11];
sprintf(responseLength,"%d\n",strlen(response)+1);
strcat(header,responseLength);
strcat(header,"\n"); // one line gap
// \n for a line gap 
successCode=send(clientSocketDescriptor,header,strlen(header)+1,0);
successCode=send(clientSocketDescriptor,response,strlen(response)+1,0);
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}