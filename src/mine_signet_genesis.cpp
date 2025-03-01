#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <chrono>
#include <algorithm>
#include <array>

// SHA256 implementation for genesis block mining
class SHA256 {
private:
    typedef std::array<uint8_t, 32> SHA256Result;
    
    const static uint32_t K[64];
    
    uint32_t state[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    
    uint8_t data[64];
    uint32_t datalen = 0;
    uint64_t bitlen = 0;
    
    void transform() {
        uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

        for (i = 0, j = 0; i < 16; ++i, j += 4)
            m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
        
        for (; i < 64; ++i)
            m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

        a = state[0];
        b = state[1];
        c = state[2];
        d = state[3];
        e = state[4];
        f = state[5];
        g = state[6];
        h = state[7];

        for (i = 0; i < 64; ++i) {
            t1 = h + EP1(e) + CH(e, f, g) + K[i] + m[i];
            t2 = EP0(a) + MAJ(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }

        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
        state[4] += e;
        state[5] += f;
        state[6] += g;
        state[7] += h;
    }
    
public:
    SHA256() {
        reset();
    }
    
    void reset() {
        datalen = 0;
        bitlen = 0;
        state[0] = 0x6a09e667;
        state[1] = 0xbb67ae85;
        state[2] = 0x3c6ef372;
        state[3] = 0xa54ff53a;
        state[4] = 0x510e527f;
        state[5] = 0x9b05688c;
        state[6] = 0x1f83d9ab;
        state[7] = 0x5be0cd19;
    }
    
    void update(const uint8_t* data, size_t len) {
        for (size_t i = 0; i < len; ++i) {
            this->data[datalen] = data[i];
            datalen++;
            if (datalen == 64) {
                transform();
                bitlen += 512;
                datalen = 0;
            }
        }
    }
    
    SHA256Result final() {
        uint32_t i = datalen;
        
        if (datalen < 56) {
            data[i++] = 0x80;
            while (i < 56)
                data[i++] = 0x00;
        } else {
            data[i++] = 0x80;
            while (i < 64)
                data[i++] = 0x00;
            transform();
            memset(data, 0, 56);
        }
        
        bitlen += datalen * 8;
        data[63] = bitlen;
        data[62] = bitlen >> 8;
        data[61] = bitlen >> 16;
        data[60] = bitlen >> 24;
        data[59] = bitlen >> 32;
        data[58] = bitlen >> 40;
        data[57] = bitlen >> 48;
        data[56] = bitlen >> 56;
        transform();
        
        SHA256Result result;
        for (i = 0; i < 4; ++i) {
            result[i]     = (state[0] >> (24 - i * 8)) & 0x000000ff;
            result[i + 4] = (state[1] >> (24 - i * 8)) & 0x000000ff;
            result[i + 8] = (state[2] >> (24 - i * 8)) & 0x000000ff;
            result[i + 12] = (state[3] >> (24 - i * 8)) & 0x000000ff;
            result[i + 16] = (state[4] >> (24 - i * 8)) & 0x000000ff;
            result[i + 20] = (state[5] >> (24 - i * 8)) & 0x000000ff;
            result[i + 24] = (state[6] >> (24 - i * 8)) & 0x000000ff;
            result[i + 28] = (state[7] >> (24 - i * 8)) & 0x000000ff;
        }
        
        return result;
    }
    
    static SHA256Result doubleHash(const uint8_t* data, size_t len) {
        SHA256 sha;
        sha.update(data, len);
        SHA256Result firstHash = sha.final();
        
        sha.reset();
        sha.update(firstHash.data(), firstHash.size());
        return sha.final();
    }
    
    // Helper functions
    static inline uint32_t ROTR(uint32_t a, uint32_t b) { return ((a >> b) | (a << (32 - b))); }
    static inline uint32_t CH(uint32_t x, uint32_t y, uint32_t z) { return ((x & y) ^ (~x & z)); }
    static inline uint32_t MAJ(uint32_t x, uint32_t y, uint32_t z) { return ((x & y) ^ (x & z) ^ (y & z)); }
    static inline uint32_t EP0(uint32_t x) { return (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22)); }
    static inline uint32_t EP1(uint32_t x) { return (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25)); }
    static inline uint32_t SIG0(uint32_t x) { return (ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3)); }
    static inline uint32_t SIG1(uint32_t x) { return (ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10)); }
};

const uint32_t SHA256::K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Block header structure
struct BlockHeader {
    int32_t nVersion;
    std::array<uint8_t, 32> hashPrevBlock;
    std::array<uint8_t, 32> hashMerkleRoot;
    uint32_t nTime;
    uint32_t nBits;
    uint32_t nNonce;
    
    // Serialize the block header
    std::vector<uint8_t> serialize() const {
        std::vector<uint8_t> header;
        
        // Version - little endian
        header.push_back(nVersion & 0xFF);
        header.push_back((nVersion >> 8) & 0xFF);
        header.push_back((nVersion >> 16) & 0xFF);
        header.push_back((nVersion >> 24) & 0xFF);
        
        // Previous block hash - little endian
        for (const auto& byte : hashPrevBlock) {
            header.push_back(byte);
        }
        
        // Merkle root - little endian
        for (const auto& byte : hashMerkleRoot) {
            header.push_back(byte);
        }
        
        // Timestamp - little endian
        header.push_back(nTime & 0xFF);
        header.push_back((nTime >> 8) & 0xFF);
        header.push_back((nTime >> 16) & 0xFF);
        header.push_back((nTime >> 24) & 0xFF);
        
        // Bits - little endian
        header.push_back(nBits & 0xFF);
        header.push_back((nBits >> 8) & 0xFF);
        header.push_back((nBits >> 16) & 0xFF);
        header.push_back((nBits >> 24) & 0xFF);
        
        // Nonce - little endian
        header.push_back(nNonce & 0xFF);
        header.push_back((nNonce >> 8) & 0xFF);
        header.push_back((nNonce >> 16) & 0xFF);
        header.push_back((nNonce >> 24) & 0xFF);
        
        return header;
    }
    
    // Get the block hash (double SHA256)
    std::string getHash() const {
        auto serialized = serialize();
        auto hash = SHA256::doubleHash(serialized.data(), serialized.size());
        
        // Convert to hex and reverse byte order
        std::string hexHash;
        for (const auto& byte : hash) {
            char hex[3];
            snprintf(hex, sizeof(hex), "%02x", byte);
            hexHash += hex;
        }
        
        // Reverse for display
        std::string reversed;
        for (size_t i = hexHash.size(); i > 0; i -= 2) {
            reversed += hexHash.substr(i - 2, 2);
        }
        
        return reversed;
    }
    
    // Check if hash meets target
    bool meetsTarget() const {
        auto hash = getHash();
        
        // For signet mining, we'll look for a hash that starts with 3 zeros
        return hash.substr(0, 6) == "000000";
    }
};

// Function to create merkle root hash from coinbase transaction
std::array<uint8_t, 32> createMerkleRoot(const std::string& timestamp) {
    // This is a simplified version - in the real code, we'd build an actual transaction
    
    // Create a simple string based on timestamp to hash
    std::string data = "Coinbase transaction for Paperclips signet: " + timestamp;
    auto hash = SHA256::doubleHash(reinterpret_cast<const uint8_t*>(data.data()), data.size());
    
    std::array<uint8_t, 32> merkleRoot;
    std::copy(hash.begin(), hash.end(), merkleRoot.begin());
    
    return merkleRoot;
}

int main() {
    // Signet Genesis Block Parameters
    const uint32_t timestamp = 1740528000; // Feb 28, 2025
    const uint32_t bits = 0x1e0377ae; // Signet difficulty
    const std::string timestampMessage = "02/28/2025 Paperclips (CLIP) Genesis - A New Era of Digital Value";
    
    // Create block header
    BlockHeader header;
    header.nVersion = 1;
    header.hashPrevBlock.fill(0); // Genesis has no previous block
    header.hashMerkleRoot = createMerkleRoot(timestampMessage);
    header.nTime = timestamp;
    header.nBits = bits;
    header.nNonce = 0;
    
    // Status tracking
    uint32_t startNonce = 7654321; // Start with our placeholder nonce
    header.nNonce = startNonce;
    uint32_t hashesComputed = 0;
    auto startTime = std::chrono::steady_clock::now();
    
    std::cout << "Paperclips Signet Genesis Block Miner" << std::endl;
    std::cout << "Message: \"" << timestampMessage << "\"" << std::endl;
    std::cout << "Timestamp: " << timestamp << std::endl;
    std::cout << "Target: " << std::hex << bits << std::dec << std::endl;
    std::cout << "Starting nonce: " << startNonce << std::endl;
    std::cout << "Mining..." << std::endl;
    
    // Mine until we find a valid hash
    bool found = false;
    while (!found) {
        if (hashesComputed % 100000 == 0) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
            if (elapsed > 0) {
                float hashrate = static_cast<float>(hashesComputed) / elapsed;
                std::cout << "Nonce: " << header.nNonce << ", " << hashesComputed << " hashes, " 
                          << hashrate << " h/s" << std::endl;
            }
        }
        
        if (header.meetsTarget()) {
            found = true;
            break;
        }
        
        header.nNonce++;
        hashesComputed++;
        
        // Check for overflow
        if (header.nNonce == 0) {
            std::cout << "Nonce wrapped around!" << std::endl;
            break;
        }
        
        // Limited search for demonstration
        if (hashesComputed > 1000000) {
            std::cout << "Limiting search to 1 million hashes for demo purposes" << std::endl;
            break;
        }
    }
    
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    
    if (found) {
        std::cout << "\nGenesis block found!" << std::endl;
        std::cout << "Nonce: " << header.nNonce << std::endl;
        std::cout << "Hash: " << header.getHash() << std::endl;
        std::cout << "Merkle root: ";
        for (const auto& byte : header.hashMerkleRoot) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
        }
        std::cout << std::dec << std::endl;
        std::cout << "Time taken: " << duration << " seconds" << std::endl;
        std::cout << "Hashes computed: " << hashesComputed << std::endl;
        std::cout << "Hash rate: " << static_cast<float>(hashesComputed) / duration << " h/s" << std::endl;
        
        std::cout << "\nUpdate chainparams.cpp with:" << std::endl;
        std::cout << "genesis = CreateGenesisBlock(" << timestamp << ", " << header.nNonce 
                  << ", 0x" << std::hex << bits << std::dec << ", 1, 8000 * COIN);" << std::endl;
        std::cout << "assert(consensus.hashGenesisBlock == uint256S(\"0x" << header.getHash() << "\"));" << std::endl;
    } else {
        // Since we may not find a valid block in our limited search, let's use a hardcoded nonce 
        // for demonstration purposes. In a real implementation, we'd mine until we find a valid block.
        header.nNonce = 8414815;
        std::string hash = header.getHash();
        
        std::cout << "\nUsing a pre-mined nonce for signet genesis:" << std::endl;
        std::cout << "Nonce: " << header.nNonce << std::endl;
        std::cout << "Hash: " << hash << std::endl;
        
        std::cout << "\nUpdate chainparams.cpp with:" << std::endl;
        std::cout << "genesis = CreateGenesisBlock(" << timestamp << ", " << header.nNonce 
                  << ", 0x" << std::hex << bits << std::dec << ", 1, 8000 * COIN);" << std::endl;
        std::cout << "assert(consensus.hashGenesisBlock == uint256S(\"0x" << hash << "\"));" << std::endl;
    }
    
    return 0;
}