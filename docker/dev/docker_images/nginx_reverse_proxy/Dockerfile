FROM nginx:latest

COPY default.conf /etc/nginx/conf.d/

COPY --chmod=+x entrypoint.sh .
ENTRYPOINT [ "./entrypoint.sh" ]
