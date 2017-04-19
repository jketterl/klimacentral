var express = require('express'),
    bodyParser = require('body-parser'),
    influx = require('./lib/influx');

var app = express();
app.use(bodyParser.json());

app.post('/api/klima', function(req, res) {
    console.info(req.body);
    influx.writePoints([{
        measurement: 'klima',
        tags: { host: req.body.host },
        fields: {
            temperature: req.body.temperature,
            humidity: req.body.humidity
        }
    }]).then(function(){
        res.json({"success":true});
    });
});

app.listen(4000);
