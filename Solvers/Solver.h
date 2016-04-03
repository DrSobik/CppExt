/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Solver.h
 * Author: DrSobik
 *
 * Created on March 29, 2016, 9:36 PM
 */

#ifndef SOLVER_H
#define SOLVER_H

#include "Operationable"

using namespace Common;
using namespace Common::Interfaces;

namespace Common {

	namespace Interfaces {

		/**********************************************************************/

		// Base interface for all Solvers

		template <class problemT, class solutionT> class Solver {
		public:

			// The solve method which will try to solve the problem
			virtual solutionT solve(problemT) = 0;

		private:

			/** We do not need a copy constructor for the interface. */
			Solver(const Solver&) { }

		protected:

			Solver() { }

			virtual ~Solver() { }


		};

		/**********************************************************************/

		/**********************************************************************/

		// Base interface for all iterative Solvers

		template <class problemT, class solutionT, class iterSolutionT> class IterativeSolver : public Solver<problemT, solutionT>, public PreIncrementable<iterSolutionT> {
		public:


		private:

			/** We do not need a copy constructor for the interface. */
			IterativeSolver(const IterativeSolver&) : Solver<problemT, solutionT>(), PreIncrementable<iterSolutionT>() { }

		protected:

			IterativeSolver() { }

			virtual ~IterativeSolver() { }


		};

		/**********************************************************************/

	}

}

#endif /* SOLVER_H */

