/*
 * This file is part of MPlayer.
 *
 * MPlayer is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * MPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with MPlayer; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>

#include "mp_msg.h"

/* maximum message length of mp_msg */
#define MSGSIZE_MAX 3072

int mp_msg_levels[MSGT_MAX]; // verbose level of this module. initialized to -2
int mp_msg_level_all = MSGL_STATUS;
int verbose = 0;
int mp_msg_color = 0;
int mp_msg_module = 0;

const char* filename_recode(const char* filename) {
    return filename;
}

void mp_msg_init(void) {
    for(int i = 0; i < MSGT_MAX; ++i) {
        mp_msg_levels[i] = -2;
    }
    mp_msg_levels[MSGT_IDENTIFY] = -1; // no -identify output by default
}

int mp_msg_test(int mod, int lev) {
    return lev <= (mp_msg_levels[mod] == -2 ? mp_msg_level_all + verbose : mp_msg_levels[mod]);
}

static void set_msg_color(FILE* stream, int lev) {
    static const unsigned char v_colors[10] = {9, 1, 3, 15, 7, 2, 2, 8, 8, 8};
    int c = v_colors[lev];
    if (mp_msg_color)
        fprintf(stream, "\033[%d;3%dm", c >> 3, c & 7);
}

static void print_msg_module(FILE* stream, int mod) {
    static const char *module_text[MSGT_MAX] = {
        "GLOBAL",
        "CPLAYER",
        "GPLAYER",
        "VIDEOOUT",
        "AUDIOOUT",
        "DEMUXER",
        "DS",
        "DEMUX",
        "HEADER",
        "AVSYNC",
        "AUTOQ",
        "CFGPARSER",
        "DECAUDIO",
        "DECVIDEO",
        "SEEK",
        "WIN32",
        "OPEN",
        "DVD",
        "PARSEES",
        "LIRC",
        "STREAM",
        "CACHE",
        "MENCODER",
        "XACODEC",
        "TV",
        "OSDEP",
        "SPUDEC",
        "PLAYTREE",
        "INPUT",
        "VFILTER",
        "OSD",
        "NETWORK",
        "CPUDETECT",
        "CODECCFG",
        "SWS",
        "VOBSUB",
        "SUBREADER",
        "AFILTER",
        "NETST",
        "MUXER",
        "OSDMENU",
        "IDENTIFY",
        "RADIO",
        "ASS",
        "LOADER",
        "STATUSLINE",
    };
    int c2 = (mod + 1) % 15 + 1;

    if (!mp_msg_module)
        return;
    if (mp_msg_color)
        fprintf(stream, "\033[%d;3%dm", c2 >> 3, c2 & 7);
    fprintf(stream, "%9s", module_text[mod]);
    if (mp_msg_color)
        fprintf(stream, "\033[0;37m");
    fprintf(stream, ": ");
}

void mp_msg(int mod, int lev, const char *format, ... ){
    va_list va;
    va_start(va, format);
    mp_msg_va(mod, lev, format, va);
    va_end(va);
}

void mp_msg_va(int mod, int lev, const char *format, va_list va){
    char tmp[MSGSIZE_MAX];
    FILE *stream = lev <= MSGL_WARN ? stderr : stdout;
    static int header = 1;
    // indicates if last line printed was a status line
    static int statusline;
    size_t len;

    if (!mp_msg_test(mod, lev)) return; // do not display
    vsnprintf(tmp, MSGSIZE_MAX, format, va);
    tmp[MSGSIZE_MAX-2] = '\n';
    tmp[MSGSIZE_MAX-1] = 0;

    // as a status line normally is intended to be overwitten by next status line
    // output a '\n' to get a normal message on a separate line
    if (statusline && lev != MSGL_STATUS) fprintf(stream, "\n");
    statusline = lev == MSGL_STATUS;

    if (header)
        print_msg_module(stream, mod);
    set_msg_color(stream, lev);
    len = strlen(tmp);
    header = len && (tmp[len-1] == '\n' || tmp[len-1] == '\r');

    fprintf(stream, "%s", tmp);
    if (mp_msg_color)
        fprintf(stream, "\033[0m");
    fflush(stream);
}
