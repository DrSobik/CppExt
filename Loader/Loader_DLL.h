/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Loader_DLL.h
 * Author: DrSobik
 *
 * Created on April 11, 2016, 9:12 PM
 */

#ifndef LOADER_DLL_H
#define LOADER_DLL_H

#include "Object"
#include "Exceptions"
#include "Loader"

using namespace Common;
using namespace Common::Interfaces;
using namespace Common::Exceptions;

namespace Common {

	namespace Util {

		/**********************************************************************/

		template<class resT, class sourceT, class nameT, class... argT> class DLLCallLoader;

		/**********************************************************************/

		template <class senderT> class DLLLoadException : public Common::Exceptions::Exception<senderT> {
		private:

		public:

			DLLLoadException(senderT* sender) : Common::Exceptions::Exception<senderT>(sender) { }

			DLLLoadException(const DLLLoadException& orig) : Common::Exceptions::Exception<senderT>(orig) { }

			virtual ~DLLLoadException() { }

		};

		/**********************************************************************/

		template <class senderT> class DLLResolveException : public Common::Exceptions::Exception<senderT> {
		private:

		public:

			DLLResolveException(senderT* sender) : Common::Exceptions::Exception<senderT>(sender) { }

			DLLResolveException(const DLLResolveException& orig) : Common::Exceptions::Exception<senderT>(orig) { }

			virtual ~DLLResolveException() { }

		};

		/**********************************************************************/

		template<class resT, class sourceT, class nameT, class... argT> class DLLResolveLoader : public Loader<resT(*)(argT...), sourceT, nameT, argT...> {
		private:

			/** We do not need a copy constructor for the interface. */
			DLLResolveLoader(const DLLResolveLoader&) { }

		protected:

		public:

			DLLResolveLoader() { }

			virtual ~DLLResolveLoader() { }

			typedef resT(*ResolvedFunction)(argT...);

			virtual ResolvedFunction load(sourceT lib, nameT name, argT... args) override {

				ResolvedFunction res = NULL;

				if (!lib.load()) {

					throw DLLLoadException<DLLResolveLoader>((DLLResolveLoader*)this);

				} else {

					ResolvedFunction resolved = NULL;

					resolved = (ResolvedFunction) lib.resolve(name);

					if (!resolved) {

						throw DLLResolveException<DLLResolveLoader>((DLLResolveLoader*)this);

					} else {

						res = resolved;

					}

				}

				return res;

			}

		};

		/**********************************************************************/

		template<class resT, class sourceT, class nameT, class... argT> class DLLCallLoader : public Loader<resT, sourceT, nameT, argT...> {
		private:

			DLLResolveLoader<resT, sourceT, nameT, argT...> resolver;
			
			/** We do not need a copy constructor for the interface. */
			DLLCallLoader(const DLLCallLoader&) : DLLResolveLoader<resT, sourceT, nameT, argT...>() { }

		protected:

		public:

			DLLCallLoader() { }

			virtual ~DLLCallLoader() { }

			typedef resT(*ResolvedFunction)(argT...);

			virtual resT load(sourceT lib, nameT name, argT... args) override {

				resT res = NULL;

				ResolvedFunction f = (ResolvedFunction) resolver.load(lib, name, args...);

				res = f(args...);

				return res;

			}

		};

		/**********************************************************************/

	}

}


#endif /* LOADER_DLL_H */

