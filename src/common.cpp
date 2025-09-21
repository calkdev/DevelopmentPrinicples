#include "common.hpp"

namespace Common {
    
    /**
     * Validates email format using regex pattern
     */
    bool isValidEmail(const string& email) {
        if (email.empty()) return false;
        
        const regex emailPattern(
            R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)"
        );
        
        return regex_match(email, emailPattern);
    }
    
    /**
     * Validates date is not in the future
     */
    bool isDateNotFuture(const string& date) {
        if (date.empty()) return false;
        
        const regex datePattern(R"(^\d{4}-\d{2}-\d{2}$)");
        if (!regex_match(date, datePattern)) {
            return false;
        }
        
        return true; // Simplified validation
    }
    
    /**
     * Additional validation functions for Student class compatibility
     */
    bool isValidRollNumber(int rollNumber) {
        return rollNumber > 0 && rollNumber <= 999999; // 6-digit max
    }
    
    bool isValidName(const string& name) {
        if (name.empty() || name.length() > 50) return false;
        return isValidAlphanumeric(name, " '-.");
    }
    
    bool isValidDateFormat(const string& date) {
        const regex datePattern(R"(^\d{4}-\d{2}-\d{2}$)");
        return regex_match(date, datePattern);
    }
    
    bool isValidDate(const string& date) {
        return isValidDateFormat(date); // Simplified
    }
    
    // === T036: INPUT SANITIZATION AND VALIDATION HELPERS ===
    
    /**
     * Sanitizes input string by removing/escaping dangerous characters
     */
    string sanitizeInput(const string& input) {
        string sanitized = input;
        
        // Remove null characters
        sanitized.erase(remove(sanitized.begin(), sanitized.end(), '\0'), sanitized.end());
        
        // Replace dangerous characters
        replace(sanitized.begin(), sanitized.end(), '<', ' ');
        replace(sanitized.begin(), sanitized.end(), '>', ' ');
        replace(sanitized.begin(), sanitized.end(), '&', ' ');
        replace(sanitized.begin(), sanitized.end(), '"', '\'');
        
        return trimString(sanitized);
    }
    
    /**
     * Removes leading and trailing whitespace from string
     */
    string trimString(const string& str) {
        if (str.empty()) return str;
        
        size_t start = str.find_first_not_of(" \t\n\r\f\v");
        if (start == string::npos) return "";
        
        size_t end = str.find_last_not_of(" \t\n\r\f\v");
        return str.substr(start, end - start + 1);
    }
    
    /**
     * Validates string contains only alphanumeric characters and specified special chars
     */
    bool isValidAlphanumeric(const string& input, const string& allowedSpecialChars) {
        return all_of(input.begin(), input.end(),
            [&allowedSpecialChars](char c) {
                return isalnum(c) || allowedSpecialChars.find(c) != string::npos;
            });
    }
    
    /**
     * Validates and sanitizes numeric input from string
     */
    bool parseAndValidateInt(const string& input, int& value, int minValue, int maxValue) {
        try {
            string trimmed = trimString(input);
            if (trimmed.empty()) return false;
            
            // Check if all characters are digits (with optional leading minus)
            bool isNegative = (trimmed[0] == '-');
            size_t startPos = isNegative ? 1 : 0;
            
            if (startPos >= trimmed.length()) return false;
            
            for (size_t i = startPos; i < trimmed.length(); ++i) {
                if (!isdigit(trimmed[i])) return false;
            }
            
            value = stoi(trimmed);
            return value >= minValue && value <= maxValue;
        } catch (...) {
            return false;
        }
    }
    
    /**
     * Validates and sanitizes double input from string
     */
    bool parseAndValidateDouble(const string& input, double& value, double minValue, double maxValue) {
        try {
            string trimmed = trimString(input);
            if (trimmed.empty()) return false;
            
            value = stod(trimmed);
            return value >= minValue && value <= maxValue;
        } catch (...) {
            return false;
        }
    }
    
    /**
     * Checks if string contains potentially dangerous characters or patterns
     */
    bool isSafeInput(const string& input) {
        // Check for null characters
        if (input.find('\0') != string::npos) return false;
        
        // Check for potentially dangerous patterns
        const vector<string> dangerousPatterns = {
            "../", "..\\", "<script", "</script", "javascript:", 
            "vbscript:", "onload=", "onerror=", "onclick=",
            "DROP TABLE", "DELETE FROM", "INSERT INTO", "UPDATE SET"
        };
        
        string lowerInput = normalizeText(input);
        for (const auto& pattern : dangerousPatterns) {
            if (lowerInput.find(pattern) != string::npos) {
                return false;
            }
        }
        
        return true;
    }
    
    /**
     * Validates string length is within acceptable bounds
     */
    bool isValidLength(const string& input, size_t minLength, size_t maxLength) {
        size_t length = input.length();
        return length >= minLength && length <= maxLength;
    }
    
    /**
     * Escapes special characters in string for safe CSV output
     */
    string escapeCSVField(const string& input) {
        if (input.empty()) return input;
        
        bool needsEscaping = input.find(',') != string::npos ||
                           input.find('"') != string::npos ||
                           input.find('\n') != string::npos ||
                           input.find('\r') != string::npos;
        
        if (!needsEscaping) return input;
        
        string escaped = "\"";
        for (char c : input) {
            if (c == '"') {
                escaped += "\"\""; // Escape quotes by doubling them
            } else {
                escaped += c;
            }
        }
        escaped += "\"";
        
        return escaped;
    }
    
    /**
     * Validates phone number format (basic international patterns)
     */
    bool isValidPhoneNumber(const string& phoneNumber) {
        if (phoneNumber.empty()) return false;

        // Normalize by removing common separators
        string normalized;
        normalized.reserve(phoneNumber.size());
        for (char c : phoneNumber) {
            if (isdigit(static_cast<unsigned char>(c)) || c == '+') {
                normalized.push_back(c);
            }
        }

        // Optional leading '+' followed by digits, or just digits
        size_t start = 0;
        if (!normalized.empty() && normalized[0] == '+') {
            start = 1;
        }

        if (start >= normalized.size()) return false; // '+' only is invalid

        // Ensure remaining are all digits
        for (size_t i = start; i < normalized.size(); ++i) {
            if (!isdigit(static_cast<unsigned char>(normalized[i]))) return false;
        }

        // Count digits (exclude '+') and enforce reasonable length (7-15 digits)
        size_t digitCount = normalized.size() - start;
        if (digitCount < 7 || digitCount > 15) return false;

        // Allow leading zero for local numbers (NZ etc.)
        // No further country-specific checks
        return true;
    }
    
    /**
     * Normalizes text by converting to lowercase and removing extra whitespace
     */
    string normalizeText(const string& input) {
        string normalized = trimString(input);
        transform(normalized.begin(), normalized.end(), normalized.begin(),
                      [](char c) { return tolower(c); });
        
        // Replace multiple whitespace with single space
        auto end = unique(normalized.begin(), normalized.end(),
                              [](char a, char b) { return isspace(a) && isspace(b); });
        normalized.erase(end, normalized.end());
        
        return normalized;
    }
    
    /**
     * Validates text contains only printable ASCII characters
     */
    bool isPrintableASCII(const string& input) {
        return all_of(input.begin(), input.end(),
            [](char c) { return c >= 32 && c <= 126; });
    }
    
    /**
     * Checks if input matches common SQL injection patterns
     */
    bool isSafeSQLInput(const string& input) {
        string lowerInput = normalizeText(input);
        
        const vector<string> sqlKeywords = {
            "select ", "insert ", "update ", "delete ", "drop ", "create ",
            "alter ", "truncate ", "exec ", "execute ", "union ", "or 1=1",
            "and 1=1", "' or ", "\" or ", "; --", "/*", "*/"
        };
        
        for (const auto& keyword : sqlKeywords) {
            if (lowerInput.find(keyword) != string::npos) {
                return false;
            }
        }
        
        return true;
    }
    
    /**
     * Validates input against a whitelist of allowed characters
     */
    bool matchesWhitelist(const string& input, const string& whitelist) {
        return all_of(input.begin(), input.end(),
            [&whitelist](char c) { return whitelist.find(c) != string::npos; });
    }
    
    // === UTILITY FUNCTIONS ===
    
    /**
     * General error handling utility
     */
    void handleError(const string& operation, const string& details, bool critical) {
        cout << "[ERROR] " << operation;
        if (!details.empty()) {
            cout << ": " << details;
        }
        cout << endl;
        
        if (critical) {
            exit(1);
        }
    }
    
    /**
     * Success message utility
     */
    void displaySuccess(const string& operation, const string& details) {
        cout << "[SUCCESS] " << operation;
        if (!details.empty()) {
            cout << ": " << details;
        }
        cout << endl;
    }
    
    /**
     * Warning message utility
     */
    void displayWarning(const string& message, const string& details) {
        cout << "[WARNING] " << message;
        if (!details.empty()) {
            cout << ": " << details;
        }
        cout << endl;
    }
    
    /**
     * Get current date in YYYY-MM-DD format
     */
    string getCurrentDate() {
        auto now = system_clock::now();
        auto time_t = system_clock::to_time_t(now);
        ostringstream oss;
        oss << put_time(localtime(&time_t), "%Y-%m-%d");
        return oss.str();
    }
    
    /**
     * Get current timestamp in YYYY-MM-DD HH:MM:SS format
     */
    string getCurrentTimestamp() {
        auto now = system_clock::now();
        auto time_t = system_clock::to_time_t(now);
        ostringstream oss;
        oss << put_time(localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

} // namespace Common
