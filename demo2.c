#include <gtk/gtk.h>

static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  GtkApplication *app = GTK_APPLICATION (data);
  GAction *action;
  g_print ("Hello World\n");

  action = g_action_map_lookup_action (G_ACTION_MAP (app), "incendio");
  g_action_activate (action, NULL);
}

static void
expelliarmus_func ()
{
  g_print ("expelliarmus World\n");
}


static void
incendio_func ()
{
  g_print ("incendio World\n");
}



static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;
  GSimpleAction *incendio; 
  GSimpleAction *expelliarmus;
  GMenu *menu;
  GtkBuilder *builder;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), app);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button);
 
  menu = g_menu_new (); 

  incendio = g_simple_action_new ("incendio",NULL);
  g_signal_connect_swapped (incendio, "activate", G_CALLBACK (incendio_func), NULL);
  g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (incendio));
  g_simple_action_set_enabled (incendio, TRUE);

  expelliarmus = g_simple_action_new ("expelliarmus",NULL);
  g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (expelliarmus));
  g_signal_connect_swapped (expelliarmus, "activate", G_CALLBACK (expelliarmus_func), NULL);

  builder = gtk_builder_new_from_file ("/home/uajain/app.ui");
  menu = G_MENU (gtk_builder_get_object (builder, "menu"));

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