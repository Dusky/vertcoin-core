# Paperclips Docker Setup

This directory contains Docker configurations for easily running Paperclips (CLIP) nodes.

## Quick Start

### Using the Helper Script

The easiest way to run a Paperclips node is using the included helper script:

```bash
# Clone the repository
git clone https://github.com/your-org/paperclips-core.git
cd paperclips-core/docker

# Copy and edit the environment configuration
cp .env.example .env
# Edit .env with your preferred settings

# Make the script executable
chmod +x run-node.sh

# Start a standard node on mainnet
./run-node.sh --network mainnet --type standard --action start

# Or start a seed node on testnet
./run-node.sh -n testnet -t seed -a start

# View logs
./run-node.sh -n mainnet -t standard -a logs

# Stop the node
./run-node.sh -n mainnet -t standard -a stop
```

### Using docker-compose Directly

You can also use docker-compose commands directly:

```bash
# Clone the repository
git clone https://github.com/your-org/paperclips-core.git
cd paperclips-core/docker

# Copy and edit the environment configuration
cp .env.example .env
# Edit .env with your preferred settings

# Start the node
docker-compose up -d
```

## Available Configurations

### 1. Standard Node

The standard node setup includes a full Paperclips node that participates in the network.

```bash
# Start a standard node
docker-compose up -d
```

### 2. Seed Node

For running a dedicated seed node to help other peers join the network:

```bash
# Start a seed node
docker-compose -f docker-compose.seed.yml up -d
```

### Network Selection

You can choose which network to run on by setting the `NETWORK` environment variable:

```bash
# Run on the testnet
NETWORK=testnet docker-compose up -d

# Run on the signet
NETWORK=signet docker-compose up -d

# Run on regtest (for development)
NETWORK=regtest docker-compose up -d
```

## Configuration Options

Edit the `.env` file to customize your node's behavior:

- `NETWORK`: Select which network to join (mainnet, testnet, signet, regtest)
- `RPC_USER` and `RPC_PASSWORD`: Credentials for JSON-RPC access
- `P2P_PORT`: Port mapping for P2P communication
- `HOST_DATA_DIR`: Local directory to store blockchain data
- `EXTERNAL_IP`: Your node's external IP address (important for seed nodes)
- `MAX_CONNECTIONS`: Maximum number of connections to accept

## Running Multiple Nodes

You can run multiple nodes by using different container names and port mappings:

```bash
# Start mainnet and testnet nodes simultaneously
NETWORK=mainnet docker-compose -p paperclips-mainnet up -d
NETWORK=testnet docker-compose -p paperclips-testnet up -d
```

## Accessing the Node

### RPC Commands

To interact with your running node via RPC:

```bash
# Example RPC command
docker exec paperclips-node paperclips-cli -rpcuser=paperclipsrpc -rpcpassword=yourpassword getblockchaininfo
```

### Logs

To view the node logs:

```bash
docker-compose logs -f
```

## Seed Node Configuration

If you're running a seed node that will be listed in the network's DNS seeds:

1. Ensure your server has a static IP address
2. Set `EXTERNAL_IP` in your `.env` file
3. Configure your firewall to allow inbound connections on port 5889
4. Contact the Paperclips developers to add your node to the DNS seeds list

## Upgrading

To upgrade to a new version:

```bash
# Pull latest code
git pull

# Rebuild and restart the container
docker-compose build --no-cache
docker-compose up -d
```

## Troubleshooting

### Common Issues

- **Port conflicts**: If port 5889 is already in use, change the port mapping in the `.env` file
- **Disk space**: Ensure you have enough disk space for the blockchain data
- **Connectivity**: Check your firewall settings if you're having trouble connecting to peers

For more help, please open an issue on the GitHub repository.