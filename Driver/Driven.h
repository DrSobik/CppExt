/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Driven.h
 * Author: DrSobik
 *
 * Created on April 3, 2016, 11:04 PM
 */

#ifndef DRIVEN_H
#define DRIVEN_H

namespace Common {

	namespace Interfaces {

		/**********************************************************************/

		// Base interface for all Driven objects

		template <class driverT> class DrivenBy {
		private:

			/** We do not need a copy constructor for the interface. */
			DrivenBy(const DrivenBy&) { }

		protected:

			DrivenBy() { }

			virtual ~DrivenBy() { }


		public:

			virtual driverT driver() = 0;

		};

		/**********************************************************************/

	}

}

#endif /* DRIVEN_H */

