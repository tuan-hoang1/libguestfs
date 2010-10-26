/* libguestfs - guestfish and guestmount shared option parsing
 * Copyright (C) 2010 Red Hat Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "guestfs.h"

#include "options.h"

/* Global that saves the root device between inspect_mount and
 * print_inspect_prompt.
 */
static char *root = NULL;

static void
free_strings (char **argv)
{
  int argc;

  for (argc = 0; argv[argc] != NULL; ++argc)
    free (argv[argc]);
  free (argv);
}

static int
count_strings (char *const *argv)
{
  int c;

  for (c = 0; argv[c]; ++c)
    ;
  return c;
}

static int
compare_keys_len (const void *p1, const void *p2)
{
  const char *key1 = * (char * const *) p1;
  const char *key2 = * (char * const *) p2;
  return strlen (key1) - strlen (key2);
}

static int
compare_keys (const void *p1, const void *p2)
{
  const char *key1 = * (char * const *) p1;
  const char *key2 = * (char * const *) p2;
  return strcasecmp (key1, key2);
}

/* This function implements the -i option. */
void
inspect_mount (void)
{
  char **roots = guestfs_inspect_os (g);
  if (roots == NULL)
    exit (EXIT_FAILURE);

  if (roots[0] == NULL) {
    fprintf (stderr, _("%s: no operating system was found on this disk\n"),
             program_name);
    exit (EXIT_FAILURE);
  }

  if (roots[1] != NULL) {
    fprintf (stderr, _("%s: multi-boot operating systems are not supported by the -i option\n"),
             program_name);
    exit (EXIT_FAILURE);
  }

  root = roots[0];
  free (roots);

  char **mountpoints = guestfs_inspect_get_mountpoints (g, root);
  if (mountpoints == NULL)
    exit (EXIT_FAILURE);

  /* Sort by key length, shortest key first, so that we end up
   * mounting the filesystems in the correct order.
   */
  qsort (mountpoints, count_strings (mountpoints) / 2, 2 * sizeof (char *),
         compare_keys_len);

  size_t i;
  for (i = 0; mountpoints[i] != NULL; i += 2) {
    int r;
    if (!read_only)
      r = guestfs_mount_options (g, "", mountpoints[i+1], mountpoints[i]);
    else
      r = guestfs_mount_ro (g, mountpoints[i+1], mountpoints[i]);
    if (r == -1)
      exit (EXIT_FAILURE);
  }

  free_strings (mountpoints);
}

/* This function is called only if the above function was called,
 * and only after we've printed the prompt in interactive mode.
 */
void
print_inspect_prompt (void)
{
  char *name = guestfs_inspect_get_product_name (g, root);
  if (STRNEQ (name, "unknown"))
    printf (_("Operating system: %s\n"), name);
  free (name);

  char **mountpoints = guestfs_inspect_get_mountpoints (g, root);
  if (mountpoints == NULL)
    return;

  /* Sort by key. */
  qsort (mountpoints, count_strings (mountpoints) / 2, 2 * sizeof (char *),
         compare_keys);

  size_t i;
  for (i = 0; mountpoints[i] != NULL; i += 2)
    printf (_("%s mounted on %s\n"), mountpoints[i+1], mountpoints[i]);

  free_strings (mountpoints);
}
