/* libguestfs - the guestfsd daemon
 * Copyright (C) 2009 Red Hat Inc.
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

#include "../src/guestfs_protocol.h"
#include "daemon.h"
#include "actions.h"

char *
do_command (char **argv)
{
  char *out, *err;
  int r;
  char *sysroot_dev, *sysroot_dev_pts, *sysroot_proc,
    *sysroot_selinux, *sysroot_sys;
  int dev_ok, dev_pts_ok, proc_ok, selinux_ok, sys_ok;

  /* We need a root filesystem mounted to do this. */
  NEED_ROOT (return NULL);

  /* Conveniently, argv is already a NULL-terminated argv-style array
   * of parameters, so we can pass it straight in to our internal
   * commandv.  We just have to check the list is non-empty.
   */
  if (argv[0] == NULL) {
    reply_with_error ("command: passed an empty list");
    return NULL;
  }

  /* While running the command, bind-mount /dev, /proc, /sys
   * into the chroot.  However we must be careful to unmount them
   * afterwards because otherwise they would interfere with
   * future mount and unmount operations.
   *
   * We deliberately allow these commands to fail silently, BUT
   * if a mount fails, don't unmount the corresponding mount.
   */
  sysroot_dev = sysroot_path ("/dev");
  sysroot_dev_pts = sysroot_path ("/dev/pts");
  sysroot_proc = sysroot_path ("/proc");
  sysroot_selinux = sysroot_path ("/selinux");
  sysroot_sys = sysroot_path ("/sys");

  if (sysroot_dev == NULL || sysroot_dev_pts == NULL ||
      sysroot_proc == NULL || sysroot_selinux == NULL ||
      sysroot_sys == NULL) {
    reply_with_perror ("malloc");
    free (sysroot_dev);
    free (sysroot_dev_pts);
    free (sysroot_proc);
    free (sysroot_selinux);
    free (sysroot_sys);
    return NULL;
  }

  r = command (NULL, NULL, "mount", "--bind", "/dev", sysroot_dev, NULL);
  dev_ok = r != -1;
  r = command (NULL, NULL, "mount", "--bind", "/dev/pts", sysroot_dev_pts, NULL);
  dev_pts_ok = r != -1;
  r = command (NULL, NULL, "mount", "--bind", "/proc", sysroot_proc, NULL);
  proc_ok = r != -1;
  r = command (NULL, NULL, "mount", "--bind", "/selinux", sysroot_selinux, NULL);
  selinux_ok = r != -1;
  r = command (NULL, NULL, "mount", "--bind", "/sys", sysroot_sys, NULL);
  sys_ok = r != -1;

  CHROOT_IN;
  r = commandv (&out, &err, argv);
  CHROOT_OUT;

  if (sys_ok) command (NULL, NULL, "umount", sysroot_sys, NULL);
  if (selinux_ok) command (NULL, NULL, "umount", sysroot_selinux, NULL);
  if (proc_ok) command (NULL, NULL, "umount", sysroot_proc, NULL);
  if (dev_pts_ok) command (NULL, NULL, "umount", sysroot_dev_pts, NULL);
  if (dev_ok) command (NULL, NULL, "umount", sysroot_dev, NULL);

  free (sysroot_dev);
  free (sysroot_dev_pts);
  free (sysroot_proc);
  free (sysroot_selinux);
  free (sysroot_sys);

  if (r == -1) {
    reply_with_error ("%s", err);
    free (out);
    free (err);
    return NULL;
  }

  free (err);

  return out;			/* Caller frees. */
}

char **
do_command_lines (char **argv)
{
  char *out;
  char **lines;

  out = do_command (argv);
  if (out == NULL)
    return NULL;

  lines = split_lines (out);
  free (out);

  if (lines == NULL)
    return NULL;

  return lines;			/* Caller frees. */
}

char *
do_sh (const char *command)
{
  char *argv[] = { "/bin/sh", "-c", command, NULL };

  return do_command (argv);
}

char **
do_sh_lines (const char *command)
{
  char *argv[] = { "/bin/sh", "-c", command, NULL };

  return do_command_lines (argv);
}
