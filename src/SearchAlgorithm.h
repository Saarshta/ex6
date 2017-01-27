//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX3_SEARCHALGORITHM_H
#define EX3_SEARCHALGORITHM_H


#include <stack>
#include "AbstractNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

/**
 * Abstract SearchAlgorithm class.
 * Different SearchAlgorithm types will inherit from this class.
 */
class SearchAlgorithm {
    friend class boost::serialization::access;

    /**
     * serialize function for SearchAlgorithm class.
     * @param ar
     * @param version
     */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
    }
public:
    virtual std::stack<AbstractNode*> *calcTrail(AbstractNode* start, AbstractNode* end)=0;
};


#endif //EX3_SEARCHALGORITHM_H
