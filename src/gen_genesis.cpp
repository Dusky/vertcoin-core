#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <algorithm>

// Basic SHA256 implementation for genesis block mining
class SHA256 {
public:
    static const uint32_t SHA256_K[];
    static void SHA256Transform(uint32_t* state, const uint32_t* data) {
        uint32_t a = state[0], b = state[1], c = state[2], d = state[3];
        uint32_t e = state[4], f = state[5], g = state[6], h = state[7];
        uint32_t m[64];
        
        for (int i = 0; i < 16; i++) {
            m[i] = data[i];
        }
        
        for (int i = 16; i < 64; i++) {
            m[i] = (SIG1(m[i-2]) + m[i-7] + SIG0(m[i-15]) + m[i-16]);
        }
        
        for (int i = 0; i < 64; i++) {
            uint32_t t1 = h + EP1(e) + CH(e,f,g) + SHA256_K[i] + m[i];
            uint32_t t2 = EP0(a) + MAJ(a,b,c);
            h = g; g = f; f = e; e = d + t1;
            d = c; c = b; b = a; a = t1 + t2;
        }
        
        state[0] += a; state[1] += b; state[2] += c; state[3] += d;
        state[4] += e; state[5] += f; state[6] += g; state[7] += h;
    }
    
    static inline uint32_t ROTR(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }
    static inline uint32_t CH(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z); }
    static inline uint32_t MAJ(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); }
    static inline uint32_t EP0(uint32_t x) { return ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22); }
    static inline uint32_t EP1(uint32_t x) { return ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25); }
    static inline uint32_t SIG0(uint32_t x) { return ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3); }
    static inline uint32_t SIG1(uint32_t x) { return ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10); }
};

const uint32_t SHA256::SHA256_K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Simplified block header structure for mining
struct BlockHeader {
    uint32_t nVersion;
    uint8_t hashPrevBlock[32];
    uint8_t hashMerkleRoot[32];
    uint32_t nTime;
    uint32_t nBits;
    uint32_t nNonce;
    
    BlockHeader() {
        nVersion = 1;
        memset(hashPrevBlock, 0, sizeof(hashPrevBlock));
        // Merkle root will be calculated
        nTime = time(NULL);
        nBits = 0x1e0ffff0; // Vertcoin difficulty target
        nNonce = 0;
    }
    
    std::string GetHash() {
        uint32_t header[20]; // Large enough for the header
        uint32_t state[8] = {
            0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
            0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
        };
        
        // Prepare header for hashing
        memcpy(header, this, 80);
        
        // First SHA256
        SHA256::SHA256Transform(state, header);
        
        // Convert state to output hash (simplified)
        std::stringstream ss;
        for (int i = 0; i < 8; i++) {
            ss << std::hex << std::setw(8) << std::setfill('0') << state[i];
        }
        
        return ss.str();
    }
    
    bool MineBlock(uint32_t target) {
        while (nNonce < UINT32_MAX) {
            std::string hash = GetHash();
            std::cout << "Nonce: " << nNonce << " Hash: " << hash << std::endl;
            
            // Check if hash meets target
            if (hash.compare(0, 6, "000000") == 0) {
                return true;
            }
            
            nNonce++;
        }
        return false;
    }
};

int main() {
    std::cout << "Paperclips Genesis Block Miner" << std::endl;
    
    BlockHeader genesisBlock;
    genesisBlock.nTime = time(NULL); // Current timestamp
    
    std::cout << "Mining genesis block with timestamp: " << genesisBlock.nTime << std::endl;
    
    if (genesisBlock.MineBlock(0x1e0ffff0)) {
        std::cout << "Block mined!" << std::endl;
        std::cout << "Nonce: " << genesisBlock.nNonce << std::endl;
        std::cout << "Hash: " << genesisBlock.GetHash() << std::endl;
    } else {
        std::cout << "Failed to mine block" << std::endl;
    }
    
    return 0;
}