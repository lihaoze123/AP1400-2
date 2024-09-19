#ifndef Q2_H
#define Q2_H

#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

namespace q2 {
    struct Patient {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };

    inline bool operator <(const Patient& lhs, const Patient& rhs) {
        return (3 * lhs.age + 5 * lhs.smokes + 2 * lhs.area_q + 4 * lhs.alkhol) <
                   (3 * rhs.age + 5 * rhs.smokes + 2 * rhs.area_q + 4 * rhs.alkhol);
    }

    inline bool operator ==(const Patient& lhs, const Patient& rhs) {
        return lhs.age == rhs.age && lhs.smokes == rhs.smokes && lhs.area_q == rhs.area_q &&
            lhs.alkhol == rhs.alkhol;
    }

    inline bool operator >(const Patient& lhs, const Patient& rhs) {
        return !(lhs == rhs || lhs < rhs);
    }

    inline bool read_patient(std::ifstream& fs, Patient& patient) {
        std::string line, t;

        getline(fs, line);
        std::replace(line.begin(), line.end(), ',', ' ');
        std::stringstream ss(line);

        auto &[name, age, smokes, area_q, alkhol] = patient;

        ss >> name >> t;
        if (ss.eof() || ss.fail())
            return false;
        name = name + ' ' + t;

        ss >> age;
        if (ss.eof() || ss.fail())
            return false;

        ss >> smokes;
        if (ss.eof() || ss.fail())
            return false;

        ss >> area_q;
        if (ss.eof() || ss.fail())
            return false;

        ss >> alkhol;
        if (ss.fail())
            return false;

        return true;
    }

    inline std::vector<Patient> read_file(std::string filename) {
        Patient patient;
        std::ifstream fs(filename);

        // Deal with header
        read_patient(fs, patient);
        read_patient(fs, patient);

        std::vector<Patient> patients;

        while (read_patient(fs, patient))
            patients.push_back(patient);

        return patients;
    }

    template <class Container = std::vector<Patient>>
    void qsort(Container& container, size_t l, size_t r) {
        if (l >= r)
            return;

        int i = l - 1, j = r + 1;
        auto x = container[l + r >> 1];
        while (i < j) {
            do i ++; while (container[i] > x);
            do j --; while (container[j] < x);

            if (i < j)
                std::swap(container[i], container[j]);
        }

        qsort(container, l, j), qsort(container, j + 1, r);
    }

    inline void sort(std::vector<Patient>& patients) {
        qsort(patients, 0, patients.size() - 1);
    }
};

#endif //Q2_H