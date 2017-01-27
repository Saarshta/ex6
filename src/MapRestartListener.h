//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX3_MAPRESTARTLISTENER_H
#define EX3_MAPRESTARTLISTENER_H


#include "Map.h"

/**
 * MapRestartListener - responsible of restarting a map's distances to -1.
 */
class MapRestartListener {
private:
    Map* map;

public:
    void restartMap();

    MapRestartListener(Map *map);


};



#endif //EX3_MAPRESTARTLISTENER_H
