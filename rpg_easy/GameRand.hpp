//----------------------------------------
// Ascll Project Game Map Library
//----------------------------------------
#ifndef ASCLL_PROJECT_GAME_MAP_LIBRARY_GAME_RAND
#define ASCLL_PROJECT_GAME_MAP_LIBRARY_GAME_RAND

namespace game {

	class GameRand {
	private:
		std::mt19937 mt;
		std::random_device rd;
	public:
		GameRand() { mt.seed(rd()); }
		uint_fast32_t operator()() {
			return mt();
		}
		//0�`�ő�l-1 (�]��)
		int_fast32_t operator()(const int_fast32_t max_) {
			std::uniform_int_distribution<> uid(0, max_ - 1);
			return uid(rd);
		}
		//�ŏ��l�`�ő�l
		int_fast32_t operator()(const int_fast32_t min_, const int_fast32_t max_) {
			std::uniform_int_distribution<> uid(0, max_ - min_);
			return uid(rd) + min_;
		}
		//�m��
		bool randBool(const double probability_ = 0.5) {
			std::bernoulli_distribution uid(probability_);
			return uid(rd);
		}
	};
	static thread_local GameRand gameRand;

}

#endif // ASCLL_PROJECT_GAME_MAP_LIBRARY_GAME_RAND