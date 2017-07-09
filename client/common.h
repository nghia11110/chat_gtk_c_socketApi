#ifndef _COMMON_H
#define _COMMON_H
#include <gtk/gtk.h>

#define BUF_SIZE 128
#define SERVER_PORT 32000
#define SERVER_IP   "127.0.0.1"

GtkBuilder *builder;
GtkBuilder *mainwindow;
GtkWidget *window;
GtkWidget *usernameEntry;
GtkWidget *passwordEntry;
GtkWidget *button;
GtkWidget *label;
GtkWidget *eventBox,*eventBox1,*eventBox2,*eventBox3,*eventBox4,*eventBox5;

GtkWidget *table;
GtkWidget *image;


GtkTextBuffer *textbuffer;


int socket_fd,connect_fd;
struct ChatMsg{
	char who[20];
	int Flag;
	char Msg[50];
	char to_who[20];
};
struct ChatMsg *chatmessage_recv;

struct LoginPack{
	int flag;
	char username[20];
	char password[20];
};
struct SendThread{
    struct ChatMsg *msg;
    GtkWidget *textview;
};
struct RecvThread{
    GtkWidget *textview;
    char user[20];
};

char buf[BUF_SIZE];
char u[10];
gchar *chatmsg;
int online[10];

#endif
