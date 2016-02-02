#include <gtk/gtk.h>

static void right_click ();

static void
button_pressed (GtkWidget *widget, GdkEventButton *event)
{
  /*
   *Simulated right click here:
   *This function will run if any button is pressed on mouse.
   *So we explicitly emit "clicked" signal to show the menu
   *when event->button = 3 i.e. the right click.
   *See : https://developer.gnome.org/gdk3/stable/gdk3-Event-Structures.html#GdkEventButton
   */

   if (event->button != 3)
    return;

   else
    {
      g_signal_connect_after (GTK_BUTTON (widget), "clicked", G_CALLBACK (right_click), NULL);
      g_signal_emit_by_name (GTK_BUTTON (widget), "clicked");
    }

}

static void
expelliarmus_func ()
{
  g_print ("Member: Expelliarmus clicked\n");
}

static void
incendio_func ()
{
  g_print ("Member: Incendio clicked\n");
}

static void
right_click ()
{
  g_print ("Right Button Clickedasd !\n");
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button_box;
  GSimpleAction *incendio; 
  GSimpleAction *expelliarmus;
  GMenuModel *menu_model;
  GtkWidget *menu_button;
  GtkBuilder *builder;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

 
  incendio = g_simple_action_new ("incendio",NULL);
  g_signal_connect_swapped (incendio, "activate", G_CALLBACK (incendio_func), NULL);
  g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (incendio));

  expelliarmus = g_simple_action_new ("expelliarmus",NULL);
  g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (expelliarmus));
  g_signal_connect_swapped (expelliarmus, "activate", G_CALLBACK (expelliarmus_func), NULL);

  menu_button = gtk_menu_button_new (); 

  builder = gtk_builder_new_from_file ("/home/uajain/app.ui");
  menu_model = G_MENU_MODEL (gtk_builder_get_object (builder, "menu"));
  gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (menu_button), menu_model);
  g_signal_connect (menu_button, "button-press-event", G_CALLBACK (button_pressed), app);

  gtk_container_add (GTK_CONTAINER (button_box), menu_button);
  g_object_unref (builder);

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