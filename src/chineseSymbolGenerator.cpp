
#include <qpainter.h>
#include <qfont.h>
#include <qtextcodec.h>
#include "chineseSymbolGenerator.h"

#define CHINESE_SYMBOL_SIZE_UNIT_DFT		2
#define CHINESE_SYMBOL_ROTATE_UNIT_DFT		2
#define	CHINESE_SYMBOL_ROTATE_MIN			-5
#define	CHINESE_SYMBOL_ROTATE_MAX			5
#define	CHINESE_SYMBOL_SIZE_MIN				12
#define	CHINESE_SYMBOL_SIZE_MAX				16
#define	CHINESE_SYMBOL_GBK_START			0x8140
#define	CHINESE_SYMBOL_GBK_END				0xFEFE

CChineseSymbolGenerator::CChineseSymbolGenerator(SymbolGeneratorParam* pParam):CSymbolGenerator(pParam)
{
}


CChineseSymbolGenerator::~CChineseSymbolGenerator()
{
}

void CChineseSymbolGenerator::InitGenerator(SymbolGeneratorParam* pParam, int* pSymbolGroups, int* pSymbolsPerGroup)
{
	if (pParam->rotateMin >= pParam->rotateMax)
	{
		pParam->rotateMin = CHINESE_SYMBOL_ROTATE_MIN;
		pParam->rotateMax = CHINESE_SYMBOL_ROTATE_MAX;
	}

	if (pParam->symbolStart >= pParam->symbolEnd)
	{
		pParam->symbolStart = CHINESE_SYMBOL_GBK_START;
		pParam->symbolEnd = CHINESE_SYMBOL_GBK_END;
	}

	if (pParam->symbolSizeMin >= pParam->symbolSizeMax)
	{
		pParam->symbolSizeMin = CHINESE_SYMBOL_SIZE_MIN;
		pParam->symbolSizeMax = CHINESE_SYMBOL_SIZE_MAX;
	}

	if (pParam->sizeUnit <= 0)
		pParam->sizeUnit = CHINESE_SYMBOL_SIZE_UNIT_DFT;


	if (pParam->rotateUnit <= 0)
		pParam->rotateUnit = CHINESE_SYMBOL_ROTATE_UNIT_DFT;

	UINT highHalfStart = (pParam->symbolStart & 0xff00) >> 8;
	UINT highHalfEnd = (pParam->symbolEnd & 0xff00) >> 8;
	UINT lowHalfStart = pParam->symbolStart & 0xff;
	UINT lowHalfEnd = pParam->symbolEnd & 0xff;

	if (highHalfEnd < highHalfEnd)
	{
		pParam->symbolStart = CHINESE_SYMBOL_GBK_START;
		pParam->symbolEnd = CHINESE_SYMBOL_GBK_END;
		highHalfStart = (pParam->symbolStart & 0xff00) >> 8;
		highHalfEnd = (pParam->symbolEnd & 0xff00) >> 8;
		lowHalfStart = pParam->symbolStart & 0xff;
		lowHalfEnd = pParam->symbolEnd & 0xff;
	}

	if (lowHalfStart == 0xff)
	{
		lowHalfStart = 0xfe;
	}

	if (lowHalfEnd == 0xff)
	{
		lowHalfEnd = 0xfe;
	}

	int highHalfDomain = (highHalfEnd - highHalfStart + 1);
	int lowHalfSymbolsPerDomain = (0xff - 0x40 - 1);		// È¥³ýxx7f

	int firstLowHalfSymbols = (0xff - lowHalfStart + 1);
	if (firstLowHalfSymbols <= 0x7f)
		firstLowHalfSymbols -= 1;    // È¥³ýxx7f

	int lastLowHalfSymbols = lowHalfEnd - 0x40+1;
	if (lastLowHalfSymbols >= 0x7f)
		lastLowHalfSymbols -= 1;
	
	if (highHalfDomain == 1)
		pSymbolGroups[0] = lastLowHalfSymbols;
	else
		pSymbolGroups[0] = lastLowHalfSymbols + firstLowHalfSymbols + (highHalfDomain - 2)*lowHalfSymbolsPerDomain;

	int rotateTimes = (pParam->rotateMax - pParam->rotateMin) / pParam->rotateUnit;
	int sizeTimes = (pParam->symbolSizeMax - pParam->symbolSizeMin) / pParam->sizeUnit;
	pSymbolsPerGroup[0] = rotateTimes*sizeTimes* (pParam->hasBold ? 2 : 1);
}

UINT CChineseSymbolGenerator::GetNextSymbolValue(UINT curSymbolVaule)
{
	UINT lowHalfGBK = curSymbolVaule & 0xff;
	UINT highHalfGBK = (curSymbolVaule & 0xff00) >> 8;
	lowHalfGBK++;
	if (lowHalfGBK == 0x7f)
		lowHalfGBK++;
	else if (lowHalfGBK == 0xff)
	{
		lowHalfGBK = 0x40;
		highHalfGBK++;
	}

	return ((highHalfGBK << 8) | lowHalfGBK);
}

void CChineseSymbolGenerator::GeneratorNextGroup(SymbolGeneratorParam* pParam, UINT symbolValu, QList<QImage* >symbolImgs)
{
	int imgIdx = 0;
	for (int fontSize = pParam->symbolSizeMin; fontSize <= pParam->symbolSizeMax; fontSize += pParam->sizeUnit)
	{
		for (int rotate = pParam->rotateMin; rotate <= pParam->rotateMax; rotate += pParam->rotateUnit)
		{
			if (imgIdx < symbolImgs.size())
			{
				QImage* pImage = symbolImgs[imgIdx++];

			}
			
		}
	}
}
