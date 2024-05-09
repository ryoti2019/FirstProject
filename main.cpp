#include <DxLib.h>
#include <vector>
#include <array>
#include <cassert>
#include "ChipDrawer.h"
int GetNum()
{
	int num = GetRand(9) + 1;
	return num;
};

int Function(int number)
{
	DrawFormatString(10, 10, 0xffffff, L"num=%d", number);
	return number;
};

struct FMFHeader
{
	char id[4];
	uint32_t size;
	uint32_t mapWidth;
	uint32_t mapHeight;
	uint8_t chipWidth;
	uint8_t chipHeight;
	uint8_t layerCount;
	uint8_t bitCount;
};

namespace MyEngine
{
	int LoadGraph(const wchar_t* path)
	{
		auto handle = DxLib::LoadGraph(path);
		assert(handle != -1);
		return handle;
	}
	int DrawGraph(int x, int y, int handle, int psH, int normH, bool transFlag = false)
	{
		int w, h;
		GetGraphSize(handle, &w, &h);
		std::array<VERTEX2DSHADER, 4> vertices;
		std::array<uint16_t, 6> indices;
		for (auto& v : vertices)
		{
			v.dif = GetColorU8(255, 255, 255, 255);
			v.spc = GetColorU8(0, 0, 0, 0);
			v.rhw = 1.0f;
			v.su = 0.5f;
			v.sv = 0.5f;
		}
		// 4頂点の設定(Zの字になるように並べてください)
		// 左上
		vertices[0].pos = VGet(x, y, 1.0f);
		vertices[0].u = 0.0f;
		vertices[0].v = 0.0f;
		// 右上
		vertices[1].pos = VGet(x+w, y, 1.0f);
		vertices[1].u = 1.0f;
		vertices[1].v = 0.0f;
		// 左下
		vertices[2].pos = VGet(x, y+h, 1.0f);
		vertices[2].u = 0.0f;
		vertices[2].v = 1.0f;
		// 右下
		vertices[3].pos = VGet(x+w, y+h, 1.0f);
		vertices[3].u = 1.0f;
		vertices[3].v = 1.0f;

		SetUseTextureToShader(0, handle);
		SetUseTextureToShader(1, normH);
		SetUsePixelShader(psH);
		if (transFlag)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		indices = { 0,1,2,
					1,3,2 };
		int result = DrawPrimitiveIndexed2DToShader(
			vertices.data(), vertices.size(),
			indices.data(),indices.size(),
			DX_PRIMTYPE_TRIANGLELIST);

		return result;
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	FMFHeader header;
	std::vector<uint8_t> data;
	auto handle = FileRead_open(L"sample.fmf");
	FileRead_read(&header, sizeof(header), handle);
	data.resize(header.chipWidth * header.chipHeight);
	FileRead_read(data.data(), data.size() * sizeof(uint8_t), handle);

	FileRead_close(handle);

	int haikeiH = MyEngine::LoadGraph(L"img/haikei.png");

	int nervH = MyEngine::LoadGraph(L"img/nerv.png");

	int nervNH = MyEngine::LoadGraph(L"img/nerv_n.png");

	int distH = MyEngine::LoadGraph(L"img/Crack.png");

	int psH = LoadPixelShader(L"PixelShader.pso");
	assert(psH != -1);
	int distPsH = LoadPixelShader(L"DistortionPS.pso");
	assert(distPsH != -1);

	int waterH = MyEngine::LoadGraph(L"img/Water+.png");

	int RT = MakeScreen(640, 480);

	int hairetu[] = { 1,10,3,6,8,7,9,12,5 };

	ChipDrawer drawer;

	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() != -1)
	{
		SetDrawScreen(RT);// レンダーターゲットをRTに

		ClearDrawScreen();
		DrawRotaGraph(320, 240, 2.0, 0.0, haikeiH, true);
		//drawer.BeginDraw(waterH, psH, -1, 400, true);
		//for (int j = 0; j < 20; ++j)
		//{
		//	for (int i = 0; i < 20; ++i)
		//	{
		//		drawer.DrawRectRotaGraph(i * 32, j * 32, 96, 32, 16, 16,2.0f);
		//	}
		//}
		//drawer.EndDraw();

		DrawFormatString(0, 0, 0x000000, L"DrawCall = % d", GetDrawCallCount());
		MyEngine::DrawGraph(200, 100, nervH, psH, nervNH, true);

		SetDrawScreen(DX_SCREEN_BACK);
		MyEngine::DrawGraph(0, 0, RT, distPsH, distH, true);

		ScreenFlip();
	}
	DxLib_End();

}
