ARG NGINX_VERSION=latest
FROM nginx:${NGINX_VERSION}

COPY default.conf /etc/nginx/conf.d/

COPY --chmod=+x entrypoint.sh .
ENTRYPOINT [ "./entrypoint.sh" ]
