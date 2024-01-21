/* statsadder_adw-window.c
 *
 * Copyright 2022 MagicWizard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "statsadder_adw-config.h"
#include "statsadder_adw-window.h"

struct _StatsadderAdwWindow {
  GtkApplicationWindow parent_instance;

  /* Template widgets */
  GtkHeaderBar *header_bar;
  GtkLabel *label;
  GtkSpinButton *YearEnter;
  GtkSpinButton *DayEnter;
  GtkSpinButton *MonthEnter;
  GtkButton *ButtonAdd;
  GtkEntry *NameEntry;
};
struct Books {
  StatsadderAdwWindow *self;
  GtkWidget *label;
};

char *concat(const char *s1, const char *s2) {
  char *result =
      malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
  // in real code you would check for errors in malloc here
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}
static void default_values(StatsadderAdwWindow *self) {
  time_t s, val = 1;
  struct tm *current_time;
  s = time(NULL);
  current_time = localtime(&s);
  int day = current_time->tm_mday;
  int month = current_time->tm_mon + 1;
  int year = current_time->tm_year + 1900;
  gtk_spin_button_set_value(GTK_LABEL(self->YearEnter), year);
  gtk_spin_button_set_value(GTK_LABEL(self->DayEnter), day);
  gtk_spin_button_set_value(GTK_LABEL(self->MonthEnter), month);
}
static void button_clicked(StatsadderAdwWindow *self) {
  int statusTouch = system("touch $HOME/.cache/statsadder");
  char command[50];

  FILE *ls_cmd = popen("cat $HOME/.cache/statsadder", "r");

  char buff[1024];
  size_t n;
  int aa = 0;
  while ((n = fread(buff, 1, sizeof(buff) - 1, ls_cmd)) > 0) {
    buff[n - 1] = '\'';
    buff[n] = '\0';
    aa++;
    printf("printing: %d %d", aa, n);
  }
  int day = 0, month = 0, year = 0;
  char *textentry;
  day = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(self->DayEnter));

  month = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(self->MonthEnter));

  year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(self->YearEnter));
  GtkEntryBuffer *entrybuffer1;
  entrybuffer1 = gtk_entry_get_buffer(GTK_ENTRY(self->NameEntry));
  textentry = gtk_entry_buffer_get_text(entrybuffer1);
  char *buffa;

  int status = 555555;
  if (textentry[0] == NULL) {

    g_print("jeste null");
  } else {
    char d[50] = "echo \""; // wwww\" >>
    char *buffaa;
    char e[50] = "\" >> \'";

    char end[50] = "\'";
    // day
    char *buffaday;

    char dayc[5];
    if (day >= 1000) {
      dayc[0] = (day / 1000) % 10 + '0';
      dayc[1] = (day / 100) % 10 + '0';
      dayc[2] = (day / 10) % 10 + '0';
      dayc[3] = day % 10 + '0';
      dayc[4] = ' ';
      dayc[5] = NULL;
    } else if (day >= 100) {

      dayc[0] = (day / 100) % 10 + '0';
      dayc[1] = (day / 10) % 10 + '0';
      dayc[2] = day % 10 + '0';
      dayc[3] = ' ';
      dayc[4] = NULL;
    } else if (day >= 10) {

      dayc[0] = (day / 10) % 10 + '0';
      dayc[1] = day % 10 + '0';
      dayc[2] = ' ';
      dayc[3] = NULL;
    } else {
      dayc[0] = '0';
      dayc[1] = day % 10 + '0';
      dayc[2] = ' ';
      dayc[3] = NULL;
    }

    buffaday = concat(d, dayc);

    // day
    //
    //
    // month

    char *buffamon;

    char monc[5];
    if (month >= 1000) {
      monc[0] = (month / 1000) % 10 + '0';
      monc[1] = (month / 100) % 10 + '0';
      monc[2] = (month / 10) % 10 + '0';
      monc[3] = month % 10 + '0';
      monc[4] = ' ';
      monc[5] = NULL;
    } else if (month >= 100) {

      monc[0] = (month / 100) % 10 + '0';
      monc[1] = (month / 10) % 10 + '0';
      monc[2] = month % 10 + '0';
      monc[3] = ' ';
      monc[4] = NULL;
    } else if (month >= 10) {

      monc[0] = (month / 10) % 10 + '0';
      monc[1] = month % 10 + '0';
      monc[2] = ' ';
      monc[3] = NULL;
    } else {
      monc[0] = '0';
      monc[1] = month % 10 + '0';
      monc[2] = ' ';
      monc[3] = NULL;
    }

    buffamon = concat(buffaday, monc);

    // month

    // yeaer

    char *buffayear;

    char yearc[5];
    if (year >= 1000) {
      yearc[0] = (year / 10) % 10 + '0';
      yearc[1] = year % 10 + '0';
      yearc[2] = ' ';
      yearc[3] = NULL;
    } else if (year >= 100) {

      yearc[0] = (year / 10) % 10 + '0';
      yearc[1] = year % 10 + '0';
      yearc[2] = ' ';
      yearc[3] = NULL;
    } else if (year >= 10) {

      yearc[0] = (year / 10) % 10 + '0';
      yearc[1] = year % 10 + '0';
      yearc[2] = ' ';
      yearc[3] = NULL;
    } else {
      yearc[0] = '0';
      yearc[1] = year % 10 + '0';
      yearc[2] = ' ';
      yearc[3] = NULL;
    }

    buffayear = concat(buffamon, yearc);

    // year
    //
    // name
    char *buffatext;
    buffatext = concat(buffayear, textentry);
    // name

    buffaa = concat(buffatext, e);

    char *bufend;
    buffa = concat(buffaa, buff);
    bufend = concat(buffa, end);

    g_print("bufaf\n");
    g_print(buffa);

    status = system(buffa);
  }

  char *statu;

  // command=system()
  // g_print(day);
  printf("You entered: %d %d %d", day, month, year);
  GtkWidget *hello;

  if (status == 0 && textentry[0] != '\0') {

    statu = "\n\nAdded successfully!!!";
    hello = gtk_message_dialog_new(self, GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                   concat(buffa, statu));
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(
        provider, ".kopytko{color: green;} .kopytkofail{color: red;}", -1);
    GtkStyleContext *context = gtk_widget_get_style_context(hello);
    gtk_style_context_add_class(context, "kopytko");
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), -20);
    gtk_style_context_save(context);

  } else {
    statu = "\n\nError! File problem. Could not add stat.";

    if (textentry[0] != NULL) {
      hello = gtk_message_dialog_new(self, GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_ERROR, GTK_BUTTONS_CANCEL,
                                     concat(buffa, statu));

      GtkCssProvider *provider = gtk_css_provider_new();
      gtk_css_provider_load_from_data(
          provider, ".kopytko{color: green;} .kopytkofail{color: red;}", -1);
      GtkStyleContext *context = gtk_widget_get_style_context(hello);
      gtk_style_context_add_class(context, "kopytkofail");
      gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider),
                                     -20);
      gtk_style_context_save(context);

    } else {
      hello = gtk_message_dialog_new(self, GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
                                     "No stat entry!\n\n Didn't add.");

      GtkCssProvider *provider = gtk_css_provider_new();
      gtk_css_provider_load_from_data(
          provider, ".kopytko{color: green;} .kopytkofail{color: orange;}", -1);
      GtkStyleContext *context = gtk_widget_get_style_context(hello);
      gtk_style_context_add_class(context, "kopytkofail");
      gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider),
                                     -20);
      gtk_style_context_save(context);
    }
  }

  /* GtkWidget* hello =  gtk_dialog_new_with_buttons ("Message",
                                       self,
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        ("_OK"),
                                        GTK_RESPONSE_NONE,
                                        NULL);
   */

  g_signal_connect(hello, "response", G_CALLBACK(gtk_window_destroy), NULL);

  gtk_widget_show(hello);
}

G_DEFINE_TYPE(StatsadderAdwWindow, statsadder_adw_window,
              GTK_TYPE_APPLICATION_WINDOW)



static void statsadder_adw_window_init(StatsadderAdwWindow *self) {
  gtk_widget_init_template(GTK_WIDGET(self));

  default_values(self);
}

static GtkWidget *labelg;
static GtkWindow *winn;

static char *filepath;
static void on_open_response(GtkWidget *self, gint response_id,
                             gpointer user_data) {
  if (response_id == GTK_RESPONSE_ACCEPT) {
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(self);

    g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser);
    g_print(g_file_get_path(file));

    // open_file (file);
    //
    gtk_label_set_text(labelg, g_file_get_path(file));

    char *a = g_file_get_path(file);
    char *b = concat("echo \'", a);
    char *w = "\' > $HOME/.cache/statsadder2";

    int status = system(concat(b, w));
    g_print(concat(a, w));
  }
  gtk_window_destroy(GTK_WINDOW(self));
}

static void open_file(GtkWidget *self, gint response_id, gpointer user_data) {

  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;

  dialog = gtk_file_chooser_dialog_new("Open File", self, action, ("_Cancel"),
                                       GTK_RESPONSE_CANCEL, ("_Open"),
                                       GTK_RESPONSE_ACCEPT, NULL);

  gtk_widget_show(dialog);

  g_signal_connect(dialog, "response", G_CALLBACK(on_open_response), NULL);
}
static void close_window(GtkWindow *widget, gpointer window) {

  int status = system("rm $HOME/.cache/statsadder2");
  gtk_window_close(winn);

  // gtk_widget_destroy(GTK_WIDGET(window));
}
static void save_file(GtkWindow *widget, gpointer window) {
  int status2 = system("cp $HOME/.cache/statsadder2 $HOME/.cache/statsadder");
  int status = system("rm $HOME/.cache/statsadder2");
  gtk_window_close(winn);
  // gtk_widget_destroy(GTK_WIDGET(window));
}

static void prefs(StatsadderAdwWindow *self) {
  g_print("huesh");
  FILE *ls_cmd = popen("cat $HOME/.cache/statsadder", "r");

  char buff[1024];
  size_t n;

  while ((n = fread(buff, 1, sizeof(buff) - 1, ls_cmd)) > 0) {

    buff[n] = '\0';
  }
  /*
   GtkWindow *window;
 GtkWidget *dialog, *label, *content_area;
 GtkDialogFlags flags;

 // Create the widgets
 flags = GTK_DIALOG_DESTROY_WITH_PARENT;
 dialog = gtk_dialog_new_with_buttons ("Preferences",
                                       self,
                                       flags,
                                       ("_OK"),
                                       GTK_RESPONSE_NONE,
                                       NULL);
   window = gtk_window_new ();
  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
 label = gtk_label_new (buff);

 // Ensure that the dialog box is destroyed when the user responds

 g_signal_connect_swapped (dialog,
                           "response",
                           G_CALLBACK (gtk_window_destroy),
                           dialog);

 // Add the label, and show everything we’ve added

 gtk_box_append (GTK_BOX (content_area), label);
 gtk_widget_show (window);

*/

  GtkWindow *window;
  window = gtk_window_new();

  gtk_widget_show(window);
  GtkWidget *button, *buttonchange, *buttoncancel, *box, *boxh, *boxh2, *label;
  button = gtk_button_new();
  buttonchange = gtk_button_new();
  buttoncancel = gtk_button_new();

  box = gtk_box_new(1, 5);
  boxh = gtk_box_new(0, 5);
  boxh2 = gtk_box_new(0, 5);
  label = gtk_label_new(buff);
  gtk_window_set_child(GTK_WINDOW(window), box);
  gtk_button_set_label(buttonchange, "Change file");
  gtk_button_set_label(button, "Save");
  gtk_button_set_label(buttoncancel, "Cancel");

  gtk_box_append(box, boxh);
  gtk_box_append(box, boxh2);
  gtk_box_append(boxh2, buttoncancel);
  gtk_box_append(boxh2, button);
  gtk_box_append(boxh, label);
  gtk_box_append(boxh, buttonchange);
  gtk_widget_show(button);
  struct Books book1;
  book1.self = self;
  book1.label = label;
  labelg = label;
  winn = window;
  g_signal_connect(button, "clicked", G_CALLBACK(save_file), NULL);
  g_signal_connect(buttonchange, "clicked", G_CALLBACK(open_file), NULL);

  g_signal_connect(G_OBJECT(buttoncancel), "clicked", G_CALLBACK(close_window),
                   G_OBJECT(window));
}

static void statsadder_adw_window_class_init(StatsadderAdwWindowClass *klass) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

  gtk_widget_class_set_template_from_resource(
      widget_class, "/com/statsadder/adw/statsadder_adw-window.ui");
  gtk_widget_class_bind_template_child(widget_class, StatsadderAdwWindow,
                                       header_bar);
  gtk_widget_class_bind_template_child(widget_class, StatsadderAdwWindow,
                                       label);

  gtk_widget_class_bind_template_child(widget_class, StatsadderAdwWindow,
                                       YearEnter);
  gtk_widget_class_bind_template_child(widget_class, StatsadderAdwWindow,
                                       DayEnter);
  gtk_widget_class_bind_template_child(widget_class, StatsadderAdwWindow,
                                       MonthEnter);
  gtk_widget_class_bind_template_child(widget_class, StatsadderAdwWindow,
                                       NameEntry);
  gtk_widget_class_bind_template_child(widget_class, StatsadderAdwWindow,
                                       ButtonAdd);
  gtk_widget_class_install_action(widget_class, "defaults", NULL,
                                  default_values);
  gtk_widget_class_install_action(widget_class, "app.preferences", NULL, prefs);
  gtk_widget_class_bind_template_callback(GTK_WIDGET_CLASS(klass),
                                          button_clicked);
}
