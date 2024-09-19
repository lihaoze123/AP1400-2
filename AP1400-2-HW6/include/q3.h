#ifndef Q3_H
#define Q3_H

#include <fstream>
#include <sstream>
#include <cstdio>
#include <queue>

namespace q3 {
    struct Flight {
        std::string flight_number;
        size_t duration{};
        size_t connections{};
        size_t connection_times{};
        size_t price{};
    };

    inline bool operator <(const Flight &lhs, const Flight &rhs) {
        return (lhs.duration + lhs.connection_times + lhs.price * 3) < (
                   rhs.duration + rhs.connection_times + rhs.price * 3);
    }

    inline bool operator ==(const Flight &lhs, const Flight &rhs) {
        return lhs.duration == rhs.duration && lhs.connection_times == rhs.connection_times && lhs.price == rhs.price;
    }

    inline bool operator !=(const Flight &lhs, const Flight &rhs) {
        return !(lhs == rhs);
    }

    inline bool operator >(const Flight &lhs, const Flight &rhs) {
        return !(lhs == rhs || lhs < rhs);
    }

    inline size_t get_time(const std::string& s) {
        size_t hours, minutes;

        std::istringstream ss(s);
        ss >> hours >> minutes;

        return hours * 60 + minutes;
    }

    inline Flight read_flight(std::istream& is) {
        if (is.fail() || is.bad() || is.eof())
            return Flight{};

        Flight flight;
        auto &[flight_number, duration, connections, connection_times, price] = flight;

        std::string line;
        getline(is, line);

        int num;
        char flight_number_buf[100], duration_buf[100], connection_times_buf[100];
        sscanf(line.c_str(), "%d- flight_number:%s - duration:%s - connections:%d - connection_times:%s - price:%d",
               &num, flight_number_buf, duration_buf, &connections, connection_times_buf, &price);

        flight_number = flight_number_buf;

        std::string duration_str{duration_buf}, connection_times_str{connection_times_buf};
        std::ranges::replace(connection_times_str, ',', ' ');

        duration = get_time(duration_str);

        std::istringstream ss(connection_times_str);
        for (size_t i = 0; i < connections; ++ i) {
            std::string connection;
            ss >> connection;

            connection_times += get_time(connection);
        }

        return flight;
    }


    typedef std::priority_queue<Flight, std::vector<Flight>, std::greater<Flight>> PriorityQueue;
    inline PriorityQueue gather_flights(const std::string& filename) {
        PriorityQueue res;

        std::ifstream fs(filename);

        Flight flight;
        while (flight = read_flight(fs), flight != Flight{})
            res.push(flight);

        return res;
    }
};

#endif //Q3_H