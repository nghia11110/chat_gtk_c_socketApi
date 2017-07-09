#include "common.h"
#include "chatWindow.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <signal.h>
void show_msg(struct RecvThread *recv_thread);

void chatInit(char a[20]){
	//struct ChatMsg chatmessage;
	GtkWidget *textview1;
    GtkWidget *textview2;
    GtkBuilder *builder1;
    GtkWidget *window1;

    char temp[50];
    struct SendThread *send_thread;
    struct ChatMsg *chatmessage;
    struct RecvThread *recv_thread;
    pthread_t show_thread;
   // int size;
    send_thread=(struct SendThread*)malloc(sizeof(struct SendThread));
    recv_thread=(struct RecvThread*)malloc(sizeof(struct RecvThread));
	chatmessage = (struct ChatMsg *)malloc(sizeof(struct ChatMsg));
    memset(chatmessage, 0 , sizeof(struct ChatMsg));
    //size = sizeof(struct ChatMsg);
    strcpy(chatmessage->to_who,a);
    strcpy(chatmessage->who,u);

    if(strcmp(a,"123")==0) online[0]=1;
    if(strcmp(a,"456")==0) online[1]=1;
    if(strcmp(a,"nghia")==0) online[2]=1;
    if(strcmp(a,"dat")==0) online[3]=1;
    if(strcmp(a,"123456")==0) online[4]=1;
    if(strcmp(a,"cr7")==0) online[5]=1;

	builder1 = gtk_builder_new();
	gtk_builder_add_from_file(builder1,"chatWindow.glade",NULL);
	window1 = GTK_WIDGET(gtk_builder_get_object(builder1,"window1"));

	gtk_signal_connect_object(GTK_OBJECT(window1),"destroy",\
                            G_CALLBACK(chat_window_close),a);

	label = GTK_WIDGET(gtk_builder_get_object(builder1, "label1"));
	strcpy(temp,u);
	strcat(temp,"--->");
	strcat(temp,a);
	gtk_label_set_text(GTK_LABEL(label),temp);

	/* button = GTK_WIDGET(gtk_builder_get_object(builder,"button1"));
	 gtk_signal_connect(GTK_OBJECT(button),"clicked", \
		 	G_CALLBACK(chat_window_close),NULL);
     */
	textview1 = GTK_WIDGET(gtk_builder_get_object(builder1,"textview1"));
	textview2 = GTK_WIDGET(gtk_builder_get_object(builder1,"textview2"));

	button = GTK_WIDGET(gtk_builder_get_object(builder1,"button2"));

     send_thread->msg=chatmessage;
     send_thread->textview=textview2;

	gtk_signal_connect_object(GTK_OBJECT(button),"clicked", \
			G_CALLBACK(sendMsg),send_thread);

	gtk_widget_show_all(window1);

    recv_thread->textview=textview1;
    strcpy(recv_thread->user,a);
	pthread_create(&show_thread,NULL, (void *)show_msg,recv_thread);

}

void sendMsg(struct SendThread *send_thread){
	getMsg(send_thread->textview);
	send_thread->msg->Flag = 100;
	strcpy(send_thread->msg->Msg, chatmsg);
	if(send(socket_fd,send_thread->msg,sizeof(struct ChatMsg), 0)==-1)
	   perror("send");
    //printf("who =%s \t statusflag=%d \t msg=%s \t to=%s \n",chatmessage->who,chatmessage->Flag,chatmessage->Msg,chatmessage->to_who);
	return ;
}

void getMsg(GtkWidget *textview2){
	GtkTextIter start,end;
	textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview2));

	/* get start Iter and end Iter of buffer */
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(textbuffer),&start,&end);

	const GtkTextIter s = start,e = end;
	chatmsg = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(textbuffer), \
			&s,&e,FALSE);/*get text of textbuffer */
	gtk_text_buffer_delete(GTK_TEXT_BUFFER(textbuffer),&start,&end);

}

void chat_window_close(char a[20]){
    printf("gia tri %s\n",a);
	if(strcmp(a,"123")==0) online[0]=0;
	if(strcmp(a,"456")==0) online[1]=0;
	if(strcmp(a,"nghia")==0) online[2]=0;
	if(strcmp(a,"dat")==0) online[3]=0;
	if(strcmp(a,"123456")==0) online[4]=0;
	if(strcmp(a,"cr7")==0) online[5]=0;

	 struct ChatMsg *chatmessage;
	 chatmessage = (struct ChatMsg *)malloc(sizeof(struct ChatMsg));
     memset(chatmessage, 0 , sizeof(struct ChatMsg));
	 strcpy(chatmessage->to_who,a);
     strcpy(chatmessage->who,u);
     chatmessage->Flag=300;
     strcpy(chatmessage->Msg,"");
     send(socket_fd,chatmessage,sizeof(struct ChatMsg), 0);
}

void show_msg( struct RecvThread *recv_thread){
GtkTextMark *mark;
GtkTextIter iter;
char text[100];
	while(1){
		if( (strcmp(chatmessage_recv->who,u)==0 && strcmp(chatmessage_recv->to_who,recv_thread->user)==0)
            || (strcmp(chatmessage_recv->to_who,u)==0 && strcmp(chatmessage_recv->who,recv_thread->user)==0)
           || (strcmp(chatmessage_recv->to_who,"all")==0 && strcmp(chatmessage_recv->who,recv_thread->user)==0) )
        {
		printf("show who =%s \t statusflag=%d \t msg=%s \t to=%s \n\n",chatmessage_recv->who,chatmessage_recv->Flag,chatmessage_recv->Msg,chatmessage_recv->to_who);

        if(chatmessage_recv->Flag==300)
          {
              chatmessage_recv->Flag=100;
              strcpy(chatmessage_recv->who,"");
              pthread_exit(NULL);
          }
		strcpy(text,chatmessage_recv->who);
		strcat(text,":  ");
		strcat(text,chatmessage_recv->Msg);
		strcat(text,"\n");

        textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(recv_thread->textview));
        mark = gtk_text_buffer_get_insert (textbuffer);
        gtk_text_buffer_get_iter_at_mark (textbuffer, &iter, mark);
		gtk_text_buffer_insert(GTK_TEXT_BUFFER(textbuffer),&iter, text, -1);

        strcpy(chatmessage_recv->who,"");

        }
	}
}
