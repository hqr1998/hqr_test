#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){

	//create socket to listen
	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1){
		perror("socket");
		return -1;
	
	}

	//bind ip and port information
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(10001);
	addr.sin_addr.s_addr=INADDR_ANY;
	int bd=bind(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(bd==-1){
		perror("bind");
		return -2;
	}

	//set listen
	int li=listen(fd,128);
	if(li==-1){
		perror("listen");
		return -3;
	}

	//create socket to communication
	struct sockaddr_in c_addr;//to save clients' ip information
	int size=sizeof(c_addr);
	int cfd=accept(fd,(struct sockaddr*)&c_addr,&size);
	if(cfd==-1){
		perror("accept");
		return -4;
	}

	//print clients' information
	char ip[32];
	printf("client's IP:%s,port:%d\n",inet_ntop(AF_INET,&c_addr.sin_addr.s_addr,ip,sizeof(ip)),ntohs(c_addr.sin_port));

	//communication
	char buff[1024];
	size_t rec=recv(cfd,buff,sizeof(buff),0);
	if(rec>0){
		printf("serve receive message:%s\n",buff);
	}else if(rec==0){
		printf("client disconnect !!!");
		close(cfd);
		close(fd);
	}else{
		perror("recv");
		return -5;
	}
	return 0;

}
