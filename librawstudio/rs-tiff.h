/*
 * * Copyright (C) 2006-2011 Anders Brander <anders@brander.dk>, 
 * * Anders Kvist <akv@lnxbx.dk> and Klaus Post <klauspost@gmail.com>
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

#ifndef RS_TIFF_H
#define RS_TIFF_H

#include "rs-types.h"
#include "rs-tiff-ifd-entry.h"
#include <glib-object.h>

G_BEGIN_DECLS

#define RS_TYPE_TIFF rs_tiff_get_type()
#define RS_TIFF(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), RS_TYPE_TIFF, RSTiff))
#define RS_TIFF_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), RS_TYPE_TIFF, RSTiffClass))
#define RS_IS_TIFF(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), RS_TYPE_TIFF))
#define RS_IS_TIFF_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), RS_TYPE_TIFF))
#define RS_TIFF_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), RS_TYPE_TIFF, RSTiffClass))

/* Macros to read from TIFF files */
#define __rs_cast(x, type) (*((type*)(&(x))))

#define rs_tiff_get_generic(tiff, pos, TYPE, type) ( \
	((tiff)->map_length >= ((pos)+sizeof(type))) \
	? \
	( \
		((tiff)->byte_order == G_LITTLE_ENDIAN) \
		? (TYPE##_FROM_LE(__rs_cast((tiff)->map[(pos)], type))) \
		: (TYPE##_FROM_BE(__rs_cast((tiff)->map[(pos)], type))) \
	) \
	: 0 \
)

#define rs_tiff_get_simple(tiff, pos, type) ( \
	((pos) <= ((tiff)->map_length-sizeof(type))) \
	? __rs_cast((tiff)->map[(pos)], type) \
	: 0 \
)

#define rs_tiff_get_uchar(tiff, pos) rs_tiff_get_simple(tiff, pos, guchar)
#define rs_tiff_get_ushort(tiff, pos) rs_tiff_get_generic(tiff, pos, GUINT16, guint16)
#define rs_tiff_get_uint(tiff, pos) rs_tiff_get_generic(tiff, pos, GUINT32, guint32)
#define rs_tiff_get_urational(tiff, pos) ((gfloat) rs_tiff_get_uint(tiff, pos)) / ((gfloat) rs_tiff_get_uint(tiff, pos+sizeof(guint)))
#define rs_tiff_get_char(tiff, pos) rs_tiff_get_simple(tiff, pos, gchar)
#define rs_tiff_get_short(tiff, pos) rs_tiff_get_generic(tiff, pos, GINT16, gshort)
#define rs_tiff_get_int(tiff, pos) rs_tiff_get_generic(tiff, pos, GINT32, gint)
#define rs_tiff_get_rational(tiff, pos) ((gfloat) rs_tiff_get_int(tiff, pos)) / ((gfloat) ((rs_tiff_get_int(tiff, pos+sizeof(gint)) == 0) ? 1 : rs_tiff_get_int(tiff, pos+sizeof(gint))))
#define rs_tiff_get_float(tiff, pos) rs_tiff_get_simple(tiff, pos, gfloat)
#define rs_tiff_get_double(tiff, pos) rs_tiff_get_simple(tiff, pos, gdouble)

typedef struct {
	GObjectClass parent_class;

	gboolean (*read_file_header)(RSTiff *tiff);
} RSTiffClass;

GType rs_tiff_get_type(void);

RSTiff *rs_tiff_new_from_file(const gchar *filename);

const gchar *
rs_tiff_get_filename(RSTiff *tiff);

const gchar *
rs_tiff_get_filename_nopath(RSTiff *tiff);

RSTiffIfdEntry *
rs_tiff_get_ifd_entry(RSTiff *tiff, guint ifd_num, gushort tag);

gchar *
rs_tiff_get_ascii(RSTiff *tiff, guint ifd_num, gushort tag);

/* Free allocated data. This will cause the file to be reloaded on next access */
void
rs_tiff_free_data(RSTiff *tiff);

G_END_DECLS

#endif /* RS_TIFF_H */
