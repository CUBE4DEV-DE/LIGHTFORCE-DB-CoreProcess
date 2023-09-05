#include "XProcess.h"
#include "../CoreBase/XDebug.h"

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  XProcess
// Params:  QObject* parent
//----------------------------------------------------------------------------- 

XProcess::XProcess(QObject *parent): QObject(parent)
{
	m_Environment = QProcessEnvironment::systemEnvironment();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  ~XProcess
//----------------------------------------------------------------------------- 

XProcess::~XProcess()
{
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  executable
// Params:  const QString& exefilename
//----------------------------------------------------------------------------- 
void XProcess::setExecutable(const QString& exefilename)
{
	m_Executable = exefilename;
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  arg
// Params:  const QString& value
//----------------------------------------------------------------------------- 
void XProcess::arg(const QString& value)
{
	m_Args <<value;
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  args
// Params:  const QStringList& values
//----------------------------------------------------------------------------- 
void XProcess::args(const QStringList& values)
{
	m_Args << values;
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  binary
// Params:  const QByteArray& value
//----------------------------------------------------------------------------- 
void XProcess::binary(const QByteArray& value)
{
	m_Args << value;
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  env
// Params:  const QString& name
// Params:  const QString& value
//----------------------------------------------------------------------------- 
void XProcess::env(const QString& name, const QString& value)
{
	m_Environment.insert(name, value);
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    12.11.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  env
// Params:  const QString& name
//----------------------------------------------------------------------------- 
QString XProcess::env(const QString& name)
{
	return m_Environment.value(name);
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    12.11.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  preInsertEnv
// Params:  const QString& name
// Params:  const QString& value
// Params:  const QString& delimiter
//----------------------------------------------------------------------------- 
void XProcess::preInsertEnv(const QString& name, const QString& value, const QString& delimiter)
{
	QString val=m_Environment.value(name);
	m_Environment.insert(name, value+delimiter+val);
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    12.11.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  postInsertEnv
// Params:  const QString& name
// Params:  const QString& value
// Params:  const QString& delimiter
//----------------------------------------------------------------------------- 

void XProcess::postInsertEnv(const QString& name, const QString& value, const QString& delimiter)
{
	QString val = m_Environment.value(name);
	m_Environment.insert(name, val + delimiter + value);
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    12.11.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  insertEnv
// Params:  const QString& name
// Params:  const QString& value
//----------------------------------------------------------------------------- 

void XProcess::insertEnv(const QString& name, const QString& value)
{
	m_Environment.insert(name, value);
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  qt
//----------------------------------------------------------------------------- 
void XProcess::qt()
{
	//env()

	//env()
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  exec
// Params:  bool run
//----------------------------------------------------------------------------- 
void XProcess::exec(bool run)
{
	m_Output.clear();
	m_Error.clear();

	QProcess process;
	process.setProcessEnvironment(m_Environment);

	if (!m_Path.isEmpty())
		process.setWorkingDirectory(m_Path);

	QString commandexe(m_Executable);

	if (run)
	{
		process.startDetached(commandexe, m_Args,m_Path);
	}
	else
	{
		process.start(commandexe, m_Args);
		QObject::connect(&process, &QProcess::readyReadStandardOutput, &process, [&] {	m_Output << QString(process.readAllStandardOutput()).remove('\r').split('\n', Qt::SkipEmptyParts); });
		QObject::connect(&process, &QProcess::readyReadStandardError, &process, [&] {	m_Error << QString(process.readAllStandardError()).remove('\r').split('\n', Qt::SkipEmptyParts); });
		process.waitForStarted(60 * 1000); // Wait 60 Secs
		process.waitForFinished(120 * 60 * 1000); // 120 Minutes
	}
}


//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  cmd
// Params:  const QString& command
// Params:  bool run
//----------------------------------------------------------------------------- 
void XProcess::cmd(const QString& command, bool run)
{
	m_Executable="cmd.exe";
	m_Args << "/C" << command << m_Args;
	exec(run);
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcess
// Method:  envs
//----------------------------------------------------------------------------- 

QStringList XProcess::envs()
{
	return m_Environment.toStringList();
}
