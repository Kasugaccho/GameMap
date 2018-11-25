//----------------------------------------
// Ascll Project Game Map Library
//----------------------------------------
#ifndef ASCLL_PROJECT_GAME_MAP_LIBRARY_DIRECTION
#define ASCLL_PROJECT_GAME_MAP_LIBRARY_DIRECTION

namespace game {
	//物体の向いている方向
	enum ObjectDirectionType :size_t {
		object_direction_type_down,
		object_direction_type_left,
		object_direction_type_right,
		object_direction_type_up,
		object_direction_type_lower_left,
		object_direction_type_lower_right,
		object_direction_type_upper_left,
		object_direction_type_upper_right,
		object_direction_type_unknown,
	};
	//歩行する方向
	enum WalkDirectionType :size_t {
		walk_direction_type_empty,
		walk_direction_type_down,
		walk_direction_type_left,
		walk_direction_type_right,
		walk_direction_type_up,
		walk_direction_type_lower_left,
		walk_direction_type_lower_right,
		walk_direction_type_upper_left,
		walk_direction_type_upper_right,
	};

	//"物体の方向"から"歩行の方向"へ変換する
	constexpr WalkDirectionType toWalkDirectionType(const ObjectDirectionType odt_) {
		switch (odt_)
		{
		case object_direction_type_down:return walk_direction_type_down;
		case object_direction_type_left:return walk_direction_type_left;
		case object_direction_type_right:return walk_direction_type_right;
		case object_direction_type_up:return walk_direction_type_up;
		case object_direction_type_lower_left:return walk_direction_type_lower_left;
		case object_direction_type_lower_right:return walk_direction_type_lower_right;
		case object_direction_type_upper_left:return walk_direction_type_upper_left;
		case object_direction_type_upper_right:return walk_direction_type_upper_right;
		}
		return walk_direction_type_empty;
	}
	//"物体の方向"から"歩行の方向"へ変換する(歩行の有無つき)
	constexpr WalkDirectionType toWalkDirectionType(const ObjectDirectionType odt_, const bool is_walk_) {
		if (is_walk_) return toWalkDirectionType(odt_);
		return walk_direction_type_empty;
	}
	//"物体の方向"から"歩行の方向"へ変換する
	constexpr void toWalkDirectionType(const ObjectDirectionType odt_, WalkDirectionType& wdt_) {
		switch (odt_)
		{
		case object_direction_type_down:wdt_ = walk_direction_type_down; return;
		case object_direction_type_left:wdt_ = walk_direction_type_left; return;
		case object_direction_type_right:wdt_ = walk_direction_type_right; return;
		case object_direction_type_up:wdt_ = walk_direction_type_up; return;
		case object_direction_type_lower_left:wdt_ = walk_direction_type_lower_left; return;
		case object_direction_type_lower_right:wdt_ = walk_direction_type_lower_right; return;
		case object_direction_type_upper_left:wdt_ = walk_direction_type_upper_left; return;
		case object_direction_type_upper_right:wdt_ = walk_direction_type_upper_right; return;
		}
		wdt_ = walk_direction_type_empty;
		return;
	}
	//"物体の方向"から"歩行の方向"へ変換する(歩行の有無つき)
	constexpr void toWalkDirectionType(const ObjectDirectionType odt_, WalkDirectionType& wdt_, const bool is_walk_) {
		if (is_walk_) {
			wdt_ = toWalkDirectionType(odt_);
			return;
		}
		wdt_ = walk_direction_type_empty;
		return;
	}

	constexpr WalkDirectionType getWalkDirectionType(const WalkDirectionType up_and_down_, const WalkDirectionType left_and_right_) {
		switch (up_and_down_) {
		case walk_direction_type_down:
			switch (left_and_right_) {
			case walk_direction_type_left:
				return walk_direction_type_lower_left;
			case walk_direction_type_right:
				return walk_direction_type_lower_right;
			default:
				return walk_direction_type_down;
			}
		case walk_direction_type_up:
			switch (left_and_right_) {
			case walk_direction_type_left:
				return walk_direction_type_upper_left;
			case walk_direction_type_right:
				return walk_direction_type_upper_right;
			default:
				return walk_direction_type_up;
			}
		default:
			switch (left_and_right_) {
			case walk_direction_type_left:
				return walk_direction_type_left;
			case walk_direction_type_right:
				return walk_direction_type_right;
			}
			break;
		}
		return walk_direction_type_empty;
	}

	constexpr game::WalkDirectionType crossKey(double& x_, double& y_, const double moving_distance_, const bool down_, const bool left_, const bool right_, const bool up_) {
		game::WalkDirectionType up_and_down{ game::walk_direction_type_empty }, left_and_right{ game::walk_direction_type_empty };
		if (!up_ || !down_) {
			if (up_) {
				y_ -= moving_distance_;
				up_and_down = game::walk_direction_type_up;
			}
			else if (down_) {
				y_ += moving_distance_;
				up_and_down = game::walk_direction_type_down;
			}
		}
		if (!left_ || !right_) {
			if (left_) {
				x_ -= moving_distance_;
				left_and_right = game::walk_direction_type_left;
			}
			else if (right_) {
				x_ += moving_distance_;
				left_and_right = game::walk_direction_type_right;
			}
		}
		return game::getWalkDirectionType(up_and_down, left_and_right);
	}
	constexpr game::WalkDirectionType movePlayer(double& x_, double& y_, const double moving_distance_, const game::WalkDirectionType wdt_) {
		switch (wdt_)
		{
		case walk_direction_type_down:
			y_ += moving_distance_;
			break;
		case walk_direction_type_left:
			x_ -= moving_distance_;
			break;
		case walk_direction_type_right:
			x_ += moving_distance_;
			break;
		case walk_direction_type_up:
			y_ -= moving_distance_;
			break;
		case walk_direction_type_lower_left:
			y_ += moving_distance_;
			x_ -= moving_distance_;
			break;
		case walk_direction_type_lower_right:
			y_ += moving_distance_;
			x_ += moving_distance_;
			break;
		case walk_direction_type_upper_left:
			y_ -= moving_distance_;
			x_ -= moving_distance_;
			break;
		case walk_direction_type_upper_right:
			y_ -= moving_distance_;
			x_ += moving_distance_;
			break;
		}
		return wdt_;
	}
	constexpr game::WalkDirectionType crossKey(const bool down_, const bool left_, const bool right_, const bool up_) {
		game::WalkDirectionType up_and_down{ game::walk_direction_type_empty }, left_and_right{ game::walk_direction_type_empty };
		if (!up_ || !down_) {
			if (up_) up_and_down = game::walk_direction_type_up;
			else if (down_) up_and_down = game::walk_direction_type_down;
		}
		if (!left_ || !right_) {
			if (left_) left_and_right = game::walk_direction_type_left;
			else if (right_) left_and_right = game::walk_direction_type_right;
		}
		return game::getWalkDirectionType(up_and_down, left_and_right);
	}

	//あたり判定
	template<typename vector_>
	constexpr auto collisionDetection(const vector_& vec_, const size_t x_, const size_t y_, const game::WalkDirectionType walk_direction_type_) {
		const size_t max_y{ vec_.size() };
		const size_t max_x{ (max_y == 0) ? 0 : vec_.front().size() };
		const size_t player_x{ x_ % max_x };
		const size_t player_y{ y_ % max_y };

		switch (walk_direction_type_)
		{
		case walk_direction_type_empty:
			return vec_[player_y][player_x];
		case walk_direction_type_down:
			return vec_[(player_y + 1) % max_y][player_x];
		case walk_direction_type_left:
			return vec_[player_y][(player_x + max_x - 1) % max_x];
		case walk_direction_type_right:
			return vec_[player_y][(player_x + 1) % max_x];
		case walk_direction_type_up:
			return vec_[(player_y + max_y - 1) % max_y][player_x];
		case walk_direction_type_lower_left:
			return vec_[(player_y + 1) % max_y][(player_x + max_x - 1) % max_x];
		case walk_direction_type_lower_right:
			return vec_[(player_y + 1) % max_y][(player_x + 1) % max_x];
		case walk_direction_type_upper_left:
			return vec_[(player_y + max_y - 1) % max_y][(player_x + max_x - 1) % max_x];
		case walk_direction_type_upper_right:
			return vec_[(player_y + max_y - 1) % max_y][(player_x + 1) % max_x];
		}
		return vec_[player_y][player_x];
	}
}

#endif // ASCLL_PROJECT_GAME_MAP_LIBRARY_DIRECTION