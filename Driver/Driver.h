/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Driver.h
 * Author: DrSobik
 *
 * Created on April 3, 2016, 11:04 PM
 */

#ifndef DRIVER_H
#define DRIVER_H

namespace Common {

	namespace Interfaces {

		/**********************************************************************/

		// Base interface for all Drivers

		template <class drivenT> class DriverOf {
		private:

			/** We do not need a copy constructor for the interface. */
			DriverOf(const DriverOf&) { }

		protected:

			DriverOf() { }

			virtual ~DriverOf() { }


		public:

			virtual drivenT driven() = 0;

		};

		/**********************************************************************/

	}

}

#endif /* DRIVER_H */

