//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include <queue>
#include <stack>
#include "Bfs.h"

using namespace std;

/**
 * calcTrail - returns the shortest path between two nodes, using the BFS
 * algorithm.
 * @param start the starting node.
 * @param end the end node.
 * @return the shortest path between the two nodes.
 */
std::stack<AbstractNode *> *Bfs::calcTrail(AbstractNode *start, AbstractNode *end) {
    std::queue<AbstractNode*> queue;
    std::stack<AbstractNode*> *stack = new std::stack<AbstractNode*>;
    start->setDistance(0);
    queue.push(start);
    AbstractNode* current = NULL;
    AbstractNode* neighbour = NULL;
    AbstractNode* traceBack = NULL;
    bool isEndFound = false;
    while (!(queue.empty())) {
        current = queue.front();
        queue.pop();
        // Go through of all of a node's neighbours.


            for (int i = 0; i < current->getNeighboursNum(); i++) {
                if ((!current->isIsObst()) && (!current->getNeighbours()[i]->isIsObst())) {
                    neighbour = current->getNeighbours()[i];
                    // If the neighbour has not been visited yet.
                    if (neighbour->getDistance() == -1) {
                        // Update the neighbour's distance from the start.
                        neighbour->setDistance(current->getDistance() + 1);
                        // Set the neighbour's previous node.
                        neighbour->setPrev(current);
                        // Add to the queue.
                        queue.push(neighbour);
                    }
                    /*
                     * If the end node has been found, there is no need to continue
                     * the loops.
                     */
                    if (neighbour == end) {
                        isEndFound = true;
                        break;
                    }
                }

        }
        if (isEndFound) {
            break;
        }

    }
    // If the end has not been found, return an empty stack.
    if (!isEndFound) {
        return stack;
    }
    /* The neighbour is the end node, since we stopped the loop after it had
     * been found. While loop pushes the trail into a stack.
     */
    traceBack = neighbour;
    while (traceBack != start) {
        stack->push(traceBack);
        traceBack = traceBack->getPrev();
    }
    // Adding the start node to the trail.
    stack->push(traceBack);

    return stack;

}

BOOST_CLASS_EXPORT(Bfs)