//----------------------------------------
// Ascll Project Game Map Library
//----------------------------------------
#ifndef ASCLL_PROJECT_GAME_MAP_LIBRARY_GAME_MAP
#define ASCLL_PROJECT_GAME_MAP_LIBRARY_GAME_MAP

namespace game {

	template<typename int_map_t>
	class GameMap {
	private:
		using game_map = std::vector<std::vector<int_map_t>>;

	public:
		game_map data{};

		//�R���X�g���N�^
		GameMap() = default;
		constexpr GameMap(const size_t x_, const size_t y_, const int_map_t& v_)
			:data(y_, std::vector<int_map_t>(x_, v_)) {}
		void reset(const size_t x_, const size_t y_, const int_map_t& v_) {
			data = std::move(game_map(y_, std::vector<int_map_t>(x_, v_)));
		}

		//X���W�}�b�v�̃}�X�T�C�Y��Ԃ�
		size_t sizeX() const {
			return (data.size() == 0) ? 0 : data.front().size();
		}

		//Y���W�}�b�v�̃}�X�T�C�Y��Ԃ�
		size_t sizeY() const {
			return data.size();
		}

		//�}�b�v�̃}�X������Ԃ�
		size_t size() const {
			return sizeX()*sizeY();
		}

		void output(const std::string& = ",")const;

		void blockOutput(const std::string&, const int_map_t&, const std::string& = " ", const int_map_t& = 0) const;
		void blockOutput2(const std::string&, const int_map_t&, const std::string&, const int_map_t&, const std::string& = " ", const int_map_t& = 0) const;

		void put(const size_t x_, const size_t y_, const int_map_t& v_) {
			data[y_][x_] = v_;
		}




	};



	//�o�͌n----------

	template<typename int_map_t>
	inline void GameMap<int_map_t>::output(const std::string& str_) const {
		for (size_t i = 0; i < data.size(); ++i) {
			for (size_t j = 0; j < data[i].size(); ++j)
				std::cout << data[i][j] << str_;
			std::cout << std::endl;
		}
	}

	template<typename int_map_t>
	inline void GameMap<int_map_t>::blockOutput(const std::string& bstr_, const int_map_t& block_, const std::string& estr_, const int_map_t& empty_) const {
		for (size_t i = 0; i < data.size(); ++i) {
			for (size_t j = 0; j < data[i].size(); ++j) {
				if (data[i][j] == block_) std::cout << bstr_;
				else if (data[i][j] == empty_) std::cout << estr_;
			}
			std::cout << std::endl;
		}
	}

	template<typename int_map_t>
	inline void GameMap<int_map_t>::blockOutput2(const std::string& bstr_, const int_map_t& block_, const std::string& rstr_, const int_map_t& root_, const std::string& estr_, const int_map_t& empty_) const {
		for (size_t i = 0; i < data.size(); ++i) {
			for (size_t j = 0; j < data[i].size(); ++j) {
				if (data[i][j] == block_) std::cout << bstr_;
				else if (data[i][j] == root_) std::cout << rstr_;
				else if (data[i][j] == empty_) std::cout << estr_;
			}
			std::cout << std::endl;
		}
	}

}

#endif // ASCLL_PROJECT_GAME_MAP_LIBRARY_GAME_MAP