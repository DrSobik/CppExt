/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RandExt_CombinedRandGen.h
 * Author: DrSobik
 *
 * Created on April 7, 2016, 12:14 AM
 */

#ifndef RANDEXT_COMBINEDRANDGEN_H
#define RANDEXT_COMBINEDRANDGEN_H

namespace Common {

	namespace Rand {

		/**********************************************************************/
		
		template <class initrgT, class... rgT> class CombinedRandGen {
		private:

			std::tuple<initrgT, rgT...> rg; //Random generator

			/** We do not need a copy constructor for the interface. */
			CombinedRandGen(const CombinedRandGen&) { }

		protected:

			//TestGeneralRandGen() { }

			//virtual ~TestGeneralRandGen() { }

		public:

			CombinedRandGen() {
				init();
			}

			virtual ~CombinedRandGen() { }

			template<class somergT> void init(const somergT&) {
				std::get<somergT>(rg).init();
			}

			template<class somergT, class... somergTs> void init(const somergT&, const somergTs&... somergts) {
				std::get<somergT>(rg).init();
				init < somergTs...>(somergts...);
			}

			virtual void init() final {
				init<initrgT, rgT...> (initrgT(), rgT()...);
			}

			template <class somergT> typename somergT::ValueType rnd() {
				return std::get<somergT> (rg).rnd();
			}

		};

		/**********************************************************************/

	}

}


#endif /* RANDEXT_COMBINEDRANDGEN_H */

