const Router = require('express-promise-router')
const db = require('../db')

const router = new Router()

module.exports = router

router.post('/login', async (req, res) => {
    const query = `SELECT * FROM usuario WHERE username = '${req.body.username}';`;
    if(req.session.user) {res.send("Already Logged in"); return};
    db.query(query, []).then((row) => { 
        if(!Array.isArray(row.rows) || !row.rows.length) {
            throw new Error("User not found"); return
        };
        const user = row.rows[0];
        if(req.body.username == user.username && req.body.senha == user.senha){
            req.session.user = user.username;
            req.session.userId = user.id;
            res.send("Logged in")
        }else{
            throw new Error("Wrong credentials"); return;
        }
    }).catch((err) => {
        res.send(`${err}`);
    });
});

router.get('/logout', async (req, res) => {
    if(!req.session.user) {res.send("Already Logged out"); return};
    req.session.destroy();
    res.send("Logged out");
});

