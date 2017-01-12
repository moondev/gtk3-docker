#include <gtk/gtk.h>

static gint sh_cmd (gchar * path, gchar * cmd, gchar * args)
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

   sh_cmd ("/usr/sbin", "midori", NULL);
  //g_print ("Hello World\n");
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Menu");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label ("Browser");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  
  gtk_container_add (GTK_CONTAINER (button_box), button);

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