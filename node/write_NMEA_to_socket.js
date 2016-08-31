
const net = require('net');
const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});


rl.question('Input IP ADDRESS: ', (ip_address) => {
  rl.question('Input Port : ', (port) => {
    const client = net.createConnection({ host: ip_address, port: port}, () => {
      console.log('connected to server!');
      function getData()
      {
        rl.question('Input Data : ', (data) => {
         CheckSum(data,function(fullstring) {
            client.write(data+'*'+fullstring.toString() + '\n');
            getData();
          });
        });
      }
          getData();
      });

      client.on('data', (data) => {
        console.log('\n\n');
        console.log(data.toString());
      });

      client.on('end', () => {
        console.log('disconnected from server');
        rl.close();
      });

      client.on('error', (e) => {
        console.log('We got an error:' , e);
        rl.close();
      });
  });
});




function CheckSum(data, callback)
{
  var checksum = 0; 
  for(var i = 1; i < data.length; i++) { 
      checksum = checksum ^ data.charCodeAt(i); 
  }
  callback(checksum.toString(16));
}
