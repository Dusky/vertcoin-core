# Paperclips (CLIP) Core

![Paperclips Logo](share/pixmaps/vertcoin128.png)

## What is Paperclips?

Paperclips (CLIP) is a cryptocurrency focused on long-term sustainability, equitable distribution, and ASIC resistance.

- 3 minute block targets (20 blocks per hour)
- Initial block reward of 8,000 CLIP
- 20% reduction in block reward every 2 years (350,400 blocks)
- Maximum supply of 69 billion CLIP
- Difficulty retargeting every 20 blocks to adapt to hashrate changes
- Verthash proof of work algorithm for ASIC resistance
- 1% of transaction fees directed to development fund
- "C" prefix for legacy addresses, "clip" prefix for bech32 addresses (clip1q...)

For more information and binary releases, see our website: https://paperclips.org

## Getting Started

### Installation

Pre-built binaries for Windows, macOS, and Linux are available on our [releases page](https://github.com/paperclips-project/paperclips-core/releases).

#### Building from Source

See [doc/build-unix.md](doc/build-unix.md) for Linux/Unix build instructions, [doc/build-osx.md](doc/build-osx.md) for macOS, or [doc/build-windows.md](doc/build-windows.md) for Windows.

Quick start for Unix/Linux/macOS:
```bash
./autogen.sh
./configure
make
make install  # optional
```

### Using Docker

Paperclips provides Docker images for easy deployment. See the [docker/README.md](docker/README.md) for detailed instructions.

Quick start:
```bash
# Standard node
cd docker
cp .env.example .env
# Edit .env as needed
./run-node.sh --network mainnet --type standard --action start

# Or start a seed node
./run-node.sh --network mainnet --type seed --action start
```

## Wallet Options

### GUI Wallet

Run the Paperclips Qt wallet:
```bash
./paperclips-qt
```

### Command Line Wallet

#### 1. Run the Daemon

First, start the Paperclips daemon:
```bash
./paperclipsd
```

You can configure the daemon by editing `~/.paperclips/paperclips.conf`:
```
rpcuser=yourusername
rpcpassword=yourpassword
server=1
```

#### 2. Use the CLI Interface

Use the command-line interface to interact with your wallet:
```bash
# Basic commands
./paperclips-cli getinfo
./paperclips-cli getnewaddress
./paperclips-cli getbalance
./paperclips-cli sendtoaddress <address> <amount>

# Mining
./paperclips-cli generate <blocks>
./paperclips-cli generatetoaddress <blocks> <address>

# Multiple wallet support
./paperclips-cli -rpcwallet=<walletname> getbalance

# Get help
./paperclips-cli help
./paperclips-cli help <command>
```

## Mining

Paperclips uses the Verthash algorithm for mining. You can:

1. Solo mine using the built-in miner:
```bash
./paperclipsd -gen=1
```

2. Use a dedicated miner (to be released)

3. Join a mining pool (see website for recommendations)

## Network Information

- P2P Default Port: 5889
- RPC Default Port: 5888
- Testnet P2P Port: 15889
- Testnet RPC Port: 15888

## Development

The `master` branch is regularly built and tested, but is not guaranteed to be stable. [Tags](https://github.com/paperclips-project/paperclips-core/tags) are created for stable release versions.

### Contributing

Developers work on their own forks and submit pull requests to merge changes with `master`. See [CONTRIBUTING.md](CONTRIBUTING.md) for details.

The Paperclips Discord server is the best place to discuss changes before creating a pull request.

### Testing

```bash
make check        # Run unit tests
test/functional/test_runner.py  # Run functional tests
```

## License

Paperclips Core is released under the terms of the MIT license. See [COPYING](COPYING) for more information or see https://opensource.org/licenses/MIT.