#ifndef AV_RB32   // R: AV_RB32 for older ffmpeg (libavutil) releases
#ifndef __GNUC__  // only implemented the GCC version of AV_RB32
#error "Get a newer ffmpeg (libavutil) version"
#endif

/*
code taken from ffmpeg/libavutil. intreadwrite.h and bswap.h

common.h is copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
bswap.h is copyright (C) 2006 by Michael Niedermayer <michaelni@gmx.at>
intreadwrite.h does not contain a specific copyright notice.

the code is licensed under LGPL 2 with the following license header

FFmpeg is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

FFmpeg is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with FFmpeg; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

union unaligned_32 {
  uint32_t l;
} __attribute__((packed)) __attribute__((may_alias));
#define AV_RN32(p) (((const union unaligned_32 *)(p))->l)

#ifdef AV_HAVE_BIGENDIAN  // TODO add detection

#define AV_RB32(p) AV_RN32(p)

#else  // little endian
static __attribute__((always_inline)) inline uint32_t __attribute__((const))
av_bswap32(uint32_t x) {
  x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0x00FF00FF);
  x = (x >> 16) | (x << 16);
  return x;
}

#define AV_RB32(p) av_bswap32(AV_RN32(p))

#endif  // AV_HAVE_BIG_ENDIAN
#endif  // AV_RB32
