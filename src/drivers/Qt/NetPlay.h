// NetPlay.h
//

#pragma once

#include <list>

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFrame>
#include <QGroupBox>
#include <QCloseEvent>

#include <QTcpSocket>
#include <QTcpServer>

class NetPlayClient;

class NetPlayServer : public QTcpServer
{
	Q_OBJECT

	public:
		NetPlayServer(QObject *parent = 0);
		~NetPlayServer(void);

		static NetPlayServer *GetInstance(void){ return instance; };

		static int Create(QObject *parent = 0);

		bool removeClient(NetPlayClient *client, bool markForDelete = false);

		int closeAllConnections(void);

		void update(void);

		int  sendMsg( NetPlayClient *client, void *msg, size_t msgSize);
		int  sendRomLoadReq( NetPlayClient *client );
		int  sendStateSyncReq( NetPlayClient *client );

		void serverProcessMessage( NetPlayClient *client, void *msgBuf, size_t msgSize );

	private:
		static NetPlayServer *instance;

		void processPendingConnections(void);

		std::list <NetPlayClient*> clientList;

	public slots:
		void newConnectionRdy(void);
};

class NetPlayClient : public QObject
{
	Q_OBJECT

	public:
		NetPlayClient(QObject *parent = 0, bool outGoing = false);
		~NetPlayClient(void);

		static NetPlayClient *GetInstance(void){ return instance; };

		static int Create(QObject *parent = 0);

		int connectToHost( const QString host, int port );

		bool isConnected(void);

		void setSocket(QTcpSocket *s);
		QTcpSocket* getSocket(void){ return sock; };

		void update(void);
		int  readMessages( void (*msgCallback)( void *userData, void *msgBuf, size_t msgSize ), void *userData );
		void clientProcessMessage( void *msgBuf, size_t msgSize );

		QString userName;
		int     role;
		int     state;

	private:
		int createSocket(void);

		static NetPlayClient *instance;

		QTcpSocket *sock;
		int     recvMsgId;
		int     recvMsgSize;
		int     recvMsgBytesLeft;
		int     recvMsgByteIndex;
		char   *recvMsgBuf;

		static constexpr size_t recvMsgBufSize = 2 * 1024 * 1024;

	public slots:
		void onConnect(void);
		void onDisconnect(void);
};


class NetPlayHostDialog : public QDialog
{
	Q_OBJECT

public:
	NetPlayHostDialog(QWidget *parent = 0);
	~NetPlayHostDialog(void);

protected:
	void closeEvent(QCloseEvent *event);

	QLineEdit  *serverNameEntry;
	QSpinBox   *portEntry;

public slots:
	void closeWindow(void);
	void onStartClicked(void);

};

class NetPlayJoinDialog : public QDialog
{
	Q_OBJECT

public:
	NetPlayJoinDialog(QWidget *parent = 0);
	~NetPlayJoinDialog(void);

protected:
	void closeEvent(QCloseEvent *event);

	QLineEdit  *hostEntry;
	QSpinBox   *portEntry;

public slots:
	void closeWindow(void);
	void onJoinClicked(void);

};

void NetPlayPeriodicUpdate(void);
