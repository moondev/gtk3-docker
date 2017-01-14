#include <gtk/gtk.h>

static gint 
sh_cmd (gchar * path, gchar * cmd, gchar * args)
{
  gchar     cmd_line[256];
  gchar   **argv;
  gint      argp;
  gint      rc = 0;

  if (cmd == NULL)
    return FALSE;

  if (cmd[0] == '\0')
    return FALSE;

  if (path != NULL)
    chdir (path);

  snprintf (cmd_line, sizeof (cmd_line), "%s %s", cmd, args);

  rc = g_shell_parse_argv (cmd_line, &argp, &argv, NULL);
  if (!rc)
  {
    g_strfreev (argv);
    return rc;
  }

  rc = g_spawn_async (path, argv, NULL,
		      G_SPAWN_STDOUT_TO_DEV_NULL | G_SPAWN_SEARCH_PATH,
		      NULL, NULL, NULL, NULL);

  g_strfreev (argv);

  return rc;
}



static void
print_hello (GtkWidget *widget,
             gpointer   data)
{

  gchar     cmd_line[256];
  gchar   **argv;
  gint      argp;
  gint      rc = 0;

   sh_cmd ("/usr/sbin", "midori", "http://news.ycombinator.com");

}

static void
print_hello2 (GtkWidget *widget,
             gpointer   data)
{

  gchar     cmd_line[256];
  gchar   **argv;
  gint      argp;
  gint      rc = 0;

   sh_cmd ("/usr/sbin", "xfce4-terminal", "--show-borders");
}

static void
print_hello3 (GtkWidget *widget,
             gpointer   data)
{

  gchar     cmd_line[256];
  gchar   **argv;
  gint      argp;
  gint      rc = 0;

   sh_cmd ("/usr/sbin", "mypaint", "-f");
}

static void
run_cmd (GtkWidget *widget,
             gpointer   data)
{

  gchar     cmd_line[256];
  gchar   **argv;
  gint      argp;
  gint      rc = 0;

   sh_cmd ("/usr/sbin", "gedit", "--new-window");
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;


  GtkWidget *button;
  GtkWidget *button_box;
  
  window = gtk_application_window_new (app);
  
  //gtk_window_set_keep_above (GTK_WINDOW (window), TRUE);

  //gtk_window_set_default_size (GTK_WINDOW (window), gdk_screen_width(), 50);

  gtk_window_set_decorated (GTK_WINDOW (window), FALSE);

  //gtk_window_move (GTK_WINDOW (window), 100, gdk_screen_width() - 50);
  
  //gint lp = 0;

  //gtk_window_set_position (GTK_WINDOW (window), lp, lp);

  // gtk_window_move (GtkWindow *window,
  //                 gint x,
  //                 gint y);
  //gtk_window_move (GTK_WINDOW (window), gdk_screen_width() - window_width, gdk_screen_height());


  button_box = gtk_button_box_new (GTK_ORIENTATION_VERTICAL);

  gtk_button_box_set_layout (GTK_CONTAINER (button_box), GTK_BUTTONBOX_SPREAD);

  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label ("Browser");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  
  gtk_container_add (GTK_CONTAINER (button_box), button);

  
  GtkWidget *button2;

  GtkWidget *button3;

  button2 = gtk_button_new_with_label ("Terminal");
  g_signal_connect (button2, "clicked", G_CALLBACK (print_hello2), NULL);
  
  gtk_container_add (GTK_CONTAINER (button_box), button2);

  button3 = gtk_button_new_with_label ("MyPaint");
  g_signal_connect (button3, "clicked", G_CALLBACK (print_hello3), NULL);
  
  gtk_container_add (GTK_CONTAINER (button_box), button3);

  GtkWidget *button4;
  button4 = gtk_button_new_with_label ("Gedit");
  g_signal_connect (button4, "clicked", G_CALLBACK (run_cmd), NULL);
  
  gtk_container_add (GTK_CONTAINER (button_box), button4);


  gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}