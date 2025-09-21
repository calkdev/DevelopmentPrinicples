# Assessment Class Manual Test Scenarios

**Test File**: `tests/manual_test_scenarios/assessment_tests.md`  
**Purpose**: Comprehensive test scenarios for Assessment entity with weighted grade calculations  
**Learning Objective**: Understanding calculation testing and weighted grade scenarios  
**Status**: Tests must FAIL until T015 (Assessment.cpp implementation) is completed

## Test Categories

### 1. Constructor and Object Creation Tests

#### Test A001: Valid Assessment Creation
**Description**: Create assessment with all valid parameters
**Input Data**:
- assessmentId: "ASS001"
- studentRollNumber: 12345
- courseId: "MATH101"
- internalMarks: 75
- finalMarks: 82
- assessmentDate: "2025-06-15"

**Expected Behavior**: 
- Assessment object created successfully
- All getter methods return correct values
- Calculated grade automatically computed as 79.1 (75*0.3 + 82*0.7)
- Assessment date validated and stored

**Test Execution**: Manual verification through constructor call and getter validation
**Expected Result**: PASS after T015 implementation
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A002: Invalid Internal Marks (Below Minimum)
**Description**: Attempt to create assessment with internal marks below 0
**Input Data**: internalMarks: -5, other fields valid
**Expected Behavior**: Constructor should reject negative marks
**Validation**: Should enforce 0-100 range for internal marks
**Expected Result**: FAIL creation, error about mark range
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A003: Invalid Internal Marks (Above Maximum)
**Description**: Attempt to create assessment with internal marks above 100
**Input Data**: internalMarks: 105, other fields valid
**Expected Behavior**: Constructor should reject excessive marks
**Expected Result**: FAIL creation, error about maximum marks (100)
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A004: Invalid Final Marks (Below Minimum)
**Description**: Attempt to create assessment with final marks below 0
**Input Data**: finalMarks: -10, other fields valid
**Expected Behavior**: Constructor should reject negative marks
**Expected Result**: FAIL creation, error about mark range
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A005: Invalid Final Marks (Above Maximum)
**Description**: Attempt to create assessment with final marks above 100
**Input Data**: finalMarks: 110, other fields valid
**Expected Behavior**: Constructor should reject excessive marks
**Expected Result**: FAIL creation, error about maximum marks (100)
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A006: Empty Assessment ID
**Description**: Attempt to create assessment with empty ID
**Input Data**: assessmentId: "", other fields valid
**Expected Behavior**: Constructor should reject empty assessment ID
**Expected Result**: FAIL creation, error about required assessment ID
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A007: Invalid Student Roll Number
**Description**: Attempt to create assessment with invalid student reference
**Input Data**: studentRollNumber: -1, other fields valid
**Expected Behavior**: Constructor should validate student reference
**Expected Result**: FAIL creation, error about invalid student reference
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A008: Invalid Course ID Format
**Description**: Attempt to create assessment with malformed course ID
**Input Data**: courseId: "math101", other fields valid
**Expected Behavior**: Constructor should validate course ID format
**Expected Result**: FAIL creation, error about course ID format
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A009: Invalid Assessment Date Format
**Description**: Attempt to create assessment with invalid date format
**Input Data**: assessmentDate: "15-06-2025", other fields valid
**Expected Behavior**: Constructor should enforce YYYY-MM-DD format
**Expected Result**: FAIL creation, error about date format
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A010: Future Assessment Date
**Description**: Attempt to create assessment with future date
**Input Data**: assessmentDate: "2026-12-31", other fields valid
**Expected Behavior**: Constructor should reject future assessment dates
**Expected Result**: FAIL creation, error about future date
**Current Status**: WILL FAIL - Assessment class does not exist yet

### 2. Weighted Grade Calculation Tests

#### Test A011: Perfect Scores Calculation
**Description**: Test grade calculation with perfect scores
**Input Data**: internalMarks: 100, finalMarks: 100
**Expected Behavior**: Calculated grade should be 100.0
**Calculation**: (100 * 0.3) + (100 * 0.7) = 30 + 70 = 100
**Expected Result**: getCalculatedGrade() returns 100.0
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A012: Zero Scores Calculation
**Description**: Test grade calculation with zero scores
**Input Data**: internalMarks: 0, finalMarks: 0
**Expected Behavior**: Calculated grade should be 0.0
**Calculation**: (0 * 0.3) + (0 * 0.7) = 0 + 0 = 0
**Expected Result**: getCalculatedGrade() returns 0.0
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A013: Mixed Scores Calculation
**Description**: Test grade calculation with typical mixed scores
**Input Data**: internalMarks: 80, finalMarks: 90
**Expected Behavior**: Calculated grade should be 87.0
**Calculation**: (80 * 0.3) + (90 * 0.7) = 24 + 63 = 87
**Expected Result**: getCalculatedGrade() returns 87.0
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A014: Internal Higher Than Final
**Description**: Test calculation when internal marks exceed final marks
**Input Data**: internalMarks: 95, finalMarks: 70
**Expected Behavior**: Calculated grade should be 77.5
**Calculation**: (95 * 0.3) + (70 * 0.7) = 28.5 + 49 = 77.5
**Expected Result**: getCalculatedGrade() returns 77.5
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A015: Final Higher Than Internal
**Description**: Test calculation when final marks exceed internal marks
**Input Data**: internalMarks: 60, finalMarks: 85
**Expected Behavior**: Calculated grade should be 77.5
**Calculation**: (60 * 0.3) + (85 * 0.7) = 18 + 59.5 = 77.5
**Expected Result**: getCalculatedGrade() returns 77.5
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A016: Decimal Precision in Calculation
**Description**: Test calculation precision for complex decimal results
**Input Data**: internalMarks: 77, finalMarks: 83
**Expected Behavior**: Calculated grade should be 81.2
**Calculation**: (77 * 0.3) + (83 * 0.7) = 23.1 + 58.1 = 81.2
**Expected Result**: getCalculatedGrade() returns 81.2 (precise to 1 decimal)
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A017: Boundary Score Calculations
**Description**: Test calculations at mark boundaries
**Test Cases**:
- Internal: 1, Final: 1 → Expected: 1.0
- Internal: 99, Final: 99 → Expected: 99.0
- Internal: 50, Final: 50 → Expected: 50.0
**Expected Behavior**: Accurate calculations at all boundary values
**Current Status**: WILL FAIL - Assessment class does not exist yet

### 3. Grade Recalculation Tests

#### Test A018: Manual Grade Recalculation
**Description**: Test manual recalculation after mark changes
**Test Steps**:
1. Create assessment with initial marks
2. Change internal or final marks
3. Call recalculateGrade() method
4. Verify updated calculated grade
**Expected Behavior**: Grade recalculated correctly after mark changes
**Expected Result**: PASS after T015 implementation
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A019: Automatic Recalculation on Mark Update
**Description**: Test automatic recalculation when marks are updated
**Test Steps**:
1. Create assessment
2. Call setInternalMarks() with new value
3. Verify calculated grade updates automatically
**Expected Behavior**: Grade automatically recalculated on mark changes
**Expected Result**: PASS after T015 implementation
**Current Status**: WILL FAIL - Assessment class does not exist yet

### 4. Getter Method Tests

#### Test A020: All Getter Methods Return Correct Values
**Description**: Verify all getter methods return constructor values
**Test Steps**:
1. Create assessment with known values
2. Call each getter method
3. Compare returned values with input values
**Expected Behavior**: All getters return original constructor values
**Expected Result**: PASS after T015 implementation
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A021: Calculated Grade Consistency
**Description**: Verify calculated grade is consistent across calls
**Test Steps**:
1. Create assessment
2. Call getCalculatedGrade() multiple times
3. Verify same result returned each time
**Expected Behavior**: Consistent calculated grade across multiple calls
**Expected Result**: PASS after T015 implementation
**Current Status**: WILL FAIL - Assessment class does not exist yet

### 5. Assessment Comparison and Sorting Tests

#### Test A022: Assessment Equality by ID
**Description**: Test assessment comparison based on assessment ID
**Test Steps**:
1. Create two assessment objects with same ID
2. Compare using equality operator (if implemented)
3. Verify assessments considered equal
**Expected Behavior**: Assessments with same ID are equal
**Expected Result**: PASS after T015 implementation
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A023: Assessment Sorting by Grade
**Description**: Test assessment sorting by calculated grade
**Test Steps**:
1. Create multiple assessments with different grades
2. Sort assessments by calculated grade
3. Verify proper ordering maintained
**Expected Behavior**: Assessments ordered by calculated grade
**Expected Result**: PASS after T015 implementation
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A024: Assessment Sorting by Date
**Description**: Test assessment sorting by assessment date
**Test Steps**:
1. Create multiple assessments with different dates
2. Sort assessments by date
3. Verify chronological ordering maintained
**Expected Behavior**: Assessments ordered by assessment date
**Expected Result**: PASS after T015 implementation
**Current Status**: WILL FAIL - Assessment class does not exist yet

### 6. Display and Formatting Tests

#### Test A025: displayInfo() Formatting
**Description**: Verify assessment information displays correctly
**Test Steps**:
1. Create assessment with test data
2. Call displayInfo()
3. Verify output format and completeness
**Expected Behavior**: Formatted output with all assessment details
**Expected Result**: PASS after T015 implementation
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A026: Grade Display Formatting
**Description**: Verify calculated grade displays with proper precision
**Test Steps**:
1. Create assessment with decimal grade result
2. Call display methods
3. Verify grade shown with appropriate decimal places
**Expected Behavior**: Grade displayed to 1-2 decimal places
**Expected Result**: PASS after T015 implementation
**Current Status**: WILL FAIL - Assessment class does not exist yet

### 7. Business Rule Validation Tests

#### Test A027: Student-Course Relationship Validation
**Description**: Verify assessment links valid student to valid course
**Test Steps**:
1. Create assessment with student not enrolled in course
2. Validate student-course relationship
3. Verify appropriate warning or error
**Expected Behavior**: Assessment should validate student enrollment
**Expected Result**: Warning or error for invalid relationships
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A028: Duplicate Assessment Prevention
**Description**: Prevent multiple assessments with same ID
**Test Steps**:
1. Create assessment with specific ID
2. Attempt to create another assessment with same ID
3. Verify duplicate prevention mechanism
**Expected Behavior**: Duplicate assessment IDs should be rejected
**Expected Result**: FAIL second assessment creation
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A029: Assessment Date Validation Rules
**Description**: Test business rules for assessment dates
**Test Cases**:
- Assessment date before course start: FAIL
- Assessment date after course end: FAIL
- Assessment date within course period: PASS
**Expected Behavior**: Date validation enforces course timeline
**Current Status**: WILL FAIL - Assessment class does not exist yet

### 8. Statistical Analysis Tests

#### Test A030: Grade Statistics Calculation
**Description**: Test statistical methods for multiple assessments
**Test Steps**:
1. Create multiple assessments for same student/course
2. Calculate average, min, max grades
3. Verify statistical accuracy
**Expected Behavior**: Accurate statistical calculations
**Expected Result**: PASS after T015 implementation
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A031: Pass/Fail Determination
**Description**: Test pass/fail determination based on calculated grade
**Test Steps**:
1. Create assessments with various grades
2. Apply pass/fail threshold (typically 50%)
3. Verify correct pass/fail determination
**Expected Behavior**: Accurate pass/fail based on grade threshold
**Expected Result**: PASS after T015 implementation
**Current Status**: WILL FAIL - Assessment class does not exist yet

### 9. Edge Cases and Error Handling

#### Test A032: Very Long Assessment ID
**Description**: Test assessment ID length limits
**Input Data**: assessmentId with 20+ characters
**Expected Behavior**: Constructor should enforce reasonable length limits
**Expected Result**: FAIL creation or truncate appropriately
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A033: Special Characters in Assessment ID
**Description**: Test acceptable special characters in assessment ID
**Input Data**: Assessment IDs with various special characters
**Expected Behavior**: Should accept valid characters, reject invalid
**Expected Result**: PASS for valid characters, FAIL for invalid
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A034: Boundary Date Values for Assessment
**Description**: Test assessment date validation boundaries
**Test Cases**:
- January 1, 2000: PASS if valid course dates
- December 31, 2099: PASS if valid course dates
- February 29 on leap year: PASS
- February 29 on non-leap year: FAIL
**Expected Behavior**: Proper date validation with course context
**Current Status**: WILL FAIL - Assessment class does not exist yet

### 10. Performance and Memory Management Tests

#### Test A035: Large Assessment Dataset Performance
**Description**: Test performance with many assessment records
**Test Steps**:
1. Create 1000+ assessment objects
2. Perform sorting and searching operations
3. Verify reasonable performance
**Expected Behavior**: Acceptable performance with large datasets
**Expected Result**: PASS after T015 implementation
**Current Status**: WILL FAIL - Assessment class does not exist yet

---

#### Test A036: Memory Management and Cleanup
**Description**: Verify proper cleanup when assessment objects destroyed
**Test Steps**:
1. Create multiple assessment objects
2. Let objects go out of scope
3. Verify no memory leaks
**Expected Behavior**: Clean destruction, no memory leaks
**Expected Result**: PASS after T015 implementation
**Current Status**: WILL FAIL - Assessment class does not exist yet

## Test Execution Summary

**Total Test Scenarios**: 36  
**Current Status**: ALL WILL FAIL - Assessment class not implemented  
**Implementation Required**: T015 (Assessment.cpp)  
**Success Criteria**: All tests PASS after entity implementation  

## Learning Checkpoints

### Pre-Implementation Understanding
- [ ] Assessment entity requirements clearly documented
- [ ] Weighted grade calculation logic specified (30% internal, 70% final)
- [ ] Business rule validation scenarios identified
- [ ] Edge cases and error conditions covered
- [ ] Statistical analysis requirements understood

### Post-Implementation Validation
- [ ] All constructor validation tests pass
- [ ] Weighted grade calculations are mathematically correct
- [ ] Getter methods return accurate values
- [ ] Grade recalculation works properly
- [ ] Display methods format output correctly
- [ ] Business rules enforced appropriately
- [ ] Statistical analysis functions correctly
- [ ] Error handling provides meaningful feedback
- [ ] Performance acceptable for expected usage

## Mentorship Review Criteria

### Test Quality Assessment
- **Calculation Testing**: Are weighted grade calculations thoroughly tested?
- **Mathematical Accuracy**: Do tests verify calculation precision?
- **Business Rules**: Are assessment-specific business rules tested?
- **Edge Cases**: Are boundary conditions and error cases covered?

### Learning Objectives
- **Understanding**: Does student understand complex business logic?
- **Validation**: Are calculation requirements clearly specified?
- **Quality**: Are test scenarios comprehensive and mathematically sound?
- **TDD Compliance**: Were tests written before implementation?

### Grade Calculation Validation
- **Weight Accuracy**: Is 30%/70% weighting correctly applied?
- **Precision**: Are decimal calculations handled properly?
- **Boundary Testing**: Are edge cases (0, 100, mixed scores) tested?
- **Recalculation**: Is automatic recalculation working correctly?

**Note**: These test scenarios follow TDD principles - they MUST exist and MUST document expected failures before any Assessment class implementation begins in T015.
