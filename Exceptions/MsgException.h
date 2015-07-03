/* 
 * File:   MsgException.h
 * Author: DrSobik
 *
 * Created on July 19, 2014, 12:32 AM
 */

#ifndef MSGEXCEPTION_H
#define	MSGEXCEPTION_H

#include <string>

#include "Exceptions"
#include "WritableReadable"
#include "Messages"


using namespace std;
		
using namespace Common;
using namespace Common::Interfaces;
using namespace Common::Messages;

namespace Common {

	namespace Exceptions {

		/**********************************************************************/

		template<class msgT = Message<string>, class senderT = BasicObject> class MsgException : public Exception<> {
		private:

			msgT msg;

		public:

			MsgException(const msgT& someMsg, senderT* sender = NULL) : Exception(sender), msg(someMsg) {}

			MsgException(const MsgException& orig) : Exception(orig), msg(orig.msg) {}

			virtual ~MsgException() {}

			virtual msgT& getMsg() {
				return msg;
			}

		private:

			MsgException() {}

		};

		/**********************************************************************/

		/**********************************************************************/

		template<class msgT = Message<string>, class senderT = BasicObject> class InfoMsgException : public MsgException<msgT> {
		public:

			InfoMsgException(msgT someMsg, senderT* sender = NULL) : MsgException<msgT>(msgT("Info: ") + someMsg, sender) {
			}

			InfoMsgException(const InfoMsgException& orig) : MsgException<msgT>(orig) {
			}

			virtual ~InfoMsgException() {
			}

		private:

			InfoMsgException() {
			}

		};

		/**********************************************************************/

		/**********************************************************************/

		template<class msgT = Message<string>, class senderT = BasicObject> class WarnMsgException : public MsgException<msgT> {
		public:

			WarnMsgException(msgT someMsg, senderT* sender = NULL) : MsgException<msgT>(msgT("Warning: ") + someMsg, sender) {
			}

			WarnMsgException(const WarnMsgException& orig) : MsgException<msgT>(orig) {
			}

			virtual ~WarnMsgException() {
			}

		private:

			WarnMsgException() {
			}

		};

		/**********************************************************************/

		/**********************************************************************/

		template<class msgT = Message<string>, class senderT = BasicObject> class ErrMsgException : public MsgException<msgT> {
		public:

			ErrMsgException(const msgT& someMsg, senderT* sender = NULL) : MsgException<msgT>(msgT("Error: ") + someMsg, sender) {}

			ErrMsgException(const ErrMsgException& orig) : MsgException<msgT>(orig) {}

			virtual ~ErrMsgException() {}

		private:

			ErrMsgException() {}

		};

		/**********************************************************************/

	}

}

#endif	/* MSGEXCEPTION_H */

