/*
*chineseSymbolGenerator.h
* 中文字符生成类
*/
#include "symbolGenerator.h"
class CChineseSymbolGenerator : public CSymbolGenerator
{
public:
	CChineseSymbolGenerator(SymbolGeneratorParam* pParam);
	virtual ~CChineseSymbolGenerator();


protected:
	virtual void InitGenerator(SymbolGeneratorParam* pParam, int* pSymbolGroups, int* pSymbolsPerGroup);
	virtual UINT GetNextSymbolValue(UINT curSymbolVaule);
	virtual void GeneratorNextGroup(SymbolGeneratorParam* pParam, UINT symbolValu, QList<QImage* >symbolImgs);
};

