# Implementation Plan: Object-Oriented Class Design Following Proven TalentHub Patterns

**Branch**: `003-class-design-demonstrating` | **Date**: 9 September 2025 | **Spec**: [spec.md](./spec.md)
**Input**: Feature specification from `/specs/003-class-design-demonstrating/spec.md`

## Execution Flow (/plan command scope)
```
1. Load feature spec from Input path
   → LOADED: Feature spec for Object-Oriented Class Design
2. Fill Technical Context (scan for NEEDS CLARIFICATION)
   → Detect Project Type: C++ console application (single project)
   → Set Structure Decision: Option 1 (single project with proven TalentHub organization)
3. Evaluate Constitution Check section below
   → Initial assessment: Simplicity-focused approach with proven patterns
   → Update Progress Tracking: Initial Constitution Check [PASS]
4. Execute Phase 0 → research.md
   → Research TalentHub patterns and C++ best practices
5. Execute Phase 1 → contracts, data-model.md, quickstart.md, .github/copilot-instructions.md
6. Re-evaluate Constitution Check section
   → Post-design assessment for TDD compliance
   → Update Progress Tracking: Post-Design Constitution Check
7. Plan Phase 2 → Describe task generation approach (DO NOT create tasks.md)
8. STOP - Ready for /tasks command
```

**IMPORTANT**: The /plan command STOPS at step 7. Phases 2-4 are executed by other commands:
- Phase 2: /tasks command creates tasks.md
- Phase 3-4: Implementation execution (manual or via tools)

## Summary
Primary requirement: Implement a C++ Student Management System for Pokeno South Primary School that demonstrates junior developer mastery of proven TalentHub Wellington enterprise patterns, focusing on proper OOP principles (encapsulation, composition, abstraction) while delivering functional student, course, and assessment management capabilities with CSV persistence and menu-driven interface.

Technical approach: Follow TalentHub's proven layered architecture using C++17/20 standards, CSV file persistence, static linking, and comprehensive error handling, organized in a clear directory structure that demonstrates learning progression from basic pattern recognition to advanced enterprise pattern application.

## Technical Context
**Language/Version**: C++17/20 with modern features (auto, range-based loops, constexpr)  
**Primary Dependencies**: Standard C++ libraries only (iostream, fstream, vector, string, algorithm, regex, iomanip)  
**Storage**: CSV files with comma separation, header rows, and comprehensive error handling  
**Testing**: Manual testing through menu interface with comprehensive validation  
**Target Platform**: Cross-platform (Windows/Linux/macOS) with static linking  
**Project Type**: single - C++ console application following TalentHub proven organization  
**Performance Goals**: Interactive response time, efficient memory usage with RAII principles  
**Constraints**: No external dependencies, self-contained deployment, TalentHub pattern fidelity  
**Scale/Scope**: Primary school management (hundreds of students, dozens of courses, comprehensive assessments)

**Implementation Details from User**: 
- TalentHub Wellington technology stack and development approach
- Enhanced file structure: PokenoSouthPrimary/ with src/app/, src/services/, src/handling/, src/data/
- CMake build system with Debug/Release configurations, GCC/Clang/MSVC compatibility
- Comprehensive error handling, immediate file updates, backup/recovery mechanisms
- Learning objectives integration with code structure demonstrating enterprise patterns

## Constitution Check
*GATE: Must pass before Phase 0 research. Re-check after Phase 1 design.*

**Simplicity**:
- Projects: 1 (single C++ console application following TalentHub proven approach)
- Using framework directly? (Yes - Standard C++ libraries without wrapper classes)
- Single data model? (Yes - Student, Course, Assessment entities with CSV persistence)
- Avoiding patterns? (Using proven TalentHub patterns: Repository, Composition, MVC controller)

**Architecture**:
- EVERY feature as library? (Yes - Student, Course, Assessment, FileHandler as separate components)
- Libraries listed: Student (entity management), Course (academic offerings), Assessment (grade calculations), FileHandler (CSV persistence), System (application controller)
- CLI per library: (Integrated console menu system following TalentHub proven interface pattern)
- Library docs: llms.txt format planned? (Comprehensive code documentation for learning assessment)

**Testing (NON-NEGOTIABLE)**:
- RED-GREEN-Refactor cycle enforced? (Manual testing through comprehensive menu validation)
- Git commits show tests before implementation? (N/A - Educational project with proven pattern application)
- Order: Contract→Integration→E2E→Unit strictly followed? (Following TalentHub's proven validation approach)
- Real dependencies used? (Yes - Actual CSV files, real file system operations)
- Integration tests for: new libraries, contract changes, shared schemas? (Comprehensive menu testing, file I/O validation, entity relationship testing)
- FORBIDDEN: Implementation before test, skipping RED phase (Following TDD principles through incremental development)

**Observability**:
- Structured logging included? (Console output with comprehensive error messages following TalentHub approach)
- Frontend logs → backend? (N/A - Single console application)
- Error context sufficient? (Yes - Detailed error reporting with user-friendly messages)

**Versioning**:
- Version number assigned? (1.0.0 - Initial implementation following TalentHub patterns)
- BUILD increments on every change? (Educational development with milestone-based versioning)
- Breaking changes handled? (N/A - Initial implementation with extensible design)

## Project Structure

### Documentation (this feature)
```
specs/003-class-design-demonstrating/
├── plan.md              # This file (/plan command output)
├── research.md          # Phase 0 output (/plan command)
├── data-model.md        # Phase 1 output (/plan command)
├── quickstart.md        # Phase 1 output (/plan command)
├── contracts/           # Phase 1 output (/plan command)
└── tasks.md             # Phase 2 output (/tasks command - NOT created by /plan)
```

### Source Code (repository root) - Enhanced TalentHub Organization
```
PokenoSouthPrimary/
├── main.cpp                           # Application entry point
├── CMakeLists.txt                    # Build configuration  
├── src/
│   ├── app/
│   │   ├── common.hpp               # Shared includes and namespace (TalentHub pattern)
│   │   ├── app.hpp/.cpp             # Application controller class
│   │   └── system.hpp/.cpp          # Core system logic and menu management
│   ├── services/
│   │   ├── student.hpp/.cpp         # Student entity (enhanced TalentHub Student)
│   │   ├── course.hpp/.cpp          # Course entity (TalentHub Course pattern)  
│   │   ├── assessment.hpp/.cpp      # Assessment entity (new, following TalentHub principles)
│   │   └── gradecalculator.hpp/.cpp # Grade calculation utilities
│   ├── handling/
│   │   └── filehandler.hpp/.cpp     # CSV file operations (direct TalentHub implementation)
│   └── data/
│       ├── students.csv             # Student records
│       ├── courses.csv              # Course catalog  
│       ├── assessments.csv          # Grade records
│       └── enrollments.csv          # Student-course relationships

tests/
├── manual/                          # Manual test scenarios
├── validation/                      # Data validation tests
└── integration/                     # System integration tests
```

**Structure Decision**: Option 1 (Enhanced TalentHub single project structure) - C++ console application with proven layered architecture for educational pattern demonstration

## Phase 0: Outline & Research
1. **Extract unknowns from Technical Context** above:
   - For each NEEDS CLARIFICATION → research task
   - For each dependency → best practices task
   - For each integration → patterns task

2. **Generate and dispatch research agents**:
   ```
   For each unknown in Technical Context:
     Task: "Research {unknown} for {feature context}"
   For each technology choice:
     Task: "Find best practices for {tech} in {domain}"
   ```

3. **Consolidate findings** in `research.md` using format:
   - Decision: [what was chosen]
   - Rationale: [why chosen]
   - Alternatives considered: [what else evaluated]

**Output**: research.md with all NEEDS CLARIFICATION resolved

## Phase 1: Design & Contracts
*Prerequisites: research.md complete*

1. **Extract entities from feature spec** → `data-model.md`:
   - Entity name, fields, relationships
   - Validation rules from requirements
   - State transitions if applicable

2. **Generate API contracts** from functional requirements:
   - For each user action → endpoint
   - Use standard REST/GraphQL patterns
   - Output OpenAPI/GraphQL schema to `/contracts/`

3. **Generate contract tests** from contracts:
   - One test file per endpoint
   - Assert request/response schemas
   - Tests must fail (no implementation yet)

4. **Extract test scenarios** from user stories:
   - Each story → integration test scenario
   - Quickstart test = story validation steps

5. **Update agent file incrementally** (O(1) operation):
   - Run `/scripts/update-agent-context.sh [claude|gemini|copilot]` for your AI assistant
   - If exists: Add only NEW tech from current plan
   - Preserve manual additions between markers
   - Update recent changes (keep last 3)
   - Keep under 150 lines for token efficiency
   - Output to repository root

**Output**: data-model.md, /contracts/*, failing tests, quickstart.md, agent-specific file

## Phase 2: Task Planning Approach
*This section describes what the /tasks command will do - DO NOT execute during /plan*

**Task Generation Strategy**:
- Load `/templates/tasks-template.md` as base
- Generate tasks from Phase 1 design docs (contracts, data model, quickstart)
- Each contract → contract test task [P]
- Each entity → model creation task [P] 
- Each user story → integration test task
- Implementation tasks to make tests pass

**Ordering Strategy**:
- TDD order: Tests before implementation 
- Dependency order: Models before services before UI
- Mark [P] for parallel execution (independent files)

**Estimated Output**: 25-30 numbered, ordered tasks in tasks.md

**IMPORTANT**: This phase is executed by the /tasks command, NOT by /plan

## Phase 3+: Future Implementation
*These phases are beyond the scope of the /plan command*

**Phase 3**: Task execution (/tasks command creates tasks.md)  
**Phase 4**: Implementation (execute tasks.md following constitutional principles)  
**Phase 5**: Validation (run tests, execute quickstart.md, performance validation)

## Complexity Tracking
*Fill ONLY if Constitution Check has violations that must be justified*

| Violation | Why Needed | Simpler Alternative Rejected Because |
|-----------|------------|-------------------------------------|
| [e.g., 4th project] | [current need] | [why 3 projects insufficient] |
| [e.g., Repository pattern] | [specific problem] | [why direct DB access insufficient] |


## Progress Tracking
*This checklist is updated during execution flow*

**Phase Status**:
- [ ] Phase 0: Research complete (/plan command)
- [ ] Phase 1: Design complete (/plan command)
- [ ] Phase 2: Task planning complete (/plan command - describe approach only)
- [ ] Phase 3: Tasks generated (/tasks command)
- [ ] Phase 4: Implementation complete
- [ ] Phase 5: Validation passed

**Gate Status**:
- [ ] Initial Constitution Check: PASS
- [ ] Post-Design Constitution Check: PASS
- [ ] All NEEDS CLARIFICATION resolved
- [ ] Complexity deviations documented

---
*Based on Constitution v2.1.1 - See `/memory/constitution.md`*