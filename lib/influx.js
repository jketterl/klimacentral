var Influx = require('influx');

module.exports = new Influx.InfluxDB({
    host: 'localhost',
    database: 'klima',
    username: 'graphite',
    password: 'graphite'
});
