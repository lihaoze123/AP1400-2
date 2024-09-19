#ifndef Q4_H
#define Q4_H

namespace q4 {
    struct Vector2D {
		double x{};
		double y{};
	};

	struct Sensor {
		Vector2D pos;
		double accuracy;
	};

	inline Vector2D kalman_filter(std::vector<Sensor> sensors) {
		double base = 0;
		for (const auto& [_, accuracy] : sensors)
			base += accuracy;

		double res_x = 0, res_y = 0;

		for (const auto& [pos, accuracy] : sensors) {
			res_x += pos.x * accuracy;
			res_y += pos.y * accuracy;
		}

		return Vector2D{res_x / base, res_y / base};
	}
};

#endif //Q4_H