#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
int main()
{
WORD ver;
WSADATA wsaData;
struct sockaddr_in serverSocketInformation;
int clientSocketDescriptor,r,i,z,len,toRecieve,successCode,rollNumber,lengthOfResponse;
char firstName[21],lastName[21],header[11],responseHeader[11],request[5000],respH[11];
char *resp,*response;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
clientSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(clientSocketDescriptor,(struct sockaddr*)&serverSocketInformation,sizeof(serverSocketInformation));
printf("Enter roll number :");
scanf("%d",&rollNumber);
printf("Enter first name :");
scanf("%s",firstName);
printf("Enter Last name :");
scanf("%s",lastName);
sprintf(request,"%d,%s,%s",rollNumber,firstName,lastName);
printf("String to be sent to server is prepared %s\n",request);
len=strlen(request);
printf("Length of request string is %d\n",len);
sprintf(header,"%-10d",len);
//for(i=0;header[i]!=' ' && header[i]!='\0';i++);
//header[i]='\0';
printf("Header for sending request length to server is prepared \n");
send(clientSocketDescriptor,header,strlen(header)+1,0);
printf("Header sent\n Now sending request string \n");
//for(i=0;request[i]!=' ' && request[i]!='\0';i++);
//request[i]='\0';
send(clientSocketDescriptor,request,strlen(request)+1,0);
printf("Ready to recieve response header \n");
toRecieve=11;
z=0;
while(z<toRecieve)
{
successCode=recv(clientSocketDescriptor,responseHeader,toRecieve-z,0);
printf("Success code to recieved %d \n",successCode);
//strcat(responseHeader,respH);
printf("Reponse header is (%s)\n",responseHeader);
z=z+successCode;
}
responseHeader[toRecieve]='\0';
//for(i=0;responseHeader[i]!='\0' && responseHeader[i]!=' ';i++);
//responseHeader[i]='\0';
printf("Response header recieved is %s\n",responseHeader);
lengthOfResponse=atoi(responseHeader);
printf("Length of response arrived is %d\n",lengthOfResponse);
//resp=(char*)malloc(sizeof(char)*lengthOfResponse);
response=(char*)malloc(sizeof(char)*lengthOfResponse+1);
toRecieve=lengthOfResponse;
z=0;
while(z<toRecieve)
{
successCode=recv(clientSocketDescriptor,response,toRecieve-z,0);
printf("Success code to recieved %d \n",successCode);
//strcat(response,resp);
printf("Response is (%s)\n",response);
z=z+successCode;
}
response[toRecieve]='\0';
//for(i=0;response[i]!='\0' && response[i]!=' ';i++);
printf("Response recieved %s\n",response);
free(resp);
free(response);
closesocket(clientSocketDescriptor);
WSACleanup();
return 0;
}