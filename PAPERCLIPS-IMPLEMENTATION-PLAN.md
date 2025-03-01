# Paperclips (CLIP) Implementation Plan

## Core Parameters
- **Name**: Paperclips
- **Ticker**: CLIP
- **Block Time**: 3 minutes (20 blocks per hour)
- **Maximum Supply**: 69 billion CLIP
- **Block Reward**: 8,000 CLIP initially, with 20% reduction every 2 years (350,400 blocks)
- **Mining Algorithm**: Verthash (keeping Vertcoin's algorithm)
- **Difficulty Adjustment**: Every 20 blocks (instead of every block)
- **Dev Fund**: 1% of transaction fees to development wallet
- **Address Format**: 
  - Legacy addresses start with "C"
  - Bech32 addresses use "clip" prefix (clip1q...)
- **Genesis Block**: February 28, 2025 - "Paperclips (CLIP) Genesis - A New Era of Digital Value"

## Completed Modifications

### Consensus Parameters
- [x] Modified `nSubsidyReductionInterval` parameter set to 350,400 blocks
- [x] Updated block time to 3 minutes (`nPowTargetSpacing` = 180 seconds)
- [x] Implemented 20% block reward reduction schedule (in `GetBlockSubsidy()`)
- [x] Implemented difficulty adjustment every 20 blocks

### Currency Units & Addresses
- [x] Changed currency units from VTC to CLIP
- [x] Updated address prefixes to use "C" for legacy addresses
- [x] Changed bech32 prefix from "vtc" to "clip" for SegWit addresses

### Fee Structure
- [x] Implemented 1% development fee from transaction fees
- [x] Added dev fund address in coinbase transaction creation

### Branding & Paths
- [x] Updated package name from "Vertcoin Core" to "Paperclips Core"
- [x] Changed all references to "Vertcoin" to "Paperclips" in UI text
- [x] Updated configuration filename to "paperclips.conf"
- [x] Updated data directory paths:
  - Windows: `%APPDATA%\Paperclips`
  - macOS: `~/Library/Application Support/Paperclips`
  - Linux: `~/.paperclips`
- [x] Changed binary names (paperclipsd, paperclips-qt, etc.)

### Genesis Block Creation
- [x] Created framework for new genesis block with timestamp of Feb 28, 2025
- [x] Updated coinbase message for genesis block
- [x] Set initial block reward to 8,000 CLIP
- [x] Created genesis block mining tools for each network type
- [x] Mined and implemented genesis blocks for all network types:
  - Mainnet: Genesis with nonce 19182709, hash 000000e167667283c96d4e3f486a3e70ea79ba4e325addb36f5d7c693ce19735
  - Testnet: Genesis with nonce 19182709, hash 000000e167667283c96d4e3f486a3e70ea79ba4e325addb36f5d7c693ce19735
  - Signet: Genesis with nonce 8414815, hash a374f453d8db43f42f9c6692c234b34def89e8b30b2adc3d08dbcffa791f9c2a
  - Regtest: Genesis with nonce 2, hash 807e2421b636aef33e4a2d1fbc3ea01eff2b0f075410f6490fea75a81363c2fe
- [x] Created documentation for genesis block mining in `GENESIS-BLOCK-MINING.md`

### Network Infrastructure
- [x] Defined placeholder seed nodes for mainnet, testnet, signet, and regtest
- [x] Updated seed node configuration in chainparams.cpp
- [x] Updated DNS seeds in contrib/seeds/nodes_main.txt and nodes_test.txt
- [x] Created documentation for seed node setup in `SEED-NODE-SETUP.md`

### Docker Deployment
- [x] Created Dockerfile for running nodes
- [x] Created specialized Dockerfile.seed for seed nodes
- [x] Set up docker-compose configurations
- [x] Documented Docker setup and usage

## Remaining Tasks

### Network Infrastructure
- [ ] Set up actual seed nodes on servers with static IPs
- [ ] Configure DNS records for seed nodes
- [ ] Generate final chainparamsseeds.h with real node data

### Visual Assets
- [ ] Create and replace logo files:
  - in share/pixmaps/
  - Update Qt resources
- [ ] Create new application icons

### Testing
- [ ] Verify all parameter changes
- [ ] Test block mining and reward calculation
- [ ] Test difficulty adjustment
- [ ] Test development fee distribution
- [ ] Test address generation and validation
- [ ] Perform regression tests

### Documentation
- [ ] Update all documentation files with Paperclips information
- [ ] Create installation guides
- [ ] Document key differences from Vertcoin

## Launch Preparation
- [ ] Set up block explorer
- [ ] Create mining pool
- [ ] Prepare wallet binaries for all platforms
- [ ] Establish community channels (website, Discord, etc.)

## Implementation Notes
- Paperclips reuses Verthash mining algorithm but with different parameters
- Development fee is implemented at the protocol level, not voluntary
- Inflation schedule is more gradual than Bitcoin's halving model
- Initial launch parameters can be adjusted before mainnet if needed
- Genesis block and seed node configurations need real-world deployment before launch