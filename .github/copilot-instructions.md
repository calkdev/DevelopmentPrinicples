# 105-Development-Principles2 Development Guidelines

Auto-generated from all feature plans. Last updated: 2025-09-10

## Active Technologies
- C++17/20 with modern features (auto, range-based loops, constexpr) (003-class-design-demonstrating)

## Project Structure
```
src/
  student.cpp/.h          # Student class with TalentHub patterns
  course.cpp/.h           # Course class with bidirectional relationships  
  assessment.cpp/.h       # Assessment class with weighted calculations
  system.cpp/.h           # System controller with composition
  filehandler.cpp/.h      # FileHandler with CSV operations
  main.cpp                # Entry point with menu interface
tests/
  manual_test_scenarios/  # Comprehensive testing scenarios
CMakeLists.txt            # Cross-platform build configuration
data/
  students.csv            # Student data persistence
  courses.csv             # Course data persistence
  assessments.csv         # Assessment data persistence
```

## Commands
# Build and run C++ Student Management System
cmake -B build -S .
cmake --build build
./build/student_management_system

## Code Style
C++17/20: Follow modern C++ conventions with RAII, const correctness, and composition patterns. Use TalentHub's proven enterprise patterns for OOP design.

## Recent Changes
- 003-class-design-demonstrating: Added Object-Oriented Class Design Following Proven TalentHub Patterns

<!-- MANUAL ADDITIONS START -->
<!-- MANUAL ADDITIONS END -->