#include "XConsole.h"

#include <QMap>
#include <QVariant>
#include "XProcess.h"
#include "../CoreBase/XDebug.h"

QTextStream XConsole::m_Output(stdout);
QTextStream XConsole::m_Debug(stderr);

bool XConsole::m_Silent=false;

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XProcessCommandCommand
// Method:  XProcessCommand
// Params:  QObject* parent
//----------------------------------------------------------------------------- 

XConsole::XConsole(QObject* parent) : QObject(parent)
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

XConsole::~XConsole()
{
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.11.2022
// Context: DefaultNamespace
// Class:   XConsole
// Method:  print
// Params:  const QString& txt
//----------------------------------------------------------------------------- 
//void XConsole::print(const QString& txt)
//{
//	m_Output<<txt;
//}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.11.2022
// Context: DefaultNamespace
// Class:   XConsole
// Method:  print
// Params:  const QVariant& var
//----------------------------------------------------------------------------- 

void XConsole::print(const QVariant& var)
{
	if (m_Silent) return;
	m_Output << var.toString() <<"\n";
	m_Output.flush();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.11.2022
// Context: DefaultNamespace
// Class:   XConsole
// Method:  print
// Params:  const QStringList& list
//----------------------------------------------------------------------------- 
void XConsole::print(const QStringList& list)
{
	if (m_Silent) return;
	for(const QString& line:list)
		m_Output << line << "\n";
	m_Output.flush();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.11.2022
// Context: DefaultNamespace
// Class:   XConsole
// Method:  print
// Params:  const QMap<QString, QVariant>& map
//----------------------------------------------------------------------------- 

void XConsole::print(const QMap<QString, QVariant>& map)
{
	if (m_Silent) return;
	for (const QString& key: map.keys())
	{
		m_Output << key+"="+map[key].toString() << "\n";
	}
	m_Output.flush();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.11.2022
// Context: DefaultNamespace
// Class:   XConsole
// Method:  print
// Params:  const QMap<QString, QString>& map
//----------------------------------------------------------------------------- 

void XConsole::print(const QMap<QString, QString>& map)
{
	if (m_Silent) return;
	for (const QString& key : map.keys())
	{
		m_Output << key + "=" + map[key] << "\n";
	}
	m_Output.flush();
}



//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.11.2022
// Context: DefaultNamespace
// Class:   XConsole
// Method:  debug
// Params:  const QString& txt
//----------------------------------------------------------------------------- 
//void XConsole::debug(const QString& txt)
//{
//	m_Debug << txt;
//}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.11.2022
// Context: DefaultNamespace
// Class:   XConsole
// Method:  debug
// Params:  const QVariant& var
//----------------------------------------------------------------------------- 

void XConsole::debug(const QVariant& var)
{
	if (m_Silent) return;
	m_Debug << var.toString() << "\n";
	m_Debug.flush();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.11.2022
// Context: DefaultNamespace
// Class:   XConsole
// Method:  debug
// Params:  const QStringList& list
//----------------------------------------------------------------------------- 
void XConsole::debug(const QStringList& list)
{
	if (m_Silent) return;

	for (const QString& line : list)
		m_Debug << line << "\n";

	m_Debug.flush();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.11.2022
// Context: DefaultNamespace
// Class:   XConsole
// Method:  debug
// Params:  const QMap<QString, QVariant>& map
//----------------------------------------------------------------------------- 

void XConsole::debug(const QMap<QString, QVariant>& map)
{
	if (m_Silent) return;

	for (const QString& key : map.keys())
	{
		m_Debug << key + "=" + map[key].toString() << "\n";
	}
	m_Debug.flush();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.11.2022
// Context: DefaultNamespace
// Class:   XConsole
// Method:  debug
// Params:  const QMap<QString, QString>& map
//----------------------------------------------------------------------------- 

void XConsole::debug(const QMap<QString, QString>& map)
{
	if (m_Silent) return;

	for (const QString& key : map.keys())
	{
		m_Debug << key + "=" + map[key] << "\n";
	}
	m_Debug.flush();
}


