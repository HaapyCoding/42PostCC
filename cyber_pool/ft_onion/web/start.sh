#!/bin/sh
set -e

# If SSH_PASSWORD is provided at runtime, set it for user 'dev'
if [ -n "${SSH_PASSWORD:-}" ]; then
  echo "dev:${SSH_PASSWORD}" | chpasswd || true
fi

# Start Tor hidden service
service tor start 

# Start sshd
/usr/sbin/sshd

chmod 700 /var/lib/tor/my_website/

# Start nginx in foreground
nginx -g 'daemon off;'


