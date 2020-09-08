module.exports = {
    influxdb: {
        host: process.env['INFLUXDB_HOST'],
        database: process.env['INFLUXDB_DATABASE'],
        username: process.env['INFLUXDB_USERNAME'],
        password: process.env['INFLUXDB_PASSWORD']
    }
}