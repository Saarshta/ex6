//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef JOB_H_
#define JOB_H_

class Job {
private:
	void *arg;
	void * (*func)(void *arg);
public:
	Job(void * (*func)(void *arg), void* arg);
	void execute();
	virtual ~Job();
};

#endif /* JOB_H_ */
