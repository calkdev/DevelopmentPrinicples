#include "Course.hpp"

namespace PokenoSouth {

    // Constructor with core data
    Course::Course(const string& courseId,
                   const string& courseName,
                   int credits,
                   const string& description,
                   int duration)
        : courseId(formatCourseId(courseId)) {
        
        // Validate course ID
        if (!isValidCourseId(this->courseId)) {
            throw invalid_argument("Invalid course ID format: must follow pattern like MATH101");
        }
        
        // Validate and set course name
        if (!isValidCourseName(courseName)) {
            throw invalid_argument("Invalid course name: cannot be empty");
        }
        this->courseName = courseName;
        
        // Validate and set credits
        if (!isValidCredits(credits)) {
            throw invalid_argument("Invalid credits: must be between " +
                                      to_string(MIN_CREDITS) + " and " +
                                      to_string(MAX_CREDITS));
        }
        this->credits = credits;
        
        // Set description
        this->description = description;
        
        // Validate and set duration
        if (!isValidDuration(duration)) {
            throw invalid_argument("Invalid duration: must be between " +
                                      to_string(MIN_DURATION) + " and " +
                                      to_string(MAX_DURATION) + " weeks");
        }
        this->duration = duration;
        
        // Initialize defaults
        this->startDate = "";
        this->endDate = "";
        this->maxEnrollment = DEFAULT_MAX_ENROLLMENT;
        this->isActive = true;
        
        // Initialize empty enrollment with optimized capacity
        enrolledStudents.clear();
        enrolledStudents.reserve(DEFAULT_MAX_ENROLLMENT);  // Reserve space for default enrollment
    }
        // Constructor with core data (with teacher)
        Course::Course(const string& courseId,
                       const string& courseName,
                       int credits,
                       const string& description,
                       int duration,
                       const string& teacher)
            : courseId(formatCourseId(courseId)), teacher(teacher) {
            // Validate course ID
            if (!isValidCourseId(this->courseId)) {
                throw invalid_argument("Invalid course ID format: must follow pattern like MATH101");
            }
            // Validate and set course name
            if (!isValidCourseName(courseName)) {
                throw invalid_argument("Invalid course name: cannot be empty");
            }
            this->courseName = courseName;
            // Validate and set credits
            if (!isValidCredits(credits)) {
                throw invalid_argument("Invalid credits: must be between " +
                                          to_string(MIN_CREDITS) + " and " +
                                          to_string(MAX_CREDITS));
            }
            this->credits = credits;
            // Set description
            this->description = description;
            // Validate and set duration
            if (!isValidDuration(duration)) {
                throw invalid_argument("Invalid duration: must be between " +
                                          to_string(MIN_DURATION) + " and " +
                                          to_string(MAX_DURATION) + " weeks");
            }
            this->duration = duration;
            // Validate and set teacher
            if (teacher.empty()) {
                throw invalid_argument("Teacher name cannot be empty");
            }
            // Initialize defaults
            this->startDate = "";
            this->endDate = "";
            this->maxEnrollment = DEFAULT_MAX_ENROLLMENT;
            this->isActive = true;
            // Initialize empty enrollment with optimized capacity
            enrolledStudents.clear();
            enrolledStudents.reserve(DEFAULT_MAX_ENROLLMENT);
        }
    
    // Constructor with full metadata
    Course::Course(const string& courseId,
                   const string& courseName,
                   int credits,
                   const string& description,
                   int duration,
                   const string& startDate,
                   const string& endDate,
                   int maxEnrollment)
        : Course(courseId, courseName, credits, description, duration) {
        
        // Validate and set start date
        if (!startDate.empty() && !Common::isValidDate(startDate)) {
            throw invalid_argument("Invalid start date format: must be YYYY-MM-DD");
        }
        this->startDate = startDate;
        
        // Validate and set end date
        if (!endDate.empty() && !Common::isValidDate(endDate)) {
            throw invalid_argument("Invalid end date format: must be YYYY-MM-DD");
        }
        this->endDate = endDate;
        
        // Validate date sequence
        if (!startDate.empty() && !endDate.empty()) {
            if (startDate >= endDate) {  // Simple string comparison for dates in YYYY-MM-DD format
                throw invalid_argument("End date must be after start date");
            }
        }
        
        // Validate and set max enrollment
        if (maxEnrollment < 1 || maxEnrollment > ABSOLUTE_MAX_ENROLLMENT) {
            throw invalid_argument("Invalid max enrollment: must be between 1 and " +
                                      to_string(ABSOLUTE_MAX_ENROLLMENT));
        }
        this->maxEnrollment = maxEnrollment;
    }
        // Constructor with full metadata (with teacher)
        Course::Course(const string& courseId,
                       const string& courseName,
                       int credits,
                       const string& description,
                       int duration,
                       const string& teacher,
                       const string& startDate,
                       const string& endDate,
                       int maxEnrollment,
                       bool isActive)
            : Course(courseId, courseName, credits, description, duration, teacher) {
            // Validate and set start date
            if (!startDate.empty() && !Common::isValidDate(startDate)) {
                throw invalid_argument("Invalid start date format: must be YYYY-MM-DD");
            }
            this->startDate = startDate;
            // Validate and set end date
            if (!endDate.empty() && !Common::isValidDate(endDate)) {
                throw invalid_argument("Invalid end date format: must be YYYY-MM-DD");
            }
            this->endDate = endDate;
            // Validate date sequence
            if (!startDate.empty() && !endDate.empty()) {
                if (startDate >= endDate) {
                    throw invalid_argument("End date must be after start date");
                }
            }
            // Validate and set max enrollment
            if (maxEnrollment < 1 || maxEnrollment > ABSOLUTE_MAX_ENROLLMENT) {
                throw invalid_argument("Invalid max enrollment: must be between 1 and " + to_string(ABSOLUTE_MAX_ENROLLMENT));
            }
            this->maxEnrollment = maxEnrollment;
            this->isActive = isActive;
        }
    
    // Copy constructor
    Course::Course(const Course& other)
        : courseId(other.courseId),
          courseName(other.courseName),
          credits(other.credits),
          description(other.description),
          duration(other.duration),
          enrolledStudents(other.enrolledStudents),
          startDate(other.startDate),
          endDate(other.endDate),
          maxEnrollment(other.maxEnrollment),
          isActive(other.isActive) {
    }
    
    // Assignment operator
    Course& Course::operator=(const Course& other) {
        if (this != &other) {
            // Note: courseId is const and cannot be changed
            courseName = other.courseName;
            credits = other.credits;
            description = other.description;
            duration = other.duration;
            enrolledStudents = other.enrolledStudents;
            startDate = other.startDate;
            endDate = other.endDate;
            maxEnrollment = other.maxEnrollment;
            isActive = other.isActive;
        }
        return *this;
    }
    
    // === DERIVED GETTERS ===
    int Course::getCurrentEnrollment() const {
        return static_cast<int>(enrolledStudents.size());
    }
    
    int Course::getAvailableSpots() const {
        return maxEnrollment - getCurrentEnrollment();
    }
    
    double Course::getEnrollmentPercentage() const {
        if (maxEnrollment == 0) return 0.0;
        return (static_cast<double>(getCurrentEnrollment()) / maxEnrollment) * 100.0;
    }
    
    bool Course::isFull() const {
        return getCurrentEnrollment() >= maxEnrollment;
    }
    
    // === SETTER METHODS ===
    void Course::setCourseName(const string& name) {
        if (!isValidCourseName(name)) {
            throw invalid_argument("Invalid course name: cannot be empty");
        }
        this->courseName = name;
    }
    
    void Course::setCredits(int credits) {
        if (!isValidCredits(credits)) {
            throw invalid_argument("Invalid credits: must be between " +
                                      to_string(MIN_CREDITS) + " and " +
                                      to_string(MAX_CREDITS));
        }
        this->credits = credits;
    }
    
    void Course::setDescription(const string& description) {
        this->description = description;
    }
    
    void Course::setDuration(int duration) {
        if (!isValidDuration(duration)) {
            throw invalid_argument("Invalid duration: must be between " +
                                      to_string(MIN_DURATION) + " and " +
                                      to_string(MAX_DURATION) + " weeks");
        }
        this->duration = duration;
    }
    
    void Course::setStartDate(const string& startDate) {
        if (!startDate.empty() && !Common::isValidDate(startDate)) {
            throw invalid_argument("Invalid start date format: must be YYYY-MM-DD");
        }
        
        // Validate with existing end date
        if (!endDate.empty() && !startDate.empty()) {
            if (startDate >= endDate) {  // Simple string comparison for dates in YYYY-MM-DD format
                throw invalid_argument("Start date must be before end date");
            }
        }
        
        this->startDate = startDate;
    }
    
    void Course::setEndDate(const string& endDate) {
        if (!endDate.empty() && !Common::isValidDate(endDate)) {
            throw invalid_argument("Invalid end date format: must be YYYY-MM-DD");
        }
        
        // Validate with existing start date
        if (!startDate.empty() && !endDate.empty()) {
            if (startDate >= endDate) {  // Simple string comparison for dates in YYYY-MM-DD format
                throw invalid_argument("End date must be after start date");
            }
        }
        
        this->endDate = endDate;
    }
    
    void Course::setMaxEnrollment(int maxEnrollment) {
        if (maxEnrollment < 1 || maxEnrollment > ABSOLUTE_MAX_ENROLLMENT) {
            throw invalid_argument("Invalid max enrollment: must be between 1 and " +
                                      to_string(ABSOLUTE_MAX_ENROLLMENT));
        }
        
        // Cannot reduce below current enrollment
        if (maxEnrollment < getCurrentEnrollment()) {
            throw runtime_error("Cannot set max enrollment below current enrollment of " +
                                   to_string(getCurrentEnrollment()));
        }
        
        this->maxEnrollment = maxEnrollment;
        
        // Memory management: Adjust vector capacity if needed
        if (maxEnrollment > enrolledStudents.capacity()) {
            enrolledStudents.reserve(maxEnrollment);
        } else if (maxEnrollment < enrolledStudents.capacity() / 2 && 
                   enrolledStudents.capacity() > DEFAULT_MAX_ENROLLMENT) {
            // Only shrink if the new capacity is significantly smaller and we're above default
            vector<shared_ptr<Student>> temp(enrolledStudents);
            enrolledStudents = move(temp);
            enrolledStudents.reserve(maxEnrollment);
        }
    }
    
    void Course::setIsActive(bool active) {
        this->isActive = active;
    }
    
    // === STUDENT ENROLLMENT MANAGEMENT (bidirectional) ===
    bool Course::enrollStudent(shared_ptr<Student> student) {
        if (!student) {
            throw invalid_argument("Cannot enroll null student");
        }
        
        // Check if course is active
        if (!isActive) {
            throw runtime_error("Cannot enroll in inactive course: " + courseId);
        }
        
        // Check if already enrolled
        if (isStudentEnrolled(student->getRollNumber())) {
            throw runtime_error("Student " + to_string(student->getRollNumber()) +
                                   " is already enrolled in course: " + courseId);
        }
        
        // Check enrollment capacity
        if (isFull()) {
            throw runtime_error("Course " + courseId + " is at maximum capacity (" +
                                   to_string(maxEnrollment) + ")");
        }
        
        // Check enrollment period
        if (!isEnrollmentPeriodActive()) {
            throw runtime_error("Enrollment period is not active for course: " + courseId);
        }
        
        // Memory management: Reserve space if needed to avoid frequent reallocations
        if (enrolledStudents.capacity() < enrolledStudents.size() + 1) {
            enrolledStudents.reserve(maxEnrollment);
        }
        
        enrolledStudents.push_back(student);
        return true;
    }
    
    bool Course::withdrawStudent(int rollNumber) {
        auto it = find_if(enrolledStudents.begin(), enrolledStudents.end(),
            [rollNumber](const shared_ptr<Student>& student) {
                return student && student->getRollNumber() == rollNumber;
            });
            
        if (it == enrolledStudents.end()) {
            throw runtime_error("Student " + to_string(rollNumber) +
                                   " is not enrolled in course: " + courseId);
        }
        
        enrolledStudents.erase(it);
        
        // Memory management: Shrink vector if significantly smaller than capacity
        if (enrolledStudents.size() < enrolledStudents.capacity() / 2 && enrolledStudents.capacity() > DEFAULT_MAX_ENROLLMENT) {
            enrolledStudents.shrink_to_fit();
        }
        
        return true;
    }
    
    bool Course::isStudentEnrolled(int rollNumber) const {
        return any_of(enrolledStudents.begin(), enrolledStudents.end(),
            [rollNumber](const shared_ptr<Student>& student) {
                return student && student->getRollNumber() == rollNumber;
            });
    }
    
    shared_ptr<Student> Course::getStudent(int rollNumber) const {
        auto it = find_if(enrolledStudents.begin(), enrolledStudents.end(),
            [rollNumber](const shared_ptr<Student>& student) {
                return student && student->getRollNumber() == rollNumber;
            });
            
        return (it != enrolledStudents.end()) ? *it : nullptr;
    }
    
    vector<shared_ptr<Student>> Course::getEnrolledStudents() const {
        return enrolledStudents;
    }
    
    // === ENROLLMENT QUERIES ===
    vector<int> Course::getEnrolledRollNumbers() const {
        vector<int> rollNumbers;
        for (const auto& student : enrolledStudents) {
            if (student) {
                rollNumbers.push_back(student->getRollNumber());
            }
        }
        return rollNumbers;
    }
    
    vector<string> Course::getEnrolledStudentNames() const {
        vector<string> names;
        for (const auto& student : enrolledStudents) {
            if (student) {
                names.push_back(student->getFullName());
            }
        }
        return names;
    }
    
    bool Course::hasWaitingList() const {
        return false; // For now, we don't implement waiting lists
    }
    
    // === BUSINESS RULE VALIDATION ===
    bool Course::canEnrollMoreStudents() const {
        return isActive && !isFull() && isEnrollmentPeriodActive();
    }
    
    bool Course::isEnrollmentPeriodActive() const {
        if (startDate.empty()) return true; // No date restrictions
        
        string currentDate = Common::getCurrentDate();
        
        // Can enroll before start date and during course
        if (!endDate.empty()) {
            return currentDate <= endDate;
        }
        
        return true; // No end date restriction
    }
    
    bool Course::meetsPrerequisites(shared_ptr<Student> student) const {
        // For primary school, no prerequisites
        return student != nullptr;
    }
    
    // === GRADE AND ASSESSMENT SUPPORT ===
    double Course::getCourseAverageGrade() const {
        if (enrolledStudents.empty()) {
            return 0.0;
        }
        
        double totalGrade = 0.0;
        int validGrades = 0;
        
        for (const auto& student : enrolledStudents) {
            if (student) {
                double courseGrade = student->getCourseGrade(courseId);
                if (courseGrade > 0.0) {
                    totalGrade += courseGrade;
                    validGrades++;
                }
            }
        }
        
        return validGrades > 0 ? totalGrade / validGrades : 0.0;
    }
    
    vector<shared_ptr<Student>> Course::getPassingStudents() const {
        vector<shared_ptr<Student>> passingStudents;
        
        for (const auto& student : enrolledStudents) {
            if (student && student->getCourseGrade(courseId) >= 50.0) {
                passingStudents.push_back(student);
            }
        }
        
        return passingStudents;
    }
    
    vector<shared_ptr<Student>> Course::getFailingStudents() const {
        vector<shared_ptr<Student>> failingStudents;
        
        for (const auto& student : enrolledStudents) {
            if (student && student->getCourseGrade(courseId) < 50.0) {
                failingStudents.push_back(student);
            }
        }
        
        return failingStudents;
    }
    
    int Course::getPassCount() const {
        return static_cast<int>(getPassingStudents().size());
    }
    
    int Course::getFailCount() const {
        return static_cast<int>(getFailingStudents().size());
    }
    
    double Course::getPassRate() const {
        int enrolled = getCurrentEnrollment();
        if (enrolled == 0) return 0.0;
        
        return (static_cast<double>(getPassCount()) / enrolled) * 100.0;
    }
    
    // === DISPLAY AND FORMATTING ===
    void Course::displayCourseInfo() const {
        cout << "\n=== Course Information ===" << endl;
        cout << "Course ID: " << courseId << endl;
        cout << "Course Name: " << courseName << endl;
        cout << "Credits: " << credits << endl;
        cout << "Duration: " << duration << " weeks" << endl;
        cout << "Description: " << description << endl;
        cout << "Start Date: " << (startDate.empty() ? "Not set" : startDate) << endl;
        cout << "End Date: " << (endDate.empty() ? "Not set" : endDate) << endl;
        cout << "Enrollment: " << getCurrentEnrollment() << "/" << maxEnrollment
                  << " (" << fixed << setprecision(1) << getEnrollmentPercentage() << "%)" << endl;
        cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
        cout << "Average Grade: " << fixed << setprecision(1) << getCourseAverageGrade() << "%" << endl;
    }
    
    void Course::displayEnrollmentList() const {
        cout << "\n=== Enrollment List ===" << endl;
        cout << "Course: " << courseId << " - " << courseName << endl;
        cout << "Enrolled Students: " << getCurrentEnrollment() << "/" << maxEnrollment << endl;
        
        if (!enrolledStudents.empty()) {
            cout << "\nStudents:" << endl;
            for (const auto& student : enrolledStudents) {
                if (student) {
                    cout << "  " << student->getRollNumber() << ": " << student->getFullName()
                              << " (Grade: " << fixed << setprecision(1)
                              << student->getCourseGrade(courseId) << "%)" << endl;
                }
            }
        }
    }
    
    void Course::displayCourseStatistics() const {
        cout << "\n=== Course Statistics ===" << endl;
        cout << "Course: " << courseId << " - " << courseName << endl;
        cout << "Total Enrolled: " << getCurrentEnrollment() << endl;
        cout << "Passing Students: " << getPassCount() << endl;
        cout << "Failing Students: " << getFailCount() << endl;
        cout << "Pass Rate: " << fixed << setprecision(1) << getPassRate() << "%" << endl;
        cout << "Average Grade: " << fixed << setprecision(1) << getCourseAverageGrade() << "%" << endl;
        cout << "Enrollment Rate: " << fixed << setprecision(1) << getEnrollmentPercentage() << "%" << endl;
    }
    
    string Course::toCSVString() const {
        ostringstream oss;
        oss << courseId << ","
            << courseName << ","
            << credits << ","
            << description << ","
            << duration << ","
            << startDate << ","
            << endDate << ","
            << maxEnrollment << ","
            << getCurrentEnrollment() << ","
            << (isActive ? "Active" : "Inactive") << ","
            << fixed << setprecision(1) << getCourseAverageGrade();
        return oss.str();
    }
    
    // === VALIDATION HELPERS ===
    bool Course::isValidCourseId(const string& courseId) {
        if (courseId.length() < 6 || courseId.length() > 10) return false;
        
        // Check pattern: letters followed by numbers (e.g., MATH101)
        bool hasLetters = false;
        bool hasNumbers = false;
        bool lettersDone = false;
        
        for (char c : courseId) {
            if (isalpha(c)) {
                if (lettersDone) return false; // Numbers already started
                if (!isupper(c)) return false; // Must be uppercase
                hasLetters = true;
            } else if (isdigit(c)) {
                lettersDone = true;
                hasNumbers = true;
            } else {
                return false; // Invalid character
            }
        }
        
        return hasLetters && hasNumbers;
    }
    
    bool Course::isValidCourseName(const string& name) {
        return !name.empty() && name.length() <= 100;
    }
    
    bool Course::isValidCredits(int credits) {
        return credits >= MIN_CREDITS && credits <= MAX_CREDITS;
    }
    
    bool Course::isValidDuration(int duration) {
        return duration >= MIN_DURATION && duration <= MAX_DURATION;
    }
    
    string Course::formatCourseId(const string& courseId) {
        string formatted = courseId;
        transform(formatted.begin(), formatted.end(), formatted.begin(), ::toupper);
        return formatted;
    }
    
    // === COMPARISON OPERATORS ===
    bool Course::operator==(const Course& other) const {
        return courseId == other.courseId;
    }
    
    bool Course::operator!=(const Course& other) const {
        return !(*this == other);
    }
    
    bool Course::operator<(const Course& other) const {
        return courseId < other.courseId;
    }
    
    // Stream operator
    ostream& operator<<(ostream& os, const Course& course) {
        os << "Course[" << course.getCourseId() << "]: " << course.getCourseName() 
           << " (" << course.getCurrentEnrollment() << "/" << course.getMaxEnrollment() << " enrolled)";
        return os;
    }
}
