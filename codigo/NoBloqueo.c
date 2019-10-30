#include <gtk/gtk.h>
#include <unistd.h>
#include <pthread.h>

GtkWidget *imagen;

static void *modificarRicardoMilos(void *_) {
  static int visible = 1;
  sleep(2);

  while(1) {  
    visible ^= 1;

    if (visible)
      gtk_widget_set_opacity(imagen, 1);
    else
      gtk_widget_set_opacity(imagen, 0);
  }

  printf("Terminando espera\n");
}

static void click(GtkWidget *button, gpointer user_data) {
  pthread_t hilo, hilo2;
  pthread_create(&hilo, NULL, modificarRicardoMilos, NULL);
  pthread_create(&hilo2, NULL, modificarRicardoMilos, NULL);
}

static void click2(GtkWidget *button, gpointer user_data) {
  printf("Click!\n");
}

static void activate(GtkApplication* app, gpointer user_data) {
  GtkWidget *window = gtk_application_window_new(app);

  GtkWidget *contenedor = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), contenedor);

  imagen = gtk_image_new_from_file("Imagen.gif");
  gtk_fixed_put(GTK_FIXED(contenedor), imagen, 0, 0);

  GtkWidget *buttonBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_fixed_put(GTK_FIXED(contenedor), buttonBox, 50, 50);

  GtkWidget *button = gtk_button_new_with_label("Bloquear");
  gtk_container_add(GTK_CONTAINER(buttonBox), button);

  GtkWidget *buttonBox2 = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_fixed_put(GTK_FIXED(contenedor), buttonBox2, 50, 150);

  GtkWidget *button2 = gtk_button_new_with_label("Clickeame");
  gtk_container_add(GTK_CONTAINER(buttonBox), button2);

  g_signal_connect(button, "clicked", G_CALLBACK(click), NULL);
  g_signal_connect(button2, "clicked", G_CALLBACK(click2), NULL);

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
