# Course Class Manual Test Scenarios

**Test File**: `tests/manual_test_scenarios/course_tests.md`  
**Purpose**: Comprehensive test scenarios for Course entity with bidirectional relationships  
**Learning Objective**: Understanding relationship testing and business rule validation  
**Status**: Tests must FAIL until T014 (Course.cpp implementation) is completed

## Test Categories

### 1. Constructor and Object Creation Tests

#### Test C001: Valid Course Creation
**Description**: Create course with all valid parameters
**Input Data**:
- courseId: "MATH101"
- courseName: "Mathematics Year 3"
- credits: 3
- description: "Basic arithmetic and problem solving"
- duration: 40

**Expected Behavior**: 
- Course object created successfully
- All getter methods return correct values
- enrolledStudents vector is empty initially
- Course ID stored in uppercase format

**Test Execution**: Manual verification through constructor call and getter validation
**Expected Result**: PASS after T014 implementation
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C002: Invalid Course ID Format (Lowercase)
**Description**: Attempt to create course with lowercase course ID
**Input Data**: courseId: "math101", other fields valid
**Expected Behavior**: Constructor should convert to uppercase or reject
**Validation**: Should enforce uppercase format for course IDs
**Expected Result**: Either convert to "MATH101" or FAIL with format error
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C003: Invalid Course ID Format (Wrong Pattern)
**Description**: Attempt to create course with invalid ID pattern
**Input Data**: courseId: "M1", other fields valid
**Expected Behavior**: Constructor should reject invalid pattern
**Expected Result**: FAIL creation, error about course ID format
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C004: Invalid Course ID Format (Special Characters)
**Description**: Attempt to create course with special characters in ID
**Input Data**: courseId: "MATH-101", other fields valid
**Expected Behavior**: Constructor should reject special characters
**Expected Result**: FAIL creation, error about course ID format
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C005: Empty Course Name
**Description**: Attempt to create course with empty name
**Input Data**: courseName: "", other fields valid
**Expected Behavior**: Constructor should reject empty course name
**Expected Result**: FAIL creation, error about required course name
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C006: Invalid Credits (Below Minimum)
**Description**: Attempt to create course with credits below minimum
**Input Data**: credits: 0, other fields valid
**Expected Behavior**: Constructor should reject invalid credit count
**Expected Result**: FAIL creation, error about minimum credits (1)
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C007: Invalid Credits (Above Maximum)
**Description**: Attempt to create course with credits above maximum
**Input Data**: credits: 7, other fields valid
**Expected Behavior**: Constructor should reject excessive credits
**Expected Result**: FAIL creation, error about maximum credits (6)
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C008: Invalid Duration (Zero)
**Description**: Attempt to create course with zero duration
**Input Data**: duration: 0, other fields valid
**Expected Behavior**: Constructor should reject zero duration
**Expected Result**: FAIL creation, error about minimum duration
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C009: Invalid Duration (Excessive)
**Description**: Attempt to create course with excessive duration
**Input Data**: duration: 60, other fields valid
**Expected Behavior**: Constructor should reject unreasonable duration
**Expected Result**: FAIL creation, error about maximum duration (52 weeks)
**Current Status**: WILL FAIL - Course class does not exist yet

### 2. Getter Method Tests

#### Test C010: All Getter Methods Return Correct Values
**Description**: Verify all getter methods return constructor values
**Test Steps**:
1. Create course with known values
2. Call each getter method
3. Compare returned values with input values
**Expected Behavior**: All getters return original constructor values
**Expected Result**: PASS after T014 implementation
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C011: Course ID Case Consistency
**Description**: Verify course ID is consistently uppercase
**Test Steps**:
1. Create course with lowercase ID input
2. Call getCourseId()
3. Verify returned ID is uppercase
**Expected Behavior**: Course ID automatically converted to uppercase
**Expected Result**: PASS after T014 implementation
**Current Status**: WILL FAIL - Course class does not exist yet

### 3. Student Enrollment Management Tests

#### Test C012: Initial Empty Student List
**Description**: Verify new course has no enrolled students
**Test Steps**:
1. Create new course
2. Call getEnrolledStudents()
3. Check vector size
**Expected Behavior**: Empty student vector initially
**Expected Result**: PASS after T014 implementation
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C013: Single Student Enrollment
**Description**: Enroll one student in course
**Test Steps**:
1. Create course and student objects
2. Call course.enrollStudent(student)
3. Verify student appears in getEnrolledStudents()
**Expected Behavior**: Student added to enrollment list
**Expected Result**: PASS after T013 and T014 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

---

#### Test C014: Multiple Student Enrollment
**Description**: Enroll multiple students in course
**Test Steps**:
1. Create course and multiple student objects
2. Enroll each student sequentially
3. Verify all students appear in enrollment list
**Expected Behavior**: All students tracked in order of enrollment
**Expected Result**: PASS after T013 and T014 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

---

#### Test C015: Duplicate Student Enrollment Prevention
**Description**: Prevent enrolling same student twice
**Test Steps**:
1. Create course and student
2. Enroll student successfully
3. Attempt to enroll same student again
**Expected Behavior**: Second enrollment should be rejected
**Expected Result**: FAIL second enrollment, appropriate warning
**Current Status**: WILL FAIL - Classes do not exist yet

---

#### Test C016: Student Withdrawal from Course
**Description**: Remove student from course enrollment
**Test Steps**:
1. Enroll student in course
2. Call removeStudent(student)
3. Verify student removed from enrollment list
**Expected Behavior**: Student removed, list updated correctly
**Expected Result**: PASS after T013 and T014 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

---

#### Test C017: Enrollment Capacity Limits
**Description**: Test course enrollment capacity (if implemented)
**Test Steps**:
1. Create course with enrollment limit
2. Enroll students up to limit
3. Attempt to exceed limit
**Expected Behavior**: Enrollment limit enforced appropriately
**Expected Result**: PASS up to limit, FAIL beyond limit
**Current Status**: WILL FAIL - Classes do not exist yet

### 4. Bidirectional Relationship Tests

#### Test C018: Student-Course Relationship Consistency
**Description**: Verify bidirectional relationship maintained
**Test Steps**:
1. Create student and course
2. Enroll student in course via course.enrollStudent()
3. Verify student's course list includes this course
4. Verify course's student list includes this student
**Expected Behavior**: Both sides of relationship updated automatically
**Expected Result**: PASS after T013 and T014 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

---

#### Test C019: Relationship Cleanup on Withdrawal
**Description**: Verify relationship cleanup when student withdraws
**Test Steps**:
1. Establish student-course relationship
2. Remove student from course
3. Verify both sides of relationship cleaned up
**Expected Behavior**: Student removed from course, course removed from student
**Expected Result**: PASS after T013 and T014 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

### 5. Course Information and Display Tests

#### Test C020: displayInfo() Formatting
**Description**: Verify course information displays correctly
**Test Steps**:
1. Create course with test data
2. Call displayInfo()
3. Verify output format and completeness
**Expected Behavior**: Formatted output with all course details
**Expected Result**: PASS after T014 implementation
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C021: displayEnrolledStudents() with Empty List
**Description**: Display enrolled students when none exist
**Test Steps**:
1. Create new course (no enrollments)
2. Call displayEnrolledStudents()
3. Verify appropriate message for empty list
**Expected Behavior**: "No students enrolled" or similar message
**Expected Result**: PASS after T014 implementation
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C022: displayEnrolledStudents() with Students
**Description**: Display enrolled students when students exist
**Test Steps**:
1. Create course and enroll multiple students
2. Call displayEnrolledStudents()
3. Verify all students listed with proper formatting
**Expected Behavior**: Formatted list of all enrolled students
**Expected Result**: PASS after T013 and T014 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

### 6. Business Rule Validation Tests

#### Test C023: Prerequisite Course Validation
**Description**: Test prerequisite course requirements (if implemented)
**Test Steps**:
1. Create advanced course with prerequisites
2. Attempt to enroll student without prerequisites
3. Verify enrollment rejected appropriately
**Expected Behavior**: Prerequisite checking enforced
**Expected Result**: FAIL enrollment without prerequisites
**Current Status**: WILL FAIL - Classes do not exist yet

---

#### Test C024: Course Schedule Conflict Detection
**Description**: Test for scheduling conflicts (if implemented)
**Test Steps**:
1. Create courses with overlapping schedules
2. Attempt to enroll student in conflicting courses
3. Verify conflict detection works
**Expected Behavior**: Schedule conflicts prevented
**Expected Result**: FAIL enrollment with schedule conflict
**Current Status**: WILL FAIL - Classes do not exist yet

---

#### Test C025: Academic Year Validation
**Description**: Test course availability by academic year
**Test Steps**:
1. Create course for specific academic year
2. Attempt enrollment outside valid period
3. Verify temporal validation works
**Expected Behavior**: Course availability enforced by date
**Expected Result**: FAIL enrollment outside valid period
**Current Status**: WILL FAIL - Classes do not exist yet

### 7. Edge Cases and Error Handling

#### Test C026: Very Long Course Name
**Description**: Test course name length limits
**Input Data**: courseName with 101+ characters
**Expected Behavior**: Constructor should enforce length limits
**Expected Result**: FAIL creation or truncate appropriately
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C027: Very Long Description
**Description**: Test description length limits
**Input Data**: description with 501+ characters
**Expected Behavior**: Constructor should enforce description limits
**Expected Result**: FAIL creation or truncate appropriately
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C028: Special Characters in Course Name
**Description**: Test acceptable special characters in course name
**Input Data**: Course names with various special characters
**Expected Behavior**: Should accept valid characters, reject invalid
**Expected Result**: PASS for valid characters, FAIL for invalid
**Current Status**: WILL FAIL - Course class does not exist yet

### 8. Performance and Memory Management Tests

#### Test C029: Large Student List Performance
**Description**: Test performance with many enrolled students
**Test Steps**:
1. Create course
2. Enroll 500+ students
3. Verify reasonable performance for operations
**Expected Behavior**: Acceptable performance, no memory issues
**Expected Result**: PASS after T013 and T014 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

---

#### Test C030: Memory Management with Relationships
**Description**: Verify proper memory management for student pointers
**Test Steps**:
1. Create course with enrolled students
2. Delete student objects
3. Verify course handles dangling pointers correctly
**Expected Behavior**: Safe handling of student object lifecycle
**Expected Result**: PASS after T013 and T014 implementation
**Current Status**: WILL FAIL - Classes do not exist yet

### 9. Course Comparison and Equality Tests

#### Test C031: Course Equality by ID
**Description**: Test course comparison based on course ID
**Test Steps**:
1. Create two course objects with same ID
2. Compare using equality operator (if implemented)
3. Verify courses considered equal
**Expected Behavior**: Courses with same ID are equal
**Expected Result**: PASS after T014 implementation
**Current Status**: WILL FAIL - Course class does not exist yet

---

#### Test C032: Course Ordering for Collections
**Description**: Test course ordering for sorted collections
**Test Steps**:
1. Create multiple courses with different IDs
2. Insert into sorted collection
3. Verify proper ordering maintained
**Expected Behavior**: Courses ordered by course ID
**Expected Result**: PASS after T014 implementation
**Current Status**: WILL FAIL - Course class does not exist yet

## Test Execution Summary

**Total Test Scenarios**: 32  
**Current Status**: ALL WILL FAIL - Course class not implemented  
**Implementation Required**: T014 (Course.cpp), T013 (Student.cpp for relationships)  
**Success Criteria**: All tests PASS after entity implementation  

## Learning Checkpoints

### Pre-Implementation Understanding
- [ ] Course entity requirements clearly documented
- [ ] Bidirectional relationship requirements specified
- [ ] Business rule validation scenarios identified
- [ ] Edge cases and error conditions covered

### Post-Implementation Validation
- [ ] All constructor validation tests pass
- [ ] Getter methods return correct values
- [ ] Student enrollment/withdrawal works correctly
- [ ] Bidirectional relationships maintained properly
- [ ] Display methods format output correctly
- [ ] Business rules enforced appropriately
- [ ] Error handling provides meaningful feedback
- [ ] Performance acceptable for expected usage

## Mentorship Review Criteria

### Test Quality Assessment
- **Relationship Testing**: Do tests verify bidirectional relationships?
- **Business Rules**: Are course-specific business rules tested?
- **Data Validation**: Is input validation thoroughly tested?
- **Edge Cases**: Are boundary conditions and error cases covered?

### Learning Objectives
- **Understanding**: Does student understand entity relationships?
- **Validation**: Are business rule requirements clear?
- **Quality**: Are test scenarios comprehensive and executable?
- **TDD Compliance**: Were tests written before implementation?

**Note**: These test scenarios follow TDD principles - they MUST exist and MUST document expected failures before any Course class implementation begins in T014.
