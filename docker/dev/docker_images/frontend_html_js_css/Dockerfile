ARG NGINX_VERSION=latest
FROM nginx:${NGINX_VERSION}

COPY ./src/ /usr/share/nginx/html/
COPY --chmod=+x ./scripts/entrypoint.sh .
ENTRYPOINT [ "./entrypoint.sh" ]
