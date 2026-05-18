#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <filesystem>

struct PlayerData {
    std::string name;
    int score;
};

class DataManager {
private:
    std::string filename;
    std::vector<PlayerData> leaderboard;

public:
    DataManager(const std::string& file = "data/leaderboard.txt") : filename(file) {}

    void addData(const std::string& name, int score) {
        leaderboard.push_back({name, score});
    }

    void saveData() const {
        std::filesystem::path p(filename);
        if (p.has_parent_path()) {
            std::filesystem::create_directories(p.parent_path());
        }
        
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& p : leaderboard) {
                file << p.name << "," << p.score << "\n";
            }
            file.close();
        } else {
            std::cerr << "Error: Cannot open file for writing: " << filename << "\n";
        }
    }

    void loadData() {
        leaderboard.clear();
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string name;
                std::string scoreStr;
                if (std::getline(ss, name, ',') && std::getline(ss, scoreStr)) {
                    leaderboard.push_back({name, std::stoi(scoreStr)});
                }
            }
            file.close();
        } else {
            std::cerr << "Error: Cannot open file for reading: " << filename << "\n";
        }
    }

    const std::vector<PlayerData>& getLeaderboard() const {
        return leaderboard;
    }
    
    // Sort logic to get top players (descending score)
    void sortLeaderboard() {
        std::sort(leaderboard.begin(), leaderboard.end(), [](const PlayerData& a, const PlayerData& b) {
            return a.score > b.score;
        });
    }

    // Search logic
    int searchPlayer(const std::string& name) const {
        for (size_t i = 0; i < leaderboard.size(); ++i) {
            if (leaderboard[i].name == name) {
                return i;
            }
        }
        return -1;
    }
    
    // Mock data for performance testing
    void generateMockData(int count) {
        leaderboard.clear();
        for (int i = 0; i < count; ++i) {
            leaderboard.push_back({"Player" + std::to_string(i), std::rand() % 10000});
        }
    }
};
