/*
 * RAWstudio - Rawstudio is an open source raw-image converter written in GTK+.
 * by Anders BRander <anders@brander.dk> and Anders Kvist <akv@lnxbx.dk>
 *
 * gtk-helper.c - some helper functions to gtk-interface
 *
 * Rawstudio is licensed under the GNU General Public License.
 * It uses DCRaw and UFraw code to do the actual raw decoding.
 */

#include <glib.h>
#include <gtk/gtk.h>

GtkWidget *gui_tooltip_no_window(GtkWidget *widget, gchar *tip_tip, gchar *tip_private)
{
	GtkWidget *e;
	GtkTooltips *tip;

	tip = gtk_tooltips_new();
	e = gtk_event_box_new();
	gtk_tooltips_set_tip(tip, e, tip_tip, tip_private);
	gtk_widget_show(widget);
	gtk_container_add(GTK_CONTAINER(e), widget);

	return e;
}

void gui_tooltip_window(GtkWidget *widget, gchar *tip_tip, gchar *tip_private)
{
	GtkTooltips *tip;

	tip = gtk_tooltips_new();
	gtk_tooltips_set_tip(tip, widget, tip_tip, tip_private);
	gtk_widget_show(widget);

	return;
}
