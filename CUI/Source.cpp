#include "Map2D.hpp"
#include <cstdio>
#include <cstdlib>

constexpr void crossKey(const int c_, double& x_, double& y_, const double v_) {
	switch (c_)
	{
	case 'w':
		y_ -= v_;
		break;
	case 's':
		y_ += v_;
		break;
	case 'a':
		x_ -= v_;
		break;
	case 'd':
		x_ += v_;
		break;
	}
}

void drawMap(const int32_t i_, const int32_t j_, const int32_t sx_, const int32_t sy_, const int32_t ex_, const int32_t ey_, const std::vector<std::vector<int>>& col_) {
	static thread_local int32_t i{ INT32_MIN };
	if (i_ != i) std::cout << std::endl;
	std::cout << ((col_[i_][j_] == 1) ? "¡" : " ");
	i = i_;
}

int main() {

	int ch{};
	double x = 0, y = 0;

	game::MapView mv(900, 600, x, y, 60);


	game::GameMap<int> col(51, 31, 1);
	game::MazeDig<int>(col.data);
	//col.mazeDig_Make(1, 0);

	mv.setMapArraySize(col.data);
	mv.setMapArrayCeil();

	mv.outputMapLoop(drawMap, col.data);
	while ((ch = std::getchar()) != EOF)
	{
		if (ch != 'w'&&ch != 's'&&ch != 'a'&&ch != 'd') continue;
		crossKey(ch, x, y, 1.0);
		mv.setMapView(x, y);
		std::cout << std::endl;
		mv.outputMapLoop(drawMap, col.data);
	}
	return 0;
}