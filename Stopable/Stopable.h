/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stopable.h
 * Author: DrSobik
 *
 * Created on March 30, 2016, 8:29 PM
 */

#ifndef STOPABLE_H
#define STOPABLE_H

#include "Object"
#include "Exceptions"

using namespace Common;
using namespace Common::Interfaces;
using namespace Common::Exceptions;

namespace Common {

	namespace Interfaces {

		template <class stoppedT> class Stopable;

		/**********************************************************************/

		template <class stoppedT> class StopException : public Exception<stoppedT> {
		public:

			StopException(stoppedT* sender) : Exception<stoppedT>(sender) { }

			StopException(const StopException& orig) : Exception<stoppedT>(orig) { }

			virtual ~StopException() { }

		private:
		};

		/**********************************************************************/

		/**********************************************************************/

		// Base interface for all Stopables

		template <class stoppedT> class Stopable {
		public:

			virtual void stopActions() = 0;

			void stop() {

				stopActions();

				throw StopException<stoppedT>((stoppedT*)this);

			}

			void stop(const bool& cond) {

				if (cond) {
					stop();
				}

			}

		private:

			/** We do not need a copy constructor for the interface. */
			Stopable(const Stopable&) { }

		protected:

			Stopable() { }

			virtual ~Stopable() { }


		};

		/**********************************************************************/

		/**********************************************************************/

		// Base interface for all Stopables

		template <class stoppedT, class condT> class StopableAtCondition : public Stopable<stoppedT> {
		public:

			void stop(const condT& cond) {

				stop(cond());

			}

			void stop(condT cond) {

				stop(cond());

			}

		private:

			/** We do not need a copy constructor for the interface. */
			StopableAtCondition(const StopableAtCondition&) : Stopable<stoppedT>() { }

		protected:

			StopableAtCondition() { }

			virtual ~StopableAtCondition() { }


		};

		/**********************************************************************/

	}

}

#endif /* STOPABLE_H */

