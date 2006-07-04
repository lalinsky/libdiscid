/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2006 Matthias Friedrich
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA

     $Id$

--------------------------------------------------------------------------- */
#ifndef MUSICBRAINZ_DISC_ID_H
#define MUSICBRAINZ_DISC_ID_H


#ifdef __cplusplus
  extern "C" {
#endif


/**
 * A transparent handle for an Audio CD.
 *
 * This is returned by discid_new() and has to be passed as the first
 * parameter to all discid_*() functions.
 */
typedef void *DiscId;


/**
 * Return a handle for a new DiscId object.
 *
 * If no memory could be allocated, NULL is returned. Don't use the created
 * DiscId object before calling discid_read().
 *
 * @return a DiscId object, or NULL.
 */
DiscId *discid_new();


/**
 * Release the memory allocated for the DiscId object.
 *
 * @param d a DiscId object created by discid_new()
 */
void discid_free(DiscId *d);


/**
 * Read the disc in the given CD-ROM/DVD-ROM drive.
 *
 * This function reads the disc in the drive specified by the given device
 * identifier. If the device is NULL, the default drive, as returned by
 * discid_get_default_device() is used.
 *
 * On error, this function returns false and sets the error message which you
 * can access using discid_get_error_msg(). In this case, the other functions
 * won't return meaningful values and should not be used.
 *
 * This function may be used multiple times with the same DiscId object.
 *
 * @param d a DiscId object created by discid_new()
 * @param device an operating system dependent device identifier, or NULL
 * @return 1 if successful, or 0 on error.
 */
int discid_read(DiscId *d, const char *device);


/**
 * Return a human-readable error message.
 *
 * This function may only be used if discid_read() failed. The returned
 * error message is only valid as long as the DiscId object exists.
 *
 * @param d a DiscId object created by discid_new()
 * @return a string describing the error that occurred
 */
char *discid_get_error_msg(DiscId *d);


/**
 * Return a MusicBrainz DiscID.
 *
 * The returned string is only valid as long as the DiscId object exists.
 *
 * @param d a DiscId object created by discid_new()
 * @return a string containing a MusicBrainz DiscID
 */
char *discid_get_id(DiscId *d);


/**
 * Return a FreeDB DiscID.
 *
 * The returned string is only valid as long as the DiscId object exists.
 *
 * @param d a DiscId object created by discid_new()
 * @return a string containing a FreeDB DiscID
 */
char *discid_get_freedb_id(DiscId *d);


/**
 * Return an URL for submitting the DiscID to MusicBrainz.
 *
 * The URL leads to an interactive disc submission wizard that guides the
 * user through the process of associating this disc's DiscID with a
 * release in the MusicBrainz database.
 *
 * The returned string is only valid as long as the DiscId object exists.
 *
 * @param d a DiscId object created by discid_new()
 * @return a string containing an URL
 */
char *discid_get_submission_url(DiscId *d);


/**
 * Return the name of the default disc drive for this operating system.
 *
 * @param a string containing an operating system dependent device identifier
 */
char *discid_get_default_device(void);


/**
 * Return the number of the first track on this disc.
 *
 * @param d a DiscId object created by discid_new()
 * @return the number of the first track
 */
int discid_get_first_track_num(DiscId *d);


/**
 * Return the number of the last track on this disc.
 *
 * @param d a DiscId object created by discid_new()
 * @return the number of the last track
 */
int discid_get_last_track_num(DiscId *d);


/**
 * Return the length of the disc in sectors.
 *
 * @param d a DiscId object created by discid_new()
 * @return the length of the disc in sectors
 */
int discid_get_sectors(DiscId *d);


/**
 * Return the sector offset of a track.
 *
 * Only track numbers between (and including) discid_get_first_track_num()
 * and discid_get_last_track_num() may be used.
 *
 * @param d a DiscId object created by discid_new()
 * @param track_num the number of a track
 * @return sector offset of the specified track
 */
int discid_get_track_offset(DiscId *d, int track_num);


/**
 * Return the length of a track in sectors.
 *
 * Only track numbers between (and including) discid_get_first_track_num()
 * and discid_get_last_track_num() may be used.
 *
 * @param d a DiscId object created by discid_new()
 * @param track_num the number of a track
 * @return length of the specified track
 */
int discid_get_track_length(DiscId *d, int track_num);


#ifdef __cplusplus
  }
#endif

#endif /* MUSICBRAINZ_DISC_ID_H */