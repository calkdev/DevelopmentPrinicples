# FileHandler Repository Interface Contract

## Class Interface Specification

### Static Data Loading Methods
```cpp
static bool loadStudentsFromFile(vector<Student>& students);
static bool loadCoursesFromFile(vector<Course>& courses);
static bool loadAssessmentsFromFile(vector<Assessment>& assessments, 
                                  const vector<Student>& students,
                                  const vector<Course>& courses);
static bool loadEnrollmentsFromFile(vector<Student>& students, 
                                   const vector<Course>& courses);
```

**Preconditions**:
- File paths must be valid and accessible
- Container references must be valid
- For assessments/enrollments: student and course collections must be populated

**Postconditions**:
- Collections populated with data from CSV files
- Referential integrity established between entities
- returns true on successful load, false on error

### Static Data Saving Methods
```cpp
static bool saveStudentsToFile(const vector<Student>& students);
static bool saveCoursesToFile(const vector<Course>& courses);
static bool saveAssessmentsToFile(const vector<Assessment>& assessments);
static bool saveEnrollmentsToFile(const vector<Student>& students);
```

**Preconditions**:
- Collections contain valid entity objects
- File system writable at target locations
- Data passes validation checks

**Postconditions**:
- CSV files updated with current entity data
- File format preserved with headers
- returns true on successful save, false on error

### Individual Entity Operations
```cpp
static bool addStudentToFile(const Student& student);
static bool updateStudentInFile(const Student& student);
static bool removeStudentFromFile(int rollNumber);

static bool addCourseToFile(const Course& course);
static bool updateCourseInFile(const Course& course);
static bool removeCourseFromFile(const string& courseId);

static bool addAssessmentToFile(const Assessment& assessment);
static bool updateAssessmentInFile(const Assessment& assessment);
static bool removeAssessmentFromFile(const string& assessmentId);
```

**Preconditions**:
- Entity objects must be valid and complete
- For updates: entity must exist in file
- For removes: entity must exist and have no dependencies

**Postconditions**:
- File updated with entity changes
- Referential integrity maintained
- returns true on success, false on error or constraint violation

### Data Validation and Integrity
```cpp
static bool validateFileFormat(const string& filePath, const string& expectedHeader);
static bool checkReferentialIntegrity(const vector<Student>& students,
                                     const vector<Course>& courses,
                                     const vector<Assessment>& assessments);
static bool backupDataFiles();
static bool restoreFromBackup();
```

**validateFileFormat Preconditions**:
- filePath points to existing, readable file
- expectedHeader contains comma-separated field names

**validateFileFormat Postconditions**:
- returns true if file format matches expected structure
- returns false if header mismatch or file corruption detected

### Utility Methods
```cpp
static vector<string> parseCSVLine(const string& line);
static string escapeCSVField(const string& field);
static string formatDateForCSV(const string& date);
static bool isValidDate(const string& date);
static bool isValidEmail(const string& email);
```

**parseCSVLine Preconditions**:
- line is a valid CSV row string

**parseCSVLine Postconditions**:
- returns vector of field values
- handles quoted fields and escape characters
- empty vector on parse error

## File Format Specifications

### Students.csv Format
```
RollNumber,FirstName,LastName,DateOfBirth,ContactEmail,EmergencyContact,EnrollmentDate
12345,"John","Smith","2010-05-15","parent@email.com","emergency@email.com","2025-02-01"
```

### Courses.csv Format
```
CourseId,CourseName,Credits,Description,Duration
"MATH101","Mathematics Year 3",3,"Basic arithmetic and problem solving",40
```

### Assessments.csv Format
```
AssessmentId,StudentRollNumber,CourseId,InternalMarks,FinalMarks,AssessmentDate,CalculatedGrade
"ASS001",12345,"MATH101",75.0,82.0,"2025-06-15",79.1
```

### Enrollments.csv Format
```
EnrollmentId,StudentRollNumber,CourseId,EnrollmentDate,Status
"ENR001",12345,"MATH101","2025-02-01","Active"
```

## Error Handling Contract

### File I/O Error Categories
- **FileNotFound**: CSV file missing or inaccessible
- **PermissionDenied**: Insufficient file system permissions
- **CorruptData**: Invalid CSV format or data corruption
- **ValidationFailure**: Data fails business rule validation

### Error Response Protocol
```cpp
enum class FileOperationResult {
    Success,
    FileNotFound,
    PermissionDenied,
    InvalidFormat,
    ValidationFailure,
    ReferentialIntegrityViolation
};
```

### Error Logging
- All errors logged with timestamp and context information
- User-friendly error messages for common issues
- Detailed technical information for debugging
- Error recovery suggestions when possible

## Data Integrity Guarantees

### Atomic Operations
- File updates are atomic (write to temp file, then rename)
- Backup created before destructive operations
- Rollback capability on operation failure

### Referential Integrity
- Student roll numbers referenced in assessments must exist
- Course IDs referenced in assessments and enrollments must exist
- Assessment deletion cascades properly
- Orphaned record detection and cleanup

### Validation Rules
- All dates in YYYY-MM-DD format and valid calendar dates
- Email addresses match standard email format pattern
- Numeric fields within specified ranges
- Text fields within length limits and character restrictions

## Performance Characteristics

### File Operations
- Sequential read/write for simplicity and reliability
- Minimal memory usage during large file operations
- Efficient CSV parsing with minimal string copying

### Scalability Considerations
- Linear performance with respect to file size
- Memory usage proportional to largest entity collection
- Suitable for primary school scale (hundreds of students)

## Backup and Recovery

### Backup Strategy
```cpp
static bool createBackup(const string& suffix = "");
static bool listAvailableBackups(vector<string>& backupList);
static bool restoreFromBackup(const string& backupName);
```

### Recovery Procedures
- Automatic backup before destructive operations
- Manual backup capability for major operations
- Point-in-time recovery from named backups
- Data validation after restoration
