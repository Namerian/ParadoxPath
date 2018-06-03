/*
 * Pathfinder.h
 *
 *  Created on: Mar 19, 2017
 *      Author: patrick
 */

#ifndef PATHFINDER_PATHFINDER_H_
#define PATHFINDER_PATHFINDER_H_


int FindPath(const int nStartX, const int nStartY,
		const int nTargetX, const int nTargetY, const unsigned char* pMap,
		const int nMapWidth, const int nMapHeight, int* pOutBuffer,
		const int nOutBufferSize);


#endif /* PATHFINDER_PATHFINDER_H_ */
