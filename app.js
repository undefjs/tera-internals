'use strict';
//---
const TeraInternals = require('./bin/terainternals.node');
console.log(TeraInternals.initGuard(`${__dirname}\\bin\\teraguard32.dll`));
