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

	class COREPROCESS_EXPORT XConsole : public QObject
	{
		Q_OBJECT
		public:
		XConsole(QObject* parent = Q_NULLPTR);
		virtual ~XConsole();

		static void silent(bool s) { m_Silent = s; }

		//static void print(const QString& txt);
		static void print(const QVariant& var);
		static void print(const QStringList& list);
		static void print(const QMap<QString,QVariant>& map);
		static void print(const QMap<QString, QString>& map);

		//static void debug(const QString& txt);
		static void debug(const QVariant& var);
		static void debug(const QStringList& list);
		static void debug(const QMap<QString, QVariant>& map);
		static void debug(const QMap<QString, QString>& map);

		private:
			static QTextStream m_Output;
			static QTextStream m_Debug;
			static bool m_Silent;
	};

}
using namespace CoreProcess;

