#include "XScript.h"
#include "../CoreStorage/XFile.h"

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XScript
// Method:  XScript
// Params:  QObject* parent
//----------------------------------------------------------------------------- 

XScript::XScript(QObject* parent) : QObject(parent)
{
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XScript
// Method:  ~XScript
//----------------------------------------------------------------------------- 

XScript::~XScript()
{
}


//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XScript
// Method:  executeScript
// Params:  const QString& filename
//----------------------------------------------------------------------------- 
void XScript::execute(const QString& filename)
{
	qDebug() << "Execute::" + filename;

	QJSValue result = engine().evaluate(XFile::readCache(filename));
	if (result.isError())
	{
		qDebug() << result.property("lineNumber").toString() << "::" << result.toString();
	}
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XScript
// Method:  command
// Params:  const QString& content
//----------------------------------------------------------------------------- 
void XScript::command(const QString& content)
{
	QJSValue result = engine().evaluate(content);
	if (result.isError())
	{
		qDebug() << result.property("lineNumber").toString() << "::" << result.toString();
	}
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    06.08.2022
// Context: DefaultNamespace
// Class:   B4DBuilder
// Method:  openScript
// Params:  const QString& filename
//----------------------------------------------------------------------------- 
void XScript::include(const QString& filename, const QStringList& paths)
{
	qDebug() << "----------------------------------------------------------";
	qDebug() << "Script::" << filename;

	// Environment
	engine().installExtensions(QJSEngine::ConsoleExtension);
	//QJSValue valuebuilder = engine().newQObject(this);
	//engine().setObjectOwnership(this, QJSEngine::CppOwnership);
	//engine().globalObject().setProperty("builder", valuebuilder);


	for (QString path : paths)
	{
		QDir dir(path);
		for (QFileInfo fileinfo : dir.entryInfoList(QStringList() << "*.js", QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::Files))
		{
			execute(path + "/" + fileinfo.fileName());
		}
	}
	execute(filename);
	qDebug() << "----------------------------------------------------------";
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   XScript
// Method:  insert
// Params:  const QString& name
// Params:  QObject* object
//----------------------------------------------------------------------------- 

void XScript::insert(const QString& name, QObject* object)
{
	QJSValue value = engine().newQObject(object);
	engine().setObjectOwnership(object, QJSEngine::CppOwnership);
	engine().globalObject().setProperty(name, value);
}
