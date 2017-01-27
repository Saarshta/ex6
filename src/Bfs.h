//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX1_ADV_PROGRAMMING_BFS_H
#define EX1_ADV_PROGRAMMING_BFS_H


#include <stack>
#include "AbstractNode.h"
#include "SearchAlgorithm.h"

/**
 * Class Bfs. Will implement a function which will return a trail
 * between two given nodes, using the BFS algorithm.
 */
class Bfs : public SearchAlgorithm {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<SearchAlgorithm>(*this);
    }

public:
    std::stack<AbstractNode*> *calcTrail(AbstractNode* start, AbstractNode* end);
};


#endif //EX1_ADV_PROGRAMMING_BFS_H
