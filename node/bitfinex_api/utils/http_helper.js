var https = require('https');
var bl = require('bl');


var HTTP_HELPER =  {

  httpsGetReq: function(options, callback) {

    options.hostname = this.API_URL;
    options.method = 'GET';

    https.get(options, function(response) {
      response.pipe(bl(function (err, data_buffer) {  
        if (err)
          return console.error(data_buffer)
        data_buffer = JSON.parse(data_buffer.toString());                 
        callback((data_buffer));
      }))
    }).on('error', function(e) {
      console.log("Got error: " + e.message);
    });
  }


}

module.exports = HTTP_HELPER;

