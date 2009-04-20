/* libguestfs generated file
 * WARNING: THIS FILE IS GENERATED BY 'src/generator.ml'.
 * ANY CHANGES YOU MAKE TO THIS FILE WILL BE LOST.
 *
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "../src/guestfs_protocol.h"

extern int do_mount (const char *device, const char *mountpoint);
extern int do_sync (void);
extern int do_touch (const char *path);
extern char *do_cat (const char *path);
extern char *do_ll (const char *directory);
extern char **do_ls (const char *directory);
extern char **do_list_devices (void);
extern char **do_list_partitions (void);
extern char **do_pvs (void);
extern char **do_vgs (void);
extern char **do_lvs (void);
extern guestfs_lvm_int_pv_list *do_pvs_full (void);
extern guestfs_lvm_int_vg_list *do_vgs_full (void);
extern guestfs_lvm_int_lv_list *do_lvs_full (void);
extern char **do_read_lines (const char *path);
extern int do_aug_init (const char *root, int flags);
extern int do_aug_close (void);
extern int do_aug_defvar (const char *name, const char *expr);
extern guestfs_aug_defnode_ret *do_aug_defnode (const char *name, const char *expr, const char *val);
extern char *do_aug_get (const char *path);
extern int do_aug_set (const char *path, const char *val);
extern int do_aug_insert (const char *path, const char *label, int before);
extern int do_aug_rm (const char *path);
extern int do_aug_mv (const char *src, const char *dest);
extern char **do_aug_match (const char *path);
extern int do_aug_save (void);
extern int do_aug_load (void);
extern char **do_aug_ls (const char *path);
extern int do_rm (const char *path);
extern int do_rmdir (const char *path);
extern int do_rm_rf (const char *path);
extern int do_mkdir (const char *path);
extern int do_mkdir_p (const char *path);
extern int do_chmod (int mode, const char *path);
extern int do_chown (int owner, int group, const char *path);
extern int do_exists (const char *path);
extern int do_is_file (const char *path);
extern int do_is_dir (const char *path);
extern int do_pvcreate (const char *device);
extern int do_vgcreate (const char *volgroup, char * const* const physvols);
extern int do_lvcreate (const char *logvol, const char *volgroup, int mbytes);
extern int do_mkfs (const char *fstype, const char *device);
extern int do_sfdisk (const char *device, int cyls, int heads, int sectors, char * const* const lines);
extern int do_write_file (const char *path, const char *content, int size);
extern int do_umount (const char *pathordevice);
extern char **do_mounts (void);
extern int do_umount_all (void);
extern int do_lvm_remove_all (void);
extern char *do_file (const char *path);
extern char *do_command (char * const* const arguments);
extern char **do_command_lines (char * const* const arguments);
extern guestfs_int_stat *do_stat (const char *path);
extern guestfs_int_stat *do_lstat (const char *path);
extern guestfs_int_statvfs *do_statvfs (const char *path);
extern char **do_tune2fs_l (const char *device);
extern int do_blockdev_setro (const char *device);
extern int do_blockdev_setrw (const char *device);
extern int do_blockdev_getro (const char *device);
extern int do_blockdev_getss (const char *device);
extern int do_blockdev_getbsz (const char *device);
extern int do_blockdev_setbsz (const char *device, int blocksize);
extern int64_t do_blockdev_getsz (const char *device);
extern int64_t do_blockdev_getsize64 (const char *device);
extern int do_blockdev_flushbufs (const char *device);
extern int do_blockdev_rereadpt (const char *device);
extern int do_upload (const char *remotefilename);
extern int do_download (const char *remotefilename);
extern char *do_checksum (const char *csumtype, const char *path);
extern int do_tar_in (const char *directory);
extern int do_tar_out (const char *directory);
extern int do_tgz_in (const char *directory);
extern int do_tgz_out (const char *directory);
