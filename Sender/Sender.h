/* 
 * File:   Sender.h
 * Author: DrSobik
 *
 * Created on August 6, 2014, 11:33 PM
 */

#ifndef SENDER_H
#define	SENDER_H

#include "Exceptions"

namespace Common {

	namespace Interfaces {

		/**********************************************************************/

		template<class T> 
		class ReceiverOf {
		
		private:

			ReceiverOf(const ReceiverOf&){}
			
		protected:

			ReceiverOf(){}
			virtual ~ReceiverOf(){}
			
		public:

			virtual void receive(T* evt) = 0; // Reimplement for receiving

		};

		/**********************************************************************/

		/**********************************************************************/

		/** Interface for Sender API. */
		template<class T, class receiverT = ReceiverOf<T>> 
		class SenderOf {
			
		private:
			
			SenderOf(const SenderOf&){}
			
		protected:	
			
			SenderOf(){}
			virtual ~SenderOf(){}
			
		public:

			/** Add a receiver for the published something. */
			virtual void addReceiver(const receiverT& receiver) = 0;

			/** Remove a receiver of the published something. */
			virtual void removeReceiver(const receiverT& receiver) = 0;

			virtual void removeAllReceiversOf(const T&) = 0;
			
			/** Send what must be sent. */
			virtual void send(T* evt) = 0;
		};

		/**********************************************************************/
		
		/**********************************************************************/

		/** How the messages are dispatched by default : iterate over all receivers. */
		template<class T, class receiverT = ReceiverOf<T>, class contT = std::set<receiverT*>> 
		class DefaultSenderOf : SenderOf<T, receiverT> {
		
		protected:
		
			contT receivers; // Objects which will receive something
		
		public:

			DefaultSenderOf() : SenderOf<T, receiverT>(){}
			DefaultSenderOf(const DefaultSenderOf& other) : SenderOf<T, receiverT>(){
				receivers = other.receivers;
			}
			virtual ~DefaultSenderOf(){}
			
			virtual void addReceiver(const receiverT& receiver) {
				receivers.insert((receiverT*) & receiver);
			}

			virtual void removeReceiver(const receiverT& receiver) {
				receivers.erase((receiverT*) & receiver);
			}

			virtual void removeAllReceiversOf(const T&){
				receivers.clear();
			}
			
			virtual void send(T* evt) {
				for (auto curReceiver : receivers) {
					curReceiver->receive(evt);
				}
			}
		};

		/**********************************************************************/

	}

}

#endif	/* SENDER_H */

