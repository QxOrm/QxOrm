ARG NGINX_VERSION=latest
FROM nginx:${NGINX_VERSION}

COPY --chmod=+x ./scripts/entrypoint.sh .
ENTRYPOINT [ "./entrypoint.sh" ]
