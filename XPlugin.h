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
	// Description:
	// The XPlugin class is responsible for loading, unloading, and calling plugin
	// files, which are libraries that extend the functionality of the application.
	// The XPlugin class contains several methods for working with plugins,
	// including methods, call, and unLoad.The methods method returns a list of
	// the available methods inside a specified plugin, while call calls a
	// specific method with given parameters.Finally, unLoad unloads a plugin
	// from memory.
	// 	The XPlugin class contains a static member variable m_Plugins, which is a
	// 	QMap that stores the loaded plugin files with their file names as keys.
	// 	This allows the application to reuse the loaded plugins instead of
	// 	reloading them every time they are needed.
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

