#include "DxLib.h"
#include "Map2D.hpp"

constexpr int window_width{ 1920 };
constexpr int window_height{ 1080 };

namespace System {
	bool Update() { return (ScreenFlip() != -1 && ClearDrawScreen() != -1 && ProcessMessage() != -1); }
}

//void drawMap(const int32_t i_, const int32_t j_, const int32_t sx_, const int32_t sy_, const int32_t ex_, const int32_t ey_, const std::vector<std::vector<int>>& col_) {
//	DrawBox(sx_, sy_, ex_ + sx_, ey_ + sy_, ((col_[i_][j_] == 1) ? 0xbbbbbbbb : 0x00000000), 1);
//}

void drawMap(const int32_t i_, const int32_t j_, const int32_t sx_, const int32_t sy_, const int32_t ex_, const int32_t ey_, const std::vector<std::vector<int>>& col_) {
	int color;
	switch (col_[i_][j_])
	{
	case game::maze_dig_type_wall:
		color = 0xbbbbbbbb;
		break;
	case game::maze_dig_type_root:
		color = 0x66666666;
		break;
	default:
		color = 0x00000000;
		break;
	}
	DrawBox(sx_, sy_, ex_ + sx_, ey_ + sy_, color, 1);
}

void Main() {
	//プレイヤーの座標
	double x{ 0.0 }, y{ 0.0 };
	game::WalkDirectionType player{ game::walk_direction_type_empty };

	game::MapView mv(window_width, window_height, x, y, 40);
	game::GameMap<int> col(91, 31, game::maze_dig_type_wall);
	game::MazeDig<int>(col.data);
	mv.setMapArraySize(col.data);
	mv.setMapArrayCeil();

	while (System::Update())
	{
		clsDx();
		//プレイヤーの操作を取得し歩行方向を返す
		player = game::crossKey((CheckHitKey(KEY_INPUT_S) == 1), (CheckHitKey(KEY_INPUT_A) == 1), (CheckHitKey(KEY_INPUT_D) == 1), (CheckHitKey(KEY_INPUT_W) == 1));
		//歩行方向のあたり判定
		const auto&& cd{ game::collisionDetection(col.data, (size_t)(x), (size_t)(y), player) };
		//動かす
		game::movePlayer(x, y, 1, (cd != game::maze_dig_type_wall) ? player : game::walk_direction_type_empty);

		//プレイヤーの座標を視点にする
		mv.setMapViewHalf(x, y);
		//マップを描画
		mv.outputMap(drawMap, col.data);
		//プレイヤー位置を補正
		mv.limitMapArrayCenter();

		DrawCircle(window_width / 2, window_height / 2, (int)mv.getMapArrayPixelWidth()/2, 0xffffffff, 1);


		printfDx("%d %d (%f,%f) %d\n", col.data.size(), col.data.front().size(), mv.getMapArrayCenterX(), mv.getMapArrayCenterY(),cd);

		printfDx("-Map-\n");
		printfDx("StartX:%f\n", mv.getMapArrayStartX());
		printfDx("StartY:%f\n", mv.getMapArrayStartY());
		printfDx("CeilStartX:%d\n", mv.getMapArrayCeilStartX());
		printfDx("CeilStartY:%d\n", mv.getMapArrayCeilStartY());
		printfDx("EndX:%f\n", mv.getMapArrayEndX());
		printfDx("EndY:%f\n", mv.getMapArrayEndY());
		printfDx("CeilEndX:%d\n", mv.getMapArrayCeilEndX());
		printfDx("CeilEndY:%d\n", mv.getMapArrayCeilEndY());

		printfDx("CenterX:%f\n", mv.getMapArrayCenterX());
		printfDx("CenterY:%f\n", mv.getMapArrayCenterY());

		printfDx("Height:%d\n", mv.getMapArrayHeight());
		printfDx("Width:%d\n", mv.getMapArrayWidth());
		printfDx("PixelHeight:%f\n", mv.getMapArrayPixelHeight());
		printfDx("PixelWidth:%f\n", mv.getMapArrayPixelWidth());


		printfDx("WindowHeight:%f\n", mv.getMapArrayWindowHeight());
		printfDx("WindowWidth:%f\n", mv.getMapArrayWindowWidth());

		printfDx("\n-Window-\n");
		printfDx("CenterX:%d\n", mv.getWindowCenterX());
		printfDx("CenterY:%d\n", mv.getWindowCenterY());
		printfDx("EndX:%d\n", mv.getWindowEndX());
		printfDx("EndY:%d\n", mv.getWindowEndY());
		printfDx("Width:%d\n", mv.getWindowWidth());
		printfDx("Height:%d\n", mv.getWindowHeight());
		printfDx("StartX:%d\n", mv.getWindowStartX());
		printfDx("StartY:%d\n", mv.getWindowStartY());

		printfDx("\n-Size-\n");
		printfDx("CenterX:%d\n", window_width);
		printfDx("CenterY:%d\n", window_height);

	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(window_width, window_height, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	Main();

	return DxLib_End();
}

//for (size_t i = 0; i < col.data.size(); ++i)
//	for (size_t j = 0; j < col.data[i].size(); ++j) {
//		col.data[i][j].r = game::gameRand(50, 206);
//		col.data[i][j].g = game::gameRand(50, 206);
//		col.data[i][j].b = game::gameRand(50, 206);
//	}

//struct rgb {
//	int32_t r;
//	int32_t g;
//	int32_t b;
//};

//void draww(const int32_t i_, const int32_t j_, const int32_t sx_, const int32_t sy_, const int32_t ex_, const int32_t ey_, const std::vector<std::vector<rgb>>& col_,const int& is_) {
//	//DrawBox(sx_, sy_, ex_ + sx_, ey_ + sy_, GetColor(col_[j_][i_].r, col_[j_][i_].g, col_[j_][i_].b), is_);
//	DrawBox(sx_, sy_, ex_ + sx_, ey_ + sy_, GetColor(col_[j_][i_].r, col_[j_][i_].g, col_[j_][i_].b), is_);
//}




