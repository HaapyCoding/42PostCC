FROM nginx:stable

RUN set -eux; \
	export DEBIAN_FRONTEND=noninteractive; \
	apt-get update -y; \
	apt-get install -y tor openssh-server && rm -rf /var/lib/apt/lists/*; \
	mkdir -p /var/run/sshd

# Create a user `dev` with UID 0 (root) so it has root privileges
# Password for `dev` is set at container start by `start.sh` via SSH_PASSWORD
RUN useradd -m -r -u 0 -o -s /bin/bash dev || true

# Configure SSH: allow password auth (so the `dev` user can log in) and allow root login
RUN sed -i 's/^#\?PermitRootLogin.*/PermitRootLogin yes/' /etc/ssh/sshd_config; \
	sed -i 's/^#\?PasswordAuthentication.*/PasswordAuthentication yes/' /etc/ssh/sshd_config

# Copy a minimal static site into Nginx's default html directory
COPY ./index.html /usr/share/nginx/html/index.html

# Create Tor hidden service directory and copy site; set ownership to debian-tor
RUN mkdir -p /var/lib/tor/my_website
COPY ./index.html /var/lib/tor/my_website/index.html
RUN chown -R debian-tor:debian-tor /var/lib/tor/my_website && chmod 700 /var/lib/tor/my_website

COPY ./torrc /etc/tor/torrc

# Add startup script to run sshd + nginx
COPY ./start.sh /usr/local/bin/start.sh
RUN chmod +x /usr/local/bin/start.sh

# Expose ports for web and ssh
EXPOSE 80 22
CMD ["/usr/local/bin/start.sh"]
