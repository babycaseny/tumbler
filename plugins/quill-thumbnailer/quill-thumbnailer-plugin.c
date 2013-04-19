/* vi:set et ai sw=2 sts=2 ts=2: */
/*-
 * Copyright (c) 2009 Jannis Pohlmann <jannis@xfce.org>
 * Copyright (c) 2009 Nokia, 
 *   written by Philip Van Hoof <philip@codeminded.be>
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public 
 * License along with this program; if not, write to the Free 
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib.h>
#include <glib/gi18n.h>
#include <glib-object.h>

#include <tumbler/tumbler.h>

#include <quill-thumbnailer/quill-thumbnailer-provider.h>
#include <quill-thumbnailer/quill-thumbnailer.h>



G_MODULE_EXPORT void tumbler_plugin_initialize (TumblerProviderPlugin *plugin);
G_MODULE_EXPORT void tumbler_plugin_shutdown   (void);
G_MODULE_EXPORT void tumbler_plugin_get_types  (const GType          **types,
                                                gint                  *n_types);



static GType type_list[1];



void
tumbler_plugin_initialize (TumblerProviderPlugin *plugin)
{
  const gchar *mismatch;

  /* verify that the tumbler versions are compatible */
  mismatch = tumbler_check_version (TUMBLER_MAJOR_VERSION, TUMBLER_MINOR_VERSION,
                                    TUMBLER_MICRO_VERSION);
  if (G_UNLIKELY (mismatch != NULL))
    {
      g_warning (_("Version mismatch: %s"), mismatch);
      return;
    }

#ifdef DEBUG
  g_message (_("Initializing the Tumbler Quill Thumbnailer plugin"));
#endif

  /* register the types provided by this plugin */
  quill_thumbnailer_register (plugin);
  quill_thumbnailer_provider_register (plugin);

  /* set up the plugin provider type list */
  type_list[0] = TYPE_QUILL_THUMBNAILER_PROVIDER;
}



void
tumbler_plugin_shutdown (void)
{
#ifdef DEBUG
  g_message (_("Shutting down the Tumbler Quill Thumbnailer plugin"));
#endif
}



void
tumbler_plugin_get_types (const GType **types,
                          gint         *n_types)
{
  *types = type_list;
  *n_types = G_N_ELEMENTS (type_list);
}
