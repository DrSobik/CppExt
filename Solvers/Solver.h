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

        template <class solutionT, class problemT, class... parametersT> class Solver {
        private:

            /** We do not need a copy constructor for the interface. */
            Solver(const Solver&) {
            }

        protected:

            Solver() {
            }

        public:

            virtual ~Solver() {
            }

            // The solve method which will try to solve the problem
            virtual solutionT solve(problemT, parametersT...) = 0;


        };

        /**********************************************************************/

        /**********************************************************************/

        // Base interface for all iterative Solvers

        template <class solutionT, class iterSolutionT, class problemT, class... parametersT> class IterativeSolver : public Solver<solutionT, problemT, parametersT...>, public PreIncrementable<iterSolutionT> {
        private:

            /** We do not need a copy constructor for the interface. */
            IterativeSolver(const IterativeSolver&) : Solver<solutionT, problemT, parametersT...>(), PreIncrementable<iterSolutionT>() {
            }

        protected:

            IterativeSolver() {
            }

        public:

            using Solver<solutionT, problemT, parametersT...>::solve;

            virtual ~IterativeSolver() {
            }

        };

        /**********************************************************************/

    }

}

#endif /* SOLVER_H */

