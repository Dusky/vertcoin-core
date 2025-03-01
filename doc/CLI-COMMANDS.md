# Paperclips CLI Commands Reference

This document provides a reference for commonly used Paperclips Core CLI commands. These commands can be used with the `paperclips-cli` utility when running `paperclipsd`.

## Basic Syntax

```
paperclips-cli [options] <command> [params]
paperclips-cli [options] -named <command> [name=value]...
paperclips-cli [options] help
paperclips-cli [options] help <command>
```

Common options:
- `-rpcuser=<user>`: Username for JSON-RPC connections
- `-rpcpassword=<pw>`: Password for JSON-RPC connections
- `-rpcwallet=<wallet>`: Send commands to a specific wallet
- `-rpcport=<port>`: Connect to JSON-RPC on specific port (default: 5888)
- `-testnet`: Use the test network
- `-regtest`: Use the regression test network
- `-signet`: Use the signet test network

## Wallet Commands

### Account and Address Management

```bash
# Generate a new address
paperclips-cli getnewaddress [account] [address_type]

# Get wallet balance
paperclips-cli getbalance [minconf=1] [include_watchonly=false]

# List accounts and balances
paperclips-cli listaccounts [minconf=1] [include_watchonly=false]

# List addresses
paperclips-cli listaddressgroupings

# List unspent transaction outputs (UTXOs)
paperclips-cli listunspent [minconf=1] [maxconf=9999999]

# Import a private key
paperclips-cli importprivkey <privkey> [label] [rescan=true]
```

### Transaction Management

```bash
# Send to an address
paperclips-cli sendtoaddress <address> <amount> [comment] [comment-to] [fee_rate]

# Create a raw transaction
paperclips-cli createrawtransaction [{"txid":"id","vout":n},...] {"address":amount,...}

# Sign a raw transaction
paperclips-cli signrawtransactionwithwallet <hexstring> [{"txid":"id","vout":n,"scriptPubKey":"hex","redeemScript":"hex"},...] [sighashtype="ALL"]

# Send a raw transaction
paperclips-cli sendrawtransaction <hexstring> [max_fee_rate]

# Get transaction details
paperclips-cli gettransaction <txid> [include_watchonly=false]

# List recent transactions
paperclips-cli listtransactions [count=10] [skip=0] [include_watchonly=false]
```

### Wallet Management

```bash
# Create a new wallet
paperclips-cli createwallet <wallet_name> [disable_private_keys] [blank] [passphrase]

# List available wallets
paperclips-cli listwallets

# Load a wallet
paperclips-cli loadwallet <filename>

# Lock wallet
paperclips-cli walletlock

# Unlock wallet
paperclips-cli walletpassphrase <passphrase> <timeout>

# Backup wallet
paperclips-cli backupwallet <destination>

# Dump private key
paperclips-cli dumpprivkey <address>
```

## Blockchain Commands

```bash
# Get blockchain info
paperclips-cli getblockchaininfo

# Get block hash at height
paperclips-cli getblockhash <height>

# Get block details
paperclips-cli getblock <hash|height> [verbosity]

# Get info about transaction in mempool
paperclips-cli getmempoolentry <txid>

# Get mempool info
paperclips-cli getmempoolinfo

# Get details about a transaction
paperclips-cli getrawtransaction <txid> [verbose=false]
```

## Mining Commands

```bash
# Generate blocks
paperclips-cli generate <nblocks> [maxtries]

# Generate blocks to a specific address
paperclips-cli generatetoaddress <nblocks> <address> [maxtries]

# Get mining info
paperclips-cli getmininginfo

# Get network hash power
paperclips-cli getnetworkhashps [nblocks=120] [height=-1]

# Submit a block
paperclips-cli submitblock <hexdata> [dummy]
```

## Network Commands

```bash
# Get node connection info
paperclips-cli getconnectioncount

# Get peers info
paperclips-cli getpeerinfo

# Add a node
paperclips-cli addnode <node> <add|remove|onetry>

# Get network info
paperclips-cli getnetworkinfo

# List banned peers
paperclips-cli listbanned

# Ban a peer
paperclips-cli setban <subnet> <add|remove> [bantime=86400] [absolute=false]
```

## Utility Commands

```bash
# Get general info (alias for several RPC calls)
paperclips-cli getinfo

# Verify message signature
paperclips-cli verifymessage <address> <signature> <message>

# Sign a message
paperclips-cli signmessage <address> <message>

# Estimate fee
paperclips-cli estimatesmartfee <conf_target> [estimate_mode="CONSERVATIVE"]

# Get network info
paperclips-cli -netinfo 
```

## Examples

### Basic Wallet Operations

```bash
# Create a new wallet
paperclips-cli createwallet "mywallet"

# Generate a new address
paperclips-cli getnewaddress
# Result: C8a7ApLVY6RxK5EGfccjHY7QGbA9Vaowwh

# Check your balance
paperclips-cli getbalance
# Result: 125.00000000

# Send funds
paperclips-cli sendtoaddress C8a7ApLVY6RxK5EGfccjHY7QGbA9Vaowwh 10.0 "payment for services" "to john doe"
# Result: 7f24a457533c5cc6c47...4a37d0dcfd8e8f2 (transaction id)

# Get transaction details
paperclips-cli gettransaction 7f24a457533c5cc6c47...4a37d0dcfd8e8f2
```

### Mining Example

```bash
# Generate 1 block to your address
paperclips-cli getnewaddress
# Result: C8a7ApLVY6RxK5EGfccjHY7QGbA9Vaowwh

paperclips-cli generatetoaddress 1 C8a7ApLVY6RxK5EGfccjHY7QGbA9Vaowwh
# Result: ["00000007fa34f47e24a3...ff834fb241e38235f"]
```

## Multi-Wallet Usage

```bash
# List wallets
paperclips-cli listwallets
# Result: ["wallet1.dat", "wallet2.dat"]

# Send from a specific wallet
paperclips-cli -rpcwallet=wallet1.dat sendtoaddress C8a7ApLVY6RxK5EGfccjHY7QGbA9Vaowwh 5.0
```

## Getting Help

For more detailed information on each command:

```bash
# List all available commands
paperclips-cli help

# Get help for a specific command
paperclips-cli help sendtoaddress
```