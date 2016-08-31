var querystring = require('querystring');
var HMAC_SHA384 = require('crypto-js/hmac-sha384');
var ENC_B64 = require('crypto-js/enc-base64');
var HttpHelpers = require('./utils/http_helper.js');

/**
 * Bitfinex Authentication Protocol
 * payload = parameters-dictionary -> JSON encode -> base64
 * signature = HMAC-SHA384(payload, api-secret) as hexadecimal
 * send (api-key, payload, signature)
    headers: {
      'X-BFX-APIKEY': ,
      'X-BFX-PAYLOAD': ,
      'X-BFX-SIGNATURE':
    }
 */

var Bitfinex =  function() {
  if( !(this instanceof Bitfinex) ) {
    return new Bitfinex();
  } else {
    this.API_URL = 'api.bitfinex.com';
  }
}

/**
 * @param {object} [options]
 * @param {integer} [options.bid_limit = 50] - # of bids 
 * @param {integer} [options.ask_limit = 50] - # of asks 
 * @param {integer} [options.groups = 1] - true or false - sorted by price
 * @param {callback} callback - orderbook data
 */
Bitfinex.prototype.getOrderBook = function(options, callback) {

  if(typeof options === 'function') {
    callback = options;
    options = '';
  }

  var http_options = {
    path: '/v1/book/btcusd?' + querystring.stringify(options),
  }

  HttpHelpers.httpsGetReq.call(this, http_options, callback);
}

/**
 * @param {object} [options]
 * @param {integer} [options.timestamp] - only show after this time
 * @param {integer} [options.limit_trades] - # of trades returned 
 * @param {callback} callback - trades data
 */
Bitfinex.prototype.getTrades = function(options, callback) {
  if(typeof options === 'function') {
    callback = options;
    options = '';
  }

  var http_options = {
    path: '/v1/trades/btcusd?' + querystring.stringify(options),
  }

  HttpHelpers.httpsGetReq.call(this, http_options, callback);
}


module.exports = Bitfinex;
