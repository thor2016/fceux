// NetPlay.h
//

#pragma once

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

		static int Create(QObject *parent = 0);

	private:
		static NetPlayClient *instance;

		QTcpSocket *sock;

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
