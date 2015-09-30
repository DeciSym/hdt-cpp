/*
 * File: HDTFactory.cpp
 * Last modified: $Date$
 * Revision: $Revision$
 * Last modified by: $Author$
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Contacting the authors:
 *   Mario Arias:               mario.arias@gmail.com
 *   Javier D. Fernandez:       jfergar@infor.uva.es
 *   Miguel A. Martinez-Prieto: migumar2@infor.uva.es
 *
 */

#include <HDT.hpp>
#include <HDTVocabulary.hpp>

#include "HDTFactory.hpp"

#include "BasicHDT.hpp"
#include "BasicModifiableHDT.hpp"

#include "../header/PlainHeader.hpp"

#include "../dictionary/PlainDictionary.hpp"
#include "../dictionary/FourSectionDictionary.hpp"
#ifdef HAVE_CDS
#include "../dictionary/LiteralDictionary.hpp"
#endif

#include "../triples/TriplesList.hpp"
#ifndef WIN32
#include "../triples/TripleListDisk.hpp"
#endif
#include "../triples/PlainTriples.hpp"
#include "../triples/CompactTriples.hpp"
#include "../triples/BitmapTriples.hpp"


using namespace hdt;


namespace hdt {

HDT *HDTFactory::createDefaultHDT()
{
	BasicHDT *h = new BasicHDT();
	return h;
}

HDT *HDTFactory::createHDT(HDTSpecification &spec)
{
	BasicHDT *h = new BasicHDT(spec);
	return h;
}

ModifiableHDT *HDTFactory::createDefaultModifiableHDT()
{
	BasicModifiableHDT *h = new BasicModifiableHDT();
	return h;
}

ModifiableHDT *HDTFactory::createModifiableHDT(HDTSpecification &spec)
{
	BasicModifiableHDT *h = new BasicModifiableHDT(spec);
	return h;
}

Triples *HDTFactory::readTriples(ControlInformation &controlInformation, HDTSpecification* specification) {
	std::string triplesType = controlInformation.getFormat();

	if(triplesType==HDTVocabulary::TRIPLES_TYPE_BITMAP) {
		return specification ? new BitmapTriples(*specification) : new BitmapTriples();
	} else if(triplesType==HDTVocabulary::TRIPLES_TYPE_COMPACT) {
		return specification ? new CompactTriples(*specification) : new CompactTriples();
	} else if(triplesType==HDTVocabulary::TRIPLES_TYPE_PLAIN) {
		return specification ? new PlainTriples(*specification) : new PlainTriples();
	} else if(triplesType==HDTVocabulary::TRIPLES_TYPE_TRIPLESLIST) {
		return specification ? new TriplesList(*specification) : new TriplesList();
#ifndef WIN32
	} else if(triplesType==HDTVocabulary::TRIPLES_TYPE_TRIPLESLISTDISK) {
		return new TripleListDisk();
#endif
	}

	throw "Triples Implementation not available";
}

Dictionary *HDTFactory::readDictionary(ControlInformation &controlInformation) {
	std::string type = controlInformation.getFormat();

	if(type==HDTVocabulary::DICTIONARY_TYPE_PLAIN) {
		return new PlainDictionary();
	} else if(type==HDTVocabulary::DICTIONARY_TYPE_FOUR) {
		return new FourSectionDictionary();

	} else if(type==HDTVocabulary::DICTIONARY_TYPE_CASE_INSENSITIVE_LITERAL) {
#ifdef HAVE_CDS
		return new LiteralDictionary();
#else
		throw "This version has been compiled without support for this dictionary";
#endif
	} else if(type==HDTVocabulary::DICTIONARY_TYPE_LITERAL) {
		throw "Case-sensitive HDT files are not supported by this version.";
    }

	throw "Dictionary Implementation not available";
}

Header *HDTFactory::readHeader(ControlInformation &controlInformation) {
    if(controlInformation.getType()!=HEADER)
		throw "Trying to get Header from Non-Header section";

	return new PlainHeader();
}


}
