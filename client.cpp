//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "src/Tcp.h"
#include <unistd.h>
#include "src/DriverOperator.h"

using namespace std;

int main(int argc, char *argv[]) {

    // Reading port.
    Socket* tcp = new Tcp(0, atoi(argv[2]));
    tcp->initialize();
    // Initializing driverOperator.
    DriverOperator driverOperator(tcp);
    // Initializing driver.
    if (driverOperator.initializeDriver()) { ; // wait for input
        // Sending the serialized driver.
        driverOperator.sendDriver();
        // Receiving a cab.
        driverOperator.receiveCab();


        while (true) {
            // Receiving input from server.
            driverOperator.receivingData();
            // Check if it's 7, if it is, break.
            if (driverOperator.isDataEnd()) {
                break;
            }
            driverOperator.updateLocation();
        }
    }
    return 0;
}