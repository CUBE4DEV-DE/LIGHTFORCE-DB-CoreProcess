#include "XArgs.h"

#include <QMap>
#include <QVariant>

#include "XConsole.h"
#include "XProcess.h"
#include "../CoreBase/XDebug.h"
#include "../CoreNetwork/XSync.h"
#include "../CoreStorage/XDirectory.h"

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcessCommandCommand
// Method:  XProcessCommand
// Params:  QObject* parent
//----------------------------------------------------------------------------- 

XArgs::XArgs(QObject* parent) : QObject(parent)
{
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcessCommand
// Method:  ~XProcessCommand
//----------------------------------------------------------------------------- 

XArgs::~XArgs()
{
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XArgs
// Method:  exec
// Params:  QStringList& args
//----------------------------------------------------------------------------- 

void XArgs::exec(QStringList args)
{
	args.takeFirst();//Filename

	{
		args.takeFirst();// process

		if (args.contains("silent",Qt::CaseInsensitive))
		{
			XConsole::silent(true);
			args.removeAll("silent");
		}

		QMap<QString, QVariant> values=XProcess::unPack<QMap<QString, QVariant>>(args.takeFirst().toLatin1());
		if (values.contains("action"))
		{
			QTextStream out(stdout);
			out << call(values["action"].toString(), values);
			return;
		}
	}
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    05.11.2022
// Context: DefaultNamespace
// Class:   XArgs
// Method:  args
// Params:  QCoreApplication& application
// Params:  
//----------------------------------------------------------------------------- 
QStringList XArgs::args(QCoreApplication& application)
{
	QStringList arglist = application.arguments();
	arglist.takeFirst();//Filename
	
	if (arglist.contains("silent", Qt::CaseInsensitive))
	{
		XConsole::silent(true);
		arglist.removeAll("silent");
	}

	return arglist;
} 

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XArgs
// Method:  arg
// Params:  const QStringList& args
// Params:  
//----------------------------------------------------------------------------- 

bool XArgs::command(const QStringList& args)
{
	if (args.contains("process"))
	{
		XArgs arg;
		arg.exec(args);
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XArgs
// Method:  ping
//----------------------------------------------------------------------------- 
bool XArgs::ping()
{
	return process("processPing");
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XArgs
// Method:  copy
// Params:  const QString& srcdirectory
// Params:  const QString& dstdirectory
//----------------------------------------------------------------------------- 
bool XArgs::copy(const QString& srcdirectory, const QString& dstdirectory)
{
	QMap<QString, QVariant> values;
	values["srcdirectory"] = srcdirectory;
	values["dstdirectory"] = dstdirectory;
	return process("processCopy",values,true);
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XArgs
// Method:  sync
// Params:  const QString& address
// Params:  qint32 port
// Params:  const QString& rootpath
// Params:  const QString& localpath
// Params:  const QString& remotepath
//----------------------------------------------------------------------------- 
bool XArgs::sync(const QString& address, qint32 port, const QString& rootpath, const QString& localpath,const QString& remotepath)
{
	QMap<QString, QVariant> values;
	values["address"] = address;
	values["port"] = port;
	values["rootpath"] = rootpath;
	values["localpath"] = localpath;
	values["remotepath"] = remotepath;
	return process("processSync", values,true);
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XArgs
// Method:  processPing
//----------------------------------------------------------------------------- 

QByteArray XArgs::processPing()
{
	return QDateTime::currentDateTime().toString(Qt::ISODate).toLatin1();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XArgs
// Method:  processCopy
// Params:  const QString& srcdirectory
// Params:  const QString& dstdirectory
//----------------------------------------------------------------------------- 
QByteArray XArgs::processCopy(const QString& srcdirectory, const QString& dstdirectory)
{
	if (srcdirectory.isEmpty())
		return "FALSE";
	if (dstdirectory.isEmpty())
		return "FALSE";
	return XDirectory::copy(srcdirectory, dstdirectory)?"OK":"FALSE";
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XArgs
// Method:  processSync
// Params:  const QString& address
// Params:  qint32 port
// Params:  const QString& rootpath
// Params:  const QString& localpath
// Params:  const QString& remotepath
//----------------------------------------------------------------------------- 
QByteArray XArgs::processSync(const QString& address, qint32 port, const QString& rootpath, const QString& localpath,const QString& remotepath)
{
	if (address.isEmpty())
		return "FALSE";
	if (port==0)
		return "FALSE";
	if (localpath.isEmpty())
		return "FALSE";
	if (remotepath.isEmpty())
		return "FALSE";

	XSync client(port, QHostAddress(address));
	client.setRootPath(rootpath);
	return client.sync(localpath, remotepath) ? "OK" : "FALSE";
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XArgs
// Method:  call
// Params:  const QString& slotname
// Params:  const QMap<QString, QVariant>& values
//----------------------------------------------------------------------------- 
QByteArray XArgs::call(const QString& slotname, const QMap<QString, QVariant>& values)
{
	int slotid = -1;
	for (int i = 0; i < metaObject()->methodCount(); i++)
	{
		QMetaMethod slotmethod = metaObject()->method(i);
		if (QString(slotmethod.methodSignature()).indexOf(slotname + "(") == 0)
		{
			slotid = i;
			i = metaObject()->methodCount();
		}
	}
	if (slotid < 0)
	{
		return QByteArray();
	}

	QMetaMethod method = metaObject()->method(slotid);
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
		if (QMetaObject::invokeMethod(this, slotname.toLocal8Bit(), Qt::DirectConnection, Q_RETURN_ARG(QByteArray, returnValue), arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9]))
		{
			return returnValue;
		}

	}
	return QByteArray();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XArgs
// Method:  process
// Params:  const QString& slotname
// Params:  const QMap<QString, QVariant>& values
//----------------------------------------------------------------------------- 
bool XArgs::process(const QString& slotname,QMap<QString,QVariant> values, bool run)
{
	XProcess process;
	process.setExecutable(QCoreApplication::applicationFilePath());
	process.arg("process");
	values["action"] = slotname;
	process.arg(XProcess::pack<QMap<QString, QVariant>>(values));
	process.exec(run);
	if (!run)
	{
		for (const QString& o : process.output()) O_PARAM(o);
		for (const QString& e : process.error()) O_PARAM(e);
	}

	if (!process.error().isEmpty())
		return false;

	return true;
}

