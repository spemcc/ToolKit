var Snoocore = require('snoocore');

var APP_KEY = '',
    SECRET = '',
    USERNAME = '',
    PASSWORD = '',
    LIMIT = '',
    SUBREDDIT = ''; // ex. '/r/SUB'

var reddit = new Snoocore({
  userAgent: '/u/mod_pm_bot v0.0',
  oauth: { 
    type: 'script',
    key: process.env.REDDIT_APP || APP_KEY, 
    secret: process.env.REDDIT_SECRET || SECRET,
    username: 'mod_pm_bot',
    password: process.env.REDDIT_PASSWORD || PASSWORD,
    scope: ['privatemessages','read'] 
  }
});  

reddit(SUBREDDIT.concat('new')).listing({
  limit:LIMIT || 10
}).then(function(slice) {

  var msgs = [];
  for (var i in slice.children) {
    var str = '';
    msgs[i] = str.concat((Number(i)+1), '.', ' Title: ', 
      slice.children[i].data.title, '\n\n Url: ', 
      slice.children[i].data.url, '\n');
  }

  var msg = msgs.join('');
  reddit('/api/compose').post({
    api_type:'json',
    subject:'Weekly Mod Review',
    text: msg,
    to: USERNAME
  })

});

reddit.on('response_error', function(responseError) {
  console.log(responseError);
});
