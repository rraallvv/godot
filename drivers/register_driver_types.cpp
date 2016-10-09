/*************************************************************************/
/*  register_driver_types.cpp                                            */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2016 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
#include "register_driver_types.h"

#include "png/image_loader_png.h"
#include "png/resource_saver_png.h"
#include "webp/image_loader_webp.h"
#include "dds/texture_loader_dds.h"
#include "etc1/texture_loader_pkm.h"
#include "pvr/texture_loader_pvr.h"
#include "etc1/image_etc.h"
#include "chibi/event_stream_chibi.h"
#include "pnm/bitmap_loader_pnm.h"


#ifdef TOOLS_ENABLED
#include "squish/image_compress_squish.h"
#endif

#ifdef TOOLS_ENABLED
#include "convex_decomp/b2d_decompose.h"
#endif

#ifdef TOOLS_ENABLED
#include "platform/windows/export/export.h"
#endif

#ifdef TREMOR_ENABLED
#include "teora/audio_stream_ogg.h"
#endif

#ifdef VORBIS_ENABLED
#include "vorbis/audio_stream_ogg_vorbis.h"
#endif

#ifdef OPUS_ENABLED
#include "opus/audio_stream_opus.h"
#endif

#ifdef THEORA_ENABLED
#include "theora/video_stream_theora.h"
#endif


#include "drivers/nrex/regex.h"

#ifdef MUSEPACK_ENABLED
#include "mpc/audio_stream_mpc.h"
#endif

static ImageLoaderPNG *image_loader_png=NULL;
static ResourceSaverPNG *resource_saver_png=NULL;

#ifdef WEBP_ENABLED
static ImageLoaderWEBP *image_loader_webp=NULL;
#endif

#ifdef DDS_ENABLED
static ResourceFormatDDS *resource_loader_dds=NULL;
#endif

#ifdef ETC1_ENABLED
static ResourceFormatPKM *resource_loader_pkm=NULL;
#endif


#ifdef PVR_ENABLED
static ResourceFormatPVR *resource_loader_pvr=NULL;
#endif

#ifdef TREMOR_ENABLED
static ResourceFormatLoaderAudioStreamOGG *vorbis_stream_loader=NULL;
#endif

#ifdef VORBIS_ENABLED
static ResourceFormatLoaderAudioStreamOGGVorbis *vorbis_stream_loader=NULL;
#endif

#ifdef OPUS_ENABLED
static ResourceFormatLoaderAudioStreamOpus *opus_stream_loader=NULL;
#endif

#ifdef THEORA_ENABLED
static ResourceFormatLoaderVideoStreamTheora* theora_stream_loader = NULL;
#endif

#ifdef MUSEPACK_ENABLED
static ResourceFormatLoaderAudioStreamMPC * mpc_stream_loader=NULL;
#endif

#ifdef OPENSSL_ENABLED
#include "openssl/register_openssl.h"
#endif



static ResourceFormatPBM * pbm_loader=NULL;

void register_core_driver_types() {

	image_loader_png = memnew( ImageLoaderPNG );
	ImageLoader::add_image_format_loader( image_loader_png );

	resource_saver_png = memnew( ResourceSaverPNG );
	ResourceSaver::add_resource_format_saver(resource_saver_png);

#ifdef WEBP_ENABLED
	image_loader_webp = memnew( ImageLoaderWEBP );
	ImageLoader::add_image_format_loader( image_loader_webp );
#endif

	pbm_loader = memnew( ResourceFormatPBM );
	ResourceLoader::add_resource_format_loader(pbm_loader);

	ObjectTypeDB::register_type<RegEx>();
}

void unregister_core_driver_types() {

	if (image_loader_png)
		memdelete( image_loader_png );
	if (resource_saver_png)
		memdelete( resource_saver_png );

#ifdef WEBP_ENABLED
	if (image_loader_webp)
		memdelete( image_loader_webp );
#endif

	memdelete( pbm_loader );
}


void register_driver_types() {

#ifdef TREMOR_ENABLED
	vorbis_stream_loader=memnew( ResourceFormatLoaderAudioStreamOGG );
	ResourceLoader::add_resource_format_loader(vorbis_stream_loader );
	ObjectTypeDB::register_type<AudioStreamOGG>();
#endif

#ifdef VORBIS_ENABLED
	vorbis_stream_loader=memnew( ResourceFormatLoaderAudioStreamOGGVorbis );
	ResourceLoader::add_resource_format_loader(vorbis_stream_loader );
	ObjectTypeDB::register_type<AudioStreamOGGVorbis>();
#endif

#ifdef OPUS_ENABLED
	opus_stream_loader=memnew( ResourceFormatLoaderAudioStreamOpus );
	ResourceLoader::add_resource_format_loader( opus_stream_loader );
	ObjectTypeDB::register_type<AudioStreamOpus>();
#endif

#ifdef DDS_ENABLED
	resource_loader_dds = memnew( ResourceFormatDDS );
	ResourceLoader::add_resource_format_loader(resource_loader_dds );
#endif

#ifdef ETC1_ENABLED
	resource_loader_pkm = memnew( ResourceFormatPKM );
	ResourceLoader::add_resource_format_loader(resource_loader_pkm);
#endif

#ifdef PVR_ENABLED
	resource_loader_pvr = memnew( ResourceFormatPVR );
	ResourceLoader::add_resource_format_loader(resource_loader_pvr );
#endif

#ifdef TOOLS_ENABLED

	Geometry::_decompose_func=b2d_decompose;
#endif

#ifdef MUSEPACK_ENABLED

	mpc_stream_loader=memnew( ResourceFormatLoaderAudioStreamMPC );
	ResourceLoader::add_resource_format_loader(mpc_stream_loader);
	ObjectTypeDB::register_type<AudioStreamMPC>();

#endif

#ifdef OPENSSL_ENABLED

	register_openssl();
#endif

#ifdef THEORA_ENABLED
	theora_stream_loader = memnew( ResourceFormatLoaderVideoStreamTheora );
	ResourceLoader::add_resource_format_loader(theora_stream_loader);
	ObjectTypeDB::register_type<VideoStreamTheora>();
#endif


#ifdef TOOLS_ENABLED
#ifdef SQUISH_ENABLED

	Image::set_compress_bc_func(image_compress_squish);

#endif
#endif

#ifdef ETC1_ENABLED
	_register_etc1_compress_func();
#endif
	
	initialize_chibi();
}

void unregister_driver_types() {


#ifdef TREMOR_ENABLED
	memdelete( vorbis_stream_loader );
#endif

#ifdef VORBIS_ENABLED
	memdelete( vorbis_stream_loader );
#endif

#ifdef OPUS_ENABLED
	memdelete( opus_stream_loader );
#endif

#ifdef THEORA_ENABLED
	memdelete (theora_stream_loader);
#endif


#ifdef MUSEPACK_ENABLED

	memdelete (mpc_stream_loader);
#endif

#ifdef DDS_ENABLED
	memdelete(resource_loader_dds);
#endif

#ifdef ETC1_ENABLED
	memdelete(resource_loader_pkm);
#endif

#ifdef PVR_ENABLED
	memdelete(resource_loader_pvr);
#endif

#ifdef OPENSSL_ENABLED

	unregister_openssl();
#endif

	finalize_chibi();
}
