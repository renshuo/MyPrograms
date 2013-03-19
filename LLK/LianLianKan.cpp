#include "stdio.h"

#include "LianLianKan_h.h"

ULONG g_ulMatric0[MAX_ROW_LENGTH][MAX_COL_LENGTH] =
{2,9,0,4,4,3,3,4,9,6,
 1,0,0,0,0,2,3,4,5,6,
 2,1,1,3,1,2,3,4,5,6,
 2,0,0,0,0,0,4,4,5,6,
 2,0,0,5,0,1,4,4,5,6,
 2,0,0,0,0,0,3,4,5,6,
 2,0,0,0,0,0,3,4,5,9,
 2,0,0,0,0,2,3,4,9,6,
};

ULONG g_ulMatric[MAX_ROW_LENGTH_AFTER][MAX_COL_LENGTH_AFTER];

StPoint g_stPointPos = {0, 8};

StPoint g_stAimPointList[MAX_ROW_LENGTH * MAX_COL_LENGTH];

void LLK_InitPointList(StPoint stPointList[]);
ULONG LLK_FindAllAimPointPos(StPoint stPointList[]);
ULONG LLK_TraverseTurnPoint(StPoint stStartPoint, StPoint *pstEndPoint);
ULONG LLK_JudgeBeConnected(StPoint stPoint1, StPoint StPoint2);
void LLK_StandardizeMatrix(ULONG aulMatrix[MAX_ROW_LENGTH][MAX_COL_LENGTH], ULONG aulStandardMatrix[MAX_ROW_LENGTH_AFTER][MAX_COL_LENGTH_AFTER]);

ULONG main()
{   
	ULONG ulRet;

	StPoint stEndPoint;

#if DEBUGLLk
	printf("{%d,%d} = %d\n", g_stPointPos.x, g_stPointPos.y, g_ulMatric0[g_stPointPos.x][g_stPointPos.y]);
#endif


	if ((g_stPointPos.x >= MAX_ROW_LENGTH) || (g_stPointPos.y >= MAX_COL_LENGTH))
	{   
		printf("The start point's position isn't correct!");
		return ERR;
	}

	if (0 == g_ulMatric0[g_stPointPos.x][g_stPointPos.y])
	{
		printf("The start point's value is 0!");
		return ERR;
	}

    LLK_StandardizeMatrix(g_ulMatric0, g_ulMatric);

	LLK_InitPointList(g_stAimPointList);

	ulRet = LLK_FindAllAimPointPos(g_stAimPointList);
	if (OK != ulRet)
	{
		printf("We can't find the aim point!");
		return ERR;
	}	

	ulRet = LLK_TraverseTurnPoint(g_stPointPos, &stEndPoint);
	if (OK == ulRet)
	{
		printf("\n-----------------The aim point is (%d, %d);-----------------------\n", stEndPoint.x, stEndPoint.y);
		printf("\n------------------------------------------------------------------\n");

		return OK;
	}
	else
	{
		printf("We can't find the aim point!");
		return ERR;
	}

	return OK;
}

//initial the aim point list
void LLK_InitPointList(StPoint stPointList[])
{
	char i;

	for (i = 0; i < MAX_ROW_LENGTH * MAX_COL_LENGTH; i++)
	{
		stPointList[i].x = MAX_ROW_LENGTH_AFTER;
		stPointList[i].y = MAX_COL_LENGTH_AFTER;
	}

	return;	
}

//find all the points position whose value equal 0
ULONG LLK_FindAllAimPointPos(StPoint stPointList[])
{
	ULONG cInitVal;
	ULONG i,j, cIndex = 0;

	cInitVal = g_ulMatric[g_stPointPos.x][g_stPointPos.y];

	for (i = 0; i < MAX_ROW_LENGTH_AFTER; i++)
	{
		for (j = 0; j < MAX_COL_LENGTH_AFTER; j++)
		{
			if (cInitVal == g_ulMatric[i][j]) 
			{
				if ((i == g_stPointPos.x) && (j == g_stPointPos.y))
				{
				}
				else
				{
					g_stAimPointList[cIndex].x = i;
					g_stAimPointList[cIndex].y = j;
					cIndex++;
#if DEBUGLLk
					printf("(%d,%d)\t",i,j);
#endif
				}

				
			}
		}
	}

	if ( 0 != cIndex)
	{
#if DEBUGLLk
		printf("\n");
#endif
		return OK;
	}

	return ERR;
}

//traverse to find the turn point from four directions, then find the aim point
ULONG LLK_TraverseTurnPoint(StPoint stStartPoint, StPoint *pstEndPoint)
{
	ULONG i,j;
	char cIndex = 0;
	StPoint stAimPoint, stPoint1, stPoint2;
	ULONG ulInitVal;

	ulInitVal = g_ulMatric[stStartPoint.x][stStartPoint.y];

	while (g_stAimPointList[cIndex].x != MAX_ROW_LENGTH_AFTER)
	{
		stAimPoint.x = g_stAimPointList[cIndex].x;
		stAimPoint.y = g_stAimPointList[cIndex].y;

#if DEBUGLLk
		printf("suppose the aim point's position is (%d,%d)\n", stAimPoint.x, stAimPoint.y);
#endif

		for (i = 0; i < MAX_COL_LENGTH_AFTER; i++)
		{
			if (((0 == g_ulMatric[stStartPoint.x][i]) || (ulInitVal == g_ulMatric[stStartPoint.x][i]))
				&& ((0 == g_ulMatric[stAimPoint.x][i]) || (ulInitVal== g_ulMatric[stAimPoint.x][i]))
				&& (i != g_stPointPos.y))
			{
				stPoint1.x = stStartPoint.x;
				stPoint1.y = i;

				stPoint2.x = stAimPoint.x;
				stPoint2.y = i;

#if DEBUGLLk
				printf("scan the same row!\n");
				printf("suppose the first point's position is (%d,%d)\n", stPoint1.x, stPoint1.y);
				printf("suppose the second point's position is (%d,%d)\n", stPoint2.x, stPoint2.y);
#endif

				if ((OK == LLK_JudgeBeConnected(stStartPoint, stPoint1)) 
					&& (OK == LLK_JudgeBeConnected(stPoint1, stPoint2)) 
					&& (OK == LLK_JudgeBeConnected(stPoint2, stAimPoint)))
				{
					pstEndPoint->x = stAimPoint.x - 1;
					pstEndPoint->y = stAimPoint.y - 1;
#if DEBUGLLk
		printf("Actually the aim point's position is (%d,%d)\n", stAimPoint.x, stAimPoint.y);
#endif					
					return OK;
				}
			}
		}

		for (j = 0; j < MAX_ROW_LENGTH; j++)
		{
			if (((0  == g_ulMatric[j][stStartPoint.y]) || (ulInitVal == g_ulMatric[j][stStartPoint.y]))
				&& ((0 == g_ulMatric[j][stAimPoint.y]) || (ulInitVal == g_ulMatric[j][stAimPoint.y]))
				&& (j != g_stPointPos.x))
			{
				stPoint1.x = j;
				stPoint1.y = stStartPoint.y;

				stPoint2.x = j;
				stPoint2.y = stAimPoint.y;
#if DEBUGLLk
				printf("scan the same col!\n");
				printf("suppose the first point's position is (%d,%d)\n", stPoint1.x, stPoint1.y);
				printf("suppose the second point's position is (%d,%d)\n", stPoint2.x, stPoint2.y);
#endif

				if ((OK == LLK_JudgeBeConnected(stStartPoint, stPoint1)) 
					&& (OK == LLK_JudgeBeConnected(stPoint1, stPoint2)) 
					&& (OK == LLK_JudgeBeConnected(stPoint2, stAimPoint)))
				{
					pstEndPoint->x = stAimPoint.x - 1;
					pstEndPoint->y = stAimPoint.y - 1;
#if DEBUGLLk
					printf("Actually the aim point's position is (%d,%d)\n", stAimPoint.x, stAimPoint.y);
#endif	
					return OK;
				}
			}
		}

		cIndex++;
	}

	return ERR;
}

//judge if the two points is connected
ULONG LLK_JudgeBeConnected(StPoint stPoint1, StPoint stPoint2)
{
	ULONG i;
    ULONG cStart, cEnd;

	if (stPoint1.x == stPoint2.x)
	{
		if (stPoint1.y < stPoint2.y)
		{
			cStart = stPoint1.y;
			cEnd   = stPoint2.y;
		}
		else
		{
			cStart = stPoint2.y;
			cEnd   = stPoint1.y;
		}

		for (i = (cStart + 1); i < cEnd; i++)
		{
			if (0 != g_ulMatric[stPoint1.x][i])
			{
				return ERR;
			}
		}
	}
	else
	{
		if (stPoint1.x < stPoint2.x)
		{
			cStart = stPoint1.x;
			cEnd   = stPoint2.x;
		}
		else
		{
			cStart = stPoint2.x;
			cEnd   = stPoint1.x;
		}

		for (i = (cStart + 1); i < cEnd; i++)
		{
			if (0 != g_ulMatric[i][stPoint1.y])
			{
				return ERR;
			}
		}
	}

	return OK;
}

void  LLK_StandardizeMatrix(ULONG aulMatrix[MAX_ROW_LENGTH][MAX_COL_LENGTH], ULONG aulStandardMatrix[MAX_ROW_LENGTH_AFTER][MAX_COL_LENGTH_AFTER])
{
	char i,j;
	char cIndex = 0;

	for (i = 0; i < MAX_ROW_LENGTH_AFTER; i++)
	{
		for (j = 0; j < MAX_COL_LENGTH_AFTER; j++)
		{
			if ((0 == i) || (i == (MAX_ROW_LENGTH_AFTER - 1)) || (0 == j) || (j == (MAX_COL_LENGTH_AFTER - 1)))
			{
				aulStandardMatrix[i][j] = 0;
				cIndex++;
			}
			else
			{
				aulStandardMatrix[i][j] = aulMatrix[i - 1][j - 1];
				cIndex++;
			}

	#if DEBUGLLk
			printf("%3d", aulStandardMatrix[i][j]);
			if (0 == cIndex % MAX_COL_LENGTH_AFTER)
			{
				printf("\n");
			}
	#endif
		}
	}

	g_stPointPos.x += 1;
	g_stPointPos.y += 1;

	return;
}
