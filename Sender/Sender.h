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
		template<class T> 
		class SenderAPI {
			
		private:
			
			SenderAPI(const SenderAPI&){}
			
		protected:	
			
			SenderAPI(){}
			virtual ~SenderAPI(){}
			
		public:

			/** Add a receiver for the published something. */
			virtual void addReceiver(const ReceiverOf<T>& receiver) = 0;

			/** Remove a receiver of the published something. */
			virtual void removeReceiver(const ReceiverOf<T>& receiver) = 0;

			virtual void removeAllReceiversOf(const T&) = 0;
			
			/** Send what must be sent. */
			virtual void send(T* evt) = 0;
		};

		/**********************************************************************/
		
		/**********************************************************************/

		/** How the messages are dispatched by default : iterate over all receivers. */
		template<class T, class receiverT = ReceiverOf<T>, class contT = std::set<receiverT*>> 
		class DefaultSenderAPI : SenderAPI<T> {
		
		protected:
		
			contT receivers; // Objects which will receive something
		
		public:

			DefaultSenderAPI() : SenderAPI<T>(){}
			DefaultSenderAPI(const DefaultSenderAPI& other) : SenderAPI<T>(){
				receivers = other.receivers;
			}
			virtual ~DefaultSenderAPI(){}
			
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
				for (receiverT* curReceiver : receivers) {
					curReceiver->receive(evt);
				}
			}
		};

		/**********************************************************************/

		/**********************************************************************/

		template<class T, class senderAPI = DefaultSenderAPI<T>> 
		class SenderOf {
		
		private:
		
			senderAPI sender;

		protected:

			SenderOf(){}
			SenderOf(const SenderOf& other) : sender(other.sender){}
			virtual ~SenderOf(){}
			
		public:

			void addReceiver(const ReceiverOf<T>& receiver) {
				sender.addReceiver(receiver);
			}

			void removeReceiver(const ReceiverOf<T>& receiver) {
				sender.removeReceiver(receiver);
			}
			
			void removeAllReceiversOf(const T& evt) {
				sender.removeAllReceiversOf(evt);
			}
			
			void send(T* evt) {
				sender.send(evt);
			}

		};

		/**********************************************************************/

	}

}

#endif	/* SENDER_H */

