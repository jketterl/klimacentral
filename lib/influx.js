var Influx = require('influx');
var config = require('./config').influxdb;

module.exports = new Influx.InfluxDB({
    host: config.host,
    database: config.database,
    username: config.username,
    password: config.password
});
