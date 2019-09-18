#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
FILE *fin;
gint row, colunm;
int ans, a[100][100], used[100][100];
GtkWidget *window, *table, *label, *event_box, *vbox, *hbox, *notebook, *entry, *button, *temp;

void delete_event ( GtkWidget *widget,
					GdkEvent *event,
					gpointer data )
{
	gtk_main_quit ();
}
void close_current_page( GtkButton *button,
						 GtkNotebook *notebook)
{
	gint page = gtk_notebook_current_page (notebook);
	gtk_notebook_remove_page (notebook, page);
}
void calc_event (GtkWidget *widget,
				 gpointer data )
{
	int i, j;
	char s[100], temp[10][50];

	/*分割参数 并运行计算程序*/	
	strcpy(s, gtk_entry_get_text(GTK_ENTRY(data)));
	i = j = 0;
	while(1)
	{
		sscanf(&s[j], " %s", temp[++i]);
		while(s[j] == ' ')j++;
		j += strlen(temp[i]);
		if(s[j] == '\0')break;
	}
	sprintf(s, "./2");
	for(j = 1; j <= i; j ++)
	{
		strcat(s, " ");
		strcat(s, temp[j]);
	}
	printf("%s\n", s);
	system(s);

	/*读入数据*/
	fin = fopen ("data", "r");
	fscanf(fin, "%d%d%d", &ans, &row, &colunm);
	for(i = 1; i <= row; i ++)
		for(j = 1; j <= colunm; j ++)
			fscanf(fin, "%d", &a[i][j]);

	for(i = 1; i <= row; i ++)
		for(j = 1; j <= colunm; j ++)
			fscanf(fin, "%d", &used[i][j]);
	fclose(fin);
	

	/*创建分页*/
	GdkColor color;

	table = gtk_table_new (row, colunm, TRUE);

	sprintf(s, "answer=%d", ans);
	label = gtk_label_new(s);

	button = gtk_button_new_with_label("x");
	g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(close_current_page), notebook);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 3);
	gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 3);

	gtk_notebook_append_page (GTK_NOTEBOOK(notebook), table, hbox);
	/*注意notebook的tab_label并不会随gtk_widget_show_all(notebook)一起show，需要单独show*/	
	gtk_widget_show_all(hbox);

	for(i = 1; i <= row; i ++)
	{
		for(j = 1; j <= colunm; j ++)
		{
			event_box = gtk_event_box_new ();

			color.red = 0xffff;
			color.green = 0xffff;
			if(used[i][j] == 1)
				color.blue = 0x0000;    
			else
				color.blue = 0xffff;

			gtk_widget_modify_bg(event_box,GTK_STATE_NORMAL, &color);
			gtk_table_attach_defaults (GTK_TABLE(table), event_box, j-1, j, i-1, i);

			sprintf(s, "%d", a[i][j]);
			label = gtk_label_new (s);
			gtk_container_add(GTK_CONTAINER(event_box), label);		

			gtk_widget_show (label);
			gtk_widget_show (event_box);
		}
	}
	gtk_widget_show(table);
	gtk_widget_show(window);

	gtk_widget_show_all(notebook);
}
int main(int argc, char *argv[])
{ 

	gtk_init (&argc, &argv); /* 初始化显示环境 */ 

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL); /* 创建一个新的窗口*/
	gtk_signal_connect (GTK_OBJECT (window), "delete_event", GTK_SIGNAL_FUNC (delete_event), NULL);
	
	vbox = gtk_vbox_new(FALSE, 0);
	hbox = gtk_hbox_new(FALSE, 0);
	entry = gtk_entry_new();
	button = gtk_button_new_with_label("get");
	notebook = gtk_notebook_new ();
	gtk_container_add (GTK_CONTAINER(window), vbox);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 3);
	gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 3);
	gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 3);
	gtk_box_pack_start(GTK_BOX(vbox), notebook, FALSE, FALSE, 3);

	gtk_signal_connect (GTK_OBJECT (button), "clicked", GTK_SIGNAL_FUNC (calc_event), (gpointer)entry);
	
	gtk_widget_show(entry);
	gtk_widget_show(button);
	gtk_widget_show(notebook);
	gtk_widget_show(hbox);
	gtk_widget_show(vbox);

	gtk_widget_show(window);


	sleep(1);  

	gtk_main (); /*进入睡眠状态，等待事件激活*/

	return(0); 

}
