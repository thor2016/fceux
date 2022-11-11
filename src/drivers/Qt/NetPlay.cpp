/* FCE Ultra - NES/Famicom Emulator
 *
 * Copyright notice for this file:
 *  Copyright (C) 2002 Xodnizel
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "Qt/NetPlay.h"

//-----------------------------------------------------------------------------
//--- NetPlayServer
//-----------------------------------------------------------------------------
NetPlayServer *NetPlayServer::instance = nullptr;

NetPlayServer::NetPlayServer(QObject *parent)
	: QTcpServer(parent)
{
	instance = this;

}


NetPlayServer::~NetPlayServer(void)
{
	instance = nullptr;

}

int NetPlayServer::Create(QObject *parent)
{
	if (NetPlayServer::GetInstance() == nullptr)
	{
		new NetPlayServer(parent);
	}
	return 0;
}
//-----------------------------------------------------------------------------
//--- NetPlayClient
//-----------------------------------------------------------------------------
NetPlayClient *NetPlayClient::instance = nullptr;

NetPlayClient::NetPlayClient(QObject *parent, bool outGoing)
	: sock(nullptr)
{
	if (outGoing)
	{
		instance = this;
	}
}


NetPlayClient::~NetPlayClient(void)
{
	if (instance == this)
	{
		instance = nullptr;
	}

}
