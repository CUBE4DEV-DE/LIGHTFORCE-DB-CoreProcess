#pragma once

#include "CoreProcessGlobal.h"

#include <QString>
#include <QObject>
#include <QProcess>
#include <QMap>
#include <QDataStream>

namespace CoreProcess
{
//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  XProcess
//----------------------------------------------------------------------------- 
	
class COREPROCESS_EXPORT XProcess  : public QObject
{
	Q_OBJECT

public:
	XProcess(QObject *parent=Q_NULLPTR);
	virtual ~XProcess();

	void setPath(const QString& path) { m_Path=path; }
	void setExecutable(const QString& exefilename);
	void arg(const QString& value);
	void args(const QStringList& values);
	void binary(const QByteArray& value);
	
	void env(const QString& name, const QString& value);
	QString env(const QString& name);
	void preInsertEnv(const QString& name, const QString& value, const QString& delimiter = ";");
	void postInsertEnv(const QString& name, const QString& value, const QString& delimiter = ";");
	void insertEnv(const QString& name, const QString& value);

	QStringList envs();

	void qt();
	void exec(bool run=false);
	void cmd(const QString&command, bool run = false);

	const QStringList& output() { return m_Output; }
	const QStringList& error() { return m_Error; }

	template <class T>
	static QByteArray pack(const T& data);

	template <class T>
	static T unPack(QByteArray data);

private:
	QString m_Executable;
	QString m_Path;
	QList<QString> m_Args;
	QProcessEnvironment m_Environment;
	QStringList m_Output;
	QStringList m_Error;
};

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  pack
// Params:  const T& data
//----------------------------------------------------------------------------- 
template <class T>
QByteArray XProcess::pack(const T& data)
{
	QByteArray binary;
	{
		QDataStream stream(&binary,QIODevice::WriteOnly);
		stream.setVersion(QDataStream::Qt_6_4);
		stream << data;
	}
	return qCompress(binary).toBase64();
}
//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  unPack
// Params:  QByteArray data
//----------------------------------------------------------------------------- 
template <class T>
T XProcess::unPack(QByteArray data)
{
	data = qUncompress(QByteArray::fromBase64(data));
	T values;
	{
		QDataStream stream(&data,QIODevice::ReadOnly);
		stream.setVersion(QDataStream::Qt_6_4);
		stream >> values;
	}
	return values;
}
};
using namespace CoreProcess;

