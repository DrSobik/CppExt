/* 
 * File:   Messages.h
 * Author: DrSobik
 *
 * Created on July 19, 2014, 3:07 PM
 * 
 * Description : Class Message implements the basic class for any message. The the type of message data can be specified by the template
 *				 parameter. IMPORTANT !!! The specified data type T must have a copy constructor correctly defined. This is especially
 *				 important if we work with pointers!!!
 * 
 *				 The class is specialized for <const char*> and <char*> to be able to work with constant strings directly. This is very
 *				 convenient.
 * 
 */

#ifndef MESSAGES_H
#define	MESSAGES_H

#include <cstring>

#include "WritableReadable"
#include "Operationable"

using namespace std;

using namespace Common::Interfaces;

namespace Common {

	namespace Messages {

		/**********************************************************************/

		template<class T = const char*> class Message : public Object<>, public Addible<Message<T>>	{
			private:

			T msgData;

			public:

			Message() : BasicObject(), Object(), Addible<Message < T >> () {
			}

			Message(const T& otherMsg) : BasicObject(), Object<>(), Addible<Message < T >> (), msgData(otherMsg) {
			}

			Message(const Message & other) : BasicObject(), Object(other), Addible<Message < T >> (), msgData(other.msgData) {
			}

			virtual ~Message() {
			}

			
			virtual Message& operator+=(const Message & other) {
				msgData += other.msgData;
				return *this;
			}

			virtual void setMsgData(const T& newMsgData) {
				msgData = newMsgData;
			}
 
			
			virtual T& getMsgData() const {
				return (T&)msgData;
			}

		};

		/**********************************************************************/

		/**********************************************************************/

		template<> Message<const char*>::Message() : BasicObject(), Object(), Addible<Message<const char*>>(), msgData(NULL) {
		}

		template<> Message<const char*>::Message(const char* const& otherMsg) : BasicObject(), Object<>(), Addible<Message<const char*>>(), msgData(NULL) {
			msgData = new char[strlen(otherMsg) + 1];
			strcpy((char*) msgData, otherMsg);
		}

		template<> Message<const char*>::Message(const Message& other) : BasicObject(), Object(other), Addible<Message<const char*>>() {
			msgData = new char[strlen(other.msgData) + 1];
			strcpy((char*) msgData, other.msgData);
		}

		template<> Message<const char*>::~Message() {
			if (msgData != NULL) {
				delete[] msgData;
			}
		}
		
		template<> void Message<const char*>::setMsgData(const char* const& newMsgData) {
			if (msgData != NULL) {
				delete[] msgData;
			}
			
			msgData = new char[strlen(newMsgData)+1];
			
			strcpy((char*)msgData, newMsgData);
		}
		
		template<> Message<const char*>& Message<const char*>::operator+=(const Message<const char*>& other) {

			char prevMsgData[strlen(msgData) + 1];

			strcpy(prevMsgData, msgData);

			if (msgData != NULL) {
				delete[] msgData;
			}

			msgData = new char[strlen(prevMsgData) + strlen(other.msgData) + 1];

			strcpy((char*) msgData, prevMsgData);
			strcat((char*) msgData, other.msgData);

			return *this;
		}

		/**********************************************************************/

		/**********************************************************************/

		template<> Message<char*>::Message() : BasicObject(), Object(), Addible<Message<char*>>(), msgData((char*) NULL) {
		}

		template<> Message<char*>::Message(char* const& otherMsg) : BasicObject(), Object<>(), Addible<Message<char*>>(), msgData((char*) NULL) {
			msgData = new char[strlen(otherMsg) + 1];
			strcpy(msgData, otherMsg);
		}

		template<> Message<char*>::Message(const Message& other) : BasicObject(), Object(other), Addible<Message<char*>>(), msgData((char*) NULL) {
			msgData = new char[strlen(other.msgData) + 1];
			strcpy(msgData, other.msgData);
		}

		template<> Message<char*>::~Message() {
			if (msgData != NULL) {
				delete[] msgData;
			}
		}

		template<> void Message<char*>::setMsgData(char* const& newMsgData) {
			if (msgData != NULL) {
				delete[] msgData;
			}
			
			msgData = new char[strlen(newMsgData)+1];
			
			strcpy((char*)msgData, newMsgData);
		}
		
		template<> Message<char*>& Message<char*>::operator+=(const Message<char*>& other) {

			char prevMsgData[strlen(msgData) + 1];

			strcpy(prevMsgData, msgData);

			if (msgData != NULL) {
				delete[] msgData;
			}

			msgData = new char[strlen(prevMsgData) + strlen(other.msgData) + 1];

			strcpy(msgData, prevMsgData);
			strcat(msgData, other.msgData);

			return *this;
		}

		/**********************************************************************/

		/**********************************************************************/

		template<class dstT, class msgDataT = const char*> class MessageWritableTo : public Message<msgDataT>, public WritableTo<dstT> {
		
		public:

			MessageWritableTo() : BasicObject(), Message<msgDataT>(), WritableTo<dstT>() {
			}

			MessageWritableTo(msgDataT& otherMsg) : BasicObject(), Message<msgDataT>(otherMsg), WritableTo<dstT>() {
			}

			MessageWritableTo(const msgDataT otherMsg) : BasicObject(), Message<msgDataT>(otherMsg), WritableTo<dstT>() {
			}

			MessageWritableTo(const MessageWritableTo& other) : BasicObject(), Message<msgDataT>(other), WritableTo<dstT>() {
			}

			MessageWritableTo(const Message<msgDataT>& other) : BasicObject(), Message<msgDataT>(other), WritableTo<dstT>() {
			}

			virtual ~MessageWritableTo() {
			}

			virtual dstT& operator>>(dstT& dst) const {

				dst << Message<msgDataT>::getMsgData();

				return dst;
			}

		};

		/**********************************************************************/

	}

}

#endif	/* MESSAGES_H */

