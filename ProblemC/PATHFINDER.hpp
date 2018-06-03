#ifndef PATHFINDER_HPP_
#define PATHFINDER_HPP_


int FindPath(const int nStartX, const int nStartY,
		const int nTargetX, const int nTargetY, const unsigned char* pMap,
		const int nMapWidth, const int nMapHeight, int* pOutBuffer,
		const int nOutBufferSize);

		


#endif /* PATHFINDER_HPP_ */
