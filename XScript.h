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

