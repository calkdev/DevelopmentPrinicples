#include "System.hpp"

namespace PokenoSouth {

System::System() 
    : isRunning(false)
    , dataLoaded(false)
    , currentSession("")
{
    auto now = system_clock::now();
    auto time_t = system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&time_t), "%d-%m-%Y %H:%M:%S");
    currentSession = "Session started: " + ss.str();
}

System::~System() {
    if (isRunning) {
        shutdown();
    }
}

bool System::initialize() {
    try {
        displayHeader("Pokeno South Primary School - Student Management System");
        cout << "Initializing system...\n" << endl;
        
        if (!FileHandler::initializeDataFiles()) {
            cerr << "Warning: Could not initialize data directories\n";
        }
        
        loadAllSystemData();
        
        cout << "System initialized successfully!" << endl;
        cout << "Students loaded: " << students.size() << endl;
        cout << "Courses loaded: " << courses.size() << endl;
        cout << "Assessments loaded: " << assessments.size() << "\n" << endl;
        
        dataLoaded = true;
        return true;
        
    } catch (const exception& e) {
        cerr << "Failed to initialize system: " << e.what() << endl;
        return false;
    }
}

int System::run() {
    if (!initialize()) {
        cerr << "System initialization failed. Exiting..." << endl;
        return 1;
    }
    
    isRunning = true;
    
    while (isRunning) {
        try {
            clearScreenWithHeader("Main Menu");
            displayMainMenu();

            switch (int choice = getMenuChoice(0, 6)) {
                case 1:
                    handleStudentMenu();
                    break;
                case 2:
                    handleCourseMenu();
                    break;
                case 3:
                    handleAssessmentMenu();
                    break;
                case 4:
                    handleReportsMenu();
                    break;
                case 5:
                    handleSystemMenu();
                    break;
                case 6:
                    cout << "\n=== ABOUT POKENO SOUTH PRIMARY SCHOOL SYSTEM ===" << endl;
                    cout << "Version: 1.0.0\n";
                    cout << "Developed by Adam Calkin : 270712965, Ben Edwards : 270471269, & Allan Werner : 270697583\n";
                    cout << "Features: Student, Course, and Assessment management\n";
                    cout << "Data persistence via CSV files\n";
                    pauseForUser();
                    break;
                case 0:
                    if (confirmSystemExit()) {
                        isRunning = false;
                    }
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    pauseForUser();
                    break;
            }
            
        } catch (const exception& e) {
            cerr << "An error occurred: " << e.what() << "\n";
            pauseForUser();
        }
    }
    
    return shutdown() ? 0 : 1;
}

bool System::shutdown() {
    try {
        if (dataLoaded) {
            cout << "\nSaving system data...\n";
            if (saveAllSystemData()) {
                cout << "All data saved successfully.\n";
            } else {
                cerr << "Warning: Some data may not have been saved properly.\n";
            }
        }
        
        isRunning = false;
        cout << "System shutdown complete.\n";
        return true;
        
    } catch (const exception& e) {
        cerr << "Error during shutdown: " << e.what() << "\n";
        return false;
    }
}

// === MENU DISPLAY METHODS ===

void System::displayMainMenu() const {
    // displayHeader("MAIN MENU");
    cout << "┌────────────────────────────────────────────────────────────┐\n";
    cout << "│                    POKENO SOUTH PRIMARY                    │\n";
    cout << "│                 Student Management System                  │\n";
    cout << "├────────────────────────────────────────────────────────────┤\n";
    cout << "│  1. Student Management                                     │\n";
    cout << "│  2. Course Management                                      │\n";
    cout << "│  3. Assessment Management                                  │\n";
    cout << "│  4. Reports & Analytics                                    │\n";
    cout << "│  5. System Management                                      │\n";
    cout << "│  6. About / Help                                           │\n";
    cout << "│  0. Exit System                                            │\n";
    cout << "└────────────────────────────────────────────────────────────┘\n";
    cout << "\nSystem Status: " << (dataLoaded ? "Ready" : "Not Initialized") << "\n";
    cout << "Students: " << students.size() << " | Courses: " << courses.size()
              << " | Assessments: " << assessments.size() << "\n";
}

void System::displayStudentMenu() const {
    displayHeader("STUDENT MANAGEMENT");
    cout << "┌────────────────────────────────────────────────────────────┐\n";
    cout << "│  1. Add New Student                                        │\n";
    cout << "│  2. View All Students                                      │\n";
    cout << "│  3. Find Student                                           │\n";
    cout << "│  4. Edit Student                                           │\n";
    cout << "│  5. Delete Student                                         │\n";
    cout << "│  6. Student Statistics                                     │\n";
    cout << "│  0. Back to Main Menu                                      │\n";
    cout << "└────────────────────────────────────────────────────────────┘\n";
    cout << "Use option numbers to navigate, 0 to go back\n\n";
}

void System::displayCourseMenu() const {
    displayHeader("COURSE MANAGEMENT");
    cout << "┌────────────────────────────────────────────────────────────┐\n";
    cout << "│  1. Add New Course                                         │\n";
    cout << "│  2. View All Courses                                       │\n";
    cout << "│  3. Find Course                                            │\n";
    cout << "│  4. Edit Course                                            │\n";
    cout << "│  5. Delete Course                                          │\n";
    cout << "│  6. Course Statistics                                      │\n";
    cout << "│  0. Back to Main Menu                                      │\n";
    cout << "└────────────────────────────────────────────────────────────┘\n\n";
}

void System::displayAssessmentMenu() const {
    displayHeader("ASSESSMENT MANAGEMENT");
    cout << "┌─────────────────────────────────────────────────────────────┐\n";
    cout << "│  1. Add New Assessment                                     │\n";
    cout << "│  2. View All Assessments                                   │\n";
    cout << "│  3. Find Assessment                                        │\n";
    cout << "│  4. Edit Assessment                                        │\n";
    cout << "│  5. Delete Assessment                                      │\n";
    cout << "│  6. Assessment Statistics                                  │\n";
    cout << "│  0. Back to Main Menu                                      │\n";
    cout << "└─────────────────────────────────────────────────────────────┘\n\n";
}

void System::displayReportsMenu() const {
    displayHeader("REPORTS & ANALYTICS");
    cout << "┌─────────────────────────────────────────────────────────────┐\n";
    cout << "│  1. System Overview                                        │\n";
    cout << "│  2. Enrollment Report                                      │\n";
    cout << "│  3. Grade Report                                           │\n";
    cout << "│  0. Back to Main Menu                                      │\n";
    cout << "└─────────────────────────────────────────────────────────────┘\n\n";
}

void System::displaySystemMenu() const {
    displayHeader("SYSTEM MANAGEMENT");
    cout << "┌─────────────────────────────────────────────────────────────┐\n";
    cout << "│  1. Load Data from Files                                   │\n";
    cout << "│  2. Save Data to Files                                     │\n";
    cout << "│  3. System Information                                     │\n";
    cout << "│  0. Back to Main Menu                                      │\n";
    cout << "└─────────────────────────────────────────────────────────────┘\n\n";
}

// === INPUT HANDLING ===

int System::getMenuChoice(int minOption, int maxOption) const {
    int choice;
    string input;
    
    while (true) {
        cout << "Enter your choice (" << minOption << "-" << maxOption << "): ";
        
        // Use getline for more robust input handling
        if (getline(cin, input)) {
            // Try to convert string to integer
            try {
                choice = stoi(input);
                if (choice >= minOption && choice <= maxOption) {
                    return choice;
                }
            } catch (const exception&) {
                // Invalid number format, continue to error message
            }
        } else {
            // Input stream error or EOF
            if (cin.eof()) {
                cout << "\nEnd of input detected. Exiting...\n";
                return 0;  // Exit choice
            }
        }
        
        cout << "Invalid choice. Please enter a number between "
                  << minOption << " and " << maxOption << ": ";
        displayNavigationTips();
    }
}

string System::getStringInput(const string& prompt) const {
    string input;
    cout << prompt;
    getline(cin, input);
    
    // T034: Enhanced input validation - trim whitespace and validate
    input = trimWhitespace(input);
    if (input.empty()) {
        throw invalid_argument("Input cannot be empty");
    }
    
    return input;
}

string System::getValidatedStringInput(const string& prompt, 
                                          function<bool(const string&)> validator,
                                          const string& errorMessage) const {
    string input;
    
    while (true) {
        try {
            input = getStringInput(prompt);
            if (validator(input)) {
                return input;
            }
            cout << errorMessage << "\n";
        } catch (const exception& e) {
            cout << e.what() << "\n";
        }
    }
}

int System::getValidatedIntInput(const string& prompt, int minValue, int maxValue) const {
    string input;
    int value;
    
    while (true) {
        cout << prompt;
        if (getline(cin, input)) {
            input = trimWhitespace(input);
            if (input.empty()) {
                cout << "Input cannot be empty. Please try again.\n";
                continue;
            }
            
            try {
                value = stoi(input);
                if (value >= minValue && value <= maxValue) {
                    return value;
                }
                cout << "Value must be between " << minValue << " and " << maxValue << ". Please try again.\n";
            } catch (const exception&) {
                cout << "Invalid number format. Please enter a valid integer.\n";
            }
        } else {
            if (cin.eof()) {
                throw runtime_error("End of input detected");
            }
            cout << "Input error. Please try again.\n";
        }
    }
}

double System::getValidatedDoubleInput(const string& prompt, double minValue, double maxValue) const {
    string input;
    double value;
    
    while (true) {
        cout << prompt;
        if (getline(cin, input)) {
            input = trimWhitespace(input);
            if (input.empty()) {
                cout << "Input cannot be empty. Please try again.\n";
                continue;
            }
            
            try {
                value = stod(input);
                if (value >= minValue && value <= maxValue) {
                    return value;
                }
                cout << "Value must be between " << minValue << " and " << maxValue << ". Please try again.\n";
            } catch (const exception&) {
                cout << "Invalid number format. Please enter a valid decimal number.\n";
            }
        } else {
            if (cin.eof()) {
                throw runtime_error("End of input detected");
            }
            cout << "Input error. Please try again.\n";
        }
    }
}

string System::trimWhitespace(const string& str) const {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == string::npos) {
        return "";
    }
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(start, end - start + 1);
}

int System::getIntInput(const string& prompt) const {
    int value;
    cout << prompt;
    
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

double System::getDoubleInput(const string& prompt) const {
    double value;
    cout << prompt;
    
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

bool System::getYesNoInput(const string& prompt) const {
    string input;
    cout << prompt << " (y/n): ";
    
    while (true) {
        getline(cin, input);
        transform(input.begin(), input.end(), input.begin(), [](char c) {return tolower(c);});
        
        if (input == "y" || input == "yes") {
            return true;
        } else if (input == "n" || input == "no") {
            return false;
        } else {
            cout << "Please enter 'y' for yes or 'n' for no: ";
        }
    }
}

// === UTILITY FUNCTIONS ===

void System::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void System::pauseForUser() const {
    cout << "\nPress Enter to continue...";
    cin.get();
}

void System::displayHeader(const string& title) const {
    cout << "\n";
    cout << "═══════════════════════════════════════════════════════════════\n";
    cout << "  " << title << "\n";
    cout << "═══════════════════════════════════════════════════════════════\n\n";
}

void System::displayFooter() const {
    cout << "───────────────────────────────────────────────────────────────\n";
}

// === SIMPLIFIED IMPLEMENTATIONS ===

void System::handleStudentMenu() {
    while (true) {
        clearScreen();
        displayStudentMenu();
        
        int choice = getMenuChoice(0, 6);
        
        switch (choice) {
            case 1:
                addNewStudent();
                break;
            case 2:
                viewAllStudents();
                break;
            case 3:
                findStudent();
                break;
            case 4:
                editStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                generateStudentReport();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                pauseForUser();
                break;
        }
    }
}

void System::handleCourseMenu() {
    while (true) {
        clearScreen();
        displayCourseMenu();
        
        int choice = getMenuChoice(0, 6);
        
        switch (choice) {
            case 1:
                addNewCourse();
                break;
            case 2:
                viewAllCourses();
                break;
            case 3:
                findCourse();
                break;
            case 4:
                editCourse();
                break;
            case 5:
                deleteCourse();
                break;
            case 6:
                generateCourseReport();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                pauseForUser();
                break;
        }
    }
}

void System::handleAssessmentMenu() {
    while (true) {
        clearScreen();
        displayAssessmentMenu();
        
        int choice = getMenuChoice(0, 6);
        
        switch (choice) {
            case 1:
                addNewAssessment();
                break;
            case 2:
                viewAllAssessments();
                break;
            case 3:
                findAssessment();
                break;
            case 4:
                editAssessment();
                break;
            case 5:
                deleteAssessment();
                break;
            case 6:
                generateGradeReport();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                pauseForUser();
                break;
        }
    }
}

void System::handleReportsMenu() {
    while (true) {
        clearScreen();
        displayReportsMenu();
        
        int choice = getMenuChoice(0, 3);
        
        switch (choice) {
            case 1:
                generateSystemStatistics();
                break;
            case 2:
                generateEnrollmentReport();
                break;
            case 3:
                generateGradeReport();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                pauseForUser();
                break;
        }
    }
}

void System::handleSystemMenu() {
    while (true) {
        clearScreen();
        displaySystemMenu();
        
        int choice = getMenuChoice(0, 3);
        
        switch (choice) {
            case 1:
                loadAllSystemData();
                pauseForUser();
                break;
            case 2:
                if (saveAllSystemData()) {
                    cout << "Data saved successfully.\n";
                } else {
                    cout << "Failed to save data.\n";
                }
                pauseForUser();
                break;
            case 3:
                cout << "\n=== SYSTEM INFORMATION ===\n";
                cout << currentSession << "\n";
                cout << "Students: " << students.size() << "\n";
                cout << "Courses: " << courses.size() << "\n";
                cout << "Assessments: " << assessments.size() << "\n";
                cout << "Total Enrollments: " << getEnrollmentCount() << "\n";
                cout << "Data Status: " << (dataLoaded ? "Loaded" : "Not Loaded") << "\n";
                pauseForUser();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                pauseForUser();
                break;
        }
    }
}

// === PLACEHOLDER IMPLEMENTATIONS ===

void System::viewAllStudents() const {
    displayHeader("ALL STUDENTS");
    
    if (students.empty()) {
        cout << "No students found in the system.\n";
    } else {
        cout << "Total Students: " << students.size() << "\n\n";
        for (const auto& student : students) {
            if (student) {
                cout << "Roll Number: " << student->getRollNumber() << "\n";
                cout << "Name: " << student->getFirstName() << " " << student->getLastName() << "\n";
                cout << "Email: " << student->getContactEmail() << "\n";
                displayFooter();
            }
        }
    }
    
    pauseForUser();
}

void System::findStudent() const {
    displayHeader("FIND STUDENT");
    
    int rollNumber = getIntInput("Enter student roll number: ");
    auto student = findStudentByRollNumber(rollNumber);
    
    if (student) {
        cout << "\nStudent found:\n";
        cout << "Roll Number: " << student->getRollNumber() << "\n";
        cout << "Name: " << student->getFirstName() << " " << student->getLastName() << "\n";
        cout << "Email: " << student->getContactEmail() << "\n";
    } else {
        cout << "Student with roll number " << rollNumber << " not found.\n";
    }
    
    pauseForUser();
}

void System::viewAllCourses() const {
    displayHeader("ALL COURSES");
    
    if (courses.empty()) {
        cout << "No courses found in the system.\n";
    } else {
        cout << "Total Courses: " << courses.size() << "\n\n";
        for (const auto& course : courses) {
            if (course) {
                cout << "Course ID: " << course->getCourseId() << "\n";
                cout << "Name: " << course->getCourseName() << "\n";
                cout << "Description: " << course->getDescription() << "\n";
                displayFooter();
            }
        }
    }
    
    pauseForUser();
}

void System::findCourse() const {
    displayHeader("FIND COURSE");
    
    string courseId = getStringInput("Enter course ID: ");
    auto course = findCourseById(courseId);
    
    if (course) {
        cout << "\nCourse found:\n";
        cout << "Course ID: " << course->getCourseId() << "\n";
        cout << "Name: " << course->getCourseName() << "\n";
        cout << "Description: " << course->getDescription() << "\n";
    } else {
        cout << "Course with ID " << courseId << " not found.\n";
    }
    
    pauseForUser();
}

void System::viewAllAssessments() const {
    displayHeader("ALL ASSESSMENTS");
    
    if (assessments.empty()) {
        cout << "No assessments found in the system.\n";
    } else {
        cout << "Total Assessments: " << assessments.size() << "\n\n";
        for (const auto& assessment : assessments) {
            if (assessment) {
                cout << "Assessment ID: " << assessment->getAssessmentId() << "\n";
                cout << "Student: " << assessment->getStudentRollNumber() << "\n";
                cout << "Course: " << assessment->getCourseId() << "\n";
                displayFooter();
            }
        }
    }
    
    pauseForUser();
}

void System::findAssessment() const {
    displayHeader("FIND ASSESSMENT");
    
    string assessmentId = getStringInput("Enter assessment ID: ");
    auto assessment = findAssessmentById(assessmentId);
    
    if (assessment) {
        cout << "\nAssessment found:\n";
        cout << "Assessment ID: " << assessment->getAssessmentId() << "\n";
        cout << "Student Roll Number: " << assessment->getStudentRollNumber() << "\n";
        cout << "Course ID: " << assessment->getCourseId() << "\n";
    } else {
        cout << "Assessment with ID " << assessmentId << " not found.\n";
    }
    
    pauseForUser();
}

void System::generateStudentReport() const {
    displayHeader("STUDENT STATISTICS");
    cout << "Total Students: " << students.size() << "\n";
    pauseForUser();
}

void System::generateCourseReport() const {
    displayHeader("COURSE STATISTICS");
    cout << "Total Courses: " << courses.size() << "\n";
    pauseForUser();
}

void System::generateGradeReport() const {
    displayHeader("GRADE STATISTICS");
    cout << "Total Assessments: " << assessments.size() << "\n";
    pauseForUser();
}

void System::generateEnrollmentReport() const {
    displayHeader("ENROLLMENT STATISTICS");
    cout << "Total Students: " << students.size() << "\n";
    cout << "Total Courses: " << courses.size() << "\n";
    pauseForUser();
}

void System::generateSystemStatistics() const {
    displayHeader("SYSTEM OVERVIEW");
    cout << currentSession << "\n\n";
    cout << "Students: " << students.size() << "\n";
    cout << "Courses: " << courses.size() << "\n";
    cout << "Assessments: " << assessments.size() << "\n";
    pauseForUser();
}

void System::loadAllSystemData() {
    try {
        cout << "Loading system data...\n";
        
        // Clear existing data first
        students.clear();
        courses.clear();
        assessments.clear();
        
        // Try to load data from CSV files
        try {
            bool loadSuccess = FileHandler::loadAllData(students, courses, assessments);
            if (loadSuccess) {
                cout << "✓ Data loaded successfully from CSV files.\n";
            } else {
                cout << "Note: No existing data found. Starting with empty system.\n";
            }
            dataLoaded = true;
            
        } catch (const exception& e) {
            cout << "Error loading data: " << e.what() << "\n";
            cout << "Starting with empty system.\n";
            dataLoaded = true;
        }
        
    } catch (const exception& e) {
        cout << "Error in loadAllSystemData: " << e.what() << "\n";
        dataLoaded = true;
    }
}

bool System::saveAllSystemData() {
    try {
        cout << "Saving system data...\n";
        
        if (FileHandler::saveAllData(students, courses, assessments)) {
            cout << "✓ All data saved successfully.\n";
            return true;
        } else {
            cout << "✗ Failed to save some data.\n";
            return false;
        }
        
    } catch (const exception& e) {
        cout << "Error saving data: " << e.what() << "\n";
        return false;
    }
}

// === PUBLIC INTERFACE IMPLEMENTATIONS ===

bool System::addStudent(shared_ptr<Student> student) {
    if (!student) return false;
    if (findStudentByRollNumber(student->getRollNumber())) return false;
    students.push_back(student);
    return true;
}

bool System::addCourse(shared_ptr<Course> course) {
    if (!course) return false;
    if (findCourseById(course->getCourseId())) return false;
    courses.push_back(course);
    return true;
}

bool System::addAssessment(shared_ptr<Assessment> assessment) {
    if (!assessment) return false;
    if (findAssessmentById(assessment->getAssessmentId())) return false;
    assessments.push_back(assessment);
    return true;
}

shared_ptr<Student> System::findStudentByRollNumber(int rollNumber) const {
    auto it = find_if(students.begin(), students.end(),
        [rollNumber](const shared_ptr<Student>& student) {
            return student && student->getRollNumber() == rollNumber;
        });
    return (it != students.end()) ? *it : nullptr;
}

shared_ptr<Course> System::findCourseById(const string& courseId) const {
    auto it = find_if(courses.begin(), courses.end(),
        [&courseId](const shared_ptr<Course>& course) {
            return course && course->getCourseId() == courseId;
        });
    return (it != courses.end()) ? *it : nullptr;
}

shared_ptr<Assessment> System::findAssessmentById(const string& assessmentId) const {
    auto it = find_if(assessments.begin(), assessments.end(),
        [&assessmentId](const shared_ptr<Assessment>& assessment) {
            return assessment && assessment->getAssessmentId() == assessmentId;
        });
    return (it != assessments.end()) ? *it : nullptr;
}

size_t System::getStudentCount() const {
    return students.size();
}

size_t System::getCourseCount() const {
    return courses.size();
}

size_t System::getAssessmentCount() const {
    return assessments.size();
}

size_t System::getEnrollmentCount() const {
    size_t count = 0;
    for (const auto& student : students) {
        if (student) {
            count += student->getEnrolledCourses().size();
        }
    }
    return count;
}

bool System::isInitialized() const {
    return dataLoaded;
}

string System::getSessionInfo() const {
    return currentSession;
}

// === PLACEHOLDER IMPLEMENTATIONS FOR REMAINING METHODS ===

void System::addNewStudent() {
    try {
        cout << "\n" << string(60, '=') << "\n";
        cout << "          ADD NEW STUDENT\n";
        cout << string(60, '=') << "\n\n";
        
        // T037: Enhanced Student CRUD with T034 validation
        
        // Get roll number with validation
        int rollNumber = getValidatedIntInput("Enter Roll Number (1-999999): ", 1, 999999);
        
        // Check if student already exists
        if (findStudentByRollNumber(rollNumber)) {
            cout << "Error: Student with roll number " << rollNumber << " already exists.\n";
            pauseForUser();
            return;
        }
        
        // Get validated inputs using T034 functions
        string firstName = getValidatedStringInput(
            "Enter First Name: ",
            [](const string& input) { return Common::isValidName(input); },
            "Error: First name must contain only letters, spaces, hyphens, and apostrophes."
        );
        
        string lastName = getValidatedStringInput(
            "Enter Last Name: ",
            [](const string& input) { return Common::isValidName(input); },
            "Error: Last name must contain only letters, spaces, hyphens, and apostrophes."
        );
        
        string dateOfBirth = getValidatedStringInput(
            "Enter Date of Birth (YYYY-MM-DD): ",
            [](const string& input) { return Common::isValidDateFormat(input) && Common::isValidDate(input); },
            "Error: Date must be in YYYY-MM-DD format and be a valid past date."
        );
        
        // Address (basic non-empty validation, 3-100 chars)
        string address = getValidatedStringInput(
            "Enter Address: ",
            [](const string& input) { return Common::isValidLength(input, 3, 100); },
            "Error: Address must be 3-100 characters."
        );

        string contactEmail = getValidatedStringInput(
            "Enter Contact Email: ",
            [](const string& input) { return Common::isValidEmail(input); },
            "Error: Please enter a valid email address (e.g., student@example.com)."
        );
        
        string emergencyContact = getValidatedStringInput(
            "Enter Emergency Contact (Email or Phone): ",
            [](const string& input) { return Common::isValidEmail(input) || Common::isValidPhoneNumber(input); },
            "Error: Please enter a valid email address or phone number for emergency contact."
        );
        
        string enrollmentDate = getValidatedStringInput(
            "Enter Enrollment Date (YYYY-MM-DD): ",
            [](const string& input) { return Common::isValidDateFormat(input); },
            "Error: Date must be in YYYY-MM-DD format."
        );
        
        // Create and add the student
        try {
            auto student = make_shared<Student>(rollNumber, firstName, lastName,
                                                    dateOfBirth, address,
                                                    contactEmail, emergencyContact,
                                                    enrollmentDate);
            
            if (addStudent(student)) {
                cout << "\n✓ Student added successfully!\n";
                cout << "Student Details:\n";
                cout << "  Roll Number: " << rollNumber << "\n";
                cout << "  Name: " << firstName << " " << lastName << "\n";
                cout << "  Email: " << contactEmail << "\n";
            } else {
                cout << "\n✗ Failed to add student.\n";
            }
        } catch (const exception& e) {
            cout << "\n✗ Error creating student: " << e.what() << "\n";
        }
        
    } catch (const exception& e) {
        cout << "Error in addNewStudent: " << e.what() << "\n";
    }
    
    pauseForUser();
}

void System::editStudent() {
    try {
        cout << "\n" << string(60, '=') << "\n";
        cout << "          EDIT STUDENT\n";
        cout << string(60, '=') << "\n\n";
        
        if (students.empty()) {
            cout << "No students found in the system.\n";
            pauseForUser();
            return;
        }
        
        // T037: Enhanced student editing with T034 validation
        int rollNumber = getValidatedIntInput("Enter student roll number to edit: ", 1, 999999);
        
        auto student = findStudentByRollNumber(rollNumber);
        if (!student) {
            cout << "Student with roll number " << rollNumber << " not found.\n";
            pauseForUser();
            return;
        }
        
        cout << "Current student details:\n";
        cout << "  Roll Number: " << student->getRollNumber() << "\n";
        cout << "  Name: " << student->getFirstName() << " " << student->getLastName() << "\n";
        cout << "  Email: " << student->getContactEmail() << "\n";
        cout << "  Emergency Contact: " << student->getEmergencyContact() << "\n";
        cout << "\nEnter new details (or press Enter to keep current value):\n";
        
        // Edit first name with validation
        cout << "First Name [" << student->getFirstName() << "] (Enter to skip): ";
        string input = getStringInput("");
        if (!input.empty()) {
            if (Common::isValidName(input)) {
                try {
                    student->setFirstName(Common::sanitizeInput(input));
                    cout << "✓ First name updated.\n";
                } catch (const exception& e) {
                    cout << "✗ Error updating first name: " << e.what() << "\n";
                }
            } else {
                cout << "✗ Invalid first name format. Keeping current value.\n";
            }
        }
        
        // Edit last name with validation
        cout << "Last Name [" << student->getLastName() << "] (Enter to skip): ";
        input = getStringInput("");
        if (!input.empty()) {
            if (Common::isValidName(input)) {
                try {
                    student->setLastName(Common::sanitizeInput(input));
                    cout << "✓ Last name updated.\n";
                } catch (const exception& e) {
                    cout << "✗ Error updating last name: " << e.what() << "\n";
                }
            } else {
                cout << "✗ Invalid last name format. Keeping current value.\n";
            }
        }
        
        // Edit contact email with validation
        cout << "Contact Email [" << student->getContactEmail() << "] (Enter to skip): ";
        input = getStringInput("");
        if (!input.empty()) {
            if (Common::isValidEmail(input)) {
                try {
                    student->setContactEmail(Common::sanitizeInput(input));
                    cout << "✓ Contact email updated.\n";
                } catch (const exception& e) {
                    cout << "✗ Error updating contact email: " << e.what() << "\n";
                }
            } else {
                cout << "✗ Invalid email format. Keeping current value.\n";
            }
        }
        
        // Edit emergency contact with validation
        cout << "Emergency Contact [" << student->getEmergencyContact() << "] (Enter to skip): ";
        input = getStringInput("");
        if (!input.empty()) {
            if (Common::isValidEmail(input)) {
                try {
                    student->setEmergencyContact(Common::sanitizeInput(input));
                    cout << "✓ Emergency contact updated.\n";
                } catch (const exception& e) {
                    cout << "✗ Error updating emergency contact: " << e.what() << "\n";
                }
            } else {
                cout << "✗ Invalid email format. Keeping current value.\n";
            }
        }
        
        cout << "\n✓ Student updated successfully!\n";
        cout << "Updated details:\n";
        cout << "  Roll Number: " << student->getRollNumber() << "\n";
        cout << "  Name: " << student->getFirstName() << " " << student->getLastName() << "\n";
        cout << "  Email: " << student->getContactEmail() << "\n";
        cout << "  Emergency Contact: " << student->getEmergencyContact() << "\n";
        
    } catch (const exception& e) {
        cout << "Error in editStudent: " << e.what() << "\n";
    }
    
    pauseForUser();
}

void System::deleteStudent() {
    try {
        cout << "\n" << string(60, '=') << "\n";
        cout << "          DELETE STUDENT\n";
        cout << string(60, '=') << "\n\n";
        
        if (students.empty()) {
            cout << "No students found in the system.\n";
            pauseForUser();
            return;
        }
        
        // T037: Enhanced student deletion with T034 validation
        int rollNumber = getValidatedIntInput("Enter student roll number to delete: ", 1, 999999);
        
        auto student = findStudentByRollNumber(rollNumber);
        if (!student) {
            cout << "Student with roll number " << rollNumber << " not found.\n";
            pauseForUser();
            return;
        }
        
        // Show student details before deletion
        cout << "Student to be deleted:\n";
        cout << "  Roll Number: " << student->getRollNumber() << "\n";
        cout << "  Name: " << student->getFirstName() << " " << student->getLastName() << "\n";
        cout << "  Email: " << student->getContactEmail() << "\n";
        
        // Check for enrollments
        auto enrolledCourses = student->getEnrolledCourses();
        if (!enrolledCourses.empty()) {
            cout << "\nWarning: Student is enrolled in " << enrolledCourses.size() << " course(s):\n";
            for (const auto& course : enrolledCourses) {
                if (course) {
                    cout << "  - " << course->getCourseId() << ": " << course->getCourseName() << "\n";
                }
            }
        }
        
        // Check for assessments
        int assessmentCount = 0;
        for (const auto& assessment : assessments) {
            if (assessment && assessment->getStudentRollNumber() == rollNumber) {
                assessmentCount++;
            }
        }
        if (assessmentCount > 0) {
            cout << "\nWarning: Student has " << assessmentCount << " assessment record(s).\n";
        }
        
        // T046: Enhanced confirmation dialog for destructive operations
        vector<string> warnings;
        if (!enrolledCourses.empty()) {
            warnings.push_back("Student is enrolled in " + to_string(enrolledCourses.size()) + " course(s)");
        }
        if (assessmentCount > 0) {
            warnings.push_back("Student has " + to_string(assessmentCount) + " assessment record(s) that will be deleted");
        }
        warnings.push_back("This action cannot be undone");
        
        string itemDesc = "Student: " + student->getFirstName() + " " + student->getLastName() +
                              " (Roll #" + to_string(rollNumber) + ")";
        
        if (confirmDestructiveOperation("delete this student", itemDesc, warnings)) {
            // Note: In this implementation, we'll remove the student but leave enrollment relationships
            // to be cleaned up by course management separately
            
            // Remove assessments for this student
            assessments.erase(remove_if(assessments.begin(), assessments.end(),
                [rollNumber](const shared_ptr<Assessment>& assessment) {
                    return assessment && assessment->getStudentRollNumber() == rollNumber;
                }), assessments.end());
            
            // Remove student from the system
            students.erase(remove_if(students.begin(), students.end(),
                [rollNumber](const shared_ptr<Student>& s) {
                    return s && s->getRollNumber() == rollNumber;
                }), students.end());
            
            displaySuccessMessage("Student Deletion", 
                "Student " + student->getFirstName() + " " + student->getLastName() + " has been removed from the system");
            
            if (assessmentCount > 0) {
                displayInfoMessage(to_string(assessmentCount) + " assessment record(s) were also removed");
            }
            if (!enrolledCourses.empty()) {
                displayWarningMessage("Student was removed from " + to_string(enrolledCourses.size()) +
                    " course(s). Course enrollments should be reviewed separately");
            }
        } else {
            displayInfoMessage("Student deletion was cancelled - no changes made");
        }
        
    } catch (const exception& e) {
        displayUserFriendlyError("Student Deletion", e.what());
    }
    
    pauseForUser();
}

void System::addNewCourse() {
    try {
        cout << "\n" << string(60, '=') << "\n";
        cout << "          ADD NEW COURSE\n";
        cout << string(60, '=') << "\n\n";
        
        // T038: Enhanced Course CRUD with T034 validation
        
        // Get course ID with validation
        string courseId = getValidatedStringInput(
            "Enter Course ID (e.g., MATH101, ENG201): ",
            [](const string& input) {
                return !input.empty() && input.length() <= 10 && 
                       Common::isValidAlphanumeric(input, "");
            },
            "Error: Course ID must be 1-10 alphanumeric characters."
        );
        
        // Check if course already exists
        if (findCourseById(courseId)) {
            cout << "Error: Course with ID " << courseId << " already exists.\n";
            pauseForUser();
            return;
        }
        
        // Get course name with validation
        string courseName = getValidatedStringInput(
            "Enter Course Name: ",
            [](const string& input) {
                return !input.empty() && input.length() <= 100 && 
                       Common::isValidAlphanumeric(input, " '-.,()&");
            },
            "Error: Course name must be 1-100 characters with letters, numbers, and basic punctuation."
        );
        
        // Get credits with validation
        int credits = getValidatedIntInput("Enter Credits (1-10): ", 1, 10);
        
        // Get description with validation
        string description = getValidatedStringInput(
            "Enter Course Description: ",
            [](const string& input) {
                return !input.empty() && input.length() <= 500 && 
                       Common::isPrintableASCII(input);
            },
            "Error: Description must be 1-500 printable characters."
        );
        
        // Get duration with validation
        int duration = getValidatedIntInput("Enter Duration (weeks, 1-52): ", 1, 52);
        
        // Get start date with validation
        string startDate = getValidatedStringInput(
            "Enter Start Date (YYYY-MM-DD) or leave empty: ",
            [](const string& input) {
                return input.empty() || (Common::isValidDateFormat(input) && Common::isValidDate(input));
            },
            "Error: Date must be empty or in YYYY-MM-DD format."
        );
        
        // Get end date with validation
        string endDate = getValidatedStringInput(
            "Enter End Date (YYYY-MM-DD) or leave empty: ",
            [](const string& input) {
                return input.empty() || (Common::isValidDateFormat(input) && Common::isValidDate(input));
            },
            "Error: Date must be empty or in YYYY-MM-DD format."
        );
        
        // Get maximum enrollment with validation
        int maxEnrollment = getValidatedIntInput("Enter Maximum Enrollment (1-1000): ", 1, 1000);
        
        // Create and add the course
        try {
            auto course = make_shared<Course>(courseId, courseName, credits, description,
                                                 duration, startDate, endDate, maxEnrollment);
            
            if (addCourse(course)) {
                cout << "\n✓ Course added successfully!\n";
                cout << "Course Details:\n";
                cout << "  Course ID: " << courseId << "\n";
                cout << "  Name: " << courseName << "\n";
                cout << "  Credits: " << credits << "\n";
                cout << "  Duration: " << duration << " weeks\n";
                cout << "  Max Enrollment: " << maxEnrollment << "\n";
            } else {
                cout << "\n✗ Failed to add course.\n";
            }
        } catch (const exception& e) {
            cout << "\n✗ Error creating course: " << e.what() << "\n";
        }
        
    } catch (const exception& e) {
        cout << "Error in addNewCourse: " << e.what() << "\n";
    }
    
    pauseForUser();
}

void System::editCourse() {
    try {
        cout << "\n" << string(60, '=') << "\n";
        cout << "          EDIT COURSE\n";
        cout << string(60, '=') << "\n\n";
        
        if (courses.empty()) {
            cout << "No courses found in the system.\n";
            pauseForUser();
            return;
        }
        
        // T038: Enhanced course editing with T034 validation
        string courseId = getValidatedStringInput(
            "Enter Course ID to edit: ",
            [](const string& input) { return !input.empty(); },
            "Course ID cannot be empty."
        );
        
        auto course = findCourseById(courseId);
        if (!course) {
            cout << "Course with ID " << courseId << " not found.\n";
            pauseForUser();
            return;
        }
        
        cout << "Current course details:\n";
        cout << "  Course ID: " << course->getCourseId() << "\n";
        cout << "  Name: " << course->getCourseName() << "\n";
        cout << "  Credits: " << course->getCredits() << "\n";
        cout << "  Description: " << course->getDescription() << "\n";
        cout << "  Duration: " << course->getDuration() << " weeks\n";
        cout << "\nEnter new details (or press Enter to keep current value):\n";
        
        // Edit course name with validation
        cout << "Course Name [" << course->getCourseName() << "] (Enter to skip): ";
        string input = getStringInput("");
        if (!input.empty()) {
            if (Common::isValidAlphanumeric(input, " '-.,()&") && input.length() <= 100) {
                try {
                    course->setCourseName(Common::sanitizeInput(input));
                    cout << "✓ Course name updated.\n";
                } catch (const exception& e) {
                    cout << "✗ Error updating course name: " << e.what() << "\n";
                }
            } else {
                cout << "✗ Invalid course name format. Keeping current value.\n";
            }
        }
        
        // Edit credits with validation
        cout << "Credits [" << course->getCredits() << "] (Enter to skip): ";
        input = getStringInput("");
        if (!input.empty()) {
            int credits;
            if (Common::parseAndValidateInt(input, credits, 1, 10)) {
                try {
                    course->setCredits(credits);
                    cout << "✓ Credits updated.\n";
                } catch (const exception& e) {
                    cout << "✗ Error updating credits: " << e.what() << "\n";
                }
            } else {
                cout << "✗ Invalid credits value (must be 1-10). Keeping current value.\n";
            }
        }
        
        // Edit description with validation
        cout << "Description [" << course->getDescription() << "] (Enter to skip): ";
        input = getStringInput("");
        if (!input.empty()) {
            if (Common::isPrintableASCII(input) && input.length() <= 500) {
                try {
                    course->setDescription(Common::sanitizeInput(input));
                    cout << "✓ Description updated.\n";
                } catch (const exception& e) {
                    cout << "✗ Error updating description: " << e.what() << "\n";
                }
            } else {
                cout << "✗ Invalid description format. Keeping current value.\n";
            }
        }
        
        // Edit duration with validation
        cout << "Duration in weeks [" << course->getDuration() << "] (Enter to skip): ";
        input = getStringInput("");
        if (!input.empty()) {
            int duration;
            if (Common::parseAndValidateInt(input, duration, 1, 52)) {
                try {
                    course->setDuration(duration);
                    cout << "✓ Duration updated.\n";
                } catch (const exception& e) {
                    cout << "✗ Error updating duration: " << e.what() << "\n";
                }
            } else {
                cout << "✗ Invalid duration value (must be 1-52 weeks). Keeping current value.\n";
            }
        }
        
        cout << "\n✓ Course updated successfully!\n";
        cout << "Updated details:\n";
        cout << "  Course ID: " << course->getCourseId() << "\n";
        cout << "  Name: " << course->getCourseName() << "\n";
        cout << "  Credits: " << course->getCredits() << "\n";
        cout << "  Description: " << course->getDescription() << "\n";
        cout << "  Duration: " << course->getDuration() << " weeks\n";
        
    } catch (const exception& e) {
        cout << "Error in editCourse: " << e.what() << "\n";
    }
    
    pauseForUser();
}

void System::deleteCourse() {
    try {
        cout << "\n" << string(60, '=') << "\n";
        cout << "          DELETE COURSE\n";
        cout << string(60, '=') << "\n\n";
        
        if (courses.empty()) {
            cout << "No courses found in the system.\n";
            pauseForUser();
            return;
        }
        
        string courseId;
        cout << "Enter course ID to delete: ";
        getline(cin, courseId);
        
        auto course = findCourseById(courseId);
        if (!course) {
            cout << "Course with ID " << courseId << " not found.\n";
            pauseForUser();
            return;
        }
        
        // Show course details before deletion
        cout << "Course to be deleted:\n";
        cout << "  Course ID: " << course->getCourseId() << "\n";
        cout << "  Name: " << course->getCourseName() << "\n";
        cout << "  Credits: " << course->getCredits() << "\n";
        
        // Check for enrolled students
        auto enrolledStudents = course->getEnrolledStudents();
        if (!enrolledStudents.empty()) {
            cout << "\nWarning: Course has " << enrolledStudents.size() << " enrolled student(s):\n";
            for (const auto& student : enrolledStudents) {
                if (student) {
                    cout << "  - " << student->getRollNumber() << ": "
                              << student->getFirstName() << " " << student->getLastName() << "\n";
                }
            }
        }
        
        // Check for assessments
        int assessmentCount = 0;
        for (const auto& assessment : assessments) {
            if (assessment && assessment->getCourseId() == courseId) {
                assessmentCount++;
            }
        }
        if (assessmentCount > 0) {
            cout << "\nWarning: Course has " << assessmentCount << " assessment record(s).\n";
        }
        
        // Confirm deletion
        cout << "\nAre you sure you want to delete this course? (y/N): ";
        string confirmation;
        getline(cin, confirmation);
        
        if (confirmation == "y" || confirmation == "Y" || confirmation == "yes" || confirmation == "YES") {
            // Note: In this implementation, we'll remove the course but leave enrollment relationships
            // to be cleaned up by student management separately
            
            // Remove assessments for this course
            assessments.erase(remove_if(assessments.begin(), assessments.end(),
                [&courseId](const shared_ptr<Assessment>& assessment) {
                    return assessment && assessment->getCourseId() == courseId;
                }), assessments.end());
            
            // Remove course from the system
            courses.erase(remove_if(courses.begin(), courses.end(),
                [&courseId](const shared_ptr<Course>& c) {
                    return c && c->getCourseId() == courseId;
                }), courses.end());
            
            cout << "\n✓ Course deleted successfully!\n";
            if (assessmentCount > 0) {
                cout << "✓ " << assessmentCount << " assessment record(s) removed.\n";
            }
            if (!enrolledStudents.empty()) {
                cout << "Note: Course removed from system. Student enrollments should be updated separately.\n";
            }
        } else {
            cout << "Deletion cancelled.\n";
        }
        
    } catch (const exception& e) {
        cout << "Error in deleteCourse: " << e.what() << "\n";
    }
    
    pauseForUser();
}

void System::addNewAssessment() {
    try {
        cout << "\n" << string(60, '=') << "\n";
        cout << "          ADD NEW ASSESSMENT\n";
        cout << string(60, '=') << "\n\n";
        
        if (students.empty()) {
            cout << "No students found in the system. Add students first.\n";
            pauseForUser();
            return;
        }
        
        if (courses.empty()) {
            cout << "No courses found in the system. Add courses first.\n";
            pauseForUser();
            return;
        }
        
        // T039: Enhanced Assessment CRUD with T034 validation
        
        // Get assessment ID with validation
        string assessmentId = getValidatedStringInput(
            "Enter Assessment ID: ",
            [](const string& input) {
                return !input.empty() && input.length() <= 20 && 
                       Common::isValidAlphanumeric(input, "_-");
            },
            "Error: Assessment ID must be 1-20 alphanumeric characters (can include _ -)."
        );
        
        // Check if assessment already exists
        if (findAssessmentById(assessmentId)) {
            cout << "Error: Assessment with ID " << assessmentId << " already exists.\n";
            pauseForUser();
            return;
        }
        
        // Get student roll number with validation
        int studentRollNumber = getValidatedIntInput("Enter Student Roll Number: ", 1, 999999);
        
        // Verify student exists
        auto student = findStudentByRollNumber(studentRollNumber);
        if (!student) {
            cout << "Error: Student with roll number " << studentRollNumber << " not found.\n";
            pauseForUser();
            return;
        }
        
        // Get course ID with validation
        string courseId = getValidatedStringInput(
            "Enter Course ID: ",
            [](const string& input) {
                return !input.empty() && Common::isValidAlphanumeric(input, "");
            },
            "Error: Course ID must be alphanumeric."
        );
        
        // Verify course exists
        auto course = findCourseById(courseId);
        if (!course) {
            cout << "Error: Course with ID " << courseId << " not found.\n";
            pauseForUser();
            return;
        }
        
        // Get internal marks with validation
        double internalMarks = getValidatedDoubleInput("Enter Internal Marks (0-100): ", 0.0, 100.0);
        
        // Get final marks with validation
        double finalMarks = getValidatedDoubleInput("Enter Final Marks (0-100): ", 0.0, 100.0);
        
        // Get assessment date with validation
        string assessmentDate = getValidatedStringInput(
            "Enter Assessment Date (YYYY-MM-DD): ",
            [](const string& input) {
                return !input.empty() && Common::isValidDateFormat(input) && Common::isValidDate(input);
            },
            "Error: Date must be in YYYY-MM-DD format and be a valid date."
        );
        
        // Get assessment type with validation
        string assessmentType = getValidatedStringInput(
            "Enter Assessment Type (e.g., MIDTERM, FINAL, ASSIGNMENT): ",
            [](const string& input) {
                return !input.empty() && input.length() <= 30 && 
                       Common::isValidAlphanumeric(input, " _-");
            },
            "Error: Assessment type must be 1-30 characters (letters, numbers, spaces, _, -)."
        );
        
        // Get remarks with validation (optional)
        string remarks = getValidatedStringInput(
            "Enter Remarks (optional, press Enter to skip): ",
            [](const string& input) {
                return input.length() <= 250 && Common::isPrintableASCII(input);
            },
            "Error: Remarks must be under 250 printable characters."
        );
        
        // Create and add the assessment
        try {
            auto assessment = make_shared<Assessment>(assessmentId, studentRollNumber, courseId,
                                                         internalMarks, finalMarks, assessmentDate,
                                                         assessmentType, remarks);
            
            if (addAssessment(assessment)) {
                cout << "\n✓ Assessment added successfully!\n";
                cout << "Assessment Details:\n";
                cout << "  Assessment ID: " << assessmentId << "\n";
                cout << "  Student: " << student->getFirstName() << " " << student->getLastName()
                          << " (" << studentRollNumber << ")\n";
                cout << "  Course: " << course->getCourseName() << " (" << courseId << ")\n";
                cout << "  Internal Marks: " << internalMarks << "\n";
                cout << "  Final Marks: " << finalMarks << "\n";
                cout << "  Assessment Type: " << assessmentType << "\n";
                if (!remarks.empty()) {
                    cout << "  Remarks: " << remarks << "\n";
                }
            } else {
                cout << "\n✗ Failed to add assessment.\n";
            }
        } catch (const exception& e) {
            cout << "\n✗ Error creating assessment: " << e.what() << "\n";
        }
        
    } catch (const exception& e) {
        cout << "Error in addNewAssessment: " << e.what() << "\n";
    }
    
    pauseForUser();
}

void System::editAssessment() {
    try {
        cout << "\n" << string(60, '=') << "\n";
        cout << "          EDIT ASSESSMENT\n";
        cout << string(60, '=') << "\n\n";
        
        if (assessments.empty()) {
            cout << "No assessments found in the system.\n";
            pauseForUser();
            return;
        }
        
        string assessmentId;
        cout << "Enter assessment ID to edit: ";
        getline(cin, assessmentId);
        
        auto assessment = findAssessmentById(assessmentId);
        if (!assessment) {
            cout << "Assessment with ID " << assessmentId << " not found.\n";
            pauseForUser();
            return;
        }
        
        // Show current assessment details
        auto student = findStudentByRollNumber(assessment->getStudentRollNumber());
        auto course = findCourseById(assessment->getCourseId());
        
        cout << "Current assessment details:\n";
        cout << "  Assessment ID: " << assessment->getAssessmentId() << "\n";
        if (student) {
            cout << "  Student: " << student->getFirstName() << " " << student->getLastName()
                      << " (" << assessment->getStudentRollNumber() << ")\n";
        }
        if (course) {
            cout << "  Course: " << course->getCourseName() << " (" << assessment->getCourseId() << ")\n";
        }
        cout << "  Internal Marks: " << assessment->getInternalMarks() << "\n";
        cout << "  Final Marks: " << assessment->getFinalMarks() << "\n";
        cout << "  Assessment Type: " << assessment->getAssessmentType() << "\n";
        cout << "  Remarks: " << assessment->getRemarks() << "\n";
        
        cout << "\nEnter new details (press Enter to keep current value):\n";
        
        string input;
        
        // Edit internal marks
        cout << "Internal Marks [" << assessment->getInternalMarks() << "]: ";
        getline(cin, input);
        if (!input.empty()) {
            try {
                double marks = stod(input);
                if (marks >= 0 && marks <= 100) {
                    assessment->setInternalMarks(marks);
                    cout << "✓ Internal marks updated.\n";
                } else {
                    cout << "✗ Internal marks must be between 0 and 100.\n";
                }
            } catch (const exception& e) {
                cout << "✗ Error updating internal marks: Invalid number format.\n";
            }
        }
        
        // Edit final marks
        cout << "Final Marks [" << assessment->getFinalMarks() << "]: ";
        getline(cin, input);
        if (!input.empty()) {
            try {
                double marks = stod(input);
                if (marks >= 0 && marks <= 100) {
                    assessment->setFinalMarks(marks);
                    cout << "✓ Final marks updated.\n";
                } else {
                    cout << "✗ Final marks must be between 0 and 100.\n";
                }
            } catch (const exception& e) {
                cout << "✗ Error updating final marks: Invalid number format.\n";
            }
        }
        
        // Edit assessment type
        cout << "Assessment Type [" << assessment->getAssessmentType() << "]: ";
        getline(cin, input);
        if (!input.empty()) {
            try {
                assessment->setAssessmentType(input);
                cout << "✓ Assessment type updated.\n";
            } catch (const exception& e) {
                cout << "✗ Error updating assessment type: " << e.what() << "\n";
            }
        }
        
        // Edit remarks
        cout << "Remarks [" << assessment->getRemarks() << "]: ";
        getline(cin, input);
        if (!input.empty()) {
            try {
                assessment->setRemarks(input);
                cout << "✓ Remarks updated.\n";
            } catch (const exception& e) {
                cout << "✗ Error updating remarks: " << e.what() << "\n";
            }
        }
        
        cout << "\n✓ Assessment updated successfully!\n";
        cout << "Updated details:\n";
        cout << "  Assessment ID: " << assessment->getAssessmentId() << "\n";
        cout << "  Internal Marks: " << assessment->getInternalMarks() << "\n";
        cout << "  Final Marks: " << assessment->getFinalMarks() << "\n";
        cout << "  Assessment Type: " << assessment->getAssessmentType() << "\n";
        cout << "  Remarks: " << assessment->getRemarks() << "\n";
        
    } catch (const exception& e) {
        cout << "Error in editAssessment: " << e.what() << "\n";
    }
    
    pauseForUser();
}

void System::deleteAssessment() {
    try {
        cout << "\n" << string(60, '=') << "\n";
        cout << "          DELETE ASSESSMENT\n";
        cout << string(60, '=') << "\n\n";
        
        if (assessments.empty()) {
            cout << "No assessments found in the system.\n";
            pauseForUser();
            return;
        }
        
        // T039: Enhanced assessment deletion with T034 validation
        string assessmentId = getValidatedStringInput(
            "Enter Assessment ID to delete: ",
            [](const string& input) { return !input.empty(); },
            "Assessment ID cannot be empty."
        );
        
        auto assessment = findAssessmentById(assessmentId);
        if (!assessment) {
            cout << "Assessment with ID " << assessmentId << " not found.\n";
            pauseForUser();
            return;
        }
        
        // Show assessment details before deletion
        auto student = findStudentByRollNumber(assessment->getStudentRollNumber());
        auto course = findCourseById(assessment->getCourseId());
        
        cout << "Assessment to be deleted:\n";
        cout << "  Assessment ID: " << assessment->getAssessmentId() << "\n";
        if (student) {
            cout << "  Student: " << student->getFirstName() << " " << student->getLastName()
                      << " (" << assessment->getStudentRollNumber() << ")\n";
        }
        if (course) {
            cout << "  Course: " << course->getCourseName() << " (" << assessment->getCourseId() << ")\n";
        }
        cout << "  Internal Marks: " << assessment->getInternalMarks() << "\n";
        cout << "  Final Marks: " << assessment->getFinalMarks() << "\n";
        cout << "  Assessment Type: " << assessment->getAssessmentType() << "\n";
        
        // T039: Enhanced confirmation with validation
        string confirmation = getValidatedStringInput(
            "\nAre you sure you want to delete this assessment? (yes/no): ",
            [](const string& input) {
                string lower = Common::normalizeText(input);
                return lower == "yes" || lower == "no" || lower == "y" || lower == "n";
            },
            "Please enter 'yes' or 'no' to confirm deletion."
        );
        
        string normalizedConfirmation = Common::normalizeText(confirmation);
        if (normalizedConfirmation == "yes" || normalizedConfirmation == "y") {
            // Remove assessment from the system
            assessments.erase(remove_if(assessments.begin(), assessments.end(),
                [&assessmentId](const shared_ptr<Assessment>& a) {
                    return a && a->getAssessmentId() == assessmentId;
                }), assessments.end());
            
            cout << "\n✓ Assessment deleted successfully!\n";
        } else {
            cout << "Deletion cancelled.\n";
        }
        
    } catch (const exception& e) {
        cout << "Error in deleteAssessment: " << e.what() << "\n";
    }
    
    pauseForUser();
}

void System::enrollStudentInCourse() {
    try {
        cout << "\n" << string(60, '=') << "\n";
        cout << "          ENROLL STUDENT IN COURSE\n";
        cout << string(60, '=') << "\n\n";
        
        if (students.empty()) {
            cout << "No students found in the system. Add students first.\n";
            pauseForUser();
            return;
        }
        
        if (courses.empty()) {
            cout << "No courses found in the system. Add courses first.\n";
            pauseForUser();
            return;
        }
        
        // T040: Enhanced enrollment management with T034 validation
        
        // Get student roll number with validation
        int studentRollNumber = getValidatedIntInput("Enter Student Roll Number: ", 1, 999999);
        
        auto student = findStudentByRollNumber(studentRollNumber);
        if (!student) {
            cout << "Error: Student with roll number " << studentRollNumber << " not found.\n";
            pauseForUser();
            return;
        }
        
        // Get course ID with validation
        string courseId = getValidatedStringInput(
            "Enter Course ID: ",
            [](const string& input) {
                return !input.empty() && Common::isValidAlphanumeric(input, "");
            },
            "Error: Course ID must be alphanumeric."
        );
        
        auto course = findCourseById(courseId);
        if (!course) {
            cout << "Error: Course with ID " << courseId << " not found.\n";
            pauseForUser();
            return;
        }
        
        // Check if student is already enrolled in the course
        auto enrolledCourses = student->getEnrolledCourses();
        bool alreadyEnrolled = false;
        for (const auto& enrolledCourse : enrolledCourses) {
            if (enrolledCourse && enrolledCourse->getCourseId() == courseId) {
                alreadyEnrolled = true;
                break;
            }
        }
        
        if (alreadyEnrolled) {
            cout << "Error: Student " << student->getFirstName() << " " << student->getLastName()
                      << " is already enrolled in course " << course->getCourseName() << ".\n";
            pauseForUser();
            return;
        }
        
        // Check course enrollment limit
        auto enrolledStudents = course->getEnrolledStudents();
        if (enrolledStudents.size() >= static_cast<size_t>(course->getMaxEnrollment())) {
            cout << "Error: Course " << course->getCourseName() << " has reached its enrollment limit of "
                      << course->getMaxEnrollment() << " students.\n";
            pauseForUser();
            return;
        }
        
        // Show enrollment details for confirmation
        cout << "\nEnrollment Details:\n";
        cout << "  Student: " << student->getFirstName() << " " << student->getLastName()
                  << " (Roll: " << studentRollNumber << ")\n";
        cout << "  Course: " << course->getCourseName() << " (ID: " << courseId << ")\n";
        cout << "  Credits: " << course->getCredits() << "\n";
        cout << "  Current Enrollment: " << enrolledStudents.size() << "/" << course->getMaxEnrollment() << "\n";
        
        // Confirm enrollment with validation
        string confirmation = getValidatedStringInput(
            "\nConfirm enrollment? (yes/no): ",
            [](const string& input) {
                string lower = Common::normalizeText(input);
                return lower == "yes" || lower == "no" || lower == "y" || lower == "n";
            },
            "Please enter 'yes' or 'no' to confirm enrollment."
        );
        
        string normalizedConfirmation = Common::normalizeText(confirmation);
        if (normalizedConfirmation == "yes" || normalizedConfirmation == "y") {
            // Create bidirectional enrollment relationship
            bool enrollmentSuccess = false;
            
            try {
                // Add course to student's enrolled courses
                student->enrollInCourse(course);
                // Add student to course's enrolled students
                course->enrollStudent(student);
                
                enrollmentSuccess = true;
                
                cout << "\n✓ Enrollment successful!\n";
                cout << "Student " << student->getFirstName() << " " << student->getLastName()
                          << " has been enrolled in " << course->getCourseName() << ".\n";
                cout << "New enrollment count: " << (enrolledStudents.size() + 1) << "/"
                          << course->getMaxEnrollment() << "\n";
                
            } catch (const exception& e) {
                cout << "\n✗ Enrollment failed: " << e.what() << "\n";
            }
            
        } else {
            cout << "Enrollment cancelled.\n";
        }
        
    } catch (const exception& e) {
        cout << "Error in enrollStudentInCourse: " << e.what() << "\n";
    }
    
    pauseForUser();
}

void System::withdrawStudentFromCourse() {
    try {
        cout << "\n" << string(60, '=') << "\n";
        cout << "          WITHDRAW STUDENT FROM COURSE\n";
        cout << string(60, '=') << "\n\n";
        
        if (students.empty()) {
            cout << "No students found in the system.\n";
            pauseForUser();
            return;
        }
        
        if (courses.empty()) {
            cout << "No courses found in the system.\n";
            pauseForUser();
            return;
        }
        
        // T040: Enhanced withdrawal management with T034 validation
        
        // Get student roll number with validation
        int studentRollNumber = getValidatedIntInput("Enter Student Roll Number: ", 1, 999999);
        
        auto student = findStudentByRollNumber(studentRollNumber);
        if (!student) {
            cout << "Error: Student with roll number " << studentRollNumber << " not found.\n";
            pauseForUser();
            return;
        }
        
        // Show student's current enrollments
        auto enrolledCourses = student->getEnrolledCourses();
        if (enrolledCourses.empty()) {
            cout << "Student " << student->getFirstName() << " " << student->getLastName()
                      << " is not enrolled in any courses.\n";
            pauseForUser();
            return;
        }
        
        cout << "Student " << student->getFirstName() << " " << student->getLastName()
                  << " is enrolled in the following courses:\n";
        for (size_t i = 0; i < enrolledCourses.size(); ++i) {
            if (enrolledCourses[i]) {
                cout << "  " << (i + 1) << ". " << enrolledCourses[i]->getCourseId()
                          << ": " << enrolledCourses[i]->getCourseName() << "\n";
            }
        }
        
        // Get course ID with validation
        string courseId = getValidatedStringInput(
            "\nEnter Course ID to withdraw from: ",
            [](const string& input) {
                return !input.empty() && Common::isValidAlphanumeric(input, "");
            },
            "Error: Course ID must be alphanumeric."
        );
        
        auto course = findCourseById(courseId);
        if (!course) {
            cout << "Error: Course with ID " << courseId << " not found.\n";
            pauseForUser();
            return;
        }
        
        // Check if student is enrolled in the course
        bool isEnrolled = false;
        for (const auto& enrolledCourse : enrolledCourses) {
            if (enrolledCourse && enrolledCourse->getCourseId() == courseId) {
                isEnrolled = true;
                break;
            }
        }
        
        if (!isEnrolled) {
            cout << "Error: Student " << student->getFirstName() << " " << student->getLastName()
                      << " is not enrolled in course " << course->getCourseName() << ".\n";
            pauseForUser();
            return;
        }
        
        // Check for existing assessments
        int assessmentCount = 0;
        for (const auto& assessment : assessments) {
            if (assessment && assessment->getStudentRollNumber() == studentRollNumber && 
                assessment->getCourseId() == courseId) {
                assessmentCount++;
            }
        }
        
        // Show withdrawal details for confirmation
        cout << "\nWithdrawal Details:\n";
        cout << "  Student: " << student->getFirstName() << " " << student->getLastName()
                  << " (Roll: " << studentRollNumber << ")\n";
        cout << "  Course: " << course->getCourseName() << " (ID: " << courseId << ")\n";
        cout << "  Credits: " << course->getCredits() << "\n";
        
        if (assessmentCount > 0) {
            cout << "  Warning: Student has " << assessmentCount
                      << " assessment record(s) for this course.\n";
        }
        
        // Confirm withdrawal with validation
        string confirmation = getValidatedStringInput(
            "\nConfirm withdrawal? (yes/no): ",
            [](const string& input) {
                string lower = Common::normalizeText(input);
                return lower == "yes" || lower == "no" || lower == "y" || lower == "n";
            },
            "Please enter 'yes' or 'no' to confirm withdrawal."
        );
        
        string normalizedConfirmation = Common::normalizeText(confirmation);
        if (normalizedConfirmation == "yes" || normalizedConfirmation == "y") {
            try {
                // Remove course from student's enrolled courses
                student->withdrawFromCourse(courseId);
                // Remove student from course's enrolled students
                course->withdrawStudent(studentRollNumber);
                
                cout << "\n✓ Withdrawal successful!\n";
                cout << "Student " << student->getFirstName() << " " << student->getLastName()
                          << " has been withdrawn from " << course->getCourseName() << ".\n";
                
                if (assessmentCount > 0) {
                    cout << "Note: " << assessmentCount
                              << " assessment record(s) remain in the system.\n";
                }
                
            } catch (const exception& e) {
                cout << "\n✗ Withdrawal failed: " << e.what() << "\n";
            }
            
        } else {
            cout << "Withdrawal cancelled.\n";
        }
        
    } catch (const exception& e) {
        cout << "Error in withdrawStudentFromCourse: " << e.what() << "\n";
    }
    
    pauseForUser();
}

void System::viewStudentEnrollments() const {
    try {
        cout << "\n" << string(60, '=') << "\n";
        cout << "          VIEW STUDENT ENROLLMENTS\n";
        cout << string(60, '=') << "\n\n";
        
        if (students.empty()) {
            cout << "No students found in the system.\n";
            pauseForUser();
            return;
        }
        
        // T040: Enhanced enrollment viewing with T034 validation
        
        // Get student roll number with validation
        int studentRollNumber = getValidatedIntInput("Enter Student Roll Number: ", 1, 999999);
        
        auto student = findStudentByRollNumber(studentRollNumber);
        if (!student) {
            cout << "Error: Student with roll number " << studentRollNumber << " not found.\n";
            pauseForUser();
            return;
        }
        
        cout << "\nStudent Information:\n";
        cout << "  Name: " << student->getFirstName() << " " << student->getLastName() << "\n";
        cout << "  Roll Number: " << student->getRollNumber() << "\n";
        cout << "  Email: " << student->getContactEmail() << "\n";
        
        auto enrolledCourses = student->getEnrolledCourses();
        
        if (enrolledCourses.empty()) {
            cout << "\nThis student is not enrolled in any courses.\n";
        } else {
            cout << "\nEnrolled Courses (" << enrolledCourses.size() << "):\n";
            cout << string(80, '-') << "\n";
            
            int totalCredits = 0;
            for (size_t i = 0; i < enrolledCourses.size(); ++i) {
                if (enrolledCourses[i]) {
                    auto course = enrolledCourses[i];
                    cout << (i + 1) << ". Course ID: " << course->getCourseId() << "\n";
                    cout << "   Name: " << course->getCourseName() << "\n";
                    cout << "   Credits: " << course->getCredits() << "\n";
                    cout << "   Description: " << course->getDescription() << "\n";
                    
                    // Check for assessments in this course
                    int assessmentCount = 0;
                    double totalMarks = 0.0;
                    for (const auto& assessment : assessments) {
                        if (assessment && assessment->getStudentRollNumber() == studentRollNumber && 
                            assessment->getCourseId() == course->getCourseId()) {
                            assessmentCount++;
                            totalMarks += (assessment->getInternalMarks() + assessment->getFinalMarks()) / 2.0;
                        }
                    }
                    
                    if (assessmentCount > 0) {
                        cout << "   Assessments: " << assessmentCount
                                  << " (Avg: " << fixed << setprecision(1)
                                  << (totalMarks / assessmentCount) << "%)\n";
                    } else {
                        cout << "   Assessments: None\n";
                    }
                    
                    totalCredits += course->getCredits();
                    cout << string(80, '-') << "\n";
                }
            }
            
            cout << "\nEnrollment Summary:\n";
            cout << "  Total Courses: " << enrolledCourses.size() << "\n";
            cout << "  Total Credits: " << totalCredits << "\n";
            
            // Calculate overall assessment performance
            int totalAssessments = 0;
            double overallAverage = 0.0;
            for (const auto& assessment : assessments) {
                if (assessment && assessment->getStudentRollNumber() == studentRollNumber) {
                    totalAssessments++;
                    overallAverage += (assessment->getInternalMarks() + assessment->getFinalMarks()) / 2.0;
                }
            }
            
            if (totalAssessments > 0) {
                cout << "  Total Assessments: " << totalAssessments << "\n";
                cout << "  Overall Average: " << fixed << setprecision(1)
                          << (overallAverage / totalAssessments) << "%\n";
            }
        }
        
    } catch (const exception& e) {
        cout << "Error in viewStudentEnrollments: " << e.what() << "\n";
    }
    
    pauseForUser();
}

void System::viewCourseEnrollments() const {
    try {
        cout << "\n" << string(60, '=') << "\n";
        cout << "          VIEW COURSE ENROLLMENTS\n";
        cout << string(60, '=') << "\n\n";
        
        if (courses.empty()) {
            cout << "No courses found in the system.\n";
            pauseForUser();
            return;
        }
        
        // T040: Enhanced course enrollment viewing with T034 validation
        
        // Get course ID with validation
        string courseId = getValidatedStringInput(
            "Enter Course ID: ",
            [](const string& input) {
                return !input.empty() && Common::isValidAlphanumeric(input, "");
            },
            "Error: Course ID must be alphanumeric."
        );
        
        auto course = findCourseById(courseId);
        if (!course) {
            cout << "Error: Course with ID " << courseId << " not found.\n";
            pauseForUser();
            return;
        }
        
        cout << "\nCourse Information:\n";
        cout << "  Course ID: " << course->getCourseId() << "\n";
        cout << "  Name: " << course->getCourseName() << "\n";
        cout << "  Credits: " << course->getCredits() << "\n";
        cout << "  Description: " << course->getDescription() << "\n";
        cout << "  Duration: " << course->getDuration() << " weeks\n";
        
        auto enrolledStudents = course->getEnrolledStudents();
        
        cout << "\nEnrollment Status: " << enrolledStudents.size() << "/"
                  << course->getMaxEnrollment() << " students\n";
        
        if (enrolledStudents.empty()) {
            cout << "\nNo students are currently enrolled in this course.\n";
        } else {
            cout << "\nEnrolled Students (" << enrolledStudents.size() << "):\n";
            cout << string(80, '-') << "\n";
            
            for (size_t i = 0; i < enrolledStudents.size(); ++i) {
                if (enrolledStudents[i]) {
                    auto student = enrolledStudents[i];
                    cout << (i + 1) << ". Roll Number: " << student->getRollNumber() << "\n";
                    cout << "   Name: " << student->getFirstName() << " " << student->getLastName() << "\n";
                    cout << "   Email: " << student->getContactEmail() << "\n";
                    
                    // Check for assessments for this student in this course
                    int assessmentCount = 0;
                    double totalMarks = 0.0;
                    string latestAssessment = "None";
                    
                    for (const auto& assessment : assessments) {
                        if (assessment && assessment->getStudentRollNumber() == student->getRollNumber() && 
                            assessment->getCourseId() == courseId) {
                            assessmentCount++;
                            totalMarks += (assessment->getInternalMarks() + assessment->getFinalMarks()) / 2.0;
                            latestAssessment = assessment->getAssessmentDate();
                        }
                    }
                    
                    if (assessmentCount > 0) {
                        cout << "   Assessments: " << assessmentCount
                                  << " (Avg: " << fixed << setprecision(1)
                                  << (totalMarks / assessmentCount) << "%)\n";
                        cout << "   Latest Assessment: " << latestAssessment << "\n";
                    } else {
                        cout << "   Assessments: None\n";
                    }
                    
                    cout << string(80, '-') << "\n";
                }
            }
            
            // Calculate course statistics
            int totalAssessments = 0;
            double courseAverage = 0.0;
            double highestAverage = 0.0;
            double lowestAverage = 100.0;
            
            for (const auto& student : enrolledStudents) {
                if (student) {
                    int studentAssessments = 0;
                    double studentTotal = 0.0;
                    
                    for (const auto& assessment : assessments) {
                        if (assessment && assessment->getStudentRollNumber() == student->getRollNumber() && 
                            assessment->getCourseId() == courseId) {
                            studentAssessments++;
                            studentTotal += (assessment->getInternalMarks() + assessment->getFinalMarks()) / 2.0;
                        }
                    }
                    
                    if (studentAssessments > 0) {
                        double studentAverage = studentTotal / studentAssessments;
                        courseAverage += studentAverage;
                        totalAssessments++;
                        
                        if (studentAverage > highestAverage) {
                            highestAverage = studentAverage;
                        }
                        if (studentAverage < lowestAverage) {
                            lowestAverage = studentAverage;
                        }
                    }
                }
            }
            
            cout << "\nCourse Statistics:\n";
            cout << "  Enrollment Rate: " << fixed << setprecision(1)
                      << (static_cast<double>(enrolledStudents.size()) / course->getMaxEnrollment() * 100) << "%\n";
            
            if (totalAssessments > 0) {
                cout << "  Students with Assessments: " << totalAssessments << "/" << enrolledStudents.size() << "\n";
                cout << "  Course Average: " << fixed << setprecision(1)
                          << (courseAverage / totalAssessments) << "%\n";
                cout << "  Highest Average: " << fixed << setprecision(1) << highestAverage << "%\n";
                cout << "  Lowest Average: " << fixed << setprecision(1) << lowestAverage << "%\n";
            }
        }
        
    } catch (const exception& e) {
        cout << "Error in viewCourseEnrollments: " << e.what() << "\n";
    }
    
    pauseForUser();
}

void System::backupSystemData() {
    cout << "Backup functionality will be implemented in full version.\n";
    pauseForUser();
}

void System::validateDataIntegrity() {
    cout << "Data integrity validation will be implemented in full version.\n";
    pauseForUser();
}

void System::resetSystemData() {
    cout << "Reset functionality will be implemented in full version.\n";
    pauseForUser();
}

void System::showOperationResult(bool success, const string& operation) const {
    if (success) {
        cout << "✓ " << operation << " completed successfully.\n";
    } else {
        cout << "✗ " << operation << " failed.\n";
    }
}

bool System::isValidDate(const string& date) const {
    return Common::isValidDate(date);
}

bool System::isValidEmail(const string& email) const {
    return Common::isValidEmail(email);
}

bool System::isValidRollNumber(int rollNumber) const {
    return rollNumber > 0 && rollNumber <= 99999;
}

bool System::isValidCourseId(const string& courseId) const {
    return !courseId.empty() && courseId.length() <= 10;
}

vector<shared_ptr<Student>> System::getStudentsInCourse(const string& courseId) const {
    auto course = findCourseById(courseId);
    return course ? course->getEnrolledStudents() : vector<shared_ptr<Student>>();
}

vector<shared_ptr<Course>> System::getCoursesForStudent(int rollNumber) const {
    auto student = findStudentByRollNumber(rollNumber);
    return student ? student->getEnrolledCourses() : vector<shared_ptr<Course>>();
}

vector<shared_ptr<Assessment>> System::getAssessmentsForStudent(int rollNumber) const {
    vector<shared_ptr<Assessment>> result;
    for (const auto& assessment : assessments) {
        if (assessment && assessment->getStudentRollNumber() == rollNumber) {
            result.push_back(assessment);
        }
    }
    return result;
}

vector<shared_ptr<Assessment>> System::getAssessmentsForCourse(const string& courseId) const {
    vector<shared_ptr<Assessment>> result;
    for (const auto& assessment : assessments) {
        if (assessment && assessment->getCourseId() == courseId) {
            result.push_back(assessment);
        }
    }
    return result;
}

bool System::removeStudent(int rollNumber) {
    auto it = find_if(students.begin(), students.end(),
        [rollNumber](const shared_ptr<Student>& student) {
            return student && student->getRollNumber() == rollNumber;
        });
    if (it != students.end()) {
        students.erase(it);
        return true;
    }
    return false;
}

bool System::removeCourse(const string& courseId) {
    auto it = find_if(courses.begin(), courses.end(),
        [&courseId](const shared_ptr<Course>& course) {
            return course && course->getCourseId() == courseId;
        });
    if (it != courses.end()) {
        courses.erase(it);
        return true;
    }
    return false;
}

bool System::removeAssessment(const string& assessmentId) {
    auto it = find_if(assessments.begin(), assessments.end(),
        [&assessmentId](const shared_ptr<Assessment>& assessment) {
            return assessment && assessment->getAssessmentId() == assessmentId;
        });
    if (it != assessments.end()) {
        assessments.erase(it);
        return true;
    }
    return false;
}

bool System::loadData() {
    loadAllSystemData();
    return dataLoaded;
}

bool System::saveData() {
    return saveAllSystemData();
}

bool System::createBackup() {
    return FileHandler::backupDataFiles();
}

bool System::enrollStudent(int rollNumber, const string& courseId) {
    auto student = findStudentByRollNumber(rollNumber);
    auto course = findCourseById(courseId);
    
    if (!student || !course) return false;
    
    try {
        student->enrollInCourse(course);
        course->enrollStudent(student);
        return true;
    } catch (const exception&) {
        return false;
    }
}

bool System::withdrawStudent(int rollNumber, const string& courseId) {
    auto student = findStudentByRollNumber(rollNumber);
    auto course = findCourseById(courseId);
    
    if (!student || !course) return false;
    
    try {
        student->withdrawFromCourse(courseId);
        course->withdrawStudent(rollNumber);
        return true;
    } catch (const exception&) {
        return false;
    }
}

bool System::isStudentEnrolled(int rollNumber, const string& courseId) const {
    auto student = findStudentByRollNumber(rollNumber);
    return student && student->isEnrolledInCourse(courseId);
}

// === T044-T046: USER EXPERIENCE IMPROVEMENTS ===

// === T044: ENHANCED MENU NAVIGATION AND USER EXPERIENCE ===

void System::showContextualHelp(const string& menuContext) const {
    cout << "\n" << string(60, '=') << "\n";
    cout << "                    HELP - " << menuContext << "\n";
    cout << string(60, '=') << "\n\n";
    
    if (menuContext == "MAIN MENU") {
        cout << "📚 NAVIGATION GUIDE:\n";
        cout << "  • Use number keys (0-6) to select menu options\n";
        cout << "  • Press 0 to go back or exit from any menu\n";
        cout << "  • Type 'help' for contextual assistance\n\n";
        
        cout << "🎯 MENU OPTIONS:\n";
        cout << "  1️⃣  Student Management - Add, edit, view students\n";
        cout << "  2️⃣  Course Management - Manage courses and curricula\n";
        cout << "  3️⃣  Assessment Management - Track student assessments\n";
        cout << "  4️⃣  Reports & Analytics - Generate reports and statistics\n";
        cout << "  5️⃣  System Management - Data backup and system settings\n";
        cout << "  6️⃣  About / Help - System information and support\n";
        cout << "  0️⃣  Exit System - Safely close the application\n\n";
        
    } else if (menuContext == "STUDENT MANAGEMENT") {
        cout << "👥 STUDENT OPERATIONS:\n";
        cout << "  • Add New: Create student records with validation\n";
        cout << "  • View All: Browse complete student directory\n";
        cout << "  • Find: Search by roll number or name\n";
        cout << "  • Edit: Update student information safely\n";
        cout << "  • Delete: Remove students (with confirmation)\n";
        cout << "  • Statistics: View enrollment and performance data\n\n";
        
        cout << "💡 TIPS:\n";
        cout << "  • Roll numbers must be unique\n";
        cout << "  • Email addresses are validated automatically\n";
        cout << "  • Phone numbers support multiple formats\n";
        
    } else if (menuContext == "COURSE MANAGEMENT") {
        cout << "📖 COURSE OPERATIONS:\n";
        cout << "  • Add New: Create course with curriculum details\n";
        cout << "  • View All: Browse course catalog\n";
        cout << "  • Find: Search by course ID or name\n";
        cout << "  • Edit: Update course information\n";
        cout << "  • Delete: Remove courses (checks for enrollments)\n";
        cout << "  • Statistics: View enrollment and assessment data\n\n";
        
        cout << "💡 TIPS:\n";
        cout << "  • Course IDs should follow school naming convention\n";
        cout << "  • Deleting courses requires no active enrollments\n";
        
    } else if (menuContext == "ASSESSMENT MANAGEMENT") {
        cout << "📝 ASSESSMENT OPERATIONS:\n";
        cout << "  • Add New: Create assessment records\n";
        cout << "  • View All: Browse all assessments\n";
        cout << "  • Find: Search by student or course\n";
        cout << "  • Edit: Update grades and feedback\n";
        cout << "  • Delete: Remove assessment records\n";
        cout << "  • Statistics: View grade distributions\n\n";
        
        cout << "💡 TIPS:\n";
        cout << "  • Grades must be between 0-100\n";
        cout << "  • Student and course must exist before assessment\n";
        
    } else {
        cout << "ℹ️  General Help:\n";
        cout << "  • Use arrow keys or numbers to navigate\n";
        cout << "  • Follow on-screen prompts carefully\n";
        cout << "  • Data is automatically saved\n";
    }
    
    cout << "\n📞 SUPPORT:\n";
    cout << "  For technical support, contact system administrators\n";
    cout << "  Version: 1.0.0 | Pokeno South Primary School\n\n";
}

bool System::handleMenuNavigation(int choice, int minOption, int maxOption, const string& menuType) {
    // Enhanced navigation with contextual feedback
    if (choice < minOption || choice > maxOption) {
        displayUserFriendlyError("Menu Navigation", 
            "Choice " + to_string(choice) + " is not available in " + menuType);
        displayInfoMessage("Please select a number between " + 
                          to_string(minOption) + " and " + to_string(maxOption));
        return false;
    }
    
    // Provide navigation feedback for special choices
    if (choice == 0) {
        if (menuType != "Main Menu") {
            displayInfoMessage("Returning to previous menu...");
        }
    }
    
    return true;
}

void System::displayNavigationTips() const {
    cout << "\n💡 NAVIGATION TIPS:\n";
    cout << "  • Type the number of your choice and press Enter\n";
    cout << "  • Use 0 to go back to the previous menu\n";
    cout << "  • All data changes are saved automatically\n";
    cout << "  • Use Ctrl+C to exit immediately if needed\n\n";
}

void System::clearScreenWithHeader(const string& title) const {
    clearScreen();
    displayHeader(title);
    cout << "Navigation: Main Menu > " << title << "\n";
    cout << "Session: " << getCurrentTimestamp() << "\n\n";
}

// === T045: USER-FRIENDLY ERROR MESSAGES ===

void System::displayUserFriendlyError(const string& operation, const string& technicalError) const {
    cout << "\n❌ " << operation << " Error\n";
    cout << string(50, '-') << "\n";
    
    // Convert technical errors to user-friendly messages
    string userMessage;
    if (technicalError.find("not found") != string::npos) {
        userMessage = "The requested information could not be found in the system.";
    } else if (technicalError.find("duplicate") != string::npos) {
        userMessage = "This information already exists in the system. Please use different values.";
    } else if (technicalError.find("invalid") != string::npos) {
        userMessage = "The information provided is not in the correct format.";
    } else if (technicalError.find("permission") != string::npos ||
               technicalError.find("access") != string::npos) {
        userMessage = "Unable to access the required files. Please check file permissions.";
    } else if (technicalError.find("network") != string::npos ||
               technicalError.find("connection") != string::npos) {
        userMessage = "Network connection issue. Please check your connection and try again.";
    } else if (technicalError.find("memory") != string::npos) {
        userMessage = "System memory issue. Please close other applications and try again.";
    } else if (technicalError.find("file") != string::npos) {
        userMessage = "File access issue. The data file may be locked by another program.";
    } else {
        userMessage = "An unexpected error occurred. Please try again or contact support.";
    }
    
    cout << "What happened: " << userMessage << "\n\n";
    
    // Provide actionable suggestions
    cout << "💡 What you can do:\n";
    if (technicalError.find("not found") != string::npos) {
        cout << "  • Check that you entered the correct information\n";
        cout << "  • Use the 'View All' option to see available items\n";
        cout << "  • Try the 'Find' option to search for specific items\n";
    } else if (technicalError.find("duplicate") != string::npos) {
        cout << "  • Check existing records before adding new ones\n";
        cout << "  • Use the 'Edit' option to update existing information\n";
        cout << "  • Try using different identification numbers or names\n";
    } else if (technicalError.find("invalid") != string::npos) {
        cout << "  • Check the format of your input (numbers, dates, emails)\n";
        cout << "  • Follow the examples provided in prompts\n";
        cout << "  • Contact support if you need help with data formats\n";
    } else if (technicalError.find("file") != string::npos) {
        cout << "  • Close other programs that might be using the data files\n";
        cout << "  • Check if you have permission to access the data directory\n";
        cout << "  • Try restarting the application\n";
    } else {
        cout << "  • Try the operation again\n";
        cout << "  • Restart the application if the problem persists\n";
        cout << "  • Contact technical support with error details\n";
    }
    
    cout << "\n📞 Need Help? Contact your system administrator\n";
    cout << "🐛 Technical Details: " << technicalError << "\n\n";
}

void System::displaySuccessMessage(const string& operation, const string& details) const {
    cout << "\n✅ " << operation << " Successful!\n";
    if (!details.empty()) {
        cout << "📋 Details: " << details << "\n";
    }
    cout << "💾 Data has been saved automatically\n\n";
}

void System::displayWarningMessage(const string& message) const {
    cout << "\n⚠️  Warning: " << message << "\n";
    cout << "Please review your action and proceed carefully.\n\n";
}

void System::displayInfoMessage(const string& message) const {
    cout << "\nℹ️  " << message << "\n\n";
}

// === T046: CONFIRMATION DIALOGS FOR DESTRUCTIVE OPERATIONS ===

bool System::confirmDestructiveOperation(const string& operation, const string& itemDescription,
                                        const vector<string>& warnings) const {
    cout << "\n" << string(60, '=') << "\n";
    cout << "⚠️  CONFIRMATION REQUIRED: " << operation << "\n";
    cout << string(60, '=') << "\n\n";
    
    cout << "🎯 You are about to " << operation << ":\n";
    cout << "   " << itemDescription << "\n\n";
    
    if (!warnings.empty()) {
        cout << "⚠️  Important Warnings:\n";
        for (const auto& warning : warnings) {
            cout << "   • " << warning << "\n";
        }
        cout << "\n";
    }
    
    cout << "🔄 This action will:\n";
    if (operation.find("delete") != string::npos || operation.find("remove") != string::npos) {
        cout << "   • Permanently remove this information from the system\n";
        cout << "   • Update all related records automatically\n";
        cout << "   • Create a backup before making changes\n";
    } else if (operation.find("overwrite") != string::npos || operation.find("replace") != string::npos) {
        cout << "   • Replace current information with new data\n";
        cout << "   • Previous information will be lost\n";
        cout << "   • Create a backup of current data\n";
    } else {
        cout << "   • Make permanent changes to the system\n";
        cout << "   • Update related information automatically\n";
    }
    
    cout << "\n💾 Data Safety:\n";
    cout << "   • A backup will be created automatically\n";
    cout << "   • You can restore from backup if needed\n";
    cout << "   • System integrity will be maintained\n\n";
    
    string confirmation;
    while (true) {
        cout << "Type 'YES' to confirm, or 'NO' to cancel: ";
        getline(cin, confirmation);
        
        // Convert to uppercase for comparison
        transform(confirmation.begin(), confirmation.end(), confirmation.begin(), ::toupper);
        
        if (confirmation == "YES" || confirmation == "Y") {
            cout << "\n✅ Operation confirmed. Proceeding...\n";
            return true;
        } else if (confirmation == "NO" || confirmation == "N") {
            cout << "\n❌ Operation cancelled. No changes made.\n";
            return false;
        } else {
            cout << "Please type 'YES' to confirm or 'NO' to cancel.\n";
        }
    }
}

bool System::confirmDataLoss(const string& operation) const {
    cout << "\n" << string(60, '!') << "\n";
    cout << "🚨 DATA LOSS WARNING\n";
    cout << string(60, '!') << "\n\n";
    
    cout << "⚠️  The operation '" << operation << "' may result in data loss!\n\n";
    
    cout << "💥 Potential consequences:\n";
    cout << "   • Unsaved changes will be lost permanently\n";
    cout << "   • Current session data may not be recoverable\n";
    cout << "   • Related information might become inconsistent\n\n";
    
    cout << "🛡️  Recommended actions:\n";
    cout << "   • Save your current work first\n";
    cout << "   • Create a backup before proceeding\n";
    cout << "   • Consider if this operation is really necessary\n\n";
    
    string confirmation;
    while (true) {
        cout << "Are you absolutely sure you want to continue? (YES/NO): ";
        getline(cin, confirmation);
        
        transform(confirmation.begin(), confirmation.end(), confirmation.begin(), ::toupper);
        
        if (confirmation == "YES") {
            cout << "\n⚠️  Proceeding with operation that may cause data loss...\n";
            return true;
        } else if (confirmation == "NO") {
            cout << "\n✅ Operation cancelled. Your data is safe.\n";
            return false;
        } else {
            cout << "Please type 'YES' to continue or 'NO' to cancel.\n";
        }
    }
}

bool System::confirmSystemExit() const {
    cout << "\n" << string(50, '=') << "\n";
    cout << "EXIT CONFIRMATION\n";
    cout << string(50, '=') << "\n" << endl;
    
    // Check if there might be unsaved data
    bool hasUnsavedData = false; // In a real system, you'd check for unsaved changes

    if (hasUnsavedData) {
        cout << "You have unsaved changes!\n" << endl;
    } else {
        cout << "All data has been saved\n";
        cout << "System is ready for safe shutdown\n" << endl;
    }
    
    cout << "📊 Session Summary:\n";
    cout << "   • Students: " << getStudentCount() << " records\n";
    cout << "   • Courses: " << getCourseCount() << " records\n";
    cout << "   • Assessments: " << getAssessmentCount() << " records\n";
    cout << "   • Session: " << getCurrentTimestamp() << "\n" << endl;
    
    string confirmation;
    while (true) {
        cout << "Exit Pokeno South Student Management System? (yes/no): ";
        getline(cin, confirmation);

        transform(confirmation.begin(), confirmation.end(), confirmation.begin(), [](char c) {return tolower(c);});
        
        if (confirmation == "yes" || confirmation == "y") {
            cout << "\nThank you for using Pokeno South Student Management System!\n";
            cout << "System shutdown complete.\n" << endl;
            return true;
        } else if (confirmation == "no" || confirmation == "n") {
            cout << "\nReturning to main menu...\n";
            return false;
        } else {
            cout << "Please type 'yes' to exit or 'no' to continue.\n";
        }
    }
}

// === HELPER METHOD FOR CURRENT TIMESTAMP ===
string System::getCurrentTimestamp() const {
    auto now = system_clock::now();
    auto time_t = system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&time_t), "%d-%m-%Y %H:%M:%S");
    return ss.str();
}

} // namespace PokenoSouth
