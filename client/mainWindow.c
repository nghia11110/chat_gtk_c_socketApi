#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "chatWindow.h"

void close_client_soket();
void recv_msg();

void setUsername();
gint label_event(GtkWidget *widget, GdkEventButton *event, \
		gpointer func_data);
gint label_event_1(GtkWidget *widget, GdkEventButton *event, \
		gpointer func_data);
gint label_event_2(GtkWidget *widget, GdkEventButton *event, \
		gpointer func_data);
gint label_event_3(GtkWidget *widget, GdkEventButton *event, \
		gpointer func_data);
gint label_event_4(GtkWidget *widget, GdkEventButton *event, \
		gpointer func_data);
gint label_event_5(GtkWidget *widget, GdkEventButton *event, \
		gpointer func_data);
GdkColor color;
struct ChatMsg *chatmessage_disconnect;

pthread_t recv_Thread;

void mainWindow(){
    int i;
    chatmessage_recv = (struct ChatMsg *)malloc(sizeof(struct ChatMsg));
    memset(chatmessage_recv, 0 , sizeof(struct ChatMsg));

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "mainWindow.glade",NULL);
	window = GTK_WIDGET(gtk_builder_get_object(builder, "listwindow"));

	gtk_signal_connect(GTK_OBJECT(window),"destroy", \
			G_CALLBACK(close_client_soket),NULL);
	gtk_window_set_default_size(GTK_WINDOW(window),250,550);

	label = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
	image = GTK_WIDGET(gtk_builder_get_object(builder, "image1"));

	setUsername(u);

	eventBox = GTK_WIDGET(gtk_builder_get_object(builder, "eventbox1"));
    eventBox1 = GTK_WIDGET(gtk_builder_get_object(builder, "eventbox2"));
    eventBox2 = GTK_WIDGET(gtk_builder_get_object(builder, "eventbox3"));
    eventBox3 = GTK_WIDGET(gtk_builder_get_object(builder, "eventbox4"));
    eventBox4 = GTK_WIDGET(gtk_builder_get_object(builder, "eventbox5"));
    eventBox5 = GTK_WIDGET(gtk_builder_get_object(builder, "eventbox6"));

	gtk_signal_connect(GTK_OBJECT(eventBox),"event", \
			G_CALLBACK(label_event),NULL);

    gtk_signal_connect(GTK_OBJECT(eventBox1),"event", \
            G_CALLBACK(label_event_1),NULL);

    gtk_signal_connect(GTK_OBJECT(eventBox2),"event", \
			G_CALLBACK(label_event_2),NULL);

	gtk_signal_connect(GTK_OBJECT(eventBox3),"event", \
			G_CALLBACK(label_event_3),NULL);

	gtk_signal_connect(GTK_OBJECT(eventBox4),"event", \
			G_CALLBACK(label_event_4),NULL);

	gtk_signal_connect(GTK_OBJECT(eventBox5),"event", \
			G_CALLBACK(label_event_5),NULL);

	printf("mainWindow run!\n");
    for(i=0;i<10;i++)
	 online[i]=0;

	gtk_widget_show_all(window);
	pthread_create(&recv_Thread,NULL, (void *)recv_msg,(void *)socket_fd);

}

void setUsername(char a[20]){
	gtk_label_set_text(GTK_LABEL(label),a);
}

gint label_event(GtkWidget *widget, GdkEventButton *event, \
		gpointer func_data){
	label = GTK_WIDGET(gtk_builder_get_object(builder,"label3"));
	setUsername("123");
	//if (GTK_IS_LABEL(widget) &&(event->type==GDK_2BUTTON_PRESS ||event->type==GDK_3BUTTON_PRESS) ) {
  	if(event->type == GDK_2BUTTON_PRESS || (strcmp(chatmessage_recv->who,u)!= 0 && strcmp(chatmessage_recv->who,"123")==0) ){
		if(online[0]==0)
		 chatInit("123");

	}else if(event->type == GDK_ENTER_NOTIFY){
		gdk_color_parse("#7093DB",&color);
		gtk_widget_modify_bg(eventBox,GTK_STATE_NORMAL,&color);

	}else if(event->type == GDK_LEAVE_NOTIFY){
		//gtk_label_set_text(GTK_LABEL(label),"label leave");
		gdk_color_parse("white",&color);
		gtk_widget_modify_bg(eventBox,GTK_STATE_NORMAL,&color);
		}
  	return FALSE;
}

gint label_event_1(GtkWidget *widget, GdkEventButton *event, \
		gpointer func_data){
	label = GTK_WIDGET(gtk_builder_get_object(builder,"label4"));
	setUsername("456");
	//if (GTK_IS_LABEL(widget) &&(event->type==GDK_2BUTTON_PRESS ||event->type==GDK_3BUTTON_PRESS) ) {
  	if(event->type == GDK_2BUTTON_PRESS || (strcmp(chatmessage_recv->who,u)!= 0 && strcmp(chatmessage_recv->who,"456")==0) ){
		if(online[1]==0)
		chatInit("456");

	}else if(event->type == GDK_ENTER_NOTIFY){
		gdk_color_parse("#7093DB",&color);
		gtk_widget_modify_bg(eventBox1,GTK_STATE_NORMAL,&color);

	}else if(event->type == GDK_LEAVE_NOTIFY){
		//gtk_label_set_text(GTK_LABEL(label),"label leave");
		gdk_color_parse("white",&color);
		gtk_widget_modify_bg(eventBox1,GTK_STATE_NORMAL,&color);
		}

  	return FALSE;
}

gint label_event_2(GtkWidget *widget, GdkEventButton *event, \
		gpointer func_data){
	label = GTK_WIDGET(gtk_builder_get_object(builder,"label5"));
	setUsername("nghia");
	//if (GTK_IS_LABEL(widget) &&(event->type==GDK_2BUTTON_PRESS ||event->type==GDK_3BUTTON_PRESS) ) {
  	if(event->type == GDK_2BUTTON_PRESS || (strcmp(chatmessage_recv->who,u)!= 0 && strcmp(chatmessage_recv->who,"nghia")==0) ){
		if(online[2]==0)
		chatInit("nghia");

	}else if(event->type == GDK_ENTER_NOTIFY){
		gdk_color_parse("#7093DB",&color);
		gtk_widget_modify_bg(eventBox2,GTK_STATE_NORMAL,&color);

	}else if(event->type == GDK_LEAVE_NOTIFY){
		//gtk_label_set_text(GTK_LABEL(label),"label leave");
		gdk_color_parse("white",&color);
		gtk_widget_modify_bg(eventBox2,GTK_STATE_NORMAL,&color);
		}

  	return FALSE;
}

gint label_event_3(GtkWidget *widget, GdkEventButton *event, \
		gpointer func_data){
	label = GTK_WIDGET(gtk_builder_get_object(builder,"label6"));
	setUsername("dat");
	//if (GTK_IS_LABEL(widget) &&(event->type==GDK_2BUTTON_PRESS ||event->type==GDK_3BUTTON_PRESS) ) {
  	if(event->type == GDK_2BUTTON_PRESS || (strcmp(chatmessage_recv->who,u)!= 0 && strcmp(chatmessage_recv->who,"dat")==0) ){
		if(online[3]==0)
		chatInit("dat");

	}else if(event->type == GDK_ENTER_NOTIFY){
		gdk_color_parse("#7093DB",&color);
		gtk_widget_modify_bg(eventBox3,GTK_STATE_NORMAL,&color);

	}else if(event->type == GDK_LEAVE_NOTIFY){
		//gtk_label_set_text(GTK_LABEL(label),"label leave");
		gdk_color_parse("white",&color);
		gtk_widget_modify_bg(eventBox3,GTK_STATE_NORMAL,&color);
		}

  	return FALSE;
}

gint label_event_4(GtkWidget *widget, GdkEventButton *event, \
		gpointer func_data){
	label = GTK_WIDGET(gtk_builder_get_object(builder,"label7"));
	setUsername("123456");
	//if (GTK_IS_LABEL(widget) &&(event->type==GDK_2BUTTON_PRESS ||event->type==GDK_3BUTTON_PRESS) ) {
  	if(event->type == GDK_2BUTTON_PRESS || (strcmp(chatmessage_recv->who,u)!= 0 && strcmp(chatmessage_recv->who,"123456")==0) ){
		if(online[4]==0)
		chatInit("123456");

	}else if(event->type == GDK_ENTER_NOTIFY){
		gdk_color_parse("#7093DB",&color);
		gtk_widget_modify_bg(eventBox4,GTK_STATE_NORMAL,&color);

	}else if(event->type == GDK_LEAVE_NOTIFY){
		//gtk_label_set_text(GTK_LABEL(label),"label leave");
		gdk_color_parse("white",&color);
		gtk_widget_modify_bg(eventBox4,GTK_STATE_NORMAL,&color);
		}

  	return FALSE;
}

gint label_event_5(GtkWidget *widget, GdkEventButton *event, \
		gpointer func_data){
	label = GTK_WIDGET(gtk_builder_get_object(builder,"label8"));
	setUsername("cr7");
	//if (GTK_IS_LABEL(widget) &&(event->type==GDK_2BUTTON_PRESS ||event->type==GDK_3BUTTON_PRESS) ) {
  	if(event->type == GDK_2BUTTON_PRESS || (strcmp(chatmessage_recv->who,u)!= 0 && strcmp(chatmessage_recv->who,"cr7")==0) ){
		if(online[5]==0)
		chatInit("cr7");

	}else if(event->type == GDK_ENTER_NOTIFY){
		gdk_color_parse("#7093DB",&color);
		gtk_widget_modify_bg(eventBox5,GTK_STATE_NORMAL,&color);

	}else if(event->type == GDK_LEAVE_NOTIFY){
		//gtk_label_set_text(GTK_LABEL(label),"label leave");
		gdk_color_parse("white",&color);
		gtk_widget_modify_bg(eventBox5,GTK_STATE_NORMAL,&color);
		}

  	return FALSE;
}
//thread recv message
void recv_msg(){

while(1)
  {
   recv(socket_fd,chatmessage_recv,sizeof(struct ChatMsg),0);
   //printf("recv who =%s \t statusflag=%d \t msg=%s \t to=%s \n",chatmessage_recv->who,chatmessage_recv->Flag,chatmessage_recv->Msg,chatmessage_recv->to_who);
  }

}


//disconnect to server
void close_client_soket(){
    chatmessage_disconnect = (struct ChatMsg *)malloc(sizeof(struct ChatMsg));
    memset(chatmessage_disconnect, 0 , sizeof(struct ChatMsg));
    strcpy(chatmessage_disconnect->to_who,"all");
    strcpy(chatmessage_disconnect->who,u);
	chatmessage_disconnect->Flag = 200;
	strcpy(chatmessage_disconnect->Msg,strcat(u," is now offline!"));
	//memcpy(buf,&chatmessage,60);
	send(socket_fd,chatmessage_disconnect, sizeof(struct ChatMsg),0);
	close(socket_fd);
    //pthread_exit(&recv_Thread);
    gtk_main_quit();
	//gtk_widget_hide(window);
}
