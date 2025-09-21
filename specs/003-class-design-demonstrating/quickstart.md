# Quickstart Guide: Student Management System

## Overview
This quickstart guide demonstrates the core functionality of the Pokeno South Primary School Student Management System, implementing proven TalentHub Wellington patterns for educational data management.

## Prerequisites
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.16 or higher
- No external dependencies required

## Build and Run

### 1. Build the Application
```bash
# Clone and navigate to project directory
cd PokenoSouthPrimary

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the application
make

# Run the application
./PokenoSouthPrimary
```

### 2. Alternative Build (Direct Compilation)
```bash
# Compile directly with g++
g++ -std=c++17 -Wall -Wextra -I src/ \
    main.cpp \
    src/app/app.cpp \
    src/app/system.cpp \
    src/services/student.cpp \
    src/services/course.cpp \
    src/services/assessment.cpp \
    src/services/gradecalculator.cpp \
    src/handling/filehandler.cpp \
    -o PokenoSouthPrimary

# Run the application
./PokenoSouthPrimary
```

## Basic Usage Walkthrough

### Initial Setup
1. **Application Start**: Run the executable to launch the menu-driven interface
2. **Data Initialization**: System loads existing data from CSV files or creates empty files
3. **Main Menu**: Navigate using numbered menu options

### Core Workflow Example

#### Step 1: Add a New Course
```
Main Menu > Course Management > Add New Course
Enter Course ID (e.g., MATH101): MATH101
Enter Course Name: Mathematics Year 3
Enter Credits (1-6): 3
Enter Description: Basic arithmetic and problem solving
Enter Duration (weeks): 40
```

#### Step 2: Register a New Student
```
Main Menu > Student Management > Register New Student
Enter Roll Number: 12345
Enter First Name: John
Enter Last Name: Smith
Enter Date of Birth (YYYY-MM-DD): 2010-05-15
Enter Contact Email: parent@email.com
Enter Emergency Contact: emergency@email.com
Enter Enrollment Date (YYYY-MM-DD): 2025-02-01
```

#### Step 3: Enroll Student in Course
```
Main Menu > Enrollment Management > Enroll Student
Enter Student Roll Number: 12345
Enter Course ID: MATH101
Confirm enrollment? (y/n): y
```

#### Step 4: Add Assessment
```
Main Menu > Assessment Management > Add Assessment
Enter Student Roll Number: 12345
Enter Course ID: MATH101
Enter Internal Marks (0-100): 75
Enter Final Marks (0-100): 82
Enter Assessment Date (YYYY-MM-DD): 2025-06-15
```

#### Step 5: View Results
```
Main Menu > Reports > Student Transcript
Enter Student Roll Number: 12345

--- Student Transcript ---
Name: John Smith (Roll: 12345)
Course: MATH101 - Mathematics Year 3
Internal: 75.0 (30%) | Final: 82.0 (70%)
Calculated Grade: 79.1
```

## Menu System Navigation

### Main Menu Structure
```
1. Student Management
   ├── 1.1 Register New Student
   ├── 1.2 View Student Details
   ├── 1.3 Update Student Information
   ├── 1.4 List All Students
   └── 1.5 Remove Student

2. Course Management
   ├── 2.1 Add New Course
   ├── 2.2 View Course Details
   ├── 2.3 Update Course Information
   ├── 2.4 List All Courses
   └── 2.5 Remove Course

3. Enrollment Management
   ├── 3.1 Enroll Student in Course
   ├── 3.2 Drop Student from Course
   ├── 3.3 View Student Enrollments
   └── 3.4 View Course Enrollments

4. Assessment Management
   ├── 4.1 Add New Assessment
   ├── 4.2 Update Assessment Marks
   ├── 4.3 View Assessment Details
   └── 4.4 Remove Assessment

5. Reports and Analytics
   ├── 5.1 Student Transcript
   ├── 5.2 Course Grade Report
   ├── 5.3 Overall Statistics
   └── 5.4 Export Data

6. System Administration
   ├── 6.1 Backup Data
   ├── 6.2 Restore from Backup
   ├── 6.3 Validate Data Integrity
   └── 6.4 System Information

0. Exit Application
```

## Data File Locations

### CSV Files Created
- `src/data/students.csv` - Student records
- `src/data/courses.csv` - Course catalog
- `src/data/assessments.csv` - Assessment records  
- `src/data/enrollments.csv` - Student-course enrollments

### Backup Files
- `src/data/backup/` - Automatic backup location
- Timestamped backups created before major operations

## Sample Data Format

### Sample Students.csv
```csv
RollNumber,FirstName,LastName,DateOfBirth,ContactEmail,EmergencyContact,EnrollmentDate
12345,John,Smith,2010-05-15,parent@email.com,emergency@email.com,2025-02-01
12346,Jane,Doe,2010-08-22,jane.parent@email.com,jane.emergency@email.com,2025-02-01
```

### Sample Courses.csv
```csv
CourseId,CourseName,Credits,Description,Duration
MATH101,Mathematics Year 3,3,Basic arithmetic and problem solving,40
ENG101,English Year 3,3,Reading comprehension and writing skills,40
```

### Sample Assessments.csv
```csv
AssessmentId,StudentRollNumber,CourseId,InternalMarks,FinalMarks,AssessmentDate,CalculatedGrade
ASS001,12345,MATH101,75.0,82.0,2025-06-15,79.1
ASS002,12346,MATH101,88.0,91.0,2025-06-15,90.1
```

## Validation Examples

### Input Validation Demonstrations
```bash
# Roll number uniqueness check
Enter Roll Number: 12345
Error: Roll number 12345 already exists. Please enter a unique number.

# Date format validation
Enter Date of Birth (YYYY-MM-DD): 15/05/2010
Error: Invalid date format. Please use YYYY-MM-DD format.

# Email format validation
Enter Contact Email: invalid-email
Error: Invalid email format. Please enter a valid email address.

# Grade range validation
Enter Internal Marks (0-100): 105
Error: Marks must be between 0 and 100. Please enter a valid score.
```

## Error Handling Examples

### File Operation Errors
```bash
# Missing data file
Warning: students.csv not found. Creating new empty file.

# Permission error
Error: Cannot write to data/students.csv. Check file permissions.

# Data corruption
Error: Invalid data format in line 5 of courses.csv. Please check file integrity.
```

### Business Rule Violations
```bash
# Enrollment without course
Error: Cannot enroll student 12345. Course PHYS101 does not exist.

# Duplicate assessment
Error: Assessment already exists for student 12345 in course MATH101.

# Course deletion with enrolled students
Error: Cannot delete course MATH101. 15 students are still enrolled.
```

## Testing Scenarios

### Complete Student Lifecycle Test
1. Register student → Verify in student list
2. Enroll in course → Verify in enrollment list
3. Add assessment → Verify grade calculation
4. Update marks → Verify recalculation
5. Generate transcript → Verify report accuracy
6. Unenroll from course → Verify cleanup
7. Remove student → Verify cascading deletion

### Data Integrity Test
1. Create backup → Verify backup file
2. Make changes → Modify student data
3. Validate integrity → Run validation check
4. Restore backup → Verify restoration
5. Compare data → Ensure consistency

### Performance Test
1. Load sample data → 100 students, 10 courses
2. Bulk enrollment → Enroll all students in all courses
3. Bulk assessment → Add assessments for all enrollments
4. Generate reports → Test report generation speed
5. Export data → Verify export functionality

## Troubleshooting

### Common Issues
- **Build errors**: Ensure C++17 compiler and CMake version compatibility
- **File permissions**: Check write access to data directory
- **Data corruption**: Use backup/restore functionality
- **Menu navigation**: Use numeric input only, press Enter after each choice

### Recovery Procedures
- **Data loss**: Restore from most recent backup
- **Corruption**: Run data integrity validation and cleanup
- **Performance**: Check file sizes and consider data archival

## Learning Objectives Demonstrated

### TalentHub Pattern Applications
- **Encapsulation**: Private data with controlled public interfaces
- **Composition**: Student owns Assessment objects (stronger than association)
- **Repository Pattern**: Static FileHandler methods for data persistence
- **Controller Pattern**: System class orchestrates all operations
- **Menu-Driven Interface**: Hierarchical navigation following TalentHub UX

### Modern C++ Features
- **RAII**: Automatic resource management
- **STL Containers**: Vector for collections, string for text
- **Const Correctness**: Immutable data and const methods
- **Range-based Loops**: Modern iteration patterns
- **Auto Type Deduction**: Simplified variable declarations
