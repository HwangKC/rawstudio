/*
 * Copyright (C) 2006-2008 Anders Brander <anders@brander.dk> and 
 * Anders Kvist <akv@lnxbx.dk>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef RS_PHOTO_H
#define RS_PHOTO_H

#include "rawstudio.h"
#include <glib-object.h>

#define RS_TYPE_PHOTO        (rs_photo_get_type ())
#define RS_PHOTO(obj)        (G_TYPE_CHECK_INSTANCE_CAST ((obj), RS_TYPE_PHOTO, RS_PHOTO))
#define RS_PHOTO_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), RS_TYPE_PHOTO, RS_PHOTOClass))
#define RS_IS_PHOTO(obj)     (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RS_TYPE_PHOTO))
#define RS_IS_PHOTO_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RS_TYPE_PHOTO))
#define RS_PHOTO_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), RS_TYPE_PHOTO, RS_PHOTOClass))

typedef struct _RS_PHOTOClass RS_PHOTOClass;

struct _RS_PHOTOClass {
	GObjectClass parent;
};

GType rs_photo_get_type (void);

/* Please note that this is not a bitmask */
enum {
	PRIO_U = 0,
	PRIO_D = 51,
	PRIO_1 = 1,
	PRIO_2 = 2,
	PRIO_3 = 3,
	PRIO_ALL = 255
};

/**
 * Allocates a new RS_PHOTO
 * @return A new RS_PHOTO
 */
extern RS_PHOTO *rs_photo_new();

/**
 * Rotates a RS_PHOTO
 * @param photo A RS_PHOTO
 * @param quarterturns How many quarters to turn
 * @param angle The angle in degrees (360 is whole circle) to turn the image
 */
extern void rs_photo_rotate(RS_PHOTO *photo, const gint quarterturns, const gdouble angle);

/**
 * Sets a new crop of a RS_PHOTO
 * @param photo A RS_PHOTO
 * @param crop The new crop or NULL to remove previous cropping
 */
extern void rs_photo_set_crop(RS_PHOTO *photo, const RS_RECT *crop);

/**
 * Gets the crop of a RS_PHOTO
 * @param photo A RS_PHOTO
 * @return The crop as a RS_RECT or NULL if the photo is uncropped
 */
extern RS_RECT *rs_photo_get_crop(RS_PHOTO *photo);

/**
 * Set the exposure of a RS_PHOTO
 * @param photo A RS_PHOTO
 * @param snapshot Which snapshot to affect
 * @param value The new value
 */
extern void rs_photo_set_exposure(RS_PHOTO *photo, const gint snapshot, const gdouble value);

/**
 * Set the saturation of a RS_PHOTO
 * @param photo A RS_PHOTO
 * @param snapshot Which snapshot to affect
 * @param value The new value
 */
extern void rs_photo_set_saturation(RS_PHOTO *photo, const gint snapshot, const gdouble value);

/**
 * Set the hue of a RS_PHOTO
 * @param photo A RS_PHOTO
 * @param snapshot Which snapshot to affect
 * @param value The new value
 */
extern void rs_photo_set_hue(RS_PHOTO *photo, const gint snapshot, const gdouble value);

/**
 * Set the contrast of a RS_PHOTO
 * @param photo A RS_PHOTO
 * @param snapshot Which snapshot to affect
 * @param value The new value
 */
extern void rs_photo_set_contrast(RS_PHOTO *photo, const gint snapshot, const gdouble value);

/**
 * Set the warmth of a RS_PHOTO
 * @param photo A RS_PHOTO
 * @param snapshot Which snapshot to affect
 * @param value The new value
 */
extern void rs_photo_set_warmth(RS_PHOTO *photo, const gint snapshot, const gdouble value);

/**
 * Set the tint of a RS_PHOTO
 * @param photo A RS_PHOTO
 * @param snapshot Which snapshot to affect
 * @param value The new value
 */
extern void rs_photo_set_tint(RS_PHOTO *photo, const gint snapshot, const gdouble value);

/**
 * Apply settings to a RS_PHOTO from a RS_SETTINGS_DOUBLE
 * @param photo A RS_PHOTO
 * @param snapshot Which snapshot to affect
 * @param rs_settings_double The settings to apply
 * @param mask A mask for defining which settings to apply
 */
extern void rs_photo_apply_settings_double(RS_PHOTO *photo, const gint snapshot, const RS_SETTINGS_DOUBLE *rs_settings_double, const gint mask);

/**
 * Flips a RS_PHOTO
 * @param photo A RS_PHOTO
 */
extern void rs_photo_flip(RS_PHOTO *photo);

/**
 * Mirrors a RS_PHOTO
 * @param photo A RS_PHOTO
 */
extern void rs_photo_mirror(RS_PHOTO *photo);

/**
 * Closes a RS_PHOTO - this basically means saving cache
 * @param photo A RS_PHOTO
 */
extern void rs_photo_close(RS_PHOTO *photo);

/**
 * Open a photo using the dcraw-engine
 * @param filename The filename to open
 * @param half_size Open in half size - without NN-demosaic
 * @return The newly created RS_PHOTO or NULL on error
 */
extern RS_PHOTO *rs_photo_open_dcraw(const gchar *filename, gboolean half_size);

/**
 * Open a photo using the GDK-engine
 * @param filename The filename to open
 * @param half_size Does nothing
 * @return The newly created RS_PHOTO or NULL on error
 */
extern RS_PHOTO *rs_photo_open_gdk(const gchar *filename, gboolean half_size);

/* For arch binders */
extern void (*rs_photo_open_dcraw_apply_black_and_shift)(dcraw_data *raw, RS_PHOTO *photo) __rs_optimized;
extern void rs_photo_open_dcraw_apply_black_and_shift_c(dcraw_data *raw, RS_PHOTO *photo);
#if defined (__i386__) || defined (__x86_64__)
extern void rs_photo_open_dcraw_apply_black_and_shift_mmx(dcraw_data *raw, RS_PHOTO *photo);
#endif

#endif /* RS_PHOTO_H */