/*
# Copyright (C) Johan Ceuppens 2013
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

void text_toggle_editable (GtkWidget *checkbutton,
                           GtkWidget *text)
{
  gtk_text_set_editable(GTK_TEXT(text),
                        GTK_TOGGLE_BUTTON(checkbutton)->active);
}

void text_toggle_word_wrap (GtkWidget *checkbutton,
                            GtkWidget *text)
{
  gtk_text_set_word_wrap(GTK_TEXT(text),
                         GTK_TOGGLE_BUTTON(checkbutton)->active);
}

void close_application( GtkWidget *widget,
                        gpointer   data )
{
       gtk_main_quit();
}

#define MAXDATASIZE 300
char *buffybuf;
char *buffybuf2;


int main( int argc,
          char *argv[] )
{
  GtkWidget *window;
  GtkWidget *box1;
  GtkWidget *box2;
  GtkWidget *hbox;
  GtkWidget *button;
  GtkWidget *check;
  GtkWidget *separator;
  GtkWidget *table;
  GtkWidget *vscrollbar;
  GtkWidget *text;
  GdkColormap *cmap;
  GdkColor color;
  GdkFont *fixed_font;

  FILE *infile;

  gtk_init (&argc, &argv);
 
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_usize (window, 600, 500);
  gtk_window_set_policy (GTK_WINDOW(window), TRUE, TRUE, FALSE);  
  gtk_signal_connect (GTK_OBJECT (window), "destroy",
                      GTK_SIGNAL_FUNC(close_application),
                      NULL);
  gtk_window_set_title (GTK_WINDOW (window), "bmail email");
  gtk_container_set_border_width (GTK_CONTAINER (window), 0);
  
  
  box1 = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), box1);
  gtk_widget_show (box1);
  
  
  box2 = gtk_vbox_new (FALSE, 10);
  gtk_container_set_border_width (GTK_CONTAINER (box2), 10);
  gtk_box_pack_start (GTK_BOX (box1), box2, TRUE, TRUE, 0);
  gtk_widget_show (box2);
  
  
  table = gtk_table_new (2, 2, FALSE);
  gtk_table_set_row_spacing (GTK_TABLE (table), 0, 2);
  gtk_table_set_col_spacing (GTK_TABLE (table), 0, 2);
  gtk_box_pack_start (GTK_BOX (box2), table, TRUE, TRUE, 0);
  gtk_widget_show (table);
  
  /* Create the GtkText widget */
  text = gtk_text_new (NULL, NULL);
  gtk_text_set_editable (GTK_TEXT (text), TRUE);
  gtk_table_attach (GTK_TABLE (table), text, 0, 1, 0, 1,
                    GTK_EXPAND | GTK_SHRINK | GTK_FILL,
                    GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);
  gtk_widget_show (text);

  /* Add a vertical scrollbar to the GtkText widget */
  vscrollbar = gtk_vscrollbar_new (GTK_TEXT (text)->vadj);
  gtk_table_attach (GTK_TABLE (table), vscrollbar, 1, 2, 0, 1,
                    GTK_FILL, GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);
  gtk_widget_show (vscrollbar);

  /* Get the system color map and allocate the color red */
  cmap = gdk_colormap_get_system();
  color.red = 0xffff;
  color.green = 0;
  color.blue = 0;
  if (!gdk_color_alloc(cmap, &color)) {
    g_error("couldn't allocate color");
  }

  /* Load a fixed font */
  fixed_font = gdk_font_load ("-misc-fixed-medium-r-*-*-*-140-*-*-*-*-*-*");

  /* Realizing a widget creates a window for it,
   * ready for us to insert some text */
  gtk_widget_realize (text);

  /* Freeze the text widget, ready for multiple updates */
  gtk_text_freeze (GTK_TEXT (text));
  
  /* Insert some colored text */
/*  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
                   "Supports ", -1);
  gtk_text_insert (GTK_TEXT (text), NULL, &color, NULL,
                   "colored ", -1);
  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
                   "text and different ", -1);
  gtk_text_insert (GTK_TEXT (text), fixed_font, &text->style->black, NULL,
                   "fonts\n\n", -1);
*/  
  /* Thaw the text widget, allowing the updates to become visible */  
  gtk_text_thaw (GTK_TEXT (text));
  
  hbox = gtk_hbutton_box_new ();
  gtk_box_pack_start (GTK_BOX (box2), hbox, FALSE, FALSE, 0);
  gtk_widget_show (hbox);

  check = gtk_check_button_new_with_label("Editable");
  gtk_box_pack_start (GTK_BOX (hbox), check, FALSE, FALSE, 0);
  gtk_signal_connect (GTK_OBJECT(check), "toggled",
                      GTK_SIGNAL_FUNC(text_toggle_editable), text);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), TRUE);
  gtk_widget_show (check);
  check = gtk_check_button_new_with_label("Wrap Words");
  gtk_box_pack_start (GTK_BOX (hbox), check, FALSE, TRUE, 0);
  gtk_signal_connect (GTK_OBJECT(check), "toggled",
                      GTK_SIGNAL_FUNC(text_toggle_word_wrap), text);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), FALSE);
  gtk_widget_show (check);

  separator = gtk_hseparator_new ();
  gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 0);
  gtk_widget_show (separator);

  box2 = gtk_vbox_new (FALSE, 10);
  gtk_container_set_border_width (GTK_CONTAINER (box2), 10);
  gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, TRUE, 0);
  gtk_widget_show (box2);
  
  button = gtk_button_new_with_label ("close");
  gtk_signal_connect (GTK_OBJECT (button), "clicked",
                      GTK_SIGNAL_FUNC(close_application),
                      NULL);
  gtk_box_pack_start (GTK_BOX (box2), button, TRUE, TRUE, 0);
  GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
  gtk_widget_grab_default (button);
  gtk_widget_show (button);

  gtk_widget_show (window);

  //struct B { char *buf; } Buffy;
  //clientsock(Buffy.buf);
  buffybuf = (char*)malloc(MAXDATASIZE);
  buffybuf2 = (char*)malloc(MAXDATASIZE);
  clientsock(&buffybuf);
  sprintf(buffybuf2, "%s", buffybuf);
  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
                   buffybuf2, strlen(buffybuf2));
 
  gtk_main ();
  
  return(0);       
}

