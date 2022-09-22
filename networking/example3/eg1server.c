#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
//char *req
char *request,*token;
const char s[2]=",";
WORD ver;
WSADATA wsaData;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
int valueOfIndex,successCode,requestLength,z,i,toRecieve,len,r,serverSocketDescriptor,clientSocketDescriptor;
char header[11],requestHeader[11],response[13],responseHeader[11];
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
if(clientSocketDescriptor<0)
{
printf("Unable to accept client connection\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}

toRecieve=11;
z=0;
while(z<toRecieve)
{
successCode=recv(clientSocketDescriptor,header,toRecieve-z,0);
//strcat(header,requestHeader);
z=z+successCode;
}
header[toRecieve]='\0';
printf("Request header arrived\n");
//for(i=0;header[i]!='\0' && header[i]!=' ';i++);
//header[i]='\0';
requestLength=atoi(header);
printf("Length of request arriving is %d\n",requestLength);
printf("Ready to recieve request\n");
request=(char*)malloc(sizeof(char)*requestLength+1);
//req=(char*)malloc(sizeof(char)*requestLength+1);
toRecieve=requestLength;
z=0;
while(z<toRecieve)
{
successCode=recv(clientSocketDescriptor,request,toRecieve-z,0);
//strcat(request,req);
z=z+successCode;
}
printf("Request arrived\n");
request[toRecieve]='\0';
printf("%s\n",request);
token=strtok(request, s);
printf("Roll Number is %s\n",token);
token=strtok(NULL,s);
printf("First Name is %s\n",token);
token=strtok(NULL, s);
printf("Last Name is %s\n",token);
strcpy(response,"Data Arrived");
len=strlen(response);
sprintf(responseHeader,"%-10d",len);
printf("Response length %d\n",len);
printf("Response %s\n",response);
printf("Response header (%s)\n",responseHeader);
printf("Length of response header is %d\n",strlen(responseHeader));
successCode=send(clientSocketDescriptor,responseHeader,strlen(responseHeader)+1,0);
printf("Success code server header send is %d\n",successCode);
printf("Header sent \n");
printf("Sending response \n");
successCode=send(clientSocketDescriptor,response,strlen(response)+1,0);
printf("Success code server response send is %d\n",successCode);
printf("Response string sent \n");
//free(req);
free(request);
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}