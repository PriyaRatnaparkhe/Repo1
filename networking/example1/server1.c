/* wsa startup function will fill the 
sructure wsaData with necessary information 
jiske bharose aage socket create krne ka kaam kiya jaega. we need to specify version in 2 bytes.



*/

#include<stdio.h>
#include<string.h>
#include<windows.h>
int main()
{
char request[5000];
char response[5000];
WORD ver;
WSADATA wsaData;
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
int successCode;
int len;

ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData); // socket library initialization
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0); // socket created
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));// socket bind
if(successCode<0)
{
printf("Unable to bind socket to port 5050 \n");
WSACleanup();
return 0;
}
listen(serverSocketDescriptor,10); // allowing 10 incomming connections at in parallel
printf("TMServer is ready to accept request on port 5050\n");

len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr*)&clientSocketInformation,&len);
// Due to this line application atak jaegi. 
// jab client side se request aaegi to incomming request will be diverted  to  
// other socket and us socket ka descriptor return kiya jno hamne client sokcet descriptor me pakda 

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
printf("Request arrived\n");
printf("%s\n",request);
}
strcpy(response,"Welcome to thinking machines");
successCode=send(clientSocketDescriptor,response,strlen(response)+1,0);
if(successCode>0)
{
printf("Response send \n");
}
else
{
printf("Unable to send the response\n");
}
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}