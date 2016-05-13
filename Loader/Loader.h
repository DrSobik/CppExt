/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Loader.h
 * Author: DrSobik
 *
 * Created on April 11, 2016, 8:07 PM
 */

#ifndef LOADER_H
#define LOADER_H

namespace Common {

	namespace Interfaces {

		/**********************************************************************/

		template<class resT, class... argT> class Loader {
		private:

			/** We do not need a copy constructor for the interface. */
			Loader(const Loader&) { }

		protected:

			Loader() { }

			virtual ~Loader() { }

		public:

			virtual resT load(argT...) = 0;

		};

		/**********************************************************************/

	}

}

#endif /* LOADER_H */

