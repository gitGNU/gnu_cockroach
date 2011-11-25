#ifndef PLUGINS_H
# define PLUGINS_H

# include <roach.h>

const char *plugin_get_name ();
int plugin_load (roach_context_t *ctx);
int plugin_free (roach_context_t *ctx);
int plugin_add (roach_context_t *ctx, const char *options);
#endif
