#include<stdio.h>
#include<string.h>
#include<windows.h>
int main()
{
char request[5000];
char response[5000];
WORD ver;
WSADATA wsaData;
int clientSocketDescriptor;
int serverSocketDescriptor;
struct sockaddr_in serverSocketInformation;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
clientSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(clientSocketDescriptor,(struct sockaddr*)&serverSocketInformation,sizeof(serverSocketInformation));
strcpy(request,"Hello thinking machines. i have ragistered for a course");
send(clientSocketDescriptor,request,strlen(request)+1,0);
recv(clientSocketDescriptor,response,sizeof(response),0);
printf("Response Recieved\n");
printf("%s\n",response);
closesocket(clientSocketDescriptor);
WSACleanup();
return 0;
}