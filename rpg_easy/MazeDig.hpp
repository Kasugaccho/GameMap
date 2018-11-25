//----------------------------------------
// Ascll Project Game Map Library
//----------------------------------------
#ifndef ASCLL_PROJECT_GAME_MAP_LIBRARY_MAZE_DIG
#define ASCLL_PROJECT_GAME_MAP_LIBRARY_MAZE_DIG

namespace game {

	enum MazeDigType {
		maze_dig_type_empty,
		maze_dig_type_wall,
		maze_dig_type_root,
	};

	template<typename int_map_t>
	class MazeDig {
	private:
		using vArray = std::vector<std::vector<int_map_t>>;
		constexpr bool mazeDig_Check(const std::vector<std::vector<int_map_t>>& data) const;
		constexpr void mazeDig_Dig(std::vector<std::vector<int_map_t>>& data, size_t x_, size_t y_, const int_map_t id_wall_, const int_map_t id_empty_);
		constexpr int_map_t mazeDig_MakeLoop(const std::vector<std::vector<int_map_t>>& data, const int_map_t id_wall_, const int_map_t id_empty_, std::unique_ptr<int_map_t[]>& select_x, std::unique_ptr<int_map_t[]>& select_y);
		constexpr void mazeDig_Make(std::vector<std::vector<int_map_t>>& data, const int_map_t, const int_map_t);
		constexpr void mazeDig_RootLoop(std::vector<std::vector<int_map_t>>& data, const size_t x_, const size_t y_, const int_map_t, const int_map_t);
		constexpr void mazeDig_Root(std::vector<std::vector<int_map_t>>& data, const int_map_t, const int_map_t);

	public:
		MazeDig() = default;
		constexpr MazeDig(std::vector<std::vector<int_map_t>>& data, const int_map_t v1_, const int_map_t v2_) {
			mazeDig_Make(data, v1_, v2_);
		}
		constexpr MazeDig(std::vector<std::vector<int_map_t>>& data, const int_map_t v1_) {
			mazeDig_Make(data, v1_, (int_map_t)maze_dig_type_empty);
		}
		constexpr MazeDig(std::vector<std::vector<int_map_t>>& data) {
			mazeDig_Make(data, (int_map_t)maze_dig_type_wall, (int_map_t)maze_dig_type_empty);
		}
		constexpr void operator()(std::vector<std::vector<int_map_t>>& data, const int_map_t v1_, const int_map_t v2_) {
			mazeDig_Make(data, v1_, v2_);
		}
		constexpr void operator()(std::vector<std::vector<int_map_t>>& data, const int_map_t v1_) {
			mazeDig_Make(data, v1_, (int_map_t)maze_dig_type_empty);
		}
		constexpr void operator()(std::vector<std::vector<int_map_t>>& data) {
			mazeDig_Make(data, (int_map_t)maze_dig_type_wall, (int_map_t)maze_dig_type_empty);
		}
		constexpr void make(std::vector<std::vector<int_map_t>>& data, const int_map_t v1_, const int_map_t v2_) {
			mazeDig_Make(data, v1_, v2_);
		}
		constexpr void make(std::vector<std::vector<int_map_t>>& data, const int_map_t v1_) {
			mazeDig_Make(data, v1_, (int_map_t)maze_dig_type_empty);
		}
		constexpr void make(std::vector<std::vector<int_map_t>>& data) {
			mazeDig_Make(data, (int_map_t)maze_dig_type_wall, (int_map_t)maze_dig_type_empty);
		}
		constexpr void root(std::vector<std::vector<int_map_t>>& data, const int_map_t v1_, const int_map_t v2_) {
			mazeDig_Root(data, v1_, v2_);
		}
		constexpr void root(std::vector<std::vector<int_map_t>>& data, const int_map_t v1_) {
			mazeDig_Root(data, v1_, (int_map_t)maze_dig_type_empty);
		}
		constexpr void root(std::vector<std::vector<int_map_t>>& data) {
			mazeDig_Root(data, (int_map_t)maze_dig_type_root, (int_map_t)maze_dig_type_empty);
		}
	};


	//ñ¿òHån----------

		//åäå@ÇËñ@ÇÃñ¿òHÇê∂ê¨Ç∑ÇÈ
	template<typename int_map_t>
	inline constexpr void MazeDig<int_map_t>::mazeDig_Make(std::vector<std::vector<int_map_t>>& data, const int_map_t id_wall_, const int_map_t id_empty_)
	{
		if (data.size() <= 2 || data.data()->size() <= 2) return;
		if ((data.size() & 1) == 0 || (data.data()->size() & 1) == 0) return;

		data[1][1] = id_empty_;

		int_map_t a, ii;
		std::unique_ptr<int_map_t[]> select_x(new int_map_t[data.size()*data.data()->size()]);
		std::unique_ptr<int_map_t[]> select_y(new int_map_t[data.size()*data.data()->size()]);

		//ç¿ïWÇëIÇ‘
		while (true) {
			ii = mazeDig_MakeLoop(data, id_wall_, id_empty_, select_x, select_y);
			if (ii == (int_map_t)0) break;

			a = (int_map_t)gameRand((int_fast32_t)ii);
			mazeDig_Dig(data, (size_t)select_x[a], (size_t)select_y[a], id_wall_, id_empty_);
		}
		return;
	}

	//ê∂ê¨É`ÉFÉbÉN
	template<typename int_map_t>
	inline constexpr bool MazeDig<int_map_t>::mazeDig_Check(const std::vector<std::vector<int_map_t>>& data) const {
		if (data.size() <= 2 || data.data()->size() <= 2) return false;
		if ((data.size() & 1) == 0 || (data.data()->size() & 1) == 0) return false;
		return true;
	}
	//åäå@ÇË
	template<typename int_map_t>
	inline constexpr void MazeDig<int_map_t>::mazeDig_Dig(std::vector<std::vector<int_map_t>>& data, size_t x_, size_t y_, const int_map_t id_wall_, const int_map_t id_empty_) {
		if (!mazeDig_Check(data)) return;
		int_fast32_t dx, dy;
		size_t random = size_t(gameRand()), counter = 0;
		while (counter < 4) {
			switch ((random + counter) & 3)
			{
			case 0:dx = 0; dy = -2; break;
			case 1:dx = -2; dy = 0; break;
			case 2:dx = 0; dy = 2; break;
			case 3:dx = 2; dy = 0; break;
			default:dx = 0; dy = 0; break;
			}
			if (x_ + dx <= 0 || y_ + dy <= 0 || x_ + dx >= data.size() - 1 || y_ + dy >= data.data()->size() - 1 || data[x_ + dx][y_ + dy] == id_empty_) {
				++counter;
			}
			else if (data[x_ + dx][y_ + dy] == id_wall_) {
				data[x_ + (dx >> 1)][y_ + (dy >> 1)] = id_empty_;
				data[x_ + dx][y_ + dy] = id_empty_;
				x_ += dx;
				y_ += dy;
				counter = 0;
				random = size_t(gameRand());
			}
		}
		return;
	}

	//ñ¿òHê∂ê¨
	template<typename int_map_t>
	inline constexpr int_map_t MazeDig<int_map_t>::mazeDig_MakeLoop(const std::vector<std::vector<int_map_t>>& data, const int_map_t id_wall_, const int_map_t id_empty_, std::unique_ptr<int_map_t[]>& select_x, std::unique_ptr<int_map_t[]>& select_y)
	{
		size_t ii{};
		const size_t i_max{ data.size() - 1 };
		const size_t j_max{ data.data()->size() - 1 };

		for (size_t i{ 1 }; i < i_max; i += 2)
			for (size_t j{ 1 }; j < j_max; j += 2) {
				if (data[i][j] != id_empty_) continue;
				if ((i >= 2 && data[i - 2][j] == id_wall_) || (j >= 2 && data[i][j - 2] == id_wall_)) {
					select_x[ii] = (int_map_t)i;
					select_y[ii] = (int_map_t)j;
					++ii;
				}
				else if ((j == data.data()->size() - 2) && (i == data.size() - 2)) break;
				else if ((i + 2 < data.size() && data[i + 2][j] == id_wall_) || (j + 2 < data.data()->size() && data[i][j + 2] == id_wall_)) {
					select_x[ii] = (int_map_t)i;
					select_y[ii] = (int_map_t)j;
					++ii;
				}
			}
		return (int_map_t)ii;
	}

	//åoòHíTçı
	template<typename int_map_t>
	inline constexpr void MazeDig<int_map_t>::mazeDig_RootLoop(std::vector<std::vector<int_map_t>>& data, const size_t x_, const size_t y_, const int_map_t id_root_, const int_map_t id_empty_) {
		//åoòHíTçıèÛãµ
		static bool b = true;

		data[x_][y_] = id_root_;
		if (x_ == data.size() - 2 && y_ == data.data()->size() - 2) b = false;
		//è„
		if (b && data[x_][y_ - 1] == id_empty_) mazeDig_RootLoop(data, x_, y_ - 1, id_root_, id_empty_);
		//â∫
		if (b && data[x_][y_ + 1] == id_empty_) mazeDig_RootLoop(data, x_, y_ + 1, id_root_, id_empty_);
		//ç∂
		if (b && data[x_ - 1][y_] == id_empty_) mazeDig_RootLoop(data, x_ - 1, y_, id_root_, id_empty_);
		//âE
		if (b && data[x_ + 1][y_] == id_empty_) mazeDig_RootLoop(data, x_ + 1, y_, id_root_, id_empty_);

		if (b) data[x_][y_] = id_empty_;
		return;
	}

	template<typename int_map_t>
	inline constexpr void MazeDig<int_map_t>::mazeDig_Root(std::vector<std::vector<int_map_t>>& data, const int_map_t id_root_, const int_map_t id_empty_) {
		if (!mazeDig_Check(data)) return;
		mazeDig_RootLoop(data, 1, 1, id_root_, id_empty_);
	}



}

#endif // ASCLL_PROJECT_GAME_MAP_LIBRARY_MAZE_DIG