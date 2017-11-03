#!/usr/bin/env node

var client = require('./rest-client.js');

client.ok = function (response) {
    console.log(response.status);
    console.log(response.data);
};

client.err = function (error) {
  console.log(error);
};


client.get(1);
client.add({ label: 'this is new add item', isFinished: true });
client.list();

/*
// add


// modify
client.modify(2, { label: 'modify item', isFinished: true });
client.list();

 // delete
 client.delete(2);
 client.list();


 */
