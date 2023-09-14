#pragma once

#include "CoreProcessGlobal.h"

#include <QString>
#include <QObject>

#include <QtQml/QJSEngine>


namespace CoreProcess
{

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   XScript
// Method:  XScript
// Description:
//	The XScript class is a part of the CoreProcess namespace and
//	it is a subclass of QObject. It has several methods like execute(),
//	command(), include(), and insert() which are used to handle the
//	execution of JavaScript code.
//	The execute method takes a QString argument which represents the filename
//	and is used to run JavaScript code from that file.The command method
//	takes a QString argument that contains the JavaScript command to execute.
//	Furthermore, include method takes a filename as its first argument
//	and a list of paths as its second argument.It is used to include other
//  JavaScript files in the current script.Finally, the insert method
//  takes a QObject pointer as its second argument and binds this
//  object to a JavaScript element.The engine() method returns a
//  reference to the QJSEngine instance that is used by the class.
//----------------------------------------------------------------------------- 

class COREPROCESS_EXPORT XScript : public QObject
{
	Q_OBJECT

public:
	XScript(QObject* parent = Q_NULLPTR);
	virtual ~XScript();

	void execute(const QString& filename);
	void command(const QString& content);

	void include(const QString& filename, const QStringList& paths);
	void insert(const QString& name, QObject* object);
	
	QJSEngine& engine() { return  m_Engine; }
private:
	QJSEngine m_Engine;

};


};
using namespace CoreProcess;

