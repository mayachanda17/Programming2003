#include <iostream> // allows printing to the screen
#include <fstream> // allows reading files
#include <cmath> // gives the square root function

// number of event + event id 
// function to calculate and return total momentum magnitude
double getMomentum(double px, double py, double pz) {
    return std::sqrt(px * px + py * py + pz * pz);
    
}

int main() {
    // open the input file
    std::ifstream infile("output-Set0.txt.txt");
    if (!infile) { // safety check that prints error and stops program if file fails to open
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    
    int eventID = 0;
    int numParticles = 0;
    
    // read the header line containing event ID and number of particles
    if (infile >> eventID >> numParticles) { // >> operator reads values from the file one by one
        std::cout << "Event ID: " << eventID << " | Number of particles: " << numParticles << "\n"; // 
        std::cout << "--------------------------------------------------------\n";
    } else {
        std::cerr << "Failed to read event header!" << std::endl;
        return 1;
    }

   // Variables for particle data
    double px = 0.0, py = 0.0, pz = 0.0;
    int particleCode = 0;

    // loop through all particles listed in the event
    for (int i = 0; i < numParticles; ++i) { // loop runs 29 times
        if (infile >> px >> py >> pz >> particleCode) { // reads four numbers for each particle row by row
            // Calculate momentum using the function
            double momentum = getMomentum(px, py, pz); // calls function defined at start to calculate result for that specific particle

            // Display results
            std::cout << "Particle " << (i + 1) << " (Code: " << particleCode << "): "
                      << "Momentum = " << momentum << "\n";
        }
    }
   
    return 0; // returns integer value
}
