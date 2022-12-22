#ifdef _WIN32
#pragma warning(disable:6258)

#include"string"
#pragma warning(disable:6305)

#ifndef MIDI_h
#define MIDI_h

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include"windows.h"
#include <mmsystem.h>
#pragma message("linking with multimedia library")
#pragma comment(lib, "winmm.lib")

#include <vector>
using namespace std;


// This message is sent to the controlling window, if the volume changes in
// another way than explicitly set by the owner of the CMIDI object.
// WPARAM	the pointer to the MIDI object
// LPARAM	lo-word: the number of the channel that changed volume
//			hi-word: the new volume in percent
#define	WM_MIDI_VOLUMECHANGED	WM_USER+23


#define MIDI_CTRLCHANGE			((BYTE)0xB0)		// + ctrlr + value
#define MIDI_PRGMCHANGE			((BYTE)0xC0)		// + new patch
#define MIDI_CHANPRESS			((BYTE)0xD0)		// + pressure (1 byte)

#define MIDICTRL_VOLUME			((BYTE)0x07)

#define MIDIEVENT_CHANNEL(dw)	(dw & 0x0000000F)
#define MIDIEVENT_TYPE(dw)		(dw & 0x000000F0)
#define MIDIEVENT_DATA1(dw)		((dw & 0x0000FF00) >> 8)
#define MIDIEVENT_VOLUME(dw)	((dw & 0x007F0000) >> 16)

#define MIDI_SYSEX				((BYTE)0xF0)		// SysEx begin
#define MIDI_SYSEXEND			((BYTE)0xF7)		// SysEx end
#define MIDI_META				((BYTE)0xFF)		// Meta event begin
#define MIDI_META_TEMPO			((BYTE)0x51)		// Tempo change
#define MIDI_META_EOT			((BYTE)0x2F)		// End-of-track


// flags for the ConvertToBuffer() method
#define CONVERTF_RESET				0x00000001
#define CONVERTF_STATUS_DONE		0x00000001
#define CONVERTF_STATUS_STUCK		0x00000002
#define CONVERTF_STATUS_GOTEVENT	0x00000004

// Return values from the ConvertToBuffer() method
#define CONVERTERR_NOERROR		0		// No error occured
#define CONVERTERR_CORRUPT		-101	// The input file is corrupt
// The converter has already encountered a corrupt file and cannot convert any
// more of this file -- must reset the converter
#define CONVERTERR_STUCK		-102
#define CONVERTERR_DONE			-103	// Converter is done
#define CONVERTERR_BUFFERFULL	-104	// The buffer is full
#define CONVERTERR_METASKIP		-105	// Skipping unknown meta event

#define STATUS_KILLCALLBACK		100		// Signals that the callback should die
#define STATUS_CALLBACKDEAD		200		// Signals callback is done processing
#define STATUS_WAITINGFOREND	300		// Callback's waiting for buffers to play

// Description of a track
//
struct TRACK
{
	DWORD	fdwTrack;		// Track's flags
	DWORD	dwTrackLength;	// Total bytes in track
	LPBYTE	pTrackStart;	// -> start of track data buffer
	LPBYTE	pTrackCurrent;	// -> next byte to read in buffer
	DWORD	tkNextEventDue;	// Absolute time of next event in track
	BYTE	byRunningStatus;// Running status from last channel msg

	TRACK()
		: fdwTrack(0)
		, dwTrackLength(0)
		, pTrackStart(0)
		, pTrackCurrent(0)
		, tkNextEventDue(0)
		, byRunningStatus(0)
	{
	}
};

#define ITS_F_ENDOFTRK		0x00000001


// This structure is used to pass information to the ConvertToBuffer()
// system and then internally by that function to send information about the
// target stream buffer and current state of the conversion process to internal
// lower level conversion routines.
struct CONVERTINFO
{
	MIDIHDR	mhBuffer;			// Standard Windows stream buffer header
	DWORD	dwStartOffset;		// Start offset from mhStreamBuffer.lpStart
	DWORD	dwMaxLength;		// Max length to convert on this pass
	DWORD	dwBytesRecorded;
	DWORD	tkStart;
	BOOL	bTimesUp;

	CONVERTINFO()
		: dwStartOffset(0)
		, dwMaxLength(0)
		, dwBytesRecorded(0)
		, tkStart(0)
		, bTimesUp(FALSE)
	{
		memset(&mhBuffer, 0, sizeof(MIDIHDR));
	}
};

// Temporary event structure which stores event data until we're ready to
// dump it into a stream buffer
struct TEMPEVENT
{
	DWORD	tkEvent;		// Absolute time of event
	BYTE	byShortData[4];	// Event type and parameters if channel msg
	DWORD	dwEventLength;	// Length of data which follows if meta or sysex
	LPBYTE	pLongData;		// -> Event data if applicable
};

class CMIDI
{
protected:
	typedef vector<TRACK>		TrackArray_t;
	typedef vector<DWORD>		VolumeArray_t;
	typedef vector<CONVERTINFO>	ConvertArray_t;

	enum {
		NUM_CHANNELS = 16,		// 16 volume channels
		VOLUME_INIT = 100,		// 100% volume by default
		NUM_STREAM_BUFFERS = 2,
		OUT_BUFFER_SIZE = 1024,	// Max stream buffer size in bytes
		DEBUG_CALLBACK_TIMEOUT = 2000,
		VOLUME_MIN = 0,
		VOLUME_MAX = 127		// == 100%
	};

public:
	CMIDI();
	virtual ~CMIDI();
	HANDLE			m_hhLoopPlayEvent = NULL;
	BOOL	Create(LPVOID pSoundData, DWORD dwSize);

	BOOL	Play(BOOL bInfinite = FALSE);
	BOOL	Stop(BOOL bReOpen = TRUE);
	BOOL	IsPlaying() const { return m_bPlaying; }

	BOOL	Pause();
	BOOL	Continue();
	BOOL	IsPaused() const { return m_bPaused; }

	// Set playback position back to the start
	BOOL	Rewind();

	// Get the number of volume channels
	size_t	GetChannelCount() const;

	// Set the volume of a channel in percent. Channels are from 0 to (GetChannelCount()-1)
	void	SetChannelVolume(DWORD channel, DWORD percent);

	// Get the volume of a channel in percent
	DWORD	GetChannelVolume(DWORD channel) const;

	// Set the volume for all channels in percent
	void	SetVolume(DWORD percent);

	// Get the average volume for all channels
	DWORD	GetVolume() const;

	// Set the tempo of the playback. Default: 100%
	void	SetTempo(DWORD percent);

	// Get the current tempo in percent (usually 100)
	DWORD	GetTempo() const;

	// You can (un)set an infinite loop during playback.
	// Note that "Play()" resets this setting!
	void	SetInfinitePlay(BOOL bSet = TRUE);

protected:	// implementation
		// This function converts MIDI data from the track buffers.
	int		ConvertToBuffer(DWORD dwFlags, CONVERTINFO* lpciInfo);

	// Fills in the event struct with the next event from the track
	BOOL	GetTrackEvent(TRACK* ptsTrack, TEMPEVENT* pteTemp);

	// Retrieve the next byte from the track buffer, refilling the buffer from
	// disk if necessary.
	BOOL	GetTrackByte(TRACK* ptsTrack, LPBYTE lpbyByte) {
		if (DWORD(ptsTrack->pTrackCurrent - ptsTrack->pTrackStart) == ptsTrack->dwTrackLength)
			return FALSE;
		*lpbyByte = *ptsTrack->pTrackCurrent++;
		return TRUE;
	}

	// Attempts to parse a variable length DWORD from the given track.
	BOOL	GetTrackVDWord(TRACK* ptsTrack, LPDWORD lpdw);

	// Put the given event into the given stream buffer at the given location.
	int		AddEventToStreamBuffer(TEMPEVENT* pteTemp, CONVERTINFO* lpciInfo);

	// Opens a MIDI stream. Then it goes about converting the data into a midiStream buffer for playback.
	BOOL	StreamBufferSetup();

	void	FreeBuffers();


protected:	// error handling
		// The default implementation writes the error message in the
		// debuggers output window. Override if you want a different
		// behavior.
	virtual void	MidiError(MMRESULT Result);

	// Failure in converting track into stream.
	// The default implementation displays the offset and the total
	// number of bytes of the failed track and the error message in
	// the debuggers output window. 
	virtual void	TrackError(TRACK*, LPSTR ErrMsg);


protected:	// overridables
		// NOTE THAT, IF YOU OVERRIDE ONE OF THESE METHODS, YOU MUST CALL
		// THE BASE CLASS IMPLEMENTATION TOO!

		// called when a MIDI output device is opened
	virtual void	OnMidiOutOpen();

	// called when the MIDI output device is closed
	virtual void	OnMidiOutClose();

	// called when the specified system-exclusive or stream buffer
	// has been played and is being returned to the application
	virtual void	OnMidiOutDone(MIDIHDR&);

	// called when a MEVT_F_CALLBACK event is reached in the MIDI output stream
	virtual void	OnMidiOutPositionCB(MIDIHDR&, MIDIEVENT&);


private:	// callback procedure
		// This procedure calls the overridables above.
	static void	CALLBACK	MidiProc(HMIDIOUT, UINT, UINT_PTR, UINT_PTR, UINT_PTR);


protected:	// data members
	DWORD			m_dwSoundSize;
	LPVOID			m_pSoundData;
	DWORD			m_dwFormat;
	DWORD			m_dwTrackCount;
	DWORD			m_dwTimeDivision;
	BOOL			m_bPlaying;
	HMIDISTRM		m_hStream;
	DWORD			m_dwProgressBytes;
	BOOL			m_bLooped;
	DWORD			m_tkCurrentTime;
	DWORD			m_dwBufferTickLength;
	DWORD			m_dwCurrentTempo;
	DWORD			m_dwTempoMultiplier;
	BOOL			m_bInsertTempo;
	BOOL			m_bBuffersPrepared;
	int				m_nCurrentBuffer;
	UINT			m_uMIDIDeviceID;
	int				m_nEmptyBuffers;
	BOOL			m_bPaused;
	UINT			m_uCallbackStatus;
	HANDLE			m_hBufferReturnEvent;
	TrackArray_t	m_Tracks;
	VolumeArray_t	m_Volumes;
	ConvertArray_t	m_StreamBuffers;

	// data members especially for ConvertToBuffer()
	TRACK* m_ptsTrack;
	TRACK* m_ptsFound;
	DWORD			m_dwStatus;
	DWORD			m_tkNext;
	DWORD			m_dwMallocBlocks;
	TEMPEVENT		m_teTemp = { 0 };
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // MIDI_h



#pragma comment(lib, "Onecore.lib") 
#ifdef _DEBUG
#define DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define ASSERT(x)

#define MThd		0x6468544D		// Start of file
#define MTrk		0x6B72544D		// Start of track


#define BUFFER_TIME_LENGTH		60   // Amount to fill in milliseconds

#define TRACE0   
#define TRACE1   
// These structures are stored in MIDI files; they need to be byte aligned.
//
#pragma pack(1)

// Contents of MThd chunk.
struct MIDIFILEHDR
{
	WORD	wFormat;			// Format (hi-lo)
	WORD	wTrackCount;		// # tracks (hi-lo)
	WORD	wTimeDivision;		// Time division (hi-lo)
};

#pragma pack() // End of need for byte-aligned structures


// Macros for swapping hi/lo-endian data
//
#define WORDSWAP(w)		(((w) >> 8) | \
						(((w) << 8) & 0xFF00))

#define DWORDSWAP(dw)	(((dw) >> 24) | \
						(((dw) >> 8) & 0x0000FF00) | \
						(((dw) << 8) & 0x00FF0000) | \
						(((dw) << 24) & 0xFF000000))


static char gteBadRunStat[] = "Reference to missing running status.";
static char gteRunStatMsgTrunc[] = "Running status message truncated";
static char gteChanMsgTrunc[] = "Channel message truncated";
static char gteSysExLenTrunc[] = "SysEx event truncated (length)";
static char gteSysExTrunc[] = "SysEx event truncated";
static char gteMetaNoClass[] = "Meta event truncated (no class byte)";
static char gteMetaLenTrunc[] = "Meta event truncated (length)";
static char gteMetaTrunc[] = "Meta event truncated";
static char gteNoMem[] = "Out of memory during malloc call";


//////////////////////////////////////////////////////////////////////
// CMIDI -- Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMIDI::CMIDI()
	: m_dwSoundSize(0)
	, m_pSoundData(0)
	, m_dwFormat(0)
	, m_dwTrackCount(0)
	, m_dwTimeDivision(0)
	, m_bPlaying(FALSE)
	, m_hStream(0)
	, m_dwProgressBytes(0)
	, m_bLooped(FALSE)
	, m_tkCurrentTime(0)
	, m_dwBufferTickLength(0)
	, m_dwCurrentTempo(0)
	, m_dwTempoMultiplier(100)
	, m_bInsertTempo(FALSE)
	, m_bBuffersPrepared(FALSE)
	, m_nCurrentBuffer(0)
	, m_uMIDIDeviceID(MIDI_MAPPER)
	, m_nEmptyBuffers(0)
	, m_bPaused(FALSE)
	, m_uCallbackStatus(0)
	, m_hBufferReturnEvent(0)

	, m_ptsTrack(0)
	, m_ptsFound(0)
	, m_dwStatus(0)
	, m_tkNext(0)
	, m_dwMallocBlocks(0)
{
	m_hBufferReturnEvent = ::CreateEvent(0, FALSE, FALSE, TEXT("Wait For Buffer Return"));

}

CMIDI::~CMIDI()
{
	Stop(FALSE);

	if (m_hBufferReturnEvent)
		::CloseHandle(m_hBufferReturnEvent);
}


//DEL BOOL CMIDI::Create(UINT uResID)
//DEL {
//DEL 	return	Create(MAKEINTRESOURCE(uResID));
//DEL }


//DEL BOOL CMIDI::Create(LPCTSTR pszResID)
//DEL {
//DEL 	//////////////////////////////////////////////////////////////////
//DEL 	// load resource
//DEL 	HINSTANCE hApp = ::GetModuleHandle(0);
//DEL 	ASSERT(hApp);
//DEL 
//DEL 	HRSRC hResInfo = ::FindResource(hApp, pszResID, TEXT("MIDI"));
//DEL 	if(hResInfo == 0)
//DEL 		return FALSE;
//DEL 
//DEL 	HGLOBAL hRes = ::LoadResource(hApp, hResInfo);
//DEL 	if(hRes == 0)
//DEL 		return FALSE;
//DEL 
//DEL 	LPVOID pTheSound = ::LockResource(hRes);
//DEL 	if(pTheSound == 0)
//DEL 		return FALSE;
//DEL 
//DEL 	DWORD dwTheSound = ::SizeofResource(hApp, hResInfo);
//DEL 
//DEL 	return Create(pTheSound, dwTheSound);
//DEL }


BOOL CMIDI::Create(LPVOID pSoundData, DWORD dwSize)
{
	if (m_pSoundData) {
		// already created

		return FALSE;
	}




	LPBYTE p = LPBYTE(pSoundData);

	// check header of MIDI
	if (*(DWORD*)p != MThd) {
		ASSERT(FALSE);
		return FALSE;
	}
	p += sizeof(DWORD);

	// check header size
	DWORD dwHeaderSize = DWORDSWAP(*(DWORD*)p);
	if (dwHeaderSize != sizeof(MIDIFILEHDR)) {
		ASSERT(FALSE);
		return FALSE;
	}
	p += sizeof(DWORD);

	// get header
	MIDIFILEHDR hdr;
	::CopyMemory(&hdr, p, dwHeaderSize);
	m_dwFormat = DWORD(WORDSWAP(hdr.wFormat));
	m_dwTrackCount = DWORD(WORDSWAP(hdr.wTrackCount));
	m_dwTimeDivision = DWORD(WORDSWAP(hdr.wTimeDivision));
	p += dwHeaderSize;

	// create the array of tracks
	m_Tracks.resize(m_dwTrackCount);
	for (DWORD i = 0; i < m_dwTrackCount; ++i) {
		// check header of track
		if (*(DWORD*)p != MTrk) {
			ASSERT(FALSE);
			return FALSE;
		}
		p += sizeof(DWORD);

		m_Tracks[i].dwTrackLength = DWORDSWAP(*(DWORD*)p);
		p += sizeof(DWORD);

		m_Tracks[i].pTrackStart = m_Tracks[i].pTrackCurrent = p;
		p += m_Tracks[i].dwTrackLength;

		// Handle bozo MIDI files which contain empty track chunks
		if (!m_Tracks[i].dwTrackLength) {
			m_Tracks[i].fdwTrack |= ITS_F_ENDOFTRK;
			continue;
		}

		// We always preread the time from each track so the mixer code can
		// determine which track has the next event with a minimum of work
		if (!GetTrackVDWord(&m_Tracks[i], &m_Tracks[i].tkNextEventDue)) {
			TRACE0("Error in MIDI data\n");
			ASSERT(FALSE);
			return FALSE;
		}
	}


	m_pSoundData = pSoundData;
	m_dwSoundSize = dwSize;


	// allocate volume channels and initialise them
	m_Volumes.resize(NUM_CHANNELS, VOLUME_INIT);

	if (!StreamBufferSetup()) {
		ASSERT(FALSE);
		return FALSE;
	}

	return TRUE;
}


BOOL CMIDI::Play(BOOL bInfinite /* = FALSE */) {
	if (IsPaused()) {
		Continue();
		return TRUE;
	}

	// calling Play() while it is already playing will restart from scratch
	if (IsPlaying())
		Stop();

	// Clear the status of our callback so it will handle
	// MOM_DONE callbacks once more
	m_uCallbackStatus = 0;

	if (!m_bLooped)
		m_bInsertTempo = TRUE;

	MMRESULT mmResult;
	if ((mmResult = midiStreamRestart(m_hStream)) != MMSYSERR_NOERROR) {
		MidiError(mmResult);
		return FALSE;
	}

	m_bPlaying = TRUE;
	m_bLooped = bInfinite;

	return m_bPlaying;
}


BOOL CMIDI::Stop(BOOL bReOpen /*=TRUE*/) {
	MMRESULT mmrRetVal;

	if (IsPlaying() || (m_uCallbackStatus != STATUS_CALLBACKDEAD)) {
		m_bPlaying = m_bPaused = FALSE;
		if (m_uCallbackStatus != STATUS_CALLBACKDEAD && m_uCallbackStatus != STATUS_WAITINGFOREND)
			m_uCallbackStatus = STATUS_KILLCALLBACK;

		if ((mmrRetVal = midiStreamStop(m_hStream)) != MMSYSERR_NOERROR) {
			MidiError(mmrRetVal);
			return FALSE;
		}
		if ((mmrRetVal = midiOutReset((HMIDIOUT)m_hStream)) != MMSYSERR_NOERROR) {
			MidiError(mmrRetVal);
			return FALSE;
		}
		// Wait for the callback thread to release this thread, which it will do by
		// calling SetEvent() once all buffers are returned to it
		if (WaitForSingleObject(m_hBufferReturnEvent, DEBUG_CALLBACK_TIMEOUT) == WAIT_TIMEOUT) {
			// Note, this is a risky move because the callback may be genuinely busy, but
			// when we're debugging, it's safer and faster than freezing the application,
			// which leaves the MIDI device locked up and forces a system reset...
			TRACE0("Timed out waiting for MIDI callback\n");
			m_uCallbackStatus = STATUS_CALLBACKDEAD;
		}
	}

	//m_pSoundData = NULL;//重新创建
	if (m_uCallbackStatus == STATUS_CALLBACKDEAD) {
		m_uCallbackStatus = 0;
		FreeBuffers();
		if (m_hStream) {
			if ((mmrRetVal = midiStreamClose(m_hStream)) != MMSYSERR_NOERROR) {
				MidiError(mmrRetVal);
			}
			m_hStream = 0;
		}

		if (bReOpen) {
			if (!StreamBufferSetup()) {
				// Error setting up for MIDI file
				// Notification is already taken care of...
				return FALSE;
			}
			if (!m_bLooped) {
				Rewind();
				m_dwProgressBytes = 0;
				m_dwStatus = 0;
			}
		}
	}
	return TRUE;
}


BOOL CMIDI::Pause() {
	if (!m_bPaused && m_bPlaying && m_pSoundData && m_hStream) {
		midiStreamPause(m_hStream);
		m_bPaused = TRUE;
	}
	return FALSE;
}


BOOL CMIDI::Continue() {
	if (m_bPaused && m_bPlaying && m_pSoundData && m_hStream) {
		midiStreamRestart(m_hStream);
		m_bPaused = FALSE;
	}
	return FALSE;
}


BOOL CMIDI::Rewind() {
	if (!m_pSoundData)
		return FALSE;

	for (DWORD i = 0; i < m_dwTrackCount; ++i) {
		m_Tracks[i].pTrackCurrent = m_Tracks[i].pTrackStart;
		m_Tracks[i].byRunningStatus = 0;
		m_Tracks[i].tkNextEventDue = 0;
		m_Tracks[i].fdwTrack = 0;

		// Handle bozo MIDI files which contain empty track chunks
		if (!m_Tracks[i].dwTrackLength) {
			m_Tracks[i].fdwTrack |= ITS_F_ENDOFTRK;
			continue;
		}

		// We always preread the time from each track so the mixer code can
		// determine which track has the next event with a minimum of work
		if (!GetTrackVDWord(&m_Tracks[i], &m_Tracks[i].tkNextEventDue)) {
			TRACE0("Error in MIDI data\n");
			ASSERT(FALSE);
			return FALSE;
		}
	}

	return TRUE;
}


size_t CMIDI::GetChannelCount() const {
	return m_Volumes.size();
}


void CMIDI::SetVolume(DWORD dwPercent) {
	const DWORD dwSize = (DWORD)m_Volumes.size();
	for (DWORD i = 0; i < dwSize; ++i)
		SetChannelVolume(i, dwPercent);
}


DWORD CMIDI::GetVolume() const {
	DWORD dwVolume = 0;
	const DWORD dwSize = (DWORD)m_Volumes.size();
	for (DWORD i = 0; i < dwSize; ++i)
		dwVolume += GetChannelVolume(i);

	return dwVolume / (DWORD)GetChannelCount();
}


void CMIDI::SetChannelVolume(DWORD dwChannel, DWORD dwPercent) {
	ASSERT(dwChannel < m_Volumes.size());

	if (!m_bPlaying)
		return;

	m_Volumes[dwChannel] = (dwPercent > 100) ? 100 : dwPercent;
	DWORD dwEvent = MIDI_CTRLCHANGE | dwChannel | ((DWORD)MIDICTRL_VOLUME << 8) | ((DWORD)(m_Volumes[dwChannel] * VOLUME_MAX / 100) << 16);
	MMRESULT mmrRetVal;
	if ((mmrRetVal = midiOutShortMsg((HMIDIOUT)m_hStream, dwEvent)) != MMSYSERR_NOERROR) {
		MidiError(mmrRetVal);
		return;
	}
}


DWORD CMIDI::GetChannelVolume(DWORD dwChannel) const {
	ASSERT(dwChannel < GetChannelCount());
	return m_Volumes[dwChannel];
}


void CMIDI::SetTempo(DWORD dwPercent) {
	m_dwTempoMultiplier = dwPercent ? dwPercent : 1;
	m_bInsertTempo = TRUE;
}


DWORD CMIDI::GetTempo() const {
	return m_dwTempoMultiplier;
}


void CMIDI::SetInfinitePlay(BOOL bSet) {
	m_bLooped = bSet;
}

//////////////////////////////////////////////////////////////////////
// CMIDI -- implementation
//////////////////////////////////////////////////////////////////////

// This function converts MIDI data from the track buffers setup by a
// previous call to ConverterInit().  It will convert data until an error is
// encountered or the output buffer has been filled with as much event data
// as possible, not to exceed dwMaxLength. This function can take a couple
// bit flags, passed through dwFlags. Information about the success/failure
// of this operation and the number of output bytes actually converted will
// be returned in the CONVERTINFO structure pointed at by lpciInfo.
int CMIDI::ConvertToBuffer(DWORD dwFlags, CONVERTINFO* lpciInfo) {
	int	    nChkErr;

	lpciInfo->dwBytesRecorded = 0;

	if (dwFlags & CONVERTF_RESET) {
		m_dwProgressBytes = 0;
		m_dwStatus = 0;
		memset(&m_teTemp, 0, sizeof(TEMPEVENT));
		m_ptsTrack = m_ptsFound = 0;
	}

	// If we were already done, then return with a warning...
	if (m_dwStatus & CONVERTF_STATUS_DONE) {
		if (m_bLooped) {
			Rewind();
			m_dwProgressBytes = 0;
			m_dwStatus = 0;
		}
		else
			return CONVERTERR_DONE;
	}
	else if (m_dwStatus & CONVERTF_STATUS_STUCK) {
		// The caller is asking us to continue, but we're already hosed because we
		// previously identified something as corrupt, so complain louder this time.
		return(CONVERTERR_STUCK);
	}
	else if (m_dwStatus & CONVERTF_STATUS_GOTEVENT) {
		// Turn off this bit flag
		m_dwStatus ^= CONVERTF_STATUS_GOTEVENT;

		// The following code for this case is duplicated from below, and is
		// designed to handle a "straggler" event, should we have one left over
		// from previous processing the last time this function was called.

		// Don't add end of track event 'til we're done
		if (m_teTemp.byShortData[0] == MIDI_META && m_teTemp.byShortData[1] == MIDI_META_EOT) {
			if (m_dwMallocBlocks) {
				delete[] m_teTemp.pLongData;
				--m_dwMallocBlocks;
			}
		}
		else if ((nChkErr = AddEventToStreamBuffer(&m_teTemp, lpciInfo)) != CONVERTERR_NOERROR) {
			if (nChkErr == CONVERTERR_BUFFERFULL) {
				// Do some processing and tell caller that this buffer's full
				m_dwStatus |= CONVERTF_STATUS_GOTEVENT;
				return CONVERTERR_NOERROR;
			}
			else if (nChkErr == CONVERTERR_METASKIP) {
				// We skip by all meta events that aren't tempo changes...
			}
			else {
				TRACE0("Unable to add event to stream buffer.\n");
				if (m_dwMallocBlocks) {
					delete[] m_teTemp.pLongData;
					m_dwMallocBlocks--;
				}
				return(TRUE);
			}
		}
	}

	for (;;) {
		m_ptsFound = 0;
		m_tkNext = 0xFFFFFFFFL;
		// Find nearest event due
		for (DWORD idx = 0; idx < m_Tracks.size(); ++idx) {
			m_ptsTrack = &m_Tracks[idx];
			if (!(m_ptsTrack->fdwTrack & ITS_F_ENDOFTRK) && (m_ptsTrack->tkNextEventDue < m_tkNext)) {
				m_tkNext = m_ptsTrack->tkNextEventDue;
				m_ptsFound = m_ptsTrack;
			}
		}

		// None found?  We must be done, so return to the caller with a smile.
		if (!m_ptsFound) {
			m_dwStatus |= CONVERTF_STATUS_DONE;
			// Need to set return buffer members properly
			return CONVERTERR_NOERROR;
		}

		// Ok, get the event header from that track
		if (!GetTrackEvent(m_ptsFound, &m_teTemp)) {
			// Warn future calls that this converter is stuck at a corrupt spot
			// and can't continue
			m_dwStatus |= CONVERTF_STATUS_STUCK;
			return CONVERTERR_CORRUPT;
		}

		// Don't add end of track event 'til we're done
		if (m_teTemp.byShortData[0] == MIDI_META && m_teTemp.byShortData[1] == MIDI_META_EOT) {
			if (m_dwMallocBlocks) {
				delete[] m_teTemp.pLongData;
				--m_dwMallocBlocks;
			}
			continue;
		}

		if ((nChkErr = AddEventToStreamBuffer(&m_teTemp, lpciInfo)) != CONVERTERR_NOERROR) {
			if (nChkErr == CONVERTERR_BUFFERFULL) {
				// Do some processing and tell somebody this buffer is full...
				m_dwStatus |= CONVERTF_STATUS_GOTEVENT;
				return CONVERTERR_NOERROR;
			}
			else if (nChkErr == CONVERTERR_METASKIP) {
				// We skip by all meta events that aren't tempo changes...
			}
			else {
				TRACE0("Unable to add event to stream buffer.\n");
				if (m_dwMallocBlocks) {
					delete[] m_teTemp.pLongData;
					m_dwMallocBlocks--;
				}
				return TRUE;
			}
		}
	}

	return CONVERTERR_NOERROR;
}

// GetTrackEvent
//
// Fills in the event struct with the next event from the track
//
// pteTemp->tkEvent will contain the absolute tick time of the event
// pteTemp->byShortData[0] will contain
//  MIDI_META if the event is a meta event;
//   in this case pteTemp->byShortData[1] will contain the meta class
//  MIDI_SYSEX or MIDI_SYSEXEND if the event is a SysEx event
//  Otherwise, the event is a channel message and pteTemp->byShortData[1]
//   and pteTemp->byShortData[2] will contain the rest of the event.
//
// pteTemp->dwEventLength will contain
//  The total length of the channel message in pteTemp->byShortData if
//   the event is a channel message
//  The total length of the paramter data pointed to by
//   pteTemp->pLongData otherwise
//
// pteTemp->pLongData will point at any additional paramters if the 
//  event is a SysEx or meta event with non-zero length; else
//  it will contain NULL
//
// Returns TRUE on success or FALSE on any kind of parse error
// Prints its own error message ONLY in the debug version
//
// Maintains the state of the input track (i.e. 
// ptsTrack->pTrackPointers, and ptsTrack->byRunningStatus).
//
BOOL CMIDI::GetTrackEvent(TRACK* ptsTrack, TEMPEVENT* pteTemp) {
	DWORD   idx;
	UINT    dwEventLength;

	// Clear out the temporary event structure to get rid of old data...
	memset(pteTemp, 0, sizeof(TEMPEVENT));

	// Already at end of track? There's nothing to read.
	if (ptsTrack->fdwTrack & ITS_F_ENDOFTRK)
		return FALSE;

	// Get the first byte, which determines the type of event.
	BYTE byByte;
	if (!GetTrackByte(ptsTrack, &byByte))
		return FALSE;

	// If the high bit is not set, then this is a channel message
	// which uses the status byte from the last channel message
	// we saw. NOTE: We do not clear running status across SysEx or
	// meta events even though the spec says to because there are
	// actually files out there which contain that sequence of data.
	if (!(byByte & 0x80)) {
		// No previous status byte? We're hosed.
		if (!ptsTrack->byRunningStatus) {
			TrackError(ptsTrack, gteBadRunStat);
			return FALSE;
		}

		pteTemp->byShortData[0] = ptsTrack->byRunningStatus;
		pteTemp->byShortData[1] = byByte;

		byByte = pteTemp->byShortData[0] & 0xF0;
		pteTemp->dwEventLength = 2;

		// Only program change and channel pressure events are 2 bytes long;
		// the rest are 3 and need another byte
		if ((byByte != MIDI_PRGMCHANGE) && (byByte != MIDI_CHANPRESS)) {
			if (!GetTrackByte(ptsTrack, &pteTemp->byShortData[2]))
				return FALSE;
			++pteTemp->dwEventLength;
		}
	}
	else if ((byByte & 0xF0) != MIDI_SYSEX) {
		// Not running status, not in SysEx range - must be
		// normal channel message (0x80-0xEF)
		pteTemp->byShortData[0] = byByte;
		ptsTrack->byRunningStatus = byByte;

		// Strip off channel and just keep message type
		byByte &= 0xF0;

		dwEventLength = (byByte == MIDI_PRGMCHANGE || byByte == MIDI_CHANPRESS) ? 1 : 2;
		pteTemp->dwEventLength = dwEventLength + 1;

		if (!GetTrackByte(ptsTrack, &pteTemp->byShortData[1]))
			return FALSE;
		if (dwEventLength == 2)
			if (!GetTrackByte(ptsTrack, &pteTemp->byShortData[2]))
				return FALSE;
	}
	else if ((byByte == MIDI_SYSEX) || (byByte == MIDI_SYSEXEND)) {
		// One of the SysEx types. (They are the same as far as we're concerned;
		// there is only a semantic difference in how the data would actually
		// get sent when the file is played. We must take care to put the proper
		// event type back on the output track, however.)
		//
		// Parse the general format of:
		//  BYTE 	bEvent (MIDI_SYSEX or MIDI_SYSEXEND)
		//  VDWORD 	cbParms
		//  BYTE   	abParms[cbParms]
		pteTemp->byShortData[0] = byByte;
		if (!GetTrackVDWord(ptsTrack, &pteTemp->dwEventLength)) {
			TrackError(ptsTrack, gteSysExLenTrunc);
			return FALSE;
		}

		// Malloc a temporary memory block to hold the parameter data
		pteTemp->pLongData = new BYTE[pteTemp->dwEventLength];
		if (pteTemp->pLongData == 0) {
			TrackError(ptsTrack, gteNoMem);
			return FALSE;
		}
		// Increment our counter, which tells the program to look around for
		// a malloc block to free, should it need to exit or reset before the
		// block would normally be freed
		++m_dwMallocBlocks;

		// Copy from the input buffer to the parameter data buffer
		for (idx = 0; idx < pteTemp->dwEventLength; idx++)
			if (!GetTrackByte(ptsTrack, pteTemp->pLongData + idx)) {
				TrackError(ptsTrack, gteSysExTrunc);
				return FALSE;
			}
	}
	else if (byByte == MIDI_META) {
		// It's a meta event. Parse the general form:
		//  BYTE	bEvent	(MIDI_META)
		//  BYTE	bClass
		//  VDWORD	cbParms
		//  BYTE	abParms[cbParms]
		pteTemp->byShortData[0] = byByte;

		if (!GetTrackByte(ptsTrack, &pteTemp->byShortData[1]))
			return FALSE;

		if (!GetTrackVDWord(ptsTrack, &pteTemp->dwEventLength)) {
			TrackError(ptsTrack, gteMetaLenTrunc);
			return FALSE;
		}

		// NOTE: It's perfectly valid to have a meta with no data
		// In this case, dwEventLength == 0 and pLongData == NULL
		if (pteTemp->dwEventLength) {
			// Malloc a temporary memory block to hold the parameter data
			pteTemp->pLongData = new BYTE[pteTemp->dwEventLength];
			if (pteTemp->pLongData == 0) {
				TrackError(ptsTrack, gteNoMem);
				return FALSE;
			}
			// Increment our counter, which tells the program to look around for
			// a malloc block to free, should it need to exit or reset before the
			// block would normally be freed
			++m_dwMallocBlocks;

			// Copy from the input buffer to the parameter data buffer
			for (idx = 0; idx < pteTemp->dwEventLength; idx++)
				if (!GetTrackByte(ptsTrack, pteTemp->pLongData + idx)) {
					TrackError(ptsTrack, gteMetaTrunc);
					return FALSE;
				}
		}

		if (pteTemp->byShortData[1] == MIDI_META_EOT)
			ptsTrack->fdwTrack |= ITS_F_ENDOFTRK;
	}
	else {
		// Messages in this range are system messages and aren't supposed to
		// be in a normal MIDI file. If they are, we've either misparsed or the
		// authoring software is stupid.
		return FALSE;
	}

	// Event time was already stored as the current track time
	pteTemp->tkEvent = ptsTrack->tkNextEventDue;

	// Now update to the next event time. The code above MUST properly
	// maintain the end of track flag in case the end of track meta is
	// missing.  NOTE: This code is a continuation of the track event
	// time pre-read which is done at the end of track initialization.
	if (!(ptsTrack->fdwTrack & ITS_F_ENDOFTRK)) {
		DWORD	tkDelta;

		if (!GetTrackVDWord(ptsTrack, &tkDelta))
			return FALSE;

		ptsTrack->tkNextEventDue += tkDelta;
	}

	return TRUE;
}


// GetTrackVDWord
//
// Attempts to parse a variable length DWORD from the given track. A VDWord
// in a MIDI file
//  (a) is in lo-hi format 
//  (b) has the high bit set on every byte except the last
//
// Returns the DWORD in *lpdw and TRUE on success; else
// FALSE if we hit end of track first.
BOOL CMIDI::GetTrackVDWord(TRACK* ptsTrack, LPDWORD lpdw) {
	ASSERT(ptsTrack != 0);
	ASSERT(lpdw != 0);

	if (ptsTrack->fdwTrack & ITS_F_ENDOFTRK)
		return FALSE;

	BYTE	byByte;
	DWORD	dw = 0;

	do {
		if (!GetTrackByte(ptsTrack, &byByte))
			return FALSE;

		dw = (dw << 7) | (byByte & 0x7F);
	} while (byByte & 0x80);

	*lpdw = dw;

	return TRUE;
}


// AddEventToStreamBuffer
//
// Put the given event into the given stream buffer at the given location
// pteTemp must point to an event filled out in accordance with the
// description given in GetTrackEvent
//
// Handles its own error notification by displaying to the appropriate
// output device (either our debugging window, or the screen).
int CMIDI::AddEventToStreamBuffer(TEMPEVENT* pteTemp, CONVERTINFO* lpciInfo) {
	MIDIEVENT* pmeEvent = (MIDIEVENT*)(lpciInfo->mhBuffer.lpData
		+ lpciInfo->dwStartOffset
		+ lpciInfo->dwBytesRecorded);

	// When we see a new, empty buffer, set the start time on it...
	if (!lpciInfo->dwBytesRecorded)
		lpciInfo->tkStart = m_tkCurrentTime;

	// Use the above set start time to figure out how much longer we should fill
	// this buffer before officially declaring it as "full"
	if (m_tkCurrentTime - lpciInfo->tkStart > m_dwBufferTickLength)
		if (lpciInfo->bTimesUp) {
			lpciInfo->bTimesUp = FALSE;
			return CONVERTERR_BUFFERFULL;
		}
		else
			lpciInfo->bTimesUp = TRUE;

	DWORD tkNow = m_tkCurrentTime;

	// Delta time is absolute event time minus absolute time
	// already gone by on this track
	DWORD tkDelta = pteTemp->tkEvent - m_tkCurrentTime;

	// Event time is now current time on this track
	m_tkCurrentTime = pteTemp->tkEvent;

	if (m_bInsertTempo) {
		m_bInsertTempo = FALSE;

		if (lpciInfo->dwMaxLength - lpciInfo->dwBytesRecorded < 3 * sizeof(DWORD)) {
			// Cleanup from our write operation
			return CONVERTERR_BUFFERFULL;
		}
		if (m_dwCurrentTempo) {
			pmeEvent->dwDeltaTime = 0;
			pmeEvent->dwStreamID = 0;
			pmeEvent->dwEvent = (m_dwCurrentTempo * 100) / m_dwTempoMultiplier;
			pmeEvent->dwEvent |= (((DWORD)MEVT_TEMPO) << 24) | MEVT_F_SHORT;

			lpciInfo->dwBytesRecorded += 3 * sizeof(DWORD);
			pmeEvent += 3 * sizeof(DWORD);
		}
	}

	if (pteTemp->byShortData[0] < MIDI_SYSEX) {
		// Channel message. We know how long it is, just copy it.
		// Need 3 DWORD's: delta-t, stream-ID, event
		if (lpciInfo->dwMaxLength - lpciInfo->dwBytesRecorded < 3 * sizeof(DWORD)) {
			// Cleanup from our write operation
			return CONVERTERR_BUFFERFULL;
		}

		pmeEvent->dwDeltaTime = tkDelta;
		pmeEvent->dwStreamID = 0;
		pmeEvent->dwEvent = (pteTemp->byShortData[0])
			| (((DWORD)pteTemp->byShortData[1]) << 8)
			| (((DWORD)pteTemp->byShortData[2]) << 16)
			| MEVT_F_SHORT;

		if (((pteTemp->byShortData[0] & 0xF0) == MIDI_CTRLCHANGE) && (pteTemp->byShortData[1] == MIDICTRL_VOLUME)) {
			// If this is a volume change, generate a callback so we can grab
			// the new volume for our cache
			pmeEvent->dwEvent |= MEVT_F_CALLBACK;
		}
		lpciInfo->dwBytesRecorded += 3 * sizeof(DWORD);
	}
	else if ((pteTemp->byShortData[0] == MIDI_SYSEX) || (pteTemp->byShortData[0] == MIDI_SYSEXEND)) {
		TRACE0("AddEventToStreamBuffer: Ignoring SysEx event.\n");
		if (m_dwMallocBlocks) {
			delete[] pteTemp->pLongData;
			--m_dwMallocBlocks;
		}
	}
	else {
		// Better be a meta event.
		//  BYTE	byEvent
		//  BYTE	byEventType
		//  VDWORD	dwEventLength
		//  BYTE	pLongEventData[dwEventLength]
		ASSERT(pteTemp->byShortData[0] == MIDI_META);

		// The only meta-event we care about is change tempo
		if (pteTemp->byShortData[1] != MIDI_META_TEMPO) {
			if (m_dwMallocBlocks) {
				delete[] pteTemp->pLongData;
				--m_dwMallocBlocks;
			}
			return CONVERTERR_METASKIP;
		}

		// We should have three bytes of parameter data...
		ASSERT(pteTemp->dwEventLength == 3);

		// Need 3 DWORD's: delta-t, stream-ID, event data
		if (lpciInfo->dwMaxLength - lpciInfo->dwBytesRecorded < 3 * sizeof(DWORD)) {
			// Cleanup the temporary event if necessary and return
			if (m_dwMallocBlocks) {
				delete[] pteTemp->pLongData;
				--m_dwMallocBlocks;
			}
			return CONVERTERR_BUFFERFULL;
		}

		pmeEvent->dwDeltaTime = tkDelta;
		pmeEvent->dwStreamID = 0;
		// Note: this is backwards from above because we're converting a single
		//		 data value from hi-lo to lo-hi format...
		pmeEvent->dwEvent = (pteTemp->pLongData[2])
			| (((DWORD)pteTemp->pLongData[1]) << 8)
			| (((DWORD)pteTemp->pLongData[0]) << 16);

		// This next step has absolutely nothing to do with the conversion of a
		// MIDI file to a stream, it's simply put here to add the functionality
		// of the tempo slider. If you don't need this, be sure to remove the
		// next two lines.
		m_dwCurrentTempo = pmeEvent->dwEvent;
		pmeEvent->dwEvent = (pmeEvent->dwEvent * 100) / m_dwTempoMultiplier;

		pmeEvent->dwEvent |= (((DWORD)MEVT_TEMPO) << 24) | MEVT_F_SHORT;

		m_dwBufferTickLength = (m_dwTimeDivision * 1000 * BUFFER_TIME_LENGTH) / m_dwCurrentTempo;
		TRACE1("m_dwBufferTickLength = %lu\n", m_dwBufferTickLength);

		if (m_dwMallocBlocks) {
			delete[] pteTemp->pLongData;
			--m_dwMallocBlocks;
		}
		lpciInfo->dwBytesRecorded += 3 * sizeof(DWORD);
	}

	return CONVERTERR_NOERROR;
}


// StreamBufferSetup()
//
// Opens a MIDI stream. Then it goes about converting the data into a midiStream buffer for playback.
BOOL CMIDI::StreamBufferSetup() {
	int		nChkErr;
	BOOL	bFoundEnd = FALSE;

	MMRESULT		mmrRetVal;

	if (!m_hStream)
		if ((mmrRetVal = midiStreamOpen(&m_hStream,
			&m_uMIDIDeviceID,
			DWORD(1), (DWORD_PTR)MidiProc,
			DWORD_PTR(this),
			CALLBACK_FUNCTION)) != MMSYSERR_NOERROR) {
			MidiError(mmrRetVal);
			return FALSE;
		}

	// allocate stream buffers and initialise them
	m_StreamBuffers.resize(NUM_STREAM_BUFFERS);

	MIDIPROPTIMEDIV mptd;
	mptd.cbStruct = sizeof(mptd);
	mptd.dwTimeDiv = m_dwTimeDivision;
	if ((mmrRetVal = midiStreamProperty(m_hStream, (LPBYTE)&mptd,
		MIDIPROP_SET | MIDIPROP_TIMEDIV)) != MMSYSERR_NOERROR) {
		MidiError(mmrRetVal);
		return FALSE;
	}

	m_nEmptyBuffers = 0;
	DWORD dwConvertFlag = CONVERTF_RESET;

	for (m_nCurrentBuffer = 0; m_nCurrentBuffer < NUM_STREAM_BUFFERS; m_nCurrentBuffer++) {
		m_StreamBuffers[m_nCurrentBuffer].mhBuffer.dwBufferLength = OUT_BUFFER_SIZE;
		m_StreamBuffers[m_nCurrentBuffer].mhBuffer.lpData = new char[OUT_BUFFER_SIZE];
		if (m_StreamBuffers[m_nCurrentBuffer].mhBuffer.lpData == 0)
			return FALSE;

		// Tell the converter to convert up to one entire buffer's length of output
		// data. Also, set a flag so it knows to reset any saved state variables it
		// may keep from call to call.
		m_StreamBuffers[m_nCurrentBuffer].dwStartOffset = 0;
		m_StreamBuffers[m_nCurrentBuffer].dwMaxLength = OUT_BUFFER_SIZE;
		m_StreamBuffers[m_nCurrentBuffer].tkStart = 0;
		m_StreamBuffers[m_nCurrentBuffer].bTimesUp = FALSE;

		if ((nChkErr = ConvertToBuffer(dwConvertFlag, &m_StreamBuffers[m_nCurrentBuffer])) != CONVERTERR_NOERROR) {
			if (nChkErr == CONVERTERR_DONE) {
				bFoundEnd = TRUE;
			}
			else {
				TRACE0("Initial conversion pass failed\n");
				return FALSE;
			}
		}
		m_StreamBuffers[m_nCurrentBuffer].mhBuffer.dwBytesRecorded = m_StreamBuffers[m_nCurrentBuffer].dwBytesRecorded;

		if (!m_bBuffersPrepared)
			if ((mmrRetVal = midiOutPrepareHeader((HMIDIOUT)m_hStream,
				&m_StreamBuffers[m_nCurrentBuffer].mhBuffer,
				sizeof(MIDIHDR))) != MMSYSERR_NOERROR) {
				MidiError(mmrRetVal);
				return FALSE;
			}

		if ((mmrRetVal = midiStreamOut(m_hStream,
			&m_StreamBuffers[m_nCurrentBuffer].mhBuffer,
			sizeof(MIDIHDR))) != MMSYSERR_NOERROR) {
			MidiError(mmrRetVal);
			break;
		}
		dwConvertFlag = 0;

		if (bFoundEnd)
			break;
	}

	m_bBuffersPrepared = TRUE;
	m_nCurrentBuffer = 0;
	return TRUE;
}

// This function unprepares and frees all our buffers -- something we must
// do to work around a bug in MMYSYSTEM that prevents a device from playing
// back properly unless it is closed and reopened after each stop.
void CMIDI::FreeBuffers() {
	DWORD	idx;
	MMRESULT	mmrRetVal;

	if (m_bBuffersPrepared) {
		for (idx = 0; idx < NUM_STREAM_BUFFERS; idx++)
			if ((mmrRetVal = midiOutUnprepareHeader((HMIDIOUT)m_hStream,
				&m_StreamBuffers[idx].mhBuffer,
				sizeof(MIDIHDR))) != MMSYSERR_NOERROR) {
				MidiError(mmrRetVal);
			}
		m_bBuffersPrepared = FALSE;
	}
	// Free our stream buffers...
	for (idx = 0; idx < NUM_STREAM_BUFFERS; idx++)
		if (m_StreamBuffers[idx].mhBuffer.lpData) {
			delete[] m_StreamBuffers[idx].mhBuffer.lpData;
			m_StreamBuffers[idx].mhBuffer.lpData = 0;
		}
}

//////////////////////////////////////////////////////////////////////
// CMIDI -- error handling
//////////////////////////////////////////////////////////////////////

void CMIDI::MidiError(MMRESULT mmResult) {
#ifdef _DEBUG
	char chText[512];
	midiOutGetErrorText(mmResult, chText, sizeof(chText));
	TRACE1("Midi error: %hs\n", chText);
#endif
}


void CMIDI::TrackError(TRACK* ptsTrack, LPSTR lpszErr) {
	TRACE1("Track buffer offset %lu\n", (DWORD)(ptsTrack->pTrackCurrent - ptsTrack->pTrackStart));
	TRACE1("Track total length %lu\n", ptsTrack->dwTrackLength);
	TRACE1("%hs\n", lpszErr);
}

//////////////////////////////////////////////////////////////////////
// CMIDI -- overridables
//////////////////////////////////////////////////////////////////////

void CMIDI::OnMidiOutOpen() {
}


void CMIDI::OnMidiOutDone(MIDIHDR& rHdr) {
	if (m_uCallbackStatus == STATUS_CALLBACKDEAD)
		return;

	++m_nEmptyBuffers;

	if (m_uCallbackStatus == STATUS_WAITINGFOREND) {
		if (m_nEmptyBuffers < NUM_STREAM_BUFFERS)
			return;
		else {
			m_uCallbackStatus = STATUS_CALLBACKDEAD;
			Stop();
			SetEvent(m_hBufferReturnEvent);
			SetEvent(m_hhLoopPlayEvent);//播放完一首,换曲
			return;
		}
	}

	// This flag is set whenever the callback is waiting for all buffers to
	// come back.
	if (m_uCallbackStatus == STATUS_KILLCALLBACK) {
		// Count NUM_STREAM_BUFFERS-1 being returned for the last time
		if (m_nEmptyBuffers < NUM_STREAM_BUFFERS)
			return;
		else {
			// Change the status to callback dead
			m_uCallbackStatus = STATUS_CALLBACKDEAD;
			SetEvent(m_hBufferReturnEvent);
			return;
		}
	}

	m_dwProgressBytes += m_StreamBuffers[m_nCurrentBuffer].mhBuffer.dwBytesRecorded;

	///////////////////////////////////////////////////////////////////////////////
	// Fill an available buffer with audio data again...

	if (m_bPlaying && m_nEmptyBuffers) {
		m_StreamBuffers[m_nCurrentBuffer].dwStartOffset = 0;
		m_StreamBuffers[m_nCurrentBuffer].dwMaxLength = OUT_BUFFER_SIZE;
		m_StreamBuffers[m_nCurrentBuffer].tkStart = 0;
		m_StreamBuffers[m_nCurrentBuffer].dwBytesRecorded = 0;
		m_StreamBuffers[m_nCurrentBuffer].bTimesUp = FALSE;

		int nChkErr;

		if ((nChkErr = ConvertToBuffer(0, &m_StreamBuffers[m_nCurrentBuffer])) != CONVERTERR_NOERROR) {
			if (nChkErr == CONVERTERR_DONE) {
				m_uCallbackStatus = STATUS_WAITINGFOREND;


				return;
			}
			else {
				TRACE0("MidiProc() conversion pass failed!\n");
				return;
			}
		}

		m_StreamBuffers[m_nCurrentBuffer].mhBuffer.dwBytesRecorded = m_StreamBuffers[m_nCurrentBuffer].dwBytesRecorded;

		MMRESULT mmrRetVal;
		if ((mmrRetVal = midiStreamOut(m_hStream, &m_StreamBuffers[m_nCurrentBuffer].mhBuffer, sizeof(MIDIHDR))) != MMSYSERR_NOERROR) {
			MidiError(mmrRetVal);
			return;
		}
		m_nCurrentBuffer = (m_nCurrentBuffer + 1) % NUM_STREAM_BUFFERS;
		m_nEmptyBuffers--;
	}
}


void CMIDI::OnMidiOutPositionCB(MIDIHDR& rHdr, MIDIEVENT& rEvent) {
	if (MIDIEVENT_TYPE(rEvent.dwEvent) == MIDI_CTRLCHANGE)
	{
		if (MIDIEVENT_DATA1(rEvent.dwEvent) == MIDICTRL_VOLUME) {
			// Mask off the channel number and cache the volume data byte
			m_Volumes[MIDIEVENT_CHANNEL(rEvent.dwEvent)] = DWORD(MIDIEVENT_VOLUME(rEvent.dwEvent) * 100 / VOLUME_MAX);
			/*
			if( m_pWndParent && ::IsWindow(m_pWndParent->GetSafeHwnd()) )
				// Do not use SendMessage(), because a change of the midi stream has no effect
				// during callback handling, so if the owner wants to adjust the volume, as a
				// result of the windows message, (s)he will not hear that change.
				m_pWndParent->PostMessage(
					WM_MIDI_VOLUMECHANGED,
					WPARAM(this),
					LPARAM(
						MAKELONG(
							WORD(MIDIEVENT_CHANNEL(rEvent.dwEvent)),
							WORD(MIDIEVENT_VOLUME(rEvent.dwEvent)*100/VOLUME_MAX)
						)
					)
				);
				*/
		}
	}
}


void CMIDI::OnMidiOutClose() {
}

//////////////////////////////////////////////////////////////////////
// CMIDI -- static members
//////////////////////////////////////////////////////////////////////

void CMIDI::MidiProc(HMIDIOUT hMidi, UINT uMsg, UINT_PTR dwInstanceData, UINT_PTR dwParam1, UINT_PTR dwParam2) {
	CMIDI* pMidi = (CMIDI*)dwInstanceData;
	ASSERT(pMidi != 0);
	MIDIHDR* pHdr = (MIDIHDR*)dwParam1;

	switch (uMsg) {
	case MOM_OPEN:
		pMidi->OnMidiOutOpen();
		break;

	case MOM_CLOSE:
		pMidi->OnMidiOutClose();
		break;

	case MOM_DONE:
		ASSERT(pHdr != 0);
		pMidi->OnMidiOutDone(*pHdr);
		break;

	case MOM_POSITIONCB:
		ASSERT(pHdr != 0);
		pMidi->OnMidiOutPositionCB(*pHdr, *((MIDIEVENT*)(pHdr->lpData + pHdr->dwOffset)));
		break;

	default:
		break;
	}
}

using namespace std;
namespace KrnlnMidInside {
	struct MIDIFILEDATAINFO
	{
		unsigned char* pData;
		size_t	dwSize;
	};
	struct MIDMUSIC
	{
		union {
			const char* name;
			const wchar_t* wname;
			MIDIFILEDATAINFO data;
		};
		int datatype;
	};
	typedef MIDMUSIC* PMIDMUSIC;
	MIDIFILEDATAINFO* pMidiFileData = NULL;
	static int nLoopNum;
	static int nPlayWaitTime;
	static size_t nMidiArrySize = 0;
	static HANDLE	hLoopPlayEvent = NULL;
	static HANDLE  hMidiPlayerThrd = NULL;
	static CMIDI* pMidiPlayer = NULL;
	typedef void (*PDESTROY)(void);
	static PDESTROY DestroyMidiPlayer;
	BOOL IsValidMidiDataPtr(MIDIFILEDATAINFO pData)
	{
		if (pData.pData == NULL) {
			return FALSE;
		}
		if (pData.dwSize > (3 * sizeof(WORD) + 2 * sizeof(DWORD))) {
			return TRUE;
		}
		return FALSE;

	}
	BOOL IsValidMidiFileName(LPCSTR pStr)
	{
		if (pStr == NULL)return FALSE;
		size_t nLen = strlen(pStr);
		if (nLen >= 4)
			return TRUE;
		return FALSE;
	}
	BOOL IsValidMidiFileName(LPCWSTR pStr)
	{
		if (pStr == NULL)return FALSE;
		size_t nLen = wcslen(pStr);
		if (nLen >= 4)
			return TRUE;
		return FALSE;

	}
	size_t GetMidiDataCount(vector<MIDMUSIC> MIDDATA)
	{
		size_t nArg = MIDDATA.size();
		size_t nCount = 0;
		for (size_t i = 0; i < nArg; i++)
		{


			if (MIDDATA[i].datatype == 2)//
			{

				if (IsValidMidiDataPtr(MIDDATA[i].data))
					nCount++;

			}
			else if (MIDDATA[i].datatype == 0) {//string

				if (IsValidMidiFileName(MIDDATA[i].name))
					nCount++;

			}
			else if (MIDDATA[i].datatype == 1) {//wstring

				if (IsValidMidiFileName(MIDDATA[i].wname)) {
					nCount++;
				}
			}
			else {
			}
		}

		return nCount;


	}
	BOOL GetMidiDataFromPtr(MIDIFILEDATAINFO pData, size_t nIDX)
	{
		pMidiFileData[nIDX].dwSize = pData.dwSize;
		pMidiFileData[nIDX].pData = new BYTE[pData.dwSize];
		if (pMidiFileData[nIDX].pData == NULL)return FALSE;
		memcpy(pMidiFileData[nIDX].pData, pData.pData, pMidiFileData[nIDX].dwSize);
		return TRUE;
	}
	BOOL GetMidiDataFromFile(LPCWSTR pStr, size_t nIDX)
	{
		HANDLE hFile = CreateFileW(pStr,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_ARCHIVE,
			0);


		if (hFile != INVALID_HANDLE_VALUE)
		{

			DWORD dwNumOfByteRead;
			INT nLen = GetFileSize(hFile, &dwNumOfByteRead);
			pMidiFileData[nIDX].dwSize = nLen;
			pMidiFileData[nIDX].pData = new BYTE[nLen];
			if (pMidiFileData[nIDX].pData)
			{
				if (ReadFile(hFile, pMidiFileData[nIDX].pData, nLen, &dwNumOfByteRead, 0))
				{
					CloseHandle(hFile);
					return TRUE;
				}
			}
			CloseHandle(hFile);

		}
		pMidiFileData[nIDX].dwSize = 0;
		pMidiFileData[nIDX].pData = NULL;
		return FALSE;

	}
	BOOL GetMidiDataFromFile(LPCSTR pStr, size_t nIDX)
	{
		HANDLE hFile = CreateFileA(pStr,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_ARCHIVE,
			0);


		if (hFile != INVALID_HANDLE_VALUE)
		{

			DWORD dwNumOfByteRead;
			INT nLen = GetFileSize(hFile, &dwNumOfByteRead);
			pMidiFileData[nIDX].dwSize = nLen;
			pMidiFileData[nIDX].pData = new BYTE[nLen];
			if (pMidiFileData[nIDX].pData)
			{
				if (ReadFile(hFile, pMidiFileData[nIDX].pData, nLen, &dwNumOfByteRead, 0))
				{
					CloseHandle(hFile);
					return TRUE;
				}
			}
			CloseHandle(hFile);

		}
		pMidiFileData[nIDX].dwSize = 0;
		pMidiFileData[nIDX].pData = NULL;
		return FALSE;

	}
	size_t GetMidiDataFromArg(vector<MIDMUSIC> MIDDATA)
	{
		size_t nArg = MIDDATA.size();
		size_t nCount = 0;
		size_t nArry = 0;
		for (size_t i = 0; i < nArg; i++)
		{


			if (MIDDATA[i].datatype == 2)//pbyte
			{

				if (IsValidMidiDataPtr(MIDDATA[i].data))
				{
					if (GetMidiDataFromPtr(MIDDATA[i].data, nArry))
						nArry++;
					nCount++;
				}

			}
			else if (MIDDATA[i].datatype == 0) {//string

				if (IsValidMidiFileName(MIDDATA[i].name))
				{
					if (GetMidiDataFromFile(MIDDATA[i].name, nArry))
						nArry++;
					nCount++;
				}

			}
			else if (MIDDATA[i].datatype == 1) {//wstring

				if (IsValidMidiFileName(MIDDATA[i].wname))
				{
					if (GetMidiDataFromFile(MIDDATA[i].wname, nArry))
						nArry++;
					nCount++;
				}

			}

		}
		return nArry;


	}
	void CloseMidiPlayer()
	{
		DestroyMidiPlayer = NULL;
		if (hMidiPlayerThrd)
		{
			TerminateThread(hMidiPlayerThrd, 0);//七号:强制中止线程。这里时候会不会导致闯入文件路径时载入音乐资源无法释放导致的泄露??
			::CloseHandle(hMidiPlayerThrd);
			hMidiPlayerThrd = NULL;
		}

		if (hLoopPlayEvent)
		{
			SetEvent(hLoopPlayEvent);
			::CloseHandle(hLoopPlayEvent);
			hLoopPlayEvent = NULL;
		}


		if (pMidiPlayer)
		{
			delete pMidiPlayer;
			pMidiPlayer = NULL;
		}
		if (pMidiFileData)
		{
			for (size_t i = 0; i < nMidiArrySize; i++)
			{
				if (pMidiFileData[i].pData)
				{
					delete[] pMidiFileData[i].pData;
					pMidiFileData[i].pData = NULL;
					pMidiFileData[i].dwSize = 0;
				}
			}
			delete[] pMidiFileData;
			pMidiFileData = NULL;
			nMidiArrySize = 0;
		}


	}


	DWORD WINAPI  PlayMidiManager(PVOID pParam)
	{

		for (INT n = 0; n < nLoopNum; n++)
		{
			for (size_t i = 0; i < nMidiArrySize; i++)
			{
				if (pMidiFileData[i].pData)
				{
					if (pMidiPlayer)
						delete  pMidiPlayer;
					pMidiPlayer = new CMIDI();
					pMidiPlayer->m_hhLoopPlayEvent = hLoopPlayEvent;
					BOOL bRet = pMidiPlayer->Create(pMidiFileData[i].pData, (DWORD)pMidiFileData[i].dwSize);
					if (bRet)
					{

						bRet = pMidiPlayer->Play();
						if (bRet)
						{
							ResetEvent(hLoopPlayEvent);
							WaitForSingleObject(hLoopPlayEvent, INFINITE);
							Sleep(nPlayWaitTime);
						}

					}
					else {
						delete[] pMidiFileData[i].pData;
						pMidiFileData[i].pData = NULL;
						pMidiFileData[i].dwSize = 0;
					}
				}
			}

		}
		::CloseHandle(hMidiPlayerThrd);
		hMidiPlayerThrd = NULL;
		CloseMidiPlayer();
		return 1;
	}
	KrnlnApi void PackMid(vector<MIDMUSIC>& MidStruct, vector<unsigned char> MemData) {
		MIDMUSIC temp;

		if (!MemData.empty())
		{
			temp.datatype = 2;
			temp.data.pData = MemData.data();
			temp.data.dwSize = MemData.size();
		}
		else {
			return;
		}

		MidStruct.push_back(temp);
	}
	KrnlnApi void PackMid(vector<MIDMUSIC>& MidStruct, wstring MemData) {
		MIDMUSIC temp;

		if (!MemData.empty())
		{
			temp.datatype = 1;
			temp.wname = MemData.c_str();
		}
		else {
			return;
		}
		MidStruct.push_back(temp);
	}
	KrnlnApi void PackMid(vector<MIDMUSIC>& MidStruct, string MemData) {
		MIDMUSIC temp;

		if (!MemData.empty())
		{
			temp.datatype = 1;
			temp.name = MemData.c_str();
		}
		else {
			return;
		}
		MidStruct.push_back(temp);
	}
	KrnlnApi void PlayMid(int times, int interval, vector<MIDMUSIC> wannaplay)
	{
		//立即中止播放线程
		CloseMidiPlayer();
		nLoopNum = times;
		if (nLoopNum == -1) {//默认最大播放次数
			nLoopNum = INT_MAX;
		}
		else if (nLoopNum <= 0) {
			return;
		}


		nPlayWaitTime = interval;

		if (nPlayWaitTime < 0) {
			nPlayWaitTime = 0;
		}
		nPlayWaitTime = nPlayWaitTime * 100;
		if (wannaplay.empty())
		{
			return;
		}
		size_t nCount = GetMidiDataCount(wannaplay);//判断有效数据
		if (nCount == 0)
			return;
		pMidiFileData = new MIDIFILEDATAINFO[nCount];
		nCount = GetMidiDataFromArg(wannaplay);
		if (nCount == 0)
		{
			delete[] pMidiFileData;
			pMidiFileData = NULL;
			return;
		}
		nMidiArrySize = nCount;

		hLoopPlayEvent = ::CreateEventW(0, FALSE, FALSE, L"Wait For Midi Play End");

		DWORD dwThreadId;
		HANDLE  hMidiPlayerThrd = CreateThread(NULL,
			0,
			PlayMidiManager,
			0,
			0,
			&dwThreadId);
		if (hMidiPlayerThrd == NULL)
		{
			CloseMidiPlayer();
			return;
		}
		DestroyMidiPlayer = (PDESTROY)CloseMidiPlayer;
	}
}
#endif // 