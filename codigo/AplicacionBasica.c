#include <gtk/gtk.h>

static void activate(GtkApplication* app, gpointer user_data) {
  GtkWidget *window = gtk_application_window_new(app);

  GtkWidget *contenedor = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), contenedor);

  GtkWidget *imagen = gtk_image_new_from_file("Imagen.gif");
  gtk_fixed_put(GTK_FIXED(contenedor), imagen, 0, 0);

  gtk_window_set_title (GTK_WINDOW(window), "Window");
  gtk_window_set_default_size (GTK_WINDOW(window), 200, 200);
  gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);

  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
