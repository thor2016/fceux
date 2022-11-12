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
#include "Qt/ConsoleWindow.h"

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
		NetPlayServer *server = new NetPlayServer(parent);

		if (server == nullptr)
		{
			printf("Error Creating Netplay Server!!!\n");
		}
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

int NetPlayClient::Create(QObject *parent)
{
	if (NetPlayClient::GetInstance() == nullptr)
	{
		NetPlayClient *client = new NetPlayClient(parent);

		if (client == nullptr)
		{
			printf("Error Creating Netplay Client!!!\n");
		}
	}
	return 0;
}
//-----------------------------------------------------------------------------
//--- NetPlayHostDialog
//-----------------------------------------------------------------------------
NetPlayHostDialog::NetPlayHostDialog(QWidget *parent)
	: QDialog(parent)
{
	QVBoxLayout *mainLayout;
	QHBoxLayout *hbox;
	QGridLayout *grid;
	QPushButton *cancelButton, *startButton;
	QLabel *lbl;

	setWindowTitle("NetPlay Host Game");

	mainLayout = new QVBoxLayout();
	grid = new QGridLayout();

	lbl = new QLabel( tr("Server Name:") );
	grid->addWidget( lbl, 0, 0 );

	serverNameEntry = new QLineEdit();
	grid->addWidget( serverNameEntry, 0, 1 );

	lbl = new QLabel( tr("Port:") );
	grid->addWidget( lbl, 1, 0 );

	portEntry = new QSpinBox();
	portEntry->setRange(0,65535);
	portEntry->setValue(5050);
	grid->addWidget( portEntry, 1, 1 );

	mainLayout->addLayout(grid);

	startButton = new QPushButton( tr("Start") );
	startButton->setIcon(style()->standardIcon(QStyle::SP_DialogApplyButton));
	connect(startButton, SIGNAL(clicked(void)), this, SLOT(onStartClicked(void)));

	cancelButton = new QPushButton( tr("Cancel") );
	cancelButton->setIcon(style()->standardIcon(QStyle::SP_DialogCancelButton));
	connect(cancelButton, SIGNAL(clicked(void)), this, SLOT(closeWindow(void)));

	hbox = new QHBoxLayout();
	hbox->addWidget( cancelButton, 1 );
	hbox->addStretch(5);
	hbox->addWidget( startButton, 1 );
	mainLayout->addLayout( hbox );

	setLayout(mainLayout);
}
//----------------------------------------------------------------------------
NetPlayHostDialog::~NetPlayHostDialog(void)
{
	//printf("Destroy NetPlay Host Window\n");
}
//----------------------------------------------------------------------------
void NetPlayHostDialog::closeEvent(QCloseEvent *event)
{
	//printf("NetPlay Host Close Window Event\n");
	done(0);
	deleteLater();
	event->accept();
}
//----------------------------------------------------------------------------
void NetPlayHostDialog::closeWindow(void)
{
	//printf("Close Window\n");
	done(0);
	deleteLater();
}
//-----------------------------------------------------------------------------
void NetPlayHostDialog::onStartClicked(void)
{
	NetPlayServer *server = NetPlayServer::GetInstance();

	if (server != nullptr)
	{
		delete server;
		server = nullptr;
	}
	NetPlayServer::Create(consoleWindow);

	server = NetPlayServer::GetInstance();

	if (server->listen( QHostAddress::Any, portEntry->value() ) == false)
	{
		printf("Error: TCP server failed to listen\n");
	}

	done(0);
	deleteLater();
}
//-----------------------------------------------------------------------------
//--- NetPlayJoinDialog
//-----------------------------------------------------------------------------
NetPlayJoinDialog::NetPlayJoinDialog(QWidget *parent)
	: QDialog(parent)
{
	QVBoxLayout *mainLayout;
	QHBoxLayout *hbox;
	QGridLayout *grid;
	QPushButton *cancelButton, *startButton;
	QLabel *lbl;

	setWindowTitle("NetPlay Host Game");

	mainLayout = new QVBoxLayout();
	grid = new QGridLayout();

	lbl = new QLabel( tr("Host:") );
	grid->addWidget( lbl, 0, 0 );

	hostEntry = new QLineEdit();
	hostEntry->setText("localhost");
	grid->addWidget( hostEntry, 0, 1 );

	lbl = new QLabel( tr("Port:") );
	grid->addWidget( lbl, 1, 0 );

	portEntry = new QSpinBox();
	portEntry->setRange(0,65535);
	portEntry->setValue(5050);
	grid->addWidget( portEntry, 1, 1 );

	mainLayout->addLayout(grid);

	startButton = new QPushButton( tr("Join") );
	startButton->setIcon(style()->standardIcon(QStyle::SP_DialogApplyButton));
	connect(startButton, SIGNAL(clicked(void)), this, SLOT(onJoinClicked(void)));

	cancelButton = new QPushButton( tr("Cancel") );
	cancelButton->setIcon(style()->standardIcon(QStyle::SP_DialogCancelButton));
	connect(cancelButton, SIGNAL(clicked(void)), this, SLOT(closeWindow(void)));

	hbox = new QHBoxLayout();
	hbox->addWidget( cancelButton, 1 );
	hbox->addStretch(5);
	hbox->addWidget( startButton, 1 );
	mainLayout->addLayout( hbox );

	setLayout(mainLayout);
}
//----------------------------------------------------------------------------
NetPlayJoinDialog::~NetPlayJoinDialog(void)
{
	//printf("Destroy NetPlay Host Window\n");
}
//----------------------------------------------------------------------------
void NetPlayJoinDialog::closeEvent(QCloseEvent *event)
{
	//printf("NetPlay Host Close Window Event\n");
	done(0);
	deleteLater();
	event->accept();
}
//----------------------------------------------------------------------------
void NetPlayJoinDialog::closeWindow(void)
{
	//printf("Close Window\n");
	done(0);
	deleteLater();
}
//----------------------------------------------------------------------------
void NetPlayJoinDialog::onJoinClicked(void)
{
	NetPlayClient *client = NetPlayClient::GetInstance();

	if (client != nullptr)
	{
		delete client;
		client = nullptr;
	}
	NetPlayClient::Create(consoleWindow);

	client = NetPlayClient::GetInstance();

	//client->connectToHost( portEntry->value() );

	//printf("Close Window\n");
	done(0);
	deleteLater();
}
