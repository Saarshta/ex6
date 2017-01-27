//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "MapRestartListener.h"

/**
 * restartMap - restarts the listener's map's node's distances to -1.
 */
void MapRestartListener::restartMap() {
    this->map->restartDistances();
}

/**
 * Constructor of the MapRestartListener.
 * @param map the map whose node's distances are to be restarted.
 * @return nothing.
 */
MapRestartListener::MapRestartListener(Map *map) : map(map) {}

