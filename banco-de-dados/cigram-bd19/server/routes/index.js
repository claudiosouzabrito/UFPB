const users = require('./user')
const auth = require('./auth')
const post = require('./post')
const topico = require("./topico")
// const photo = require('./photo')
const block = require("./block")
const follow = require("./follow")

module.exports = app => {
  app.use('/users', users);
  app.use('/auth', auth);
  app.use('/posts', post);
  app.use('/topicos', topico);
  app.use('/block',  block);
  app.use('/follow',  follow);


  // etc..
}