#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main(){
	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1){
		perror("socket");
		return -1;
	}

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(10001);
	inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr.s_addr);
	int conn=connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(conn==-1){
		perror("connect");
		return -2;
	}

	char buff[1024];
	sprintf(buff,"hello world!!\n");
	send(fd,buff,strlen(buff)+1,0);

	close(fd);
}
