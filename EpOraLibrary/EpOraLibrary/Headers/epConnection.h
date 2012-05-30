// OraLib 0.0.3 / 2002-06-30
//	connection.h
//
//	http://606u.dir.bg/
//	606u@dir.bg

#ifndef	__EP_CONNECTION_H__
#define	__EP_CONNECTION_H__

#include "epOraLib.h"
namespace epol 
{
	class Statement;
	class ResultSet;

	class EP_ORACLELIB Connection
	{
		// friends
		friend class Statement;
		friend class Parameter;
		friend class ResultSet;
		friend class Column;


	public:
		Connection ();

		// create an instance and open the connection
		Connection (const char *serviceName, const char *loginID,const char *password, unsigned long envMode = OCI_OBJECT, bool nonBlockingMode = false);

		~Connection ();

		// connects to an Oracle server
		void Open (const char *serviceName,const char *loginID,const char *password,unsigned long envMode = OCI_OBJECT, bool nonBlockingMode = false);

		// closes the connection
		void Close ();

		// executes a sql statement with no result
		void Execute (const char *sqlStmt, int sqlStmtLen = -1);

		// prepares (and returns) a sql statement for execution
		Statement *Prepare (const char *sqlStmt,int sqlStmtLen = -1);

		// executes a select sql statement and return the result set
		ResultSet *Select (const char *selectStmt, int selectStmtLen = -1);

		// commits changes
		inline void Commit ()
		{ 
			Execute ("commit", 6); 
		};

		// rollbacks changes
		inline void rollback ()
		{ 
			Execute ("rollback", 8); 
		};


	private:
		// private copy-constructor and assignment operator - class could not be copied
		inline Connection (const Connection& /* cn */) { /* could not be copy-constructed */ };
		inline Connection& operator = (const Connection& /* cn */) 
		{
			return (*this); /* could not be copy-constructed */ 
		};

		// initialize private data
		void initialize ();

		// free resources allocated
		inline void cleanup () 
		{
			Close (); 
		};


		OCIEnv		*m_envHandle;
		OCIServer	*m_serverHandle;
		mutable OCIError	*m_errorHandle;	// because it could be changed by most oracle APIs
		OCISession	*m_sessionHandle;
		OCISvcCtx	*m_svcContextHandle;

		bool		m_isOpened;
		bool		m_isAvailable;			// (used for connection pooling)?
		bool		m_isBlocking;			// mode (a call could return OCI_STILL_EXECUTING)


	}; // connection class


}; // oralib namespace


#endif	// __EP_CONNECTION_H__
