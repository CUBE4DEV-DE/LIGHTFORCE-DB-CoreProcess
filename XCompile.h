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
	// Description:
	//	The XCompile class is a part of the CoreProcess library in C++, which is
	//	responsible for compiling files.It has a method called compile that takes
	//	three parameters : filename, configuration, and platform.These parameters
	//	define the file name of the file to be compiled, the configuration to be
	//	used, and the platform to be targeted, respectively.
	//	The class contains a member variable called m_Build, which is used to
	//	store the build configuration.If the m_Build variable is empty, the
	//	compile method will return false.Otherwise, the XProcess class is used
	//	to set up a process for compiling the file.The process object
	//	subsequently runs the compilation process by running the file passed in,
	//	and stores its output in m_Output and error messages in m_Error.If the
	//	m_Error variable is not empty, then the compile function will return false.
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

