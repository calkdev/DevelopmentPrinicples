# Student Entity Interface Contract

## Class Interface Specification

### Constructor
```cpp
Student(int rollNumber, const string& firstName, const string& lastName, 
        const string& dateOfBirth, const string& contactEmail, 
        const string& emergencyContact, const string& enrollmentDate);
```

**Preconditions**:
- rollNumber > 0 and unique across all students
- firstName and lastName are non-empty and contain only alphabetic characters
- dateOfBirth follows YYYY-MM-DD format and is a valid past date
- contactEmail follows valid email format pattern
- emergencyContact is non-empty
- enrollmentDate follows YYYY-MM-DD format and is not in future

**Postconditions**:
- Student object created with immutable rollNumber
- All fields validated and stored
- Empty enrolledCourses and assessments collections initialized

### Getter Methods
```cpp
int getRollNumber() const;                    // Returns immutable roll number
const string& getFirstName() const;          // Returns first name
const string& getLastName() const;           // Returns last name
const string& getDateOfBirth() const;        // Returns birth date
const string& getContactEmail() const;       // Returns contact email
const string& getEmergencyContact() const;   // Returns emergency contact
const string& getEnrollmentDate() const;     // Returns enrollment date
const vector<Course*>& getEnrolledCourses() const;  // Returns course list
const vector<Assessment>& getAssessments() const;   // Returns assessments
```

**Preconditions**: Valid Student object
**Postconditions**: Returns immutable reference to requested field

### Course Management
```cpp
bool enrollInCourse(Course* course);         // Add course enrollment
bool dropCourse(const string& courseId);     // Remove course enrollment
bool isEnrolledIn(const string& courseId) const; // Check enrollment status
```

**enrollInCourse Preconditions**:
- course pointer is not null
- course exists and is active
- student not already enrolled in course

**enrollInCourse Postconditions**:
- course added to enrolledCourses
- bidirectional relationship established
- returns true on success, false if already enrolled

### Assessment Management
```cpp
bool addAssessment(const Assessment& assessment);        // Add assessment record
Assessment* getAssessmentForCourse(const string& courseId); // Get course assessment
bool hasAssessmentForCourse(const string& courseId) const;  // Check assessment exists
double getOverallGPA() const;                            // Calculate overall GPA
```

**addAssessment Preconditions**:
- assessment references this student's rollNumber
- student enrolled in assessment's course
- no existing assessment for same course

**addAssessment Postconditions**:
- assessment added to assessments collection
- returns true on success, false if duplicate

### Display Methods
```cpp
void displayInfo() const;                    // Display student information
void displayEnrolledCourses() const;        // Display enrolled courses
void displayAssessments() const;            // Display all assessments
void displayTranscript() const;             // Display academic transcript
```

**Preconditions**: Valid Student object
**Postconditions**: Formatted information output to console

## Validation Rules

### Input Validation
- Roll number: Positive integer, uniqueness checked by System class
- Names: Non-empty, alphabetic characters only, max 50 characters
- Dates: YYYY-MM-DD format, valid calendar dates
- Email: Standard email format pattern validation
- Text fields: Non-empty, reasonable length limits

### Business Rule Validation
- Roll number immutable after construction
- Course enrollment requires active course
- Assessment creation requires course enrollment
- No duplicate assessments per course
- Course drop removes related assessments

### Error Handling
- Invalid input throws std::invalid_argument with descriptive message
- Null pointer operations return false or throw std::runtime_error
- File I/O errors propagated to FileHandler level
- Business rule violations return false with error logging

## Memory Management Contract

### Ownership Rules
- Student owns Assessment objects (composition)
- Student holds non-owning pointers to Course objects
- Student lifetime managed by System class
- Assessment objects destroyed when Student destroyed

### Pointer Safety
- Course pointers validated before dereferencing
- Null pointer checks in all pointer operations
- No manual memory allocation/deallocation
- RAII principles ensure automatic cleanup

## Thread Safety
- Single-threaded application design
- No concurrent access protection required
- All operations assumed to run in main thread context
