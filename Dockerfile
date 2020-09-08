FROM node:14-alpine

COPY index.js \
     package.json \
     package-lock.json \
     /opt/klimacentral/
COPY lib /opt/klimacentral/lib/
WORKDIR /opt/klimacentral

RUN ["npm", "install"]

EXPOSE 4000

CMD ["index.js"]