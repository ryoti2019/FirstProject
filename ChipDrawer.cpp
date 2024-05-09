#include "ChipDrawer.h"

void ChipDrawer::BeginDraw(int handle, int psH, int additionalH, size_t expectedNum, bool transFlag)
{
	handle_ = handle;
	psH_ = psH;
	additionalH_ = additionalH;
	transFlag_ = transFlag;
	vertices_.clear();
	vertices_.reserve(expectedNum * 4);
	indices_.clear();
	indices_.reserve(expectedNum * 6);
}

void ChipDrawer::DrawGraph(int x, int y)
{
	int w, h;
	GetGraphSize(handle_, &w, &h);
	int startVertex = vertices_.size();
	int startIndices = indices_.size();

	vertices_.resize(vertices_.size() + 4);
	indices_.resize(indices_.size() + 6);

	for (int i = startVertex; i < vertices_.size(); ++i)
	{
		auto& v = vertices_[i];
		v.dif = GetColorU8(255, 255, 255, 255);
		v.spc = GetColorU8(0, 0, 0, 0);
		v.rhw = 1.0f;
		v.su = 0.5f;
		v.sv = 0.5f;
	}
	// 4頂点の設定(Zの字になるように並べてください)
	// 左上
	vertices_[startVertex+0].pos = VGet(x, y, 1.0f);
	vertices_[startVertex+0].u = 0.0f;
	vertices_[startVertex+0].v = 0.0f;
	// 右上
	vertices_[startVertex + 1].pos = VGet(x + w, y, 1.0f);
	vertices_[startVertex + 1].u = 1.0f;
	vertices_[startVertex + 1].v = 0.0f;
	// 左下
	vertices_[startVertex + 2].pos = VGet(x, y + h, 1.0f);
	vertices_[startVertex + 2].u = 0.0f;
	vertices_[startVertex + 2].v = 1.0f;
	// 右下
	vertices_[startVertex + 3].pos = VGet(x + w, y + h, 1.0f);
	vertices_[startVertex + 3].u = 1.0f;
	vertices_[startVertex + 3].v = 1.0f;

	//0,1,2 1,3,2
	indices_[startIndices + 0] = startVertex + 0;
	indices_[startIndices + 1] = startVertex + 1;
	indices_[startIndices + 2] = startVertex + 2;
	indices_[startIndices + 3] = startVertex + 1;
	indices_[startIndices + 4] = startVertex + 3;
	indices_[startIndices + 5] = startVertex + 2;

}

void ChipDrawer::DrawRectGraph(int x, int y, int srcX, int srcY, int srcW, int srcH)
{
	int w, h;
	GetGraphSize(handle_, &w, &h);
	float startU = static_cast<float>(srcX) / static_cast<float>(w);
	float startV = static_cast<float>(srcY) / static_cast<float>(h);
	float uWid = static_cast<float>(srcW) / static_cast<float>(w);
	float vHgt = static_cast<float>(srcH) / static_cast<float>(h);

	int startVertex = vertices_.size();
	int startIndices = indices_.size();

	vertices_.resize(vertices_.size() + 4);
	indices_.resize(indices_.size() + 6);

	for (int i = startVertex; i < vertices_.size(); ++i)
	{
		auto& v = vertices_[i];
		v.dif = GetColorU8(255, 255, 255, 255);
		v.spc = GetColorU8(0, 0, 0, 0);
		v.rhw = 1.0f;
		v.su = 0.5f;
		v.sv = 0.5f;
	}
	// 4頂点の設定(Zの字になるように並べてください)
	// 左上
	vertices_[startVertex + 0].pos = VGet(x, y, 1.0f);
	vertices_[startVertex + 0].u = startU;
	vertices_[startVertex + 0].v = startV;
	// 右上
	vertices_[startVertex + 1].pos = VGet(x + srcW, y, 1.0f);
	vertices_[startVertex + 1].u = startU + uWid;
	vertices_[startVertex + 1].v = startV;
	// 左下
	vertices_[startVertex + 2].pos = VGet(x, y + srcH, 1.0f);
	vertices_[startVertex + 2].u = startU;
	vertices_[startVertex + 2].v = startV + vHgt;
	// 右下
	vertices_[startVertex + 3].pos = VGet(x + srcW, y + srcH, 1.0f);
	vertices_[startVertex + 3].u = startU + uWid;
	vertices_[startVertex + 3].v = startV + vHgt;

	//0,1,2 1,3,2
	indices_[startIndices + 0] = startVertex + 0;
	indices_[startIndices + 1] = startVertex + 1;
	indices_[startIndices + 2] = startVertex + 2;
	indices_[startIndices + 3] = startVertex + 1;
	indices_[startIndices + 4] = startVertex + 3;
	indices_[startIndices + 5] = startVertex + 2;

}

void ChipDrawer::DrawRectRotaGraph(int x, int y, int srcX, int srcY, int srcW, int srcH, float scale)
{
	int w, h;
	GetGraphSize(handle_, &w, &h);
	float startU = static_cast<float>(srcX) / static_cast<float>(w);
	float startV = static_cast<float>(srcY) / static_cast<float>(h);
	float uWid = static_cast<float>(srcW) / static_cast<float>(w);
	float vHgt = static_cast<float>(srcH) / static_cast<float>(h);

	int startVertex = vertices_.size();
	int startIndices = indices_.size();

	vertices_.resize(vertices_.size() + 4);
	indices_.resize(indices_.size() + 6);

	for (int i = startVertex; i < vertices_.size(); ++i)
	{
		auto& v = vertices_[i];
		v.dif = GetColorU8(255, 255, 255, 255);
		v.spc = GetColorU8(0, 0, 0, 0);
		v.rhw = 1.0f;
		v.su = 0.5f;
		v.sv = 0.5f;
	}
	// 4頂点の設定(Zの字になるように並べてください)
	// 左上
	vertices_[startVertex + 0].pos = VGet(x, y, 1.0f);
	vertices_[startVertex + 0].u = startU;
	vertices_[startVertex + 0].v = startV;
	// 右上
	vertices_[startVertex + 1].pos = VGet(x + srcW * scale, y, 1.0f);
	vertices_[startVertex + 1].u = startU + uWid;
	vertices_[startVertex + 1].v = startV;
	// 左下
	vertices_[startVertex + 2].pos = VGet(x, y + srcH * scale, 1.0f);
	vertices_[startVertex + 2].u = startU;
	vertices_[startVertex + 2].v = startV + vHgt;
	// 右下
	vertices_[startVertex + 3].pos = VGet(x + srcW * scale, y + srcH * scale, 1.0f);
	vertices_[startVertex + 3].u = startU + uWid;
	vertices_[startVertex + 3].v = startV + vHgt;

	//0,1,2 1,3,2
	indices_[startIndices + 0] = startVertex + 0;
	indices_[startIndices + 1] = startVertex + 1;
	indices_[startIndices + 2] = startVertex + 2;
	indices_[startIndices + 3] = startVertex + 1;
	indices_[startIndices + 4] = startVertex + 3;
	indices_[startIndices + 5] = startVertex + 2;
}

void ChipDrawer::EndDraw()
{
	SetUseTextureToShader(0, handle_);
	SetUseTextureToShader(1, additionalH_);
	SetUsePixelShader(psH_);
	if (transFlag_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	DrawPrimitiveIndexed2DToShader(
		vertices_.data(), vertices_.size(),
		indices_.data(), indices_.size(),
		DX_PRIMTYPE_TRIANGLELIST);
}
