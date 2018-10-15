'use strict';
//---
//const TeraInternals = require('./bin/terainternals.node');
//console.log(TeraInternals.initGuard(`${__dirname}\\bin\\teraguard32.dll`));

//--

const { log } = console;
const DEFAULT_PORT = 1337;

const net = require('net');
const s = new net.Socket();
s.connect(DEFAULT_PORT, '127.0.0.1', function() {
  log('Connected');
  s.write('print');
});
s.on('data', function(data) {
  log(JSON.parse(data));
  //client.destroy();
});
s.on('close', function() {
  log('Connection closed');
});
