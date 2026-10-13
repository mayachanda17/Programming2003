#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <iomanip>

// Structure to store results per sub-sample (file)
struct SubSampleData {
    std::unordered_map<int, double> particle_counts;
    long long total_events = 0;
};

void processFile(const std::string& filename, SubSampleData& subSample) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    int event_id, n_particles;
    while (file >> event_id >> n_particles) {
        subSample.total_events++;
        
        for (int i = 0; i < n_particles; ++i) {
            double px, py, pz;
            int pdg_id;
            file >> px >> py >> pz >> pdg_id;
            subSample.particle_counts[pdg_id]++;
        }
    }
    file.close();
}

int main() {
    // List of input filenames (11 sub-samples)
    std::vector<std::string> file_list = {
        "output-Set0.txt", "output-Set1.txt", "output-Set2.txt", "output-Set3.txt", "output-Set4.txt",
        "output-Set5.txt", "output-Set6.txt", "output-Set7.txt", "output-Set8.txt", "output-Set9.txt", "output-Set10.txt"
    };

    size_t num_subsamples = file_list.size();
    
    // Store per-event average counts for each ID across all sub-samples
    // Map: [Particle_ID] -> vector of length N_subsamples containing (counts / total_events)
    std::unordered_map<int, std::vector<double>> subsample_averages;

    std::cout << "Processing " << num_subsamples << " sub-samples..." << std::endl;

    for (size_t i = 0; i < num_subsamples; ++i) {
        std::cout << "Processing file " << (i + 1) << " of " << num_subsamples 
                  << ": " << file_list[i] << "..." << std::flush;
        SubSampleData data;
        processFile(file_list[i], data);

        std::cout << " Done! (" << data.total_events << " events processed)" << std::endl;

        if (data.total_events == 0) continue;

        // Collect all unique IDs found so far
        for (const auto& pair : data.particle_counts) {
            int id = pair.first;
            if (subsample_averages.find(id) == subsample_averages.end()) {
                subsample_averages[id] = std::vector<double>(num_subsamples, 0.0);
            }
            subsample_averages[id][i] = pair.second / static_cast<double>(data.total_events);
        }
    }

    // Print Results formatted for markdown export
    std::cout << "\n=== RESULTS ===" << std::endl;
    std::cout << std::left << std::setw(12) << "ID" 
              << std::setw(20) << "Mean (per event)" 
              << std::setw(20) << "Stat Uncertainty" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    for (const auto& pair : subsample_averages) {
        int id = pair.first;
        const std::vector<double>& yields = pair.second;

        // Compute overall mean
        double sum = 0.0;
        for (double val : yields) {
            sum += val;
        }
        double mean = sum / num_subsamples;

        // Compute sample standard deviation (statistical uncertainty via sub-sampling)
        double variance_sum = 0.0;
        for (double val : yields) {
            variance_sum += std::pow(val - mean, 2);
        }
        double stdev = (num_subsamples > 1) 
                     ? std::sqrt(variance_sum / (num_subsamples - 1)) 
                     : 0.0;

        std::cout << std::left << std::setw(12) << id 
                  << std::setw(20) << mean 
                  << std::setw(20) << stdev << std::endl;
    }

    return 0;
}