# FileHandler Class Manual Test Scenarios

**Test File**: `tests/manual_test_scenarios/filehandler_tests.md`  
**Purpose**: Comprehensive test scenarios for FileHandler with CSV operations and error handling  
**Learning Objective**: Understanding file I/O testing and error condition handling  
**Status**: Tests must FAIL until T017 (FileHandler.cpp implementation) is completed

## Test Categories

### 1. CSV File Loading Tests

#### Test F001: Load Valid Students CSV File
**Description**: Load students from properly formatted CSV file
**Setup**: Create `data/students.csv` with valid student records
**CSV Content**:
```csv
RollNumber,FirstName,LastName,DateOfBirth,ContactEmail,EmergencyContact,EnrollmentDate
12345,John,Smith,2010-05-15,parent@email.com,emergency@contact.com,2025-02-01
12346,Jane,Doe,2010-03-22,jane.parent@email.com,jane.emergency@contact.com,2025-02-01
```

**Expected Behavior**: 
- File loaded successfully
- Two student objects created
- All fields parsed correctly
- Vector populated with students

**Test Execution**: Call `FileHandler::loadStudentsFromFile(studentVector)`
**Expected Result**: PASS after T017 implementation
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F002: Load Valid Courses CSV File
**Description**: Load courses from properly formatted CSV file
**Setup**: Create `data/courses.csv` with valid course records
**CSV Content**:
```csv
CourseId,CourseName,Credits,Description,Duration
MATH101,Mathematics Year 3,3,Basic arithmetic and problem solving,40
ENG201,English Year 5,4,Advanced reading and writing skills,36
```

**Expected Behavior**: 
- File loaded successfully
- Two course objects created
- All fields parsed correctly
- Vector populated with courses

**Test Execution**: Call `FileHandler::loadCoursesFromFile(courseVector)`
**Expected Result**: PASS after T017 implementation
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F003: Load Valid Assessments CSV File
**Description**: Load assessments from properly formatted CSV file
**Setup**: Create `data/assessments.csv` with valid assessment records
**CSV Content**:
```csv
AssessmentId,StudentRollNumber,CourseId,InternalMarks,FinalMarks,AssessmentDate,CalculatedGrade
ASS001,12345,MATH101,75,82,2025-06-15,79.1
ASS002,12346,ENG201,88,90,2025-06-20,89.4
```

**Expected Behavior**: 
- File loaded successfully
- Two assessment objects created
- Calculated grades match expected values
- All relationships established correctly

**Test Execution**: Call `FileHandler::loadAssessmentsFromFile(assessmentVector)`
**Expected Result**: PASS after T017 implementation
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F004: Load Enrollments and Establish Relationships
**Description**: Load enrollment data and establish student-course relationships
**Setup**: Create `data/enrollments.csv` with enrollment records
**CSV Content**:
```csv
EnrollmentId,StudentRollNumber,CourseId,EnrollmentDate,Status
ENR001,12345,MATH101,2025-02-01,Active
ENR002,12346,ENG201,2025-02-01,Active
ENR003,12345,ENG201,2025-02-15,Active
```

**Expected Behavior**: 
- Enrollment relationships established
- Students linked to appropriate courses
- Courses linked to appropriate students
- Bidirectional relationships maintained

**Test Execution**: Call `FileHandler::loadEnrollments(studentVector, courseVector)`
**Expected Result**: PASS after T017 implementation
**Current Status**: WILL FAIL - FileHandler class does not exist yet

### 2. File Not Found and Access Error Tests

#### Test F005: Missing Students File
**Description**: Attempt to load from non-existent students file
**Setup**: Ensure `data/students.csv` does not exist
**Expected Behavior**: 
- Method should handle missing file gracefully
- Return appropriate error status
- Display meaningful error message
- Not crash the application

**Test Execution**: Call `FileHandler::loadStudentsFromFile(studentVector)`
**Expected Result**: FAIL with appropriate error message
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F006: Permission Denied on File Access
**Description**: Attempt to load from file with restricted permissions
**Setup**: Create file with read-only permissions (chmod 000)
**Expected Behavior**: 
- Method should detect permission issue
- Return appropriate error status
- Display meaningful error message
- Handle gracefully without crash

**Test Execution**: Call `FileHandler::loadStudentsFromFile(studentVector)`
**Expected Result**: FAIL with permission error message
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F007: Corrupted File Recovery
**Description**: Attempt to load from corrupted or binary file
**Setup**: Create file with binary content or random data
**Expected Behavior**: 
- Method should detect invalid content
- Skip corrupted records where possible
- Report corruption issues
- Continue processing valid records if any

**Test Execution**: Call `FileHandler::loadStudentsFromFile(studentVector)`
**Expected Result**: Partial load with error reporting
**Current Status**: WILL FAIL - FileHandler class does not exist yet

### 3. CSV Format and Parsing Error Tests

#### Test F008: Missing CSV Headers
**Description**: Load file without proper CSV headers
**Setup**: Create CSV file without header row
**CSV Content**:
```csv
12345,John,Smith,2010-05-15,parent@email.com,emergency@contact.com,2025-02-01
```

**Expected Behavior**: 
- Method should detect missing headers
- Report format error
- Either reject file or handle with default headers

**Test Execution**: Call `FileHandler::loadStudentsFromFile(studentVector)`
**Expected Result**: Error about missing headers
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F009: Insufficient CSV Fields
**Description**: Load records with missing required fields
**Setup**: Create CSV with incomplete records
**CSV Content**:
```csv
RollNumber,FirstName,LastName,DateOfBirth,ContactEmail,EmergencyContact,EnrollmentDate
12345,John,Smith,2010-05-15,parent@email.com
12346,Jane,Doe,2010-03-22,jane.parent@email.com,jane.emergency@contact.com,2025-02-01
```

**Expected Behavior**: 
- Skip records with insufficient fields
- Report line numbers with errors
- Continue processing valid records
- Provide detailed error feedback

**Test Execution**: Call `FileHandler::loadStudentsFromFile(studentVector)`
**Expected Result**: Partial load with error reporting
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F010: Excessive CSV Fields
**Description**: Load records with more fields than expected
**Setup**: Create CSV with extra fields
**CSV Content**:
```csv
RollNumber,FirstName,LastName,DateOfBirth,ContactEmail,EmergencyContact,EnrollmentDate,ExtraField
12345,John,Smith,2010-05-15,parent@email.com,emergency@contact.com,2025-02-01,Extra
```

**Expected Behavior**: 
- Ignore extra fields gracefully
- Process required fields correctly
- Continue with successful parsing
- Optionally warn about extra fields

**Test Execution**: Call `FileHandler::loadStudentsFromFile(studentVector)`
**Expected Result**: Successful load with optional warning
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F011: Quoted Fields with Commas
**Description**: Parse CSV fields containing commas within quotes
**Setup**: Create CSV with quoted fields containing commas
**CSV Content**:
```csv
RollNumber,FirstName,LastName,DateOfBirth,ContactEmail,EmergencyContact,EnrollmentDate
12345,John,Smith,2010-05-15,"parent@email.com","Contact, Emergency",2025-02-01
```

**Expected Behavior**: 
- Properly parse quoted fields
- Handle embedded commas correctly
- Maintain field integrity
- Create objects with correct data

**Test Execution**: Call `FileHandler::loadStudentsFromFile(studentVector)`
**Expected Result**: Successful parsing with comma-containing fields
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F012: Quoted Fields with Quotes
**Description**: Parse CSV fields containing escaped quotes
**Setup**: Create CSV with escaped quotes within fields
**CSV Content**:
```csv
RollNumber,FirstName,LastName,DateOfBirth,ContactEmail,EmergencyContact,EnrollmentDate
12345,John,Smith,2010-05-15,"parent@email.com","Emergency ""Main"" Contact",2025-02-01
```

**Expected Behavior**: 
- Properly handle escaped quotes
- Parse fields with embedded quotes correctly
- Maintain data integrity
- Handle CSV escaping standards

**Test Execution**: Call `FileHandler::loadStudentsFromFile(studentVector)`
**Expected Result**: Successful parsing with quote-containing fields
**Current Status**: WILL FAIL - FileHandler class does not exist yet

### 4. Data Validation During Loading Tests

#### Test F013: Invalid Roll Number in CSV
**Description**: Load CSV with invalid roll numbers
**Setup**: Create CSV with invalid roll number values
**CSV Content**:
```csv
RollNumber,FirstName,LastName,DateOfBirth,ContactEmail,EmergencyContact,EnrollmentDate
-1,John,Smith,2010-05-15,parent@email.com,emergency@contact.com,2025-02-01
ABC,Jane,Doe,2010-03-22,jane.parent@email.com,jane.emergency@contact.com,2025-02-01
```

**Expected Behavior**: 
- Validate roll numbers during parsing
- Skip records with invalid roll numbers
- Report validation errors with line numbers
- Continue processing valid records

**Test Execution**: Call `FileHandler::loadStudentsFromFile(studentVector)`
**Expected Result**: Partial load with validation error reporting
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F014: Invalid Email Formats in CSV
**Description**: Load CSV with malformed email addresses
**Setup**: Create CSV with invalid email formats
**CSV Content**:
```csv
RollNumber,FirstName,LastName,DateOfBirth,ContactEmail,EmergencyContact,EnrollmentDate
12345,John,Smith,2010-05-15,invalid.email,emergency@contact.com,2025-02-01
12346,Jane,Doe,2010-03-22,jane@,jane.emergency@contact.com,2025-02-01
```

**Expected Behavior**: 
- Validate email formats during parsing
- Skip or flag records with invalid emails
- Report email validation errors
- Maintain data integrity

**Test Execution**: Call `FileHandler::loadStudentsFromFile(studentVector)`
**Expected Result**: Validation errors with email format feedback
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F015: Invalid Date Formats in CSV
**Description**: Load CSV with malformed date values
**Setup**: Create CSV with invalid date formats
**CSV Content**:
```csv
RollNumber,FirstName,LastName,DateOfBirth,ContactEmail,EmergencyContact,EnrollmentDate
12345,John,Smith,15-05-2010,parent@email.com,emergency@contact.com,2025-02-01
12346,Jane,Doe,2010/03/22,jane.parent@email.com,jane.emergency@contact.com,01-02-2025
```

**Expected Behavior**: 
- Validate date formats during parsing
- Reject records with invalid date formats
- Report date format errors
- Continue with valid records

**Test Execution**: Call `FileHandler::loadStudentsFromFile(studentVector)`
**Expected Result**: Date validation errors with format feedback
**Current Status**: WILL FAIL - FileHandler class does not exist yet

### 5. CSV File Saving Tests

#### Test F016: Save Students to CSV File
**Description**: Save student vector to CSV file
**Setup**: Create student objects in memory
**Expected Behavior**: 
- Create properly formatted CSV file
- Include appropriate headers
- Quote fields containing special characters
- Maintain data integrity during save

**Test Execution**: Call `FileHandler::saveStudentsToFile(studentVector)`
**Expected Result**: Valid CSV file created with student data
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F017: Save Courses to CSV File
**Description**: Save course vector to CSV file
**Setup**: Create course objects in memory
**Expected Behavior**: 
- Create properly formatted CSV file
- Handle course descriptions with special characters
- Maintain field order and formatting
- Include all required course data

**Test Execution**: Call `FileHandler::saveCoursesToFile(courseVector)`
**Expected Result**: Valid CSV file created with course data
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F018: Save Assessments to CSV File
**Description**: Save assessment vector to CSV file
**Setup**: Create assessment objects in memory
**Expected Behavior**: 
- Create properly formatted CSV file
- Include calculated grades with proper precision
- Maintain assessment relationships
- Handle all assessment data fields

**Test Execution**: Call `FileHandler::saveAssessmentsToFile(assessmentVector)`
**Expected Result**: Valid CSV file created with assessment data
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F019: Save Enrollments to CSV File
**Description**: Save enrollment relationships to CSV file
**Setup**: Create enrollment relationships in memory
**Expected Behavior**: 
- Create enrollment CSV with proper relationships
- Maintain referential integrity
- Include enrollment status and dates
- Handle multiple enrollments per student

**Test Execution**: Call `FileHandler::saveEnrollmentsToFile(studentVector, courseVector)`
**Expected Result**: Valid enrollment CSV file created
**Current Status**: WILL FAIL - FileHandler class does not exist yet

### 6. File Writing Error Tests

#### Test F020: Write to Read-Only Directory
**Description**: Attempt to save to read-only directory
**Setup**: Set data directory to read-only permissions
**Expected Behavior**: 
- Detect write permission issues
- Return appropriate error status
- Display meaningful error message
- Handle gracefully without crash

**Test Execution**: Call `FileHandler::saveStudentsToFile(studentVector)`
**Expected Result**: Write permission error with helpful message
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F021: Disk Full During Write
**Description**: Simulate disk full condition during file write
**Setup**: Create scenario with insufficient disk space
**Expected Behavior**: 
- Detect disk space issues
- Handle partial write gracefully
- Provide appropriate error feedback
- Maintain existing file if possible

**Test Execution**: Call `FileHandler::saveStudentsToFile(studentVector)`
**Expected Result**: Disk space error with recovery guidance
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F022: Concurrent File Access
**Description**: Handle concurrent access to same file
**Setup**: Simulate multiple processes accessing same file
**Expected Behavior**: 
- Handle file locking appropriately
- Detect access conflicts
- Provide retry mechanisms or error feedback
- Maintain data integrity

**Test Execution**: Call save/load methods concurrently
**Expected Result**: Safe handling of concurrent access
**Current Status**: WILL FAIL - FileHandler class does not exist yet

### 7. Data Integrity and Backup Tests

#### Test F023: File Backup Before Overwrite
**Description**: Create backup before overwriting existing file
**Setup**: Existing file with previous data
**Expected Behavior**: 
- Create backup of existing file
- Write new data to main file
- Maintain backup for recovery
- Handle backup naming conflicts

**Test Execution**: Call save methods on existing files
**Expected Result**: Backup created before overwrite
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F024: Restore from Backup
**Description**: Restore data from backup file after corruption
**Setup**: Corrupted main file with valid backup
**Expected Behavior**: 
- Detect main file corruption
- Automatically attempt backup restoration
- Provide user notification of restoration
- Maintain data integrity

**Test Execution**: Load data after simulated corruption
**Expected Result**: Successful restoration from backup
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F025: Referential Integrity Validation
**Description**: Validate data relationships across files
**Setup**: Files with mismatched relationships
**Expected Behavior**: 
- Detect orphaned assessments (student/course not found)
- Report referential integrity violations
- Provide options for data cleanup
- Maintain valid relationships only

**Test Execution**: Load data with integrity issues
**Expected Result**: Integrity validation with error reporting
**Current Status**: WILL FAIL - FileHandler class does not exist yet

### 8. Performance and Large Dataset Tests

#### Test F026: Large Student Dataset Performance
**Description**: Test performance with large student file
**Setup**: CSV file with 10,000+ student records
**Expected Behavior**: 
- Load large dataset within reasonable time
- Maintain memory efficiency
- Provide progress feedback for large operations
- Handle large files without crashes

**Test Execution**: Call `FileHandler::loadStudentsFromFile()` with large file
**Expected Result**: Acceptable performance with large dataset
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F027: Memory Usage During Large Operations
**Description**: Monitor memory usage during large file operations
**Setup**: Large CSV files for all entity types
**Expected Behavior**: 
- Efficient memory usage during loading
- No memory leaks during operations
- Proper cleanup after operations
- Reasonable memory footprint

**Test Execution**: Load/save operations with memory monitoring
**Expected Result**: Efficient memory usage patterns
**Current Status**: WILL FAIL - FileHandler class does not exist yet

### 9. Cross-Platform Compatibility Tests

#### Test F028: Different Line Ending Handling
**Description**: Handle different line ending formats (Windows/Linux/Mac)
**Setup**: CSV files with different line endings
**Expected Behavior**: 
- Parse files with \r\n (Windows)
- Parse files with \n (Linux/Mac)
- Parse files with \r (old Mac)
- Maintain cross-platform compatibility

**Test Execution**: Load files with various line endings
**Expected Result**: Successful parsing regardless of line endings
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F029: Character Encoding Support
**Description**: Handle different character encodings
**Setup**: CSV files with various character encodings
**Expected Behavior**: 
- Handle UTF-8 encoding properly
- Support common special characters
- Maintain character integrity
- Provide encoding error feedback

**Test Execution**: Load files with special characters
**Expected Result**: Proper character handling and display
**Current Status**: WILL FAIL - FileHandler class does not exist yet

### 10. Error Recovery and Logging Tests

#### Test F030: Comprehensive Error Logging
**Description**: Verify detailed error logging for all operations
**Setup**: Various error conditions
**Expected Behavior**: 
- Log all file operation attempts
- Include timestamps and error details
- Provide sufficient information for debugging
- Maintain log file management

**Test Execution**: Trigger various error conditions
**Expected Result**: Comprehensive error logs generated
**Current Status**: WILL FAIL - FileHandler class does not exist yet

---

#### Test F031: Graceful Degradation
**Description**: System continues operating despite file errors
**Setup**: Various file operation failures
**Expected Behavior**: 
- System remains functional after file errors
- Provide alternative data sources if available
- Maintain core functionality without file access
- Clear user feedback about limitations

**Test Execution**: Trigger file errors during normal operation
**Expected Result**: System remains stable and functional
**Current Status**: WILL FAIL - FileHandler class does not exist yet

## Test Execution Summary

**Total Test Scenarios**: 31  
**Current Status**: ALL WILL FAIL - FileHandler class not implemented  
**Implementation Required**: T017 (FileHandler.cpp)  
**Success Criteria**: All tests PASS after FileHandler implementation  

## Learning Checkpoints

### Pre-Implementation Understanding
- [ ] File I/O requirements clearly documented
- [ ] CSV parsing and writing specifications understood
- [ ] Error handling scenarios comprehensively covered
- [ ] Data validation requirements specified
- [ ] Performance expectations established

### Post-Implementation Validation
- [ ] All file loading operations work correctly
- [ ] CSV parsing handles edge cases properly
- [ ] File writing operations maintain data integrity
- [ ] Error conditions handled gracefully
- [ ] Performance acceptable for expected usage
- [ ] Cross-platform compatibility maintained
- [ ] Data validation enforced during loading
- [ ] Backup and recovery mechanisms functional

## Mentorship Review Criteria

### Test Quality Assessment
- **File I/O Coverage**: Do tests cover all file operation scenarios?
- **Error Handling**: Are error conditions thoroughly tested?
- **Data Integrity**: Is data validation comprehensively tested?
- **Performance**: Are large dataset scenarios included?

### Learning Objectives
- **Understanding**: Does student understand file I/O complexities?
- **Error Handling**: Are robust error handling patterns demonstrated?
- **Data Validation**: Is input validation thoroughly understood?
- **TDD Compliance**: Were tests written before implementation?

### Critical Success Factors
- **Data Safety**: No data loss during file operations
- **Error Resilience**: System handles all error conditions gracefully
- **Performance**: Acceptable performance with realistic datasets
- **Cross-Platform**: Works consistently across different systems

**Note**: These test scenarios follow TDD principles - they MUST exist and MUST document expected failures before any FileHandler class implementation begins in T017.
