FROM nginx:latest

COPY default.conf /etc/nginx/conf.d/

COPY entrypoint.sh .
ENTRYPOINT [ "./entrypoint.sh" ]
