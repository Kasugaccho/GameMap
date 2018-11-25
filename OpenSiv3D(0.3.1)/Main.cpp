#include "Map2D.hpp"
#include <Siv3D.hpp> // OpenSiv3D v0.3.1

void crossKey(float& x_, float& y_, const float v_) {
	if (KeyW.pressed()) y_ -= v_;
	if (KeyS.pressed()) y_ += v_;
	if (KeyA.pressed()) x_ -= v_;
	if (KeyD.pressed()) x_ += v_;
}

void drawMap(const int32_t i_, const int32_t j_, const int32_t sx_, const int32_t sy_, const int32_t ex_, const int32_t ey_, const std::vector<std::vector<int>>& col_) {
	Rect(sx_, sy_, ex_, ey_).draw((col_[i_][j_] == 1) ? Color(200, 200, 200) : Color(0, 0, 0));
}

constexpr int32_t window_width{ 1920 };
constexpr int32_t window_height{ 1080 };

void Main()
{
	Window::Resize(window_width, window_height);

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
		//プレイヤーの操作を取得し歩行方向を返す
		player = game::crossKey((KeyS.pressed()), (KeyA.pressed()), (KeyD.pressed()), (KeyW.pressed()));
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
	}
}

//float x = 11, y = 10;

//game::MapView mv(900, 600, x, y, 20);
//mv.setMapArraySize(51, 31);
//mv.setMapArrayCeil();

//game::GameMap<int> col(51, 31, 1);
//col.mazeDig_Make(1, 0);

//while (System::Update())
//{
//	crossKey(x, y, 0.3f);
//	mv.setMapView(x, y);
//	mv.outputMapLoop(drawMap, col.data);
//}


/*
# include <Siv3D.hpp> // OpenSiv3D v0.3.1

void Main()
{
	Graphics::SetBackground(ColorF(0.8, 0.9, 1.0));

	const Font font(60);

	const Texture textureCat(Emoji(U"🐈"), TextureDesc::Mipped);

	while (System::Update())
	{
		font(U"Hello, Siv3D!🐣").drawAt(Window::Center(), Palette::Black);

		font(Cursor::Pos()).draw(20, 500, ColorF(0.6));

		textureCat.resized(80).draw(700, 500);

		Circle(Cursor::Pos(), 60).draw(ColorF(1, 0, 0, 0.5));
	}
}
*/