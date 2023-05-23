// NetPlayMsgDef.h

#pragma once

#include <string.h>
#include <stdint.h>

#pragma pack(push,4)

enum netPlayMsgType
{
	NETPLAY_AUTH_REQ,
	NETPLAY_AUTH_RESP,
	NETPLAY_LOAD_ROM_REQ,
	NETPLAY_SYNC_STATE,
	NETPLAY_RUN_FRAME_REQ,
	NETPLAY_RUN_FRAME_RESP,
	NETPLAY_CTRL_UPDATE,
};

static const uint32_t NETPLAY_MAGIC_NUMBER = 0xaa55aa55;

struct netPlayMsgHdr
{
	uint32_t  magic[2];
	uint32_t  msgId;
	uint32_t  msgSize;

	netPlayMsgHdr( uint32_t id, uint32_t size = sizeof(netPlayMsgHdr) )
	{
		magic[0] = NETPLAY_MAGIC_NUMBER;
		magic[1] = NETPLAY_MAGIC_NUMBER;
		msgId = id; msgSize = size;
	}
};

struct netPlayAuthReq
{
	netPlayMsgHdr  hdr;

	uint8_t  ctrlMask;

	netPlayAuthReq(void)
		: hdr(NETPLAY_AUTH_REQ, sizeof(netPlayAuthReq)), ctrlMask(0)
	{
	}
};

struct netPlayAuthResp
{
	netPlayMsgHdr  hdr;

	uint32_t  ctrlId;
	char pswd[128];

	netPlayAuthResp(void)
		: hdr(NETPLAY_AUTH_RESP, sizeof(netPlayAuthResp)), ctrlId(0)
	{
		memset(pswd, 0, sizeof(pswd));
	}
};

struct netPlayLoadRomReq
{
	netPlayMsgHdr  hdr;

	uint32_t  fileSize;
	char fileName[256];

	netPlayLoadRomReq(void)
		: hdr(NETPLAY_LOAD_ROM_REQ, sizeof(netPlayLoadRomReq)), fileSize(0)
	{
		memset(fileName, 0, sizeof(fileName));
	}
};


struct netPlayRunFrameReq
{
	netPlayMsgHdr  hdr;

	uint32_t  frameNum;
	uint32_t  ctrlState;
};

struct netPlayRunFrameResp
{
	netPlayMsgHdr  hdr;

	uint32_t  frameNum;
	uint32_t  ctrlState;
};

#pragma pack(pop)
