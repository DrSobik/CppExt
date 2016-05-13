/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.h
 * Author: DrSobik
 *
 * Created on 30 квітня 2016, 14:50
 */

#ifndef PARSER_H
#define PARSER_H

namespace Common {

    namespace Interfaces {

	/**********************************************************************/

	template <class resT = void, class... parsedT> class Parser {
	private:

	    /** We do not need a copy constructor for the interface. */
	    Parser(const Parser&) {
	    }

	protected:

	    Parser() {
	    }

	public:

	    virtual ~Parser() {
	    }

	    virtual resT parse(parsedT...) = 0;

	};

	/**********************************************************************/

    }

}

#endif /* PARSER_H */

