FROM ubuntu:22.04

LABEL maintainer="Paperclips Core Team"
LABEL description="Paperclips Core node in Docker"

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    libtool \
    autotools-dev \
    automake \
    pkg-config \
    libssl-dev \
    libevent-dev \
    bsdmainutils \
    libboost-system-dev \
    libboost-filesystem-dev \
    libboost-chrono-dev \
    libboost-program-options-dev \
    libboost-test-dev \
    libboost-thread-dev \
    libminiupnpc-dev \
    libzmq3-dev \
    git \
    curl \
    wget \
    jq \
    python3 \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /opt/paperclips

# Copy source files (assumes this is run from the root of the project)
COPY . .

# Build Paperclips
RUN ./autogen.sh && \
    ./configure --disable-wallet --disable-tests --disable-bench --disable-gui && \
    make -j$(nproc) && \
    make install

# Create data directory
RUN mkdir -p /data

# Create configuration file with safe defaults
RUN mkdir -p /root/.paperclips/
RUN echo "rpcuser=paperclipsrpc\n\
rpcpassword=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1)\n\
rpcallowip=127.0.0.1\n\
rpcallowip=172.17.0.0/16\n\
rpcallowip=192.168.0.0/16\n\
rpcallowip=10.0.0.0/8\n\
rpcbind=0.0.0.0\n\
server=1\n\
daemon=0\n\
txindex=1\n\
listen=1\n\
discover=1\n\
maxconnections=125\n\
" > /root/.paperclips/paperclips.conf

# Expose ports (P2P and RPC)
EXPOSE 5889 5888

# Set volume for blockchain data
VOLUME ["/root/.paperclips"]

# Create entrypoint script
RUN echo '#!/bin/bash\n\
exec paperclipsd -datadir=/root/.paperclips "$@"\n\
' > /entrypoint.sh && chmod +x /entrypoint.sh

# Set entrypoint
ENTRYPOINT ["/entrypoint.sh"]

# Default command
CMD ["--printtoconsole"]