/* 
 * File:   Debug.h
 * Author: DrSobik
 *
 * Created on January 30, 2010, 2:52 PM
 */

#ifndef _DEBUG_H
#define	_DEBUG_H

#include <iostream>
//#include <ostream>
#include <stdlib.h>
#include <string>

using namespace std;


namespace Common {

	enum StreamManipulator {
		ENDL
	};

	class ADebuggerOStream : public ostream {
	public:

	private:
		bool pre_msg; // Perform actions before the message is printed
		//bool post_msg; // Perform actions after the message is pronted
	private:

		virtual void preMsg() {
			identify();
		}

		virtual void postMsg() {
		}

		virtual void identify() {
			cout << "NONE! ";
		}

		virtual void writeIdent() {
			if (pre_msg) {
				identify();
				pre_msg = false;
			}
		}

		virtual void write(const string &msg) {
			writeIdent();
			cout << msg;
		}

		virtual void write(const int &val) {
			writeIdent();
			cout << val;
		}

		virtual void write(const unsigned int &val) {
			writeIdent();
			cout << val;
		}
		
		virtual void write(const double &val) {
			writeIdent();
			cout << val;
		}

		virtual void write(StreamManipulator manip) {
			switch (manip) {
				case ENDL:
				{
					pre_msg = true;
					cout << endl;
					postMsg();
				}
			}
		}

	public:

        ADebuggerOStream():ostream(cout.rdbuf()){
			//cout<<"ADebuggerOStream()"<<endl;
			pre_msg = true;
		}

		friend ADebuggerOStream & operator<<(ADebuggerOStream& strm, const string &msg) {
			//strm.write("Info: ");
			strm.write(msg);
			return strm;
		}

		friend ADebuggerOStream & operator<<(ADebuggerOStream& strm, const char* msg) {
			//strm.write("Info: ");
			strm.write(msg);
			return strm;
		}

		friend ADebuggerOStream & operator<<(ADebuggerOStream& strm, const int &val) {
			//strm.write("Info: ");
			strm.write(val);
			return strm;
		}

		friend ADebuggerOStream & operator<<(ADebuggerOStream& strm, const double &val) {
			//strm.write("Info: ");
			strm.write(val);
			return strm;
		}

		friend ADebuggerOStream & operator<<(ADebuggerOStream& strm, StreamManipulator manip) {
			//strm.write("Info: ");
			strm.write(manip);
			return strm;
		}
	};

	class DebuggerOStreamInfo : public ADebuggerOStream {
	public:

		DebuggerOStreamInfo() : ADebuggerOStream() {
		}

	private:

#    ifndef IDEBUG

        virtual void write(const string &) {
        }

        virtual void write(const int &) {
        }

        virtual void write(const double &) {
        }

        virtual void write(StreamManipulator ) {
        }

#    endif

#    ifdef IDEBUG

		virtual void identify() {
			cout << "Info. ";
		}
#    endif

	};

	class DebuggerOStreamWarn : public ADebuggerOStream {
	public:

		DebuggerOStreamWarn() : ADebuggerOStream() {

		}
	private:
#    ifndef WDEBUG

        virtual void write(const string &) {
        }

        virtual void write(const int &) {
        }

        virtual void write(const double &) {
        }

        virtual void write(StreamManipulator) {
        }

#    endif

#    ifdef WDEBUG

		virtual void identify() {
			cout << "Warning! ";
		}
#    endif

	};

	class DebuggerOStreamError : public ADebuggerOStream {
	public:

		DebuggerOStreamError() : ADebuggerOStream() {
			//cout<<"DebuggerOStreamError():ADebuggerOStream()"<<endl;
		}
	private:

#    ifndef EDEBUG

        virtual void write(const string &) {
        }

        virtual void write(const int &) {
        }

        virtual void write(const double &) {
        }

        virtual void write(StreamManipulator) {
        }

#    endif

#    ifdef EDEBUG

		virtual void identify() {
			cout << "Error!!! ";
		}

		virtual void postMsg() {
			cout << " Exiting the program!" << endl;
			exit(-1);
		}

#    endif

	};

	class Debugger {
	public:
		static DebuggerOStreamInfo info;
		static DebuggerOStreamWarn warn;
		static DebuggerOStreamError err;
	public:

		/** General information debug message. */
#    if defined IDEBUG
        static inline void iDebug(const string &msg) {

			cout << "Info. " << msg << endl;

		}
#    endif
#    ifndef IDEBUG
        static inline void iDebug(const string &) {

        }
#    endif

		/** General warning debug message. */
#    if defined WDEBUG
		static inline void wDebug(const string &msg) {

			cout << "Warning! " << msg << endl;
		}
#    endif
#    ifndef WDEBUG
        static inline void wDebug(const string &) {

        }
#    endif

		/** General error debug message. Forces the program terminate. */
#    if defined EDEBUG
        static inline void eDebug(const string &msg) {

			cerr << "Error!!! " << msg << " Exiting the program ..." << endl;
			exit(-1);
		}
#    endif
#    ifndef EDEBUG
        static inline void eDebug(const string &) {

        }
#    endif


	};
}
#endif	/* _DEBUG_H */

