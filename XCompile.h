#pragma once

#include "CoreProcessGlobal.h"

#include <QString>
#include <QObject>

namespace CoreProcess
{

	//-----------------------------------------------------------------------------
	// Author:  Tobias Post
	// Company: CUBE4DEV GmbH
	// Date:    29.10.2022
	// Context: DefaultNamespace
	// Class:   XCompile
	// Method:  XCompile
	//----------------------------------------------------------------------------- 

	class COREPROCESS_EXPORT XCompile : public QObject
	{
		Q_OBJECT

	public:
		XCompile(QObject* parent = Q_NULLPTR);
		virtual ~XCompile();
		bool compile(const QString& filename, const QString& configuration="Release", const QString& platform= "x64");

		static void setBuild(const QString& build) { m_Build = build; }

		QStringList output() { return m_Output; }
		QStringList error() { return m_Error; }
		
	private:
		QStringList m_Output;
		QStringList m_Error;
		static QString m_Build;
	};


};
using namespace CoreProcess;

