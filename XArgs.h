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

