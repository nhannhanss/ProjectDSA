#include "data_manager.h"
#include <iostream>
#include <chrono>
#include <cassert>

void run_performance_tests() {
    DataManager dm("test_leaderboard.csv");
    const int DATA_SIZE = 10000;

    std::cout << "--- BAT DAU PERFORMANCE TEST (" << DATA_SIZE << " records) ---\n";

    // 1. Sinh mock data
    auto start = std::chrono::high_resolution_clock::now();
    dm.generateMockData(DATA_SIZE);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "1. Generate Mock Data: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms\n";

    // 2. Save data
    start = std::chrono::high_resolution_clock::now();
    dm.saveData();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "2. Save Data to File: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms\n";

    // 3. Load data
    DataManager dm2("test_leaderboard.csv");
    start = std::chrono::high_resolution_clock::now();
    dm2.loadData();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "3. Load Data from File: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms\n";
    assert(dm2.getLeaderboard().size() == DATA_SIZE);

    // 4. Search player
    std::string searchTarget = "Player9999";
    start = std::chrono::high_resolution_clock::now();
    int index = dm2.searchPlayer(searchTarget);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "4. Search '" << searchTarget << "': " 
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() 
              << " us (micro-seconds)\n";
    assert(index != -1);

    // 5. Sort leaderboard
    start = std::chrono::high_resolution_clock::now();
    dm2.sortLeaderboard();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "5. Sort Data (Top scores): " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms\n";

    // Print Top 10
    std::cout << "\n--- TOP 10 PLAYERS ---\n";
    const auto& leaderboard = dm2.getLeaderboard();
    for(int i = 0; i < 10 && i < leaderboard.size(); ++i) {
        std::cout << i + 1 << ". " << leaderboard[i].name << " - " << leaderboard[i].score << "\n";
    }

    std::cout << "\n--- PERFORMANCE TEST HOAN THANH ---\n";
}

int main() {
    run_performance_tests();
    return 0;
}
