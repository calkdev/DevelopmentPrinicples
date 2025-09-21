#include "System.hpp"

/**
 * @brief Main entry point for Pokeno South Primary School Student Management System
 * @return Exit code (0 for success, 1 for failure)
 */

int main() {
    try {
        // Create system controller
        PokenoSouth::System system;
        
        // Run the application
        return system.run();
        
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "Unknown fatal error occurred." << endl;
        return 1;
    }
}
