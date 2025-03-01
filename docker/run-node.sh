#!/bin/bash

# Paperclips Node Launcher Script
# This script helps you easily launch a Paperclips node in a Docker container

# Check if Docker is installed
if ! command -v docker &> /dev/null; then
    echo "Docker not found. Please install Docker first."
    exit 1
fi

# Check if docker-compose is installed
if ! command -v docker-compose &> /dev/null; then
    echo "docker-compose not found. Please install docker-compose first."
    exit 1
fi

# Default values
NETWORK="mainnet"
NODE_TYPE="standard"
ACTION="start"

# Function to display help
show_help() {
    echo "Paperclips Node Launcher"
    echo ""
    echo "Usage: $0 [options]"
    echo ""
    echo "Options:"
    echo "  -n, --network <network>   Network to use (mainnet, testnet, signet, regtest)"
    echo "  -t, --type <type>         Node type (standard, seed)"
    echo "  -a, --action <action>     Action to perform (start, stop, restart, logs)"
    echo "  -h, --help                Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0 --network testnet --type seed --action start"
    echo "  $0 -n mainnet -t standard -a restart"
    echo ""
}

# Parse arguments
while [[ "$#" -gt 0 ]]; do
    case $1 in
        -n|--network) NETWORK="$2"; shift ;;
        -t|--type) NODE_TYPE="$2"; shift ;;
        -a|--action) ACTION="$2"; shift ;;
        -h|--help) show_help; exit 0 ;;
        *) echo "Unknown parameter: $1"; show_help; exit 1 ;;
    esac
    shift
done

# Validate network
if [[ "$NETWORK" != "mainnet" && "$NETWORK" != "testnet" && "$NETWORK" != "signet" && "$NETWORK" != "regtest" ]]; then
    echo "Invalid network: $NETWORK"
    echo "Valid networks are: mainnet, testnet, signet, regtest"
    exit 1
fi

# Validate node type
if [[ "$NODE_TYPE" != "standard" && "$NODE_TYPE" != "seed" ]]; then
    echo "Invalid node type: $NODE_TYPE"
    echo "Valid node types are: standard, seed"
    exit 1
fi

# Validate action
if [[ "$ACTION" != "start" && "$ACTION" != "stop" && "$ACTION" != "restart" && "$ACTION" != "logs" ]]; then
    echo "Invalid action: $ACTION"
    echo "Valid actions are: start, stop, restart, logs"
    exit 1
fi

# Set docker-compose file based on node type
if [[ "$NODE_TYPE" == "seed" ]]; then
    COMPOSE_FILE="docker-compose.seed.yml"
    CONTAINER_NAME="paperclips-seed-${NETWORK}"
else
    COMPOSE_FILE="docker-compose.yml"
    CONTAINER_NAME="paperclips-node"
fi

# Execute the requested action
case $ACTION in
    start)
        echo "Starting Paperclips $NODE_TYPE node on $NETWORK..."
        NETWORK=$NETWORK docker-compose -f $COMPOSE_FILE up -d
        ;;
    stop)
        echo "Stopping Paperclips $NODE_TYPE node on $NETWORK..."
        NETWORK=$NETWORK docker-compose -f $COMPOSE_FILE down
        ;;
    restart)
        echo "Restarting Paperclips $NODE_TYPE node on $NETWORK..."
        NETWORK=$NETWORK docker-compose -f $COMPOSE_FILE restart
        ;;
    logs)
        echo "Showing logs for Paperclips $NODE_TYPE node on $NETWORK..."
        docker logs -f $CONTAINER_NAME
        ;;
esac

# Check result
if [ $? -eq 0 ]; then
    if [[ "$ACTION" == "start" ]]; then
        echo "Paperclips $NODE_TYPE node on $NETWORK started successfully!"
        echo "To view logs, run: $0 -n $NETWORK -t $NODE_TYPE -a logs"
    elif [[ "$ACTION" == "stop" ]]; then
        echo "Paperclips $NODE_TYPE node on $NETWORK stopped successfully!"
    elif [[ "$ACTION" == "restart" ]]; then
        echo "Paperclips $NODE_TYPE node on $NETWORK restarted successfully!"
        echo "To view logs, run: $0 -n $NETWORK -t $NODE_TYPE -a logs"
    fi
else
    echo "Error performing $ACTION on Paperclips $NODE_TYPE node on $NETWORK!"
fi