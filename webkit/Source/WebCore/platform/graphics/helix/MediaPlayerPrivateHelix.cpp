/*
 * Copyright (C) 2007, 2009 Apple Inc.  All rights reserved.
 * Copyright (C) 2007 Collabora Ltd.  All rights reserved.
 * Copyright (C) 2007 Alp Toker <alp@atoker.com>
 * Copyright (C) 2009 Gustavo Noronha Silva <gns@gnome.org>
 * Copyright (C) 2009, 2010 Igalia S.L
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * aint with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "config.h"

#if ENABLE(VIDEO) && USE(GSTREAMER)

#include "ColorSpace.h"
#include "IntRect.h"
#include "KURL.h"
#include "MIMETypeRegistry.h"
#include "MediaPlayer.h"
#include "NotImplemented.h"
#include "SecurityOrigin.h"
#include "TimeRanges.h"
#include <limits>
#include <math.h>
#include <wtf/gobject/GOwnPtr.h>
#include <wtf/text/CString.h>
#include <wtf/text/WTFString.h>
#include <stdio.h>
#include "MediaPlayerPrivateHelix.h"

#define MAX_PATH 1024

namespace WebCore {


static HashSet<String> mimeTypeCache();

MediaPlayerPrivateHelix::~MediaPlayerPrivateHelix()
{
    m_PlayerDriver->enqueueCommand(new PlayerQuit(0,0));
    if(m_DataSourcePath)
    {
        free(m_DataSourcePath);
        m_DataSourcePath = NULL;
    }
    HX_DELETE(m_PlayerDriver);
}

PassOwnPtr<MediaPlayerPrivateInterface> MediaPlayerPrivateHelix::create(MediaPlayer* player)
{
	printf("MediaPlayerPrivateHelix::create ");
    return adoptPtr(new MediaPlayerPrivateHelix(player));
}

void MediaPlayerPrivateHelix::registerMediaEngine(MediaEngineRegistrar registrar)
{
    registrar(create, getSupportedTypes, supportsType, 0, 0, 0);
}

void MediaPlayerPrivateHelix::load(const String &url)
{
    m_Duration = 0;
    m_VideoWidth = 0;
    m_VideoHeight = 0;

	printf("HelixOverWebkit [%s] [%s] [%d] setDataSource %s\n",
			__FILE__, __FUNCTION__, __LINE__, url.utf8().data());
    KURL kurl(KURL(), url);
    String cleanUrl(url);

    // Clean out everything after file:// url path.
    if (kurl.isLocalFile())
        cleanUrl = cleanUrl.substring(0, kurl.pathEnd());

    if(m_DataSourcePath)
    {
        free(m_DataSourcePath);
        m_DataSourcePath = NULL;
    }
    m_DataSourcePath = strdup(cleanUrl.utf8().data());
    m_PlayerDriver->enqueueCommand(new PlayerSetDataSource(m_DataSourcePath,0,0));
	printf("HelixOverWebkit [%s] [%s] [%d]", __FILE__, __FUNCTION__, __LINE__);
}

void MediaPlayerPrivateHelix::cancelLoad()
{
	printf("HelixOverWebkit [%s] [%s] [%d]", __FILE__, __FUNCTION__, __LINE__);
    if (m_networkState < MediaPlayer::Loading || m_networkState == MediaPlayer::Loaded)
        return;
}


void MediaPlayerPrivateHelix::prepareToPlay()
{
	printf("HelixOverWebkit [%s] [%s] [%d]", __FILE__, __FUNCTION__, __LINE__);
	m_PlayerDriver->enqueueCommand(new PlayerPrepare(0,0));
}

void MediaPlayerPrivateHelix::play()
{
	printf("HelixOverWebkit [%s] [%s] [%d]", __FILE__, __FUNCTION__, __LINE__);
    m_bIsPlaying = true;
    m_bPlayerStarted = true;
    m_PlayerDriver->m_bEnableSendEvent = true;
    m_PlayerDriver->enqueueCommand(new PlayerStart(0,0));
	printf("HelixOverWebkit [%s] [%s] [%d]", __FILE__, __FUNCTION__, __LINE__);
}

void MediaPlayerPrivateHelix::pause()
{
    m_bPlayerStarted = false;
    m_PlayerDriver->enqueueCommand(new PlayerPause(0,0));
}


// TODO: m_VideoWidth/m_VideoHeight always being 0 at present
IntSize MediaPlayerPrivateHelix::naturalSize() const
{
    if (!hasVideo())
        return IntSize();

    IntSize m_videoSize = IntSize(static_cast<int>(m_VideoWidth), static_cast<int>(m_VideoHeight));
    return m_videoSize;
}

void MediaPlayerPrivateHelix::setVisible(bool)
{
}

float MediaPlayerPrivateHelix::duration() const
{
	return m_Duration;
}

void MediaPlayerPrivateHelix::setDuration(int duration)
{
	m_Duration = duration;
}

void MediaPlayerPrivateHelix::setPlayerState(int state)
{
 MediaPlayer::NetworkState oldNetworkState = m_networkState;
 MediaPlayer::ReadyState oldReadyState = m_readyState;
	switch(state)
	{
	case 3:
        m_readyState = MediaPlayer::HaveMetadata;
        m_networkState = MediaPlayer::Empty;
	case 5:
        m_readyState = MediaPlayer::HaveCurrentData;
        m_networkState = MediaPlayer::Loading;
        break;
	case 6:
        m_readyState = MediaPlayer::HaveFutureData;
        m_networkState = MediaPlayer::Loading;
					break;
	default:
					break;
	}
    if (m_networkState != oldNetworkState) {
        m_player->networkStateChanged();
    		}
    if (m_readyState != oldReadyState) {
        m_player->readyStateChanged();
    		}
}

float MediaPlayerPrivateHelix::currentTime() const
{

}

void MediaPlayerPrivateHelix::seek(float time)
{

}

bool MediaPlayerPrivateHelix::seeking() const
{

}

bool MediaPlayerPrivateHelix::paused() const
{

}

void MediaPlayerPrivateHelix::setRate(float)
{

}

void MediaPlayerPrivateHelix::setVolume(float)
{

}

MediaPlayer::NetworkState MediaPlayerPrivateHelix::networkState() const
{
	return m_networkState;
}

MediaPlayer::ReadyState MediaPlayerPrivateHelix::readyState() const
{
	return m_readyState;
}

float MediaPlayerPrivateHelix::maxTimeSeekable() const
{
	return m_Duration;
}

PassRefPtr<TimeRanges> MediaPlayerPrivateHelix::buffered() const
{
    RefPtr<TimeRanges> timeRanges = TimeRanges::create();
    // TODO: how to retrieve real duration
    //float loaded = maxTimeLoaded();
    float loaded = m_Duration;
    if (loaded > 0)
    		timeRanges->add(0, loaded);
    return timeRanges.release();
}

bool MediaPlayerPrivateHelix::didLoadingProgress() const
{

}

void MediaPlayerPrivateHelix::setSize(const IntSize&)
{

}

void MediaPlayerPrivateHelix::paint(GraphicsContext*, const IntRect&)
{

}

bool MediaPlayerPrivateHelix::IsPlayerStarted()
{
	return m_bPlayerStarted;
}

MediaPlayerPrivateHelix::MediaPlayerPrivateHelix(MediaPlayer* player)
    : m_bInit(false)
		, m_player(player)
		, m_networkState(MediaPlayer::Empty)
		, m_readyState(MediaPlayer::HaveNothing)
		, m_eState(-1)
		, m_Duration(-1)
		, m_bIsPlaying(false)
		, m_bPlayerStarted(false)
		, m_DataSourcePath(NULL)
		, m_hasAudio(true)
		, m_hasVideo(false)
{
    m_PlayerDriver = new PlayerDriver(this);
    m_bInit = m_PlayerDriver->SetupPlaybackEngine();
    printf("MediaPlayerPrivateHelix %p\n", this);
}

void MediaPlayerPrivateHelix::getSupportedTypes(HashSet<String>& types)
{
    types = mimeTypeCache();
}

MediaPlayer::SupportsType MediaPlayerPrivateHelix::supportsType(const String& type, const String& codecs, const KURL&)
{
    if (type.isNull() || type.isEmpty())
        return MediaPlayer::IsNotSupported;

    // spec says we should not return "probably" if the codecs string is empty
    if (mimeTypeCache().contains(type))
        return codecs.isEmpty() ? MediaPlayer::MayBeSupported : MediaPlayer::IsSupported;
    return MediaPlayer::IsNotSupported;
}

static HashSet<String> mimeTypeCache()
{
    DEFINE_STATIC_LOCAL(HashSet<String>, cache, ());
    static bool typeListInitialized = false;

    if (typeListInitialized)
        return cache;
    const char* mimeTypes[] = {"application/ogg",
                               "application/vnd.apple.mpegurl",
                               "application/vnd.rn-realmedia",
                               "application/x-3gp",
                               "application/x-pn-realaudio",
                               "audio/3gpp",
                               "audio/aac",
                               "audio/flac",
                               "audio/iLBC-sh",
                               "audio/midi",
                               "audio/mobile-xmf",
                               "audio/mp1",
                               "audio/mp2",
                               "audio/mp3",
                               "audio/mp4",
                               "audio/mpeg",
                               "audio/ogg",
                               "audio/qcelp",
                               "audio/riff-midi",
                               "audio/wav",
                               "audio/webm",
                               "audio/x-ac3",
                               "audio/x-aiff",
                               "audio/x-amr-nb-sh",
                               "audio/x-amr-wb-sh",
                               "audio/x-au",
                               "audio/x-ay",
                               "audio/x-celt",
                               "audio/x-dts",
                               "audio/x-flac",
                               "audio/x-gbs",
                               "audio/x-gsm",
                               "audio/x-gym",
                               "audio/x-imelody",
                               "audio/x-ircam",
                               "audio/x-kss",
                               "audio/x-m4a",
                               "audio/x-mod",
                               "audio/x-mp3",
                               "audio/x-mpeg",
                               "audio/x-musepack",
                               "audio/x-nist",
                               "audio/x-nsf",
                               "audio/x-paris",
                               "audio/x-sap",
                               "audio/x-sbc",
                               "audio/x-sds",
                               "audio/x-shorten",
                               "audio/x-sid",
                               "audio/x-spc",
                               "audio/x-speex",
                               "audio/x-svx",
                               "audio/x-ttafile",
                               "audio/x-vgm",
                               "audio/x-voc",
                               "audio/x-vorbis+ogg",
                               "audio/x-w64",
                               "audio/x-wav",
                               "audio/x-wavpack",
                               "audio/x-wavpack-correction",
                               "video/3gpp",
                               "video/mj2",
                               "video/mp4",
                               "video/mpeg",
                               "video/mpegts",
                               "video/ogg",
                               "video/quicktime",
                               "video/vivo",
                               "video/webm",
                               "video/x-cdxa",
                               "video/x-dirac",
                               "video/x-dv",
                               "video/x-fli",
                               "video/x-flv",
                               "video/x-h263",
                               "video/x-ivf",
                               "video/x-m4v",
                               "video/x-matroska",
                               "video/x-mng",
                               "video/x-ms-asf",
                               "video/x-msvideo",
                               "video/x-mve",
                               "video/x-nuv",
                               "video/x-vcd"};

    for (unsigned i = 0; i < (sizeof(mimeTypes) / sizeof(*mimeTypes)); ++i)
        cache.add(String(mimeTypes[i]));

    typeListInitialized = true;
    return cache;
}
}
#endif // USE(GSTREAMER)
