# Paperclips (CLIP) Seed Node Setup Guide

This guide explains how to set up seed nodes for the Paperclips cryptocurrency network. Seed nodes are critical for new nodes to discover peers when joining the network.

## Types of Seed Nodes

In Paperclips, there are two main types of seed nodes:

1. **DNS Seed Nodes**: DNS servers that return IP addresses of active nodes
2. **Fixed Seed Nodes**: Hardcoded IP addresses in the chainparams.cpp file

## Setting Up DNS Seed Nodes

### 1. Requirements

- A domain name (e.g., paperclips.network)
- Server with a static IP address
- DNS hosting service

### 2. Setting Up the DNS Server

Create DNS A records for your seed nodes:

```
seed1.paperclips.network.   IN   A   123.45.67.89
seed2.paperclips.network.   IN   A   98.76.54.32
seed3.paperclips.network.   IN   A   111.222.333.444
```

For IPv6 addresses, use AAAA records.

### 3. Running a DNS Seeder

You can use the DNS seeder code in `contrib/seeds/` to automatically maintain a list of valid nodes:

1. Compile and run the seeder:
   ```
   cd contrib/seeds/
   make
   ./dnsseed -h seed1.paperclips.network -n 123.45.67.89
   ```

2. The seeder will crawl the network and automatically update DNS records.

## Setting Up Fixed Seed Nodes

Fixed seed nodes are hardcoded in `src/chainparams.cpp` and `src/chainparamsseeds.h`.

### 1. Run Reliable Full Nodes

Set up reliable full nodes with:
- Static IP addresses
- Good bandwidth
- High availability
- Fully synced blockchain

### 2. Update the Node Lists

1. Add IP addresses to `contrib/seeds/nodes_main.txt` (mainnet) and `contrib/seeds/nodes_test.txt` (testnet)

2. Generate the seeds header file:
   ```
   cd contrib/seeds/
   python3 generate-seeds.py . > ../../src/chainparamsseeds.h
   ```

3. Update the DNS names in `src/chainparams.cpp`:
   ```cpp
   vSeeds.emplace_back("seed1.paperclips.network");
   vSeeds.emplace_back("seed2.paperclips.network");
   vSeeds.emplace_back("seed3.paperclips.network");
   vSeeds.emplace_back("dnsseed.paperclips.network");
   ```

## Maintenance Responsibilities

Operating seed nodes comes with responsibilities:

1. Ensure high uptime (24/7 operation)
2. Keep nodes updated with the latest software
3. Monitor for attacks or malicious behavior
4. Maintain proper network security
5. Regularly update the list of good peers

## Current Paperclips Seed Configuration

In our repository, we've configured:

1. **Mainnet Seeds**:
   - seed1.paperclips.network
   - seed2.paperclips.network
   - seed3.paperclips.network
   - dnsseed.paperclips.network

2. **Testnet Seeds**:
   - testseed1.paperclips.network
   - testseed2.paperclips.network

3. **Signet Seeds**:
   - signetseed1.paperclips.network
   - signetseed2.paperclips.network

4. **Regtest Seed**:
   - regtestseed.paperclips.network

**Note**: These are placeholder domains. In a real implementation, you need to use actual domains and servers that you control.