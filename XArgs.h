#pragma once

#include "CoreProcessGlobal.h"

#include <QString>
#include <QObject>
#include <QMap>
#include <QVariant>
#include <QDataStream>
#include <QCoreApplication>

namespace CoreProcess
{
	//-----------------------------------------------------------------------------
	// Author:  Tobias Post
	// Company: CUBE4DEV GmbH
	// Date:    29.10.2022
	// Context: DefaultNamespace
	// Class:   XProcessCommand
	// Method:  XProcessCommand
	// Description: 
	// The XArgs class contains several methods and slots, including exec(), args(),
	// command(), and call().The exec() method takes a QStringList as an argument
	// and can execute that list as arguments for a command, while the args()
	// method takes a QCoreApplication object and returns a QStringList of command - line arguments.
	// The command() method takes a QStringList and checks to see if it matches any
	// of the predefined commands like ping(), copy(), sync() orcommand().
	// The slots processPing(), processCopy(), and processSync() all return a
	// QByteArray and are called when the corresponding command is executed.
	// The XArgs class also contains a private method process() which
	// essentially runs a command as a subprocess, passing in certain
	// arguments and a boolean to determine whether the subprocess should
	// be executed asynchronously or not.
	// Overall, the XArgs class is a command - line tool that facilitates the
	// functionality of the CoreProcess namespace.
	//----------------------------------------------------------------------------- 

	class COREPROCESS_EXPORT XArgs : public QObject
	{
		Q_OBJECT
	public:
		XArgs(QObject* parent = Q_NULLPTR);
		virtual ~XArgs();
		void exec(QStringList args);

		static QStringList args(QCoreApplication& application);
		static bool command(const QStringList& args);

		static bool ping();
		static bool copy(const QString& srcdirectory, const QString& dstdirectory);
		static bool sync(const QString& address, qint32 port, const QString& rootpath, const QString& localpath, const QString& remotepath);

	public slots:
		QByteArray processPing();
		QByteArray processCopy(const QString& srcdirectory, const QString& dstdirectory);
		QByteArray processSync(const QString& address, qint32 port,const QString&rootpath, const QString& localpath, const QString& remotepath);
	private:
		QByteArray call(const QString& slotname, const QMap<QString, QVariant>& values = QMap<QString, QVariant>());
		static bool process(const QString& slotname, QMap<QString, QVariant> values= QMap<QString, QVariant>(),bool run=false);
	};

}
using namespace CoreProcess;

