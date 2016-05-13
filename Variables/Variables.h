/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Settings.h
 * Author: DrSobik
 *
 * Created on 29 квітня 2016, 22:11
 */

#ifndef VARIABLES_H
#define VARIABLES_H

#include <tuple>

#include "Changeable"
#include "Functor"
#include "Assignable"
#include "Acceptable"

namespace Common {

    namespace Interfaces {

	/**********************************************************************/

	// Base interface for all Settables

	template <class T> class Setable {
	private:

	    /** We do not need a copy constructor for the interface. */
	    Setable(const Setable&) {
	    }

	protected:

	    Setable() {
	    }

	public:

	    virtual ~Setable() {
	    }

	    virtual Setable& set(const T&) = 0;

	};

	/**********************************************************************/

	/**********************************************************************/

	// Base interface for all Gettables

	template <class T> class Getable {
	private:

	    /** We do not need a copy constructor for the interface. */
	    Getable(const Getable&) {
	    }

	protected:

	    Getable() {
	    }

	public:

	    virtual ~Getable() {
	    }

	    virtual T& get() = 0;

	    virtual const T& get() const = 0;

	};

	/**********************************************************************/


	/**********************************************************************/

	// Base interface for all Variables
	template <class valT> class Variable : public Setable<valT>, public Getable<valT>, public AssignableFrom<Variable<valT>>, public AssignableFrom<valT>, public Changeable<>, public Acceptable<Variable<valT>>
	{
	    private:

	    /** We do not need a copy constructor for the interface. */
	    Variable(const Variable&) {
	    }

	    protected:

	    Variable() {
	    }

	    public:

	    typedef valT ValueType;

	    virtual ~Variable() {
	    }

	    // Setters/Getters
	    using Setable<valT>::set;
	    using Getable<valT>::get;

	    // Assigner

	    virtual AssignableFrom<valT>& operator=(const valT & val) override {
		set(val); // Will set isChanged by default
		return *this;
	    }

	    // Assigner

	    virtual AssignableFrom<Variable < valT>>& operator=(const Variable<valT> & other) override {
		set(other.get()); // Will set isChanged by default
		return *this;
	    }

	    virtual void setChanged(const bool& ch = true) = 0;

	    // Accept the the last change and treat the setting as if did not change ever since

	    virtual void accept() override {
		setChanged(false);
	    }

	};

	/**********************************************************************/

	/**********************************************************************/

	// Base interface for all sets of Variables
	template <template <class, class, class...> class contT, class keyT, class varT> class Variables : public Subscriptable<varT, keyT>, public AssignableFrom<Variables<contT, keyT, varT>>, public Changeable<>, Acceptable<Variables<contT, keyT, varT>>
	{
	    private:

	    /** We do not need a copy constructor for the interface. */
	    Variables(const Variables&) {
	    }

	    protected:

	    contT<keyT, varT> vars;

	    Variables() {
	    }

	    public:

	    typedef contT<keyT, varT> ContainerType;

	    virtual ~Variables() {
	    }

	    // Normal access

	    varT& operator[](const keyT & key) override {
		return vars[key];
	    }

	    // Const access needs to be defined in the class itself since it is impossible to access by [] (silent element creation)

	    // Access to the container

	    const contT<keyT, varT>& container() {
		return vars;
	    }

	    // Access to the container

	    const contT<keyT, varT>& container() const {
		return vars;
	    }

	    // Assign other settings

	    AssignableFrom<Variables<contT, keyT, varT>>& operator=(const Variables<contT, keyT, varT>& other) override {
		vars = other.vars;
		return *this;
	    }

	    // Set all variables to changed or not changed
	    virtual void setChanged(const bool& ch = true) = 0;

	    // Clear
	    virtual void clear() = 0;

	};

	/**********************************************************************/

	/**********************************************************************/

	// Base interface for all sets of Variables

	template <template <class, class, class...> class contT, class keyT, template<class...> class varT, class... valT> class MultiVariables {
	private:

	    /** We do not need a copy constructor for the interface. */
	    MultiVariables(const MultiVariables&) {
	    }

	protected:

	    std::tuple<contT<keyT, varT<valT>>...> multiVars;

	    MultiVariables() {
	    }

	public:

	    virtual ~MultiVariables() {
	    }

	    template<class T> MultiVariables& set(const keyT& key, const T& val) {

		std::get<contT<keyT, varT < T>>> (multiVars)[key] = val;

		return *this;
	    }

	    template<class T> varT<T>& get(const keyT& key) {

		return std::get<contT<keyT, varT<T> >> (multiVars)[key];

	    }

	    void clear() {

		multiVars = std::make_tuple(contT<keyT, varT<valT>>()...);
		
	    }

	};

	/**********************************************************************/

    }

}

#endif /* VARIABLES_H */

