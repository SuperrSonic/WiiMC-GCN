/*
 * Raw FLAC picture parser
 *
 * This file is part of Libav.
 *
 * Libav is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * Libav is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Libav; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "avformat.h"
#include "flac_picture.h"
#include "id3v2.h"
#include "internal.h"

// WiiMC stuff
#include <malloc.h>
extern uint8_t *pos_pic;
extern unsigned epic_size;
extern unsigned bannerSSactive;
extern int menuCurrent;
extern int embedded_pic;

//extern int flac_find;

#if 0

#else
int ff_flac_parse_picture(AVFormatContext *s, uint8_t *buf, int buf_size)
{
//	return 0;
#if 1
	// skip for banner ss
	if(bannerSSactive || menuCurrent != 1)
		return 0;

    const CodecMime *mime = ff_id3v2_mime_tags;
    enum CodecID id = CODEC_ID_NONE;
//    AVBufferRef *data = NULL;
    uint8_t mimetype[64], *desc = NULL;
    AVIOContext *pb = NULL;
//    AVStream *st;
    int type, width, height;
    int len, ret = 0;
	
	if(buf_size < 34) {
		return 0;
	}

    pb = avio_alloc_context(buf, buf_size, 0, NULL, NULL, NULL, NULL);
    if (!pb)
        return AVERROR(ENOMEM);


//flac_find = type;

#if 0
pos_pic = (uint8_t *)memalign(32, buf_size);
avio_read(pb, pos_pic, buf_size);

FILE * fp = fopen("sd1:/dump_data.bin", "wb");

fwrite(pos_pic, 1, buf_size, fp);
fclose(fp);
return 0;
#endif

    /* read the picture type */
    type = avio_rb32(pb);
    if (type >= FF_ARRAY_ELEMS(ff_id3v2_picture_types) || type < 0) {
        av_log(s, AV_LOG_ERROR, "Invalid picture type: %d.\n", type);
        if (s->error_recognition & AV_EF_EXPLODE) {
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }
        type = 0;
    }
//flac_find = 1;
    /* picture mimetype */
    len = avio_rb32(pb);
    if (len <= 0 ||
        avio_read(pb, mimetype, FFMIN(len, sizeof(mimetype) - 1)) != len) {
        av_log(s, AV_LOG_ERROR, "Could not read mimetype from an attached "
               "picture.\n");
        if (s->error_recognition & AV_EF_EXPLODE)
            ret = AVERROR_INVALIDDATA;
        goto fail;
    }
	//flac_find = 2;
    mimetype[len] = 0;
#if 1
    while (mime->id != CODEC_ID_NONE) {
        if (!strncmp(mime->str, mimetype, sizeof(mimetype))) {
            id = mime->id;
            break;
        }
        mime++;
    }
#endif
#if 1
    if (id == CODEC_ID_NONE) {
        av_log(s, AV_LOG_ERROR, "Unk pic mimetype: %s.\n",
               mimetype);
        if (s->error_recognition & AV_EF_EXPLODE)
            ret = AVERROR_INVALIDDATA;
        goto fail;
    }
	//flac_find = 3;
#endif
#if 1
    /* picture description */
    len = avio_rb32(pb);
#if 1
    if (len > 0) {
        if (!(desc = av_malloc(len + 1))) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        if (avio_read(pb, desc, len) != len) {
            av_log(s, AV_LOG_ERROR, "Error reading attached picture description.\n");
            if (s->error_recognition & AV_EF_EXPLODE)
                ret = AVERROR(EIO);
            goto fail;
        }
        desc[len] = 0;
    }
#endif
#endif
//flac_find = 4;
    /* picture metadata */
    width  = avio_rb32(pb);
    height = avio_rb32(pb);
    avio_skip(pb, 8);
	
	//flac_find = height;

    /* picture data */
    len = avio_rb32(pb);
    if (len <= 0) {
        av_log(s, AV_LOG_ERROR, "Invalid attached picture size: %d.\n", len);
        if (s->error_recognition & AV_EF_EXPLODE)
            ret = AVERROR_INVALIDDATA;
	//	flac_find = 33;
        goto fail;
    }
//flac_find = 3;
	// Limit the size
	if(len > 1*1024*1024)
		len = 1*1024*1024;
	epic_size = len;
	pos_pic = (uint8_t *)memalign(32, epic_size);
	
    if (avio_read(pb, pos_pic, len) != len) {
        av_log(s, AV_LOG_ERROR, "Error reading attached picture data.\n");
        if (s->error_recognition & AV_EF_EXPLODE)
            ret = AVERROR(EIO);
        goto fail;
    }
	
	embedded_pic = 1;
//flac_find = 7;
#if 0
    st = avformat_new_stream(s, NULL);
    if (!st) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    av_init_packet(&st->attached_pic);
    st->attached_pic.buf          = data;
    st->attached_pic.data         = data->data;
    st->attached_pic.size         = len;
    st->attached_pic.stream_index = st->index;
    st->attached_pic.flags       |= AV_PKT_FLAG_KEY;

    st->disposition      |= AV_DISPOSITION_ATTACHED_PIC;
    st->codec->codec_type = AVMEDIA_TYPE_VIDEO;
//    st->codec->codec_id   = id;
 //   st->codec->width      = width;
 //   st->codec->height     = height;
 //   av_dict_set(&st->metadata, "comment", ff_id3v2_picture_types[type], 0);
 //   if (desc)
  //      av_dict_set(&st->metadata, "title", desc, AV_DICT_DONT_STRDUP_VAL);
#endif

    av_freep(&pb);

    return 0;

fail:
  //  av_buffer_unref(&data);
    av_freep(&desc);
    av_freep(&pb);

    return ret;
#endif
}
#endif