//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "Job.h"
/**
 * Constructor
 * @param func - the function we need to run
 * @param arg - the parameters of that function as a void*
 * @return
 */
Job::Job(void *(*func)(void *arg), void *arg): func(func), arg(arg) {
	// TODO Auto-generated constructor stub

}
/**
 * execute the function with its parameters.
 */
void Job::execute() {
	func(arg);
}
/**
 * default destructor.
 */
Job::~Job() {
	// TODO Auto-generated destructor stub
}

