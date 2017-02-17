(* mllib
 * Copyright (C) 2009-2017 Red Hat Inc.
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
 *)

(** Common Windows Registry types and functions. *)

type node = int64
type value = int64

val with_hive_readonly : Guestfs.guestfs -> string -> (node -> 'a) -> 'a
val with_hive_write : Guestfs.guestfs -> string -> (node -> 'a) -> 'a
(** [with_hive_(readonly|write) g hive_filename f]
    are wrappers that handle opening and closing the hive
    named [hive_filename] around a function [f].

    [with_hive_readonly] opens the hive for read-only (attempts
    to write will throw an error).  [with_hive_write] opens the
    hive for writes, and commits the changes at the end if there
    were no errors. *)

val get_node : Guestfs.guestfs -> node -> string list -> node option
(** [get_node g root path] starts at the [root] node of the hive (it does
    not need to be the actual hive root), and searches down the [path].
    It returns [Some node] of the final node if found, or [None] if
    not found. *)

val encode_utf16le : string -> string
(** Helper: Take a 7 bit ASCII string and encode it as UTF-16LE. *)

val decode_utf16le : string -> string
(** Helper: Take a UTF-16LE string and decode it to UTF-8. *)