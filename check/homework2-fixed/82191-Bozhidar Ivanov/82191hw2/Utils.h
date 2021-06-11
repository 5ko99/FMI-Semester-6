#include <string>
#include <vector>

class Utils
{
public:
    static uint32_t GetNumberLength(int64_t number);
    static std::vector<std::string> SplitString(const std::string& str, const std::string& delim);
    static bool ValidateCarId(const std::string& id);
    
    static inline uint32_t Fnv1a(std::string const & text) { // assumes 32-bit hashes, needed for different compiler hashes
        uint32_t constexpr fnv_prime = 16777619U;
        uint32_t constexpr fnv_offset_basis = 2166136261U;
        
        uint32_t hash = fnv_offset_basis;
        
        for(auto c : text) {
            hash ^= c;
            hash *= fnv_prime;
        }

        return hash;
    }
};
