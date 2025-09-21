# Course Entity Interface Contract

## Class Interface Specification

### Constructor
```cpp
Course(const string& courseId, const string& courseName, int credits, 
       const string& description, int duration);
```

**Preconditions**:
- courseId follows pattern: 3-4 letters + 3 digits (e.g., "MATH101")
- courseId is unique across all courses
- courseName is non-empty, max 100 characters
- credits in range 1-6
- description max 500 characters (can be empty)
- duration in range 1-52 weeks

**Postconditions**:
- Course object created with validated data
- Empty enrolledStudents collection initialized
- Course marked as active and available for enrollment

### Getter Methods
```cpp
const string& getCourseId() const;          // Returns immutable course ID
const string& getCourseName() const;        // Returns course name
int getCredits() const;                     // Returns credit hours
const string& getDescription() const;       // Returns course description
int getDuration() const;                    // Returns duration in weeks
const vector<Student*>& getEnrolledStudents() const; // Returns enrolled students
int getEnrollmentCount() const;             // Returns number of enrolled students
```

**Preconditions**: Valid Course object
**Postconditions**: Returns immutable reference or value of requested field

### Student Enrollment Management
```cpp
bool enrollStudent(Student* student);       // Add student to course
bool dropStudent(int rollNumber);           // Remove student from course
bool hasStudent(int rollNumber) const;      // Check if student enrolled
Student* findStudent(int rollNumber) const; // Find enrolled student
```

**enrollStudent Preconditions**:
- student pointer is not null
- student not already enrolled in course
- course is active and accepting enrollments

**enrollStudent Postconditions**:
- student added to enrolledStudents
- bidirectional relationship established
- returns true on success, false if already enrolled

**dropStudent Preconditions**:
- rollNumber refers to currently enrolled student

**dropStudent Postconditions**:
- student removed from enrolledStudents
- bidirectional relationship removed
- returns true on success, false if not enrolled

### Course Information Management
```cpp
bool updateCourseName(const string& newName);       // Update course name
bool updateDescription(const string& newDescription); // Update description
bool updateCredits(int newCredits);                 // Update credit hours
bool updateDuration(int newDuration);               // Update duration
```

**Update Method Preconditions**:
- newName: non-empty, max 100 characters
- newDescription: max 500 characters
- newCredits: range 1-6
- newDuration: range 1-52 weeks

**Update Method Postconditions**:
- Field updated with new value
- returns true on success, false on validation failure

### Statistics and Reporting
```cpp
double getAverageGrade() const;              // Calculate average grade for course
int getPassingStudents() const;              // Count students with passing grades
int getFailingStudents() const;              // Count students with failing grades
void generateClassReport() const;            // Generate comprehensive class report
```

**Preconditions**: Valid Course object with enrolled students
**Postconditions**: Returns calculated statistics or displays formatted report

### Display Methods
```cpp
void displayInfo() const;                    // Display course information
void displayEnrolledStudents() const;       // Display all enrolled students
void displayGradeDistribution() const;      // Display grade statistics
void displayDetailedReport() const;         // Display comprehensive report
```

**Preconditions**: Valid Course object
**Postconditions**: Formatted information output to console

## Validation Rules

### Input Validation
- Course ID: Pattern matching [A-Z]{3,4}[0-9]{3}, uniqueness checked by System
- Course name: Non-empty, max 100 characters, printable characters only
- Credits: Integer range 1-6 inclusive
- Description: Max 500 characters, printable characters only
- Duration: Integer range 1-52 inclusive

### Business Rule Validation
- Course ID immutable after construction
- Student enrollment requires valid Student object
- No duplicate student enrollments
- Course updates preserve referential integrity
- Course deletion requires all students unenrolled first

### Error Handling
- Invalid input throws std::invalid_argument with descriptive message
- Null pointer operations return false or throw std::runtime_error
- Business rule violations return false with error logging
- Referential integrity violations prevent operation completion

## Memory Management Contract

### Ownership Rules
- Course holds non-owning pointers to Student objects
- Course lifetime managed by System class
- No ownership of Student objects (association only)
- Bidirectional relationships maintained through pointer updates

### Pointer Safety
- Student pointers validated before dereferencing
- Null pointer checks in all pointer operations
- Dangling pointer detection during student removal
- RAII principles ensure automatic cleanup

### Relationship Management
- Enrollment creates bidirectional pointers
- Unenrollment removes pointers from both sides
- Student deletion triggers automatic unenrollment
- Course deletion requires prior student unenrollment

## Performance Considerations

### Search Operations
- Student lookup by roll number: O(n) linear search
- Enrollment status check: O(n) linear search
- For large enrollments, consider hash map optimization

### Memory Usage
- Minimal memory overhead with pointer-based relationships
- No duplicate student data storage
- Efficient vector-based storage for enrolled students

## Thread Safety
- Single-threaded application design
- No concurrent access protection required
- All operations assumed to run in main thread context
