#pragma once

#include "CoreProcessGlobal.h"

#include <QString>
#include <QObject>
#include <QMap>
#include <QVariant>
#include <QPluginLoader>

namespace CoreProcess
{
	//-----------------------------------------------------------------------------
	// Author:  Tobias Post
	// Company: CUBE4DEV GmbH
	// Date:    29.10.2022
	// Context: DefaultNamespace
	// Class:   XPlugin
	// Method:  XPlugin
	//----------------------------------------------------------------------------- 

	class COREPROCESS_EXPORT XPlugin : public QObject
	{
		Q_OBJECT

	public:
		XPlugin(QObject* parent = Q_NULLPTR);
		virtual ~XPlugin();


		static QStringList methods(const QString& libraryname);

		static QByteArray call(const QString& libraryname,const QString& slotname, const QMap<QString, QVariant>& values = QMap<QString, QVariant>());
		static void unLoad(const QString& libraryname);

	private:
		static QByteArray call(QObject*object,const QString& slotname, const QMap<QString, QVariant>& values = QMap<QString, QVariant>());
		static QMap<QString, QPointer<QPluginLoader> > m_Plugins;
	};


};
using namespace CoreProcess;

