#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>

const std::string numbers = "0123456789";
const std::string lower_case = "abcdefghijklmnopqrstuvwxyz";
const std::string upper_case = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string special_chars = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/`~";


// Function to calculate time to crack the password (in seconds)
double calculate_crack_time(int length) {
    const double attempts_per_second = 1e9; // 1 billion attempts per second
    double total_combinations = pow(numbers.size() + lower_case.size() + upper_case.size() + special_chars.size(), length);
    return total_combinations / attempts_per_second;
}

// Function to format time (in seconds) into human-readable format
std::string format_time(double seconds) {
    if (seconds < 60) {
        return std::to_string(seconds) + " seconds";
    } else if (seconds < 3600) {
        return std::to_string(seconds / 60) + " minutes";
    } else if (seconds < 86400) {
        return std::to_string(seconds / 3600) + " hours";
    } else if (seconds < 31536000) {
        return std::to_string(seconds / 86400) + " days";
    } else {
        return std::to_string(seconds / 31536000) + " years";
    }
}

// Function to generate a random password
std::string generate_password(int length) {
    std::string all_chars = numbers + lower_case + upper_case + special_chars;
    std::string password;
    
    // Ensure password contains at least one character from each category
    password += numbers[rand() % numbers.size()];
    password += lower_case[rand() % lower_case.size()];
    password += upper_case[rand() % upper_case.size()];
    password += special_chars[rand() % special_chars.size()];
    
    // Fill the rest of the password with random characters
    for (int i = 4; i < length; ++i) {
        password += all_chars[rand() % all_chars.size()];
    }
    
    // Shuffle the password to randomize order
    std::random_shuffle(password.begin(), password.end());
    
    return password;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    char repeat;
    do {
        int length;
        std::cout << "Enter the desired password length (minimum 4): ";
        std::cin >> length;
        
        if (length < 4) {
            std::cerr << "Password length must be at least 4 to include all character types!" << std::endl;
            return 1;
        }
        
        std::string password = generate_password(length);
        double crack_time = calculate_crack_time(length);
        
        std::cout << "Generated Password: " << password << std::endl;
        std::cout << "Estimated time to crack: " << format_time(crack_time) << std::endl;
        
        std::cout << "Would you like to generate another password? (y/n): ";
        std::cin >> repeat;
    } while (repeat == 'y' || repeat == 'Y');
    
    return 0;
}
