/*
*symbolGenerator.cpp
*/

#include <qpainter.h>
#include "symbolGenerator.h"



CSymbolGenerator::CSymbolGenerator(SymbolGeneratorParam* pParam)
{
	memcpy(&m_param, pParam, sizeof(SymbolGeneratorParam));
}


CSymbolGenerator::~CSymbolGenerator()
{

}

void CSymbolGenerator::InitSymbolGenerator(int* pSymbolGroups, int* pSymbolsPerGroup)
{
	InitGenerator(&m_param, pSymbolGroups, pSymbolsPerGroup);
}

BOOL CSymbolGenerator::NextSymbolGroup(QList<QImage* >symbolImgs)
{
	if (m_curSymbolVal > m_param.symbolEnd)
		return FALSE;

	UINT curSymbolVal = GetNextSymbolValue(m_curSymbolVal);

	GeneratorNextGroup(&m_param, curSymbolVal, symbolImgs);

	m_curSymbolVal = curSymbolVal;
	
	return TRUE;
}