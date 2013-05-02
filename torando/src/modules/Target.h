/*
 * Target.h
 *
 *  Created on: 27/04/2013
 *      Author: yuriclaure
 */

#ifndef TARGET_H_
#define TARGET_H_

class Target {
	public:
		Target();
		virtual ~Target();

	protected:

		float x;
		float y;

		friend class Vision;

};

#endif /* TARGET_H_ */
