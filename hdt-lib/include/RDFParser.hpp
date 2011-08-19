/*
 * RDFParser.h
 *
 *  Created on: 02/03/2011
 *      Author: mck
 */

#ifndef RDFPARSER_H_
#define RDFPARSER_H_

#include <string>
#include <istream>
#include <stdint.h>

#include <SingleTriple.hpp>
#include <HDTEnums.hpp>


namespace hdt {

class RDFCallback {
public:
	virtual void processTriple(TripleString &triple, unsigned long long pos)=0;
};

class RDFParser: public IteratorTripleString {

protected:
	RDFNotation notation;

public:
	RDFParser(RDFNotation notation) : notation(notation) { }
	~RDFParser() { }

	virtual bool hasNext()=0;
	virtual TripleString *next()=0;
	virtual void reset()=0;
	virtual uint64_t getPos()=0;
	virtual uint64_t getSize()=0;

	static RDFParser *getParser(const char *filename, RDFNotation notation);
	static RDFParser *getParser(std::istream &stream, RDFNotation notation);
};

}

#endif /* RDFPARSER_H_ */