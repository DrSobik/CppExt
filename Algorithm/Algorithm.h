/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Algorithm.h
 * Author: DrSobik
 *
 * Created on March 30, 2016, 8:13 PM
 */

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Operationable"


using namespace Common;
using namespace Common::Interfaces;

namespace Common {

	namespace Interfaces {

		/**********************************************************************/

		// Base interface for all Algorithms

		class Algorithm {
		public:


		private:

			/** We do not need a copy constructor for the interface. */
			Algorithm(const Algorithm&) { }

		protected:

			Algorithm() { }

			virtual ~Algorithm() { }


		};

		/**********************************************************************/

		/**********************************************************************/

		// Base interface for all iterative Solvers

		template <class iterResT> class IterativeAlgorithm : public virtual Algorithm, public PreIncrementable<iterResT> {
		public:


		private:

			/** We do not need a copy constructor for the interface. */
			IterativeAlgorithm(const IterativeAlgorithm&) : Algorithm() { }

		protected:

			IterativeAlgorithm() { }

			virtual ~IterativeAlgorithm() { }


		};

		/**********************************************************************/

	}

}


#endif /* ALGORITHM_H */

