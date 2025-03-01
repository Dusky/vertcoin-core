# Paperclips Development Fund

## Overview

The Paperclips (CLIP) cryptocurrency includes a 1% development fee on all transaction fees. This fee is automatically sent to the official development fund address with each block that is mined.

## Development Fund Address

The official development fund address is:

```
CeyfoA5q3wEE1T3jCuFJxiShdkcmrgQxPW
```

This address was generated deterministically using a secure key generation process. The private key for this address is securely stored by the Paperclips development team.

## Fee Structure

- 1% of all transaction fees in each block is sent to the development fund
- The development fee is taken before the block reward is paid to miners
- If there are no transaction fees in a block, no development fee is paid

## Purpose of the Development Fund

The development fund will be used for:

1. Ongoing development and maintenance of the Paperclips codebase
2. Security audits and bug bounties
3. Infrastructure costs for seed nodes and other network services
4. Marketing and community building efforts
5. Exchange listing fees and other ecosystem development costs

## Transparency

The Paperclips development team commits to:

1. Publishing quarterly reports on the use of development funds
2. Maintaining transparency in all spending decisions
3. Prioritizing expenditures that benefit the long-term health of the network

## Implementation Details

The development fee is implemented directly in the block creation code in `src/node/miner.cpp`. When a new block is mined, 1% of the transaction fees are automatically sent to the development fund address before the remaining rewards are sent to the miner.
