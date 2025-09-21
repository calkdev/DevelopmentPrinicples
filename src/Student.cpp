#include "Student.hpp"

namespace PokenoSouth {

    // Constructor with comprehensive validation
    Student::Student(int rollNumber, 
                     const string& firstName,
                     const string& lastName,
                     const string& dateOfBirth,
                     const string& address,
                     const string& contactEmail,
                     const string& emergencyContact,
                     const string& enrollmentDate)
        : rollNumber(rollNumber) {
        
        // Validate roll number
        if (!Common::isValidRollNumber(rollNumber)) {
            throw invalid_argument("Invalid roll number: must be between " + 
                                      to_string(MIN_ROLL_NUMBER) + " and " + 
                                      to_string(MAX_ROLL_NUMBER));
        }
        
        // Validate and set first name
        if (!Common::isValidName(firstName)) {
            throw invalid_argument("Invalid first name: must contain only alphabetic characters and not be empty");
        }
        this->firstName = firstName;
        
        // Validate and set last name
        if (!Common::isValidName(lastName)) {
            throw invalid_argument("Invalid last name: must contain only alphabetic characters and not be empty");
        }
        this->lastName = lastName;
        
        // Validate and set date of birth
        if (!Common::isValidDateFormat(dateOfBirth)) {
            throw invalid_argument("Invalid date of birth format: must be YYYY-MM-DD");
        }
        if (!Common::isValidDate(dateOfBirth)) {
            throw invalid_argument("Invalid date of birth: must be a valid past date");
        }
        this->dateOfBirth = dateOfBirth;
        
        // Validate and set address (basic length check; detailed checks are in System prompts)
        if (!Common::isValidLength(address, 1, 100)) {
            throw invalid_argument("Invalid address: must be 1-100 characters");
        }
        this->address = address;
        
        // Validate and set contact email
        if (!Common::isValidEmail(contactEmail)) {
            throw invalid_argument("Invalid contact email format");
        }
        this->contactEmail = contactEmail;
        
        // Validate and set emergency contact (accept either phone number or email)
        if (!(Common::isValidPhoneNumber(emergencyContact) || Common::isValidEmail(emergencyContact))) {
            throw invalid_argument("Invalid emergency contact: must be a valid phone number or email address");
        }
        this->emergencyContact = emergencyContact;
        
        // Validate and set enrollment date
        if (!Common::isValidDateFormat(enrollmentDate)) {
            throw invalid_argument("Invalid enrollment date format: must be YYYY-MM-DD");
        }
        if (!Common::isDateNotFuture(enrollmentDate)) {
            throw invalid_argument("Invalid enrollment date: cannot be in the future");
        }
        this->enrollmentDate = enrollmentDate;
        
        // Initialize empty collections with optimized capacity
        enrolledCourses.clear();
        enrolledCourses.reserve(MAX_ENROLLMENTS);  // Reserve space for maximum enrollments
        
        assessments.clear();
        assessments.reserve(20);  // Reserve space for estimated assessments
    }
    
    // Copy constructor
    Student::Student(const Student& other)
        : rollNumber(other.rollNumber),
          firstName(other.firstName),
          lastName(other.lastName),
          dateOfBirth(other.dateOfBirth),
          address(other.address),
          contactEmail(other.contactEmail),
          emergencyContact(other.emergencyContact),
          enrollmentDate(other.enrollmentDate),
          enrolledCourses(other.enrolledCourses),
          assessments(other.assessments) {
    }
    
    // Assignment operator
    Student& Student::operator=(const Student& other) {
        if (this != &other) {
            // Note: rollNumber is const and cannot be changed
            firstName = other.firstName;
            lastName = other.lastName;
            dateOfBirth = other.dateOfBirth;
            address = other.address;
            contactEmail = other.contactEmail;
            emergencyContact = other.emergencyContact;
            enrollmentDate = other.enrollmentDate;
            enrolledCourses = other.enrolledCourses;
            assessments = other.assessments;
        }
        return *this;
    }
    
    // === DERIVED GETTERS ===
    string Student::getFullName() const {
        return firstName + " " + lastName;
    }
    
    int Student::getAge() const {
        // Simple age calculation - for now return a placeholder
        // In a real implementation, would parse date and calculate difference
        return 8; // Primary school age placeholder
    }
    
    // === SETTER METHODS ===
    void Student::setFirstName(const string& firstName) {
        if (!Common::isValidName(firstName)) {
            throw invalid_argument("Invalid first name: must contain only alphabetic characters and not be empty");
        }
        this->firstName = firstName;
    }
    
    void Student::setLastName(const string& lastName) {
        if (!Common::isValidName(lastName)) {
            throw invalid_argument("Invalid last name: must contain only alphabetic characters and not be empty");
        }
        this->lastName = lastName;
    }
    
    void Student::setContactEmail(const string& email) {
        if (!Common::isValidEmail(email)) {
            throw invalid_argument("Invalid contact email format");
        }
        this->contactEmail = email;
    }
    
    void Student::setEmergencyContact(const string& phoneNumber) {
        if (!Common::isValidPhoneNumber(phoneNumber)) {
            throw invalid_argument("Invalid emergency contact phone number format");
        }
        this->emergencyContact = phoneNumber;
    }
    
    // === COURSE ENROLLMENT MANAGEMENT ===
    void Student::enrollInCourse(shared_ptr<Course> course) {
        if (!course) {
            throw invalid_argument("Cannot enroll in null course");
        }
        
        // Check if already enrolled
        if (isEnrolledInCourse(course->getCourseId())) {
            throw runtime_error("Student is already enrolled in course: " + course->getCourseId());
        }
        
        // Check enrollment limit
        if (enrolledCourses.size() >= MAX_ENROLLMENTS) {
            throw runtime_error("Student has reached maximum enrollment limit of " + 
                                   to_string(MAX_ENROLLMENTS) + " courses");
        }
        
        // Memory management: Reserve space if needed to avoid frequent reallocations
        if (enrolledCourses.capacity() < enrolledCourses.size() + 1) {
            enrolledCourses.reserve(MAX_ENROLLMENTS);
        }
        
        enrolledCourses.push_back(course);
    }

    void Student::withdrawFromCourse(const string& courseId) {
        auto it = find_if(enrolledCourses.begin(), enrolledCourses.end(),
            [&courseId](const shared_ptr<Course>& course) {
                return course && course->getCourseId() == courseId;
            });
            
        if (it == enrolledCourses.end()) {
            throw runtime_error("Student is not enrolled in course: " + courseId);
        }
        
        // Memory management: Remove and shrink if needed
        enrolledCourses.erase(it);
        
        // Optional: Shrink vector if significantly smaller than capacity
        if (enrolledCourses.size() < enrolledCourses.capacity() / 2 && enrolledCourses.capacity() > MAX_ENROLLMENTS) {
            enrolledCourses.shrink_to_fit();
        }
    }

    bool Student::isEnrolledInCourse(const string& courseId) const {
        return any_of(enrolledCourses.begin(), enrolledCourses.end(),
            [&courseId](const shared_ptr<Course>& course) {
                return course && course->getCourseId() == courseId;
            });
    }

    vector<shared_ptr<Course>> Student::getEnrolledCourses() const {
        return enrolledCourses;
    }
    
    int Student::getEnrollmentCount() const {
        return static_cast<int>(enrolledCourses.size());
    }
    
    // === ASSESSMENT MANAGEMENT ===
    void Student::addAssessment(shared_ptr<Assessment> assessment) {
        if (!assessment) {
            throw invalid_argument("Cannot add null assessment");
        }
        
        // Verify assessment belongs to this student
        if (assessment->getStudentRollNumber() != rollNumber) {
            throw invalid_argument("Assessment does not belong to this student");
        }
        
        // Check if assessment already exists
        auto it = find_if(assessments.begin(), assessments.end(),
            [&assessment](const shared_ptr<Assessment>& existing) {
                return existing && existing->getAssessmentId() == assessment->getAssessmentId();
            });
            
        if (it != assessments.end()) {
            throw runtime_error("Assessment already exists: " + assessment->getAssessmentId());
        }
        
        // Memory management: Reserve space for assessments (estimate 20 assessments max per student)
        static constexpr size_t ESTIMATED_MAX_ASSESSMENTS = 20;
        if (assessments.capacity() < assessments.size() + 1) {
            assessments.reserve(ESTIMATED_MAX_ASSESSMENTS);
        }
        
        assessments.push_back(assessment);
    }

    void Student::removeAssessment(const string& assessmentId) {
        auto it = find_if(assessments.begin(), assessments.end(),
            [&assessmentId](const shared_ptr<Assessment>& assessment) {
                return assessment && assessment->getAssessmentId() == assessmentId;
            });
            
        if (it == assessments.end()) {
            throw runtime_error("Assessment not found: " + assessmentId);
        }
        
        assessments.erase(it);
    }

    vector<shared_ptr<Assessment>> Student::getAssessments() const {
        return assessments;
    }

    vector<shared_ptr<Assessment>> Student::getAssessmentsForCourse(const string& courseId) const {
        vector<shared_ptr<Assessment>> courseAssessments;
        
        for (const auto& assessment : assessments) {
            if (assessment && assessment->getCourseId() == courseId) {
                courseAssessments.push_back(assessment);
            }
        }
        
        return courseAssessments;
    }
    
    // === GRADE CALCULATION AND REPORTING ===
    double Student::getOverallGrade() const {
        if (assessments.empty()) {
            return 0.0;
        }
        
        double totalGrade = 0.0;
        int validAssessments = 0;
        
        for (const auto& assessment : assessments) {
            if (assessment) {
                totalGrade += assessment->getCalculatedGrade();
                validAssessments++;
            }
        }
        
        return validAssessments > 0 ? totalGrade / validAssessments : 0.0;
    }
    
    double Student::getCourseGrade(const string& courseId) const {
        auto courseAssessments = getAssessmentsForCourse(courseId);
        
        if (courseAssessments.empty()) {
            return 0.0;
        }
        
        double totalGrade = 0.0;
        for (const auto& assessment : courseAssessments) {
            if (assessment) {
                totalGrade += assessment->getCalculatedGrade();
            }
        }
        
        return totalGrade / courseAssessments.size();
    }

    string Student::getGradeStatus() const {
        double overallGrade = getOverallGrade();
        return overallGrade >= PASS_THRESHOLD ? "Pass" : "Fail";
    }
    
    // === DISPLAY AND FORMATTING ===
    void Student::displayStudentInfo() const {
        cout << "\n=== Student Information ===" << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << getFullName() << endl;
        cout << "Age: " << getAge() << " years" << endl;
        cout << "Date of Birth: " << dateOfBirth << endl;
        cout << "Address: " << address << endl;
        cout << "Contact Email: " << contactEmail << endl;
        cout << "Emergency Contact: " << emergencyContact << endl;
        cout << "Enrollment Date: " << enrollmentDate << endl;
        cout << "Overall Grade: " << fixed << setprecision(1) << getOverallGrade() << "%" << endl;
        cout << "Status: " << getGradeStatus() << endl;
    }
    
    void Student::displayEnrollmentSummary() const {
        cout << "\n=== Enrollment Summary ===" << endl;
        cout << "Student: " << getFullName() << " (Roll: " << rollNumber << ")" << endl;
        cout << "Enrolled Courses: " << enrolledCourses.size() << "/" << MAX_ENROLLMENTS << endl;

        if (!enrolledCourses.empty()) {
            cout << "\nCourses:" << endl;
            for (const auto& course : enrolledCourses) {
                if (course) {
                    cout << "  - " << course->getCourseId() << ": " << course->getCourseName() << endl;
                }
            }
        }
    }
    
    void Student::displayGradeSummary() const {
        cout << "\n=== Grade Summary ===" << endl;
        cout << "Student: " << getFullName() << " (Roll: " << rollNumber << ")" << endl;
        cout << "Total Assessments: " << assessments.size() << endl;
        cout << "Overall Grade: " << fixed << setprecision(1) << getOverallGrade() << "%" << endl;
        cout << "Status: " << getGradeStatus() << endl;

        if (!assessments.empty()) {
            cout << "\nAssessment Breakdown:" << endl;
            for (const auto& assessment : assessments) {
                if (assessment) {
                    cout << "  " << assessment->getAssessmentId() 
                              << " (" << assessment->getCourseId() << "): "
                              << fixed << setprecision(1) 
                              << assessment->getCalculatedGrade() << "%" << endl;
                }
            }
        }
    }
    
    string Student::toCSVString() const {
        ostringstream oss;
        oss << rollNumber << ","
            << firstName << ","
            << lastName << ","
            << dateOfBirth << ","
            << address << ","
            << contactEmail << ","
            << emergencyContact << ","
            << enrollmentDate << ","
            << fixed << setprecision(1) << getOverallGrade() << ","
            << getGradeStatus();
        return oss.str();
    }
    
    // === COMPARISON OPERATORS ===
    bool Student::operator==(const Student& other) const {
        return rollNumber == other.rollNumber;
    }
    
    bool Student::operator!=(const Student& other) const {
        return !(*this == other);
    }
    
    bool Student::operator<(const Student& other) const {
        return rollNumber < other.rollNumber;
    }
    
    // Stream operator
    ostream& operator<<(ostream& os, const Student& student) {
        os << "Student[" << student.getRollNumber() << "]: " << student.getFullName() 
           << " (Grade: " << fixed << setprecision(1) << student.getOverallGrade() << "%)";
        return os;
    }
}
