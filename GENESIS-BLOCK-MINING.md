# Paperclips (CLIP) Genesis Block Mining Guide

This guide explains how to mine the genesis block for Paperclips (CLIP) cryptocurrency. In the code, we've set placeholder values, but in a real implementation, you need to mine valid blocks.

## The Importance of Genesis Block Mining

The genesis block is the first block in the blockchain. Its hash is used to verify the integrity of the entire chain. Mining the genesis block means finding a valid nonce that produces a hash meeting the required difficulty target.

## The Mining Process

1. **Compile and run the genesis block miner**

   We've provided a simplified mining script in `src/gen_genesis.cpp`. In a real implementation, you'd want a more robust miner:

   ```
   g++ -o genesis_miner src/gen_genesis.cpp -std=c++11
   ./genesis_miner
   ```

2. **Configure the parameters**

   Key parameters for the genesis block:
   - `nTime`: Timestamp (we've set to February 28, 2025 - 1740528000)
   - `nBits`: Difficulty target (we've set to 0x1e0ffff0)
   - `pszTimestamp`: The coinbase message ("02/28/2025 Paperclips (CLIP) Genesis - A New Era of Digital Value")
   - `genesisReward`: Initial reward (we've set to 8000 CLIP)

3. **Once a valid block is found**

   Update the following files with the correct values:
   - In `src/chainparams.cpp`:
     - Update the nonce value for each network's genesis block
     - Uncomment and update the assertions with the correct hash values
   - Verify that the genesis block's Merkle root is correct

4. **For all networks**

   You'll need to mine a genesis block for:
   - Mainnet: The primary network
   - Testnet: For testing without real value
   - Signet: For testing with signature-based consensus
   - Regtest: For local regression testing

## Running in a Real Implementation

For a real cryptocurrency launch, you would need to:

1. Mine actual genesis blocks with valid hashes
2. Configure real DNS seed nodes that you control
3. Generate a proper `chainparamsseeds.h` file using the tools in `contrib/seeds/`
4. Build and distribute the finalized software

## Example Genesis Block Values (Placeholder)

In our code base, we've used these placeholder values:

```cpp
// Mainnet
genesis = CreateGenesisBlock(1740528000, 2083236893, 0x1e0ffff0, 1, 8000 * COIN);

// Testnet
genesis = CreateGenesisBlock(1740528000, 1234567, 0x1e0ffff0, 1, 8000 * COIN);

// Signet
genesis = CreateGenesisBlock(1740528000, 7654321, 0x1e0377ae, 1, 8000 * COIN);

// Regtest
genesis = CreateGenesisBlock(1740528000, 2, 0x207fffff, 1, 8000 * COIN);
```

These placeholder values should be replaced with actual mined values in production.