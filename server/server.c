#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sqlite3.h>
#include <unistd.h>
#include <pthread.h>

#define SERVER_PORT 32000
#define SERVER_IP   "127.0.0.1"
#define SERVER_BACK 10
#define BUF_SIZE    128

char client_user[100][10];

//void *sndmsg(void *arg);
void clients_thread();
int authentication_user();
int recv_name_pwd(int client_fd);

struct ChatMsg{
    char who[20];
	int Flag;
	char Msg[50];
	char to_who[20];
};
struct ChatMsg *chatmessage;
struct LoginPack{
	int flag;
	char username[20];
	char password[20];
};
struct threadflag{
	int clientdes;
	int userflag;
};


/* save received username and password */
char unamebuf[BUF_SIZE];
char pwordbuf[BUF_SIZE];
char userMsg[BUF_SIZE];
struct LoginPack *loginmsg;
int loginFlag = 0;
int i;
int send_complete;

pthread_t thread,sndthread;
struct sockaddr_in addr;
int chatmsglen;

int sockfd,bind_fd,client_fd,recv_fd;
pthread_mutex_t mutex;

int main(int argc,char **argv){
	struct sockaddr_in client;
	unsigned int addrlen;

    for(i=0;i<100;i++)
     strcpy(client_user[i],"");
    chatmessage = (struct ChatMsg *)malloc(sizeof(struct ChatMsg));
    memset(chatmessage, 0 , sizeof(struct ChatMsg));
	chatmsglen = sizeof(struct ChatMsg);

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0){
		printf("create socket error!\n");
		exit(1);
	}
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	bind_fd = bind(sockfd,(struct sockaddr*)&addr, sizeof(struct sockaddr));
	if(bind_fd < 0){
		printf("Server Bind error!\n");
		exit(1);
	}

	listen(sockfd, SERVER_BACK);
	printf("server ready!\n");
	while(1){
		addrlen = sizeof(struct sockaddr_in);
		client_fd = accept(sockfd, (struct sockaddr*)&addr, &addrlen);

		if(client_fd == -1){
			printf("accept error!\n");
			return 0;
		}

		if(pthread_create(&thread, NULL, (void *)clients_thread, (void *)client_fd) < 0){
			printf("pthread create error!\n");
		}
	}

	//close(sockfd);

}

int recv_name_pwd(int client_fd){
	/* receive username */
	loginmsg = (struct LoginPack *)malloc(sizeof(struct LoginPack));
	memset(loginmsg, 0 , sizeof(struct LoginPack));
	recv_fd = recv(client_fd, loginmsg, sizeof(struct LoginPack), 0);
	if(recv <= 0){
		printf("receive error!\n");
		return -1;
	}

	strcpy(unamebuf, loginmsg->username);
	strcpy(pwordbuf, loginmsg->password);
	return 0;
}

void clients_thread(){
	short int flag;
	int j;
    char username_thread[50];
    char temp[20];
	/* recv name and pwd */
	if(recv_name_pwd(client_fd) < 0){
		pthread_exit("client_fd exit:recv_name_pwd error!\n");
	}

	if(authentication_user() == 0){
		/* login fail */
		flag = -1;
		flag = htons(flag);
		send(client_fd, &flag, 2, 0);
		pthread_exit("name or pwd error!\n");
	}else{
		/* login success */
		for(i=0;i<100;i++)
		 {
		     if(strcmp(client_user[i],unamebuf)==0)
		       {
		         flag = -2;
		         flag = htons(flag);
		         send(client_fd, &flag, 2, 0);
		         printf("  login not succeed !!!\n");
		         pthread_exit("user logined!\n");
		       }
		 }
		flag = 0;
		flag = htons(flag);
		send(client_fd, &flag,2,0);
		printf("client IP:%s in port:%d \n",inet_ntoa(addr.sin_addr),client_fd);
		strcpy(client_user[client_fd],unamebuf);
		strcpy(username_thread,unamebuf);
	//	printf("%s\n",client_user[client_fd]);
	}

	while(1){
#if 0
	//	fd_set set;
	//	FD_ZERO(set);
	//	FD_SET(client_fd, set);
	//	select(client_fd + 1, set, set, NULL, NULL);
#endif
        send_complete=0;
       for(j=0;j<100;j++)
         if(strcmp(client_user[j],username_thread)==0) break;
        recv(j,chatmessage,chatmsglen,0);
    //  printf("send complete %d\n",send_complete);
      printf("who =%s \t statusflag=%d \t msg=%s \t to=%s \n",chatmessage->who,chatmessage->Flag,chatmessage->Msg,chatmessage->to_who);
      if(chatmessage->Flag == 200){
            for(i=0;i<100;i++)
              {
                  if( strlen(client_user[i])!=0 && strcmp(client_user[i],chatmessage->who)!=0 )
                    send(i, chatmessage, chatmsglen, 0);
                  else continue;
              }
			strcpy(client_user[j],"");
			close(j);
			pthread_exit(NULL);
		}

       if(chatmessage->Flag == 400){
            for(i=0;i<100;i++)
              {
                  if( strlen(client_user[i])!=0 && strcmp(client_user[i],chatmessage->who)!=0 )
                    send(i, chatmessage, chatmsglen, 0);
                  else continue;
              }
		}

      if(chatmessage->Flag==300){
        send(j, chatmessage, chatmsglen, 0);
       }

      if(chatmessage->Flag==100) {
   //    if(strcmp(chatmessage->to_who,chatmessage->who)!=0)
        if(strlen(chatmessage->Msg)<10){
          for(i=0;i<100;i++)
             if(strcmp(client_user[i],chatmessage->to_who)==0 || strcmp(client_user[i],chatmessage->who)==0)
               send_complete++;
          if(send_complete == 2 || strcmp(chatmessage->to_who,chatmessage->who)==0)  //send successful
         {
          for(i=0;i<100;i++)
           {
               if(strcmp(client_user[i],chatmessage->to_who)==0 || strcmp(client_user[i],chatmessage->who)==0)
              {
                if (send(i, chatmessage, chatmsglen, 0) == -1)
               {
                 perror("send");
               }
              }
           }
         }
          if(send_complete < 2 && strcmp(chatmessage->to_who,chatmessage->who)!=0) //send error
          {
            strcpy(temp,chatmessage->who);
            strcpy(chatmessage->who,chatmessage->to_who);
            strcpy(chatmessage->to_who,temp);
            strcpy(chatmessage->Msg," is now offline!!!");
            printf("error send who =%s \t statusflag=%d \t msg=%s \t to=%s \n",chatmessage->who,chatmessage->Flag,chatmessage->Msg,chatmessage->to_who);
            send(j, chatmessage, chatmsglen, 0);

          }
        }
        else
        {
            strcpy(temp,chatmessage->who);
            strcpy(chatmessage->who,chatmessage->to_who);
            strcpy(chatmessage->to_who,temp);
            strcpy(chatmessage->Msg," Msg can't send because too long!!!");
            printf("error send who =%s \t statusflag=%d \t msg=%s \t to=%s \n",chatmessage->who,chatmessage->Flag,chatmessage->Msg,chatmessage->to_who);
            send(j, chatmessage, chatmsglen, 0);
        }
      }

	}
}
/*
void *sndmsg(void *arg){

	struct threadflag *argg;
	argg = (struct threadflag *)arg;
	printf("clientfd = %d\t userflag = %d\n",(*argg).clientdes,(*argg).userflag);
	while(1){

		if(chatmessage->who == (*argg).userflag){
			send((*argg).clientdes,chatmessage->Msg,50,0);
			//printf("i send to %d ,who = %d\n",atoi(unamebuf),chatmessage.who);
		}

		sleep(1);
	}

}
*/

/*
 * Fun name : authentication_user
 * Description: verify user name and password,
 * 	and print result of verify.
 */
int authentication_user(){
	sqlite3 *db;
	char *ErrMsg=0;
	char sql[200];
	int rc;
	int i;
	int nrow=0,ncolumn=0;
	char **Result;

	rc = sqlite3_open("qq.db",&db);
	if(SQLITE_ERROR == rc){
		printf("can't open the database!\n");
		exit(1);
	}
	sprintf(sql, "select * from basicinfo where username='%s' and password='%s';", loginmsg->username, loginmsg->password);
	sqlite3_get_table(db,sql,&Result,&nrow,&ncolumn,&ErrMsg);
	printf("row=%d column=%d\n",nrow,ncolumn);
	printf("result of query is\n");

	for(i=2;i<(nrow+1)*ncolumn;i++){
		printf("Result[%d]=%s\n",i,Result[i]);
	}
	if(nrow==1){
		printf("***user=%s login successful!**\n",unamebuf);
		return 1;
	}else{
		printf("~~~user=%s login failed!~~~\n",unamebuf);
		return 0;
	}
	sqlite3_free_table(Result);
	sqlite3_close(db);
}

