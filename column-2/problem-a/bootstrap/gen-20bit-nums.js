'use strict';

var BIT_SCALE = 20;
var NUMS = 1000000;

function random_bool() {
  return Math.random() < 0.5;
}

function random_nbit_int(n) {
  var res, i=0, bit=0;
  for(; i<n; i+=1) {
    bit = random_bool() ? 1 : 0;
    res |= bit << i;
  }

  return res;
}

var counter = 0;
for(; counter< NUMS; counter+=1) {
  console.log(random_nbit_int(BIT_SCALE));
}
