#pragma once
#include<vector>
#include<DxLib.h>
class ChipDrawer
{
private:
	std::vector< VERTEX2DSHADER> vertices_;
	std::vector<uint16_t> indices_;
	int handle_;
	int psH_;
	int additionalH_;
	int transFlag_;
public:
	void BeginDraw(int handle, int psH, int additionalH, size_t expectedNum = 0, bool transFlag = false);
	void DrawGraph(int x, int y);
	void DrawRectGraph(int x, int y, int srcX, int srcY, int srcW, int srcH);
	void DrawRectRotaGraph(int x, int y, int srcX, int srcY, int srcW, int srcH,float scale);
	void EndDraw();
};

