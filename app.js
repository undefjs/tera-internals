'use strict';
//---
const INJECT_DLL = true;
const TERA_EXE = 'TERA.exe';
const PATH_INJECTOR = `${__dirname}/bin/injector.exe`;
const PATH_GUARD = `${__dirname}/bin/teraguard.dll`;
const GUARD_PORT = 1337;
const GUARD_HOST = '127.0.0.1';
//---
const os = require('os');
const util = require('util');
const execFile = util.promisify(require('child_process').execFile);
const find = require('find-process');
const { log } = console;
//---
async function injectDLL() {
  if(os.platform() !== 'win32')
    throw new Error('Can\'t inject dll from this OS, do it manually or run with --no-inject??');
  
  const list = await find('name', TERA_EXE);
  
  if(!list.length)
    throw new Error(`Process '${TERA_EXE}' not found`);
  if(list.length > 1)
    throw new Error(`ERROR: Multiple '${TERA_EXE}' clients found, run with --pid=<PID>??`);
  
  try {
    await execFile(PATH_INJECTOR, [list[0].pid, PATH_GUARD]);
  }
  catch(e) {
    throw new Error(`Injector failed, not enough privileges??, ExitCode: ${e.code}`);
  }
}
//---
(async function() {
  if(INJECT_DLL) {
    try { await injectDLL(); }
    catch(e) { return console.error(e); }
    log('- Guard injected');
  }
  
  const repl = require('repl');
  
  const net = require('net');
  const s = new net.Socket();
  s.connect(GUARD_PORT, GUARD_HOST, function() {
    log('- Socket connected');
  
    function replHandler(cmd, context, filename, callback) {
      s.once('data', data => callback(null, JSON.parse(data)));
      s.write(cmd.replace(/\n/g, '') + '\n');
    }
    
    const replServer = repl.start({ prompt: '> ', eval: replHandler });
    replServer.on('exit', () => s.destroy());
    
    s.on('error', e => {
      replServer.close();
      log('- Connection error: %s', e.message);
    });
    s.on('close', () => {
      replServer.close();
      log('- Connection closed');
    });
    
  });

})();
