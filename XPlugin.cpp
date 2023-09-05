#include "XPlugin.h"

#include <QMetaMethod>

#include "../CoreStorage/XFile.h"
#include "../CoreBase/XDebug.h"

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XPlugin
// Method:  m_Plugins
//----------------------------------------------------------------------------- 
QMap<QString, QPointer<QPluginLoader> > XPlugin::m_Plugins;

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XPlugin
// Method:  XPlugin
// Params:  QObject* parent
//----------------------------------------------------------------------------- 
XPlugin::XPlugin(QObject* parent) : QObject(parent)
{

}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XPlugin
// Method:  ~XPlugin
//----------------------------------------------------------------------------- 
XPlugin::~XPlugin()
{
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XPlugin
// Method:  methods
// Params:  const QString& libraryname
//----------------------------------------------------------------------------- 
QStringList XPlugin::methods(const QString& libraryname)
{
	QStringList methodlist;
	if (!m_Plugins.contains(libraryname))
	{
		if (!XFile::exists(libraryname))
			return QStringList();
		QPluginLoader* pluginloader = new QPluginLoader(libraryname);
		if (pluginloader == Q_NULLPTR)
			return QStringList();
		if (!pluginloader->load())
		{
			delete pluginloader;
			return QStringList();
		}
		if (!pluginloader->instance())
		{
			delete pluginloader;
			return QStringList();
		}
		m_Plugins[libraryname] = pluginloader;
	}

	if (m_Plugins.contains(libraryname) && m_Plugins[libraryname]->instance())
	{
		for (int i = 0; i < m_Plugins[libraryname]->instance()->metaObject()->methodCount(); i++)
		{
			QMetaMethod slotmethod = m_Plugins[libraryname]->instance()->metaObject()->method(i);
			methodlist << QString(slotmethod.methodSignature());
		}
	}

	return methodlist;
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XPlugin
// Method:  call
// Params:  const QString& libraryname
// Params:  const QString& slotname
// Params:  const QMap<QString, QVariant>& values
//----------------------------------------------------------------------------- 
QByteArray XPlugin::call(const QString& libraryname, const QString& slotname, const QMap<QString, QVariant>& values)
{
	if (!m_Plugins.contains(libraryname))
	{
		if (!XFile::exists(libraryname))
			return QByteArray();

		QPluginLoader* pluginloader = new QPluginLoader(libraryname);
		if (pluginloader==Q_NULLPTR)
			return QByteArray();
		if (!pluginloader->load())
		{
			delete pluginloader;
			return QByteArray();
		}
		if (!pluginloader->instance())
		{
			delete pluginloader;
			return QByteArray();
		}
		m_Plugins[libraryname] = pluginloader;
	}

	if (m_Plugins.contains(libraryname) && m_Plugins[libraryname]->instance())
	{
		return call(m_Plugins[libraryname]->instance(), slotname, values);
	}

	return QByteArray();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XPlugin
// Method:  unLoad
// Params:  const QString& libraryname
//----------------------------------------------------------------------------- 

void XPlugin::unLoad(const QString& libraryname)
{
	if (m_Plugins.contains(libraryname))
	{
		m_Plugins[libraryname]->unload();
		delete m_Plugins[libraryname];
		m_Plugins.remove(libraryname);
	}
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XPlugin
// Method:  call
// Params:  QObject* object
// Params:  const QString& slotname
// Params:  const QMap<QString, QVariant>& values
//----------------------------------------------------------------------------- 
QByteArray XPlugin::call(QObject*object,const QString& slotname, const QMap<QString, QVariant>& values)
{
	int slotid = -1;
	for (int i = 0; i < object->metaObject()->methodCount(); i++)
	{
		QMetaMethod slotmethod = object->metaObject()->method(i);
		if (QString(slotmethod.methodSignature()).indexOf(slotname + "(") == 0)
		{
			slotid = i;
			i = object->metaObject()->methodCount();
		}
	}
	if (slotid < 0)
	{
		return QByteArray();
	}

	QMetaMethod method = object->metaObject()->method(slotid);
	{
		QMetaMethodArgument arg[10];

		QString paramstring[10];
		int paramint[10];
		bool parambool[10];
		double paramdouble[10];
		long paramlong[10];
		float paramfloat[10];
		QDate paramdate[10];
		QTime paramtime[10];
		QUuid paramuuid[10];
		QByteArray parambyte[10];

		int i = 0;
		for (; i < method.parameterNames().count(); i++)
		{
			QString paramname = QString(method.parameterNames()[i]);
			QString paramtype = QString(method.parameterTypes()[i]);
			QVariant paramvalue;

			if (values.contains(paramname.toLocal8Bit()))
			{
				paramvalue = values.value(paramname.toLocal8Bit()).toString();
			}
			else if (values.contains(paramname.toUpper().toLocal8Bit()))
			{
				paramvalue = values.value(paramname.toUpper().toLocal8Bit()).toString();
			}

			if (paramtype == QString("QString"))
			{
				paramstring[i] = paramvalue.toString();
				arg[i] = Q_ARG(QString, paramstring[i]);
				//O_PARAM(paramstring[i]);
			}
			else if (paramtype == QString("int"))
			{
				paramint[i] = paramvalue.toInt();
				arg[i] = Q_ARG(int, paramint[i]);
				//O_PARAM(paramint[i]);
			}
			else if (paramtype == QString("bool"))
			{
				parambool[i] = paramvalue.toString().indexOf("T", Qt::CaseInsensitive) == 0 || paramvalue.toString().indexOf("on", Qt::CaseInsensitive) == 0;
				arg[i] = Q_ARG(bool, parambool[i]);
			}
			else if (paramtype == QString("double"))
			{
				paramdouble[i] = paramvalue.toDouble();
				arg[i] = Q_ARG(double, paramdouble[i]);
			}
			else if (paramtype == QString("float"))
			{
				paramfloat[i] = paramvalue.toFloat();
				arg[i] = Q_ARG(float, paramfloat[i]);
			}
			else if (paramtype == QString("long"))
			{
				paramlong[i] = paramvalue.toString().toLong();
				arg[i] = Q_ARG(long, paramlong[i]);
			}
			else if (paramtype == QString("QDate"))
			{
				paramdate[i] = QDate::fromString(paramvalue.toString(), Qt::ISODate);
				arg[i] = Q_ARG(QDate, paramdate[i]);
			}
			else if (paramtype == QString("QTime"))
			{
				paramtime[i] = QTime::fromString(paramvalue.toString(), Qt::ISODate);
				arg[i] = Q_ARG(QTime, paramtime[i]);
			}
			else if (paramtype == QString("QUuid"))
			{
				paramuuid[i] = QUuid(paramvalue.toString());
				arg[i] = Q_ARG(QUuid, paramuuid[i]);
			}
			else if (paramtype == QString("QByteArray"))
			{
				parambyte[i] = paramvalue.toByteArray();
				arg[i] = Q_ARG(QByteArray, parambyte[i]);
			}
			else
			{
				paramstring[i] = paramvalue.toString();
				arg[i] = Q_ARG(QString, paramstring[i]);
			}
		}

		for (; i < 10; i++)
		{
			paramstring[i] = "";
			paramint[i] = 0;
			parambool[i] = false;
			paramdouble[i] = 0;
			paramlong[i] = 0;
			paramfloat[i] = 0;
			paramdate[i] = QDate();
			paramtime[i] = QTime();
			paramuuid[i] = QUuid();
			parambyte[i] = QByteArray();
		}

		QByteArray returnValue;
		if (QMetaObject::invokeMethod(object, slotname.toLocal8Bit(), Qt::DirectConnection, Q_RETURN_ARG(QByteArray, returnValue), arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9]))
		{
			return returnValue;
		}
	}

	return QByteArray();
}
