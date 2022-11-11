// NetPlay.h
//

#pragma once

#include <QTcpSocket>
#include <QTcpServer>


class NetPlayServer : public QTcpServer
{
	Q_OBJECT

	public:
		NetPlayServer(QObject *parent = 0);
		~NetPlayServer(void);

		static NetPlayServer *GetInstance(void){ return instance; };

		static int Create(QObject *parent = 0);

	private:
		static NetPlayServer *instance;

};

class NetPlayClient : public QObject
{
	Q_OBJECT

	public:
		NetPlayClient(QObject *parent = 0, bool outGoing = false);
		~NetPlayClient(void);

		static NetPlayClient *GetInstance(void){ return instance; };

	private:
		static NetPlayClient *instance;

		QTcpSocket *sock;

};


