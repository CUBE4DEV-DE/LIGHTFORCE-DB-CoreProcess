#include "XCompile.h"

#include "XProcess.h"
#include "../CoreBase/XDebug.h"

QString XCompile::m_Build;

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XCompile
// Method:  XCompile
// Params:  QObject* parent
//----------------------------------------------------------------------------- 

XCompile::XCompile(QObject* parent):QObject(parent)
{
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XCompile
// Method:  ~XCompile
//----------------------------------------------------------------------------- 

XCompile::~XCompile()
{
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    31.10.2022
// Context: DefaultNamespace
// Class:   XCompile
// Method:  compile
// Params:  const QString& filename
// Params:  const QString& configuration
// Params:  const QString& platform
// Params:  
//----------------------------------------------------------------------------- 

bool XCompile::compile(const QString&filename, const QString& configuration, const QString& platform)
{
	if (m_Build.isEmpty())
		return false;

	XProcess process;
	process.setExecutable(m_Build);
	process.arg("/p:configuration="+ configuration);
	process.arg("/p:platform="+ platform);
	process.arg("-nologo");
	process.arg(filename);
	process.exec();

	m_Output=process.output();
	m_Error=process.error();
	
	if (!process.error().isEmpty())
		return false;
		
	return true;
}