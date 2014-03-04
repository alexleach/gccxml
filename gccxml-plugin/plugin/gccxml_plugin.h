/* gccxml_plugin - A GCC plugin, dumping translation units as XML.

Copyright 2013 - Alex Leach <beamesleach /at/ gmail /dot/ com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the

  Free Software Foundation, Inc.
  51 Franklin Street, Fifth Floor
  Boston, MA  02110-1301  USA

*/

/**
 * \file gccxml_plugin.h
 *
 * Provides gccxml_plugin.c with external definitions.
 */

#ifndef GCCXML_PLUGIN_H
#define GCCXML_PLUGIN_H

/* These were hacked in to GCC's c-common/c.opt file, so don't exist for
 * the plugin. We populate them in the callback routine,
 * `collect_callback_args`.   */
extern char *flag_xml_start;

/* Counter for number of missed GCCXML_DECL_ERROR checks */
extern int n_gccxml_decl_errors_missed;

///@{
//   Declarations shared between xml.c and gccxml_plugin.c

#ifdef __cplusplus
  extern "C" {
#endif

/// Main entry point, called by one of gcc's plugin hooks.
void do_xml_output (void* plugin_data);

/// Start dumping XML to xml_plugin_data->xdi->file
void xml_start_dump (void* plugin_data);

/// Close XML tags in output file
void xml_end_dump (void* plugin_data);

/// Initialise xml_plugin_data struct (allocate memory)
void xml_init_plugin_data(const char* filename, void** data);

/// Finalise xml_plugin_data struct (deallocate memory)
void xml_del_plugin_data(void* data);


#ifdef __cplusplus
  }
#endif

///@}

#endif
