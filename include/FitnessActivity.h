/*
 * FitnessActivity.h
 *
 *  Created on: 16 mar 2024
 *      Author: root
 */

#ifndef SRC_MODEL_FITNESSACTIVITY_H_
#define SRC_MODEL_FITNESSACTIVITY_H_
#include <list>
#include "ISubject.h"

class FitnessActivity : public ISubject{
public:
	FitnessActivity();
	virtual ~FitnessActivity();
	void notify() override;
	void attach(IObserver *observer) override;
	void detach(IObserver *observer) override;
private:
	std::list<IObserver *> list_observer;
};

#endif /* SRC_MODEL_FITNESSACTIVITY_H_ */
