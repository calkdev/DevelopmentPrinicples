# Student Class Manual Test Scenarios

**Test File**: `tests/manual_test_scenarios/student_tests.md`  
**Purpose**: Comprehensive test scenarios for Student entity following TDD principles  
**Learning Objective**: Understanding test-driven development and edge case planning  
**Status**: Tests must FAIL until T013 (Student.cpp implementation) is completed

## Test Categories

### 1. Constructor and Object Creation Tests

#### Test S001: Valid Student Creation
**Description**: Create student with all valid parameters
**Input Data**:
- rollNumber: 12345
- firstName: "John"
- lastName: "Smith"
- dateOfBirth: "2010-05-15"
- contactEmail: "parent@email.com"
- emergencyContact: "emergency@contact.com"
- enrollmentDate: "2025-02-01"

**Expected Behavior**: 
- Student object created successfully
- All getter methods return correct values
- enrolledCourses vector is empty initially
- assessments vector is empty initially

**Test Execution**: Manual verification through constructor call and getter validation
**Expected Result**: PASS after T013 implementation
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S002: Invalid Roll Number (Negative)
**Description**: Attempt to create student with negative roll number
**Input Data**: rollNumber: -1, other fields valid
**Expected Behavior**: Constructor should reject invalid roll number
**Validation**: Should throw exception or handle error gracefully
**Expected Result**: FAIL creation, appropriate error message
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S003: Invalid Roll Number (Zero)
**Description**: Attempt to create student with zero roll number
**Input Data**: rollNumber: 0, other fields valid
**Expected Behavior**: Constructor should reject zero as invalid
**Expected Result**: FAIL creation, error about minimum roll number
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S004: Invalid Roll Number (Too Large)
**Description**: Attempt to create student with roll number exceeding maximum
**Input Data**: rollNumber: 100000, other fields valid
**Expected Behavior**: Constructor should reject oversized roll number
**Expected Result**: FAIL creation, error about maximum roll number limit
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S005: Empty First Name
**Description**: Attempt to create student with empty first name
**Input Data**: firstName: "", other fields valid
**Expected Behavior**: Constructor should reject empty name
**Expected Result**: FAIL creation, error about required first name
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S006: Invalid First Name (Numbers)
**Description**: Attempt to create student with numeric characters in first name
**Input Data**: firstName: "John123", other fields valid
**Expected Behavior**: Constructor should reject non-alphabetic names
**Expected Result**: FAIL creation, error about name format
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S007: Invalid Email Format
**Description**: Attempt to create student with malformed email
**Input Data**: contactEmail: "invalid.email", other fields valid
**Expected Behavior**: Constructor should validate email format
**Expected Result**: FAIL creation, error about email format
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S008: Invalid Date Format
**Description**: Attempt to create student with invalid date format
**Input Data**: dateOfBirth: "15-05-2010", other fields valid
**Expected Behavior**: Constructor should enforce YYYY-MM-DD format
**Expected Result**: FAIL creation, error about date format
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S009: Future Enrollment Date
**Description**: Attempt to create student with future enrollment date
**Input Data**: enrollmentDate: "2026-12-31", other fields valid
**Expected Behavior**: Constructor should reject future enrollment dates
**Expected Result**: FAIL creation, error about future date
**Current Status**: WILL FAIL - Student class does not exist yet

### 2. Getter Method Tests

#### Test S010: getRollNumber() Immutability
**Description**: Verify roll number cannot be modified after creation
**Test Steps**:
1. Create student with rollNumber: 12345
2. Call getRollNumber() multiple times
3. Verify same value returned consistently
**Expected Behavior**: Immutable roll number, consistent returns
**Expected Result**: PASS after T013 implementation
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S011: All Getter Methods Return Correct Values
**Description**: Verify all getter methods return constructor values
**Test Steps**:
1. Create student with known values
2. Call each getter method
3. Compare returned values with input values
**Expected Behavior**: All getters return original constructor values
**Expected Result**: PASS after T013 implementation
**Current Status**: WILL FAIL - Student class does not exist yet

### 3. Course Enrollment Tests

#### Test S012: Initial Empty Course List
**Description**: Verify new student has no enrolled courses
**Test Steps**:
1. Create new student
2. Call getEnrolledCourses()
3. Check vector size
**Expected Behavior**: Empty course vector initially
**Expected Result**: PASS after T013 implementation
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S013: Single Course Enrollment
**Description**: Enroll student in one course
**Test Steps**:
1. Create student and course objects
2. Call student.enrollInCourse(course)
3. Verify course appears in getEnrolledCourses()
**Expected Behavior**: Course added to enrollment list
**Expected Result**: PASS after T013 and T014 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

---

#### Test S014: Multiple Course Enrollment
**Description**: Enroll student in multiple courses
**Test Steps**:
1. Create student and multiple course objects
2. Enroll in each course sequentially
3. Verify all courses appear in enrollment list
**Expected Behavior**: All courses tracked in order of enrollment
**Expected Result**: PASS after T013 and T014 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

---

#### Test S015: Duplicate Course Enrollment Prevention
**Description**: Prevent enrolling in same course twice
**Test Steps**:
1. Create student and course
2. Enroll in course successfully
3. Attempt to enroll in same course again
**Expected Behavior**: Second enrollment should be rejected
**Expected Result**: FAIL second enrollment, appropriate warning
**Current Status**: WILL FAIL - Classes do not exist yet

---

#### Test S016: Course Dropout Functionality
**Description**: Remove student from enrolled course
**Test Steps**:
1. Enroll student in course
2. Call dropFromCourse(course)
3. Verify course removed from enrollment list
**Expected Behavior**: Course removed, list updated correctly
**Expected Result**: PASS after T013 and T014 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

### 4. Assessment Management Tests

#### Test S017: Initial Empty Assessment List
**Description**: Verify new student has no assessments
**Test Steps**:
1. Create new student
2. Call getAssessments()
3. Check vector size
**Expected Behavior**: Empty assessment vector initially
**Expected Result**: PASS after T013 implementation
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S018: Add Assessment to Student
**Description**: Add assessment record to student
**Test Steps**:
1. Create student and assessment objects
2. Call addAssessment(assessment)
3. Verify assessment appears in getAssessments()
**Expected Behavior**: Assessment added to student record
**Expected Result**: PASS after T013 and T015 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

---

#### Test S019: Multiple Assessments per Course
**Description**: Add multiple assessments for same course
**Test Steps**:
1. Create student enrolled in course
2. Add multiple assessments for same course
3. Verify all assessments tracked correctly
**Expected Behavior**: Multiple assessments per course supported
**Expected Result**: PASS after T013 and T015 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

### 5. Display and Utility Tests

#### Test S020: displayInfo() Formatting
**Description**: Verify student information displays correctly
**Test Steps**:
1. Create student with test data
2. Call displayInfo()
3. Verify output format and completeness
**Expected Behavior**: Formatted output with all student details
**Expected Result**: PASS after T013 implementation
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S021: displayEnrolledCourses() with Empty List
**Description**: Display enrolled courses when none exist
**Test Steps**:
1. Create new student (no enrollments)
2. Call displayEnrolledCourses()
3. Verify appropriate message for empty list
**Expected Behavior**: "No courses enrolled" or similar message
**Expected Result**: PASS after T013 implementation
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S022: displayEnrolledCourses() with Courses
**Description**: Display enrolled courses when courses exist
**Test Steps**:
1. Create student and enroll in multiple courses
2. Call displayEnrolledCourses()
3. Verify all courses listed with proper formatting
**Expected Behavior**: Formatted list of all enrolled courses
**Expected Result**: PASS after T013 and T014 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

### 6. Edge Cases and Error Handling

#### Test S023: Very Long Names
**Description**: Test name length limits
**Input Data**: firstName with 51+ characters
**Expected Behavior**: Constructor should enforce length limits
**Expected Result**: FAIL creation or truncate appropriately
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S024: Special Characters in Names
**Description**: Test acceptable special characters
**Input Data**: Names with hyphens, apostrophes, spaces
**Expected Behavior**: Should accept valid special characters
**Expected Result**: PASS for valid characters, FAIL for invalid
**Current Status**: WILL FAIL - Student class does not exist yet

---

#### Test S025: Boundary Date Values
**Description**: Test date validation boundaries
**Test Cases**:
- February 29 on leap year: PASS
- February 29 on non-leap year: FAIL
- Invalid month (13): FAIL
- Invalid day (32): FAIL
**Expected Behavior**: Proper date validation
**Current Status**: WILL FAIL - Student class does not exist yet

### 7. Memory Management and Performance Tests

#### Test S026: Large Course List Performance
**Description**: Test performance with many enrolled courses
**Test Steps**:
1. Create student
2. Enroll in 100+ courses
3. Verify reasonable performance for operations
**Expected Behavior**: Acceptable performance, no memory issues
**Expected Result**: PASS after T013 and T014 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

---

#### Test S027: Object Destruction and Cleanup
**Description**: Verify proper cleanup when student object destroyed
**Test Steps**:
1. Create student with enrollments and assessments
2. Let object go out of scope
3. Verify no memory leaks or dangling pointers
**Expected Behavior**: Clean destruction, no memory leaks
**Expected Result**: PASS after T013 implementation
**Current Status**: WILL FAIL - Student class does not exist yet

## Test Execution Summary

**Total Test Scenarios**: 27  
**Current Status**: ALL WILL FAIL - Student class not implemented  
**Implementation Required**: T013 (Student.cpp), T014 (Course.cpp), T015 (Assessment.cpp)  
**Success Criteria**: All tests PASS after entity implementation  

## Learning Checkpoints

### Pre-Implementation Understanding
- [ ] Student entity requirements clearly documented
- [ ] Edge cases and error conditions identified
- [ ] Test scenarios cover all CRUD operations
- [ ] Validation requirements specified in detail

### Post-Implementation Validation
- [ ] All constructor validation tests pass
- [ ] Getter methods return correct values
- [ ] Course enrollment/dropout works correctly
- [ ] Assessment management functions properly
- [ ] Display methods format output correctly
- [ ] Error handling provides meaningful feedback
- [ ] Performance acceptable for expected usage

## Mentorship Review Criteria

### Test Quality Assessment
- **Coverage**: Do tests cover all public methods and edge cases?
- **Clarity**: Are test scenarios clearly described and executable?
- **Validation**: Do tests verify both success and failure conditions?
- **Learning**: Do tests demonstrate understanding of OOP principles?

### TDD Compliance
- **Tests First**: Were tests written before implementation?
- **Failure Expected**: Do tests currently fail as expected?
- **Comprehensive**: Are all requirements covered by test scenarios?
- **Maintainable**: Are tests easy to execute and update?

**Note**: These test scenarios follow TDD principles - they MUST exist and MUST document expected failures before any Student class implementation begins in T013.
