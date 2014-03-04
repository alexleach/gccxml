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

#include "gccxml_plugin.h"

#include "gcc-plugin.h"
#include "plugin-version.h"

#include "options.h"

/* Declare GPL compatible license. */
int plugin_is_GPL_compatible;

//@{
/// Plugin routines

#ifdef __cplusplus
  extern "C" {
#endif

// File name passed on command line
static const char *flag_xml;

char *flag_xml_start;
int n_gccxml_decl_errors_missed = 0;

// forward decl.
void plugin_print_warnings(void);

/** Start XML dump. */
static void
plugin_dump_xml(void *gcc_data, void *user_data)
{
  do_xml_output(user_data);
}

/** End XML dump. */
static void
plugin_finish(void *gcc_data, void *user_data)
{
  xml_end_dump(user_data);
  xml_del_plugin_data(user_data);
  // print GCCXML-plugin warning messages
  plugin_print_warnings();
}

void print_gccxml_plugin_version(struct plugin_name_args *plugin_info)
{
  printf("gccxml plugin info:\n"
         "\tVersion:  %s\n"
         "\tbase_name: %s\n"
         "\tfull_name: %s\n",
          plugin_info->version,
          plugin_info->base_name,
          plugin_info->full_name);

  printf("GCC info:\n"
         "\tVersion: %s\n",
          gcc_version.basever);
}

#if defined(_WIN32) && !defined(__MINGW32__)
// No colours
#define BOLD
#define RESET
#else
// Use ANSI Bold
#define BOLD   "\033[1m"
#define RESET  "\033[0m"
#endif

/** Collect command-line arguments from `plugin_init(..)`
 *
 * If more options are needed, do a couple of things:-
 *   1. Add the option to `allowed_args`, making sure to increase
 *      its size by one.
 *   2. Add a new `else if` clause, to deal with the option.
 *
 * Not very elegant cf. GCC, but does the job.
 */
int
collect_plugin_args(struct plugin_name_args *plugin_info)
{
  struct plugin_argument *arg;
  const char *key;
  const char* const allowed_args[3] = 
  {
    "xml_start",
    "xml",
    "version",
  };

  int i;
  for (i=0; i < plugin_info->argc; i++)
  {
    arg = &plugin_info->argv[i];
    key = arg->key;
    if (strncmp(key, allowed_args[0], strlen(allowed_args[0])) == 0)
    {
      // -fxml_start arg.
      flag_xml_start = arg->value;
    }
    else if (strncmp(key, allowed_args[1], strlen(allowed_args[1])) == 0)
    {
      // -fxml arg.
      flag_xml = arg->value;
    }
    else if (strncmp(key, allowed_args[2], strlen(allowed_args[2])) == 0)
    {
      // -version
      print_gccxml_plugin_version(plugin_info);
    }
    else
    {
      // Print a pretty error message, showing in bold where the option
      // went wrong.
      fprintf(stderr, "Unrecognised xml plugin argument: ");
      fprintf(stderr, BOLD "%s\n" RESET, arg->key);         // The problem option key
      fprintf(stderr, "Allowed arguments:\n");
      fprintf(stderr, "\t'-fplugin-arg-%s-", plugin_info->base_name);
      fprintf(stderr, BOLD "%s" RESET, allowed_args[0]);    // An option, in bold
      fprintf(stderr, "=<val>'");
      int j = 1;
      const int n_allowed_args = sizeof(allowed_args) / sizeof(allowed_args[0]);

      // loop through options, printing them prettily.
      for ( ; j < n_allowed_args ; j++)
      {
        fprintf(stderr, ", or\n");
        fprintf(stderr, "\t'-fplugin-arg-%s-", plugin_info->base_name);
        fprintf(stderr, BOLD "%s" RESET, allowed_args[j]);    // An option, in bold 
        fprintf(stderr, "=<val>'");
      }
      fprintf(stderr, "\n");
      return 1;
    }
  }
  return 0;
}

// Plugin info Structs
static struct plugin_info
gccxml_plugin_info = {
  .version = GCCXML_PLUGIN_VERSION_FULL,
  .help = "Generate XML representation of a C++ Abstract Syntax Tree."
};

void
plugin_print_warnings(void)
{
  if (n_gccxml_decl_errors_missed > 0)
    printf("\nPlease note.\n"
           "The plugin is missing the GCCXML_DECL_ERROR macro, so the test \n"
           "on about line %i is missing from this implementation of GCCXML.\n"
           "I'm not sure what repercussions there are, but I can tell you  \n"
           "that the test was encountered %i times...\n",
           4095,
           n_gccxml_decl_errors_missed);
}

int
plugin_init(struct plugin_name_args   *plugin_info,
            struct plugin_gcc_version *version)
{
  plugin_info->version = GCCXML_PLUGIN_VERSION_FULL;

  // Complain if built for a different major, or minor version.
  // Ignore patchlevel and other `plugin_gcc_version` attributes.
  if (strncmp(version->basever, gcc_version.basever, 3))
  {
    fprintf(stderr, "Incompatible version (%s). Compiled for %s\n",
            version->basever, gcc_version.basever);
    return 1;
  }

  if (collect_plugin_args(plugin_info) != 0)
    return 1;

  /* Disable assembler output */
  asm_file_name = HOST_BIT_BUCKET;

  /* Populate the plugin_info struct */
  register_callback(plugin_info->base_name, PLUGIN_INFO,
                    NULL, &gccxml_plugin_info);

  void* plugin_data;
  xml_init_plugin_data(flag_xml, &plugin_data);
  xml_start_dump(plugin_data);

  /* Register callback to dump XML */
  register_callback(plugin_info->base_name, PLUGIN_FINISH_UNIT,
                    plugin_dump_xml, plugin_data);

  /* End dump */
  register_callback(plugin_info->base_name, PLUGIN_FINISH,
                    plugin_finish, plugin_data);

  return 0;
}

// End plugin callback group.
//@}

#ifdef __cplusplus
  }
#endif

